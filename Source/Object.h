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

#pragma once
#include <glm/gtx/transform.hpp>
#include "Shape.h"
#include <vector>
class Object
{
protected:
    // Shape-level values
    std::vector<Shape*> definedShapes;
    std::vector<Object*> definedObjects;
    std::vector<Shape*> allShapes;

    // object-level methods
    void InitiateObject(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);

    // shape-level methods
    void AddToObject(Shape* shape);
    void AddToObject(Object* object);
    void TransformShapes();

    virtual void LoadShapes();

    Shape origin;

    // default constructor.
    
public:
    Object();

    std::vector<Shape*> GetShapes();
    glm::mat4 GetView();

    // These methods modify the object object origin shape, then call methods to adjust all object shapes based off of the new origin

    void SetTransformations(glm::mat4 transformations);
    void setPosition(glm::vec3 positionXYZ);
    void setScale(glm::vec3 scaleXYZ);
    void setRotation(glm::vec3 rotationXYZ);
    void modifyPosition(glm::vec3 positionXYZ);
    void modifyScale(glm::vec3 scaleXYZ);
    void modifyRotation(glm::vec3 rotationXYZ);
};

class Inkwell : public Object
{
    virtual void LoadShapes();
public:
    Inkwell(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
};

class Pen : public Object
{
    virtual void LoadShapes();
public:
    Pen(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
};

class Chessman : public Object
{
    virtual void LoadShapes();
public:
    float scaleOffset;
    static enum variants {
        pawn,
        rook,
        knight,
        bishop,
        queen,
        king
    };
    static enum colors {
        black,
        white
    };
    colors color;
    variants variant;
    Texture::textures texture;
    Material::materials material;


    Chessman(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, colors, variants);
};

class Room : public Object
{
    virtual void LoadShapes();
public:
    Room(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
};

class Moulding : public Object
{
    virtual void LoadShapes();
public:
    Moulding(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
};

class CornerDesk : public Object
{
public:
    static enum variants {
        blank,
        withScene
    };
    CornerDesk(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
    CornerDesk(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, variants variant);

private:
    virtual void LoadShapes();
    void LoadShapesAlt1();
};

class SceneGroup : public Object
{
    virtual void LoadShapes();
public:
    SceneGroup(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
};

class Binder : public Object
{
    virtual void LoadShapes();
public:
    Binder(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
};

class LightSource : public Object
{
    virtual void LoadShapes();
public:
    void setThePosition(glm::vec3 positionXYZ);
    void setTheColors(glm::vec3 diffuse, glm::vec3 specular);
    void setTheProperties(float focalStrength, float specularIntensity);
    glm::vec3 position;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
    float focalStrength;
    float specularIntensity;
    
    LightSource(glm::vec3 positionXYZ, glm::vec3 diffuseColor, glm::vec3 specularColor, float focalStrength, float specularIntensity);
};