#include "NeoObject.h"
#include <string>
#include <iomanip>

void NeoObject::SetTransformations()
{


    glm::vec3 scaleXYZ = this->scaleXYZ;
    float XrotationDegrees = this->rotationXYZ[0];
    float YrotationDegrees = this->rotationXYZ[1];
    float ZrotationDegrees = this->rotationXYZ[2];
    glm::vec3 positionXYZ = this->originXYZ;


    // variables for this method
    glm::mat4 scale;
    glm::mat4 rotationX;
    glm::mat4 rotationY;
    glm::mat4 rotationZ;
    glm::mat4 translation;

    // set the scale value in the transform buffer
    scale = glm::scale(scaleXYZ);
    // set the rotation values in the transform buffer
    rotationX = glm::rotate(glm::radians(XrotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationY = glm::rotate(glm::radians(YrotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationZ = glm::rotate(glm::radians(ZrotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
    // set the translation value in the transform buffer
    
    translation = glm::translate(positionXYZ);

    this->modelView = translation * rotationZ * rotationY * rotationX * scale;
    this->objectOrigin.modelView = modelView;

}

void NeoObject::SetShapeTransformations()
{


    glm::vec3 scaleXYZ = this->scaleXYZ;
    float XrotationDegrees = this->rotationXYZ[0];
    float YrotationDegrees = this->rotationXYZ[1];
    float ZrotationDegrees = this->rotationXYZ[2];
    glm::vec3 positionXYZ = this->originXYZ;


    // variables for this method
    glm::mat4 scale;
    glm::mat4 rotationX;
    glm::mat4 rotationY;
    glm::mat4 rotationZ;
    glm::mat4 translation;

    // set the scale value in the transform buffer
    scale = glm::scale(scaleXYZ);
    // set the rotation values in the transform buffer
    rotationX = glm::rotate(glm::radians(XrotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
    rotationY = glm::rotate(glm::radians(YrotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
    rotationZ = glm::rotate(glm::radians(ZrotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
    // set the translation value in the transform buffer

    translation = glm::translate(positionXYZ);

    this->modelView = translation * rotationZ * rotationY * rotationX * scale;
    this->objectOrigin.modelView = modelView;

}



// This method calculates starting parameters for the object
void NeoObject::InitiateObject(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    this->scaleXYZ = scaleXYZ;
    this-> rotationXYZ = rotationXYZ;
    this->originXYZ = positionXYZ;
    
    this->objectOrigin = Box();
    this->objectOrigin.setColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    
    SetTransformations();

    //SetLocalVectors(scaleXYZ, rotationXYZ);

    //and more. Set the world offset
}


// Processes the relative position of a shape and calculates its position by factoring in object orientation and worldspace position
glm::vec3 NeoObject::GetWorldCoordOffset(int index) {
    glm::vec3 returnedCoordinates = glm::vec3 (0.0f, 0.0f, 0.0f);

    // Translate local X vertex into world space
    returnedCoordinates[0] += ((localVectorX[0] * localVectorX[3]) * this->shapePosNorm[index][0]);// Add scaled X coordinate to global coodinate
    returnedCoordinates[1] += (localVectorX[1] * localVectorX[3]) * this->shapePosNorm[index][0];// Add scaled Y coordinate to global coodinate
    returnedCoordinates[2] += (localVectorX[2] * localVectorX[3]) * this->shapePosNorm[index][0];// Add scaled Z coordinate to global coodinate

    // Translate local Y vertex into world space
    returnedCoordinates[0] += (localVectorY[0] * localVectorY[3]) * this->shapePosNorm[index][1];// Add scaled X coordinate to global coodinate
    returnedCoordinates[1] += (localVectorY[1] * localVectorY[3]) * this->shapePosNorm[index][1];// Add scaled Y coordinate to global coodinate
    returnedCoordinates[2] += (localVectorY[2] * localVectorY[3]) * this->shapePosNorm[index][1];// Add scaled Z coordinate to global coodinate

    // Translate local Z vertex into world space
    returnedCoordinates[0] += (localVectorZ[0] * localVectorZ[3]) * this->shapePosNorm[index][2];// Add scaled X coordinate to global coodinate
    returnedCoordinates[1] += (localVectorZ[1] * localVectorZ[3]) * this->shapePosNorm[index][2];// Add scaled Y coordinate to global coodinate
    returnedCoordinates[2] += (localVectorZ[2] * localVectorZ[3]) * this->shapePosNorm[index][2];// Add scaled Z coordinate to global coodinate

    //Add object origin to XYZ values
    returnedCoordinates[0] += originXYZ[0];
    returnedCoordinates[1] += originXYZ[1];
    returnedCoordinates[2] += originXYZ[2];


    return returnedCoordinates;
}

void NeoObject::AddShape(Shape shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    this->shapes.push_back(shape);
    this->shapeScaleNorm.push_back(scaleXYZ);
    this->shapeRotNorm.push_back(rotationXYZ);
    this->shapePosNorm.push_back(positionXYZ);
}

void NeoObject::TransformShapes() {
    //glm::vec3 currShapeScale;
    //glm::vec3 currShapeRot;
    //glm::vec3 currShapePos;

    //glm::vec3 scaleXYZ;
    //glm::vec3 rotationXYZ;
    //glm::vec3 originXYZ;

    for (int i = 0; i < this->shapes.size(); i ++){
        // Calculate shape scale
        
        /*
        currShapeScale = glm::vec3(
            (this->scaleXYZ[0] * this->shapeScaleNorm[i][0]),
            (this->scaleXYZ[1] * this->shapeScaleNorm[i][1]),
            (this->scaleXYZ[2] * this->shapeScaleNorm[i][2]));

        currShapeRot = glm::vec3(
            (this->rotationXYZ[0] + this->shapeRotNorm[i][0]),
            (this->rotationXYZ[1] + this->shapeRotNorm[i][1]),
            (this->rotationXYZ[2] + this->shapeRotNorm[i][2]));
        currShapePos = GetWorldCoordOffset(i);

            this->shapes[i].setScale(currShapeScale);
            this->shapes[i].setRotation(currShapeRot);
            this->shapes[i].setPosition(currShapePos);
        */





            ////////////////////


            /*
            glm::vec3 scaleXYZ = glm::vec3(
                (this->scaleXYZ[0] * this->shapeScaleNorm[i][0]),
                (this->scaleXYZ[1] * this->shapeScaleNorm[i][1]),
                (this->scaleXYZ[2] * this->shapeScaleNorm[i][2]));


            float XrotationDegrees = this->rotationXYZ[0] + this->shapeRotNorm[i][0];
            float YrotationDegrees = this->rotationXYZ[1] + this->shapeRotNorm[i][1];
            float ZrotationDegrees = this->rotationXYZ[2] + this->shapeRotNorm[i][2];
            glm::vec3 positionXYZ = GetWorldCoordOffset(i);


            // variables for this method
            glm::mat4 scale;
            glm::mat4 rotationX;
            glm::mat4 rotationY;
            glm::mat4 rotationZ;
            glm::mat4 translation;

            // set the scale value in the transform buffer
            scale = glm::scale(scaleXYZ);
            // set the rotation values in the transform buffer
            rotationX = glm::rotate(glm::radians(XrotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
            rotationY = glm::rotate(glm::radians(YrotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
            rotationZ = glm::rotate(glm::radians(ZrotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
            // set the translation value in the transform buffer

            translation = glm::translate(positionXYZ);

            this->shapes[i].modelView = translation * rotationZ * rotationY * rotationX * scale;*/
        glm::vec3 scaleXYZ = this->shapeScaleNorm[i];
        float XrotationDegrees = this->shapeRotNorm[i][0];
        float YrotationDegrees = this->shapeRotNorm[i][1];
        float ZrotationDegrees = this->shapeRotNorm[i][2];
        glm::vec3 positionXYZ = this->shapePosNorm[i];


        // variables for this method
        glm::mat4 scale;
        glm::mat4 rotationX;
        glm::mat4 rotationY;
        glm::mat4 rotationZ;
        glm::mat4 translation;

        // set the scale value in the transform buffer
        scale = glm::scale(scaleXYZ);
        // set the rotation values in the transform buffer
        rotationX = glm::rotate(glm::radians(XrotationDegrees), glm::vec3(1.0f, 0.0f, 0.0f));
        rotationY = glm::rotate(glm::radians(YrotationDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
        rotationZ = glm::rotate(glm::radians(ZrotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
        // set the translation value in the transform buffer

        translation = glm::translate(positionXYZ);

        this->shapes[i].modelView = this->modelView * (translation * rotationZ * rotationY * rotationX * scale);



    }
}

void NeoObject::LoadShapes() {}

// Public
std::vector<Shape> NeoObject::getShapes() {
    return shapes;
};

void NeoTest::LoadShapes() {
    glm::vec4 red = glm::vec4(1.0f, 0.5f, 0.5f, 1.0f);
    glm::vec4 green = glm::vec4(0.5f, 1.0f, 0.5f, 1.0f);
    glm::vec4 blue = glm::vec4(0.5f, 0.5f, 1.0f, 1.0f);

    /////// draw shapes
    // scope
    // X
    Sphere scope = Sphere();
    scope.setColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.001f));

    AddShape(
        scope,
        glm::vec3(0.01f, 0.01f, 0.01f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f));


    // X
    Box xb = Box();
    xb.setColor(red);

    AddShape(
        xb,
        glm::vec3(1.0f, 0.05f, 0.05f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.5f, 0.0f, 0.0f));

    // Y
    Box yb = Box();
    yb.setColor(green);

    AddShape(
        yb,
        glm::vec3(0.05f, 1.0f, 0.05f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.5f, 0.0f));

    // Z
    Box zb = Box();
    zb.setColor(blue);

    AddShape(
        zb,
        glm::vec3(0.05f, 0.05f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.5f));

    // X
    Sphere x = Sphere();
    x.setColor(red);

    AddShape(
        x,
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f));

    // Y
    Sphere y = Sphere();
    y.setColor(green);

    AddShape(
        y,
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));

    // Z
    Sphere z = Sphere();
    z.setColor(blue);

    AddShape(
        z,
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));

    // Origin
    Sphere o = Sphere();
    o.setColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

    AddShape(
        o,
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f));
}

NeoTest::NeoTest(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
    LoadShapes();
    TransformShapes();
}

void NeoInkwell::LoadShapes() {
    glm::vec4 glassColor = glm::vec4(0.2f, 0.2f, 0.2f, 0.7f);
    glm::vec4 inkColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 capColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    std::vector<std::string> capTextures = { "blackABSalt" , "blackABS" , "blackABS" };
    std::vector<float> capXVals = { 3,1,1 };
    std::vector<float> capYVals = { 1,1,1 };

    std::string labelFrontTexture = "labelFront";
    std::string labelLeftTexture = "labelLeft";
    std::string labelRightTexture = "labelRight";
    glm::vec4 labelColor = glm::vec4(0.3529f, 0.1686f, 0.3843f, 1.0f);

    /////// draw labels


    Plane labelFront = Plane();
    labelFront.setColor(labelColor);
    labelFront.setTexture(labelFrontTexture, 1.0f, 0.5f);

    AddShape(
        labelFront,
        glm::vec3(0.4f, 0.5f, 0.25f),
        glm::vec3(90.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.3f, 0.501f));

    Plane labelLeft = Plane();
    labelLeft.setColor(labelColor);
    labelLeft.setTexture(labelLeftTexture, 0.5f, 1.0f);

    AddShape(
        labelLeft,
        glm::vec3(0.1f, 0.5f, 0.25f),
        glm::vec3(90.0f, -90.0f, 0.0f),
        glm::vec3(-0.501f, 0.3f, 0.3f));

    Plane labelRight = Plane();
    labelRight.setColor(labelColor);
    labelRight.setTexture(labelRightTexture, 0.5f, 1.0f);

    AddShape(
        labelRight,
        glm::vec3(0.1f, 0.5f, 0.25f),
        glm::vec3(90.0f, 90.0f, 0.0f),
        glm::vec3(0.501f, 0.3f, 0.3f));

    /////// Draw bottom of vial

    Box Bottom = Box();
    Bottom.setColor(glassColor);

    AddShape(
        Bottom,
        glm::vec3(0.8f, 0.15f, 0.8f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.1f, 0.0f));

    Box ink = Box();
    ink.setColor(inkColor);

    AddShape(
        ink,
        glm::vec3(0.88f, 0.55f, 0.88f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.32f, 0.0f));

    Cylinder BottomLeftFillet = Cylinder();
    BottomLeftFillet.setColor(glassColor);

    AddShape(
        BottomLeftFillet,
        glm::vec3(0.05f, 0.8f, 0.1f),
        glm::vec3(-90.0f, 0.0f, 90.0f),
        glm::vec3(-0.4f, 0.05f, 0.4f));

    Cylinder BottomRightFillet = Cylinder();
    BottomRightFillet.setColor(glassColor);

    AddShape(
        BottomRightFillet,
        glm::vec3(0.05f, 0.8f, 0.1f),
        glm::vec3(-90.0f, 0.0f, 90.0f),
        glm::vec3(0.4f, 0.05f, 0.4f));

    Cylinder BottomFrontFillet = Cylinder();
    BottomFrontFillet.setColor(glassColor);

    AddShape(
        BottomFrontFillet,
        glm::vec3(0.05f, 0.8f, 0.1f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(0.4f, 0.05f, 0.4f));

    Cylinder BottomBackFillet = Cylinder();
    BottomBackFillet.setColor(glassColor);

    AddShape(
        BottomBackFillet,
        glm::vec3(0.05f, 0.8f, 0.1f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(0.4f, 0.05f, -0.4f));

    Sphere BottomBackLeftCorner = Sphere();
    BottomBackLeftCorner.setColor(glassColor);

    AddShape(
        BottomBackLeftCorner,
        glm::vec3(0.1f, 0.05f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-0.4f, 0.05f, -0.4f));

    Sphere BottomBackRightCorner = Sphere();
    BottomBackRightCorner.setColor(glassColor);

    AddShape(
        BottomBackRightCorner,
        glm::vec3(0.1f, 0.05f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.4f, 0.05f, -0.4f));

    Sphere BottomFrontLeftCorner = Sphere();
    BottomBackRightCorner.setColor(glassColor);

    AddShape(
        BottomBackRightCorner,
        glm::vec3(0.1f, 0.05f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-0.4f, 0.05f, 0.4f));

    Sphere BottomFrontRightCorner = Sphere();
    BottomFrontRightCorner.setColor(glassColor);

    AddShape(
        BottomFrontRightCorner,
        glm::vec3(0.1f, 0.05f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.40f, 0.05f, 0.40f));

    /////// Draw walls of vial

    Box wallLeft = Box();
    wallLeft.setColor(glassColor);

    AddShape(
        wallLeft,
        glm::vec3(0.1f, 0.5f, 0.8f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-0.45f, 0.3f, 0.0f));

    Box wallRight = Box();
    wallRight.setColor(glassColor);

    AddShape(
        wallRight,
        glm::vec3(0.1f, 0.5f, 0.8f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.45f, 0.3f, 0.0f));

    Box wallBack = Box();
    wallBack.setColor(glassColor);

    AddShape(
        wallBack,
        glm::vec3(0.8f, 0.5f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.3f, -0.45f));

    Box wallFront = Box();
    wallFront.setColor(glassColor);

    AddShape(
        wallFront,
        glm::vec3(0.8f, 0.5f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.3f, 0.45f));

    Cylinder wallFilletFrontLeft = Cylinder();
    wallFilletFrontLeft.setColor(labelColor);

    AddShape(
        wallFilletFrontLeft,
        glm::vec3(0.1f, 0.5f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-0.4f, 0.05f, 0.4f));

    Cylinder wallFilletFrontRight = Cylinder();
    wallFilletFrontRight.setColor(labelColor);

    AddShape(
        wallFilletFrontRight,
        glm::vec3(0.1f, 0.5f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.4f, 0.05f, 0.4f));

    Cylinder wallFilletBackLeft = Cylinder();
    wallFilletBackLeft.setColor(glassColor);

    AddShape(
        wallFilletBackLeft,
        glm::vec3(0.1f, 0.5f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-0.4f, 0.05f, -0.4f));

    Cylinder wallFilletBackRight = Cylinder();
    wallFilletBackRight.setColor(glassColor);

    AddShape(
        wallFilletBackRight,
        glm::vec3(0.1f, 0.5f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.4f, 0.05f, -0.4f));



    /////// Draw top of vial

    Box top = Box();
    top.setColor(glassColor);

    AddShape(
        top,
        glm::vec3(0.8f, 0.1f, 0.8f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.6f, 0.0f));

    Cylinder TopLeftFillet = Cylinder();
    TopLeftFillet.setColor(glassColor);

    AddShape(
        TopLeftFillet,
        glm::vec3(0.1f, 0.8f, 0.1f),
        glm::vec3(90.0f, 0.0f, 0.0f),
        glm::vec3(-0.40f, 0.55f, -0.40f));

    Cylinder TopRightFillet = Cylinder();
    TopRightFillet.setColor(glassColor);

    AddShape(
        TopRightFillet,
        glm::vec3(0.1f, 0.8f, 0.1f),
        glm::vec3(-90.0f, 0.0f, 0.0f),
        glm::vec3(0.4f, 0.55f, 0.4f));

    Cylinder TopFrontFillet = Cylinder();
    TopFrontFillet.setColor(glassColor);

    AddShape(
        TopFrontFillet,
        glm::vec3(0.1f, 0.8f, 0.1f),
        glm::vec3(0.0f, 0.0f, 90.0f),
        glm::vec3(0.4f, 0.55f, 0.4f));

    Cylinder TopBackFillet = Cylinder();
    TopBackFillet.setColor(glassColor);

    AddShape(
        TopBackFillet,
        glm::vec3(0.1f, 0.8f, 0.1f),
        glm::vec3(0.0f, 0.0f, -90.0f),
        glm::vec3(-0.4f, 0.55f, -0.4f));

    Sphere TopBackLeftCorner = Sphere();
    TopBackLeftCorner.setColor(glassColor);

    AddShape(
        TopBackLeftCorner,
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-0.4f, 0.55f, -0.4f));

    Sphere TopBackRightCorner = Sphere();
    TopBackRightCorner.setColor(glassColor);

    AddShape(
        TopBackRightCorner,
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.4f, 0.55f, -0.4f));

    Sphere TopFrontLeftCorner = Sphere();
    TopFrontLeftCorner.setColor(glassColor);

    AddShape(
        TopFrontLeftCorner,
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(-0.4f, 0.55f, 0.4f));

    Sphere TopFrontRightCorner = Sphere();
    TopFrontRightCorner.setColor(glassColor);

    AddShape(
        TopFrontRightCorner,
        glm::vec3(0.1f, 0.1f, 0.1f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.4f, 0.55f, 0.4f));

    /////// Draw stem of vial

    Cylinder stem = Cylinder();
    stem.setColor(glassColor);

    AddShape(
        stem,
        glm::vec3(0.25f, 0.17f, 0.25f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.60f, 0.0f));

    Torus stemLip = Torus();
    stemLip.setColor(glassColor);

    AddShape(
        stemLip,
        glm::vec3(0.23f, 0.23f, 0.23f),
        glm::vec3(90.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.71f, 0.0f));

    /////// Draw cap of vial

    Cylinder cap = Cylinder();
    cap.setColor(capColor);
    cap.setTextureSides(capTextures, capXVals, capYVals);

    AddShape(
        cap,
        glm::vec3(0.3f, 0.23f, 0.3f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.77f, 0.0f));


    Cylinder capLip = Cylinder();
    capLip.setColor(capColor);
    capLip.setTexture(capTextures[1], capXVals[1], capYVals[1]);

    AddShape(
        capLip,
        glm::vec3(0.2999f, 0.2302f, 0.299f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.7699f, 0.0f));





    /*
    Box box3 = Box();
    box3.setColor(blue);

    AddShape(
        box3,
        glm::vec3(1.0f, 0.33f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.8333f, 0.0f));*/
}

NeoInkwell::NeoInkwell(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
    LoadShapes();
    TransformShapes();
}

void NeoOrigin::LoadShapes() {
    glm::vec4 red = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 green = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    glm::vec4 blue = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    /////// draw shapes

    // X
    Box x = Box();
    x.setColor(red);

    AddShape(
        x,
        glm::vec3(1.0f, 0.05f, 0.05f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.5f, 0.0f, 0.0f));

    // Y
    Box y = Box();
    y.setColor(green);

    AddShape(
        y,
        glm::vec3(0.05f, 1.0f, 0.05f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.5f, 0.0f));

    // Z
    Box z = Box();
    z.setColor(blue);

    AddShape(
        z,
        glm::vec3(0.05f, 0.05f, 1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.5f));
}

NeoOrigin::NeoOrigin(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
    LoadShapes();
    TransformShapes();
}