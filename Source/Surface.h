///////////////////////////////////////////////////////////////////////////////
// Surface.h
// ============
// Holds individualized texture and color information for each face of a Shape object
//
//  AUTHOR: Rachel Aldava - SNHU Student / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, June, 2024
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <glm/gtx/transform.hpp>
#include <tuple>
#include "Texture.h"
#include "Material.h"
class Surface
{
private:
    bool isRendered;

    bool hasTexture;
    std::string texture = "";
    float textureScaleX = 1.0f;
    float textureScaleY = 1.0f;

    bool hasColor;
    glm::vec4 colorRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    bool hasMaterial;
    std::string material = "";

public:

    Surface();
    void setTexture(std::string texture, float textureScaleX, float textureScaleY);
    void setMaterial(std::string material);
    void setColor(glm::vec4 colorRGBA);

    bool IsRendered();
    bool HasTexture();
    bool HasColor();
    bool HasMaterial();

    std::tuple< std::string, float, float> GetTexture();
    glm::vec4 GetColor();
    std::string GetMaterial();
};
