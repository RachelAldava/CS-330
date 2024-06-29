///////////////////////////////////////////////////////////////////////////////
// Shape.cpp
// ============
//  This is the primary interface between the student code (my code) and the instructor code.
//  It houses the projection data for each shape in the scene and supplies the SceneManager with this data and rendering instructions.
//
//  AUTHOR: Rachel Aldava - SNHU Student / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, June, 2024
///////////////////////////////////////////////////////////////////////////////

#include "Shape.h"

// This will update the projection data for the Shape.
void Shape::SetLocalTransformations()
{
    glm::vec3 scaleXYZ = this->scaleXYZ;
    float XrotationDegrees = this->rotationXYZ[0];
    float YrotationDegrees = this->rotationXYZ[1];
    float ZrotationDegrees = this->rotationXYZ[2];
    glm::vec3 positionXYZ = this->positionXYZ;


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

    this->localModelView = translation * rotationZ * rotationY * rotationX * scale;
}

// Straighforward get and set methods
glm::mat4 Shape::GetView() {
    // We shouldn't mix local and global informations except when retriving view information
    this->totalView = transformations * localModelView;
    return this->totalView;
}

void Shape::SetTransformations(glm::mat4 transformations){
    this->transformations = transformations;
}

void Shape::setPosition(glm::vec3 positionXYZ) {
    this->positionXYZ = positionXYZ;
    this->SetLocalTransformations();
}

void Shape::setScale(glm::vec3 scaleXYZ) {
    this->scaleXYZ = scaleXYZ;
    this->SetLocalTransformations();
}

void Shape::setRotation(glm::vec3 rotationXYZ) {
    this->rotationXYZ = rotationXYZ;
    this->SetLocalTransformations();
}

void Shape::setColor(glm::vec4 color) {
    for (int i = 0; i < surfaces.size(); i++) {
        surfaces[i].setColor(color);
    }
}

// Sets each side with a color within supplied vector, enabling objects with different colored faces.
void Shape::setColorSides(std::vector<glm::vec4> colors) {
    int currColor = 0;
    for (int i = 0; i < surfaces.size(); i++) {
        surfaces[i].setColor(colors[currColor]);
        if (currColor + 1 < colors.size()) currColor++;
    }
}

void Shape::setTexture(Texture::textures texture, float x, float y) {
    for (int i = 0; i < surfaces.size(); i++) {
        surfaces[i].setTexture(Texture::GetTag(texture), x, y);
    }
}

// Sets each side with a texture within supplied vectors, enabling objects with different textured faces.
void Shape::setTextureSides(std::vector<std::string> textures, std::vector<float> xVals, std::vector<float> yVals) {
    int currTexture = 0;
    int currXVal = 0;
    int currYVal = 0;

    for (int i = 0; i < surfaces.size(); i++) {
        surfaces[i].setTexture(textures[currTexture], xVals[currYVal], yVals[currYVal]);
        if (currTexture + 1 < textures.size()) currTexture++;
        if (currXVal + 1 < xVals.size()) currXVal++;
        if (currYVal + 1 < yVals.size()) currYVal++;
    }
}

void Shape::setMaterial(Material::materials material) {
    for (int i = 0; i < surfaces.size(); i++) {
        surfaces[i].setMaterial(Material::GetTag(material));
    }
}

void Shape::modifyPosition(glm::vec3 positionXYZ) {
    this->positionXYZ += positionXYZ;
    this->SetLocalTransformations();
}

void Shape::modifyScale(glm::vec3 scaleXYZ) {
    this->scaleXYZ += scaleXYZ;
    if (this->scaleXYZ[0] < 0) this->scaleXYZ[0] = 0;
    if (this->scaleXYZ[1] < 0) this->scaleXYZ[1] = 0;
    if (this->scaleXYZ[2] < 0) this->scaleXYZ[2] = 0;
    this->SetLocalTransformations();
}

void Shape::modifyRotation(glm::vec3 rotationXYZ) {
    this->rotationXYZ += rotationXYZ;
    this->SetLocalTransformations();
}


// The main thrust of this Class is this method. 
// It enables the abstraction of shapes by generalizing the properties while still retaining 
//   the ability to call the different rendering methods supplied by the instructor code.
void Shape::Render(ShapeMeshes* m_basicMeshes, int faceIndex) {
    /*
    box,
    cone,
    cylinder,
    plane,
    prism,
    pyramid3,
    pyramid4,
    sphere,
    taperedCylinder,
    torus
    */

    switch (shapeType) {
    case box:
        switch (faceIndex) {
        case 0:
            m_basicMeshes->DrawBoxMeshSide(ShapeMeshes::front);
            break;
        case 1:
            m_basicMeshes->DrawBoxMeshSide(ShapeMeshes::back);
            break;
        case 2:
            m_basicMeshes->DrawBoxMeshSide(ShapeMeshes::left);
            break;
        case 3:
            m_basicMeshes->DrawBoxMeshSide(ShapeMeshes::right);
            break;
        case 4:
            m_basicMeshes->DrawBoxMeshSide(ShapeMeshes::top);
            break;
        case 5:
            m_basicMeshes->DrawBoxMeshSide(ShapeMeshes::bottom);
            break;
        }
        break;
    case cone:
        m_basicMeshes->DrawConeMesh();
        break;
    case cylinder:
        switch (faceIndex) {
        case 0:
            m_basicMeshes->DrawCylinderMesh(true, false, false);
        case 1:
            m_basicMeshes->DrawCylinderMesh(false, true, false);
        case 2:
            m_basicMeshes->DrawCylinderMesh(false, false, true);
        }
        break;
    case plane:
        m_basicMeshes->DrawPlaneMesh();
        break;
    case prism:
        m_basicMeshes->DrawPrismMesh();
        break;
    case pyramid3:
        m_basicMeshes->DrawPyramid3Mesh();
        break;
    case pyramid4:
        m_basicMeshes->DrawPyramid4Mesh();
        break;
    case sphere:
        m_basicMeshes->DrawSphereMesh();
        break;
    case taperedCylinder:
        m_basicMeshes->DrawTaperedCylinderMesh();
        break;
    case torus:
        m_basicMeshes->DrawTorusMesh();
        break;

    }
}

// Common constructor instructions shared by all constructors.
void Shape::InitiateShape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    this->shapeType = shape;
    this->scaleXYZ = scaleXYZ;
    this->rotationXYZ = rotationXYZ;
    this->positionXYZ = positionXYZ;
    for (int i = 0; i < 6; i++) this->surfaces.push_back(Surface());
    this->SetLocalTransformations();
    this->transformations = glm::mat4(1.0f);// blank transformations
}

// When the details of a shape don't matter
Shape::Shape() {
    this->InitiateShape(box, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
}

// When the form of the shape only matters
Shape::Shape(shapes shape) {
    this->InitiateShape(shape, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
}

// when an object with a form, scale, rotation, and position is needed, but colors and textures, and materials are not important.
Shape::Shape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    this->InitiateShape(shape, scaleXYZ, rotationXYZ, positionXYZ);
}

// For colors without materials.
Shape::Shape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, glm::vec4 color) {
    this->InitiateShape(shape, scaleXYZ, rotationXYZ, positionXYZ);
    this->setColor(color);
}

// for colors with materials.
Shape::Shape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, glm::vec4 color, Material::materials material) {
    this->InitiateShape(shape, scaleXYZ, rotationXYZ, positionXYZ);
    this->setColor(color);
    this->setMaterial(material);
}

// for textures without materials
Shape::Shape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, Texture::textures texture, float x, float y) {
    this->InitiateShape(shape, scaleXYZ, rotationXYZ, positionXYZ);
    this->setTexture(texture, x, y);
}

// for textures with materials
Shape::Shape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, Texture::textures texture, float x, float y, Material::materials material) {
    this->InitiateShape(shape, scaleXYZ, rotationXYZ, positionXYZ);
    this->setTexture(texture, x, y);
    this->setMaterial(material);
}

