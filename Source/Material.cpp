///////////////////////////////////////////////////////////////////////////////
// Material.cpp
// ============
//  Houses some basic information about the materials used in this project.
// 
//  AUTHOR: Rachel Aldava - SNHU Student / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, June, 2024
///////////////////////////////////////////////////////////////////////////////

#include "Material.h"


static std::map<Material::materials, Material::OBJECT_MATERIAL> map;

// Edgecase: GetMaterial(LAST) is called
Material::OBJECT_MATERIAL Material::GetMaterial(materials material) {
	if (material == Material::LAST) return map[paper];
	return map[material];
}

// straightforward "get" methods which return values at the key of the specified enum
float Material::GetAmbientStrength(materials material) {
	return GetMaterial(material).ambientStrength;
}
glm::vec3 Material::GetAmbientColor(materials material) {
	return GetMaterial(material).ambientColor;
}
glm::vec3 Material::GetDiffuseColor(materials material) {
	return GetMaterial(material).diffuseColor;
}
glm::vec3 Material::GetSpecularColor(materials material) {
	return GetMaterial(material).specularColor;
}
float Material::GetShininess(materials material) {
	return GetMaterial(material).shininess;
}

std::string Material::GetTag(materials material) {
	return GetMaterial(material).tag;
}


// inserts OBJECT_MATERIAL values into the dictionary, using the public enum as a key
void Material::DefineObjectMaterials()
{
	// Chrome
	OBJECT_MATERIAL chromeMaterial;
	chromeMaterial.ambientStrength = 1.0f;
	chromeMaterial.diffuseColor = glm::vec3(0.6f, 0.6f, 0.6f);
	chromeMaterial.specularColor = glm::vec3(0.6f, 0.6f, 0.6f);
	chromeMaterial.shininess = 5.0;
	chromeMaterial.tag = "chrome";
	map[chrome] = chromeMaterial;

	// Wood: light matte
	OBJECT_MATERIAL woodLightMatteMaterial;
	woodLightMatteMaterial.diffuseColor = glm::vec3(0.9f, 0.2f, 0.00f);
	woodLightMatteMaterial.specularColor = glm::vec3(1.2f, 0.9f, 1.50f);
	woodLightMatteMaterial.shininess = 0.05;
	woodLightMatteMaterial.tag = "woodLightMatte";
	map[woodLightMatte] = woodLightMatteMaterial;

	// Wood: light matte
	OBJECT_MATERIAL woodDarkMatteMaterial;
	woodDarkMatteMaterial.diffuseColor = glm::vec3(0.4f, 0.4f, 0.99f);
	woodDarkMatteMaterial.specularColor = glm::vec3(0.05f, 0.05f, 0.9f);
	woodDarkMatteMaterial.shininess = 1;
	woodDarkMatteMaterial.tag = "woodDarkMatte";
	map[woodDarkMatte] = woodDarkMatteMaterial;

	// glass
	OBJECT_MATERIAL glassMaterial;
	glassMaterial.diffuseColor = glm::vec3(0.3f, 0.1f, 0.3f);
	glassMaterial.specularColor = glm::vec3(0.2f, 0.2f, 0.2f);
	glassMaterial.shininess = 85.0;
	glassMaterial.tag = "glass";
	map[glass] = glassMaterial;

	// Wood: dark semigloss
	OBJECT_MATERIAL woodDarkSemiglossMaterial;
	woodDarkSemiglossMaterial.diffuseColor = glm::vec3(0.0f, 0.0f, 0.0f);
	woodDarkSemiglossMaterial.specularColor = glm::vec3(1, 1, 25);
	woodDarkSemiglossMaterial.shininess = 1.0f;
	woodDarkSemiglossMaterial.tag = "woodDarkSemigloss";
	map[woodDarkSemigloss] = woodDarkSemiglossMaterial;

	// Paper
	OBJECT_MATERIAL paperMaterial;
	paperMaterial.diffuseColor = glm::vec3(0.3f, 0.3f, 0.3f);
	paperMaterial.specularColor = glm::vec3(0.1f, 0.1f, 0.1f);
	paperMaterial.shininess = 0.0001;
	paperMaterial.tag = "paper";
	map[paper] = paperMaterial;


	// leather
	OBJECT_MATERIAL leatherMaterial;
	leatherMaterial.diffuseColor = glm::vec3(0.4f, 0.33f, 0.29f);
	leatherMaterial.specularColor = glm::vec3(0.4f, 0.33f, 0.29f);
	leatherMaterial.shininess = 1.0;
	leatherMaterial.tag = "leather";
	map[leather] = leatherMaterial;

	// plasma
	OBJECT_MATERIAL LEDMaterial;
	LEDMaterial.diffuseColor = glm::vec3(1, 1, 1);
	LEDMaterial.specularColor = glm::vec3(1, 1, 1);
	LEDMaterial.shininess = 99999999999.0f;
	LEDMaterial.tag = "LED";
	map[LED] = LEDMaterial;

	// ABS
	OBJECT_MATERIAL ABSMaterial;
	ABSMaterial.diffuseColor = glm::vec3(0.6f, 0.6f, 0.6f);
	ABSMaterial.specularColor = glm::vec3(0.6f, 0.6f, 0.6f);
	ABSMaterial.shininess = 25.0;
	ABSMaterial.tag = "ABSMaterial";
	map[ABS] = ABSMaterial;

}
