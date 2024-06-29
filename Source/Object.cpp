///////////////////////////////////////////////////////////////////////////////
// Object.h
// ============
//  Objects are groups of Shapes.
// 
//  This class contains the bulk of the project. It provides a framework for 
//  working with Shapes which enables groups of shapes to easily be formed.
//  This includes the ability to add objects to other objects.
// 
//  All objects, when properly defined, will support full scaling, rotation, and 
//     repositioning of all component shapes and component objects.
// 
//  AUTHOR: Rachel Aldava - SNHU Student / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, June, 2024
///////////////////////////////////////////////////////////////////////////////

#include "Object.h"
#include <string>
#include <iomanip>

// This method calculates starting parameters for the object
void Object::InitiateObject(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {

    // Populate shapes vector with shapes.
    for (Shape* shapeptr : definedShapes) {
        allShapes.push_back(shapeptr);
    }

    // Populate shapes vector with shapes from each sub-object.
    std::vector<Shape*> theseShapes;
    for (Object* objectptr : definedObjects) {
        theseShapes = objectptr->GetShapes();
        for (Shape* shapes : theseShapes) {
            allShapes.push_back(shapes);
        }
    }

    // define a Shape to hold global information about the object.
    this->origin = Shape(
        Shape::box,
        scaleXYZ,
        rotationXYZ,
        positionXYZ,
        glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)
    );

    TransformShapes();
}

void Object::AddToObject(Shape* shape) {
    this->definedShapes.push_back(shape);
}

void Object::AddToObject(Object* object) {
    this->definedObjects.push_back(object);
}

void Object::TransformShapes() {
    for (int i = 0; i < this->definedShapes.size(); i++) {
        this->definedShapes[i]->SetTransformations(origin.GetView());
    }

    for (int i = 0; i < this->definedObjects.size(); i++) {
        this->definedObjects[i]->SetTransformations(origin.GetView());
    }
}

void Object::LoadShapes() {}

Object::Object(){}

// Public

// Typical get methods
std::vector<Shape*> Object::GetShapes() {
    return allShapes;
};

glm::mat4 Object::GetView() {
    return origin.GetView();
}


// These methods modify the object object origin shape, then call methods to adjust all object shapes based off of the new origin

void Object::SetTransformations(glm::mat4 transformations) {
    origin.SetTransformations(transformations);
    TransformShapes();
}

void Object::setPosition(glm::vec3 positionXYZ) {
    origin.setPosition(positionXYZ);
    TransformShapes();
}

void Object::setScale(glm::vec3 scaleXYZ) {
    origin.setScale(scaleXYZ);
    TransformShapes();
}

void Object::setRotation(glm::vec3 rotationXYZ) {
    origin.setRotation(rotationXYZ);
    TransformShapes();
}


void Object::modifyPosition(glm::vec3 positionXYZ) {
    origin.modifyPosition(positionXYZ);
    TransformShapes();
}

void Object::modifyScale(glm::vec3 scaleXYZ) {
    origin.modifyScale(scaleXYZ);
    TransformShapes();
}

void Object::modifyRotation(glm::vec3 rotationXYZ) {
    origin.modifyRotation(rotationXYZ);
    TransformShapes();
}

/***********************************************************
 *  Children
 *
 *  All further methods involve children of the Object class.
 ***********************************************************/

void Chessman::LoadShapes() {
    // Shape #1 - Cylinder #1
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.145f, 0.05f, 0.145f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            texture, 0.145f, 0.145f,
            material
        )
    );


    // Shape #2 - TapCylinder #1
    AddToObject(
        new Shape(
            Shape::taperedCylinder,
            glm::vec3(0.145f, 0.25f, 0.145f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.05f, 0.0f),
            texture, 0.25f, 0.25f,
            material
        )
    );

    // Shape #3 - Torus #1
    AddToObject(
        new Shape(
            Shape::torus,
            glm::vec3(0.125f, 0.125f, 0.12f),
            glm::vec3(90.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.075f, 0.0f),
            texture, 0.25f, 0.25f,
            material
        )
    );



    // Shape #4 - TapCylinder #2 (inverted)
    AddToObject(
        new Shape(
            Shape::taperedCylinder,
            glm::vec3(0.125f, 0.22f, 0.125f),
            glm::vec3(180.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.23f, 0.0f),
            texture, 0.22f, 0.22f,
            material
        )
    );


    // Shape #5 - TapCylinder #3 
    AddToObject(
        new Shape(
            Shape::taperedCylinder,
            glm::vec3(0.11f, 0.54f, 0.11f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.23f, 0.0f),
            texture, 0.54f, 0.54f,
            material
        )
    );



    

    switch (this->variant) {
    case pawn:

        // Shape #6 - Cylinder #2
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.09f, 0.15f, 0.09f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.43f, 0.0f),
                texture, 0.9f, 0.9f,
                material
            )
        );



        // Shape #7 - Cylinder #3
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.14f, 0.05f, 0.14f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.58f, 0.0f),
                texture, 0.14f, 0.14f,
                material
            )
        );

        // Shape #8 - Cylinder #4
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.11f, 0.01f, 0.11f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.63f, 0.0f),
                texture, 0.11f, 0.11f,
                material
            )
        );

        //Shape #9 - sphere
        AddToObject(
            new Shape(
                Shape::sphere,
                glm::vec3(0.11f, 0.11f, 0.11f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.75f, 0.0f),
                texture, 0.05f, 0.05f,
                material
            )
        );
        break;
    case rook:
        //Shape #6 - taperedCylinder
        AddToObject(
            new Shape(
                Shape::taperedCylinder,
                glm::vec3(0.14f, 0.1f, 0.14f),
                glm::vec3(180.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.7f, 0.0f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        //Shape #7 - cylinder
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.14f, 0.1f, 0.14f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.7f, 0.0f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        //Shape #8 - box
        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.06f, 0.06f, 0.06f),
                glm::vec3(0.0f, 45.0f, 0.0f),
                glm::vec3(-0.0758f, 0.83f, -0.0758f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        //Shape #9 - box
        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.06f, 0.06f, 0.06f),
                glm::vec3(0.0f, 45.0f, 0.0f),
                glm::vec3(0.0758f, 0.83f, -0.0758f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        //Shape #10 - box
        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.06f, 0.06f, 0.06f),
                glm::vec3(0.0f, 45.0f, 0.0f),
                glm::vec3(-0.0758f, 0.83f, 0.0758f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        //Shape #11 - box
        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.06f, 0.06f, 0.06f),
                glm::vec3(0.0f, 45.0f, 0.0f),
                glm::vec3(0.0758f, 0.83f, 0.0758f),
                texture, 0.05f, 0.05f,
                material
            )
        );


        //Shape #12 - box
        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.06f, 0.06f, 0.06f),
                glm::vec3(0.0f, .0f, 0.0f),
                glm::vec3(0.106f, 0.83f, 0.0f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        //Shape #13 - box
        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.06f, 0.06f, 0.06f),
                glm::vec3(0.0f, .0f, 0.0f),
                glm::vec3(-0.106f, 0.83f, 0.0f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        //Shape #14 - box
        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.06f, 0.06f, 0.06f),
                glm::vec3(0.0f, .0f, 0.0f),
                glm::vec3(0.0f, 0.83f, 0.106f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        //Shape #15 - box
        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.06f, 0.06f, 0.06f),
                glm::vec3(0.0f, .0f, 0.0f),
                glm::vec3(0.0f, 0.83f, -0.106f),
                texture, 0.05f, 0.05f,
                material
            )
        );



        break;
    case knight:
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.13f, 0.15f, 0.13f),
                glm::vec3(0.0f, 0.0f, 90.0f),
                glm::vec3(0.15f /2, 0.4f, -0.0f),
                texture, 0.9f, 0.9f,
                material
            )
        );

        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.1495f, 0.3f, 0.26f),
                glm::vec3(-12.0f, 0.0f, 0.0f),
                glm::vec3(0, 0.55f, -0.035f),
                texture, 0.9f, 0.9f,
                material
            )
        );

        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.149f, 0.22f, 0.26f),
                glm::vec3(15.0f, 0.0f, 0.0f),
                glm::vec3(0, 0.74f, -0.04f),
                texture, 0.9f, 0.9f,
                material
            )
        );

        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.13f, 0.15f, 0.22f),
                glm::vec3(0.0f, -30.0f, 90.0f),
                glm::vec3(0.15f / 2, 0.75f, 0.05f),
                texture, 0.9f, 0.9f,
                material
            )
        );
        break;
    case bishop:

        // Shape #6 - Cylinder #2
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.09f, 0.15f, 0.09f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.43f, 0.0f),
                texture, 0.9f, 0.9f,
                material
            )
        );

        // Shape #7 - Cylinder #3
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.14f, 0.05f, 0.14f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.58f, 0.0f),
                texture, 0.14f, 0.14f,
                material
            )
        );

        // Shape #8 - Cylinder #4
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.11f, 0.01f, 0.11f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.63f, 0.0f),
                texture, 0.11f, 0.11f,
                material
            )
        );

        // Shape #9 - Torus #2
        AddToObject(
            new Shape(
                Shape::torus,
                glm::vec3(0.065f, 0.065f, 0.04f),
                glm::vec3(90.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.69f, 0.0f),
                texture, 0.065f, 0.065f,
                material
            )
        );

        // Shape #10 - sphere
        AddToObject(
            new Shape(
                Shape::sphere,
                glm::vec3(0.105f, 0.18f, 0.105),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.75f, 0.0f),
                texture, 0.17f, 0.17f,
                material
            )
        );

        // Shape #11 - sphere
        AddToObject(
            new Shape(
                Shape::sphere,
                glm::vec3(0.04f, 0.04f, 0.04),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.95f, 0.0f),
                texture, 0.17f, 0.17f,
                material
            )
        );
        break;
    case queen:

        // Shape #6 - Cylinder #2
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.09f, 0.15f, 0.09f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.43f, 0.0f),
                texture, 0.9f, 0.9f,
                material
            )
        );



        // Shape #7 - Cylinder #3
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.14f, 0.05f, 0.14f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.58f, 0.0f),
                texture, 0.14f, 0.14f,
                material
            )
        );

        // Shape #8 - Cylinder #4
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.11f, 0.01f, 0.11f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.63f, 0.0f),
                texture, 0.11f, 0.11f,
                material
            )
        );
        // Shape #9 - Torus #2
        AddToObject(
            new Shape(
                Shape::torus,
                glm::vec3(0.065f, 0.065f, 0.04f),
                glm::vec3(90.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.69f, 0.0f),
                texture, 0.065f, 0.065f,
                material
            )
        );

        // Shape #10 - TapCylinder #4 (inverted)
        AddToObject(
            new Shape(
                Shape::taperedCylinder,
                glm::vec3(0.12f, 0.17f, 0.12f),
                glm::vec3(180.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.86f, 0.0f),
                texture, 0.17f, 0.17f,
                material
            )
        );

        // Shape #11 - torus
        AddToObject(
            new Shape(
                Shape::torus,
                glm::vec3(0.095f, 0.095f, 0.095f),
                glm::vec3(90.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.85f, 0.0f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        //Shape #12 - sphere
        AddToObject(
            new Shape(
                Shape::sphere,
                glm::vec3(0.05f, 0.04f, 0.05f),
                glm::vec3(90.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.9f, 0.0f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        break;
    case king:

        // Shape #6 - Cylinder #2
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.09f, 0.15f, 0.09f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.43f, 0.0f),
                texture, 0.9f, 0.9f,
                material
            )
        );



        // Shape #7 - Cylinder #3
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.14f, 0.05f, 0.14f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.58f, 0.0f),
                texture, 0.14f, 0.14f,
                material
            )
        );

        // Shape #8 - Cylinder #4
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.11f, 0.01f, 0.11f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.63f, 0.0f),
                texture, 0.11f, 0.11f,
                material
            )
        );
        // Shape #9 - Torus #2
        AddToObject(
            new Shape(
                Shape::torus,
                glm::vec3(0.065f, 0.065f, 0.04f),
                glm::vec3(90.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.69f, 0.0f),
                texture, 0.065f, 0.065f,
                material
            )
        );

        // Shape #10 - TapCylinder #4 (inverted)
        AddToObject(
            new Shape(
                Shape::taperedCylinder,
                glm::vec3(0.12f, 0.17f, 0.12f),
                glm::vec3(180.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.86f, 0.0f),
                texture, 0.17f, 0.17f,
                material
            )
        );

        // Shape #11 - Cylinder #6
        AddToObject(
            new Shape(
                Shape::cylinder,
                glm::vec3(0.05f, 0.04f, 0.05f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.86f, 0.0f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        // Shape #12 - RecPrism Vertical
        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.05f, 0.1f, 0.05f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.95f, 0.0f),
                texture, 0.05f, 0.05f,
                material
            )
        );

        // Shape #13 - RecPrism Horizontal
        AddToObject(
            new Shape(
                Shape::box,
                glm::vec3(0.048f, 0.1f, 0.048f),
                glm::vec3(0.0f, 0.0f, 90.0f),
                glm::vec3(0.0f, 0.95f, 0.0f),
                texture, 0.05f, 0.05f,
                material
            )
        );
        break;
    }

}

Chessman::Chessman(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, colors color, variants variant) {
    this->color = color;
    this->variant = variant;

    if (color == white) {
        texture = Texture::woodLight;
        material = Material::woodLightMatte;
    }
    else {
        texture = Texture::woodDark;
        material = Material::woodDarkMatte;
    }
    switch (variant) {
    case pawn:
        scaleOffset = .7;
        break;
    case rook:
        scaleOffset = .8;
        break;
    case knight:
        scaleOffset = .8;
        break;
    case bishop:
        scaleOffset = .8;
        break;
    case queen:
        scaleOffset = 1;
        break;
    case king:
        scaleOffset = 1;
        break;
    }
    LoadShapes();

    glm::vec3 scaleAdjusted = glm::vec3(scaleXYZ[0] * scaleOffset, scaleXYZ[1] * scaleOffset, scaleXYZ[2] * scaleOffset);

    InitiateObject(scaleAdjusted, rotationXYZ, positionXYZ);
}

void Inkwell::LoadShapes() {
    glm::vec4 glassColor = glm::vec4(0.4f, 0.4f, 0.4f, 0.2f);

    //glm::vec4 glassColor = glm::vec4(0.7f, 0.9f, 0.7f, 0.2f);
    Material::materials glass = Material::glass;
    Material::materials ABS = Material::ABS;

    glm::vec4 inkColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 capColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    Texture::textures capWallTexture = Texture::blackABS;

    Material::materials paper = Material::paper;
    Texture::textures labelTexture = Texture::inklabel;
    glm::vec4 labelColor = glm::vec4(0.3529f, 0.1686f, 0.3843f, 1.0f);


    /////// draw label

    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.4f, 0.5f, 0.25f),// scale
            glm::vec3(90.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.3f, 0.501f),// position
            labelTexture, 1.0f, 0.5f, // texture
            paper // material
        )
    );

    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.1f, 0.5f, 0.25f),// scale
            glm::vec3(90.0f, -90.0f, 0.0f),// rotation
            glm::vec3(-0.501f, 0.3f, 0.3f),// position
            labelColor, // color
            paper // material
        )
    );

    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.1f, 0.5f, 0.25f),// scale
            glm::vec3(90.0f, 90.0f, 0.0f),// rotation
            glm::vec3(0.501f, 0.3f, 0.3f),// position
            labelColor, // color
            paper // material
        )
    );

    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.0717f, 0.5f, 0.25f),// scale
            glm::vec3(90.0f, 45.0f, 0.0f),// rotation
            glm::vec3(0.4505f, 0.3f, 0.4505f),// position
            labelColor, // color
            paper // material
        )
    );

    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.0717f, 0.5f, 0.25f),// scale
            glm::vec3(90.0f, -45.0f, 0.0f),// rotation
            glm::vec3(-0.4505f, 0.3f, 0.4505f),// position
            labelColor, // color
            paper // material
        )
    );

    /////// Draw bottom of vial

    // bottom
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.8f, 0.15f, 0.8f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.1f, 0.0f),// position
            glassColor, // color
            glass // material
        )
    );

    // ink
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.88f, 0.55f, 0.88f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.32f, 0.0f),// position
            inkColor, // color
            glass // material
        )
    );

    // Bottom left fillet
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.05f, 0.8f, 0.1f),// scale
            glm::vec3(-90.0f, 0.0f, 90.0f),// rotation
            glm::vec3(-0.4f, 0.05f, 0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // Bottom right fillet
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.05f, 0.8f, 0.1f),// scale
            glm::vec3(-90.0f, 0.0f, 90.0f),// rotation
            glm::vec3(0.4f, 0.05f, 0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // bottom front fillet
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.05f, 0.8f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 90.0f),// rotation
            glm::vec3(0.4f, 0.05f, 0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // bottom back fillet
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.05f, 0.8f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 90.0f),// rotation
            glm::vec3(0.4f, 0.05f, -0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // bottom back left corner
    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.1f, 0.05f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.4f, 0.05f, -0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // bottom back right corner
    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.1f, 0.05f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.4f, 0.05f, -0.4f),// position
            glassColor, // color
            glass // material
        )
    );
 
    // bottom back right corner
    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.1f, 0.05f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.4f, 0.05f, 0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // bottom front right corner
    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.1f, 0.05f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.40f, 0.05f, 0.40f),// position
            glassColor, // color
            glass // material
        )
    );

    /////// Draw walls of vial

    // wall left
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.1f, 0.5f, 0.8f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.45f, 0.3f, 0.0f),// position
            glassColor, // color
            glass // material
        )
    );

    // wall right
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.1f, 0.5f, 0.8f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.45f, 0.3f, 0.0f),// position
            glassColor, // color
            glass // material
        )
    );

    // wall back
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.8f, 0.5f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.3f, -0.45f),// position
            glassColor, // color
            glass // material
        )
    );

    // wall front
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.8f, 0.5f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.3f, 0.45f),// position
            glassColor, // color
            glass // material
        )
    );

    // wall fillet front left
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.1f, 0.5f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.4f, 0.05f, 0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // wall fillet front right
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.1f, 0.5f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.4f, 0.05f, 0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // wall fillet back left
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.1f, 0.5f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.4f, 0.05f, -0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // wall fillet back right
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.1f, 0.5f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.4f, 0.05f, -0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    /////// Draw top of vial

    // top
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.8f, 0.1f, 0.8f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.6f, 0.0f),// position
            glassColor, // color
            glass // material
        )
    );

    // top left fillet
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.1f, 0.8f, 0.1f),// scale
            glm::vec3(90.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.40f, 0.55f, -0.40f),// position
            glassColor, // color
            glass // material
        )
    );

    // top right fillet
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.1f, 0.8f, 0.1f),// scale
            glm::vec3(-90.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.4f, 0.55f, 0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // top front fillet
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.1f, 0.8f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 90.0f),// rotation
            glm::vec3(0.4f, 0.55f, 0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // top back fillet
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.1f, 0.8f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, -90.0f),// rotation
            glm::vec3(-0.4f, 0.55f, -0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // top back left corner
    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.1f, 0.1f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.4f, 0.55f, -0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // top back right corner
    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.1f, 0.1f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.4f, 0.55f, -0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // top front left corner
    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.1f, 0.1f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.4f, 0.55f, 0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    // top front right corner
    AddToObject(
        new Shape(
            Shape::sphere,
            glm::vec3(0.1f, 0.1f, 0.1f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.4f, 0.55f, 0.4f),// position
            glassColor, // color
            glass // material
        )
    );

    /////// Draw stem of vial

    // stem
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.25f, 0.17f, 0.25f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.60f, -0.12f),// position
            glassColor, // color
            glass // material
        )
    );

    // stemlip
    AddToObject(
        new Shape(
            Shape::torus,
            glm::vec3(0.23f, 0.23f, 0.23f),// scale
            glm::vec3(90.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.71f, -0.12f),// position
            glassColor, // color
            glass // material
        )
    );

    /////// Draw cap of vial

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.3f, 0.23f, 0.3f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.77f, -0.12f),// position
            capWallTexture, 3, 1, // texture
            ABS // material
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.2999f, 0.2302f, 0.299f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.7699f, -0.12f),// position
            capColor, // color
            ABS // material
        )
    );
}

Inkwell::Inkwell(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    LoadShapes();
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
}

void Pen::LoadShapes() {
    glm::vec4 glassColor = glm::vec4(0.4f, 0.4f, 0.4f, 0.2f);

    //glm::vec4 glassColor = glm::vec4(0.7f, 0.9f, 0.7f, 0.2f);
    Material::materials nylon = Material::ABS;
    Material::materials ABS = Material::ABS;
    Material::materials steel = Material::chrome;

    glm::vec4 ABSColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    Texture::textures nylonTexture = Texture::nylonGlitter;
    Texture::textures steelTexture = Texture::stainless;


    /////// draw body

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.05f, 0.023f, 0.05f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.977f, 0.0f),// position
            ABSColor,
            ABS // material
        )
    );
    
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.05f, 0.62f, 0.05f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.357f, 0.0f),// position
            nylonTexture, 1.0f, 0.5f, // texture
            nylon // material
        )
    );


    // draw section
    
    AddToObject(
        new Shape(
            Shape::taperedCylinder,
            glm::vec3(0.05f, 0.19f, 0.05f),// scale
            glm::vec3(180.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.357f, 0.0f),// position
            ABSColor,
            nylon // material
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.0354f, 0.123f, 0.0354f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.147f, 0.0f),// position
            ABSColor,
            ABS // material
        )
    );

    AddToObject(
        new Shape(
            Shape::torus,
            glm::vec3(0.034f, 0.034f, 0.034f),// scale
            glm::vec3(90.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.159f, 0.0f),// position
            ABSColor,
            nylon // material
        )
    );

    // draw nib

    AddToObject(
        new Shape(
            Shape::cone,
            glm::vec3(0.0354f, 0.06923f, 0.0154f),// scale
            glm::vec3(174.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.06923f, 0.005f),// position
            steelTexture, 1,1 ,
            steel // material
        )
    );

    AddToObject(
        new Shape(
            Shape::taperedCylinder,
            glm::vec3(0.0354f, 0.15f, 0.0154f),// scale
            glm::vec3(7.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.06923f, 0.005f),// position
            steelTexture, 1, 1,
            steel // material
        )
    );

    // draw feed

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.027f, 0.08f, 0.018f),// scale
            glm::vec3(180.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.147f, 0.0f),// position
            ABSColor,
            ABS // material
        )
    );

    AddToObject(
        new Shape(
            Shape::cone,
            glm::vec3(0.027f, 0.06f, 0.018f),// scale
            glm::vec3(172.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.06923f, 0.0f),// position
            ABSColor,
            steel // material
        )
    );
}

Pen::Pen(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    LoadShapes();
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
}

void Room::LoadShapes() {
    Texture::textures textureWall = Texture::wall;
    Texture::textures textureFloor = Texture::floor;
    glm::vec4 ceilingColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    Material::materials materialWall = Material::paper;
    Material::materials materialFloor = Material::paper;

    // add floor
    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.5f, 0.0f, 0.5f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.0f, 0.0f),// position
            textureFloor, 2, 2, // texture
            materialFloor // material
        )
    );

    // Add walls
    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.5f, 0.0f, 0.4f),// scale
            glm::vec3(90.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.4f, -0.5f),// position
            textureWall, 5.0f, 4.0f, // texture
            materialFloor // material
        )
    );

    
    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.5f, 0.0f, 0.4f),// scale
            glm::vec3(-90.0f, 0.0f, 180.0f),// rotation
            glm::vec3(0.0f, 0.4f, 0.5f),// position
            textureWall, 5.0f, 4.0f, // texture
            materialFloor // material
        )
    );

    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.5f, 0.0f, 0.4f),// scale
            glm::vec3(0.0f, -90.0f, 90.0f),// rotation
            glm::vec3(0.5f, 0.4f, 0.0f),// position
            textureWall, 5.0f, 4.0f, // texture
            materialFloor // material
        )
    );

    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.5f, 0.0f, 0.4f),// scale
            glm::vec3(0.0f, 90.0f, -90.0f),// rotation
            glm::vec3(-0.5f, 0.4f, 0.0f),// position
            textureWall, 5.0f, 4.0f, // texture
            materialFloor // material
        )
    );

    // Add ceiling
    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.5f, 0.0f, 0.5f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.8f, 0.0f),// position
            ceilingColor,// color
            materialFloor // material
        )
    );

    AddToObject(new CornerDesk(glm::vec3(0.45f, 0.5f, 0.45f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-0.25f, 0.0f, -0.25f), CornerDesk::withScene));
    AddToObject(new CornerDesk(glm::vec3(0.45f, 0.5f, 0.45f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(-0.25f, 0.0f, 0.25f)));

    AddToObject(new Moulding(glm::vec3(1.0f, 0.02f, 0.01f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0, 0, -.5)));
    AddToObject(new Moulding(glm::vec3(1.0f, 0.02f, 0.01f), glm::vec3(0.0f, -90.0f, 0.0f), glm::vec3(.5, 0, 0)));
    AddToObject(new Moulding(glm::vec3(1.0f, 0.02f, 0.01f), glm::vec3(0.0f, 180.0f, 0.0f), glm::vec3(0, 0, .5)));
    AddToObject(new Moulding(glm::vec3(1.0f, 0.02f, 0.01f), glm::vec3(0.0f, 90.0f, 0.0f), glm::vec3(-.5, 0, 0)));
}

Room::Room(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    LoadShapes();
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
}

void Moulding::LoadShapes() {
    glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    Material::materials material = Material::paper;

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(1.0f, 0.25f, 1.0f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.125f, 0.5f),// position
            color, // color
            material // material
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.25f, 1.0f, 0.5f),// scale
            glm::vec3(0.0f, 0.0f, 90.0f),// rotation
            glm::vec3(0.5f, 0.25f, 0.5f),// position
            color, // color
            material // material
        )
    );

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(1.0f, 0.5f, 0.5f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.5f, 0.25f),// position
            color, // color
            material // material
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.25f, 1.0f, 0.25f),// scale
            glm::vec3(0.0f, 0.0f, 90.0f),// rotation
            glm::vec3(0.5f, 0.75f, 0.25f),// position
            color, // color
            material // material
        )
    );

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(1.0f, 0.25f, 0.25f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.875f, 0.125f),// position
            color, // color
            material // material
        )
    );

}

Moulding::Moulding(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    LoadShapes();
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
}

void CornerDesk::LoadShapes() {
    Texture::textures texture = Texture::woodDark;
    Material::materials material = Material::woodDarkSemigloss;

    // add desktop
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.33f, 0.008f, 1.0f),// scale
            glm::vec3(0.0f, 90.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.496f, -0.335f),// position
            texture, 3.0f, 6.0f, // texture
            material // material
        )
    );

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.33f, 0.008f, 0.67f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.335, 0.496f, 0.165f),// position
            texture, 2.5f, 3.6f, // texture
            material // material
        )
    );

    // add legs
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(.04, 0.492f, .04),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.45f, 0.248f, -0.45f),// position
            texture, 0.1f, 4.0f, // texture
            material // material
        )
    );

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(.04, 0.492f, .04),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.45f, 0.248f, 0.45f),// position
            texture, 0.1f, 4.0f, // texture
            material // material
        )
    );

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(.04, 0.492f, .04),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(-0.22f, 0.248f, 0.45f),// position
            texture, 0.1f, 4.0f, // texture
            material // material
        )
    );

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(.04, 0.492f, .04),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.45f, 0.248f, -0.45f),// position
            texture, 0.1f, 4.0f, // texture
            material // material
        )
    );

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(.04, 0.492f, .04),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.45f, 0.248f, -0.22f),// position
            texture, 0.1f, 4.0f, // texture
            material // material
        )
    );
}

CornerDesk::CornerDesk(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    LoadShapes();
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
}

CornerDesk::CornerDesk(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, variants variant) {
    LoadShapes();
    switch (variant) {
    case blank:
        break;
    case withScene:
        LoadShapesAlt1();
        break;
    }
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
}

void CornerDesk::LoadShapesAlt1(){
    AddToObject(new SceneGroup(glm::vec3(0.333f, 0.333f, 0.333f), glm::vec3(0.0f, -12.0f, 0.0f), glm::vec3(0.335f, 0.5f, -0.36f)));
}

void SceneGroup::LoadShapes() {

    AddToObject(new Chessman(glm::vec3(0.175f, 0.175f, 0.175f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.013f, 0.0f, -0.03f), Chessman::white, Chessman::king));
    AddToObject(new Inkwell(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, -45.0f, 0.0f), glm::vec3(0.22f, 0.0f, -0.03f)));
    AddToObject(new Pen(glm::vec3(0.27f, 0.27f, 0.27f), glm::vec3(-90.0f, 45.0f, 0.0f), glm::vec3(0.295f, 0.08f, 0.094f)));
    AddToObject(new Binder(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.25f)));
}

SceneGroup::SceneGroup(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    LoadShapes();
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
}

void Binder::LoadShapes() {
    Texture::textures metalTex = Texture::stainless;
    Texture::textures paperTex = Texture::name;
    Texture::textures leatherTex = Texture::leather;
    Material::materials metalMat = Material::chrome;
    Material::materials paperMat = Material::paper;
    Material::materials leatherMat = Material::leather;

    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.85f, 0.01f, 0.7f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.0051f, 0.0f),// position
            leatherTex, 1.0f, 0.7f, // texture
            leatherMat // material
        )
    );
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.9f, 0.01f, 0.65f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.0052f, 0.0f),// position
            leatherTex, 1.0f, 0.7f, // texture
            leatherMat // material
        )
    );


    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.025f, 0.01f, 0.025f),// scale
            glm::vec3(0.0f, 0.0f, -0.0f),// rotation
            glm::vec3(-0.425f, 0.0f, -0.325f),// position
            leatherTex, 0.075f, 0.075f, // texture
            leatherMat // material
        )
    );
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.025f, 0.01f, 0.025f),// scale
            glm::vec3(0.0f, 0.0f, -0.0f),// rotation
            glm::vec3(0.425f, 0.0f, -0.325f),// position
            leatherTex, 0.075f, 0.075f, // texture
            leatherMat // material
        )
    );
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.025f, 0.01f, 0.025f),// scale
            glm::vec3(0.0f, 0.0f, -0.0f),// rotation
            glm::vec3(-0.425f, 0.0f, 0.325f),// position
            leatherTex, 0.075f, 0.075f, // texture
            leatherMat // material
        )
    );
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.025f, 0.01f, 0.025f),// scale
            glm::vec3(0.0f, 0.0f, -0.0f),// rotation
            glm::vec3(0.425f, 0.0f, 0.325f),// position
            leatherTex, 0.075f, 0.075f, // texture
            leatherMat // material
        )
    );

    // Chrome rings, spine
    AddToObject(
        new Shape(
            Shape::box,
            glm::vec3(0.05f, 0.01f, 0.60f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.01f, 0.0),// position
            metalTex, 1.0f, 0.7f, // texture
            metalMat // material
        )
    );
    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.025f, 0.01f, 0.025f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.005f, 0.3f),// position
            metalTex, 1.0f, 0.7f, // texture
            metalMat // material
        )
    );

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.025f, 0.01f, 0.025f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.005f, -0.3f),// position
            metalTex, 1.0f, 0.7f, // texture
            metalMat // material
        )
    );

    AddToObject(
        new Shape(
            Shape::torus,
            glm::vec3(0.02f, 0.02f, 0.02f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.03f, -0.20f),// position
            metalTex, 1.0f, 0.7f, // texture
            metalMat // material
        )
    );

    AddToObject(
        new Shape(
            Shape::torus,
            glm::vec3(0.02f, 0.02f, 0.02f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.03f, -0.15f),// position
            metalTex, 1.0f, 0.7f, // texture
            metalMat // material
        )
    );

    AddToObject(
        new Shape(
            Shape::torus,
            glm::vec3(0.02f, 0.02f, 0.02f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.03f, -0.10f),// position
            metalTex, 1.0f, 0.7f, // texture
            metalMat // material
        )
    );

    AddToObject(
        new Shape(
            Shape::torus,
            glm::vec3(0.02f, 0.02f, 0.02f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.03f, 0.10f),// position
            metalTex, 1.0f, 0.7f, // texture
            metalMat // material
        )
    );

    AddToObject(
        new Shape(
            Shape::torus,
            glm::vec3(0.02f, 0.02f, 0.02f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.03f, 0.15f),// position
            metalTex, 1.0f, 0.7f, // texture
            metalMat // material
        )
    );

    AddToObject(
        new Shape(
            Shape::torus,
            glm::vec3(0.02f, 0.02f, 0.02f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.03f, 0.20f),// position
            metalTex, 1.0f, 0.7f, // texture
            metalMat // material
        )
    );

    // Draw paper

    AddToObject(
        new Shape(
            Shape::plane,
            glm::vec3(0.2f, 0.01f, 0.33f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.2f, 0.02f, 0.0f),// position
            paperTex, 0.7f, 1.0f, // texture
            paperMat // material
        )
    );

}

Binder::Binder(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ) {
    LoadShapes();
    InitiateObject(scaleXYZ, rotationXYZ, positionXYZ);
}

void LightSource::LoadShapes() {
    Texture::textures texture = Texture::woodCherry;
    Material::materials material = Material::paper;

    AddToObject(
        new Shape(
            Shape::cylinder,
            glm::vec3(0.5f, 0.1f, 0.5f),// scale
            glm::vec3(180.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.0f, 0.0f),// position
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            material // material
        )
    );

    AddToObject(
        new Shape(
            Shape::taperedCylinder,
            glm::vec3(0.5f, 0.9f, 0.5f),// scale
            glm::vec3(0.0f, 0.0f, 0.0f),// rotation
            glm::vec3(0.0f, 0.0f, 0.0f),// position
            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            material // material
        )
    );

}
void LightSource::setThePosition(glm::vec3 positionXYZ) {
    this->position = positionXYZ;
    setPosition(positionXYZ);
};
void LightSource::setTheColors(glm::vec3 diffuse, glm::vec3 specular) {
    definedShapes[0]->setColor(glm::vec4(specular[0], specular[1], specular[2], 1));
    definedShapes[1]->setColor(glm::vec4(diffuse[0], diffuse[1], diffuse[2], 1));
    this->specularColor = specular;
    this->diffuseColor = diffuse;
}
void LightSource::setTheProperties(float focalStrength, float specularIntensity) {
    this->setScale(glm::vec3(focalStrength / 10.0f, specularIntensity / 10.0f, focalStrength / 10.0f));
    this->focalStrength = focalStrength;
    this->specularIntensity = specularIntensity;
}

LightSource::LightSource(glm::vec3 positionXYZ, glm::vec3 diffuseColor, glm::vec3 specularColor, float focalStrength, float specularIntensity) {
    LoadShapes();
    setThePosition(positionXYZ);
    setTheColors(diffuseColor, specularColor);
    setTheProperties(focalStrength, specularIntensity);
    InitiateObject(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), positionXYZ);
}