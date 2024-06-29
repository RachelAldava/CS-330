#pragma once
#include <glm/gtx/transform.hpp>
#include "Shape.h"
#include <vector>
class NeoObject
{
protected:
    // object-level values
    glm::vec4 localVectorX;
    glm::vec4 localVectorY;
    glm::vec4 localVectorZ;
    glm::vec3 scaleXYZ;
    glm::vec3 rotationXYZ;
    glm::vec3 originXYZ;

    // Shape-level values
    std::vector<Shape> shapes;
    std::vector<glm::vec3> shapeScaleNorm;
    std::vector<glm::vec3> shapeRotNorm;
    std::vector<glm::vec3> shapePosNorm;
    
    // object-level methods
    void InitiateObject(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
    void SetLocalVectors(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ);
    void RotateLocalVectors(glm::vec3 rotationXYZ);
    static glm::vec4 RotateVector(glm::vec4 vector, glm::vec3 rotationXYZ);
    void ScaleLocalVectors(glm::vec3 scaleXYZ);
    glm::vec3 GetWorldCoordOffset(int index);

    // shape-level methods
    void AddShape(Shape shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
    void TransformShapes();

    virtual void LoadShapes();

public:
    //Box objectOrigin;
    glm::mat4 modelView;

    void SetTransformations();
    void SetShapeTransformations();

    std::vector<Shape> getShapes();
};

class 
NeoTest : public NeoObject
{
    virtual void LoadShapes();
public:
    NeoTest(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);

    void Print();
};

class NeoInkwell : public NeoObject
{
    virtual void LoadShapes();
public:
    NeoInkwell(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
};

class NeoOrigin : public NeoObject
{
    virtual void LoadShapes();
public:
    NeoOrigin(glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
};