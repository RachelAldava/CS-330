///////////////////////////////////////////////////////////////////////////////
// Shape.h
// ============
//  This is the primary interface between the student code (my code) and the instructor code.
//  It houses the projection data for each shape in the scene and supplies the SceneManager with this data and rendering instructions.
//
//  AUTHOR: Rachel Aldava - SNHU Student / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, June, 2024
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <glm/gtx/transform.hpp>
#include <string>
#include <vector>
 
#include "ShaderManager.h"
#include "ShapeMeshes.h"
#include "Surface.h"
#include <glm/gtx/transform.hpp>
class Shape
{
private:
    glm::vec3 scaleXYZ;
    glm::vec3 rotationXYZ;
    glm::vec3 positionXYZ;
    
    glm::mat4 localModelView;
    glm::mat4 transformations;
    glm::mat4 totalView;

    void calculateTotalView();
    bool needsViewUpdate;
    int count;

public:
    glm::mat4 GetView();
    void SetTransformations(glm::mat4 transformations);
    
    int numSurfaces;

    void SetLocalTransformations();


    static enum shapes {
    box,
    cone,
    cylinder,
    plane,
    prism,
    pyramid3,
    pyramid4,
    sphere,
    taperedCylinder,
    torus};

    shapes shapeType;
    std::vector<Surface> surfaces;
    
    void InitiateShape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
    
    void setPosition(glm::vec3 positionXYZ);
    virtual void setScale(glm::vec3 scaleXYZ);
    void setRotation(glm::vec3 rotationXYZ);
    void setColor(glm::vec4 color);
    void setColorSides(std::vector<glm::vec4> colors);
    void setTexture(Texture::textures textures, float x, float y);
    void setTextureSides(std::vector<std::string> textures, std::vector<float> xVals, std::vector<float> yVals);
    void setMaterial(Material::materials material);
    
    void modifyPosition(glm::vec3 positionXYZ);
    void modifyScale(glm::vec3 scaleXYZ);
    void modifyRotation(glm::vec3 rotationXYZ);

    void Render(ShapeMeshes* m_basicMeshes, int faceIndex);

    // Various constructors
    Shape();
    Shape(shapes shape);
    Shape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ);
    Shape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, glm::vec4 color);
    Shape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, glm::vec4 color, Material::materials material);
    Shape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, Texture::textures texture, float x, float y);
    Shape(shapes shape, glm::vec3 scaleXYZ, glm::vec3 rotationXYZ, glm::vec3 positionXYZ, Texture::textures texture, float x, float y, Material::materials material);

};
