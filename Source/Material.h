///////////////////////////////////////////////////////////////////////////////
// Material.h
// ============
//  Houses some basic information about the materials used in this project.
// 
//  AUTHOR: Rachel Aldava - SNHU Student / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, June, 2024
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>
#include <map>
#include <glm/gtx/transform.hpp>
class Material
{
public:
    static enum materials {
        chrome,
        woodLightMatte,
        woodDarkMatte,
        glass,
        woodDarkSemigloss,
        paper,
        leather,
        LED,
        ABS,
        LAST
    };


    static float GetAmbientStrength(materials);
    static glm::vec3 GetAmbientColor(materials);
    static glm::vec3 GetDiffuseColor(materials);
    static glm::vec3 GetSpecularColor(materials);
    static float GetShininess(materials);
    static std::string GetTag(materials);


    static void DefineObjectMaterials();


    
    struct OBJECT_MATERIAL
    {
        float ambientStrength;
        glm::vec3 ambientColor;
        glm::vec3 diffuseColor;
        glm::vec3 specularColor;
        float shininess;
        std::string tag;
    };

private:
    static Material::OBJECT_MATERIAL GetMaterial(materials material);

};

