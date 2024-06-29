///////////////////////////////////////////////////////////////////////////////
// scenemanager.cpp
// ============
// manage the preparing and rendering of 3D scenes - textures, materials, lighting
//
//  AUTHOR: Brian Battersby - SNHU Instructor / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, Nov. 1st, 2023
///////////////////////////////////////////////////////////////////////////////

#include "SceneManager.h"
#include <cmath>
#include <vector>
#include <iostream>
#include "GLFW/glfw3.h" 

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include <glm/gtx/transform.hpp>

// declaration of global variables
namespace
{
	const char* g_ModelName = "model";
	const char* g_ColorValueName = "objectColor";
	const char* g_TextureValueName = "objectTexture";
	const char* g_UseTextureName = "bUseTexture";
	const char* g_UseLightingName = "bUseLighting";
	glm::vec3 lightPositions[4];
	std::vector <Object*> sceneObjects;
	Chessboard* test;
}

/***********************************************************
 *  SceneManager()
 *
 *  The constructor for the class
 ***********************************************************/
SceneManager::SceneManager(ShaderManager* pShaderManager)
{
	m_pShaderManager = pShaderManager;
	m_basicMeshes = new ShapeMeshes();
}

/***********************************************************
 *  ~SceneManager()
 *
 *  The destructor for the class
 ***********************************************************/
SceneManager::~SceneManager()
{
	m_pShaderManager = NULL;
	delete m_basicMeshes;
	m_basicMeshes = NULL;
}

/***********************************************************
 *  CreateGLTexture()
 *
 *  This method is used for loading textures from image files,
 *  configuring the texture mapping parameters in OpenGL,
 *  generating the mipmaps, and loading the read texture into
 *  the next available texture slot in memory.
 ***********************************************************/
bool SceneManager::CreateGLTexture(const char* filename, std::string tag)
{
	int width = 0;
	int height = 0;
	int colorChannels = 0;
	GLuint textureID = 0;

	// indicate to always flip images vertically when loaded
	stbi_set_flip_vertically_on_load(true);

	// try to parse the image data from the specified image file
	unsigned char* image = stbi_load(
		filename,
		&width,
		&height,
		&colorChannels,
		0);

	// if the image was successfully read from the image file
	if (image)
	{
		std::cout << "Successfully loaded image:" << filename << ", width:" << width << ", height:" << height << ", channels:" << colorChannels << std::endl;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if the loaded image is in RGB format
		if (colorChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		// if the loaded image is in RGBA format - it supports transparency
		else if (colorChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		else
		{
			std::cout << "Not implemented to handle image with " << colorChannels << " channels" << std::endl;
			return false;
		}

		// generate the texture mipmaps for mapping textures to lower resolutions
		glGenerateMipmap(GL_TEXTURE_2D);

		// free the image data from local memory
		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

		// register the loaded texture and associate it with the special tag string
		m_textureIDs[m_loadedTextures].ID = textureID;
		m_textureIDs[m_loadedTextures].tag = tag;
		m_loadedTextures++;

		return true;
	}

	std::cout << "Could not load image:" << filename << std::endl;

	// Error loading the image
	return false;
}

/***********************************************************
 *  BindGLTextures()
 *
 *  This method is used for binding the loaded textures to
 *  OpenGL texture memory slots.  There are up to 16 slots.
 ***********************************************************/
void SceneManager::BindGLTextures()
{
	for (int i = 0; i < m_loadedTextures; i++)
	{
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textureIDs[i].ID);
	}
}

/***********************************************************
 *  DestroyGLTextures()
 *
 *  This method is used for freeing the memory in all the
 *  used texture memory slots.
 ***********************************************************/
void SceneManager::DestroyGLTextures()
{
	for (int i = 0; i < m_loadedTextures; i++)
	{
		glGenTextures(1, &m_textureIDs[i].ID);
	}
}

/***********************************************************
 *  FindTextureID()
 *
 *  This method is used for getting an ID for the previously
 *  loaded texture bitmap associated with the passed in tag.
 ***********************************************************/
int SceneManager::FindTextureID(std::string tag)
{
	int textureID = -1;
	int index = 0;
	bool bFound = false;

	while ((index < m_loadedTextures) && (bFound == false))
	{
		if (m_textureIDs[index].tag.compare(tag) == 0)
		{
			textureID = m_textureIDs[index].ID;
			bFound = true;
		}
		else
			index++;
	}

	return(textureID);
}

/***********************************************************
 *  FindTextureSlot()
 *
 *  This method is used for getting a slot index for the previously
 *  loaded texture bitmap associated with the passed in tag.
 ***********************************************************/
int SceneManager::FindTextureSlot(std::string tag)
{
	int textureSlot = -1;
	int index = 0;
	bool bFound = false;

	while ((index < m_loadedTextures) && (bFound == false))
	{
		if (m_textureIDs[index].tag.compare(tag) == 0)
		{
			textureSlot = index;
			bFound = true;
		}
		else
			index++;
	}

	return(textureSlot);
}

/***********************************************************
 *  FindMaterial()
 *
 *  This method is used for getting a material from the previously
 *  defined materials list that is associated with the passed in tag.
 ***********************************************************/
bool SceneManager::FindMaterial(std::string tag, OBJECT_MATERIAL& material)
{
	if (m_objectMaterials.size() == 0)
	{
		return(false);
	}

	int index = 0;
	bool bFound = false;
	while ((index < m_objectMaterials.size()) && (bFound == false))
	{
		if (m_objectMaterials[index].tag.compare(tag) == 0)
		{
			bFound = true;
			material.ambientColor = m_objectMaterials[index].ambientColor;
			material.ambientStrength = m_objectMaterials[index].ambientStrength;
			material.diffuseColor = m_objectMaterials[index].diffuseColor;
			material.specularColor = m_objectMaterials[index].specularColor;
			material.shininess = m_objectMaterials[index].shininess;
		}
		else
		{
			index++;
		}
	}

	return(true);
}

/***********************************************************
 *  SetTransformations()
 *
 *  This method is used for setting the transform buffer
 *  using the passed in transformation values.
 ***********************************************************/
void SceneManager::SetTransformations(
	glm::vec3 scaleXYZ,
	float XrotationDegrees,
	float YrotationDegrees,
	float ZrotationDegrees,
	glm::vec3 positionXYZ)
{
	// variables for this method
	glm::mat4 modelView;
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

	modelView = translation * rotationZ * rotationY * rotationX * scale;

	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setMat4Value(g_ModelName, modelView);
	}
}

// This is a wrapper function for the Shape object
void SceneManager::SetTransformations(Shape shape)
{
	//SetTransformations(shape.scaleXYZ, shape.rotationXYZ[0], shape.rotationXYZ[1], shape.rotationXYZ[2], shape.positionXYZ);
}



/***********************************************************
 *  SetShaderColor()
 *
 *  This method is used for setting the passed in color
 *  into the shader for the next draw command
 ***********************************************************/
void SceneManager::SetShaderColor(
	float redColorValue,
	float greenColorValue,
	float blueColorValue,
	float alphaValue)
{
	// variables for this method
	glm::vec4 currentColor;

	currentColor.r = redColorValue;
	currentColor.g = greenColorValue;
	currentColor.b = blueColorValue;
	currentColor.a = alphaValue;

	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setIntValue(g_UseTextureName, false);
		m_pShaderManager->setVec4Value(g_ColorValueName, currentColor);
	}
}

void SceneManager::SetShaderColor(glm::vec4 color) { 
	SetShaderColor(color[0], color[1], color[2], color[3]); 
}

/***********************************************************
 *  SetShaderTexture()
 *
 *  This method is used for setting the texture data
 *  associated with the passed in ID into the shader.
 ***********************************************************/
void SceneManager::SetShaderTexture(
	std::string textureTag)
{
	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setIntValue(g_UseTextureName, true);

		int textureID = -1;
		textureID = FindTextureSlot(textureTag);
		m_pShaderManager->setSampler2DValue(g_TextureValueName, textureID);
	}
}

/***********************************************************
 *  SetTextureUVScale()
 *
 *  This method is used for setting the texture UV scale
 *  values into the shader.
 ***********************************************************/
void SceneManager::SetTextureUVScale(float u, float v)
{
	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setVec2Value("UVscale", glm::vec2(u, v));
	}
}

/***********************************************************
 *  SetShaderMaterial()
 *
 *  This method is used for passing the material values
 *  into the shader.
 ***********************************************************/
void SceneManager::SetShaderMaterial(
	std::string materialTag)
{
	if (m_objectMaterials.size() > 0)
	{
		OBJECT_MATERIAL material;
		bool bReturn = false;

		bReturn = FindMaterial(materialTag, material);
		if (bReturn == true)
		{
			m_pShaderManager->setVec3Value("material.ambientColor", material.ambientColor);
			m_pShaderManager->setFloatValue("material.ambientStrength", material.ambientStrength);
			m_pShaderManager->setVec3Value("material.diffuseColor", material.diffuseColor);
			m_pShaderManager->setVec3Value("material.specularColor", material.specularColor);
			m_pShaderManager->setFloatValue("material.shininess", material.shininess);
		}
	}
}

/**************************************************************/
/*** STUDENTS CAN MODIFY the code in the methods BELOW for  ***/
/*** preparing and rendering their own 3D replicated scenes.***/
/*** Please refer to the code in the OpenGL sample project  ***/
/*** for assistance.                                        ***/
/**************************************************************/

 /***********************************************************
  *  DefineObjectMaterials()
  *
  *  This method is used for configuring the various material
  *  settings for all of the objects within the 3D scene.
  ***********************************************************/
void SceneManager::DefineObjectMaterials()
{
	// Loop throuch the materials defined in Material.cpp, and add them.
	Material::DefineObjectMaterials();
	for (int materialInt = 0; materialInt != Material::LAST; materialInt++) {
		OBJECT_MATERIAL currMat;
		Material::materials material = static_cast<Material::materials>(materialInt);

		currMat.ambientStrength = Material::GetAmbientStrength(material);
		currMat.ambientColor = Material::GetAmbientColor(material);
		currMat.diffuseColor = Material::GetDiffuseColor(material);
		currMat.specularColor = Material::GetSpecularColor(material);
		currMat.shininess = Material::GetShininess(material);
		currMat.tag = Material::GetTag(material);
		m_objectMaterials.push_back(currMat);
	}
}

/***********************************************************
 *  SetupSceneLights()
 *
 *  This method is called to add and configure the light
 *  sources for the 3D scene.  There are up to 4 light sources.
 ***********************************************************/
void SceneManager::SetupSceneLights()
{
	// this line of code is NEEDED for telling the shaders to render 
	// the 3D scene with custom lighting, if no light sources have
	// been added then the display window will be black - to use the 
	// default OpenGL lighting then comment out the following line
	//m_pShaderManager->setBoolValue(g_UseLightingName, true);

	
	m_pShaderManager->setBoolValue(g_UseLightingName, true);

	m_pShaderManager->setVec3Value("globalAmbientColor", .15, .15, .15);

	lightPositions[0] = glm::vec3(-2.0f, 4.0f, 1.25f);
	m_pShaderManager->setVec3Value("lightSources[0].position", lightPositions[0][0], lightPositions[0][1], lightPositions[0][2]);
	m_pShaderManager->setVec3Value("lightSources[0].diffuseColor", 0.9f, 0.9f, 0.9f);
	m_pShaderManager->setVec3Value("lightSources[0].specularColor", 0.3f, 0.3f, 0.3f);
	m_pShaderManager->setFloatValue("lightSources[0].focalStrength", 10.0f);
	m_pShaderManager->setFloatValue("lightSources[0].specularIntensity", 20.0f);

	lightPositions[1] = glm::vec3(-2.0f, 10.0f, 1.25f);
	m_pShaderManager->setVec3Value("lightSources[1].position", lightPositions[1][0], lightPositions[1][1], lightPositions[1][2]);
	m_pShaderManager->setVec3Value("lightSources[1].diffuseColor", 0.9f, 0.9f, 0.9f);
	m_pShaderManager->setVec3Value("lightSources[1].specularColor", 0.3f, 0.1f, 0.2f);
	m_pShaderManager->setFloatValue("lightSources[1].focalStrength", 0.5f);
	m_pShaderManager->setFloatValue("lightSources[1].specularIntensity", 5.0f);

	lightPositions[2] = glm::vec3(-2.0f, 20.0f, 1.25f);
	m_pShaderManager->setVec3Value("lightSources[2].position", lightPositions[2][0], lightPositions[2][1], lightPositions[2][2]);
	m_pShaderManager->setVec3Value("lightSources[2].diffuseColor", 0.6f, 0.6f, 0.6f);
	m_pShaderManager->setVec3Value("lightSources[2].specularColor", 0.0f, 0.0f, 0.0f);
	m_pShaderManager->setFloatValue("lightSources[2].focalStrength", 0.1f);
	m_pShaderManager->setFloatValue("lightSources[2].specularIntensity", 2.0f);

	lightPositions[3] = glm::vec3(2.0f, 5.0f, -9999995.0f);
	m_pShaderManager->setVec3Value("lightSources[3].position", lightPositions[3][0], lightPositions[3][1], lightPositions[3][2]);
	m_pShaderManager->setVec3Value("lightSources[3].diffuseColor", 0.6f, 0.6f, 0.6);
	m_pShaderManager->setVec3Value("lightSources[3].specularColor", 0.0f, 0.0f, 0.0f);
	m_pShaderManager->setFloatValue("lightSources[3].focalStrength", 4.0f);
	m_pShaderManager->setFloatValue("lightSources[3].specularIntensity", 0.2f);

	m_pShaderManager->setBoolValue(g_UseLightingName, true);


}

/***********************************************************
 *  PrepareScene()
 *
 *  This method is used for preparing the 3D scene by loading
 *  the shapes, textures in memory to support the 3D scene
 *  rendering
 ***********************************************************/
void SceneManager::LoadSceneTextures() {
	bool bReturn = false;
	for (int textureInt = 0; textureInt != Texture::LAST; textureInt++) {
		Texture::textures texture = static_cast<Texture::textures>(textureInt);

		bReturn = CreateGLTexture(
			Texture::GetFile(texture).c_str(),
			Texture::GetTag(texture).c_str());
	}
	BindGLTextures();
}

void SceneManager::PrepareScene()
{
	LoadSceneTextures();
	
	// define the materials for objects in the scene
	DefineObjectMaterials();
	// add and define the light sources for the scene
	SetupSceneLights();

	// only one instance of a particular mesh needs to be
	// loaded in memory no matter how many times it is drawn
	// in the rendered 3D scene

	m_basicMeshes->LoadPlaneMesh();
	m_basicMeshes->LoadCylinderMesh();
	m_basicMeshes->LoadTaperedCylinderMesh();
	m_basicMeshes->LoadTorusMesh();
	m_basicMeshes->LoadBoxMesh();
	m_basicMeshes->LoadSphereMesh();
	m_basicMeshes->LoadTorusMesh();
	m_basicMeshes->LoadConeMesh();

	// load the Room object into memory, which is defined in Object.cpp to house many different shapes.
	sceneObjects.push_back(new Room(glm::vec3(20.0f, 20.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -3.0f, 8.0f)));
	test = new Chessboard(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-5.0f, 2.0f, 0.0f));
}

/***********************************************************
 *  RenderScene()
 *
 *  This method is used for rendering the 3D scene by
 *  transforming and drawing the basic 3D shapes
 ***********************************************************/
void SceneManager::RenderScene()
{
	test->Animate();
	// Render the scene objects
	Render(*test);
	
	for (int i = 0; i < sceneObjects.size(); i++) {
		Render(*sceneObjects[i]);
	}
	
}

/***********************************************************
 *  RenderObject()
 *
 *  This method is used for rendering members of the Object
 * class by rendering the individual Shape objects
 ***********************************************************/
void SceneManager::Render(Object object) {
	std::vector<Shape*> shapes = object.GetShapes();
	for (Shape* shape : shapes) {
		Render(*shape);
	}
}

/***********************************************************
 *  RenderObject()
 *
 *  This method is used for rendering members of the Shape class
 ***********************************************************/
void SceneManager::Render(Shape shape) {

	// Load the scale, rotation, and position of the mesh into memory

	if (NULL != m_pShaderManager)
	{
		m_pShaderManager->setMat4Value(g_ModelName, shape.GetView());
	}
	
	// Access information about individual faces
	std::vector<Surface> surfaces = shape.surfaces;

	glm::vec4 currentColor;
	std::tuple< std::string, float, float> currentTexture;
	std::string currentMaterial;
	
	for (int i = 0; i < shape.surfaces.size(); i++) {
		// If the face has a texture, load the texture
		if (surfaces[i].HasMaterial()) {
			currentMaterial = surfaces[i].GetMaterial();
			SetShaderMaterial(currentMaterial);
		}
		else {
			SetShaderMaterial("paper");
		}
		
		if (surfaces[i].HasTexture()) {
			currentTexture = surfaces[i].GetTexture();

			SetShaderTexture(std::get<0>(currentTexture));
			SetTextureUVScale(std::get<1>(currentTexture), std::get<2>(currentTexture));
		}

		// else, load the color
		else {
			currentColor = surfaces[i].GetColor();
			SetShaderColor(currentColor);
		}
		// render the object using only the current face. A sphere will loop once, whereas a cube will loop six times.
		shape.Render(m_basicMeshes, i);
	}
	
}

