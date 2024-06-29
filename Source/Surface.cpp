///////////////////////////////////////////////////////////////////////////////
// Surface.cpp
// ============
// Holds individualized texture and color information for each face of a Shape object
//
//  AUTHOR: Rachel Aldava - SNHU Student / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, June, 2024
///////////////////////////////////////////////////////////////////////////////

#include "Surface.h"

Surface::Surface(){
    this->isRendered = false;
    this->hasColor = false;
    this->hasTexture = false;
    this->hasMaterial = false;
}

void Surface::setTexture(std::string texture, float textureScaleX, float textureScaleY){
    this->isRendered = true;
    this->hasTexture = true;
    this->texture = texture;
    this->textureScaleX = textureScaleX;
    this->textureScaleY = textureScaleY;
}

void Surface::setColor(glm::vec4 colorRGBA){
    this->isRendered = true;
    this->hasColor = true;
    this->colorRGBA = colorRGBA;
}

void Surface::setMaterial(std::string material) {
    this->isRendered = true;
    this->hasMaterial = true;
    this->material = material;
}

bool Surface::IsRendered() {
    return isRendered;
}

bool Surface::HasTexture() {
    return hasTexture;
}

bool Surface::HasColor() {
    return hasColor;
}

bool Surface::HasMaterial() {
    return hasMaterial;
}

std::tuple< std::string, float, float> Surface::GetTexture() {
    return {texture, textureScaleX, textureScaleY };
}

glm::vec4 Surface::GetColor() {
    return colorRGBA;
}

std::string Surface::GetMaterial() {
    return material;
}