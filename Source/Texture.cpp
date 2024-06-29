///////////////////////////////////////////////////////////////////////////////
// Texture.cpp
// ============
//  Houses some basic information about the textures used in this project. 
//  Namely, where they are located in the directory and what tags this program will use.
// 
//  AUTHOR: Rachel Aldava - SNHU Student / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, June, 2024
///////////////////////////////////////////////////////////////////////////////

#include "Texture.h"

std::string Texture::tags[] = {
"blackABS",
"blackABSalt",
"inkLabel",
"woodLight",
"woodDark",
"woodCherry",
"wall",
"stainless",
"nylonGlitter",
"leather",
"name",
"floor"
};

std::string Texture::fileNames[] = {
"textures/blackABS.jpg",// Created by author
"textures/blackABSalt.jpg",// Created by author
"textures/labelFront.jpg",// Not creative commons; Is a photo of an actual product. https://www.amazon.com/Herbin-Fountain-Pen-Ink-Poussiere/dp/B002MP3YTK/
"textures/woodLight.jpg",//https://www.myfreetextures.com/white-background-seamless-wood-texture/
"textures/woodDark.jpg",// Recolor of woodLightMatte.jpg by myself.
"textures/woodCherry.jpg",// Recolor of woodLightMatte.jpg by myself.
"textures/wall.jpg",//https://commons.wikimedia.org/wiki/File:Beige_tan_sand_faced_finish_clean_seamless_building_wall_texture.jpg
"textures/stainless.jpg",// Default texture within sample code.
"textures/nylonGlitter.jpg",// created by author
"textures/fauxLeather.jpg",// https://www.flickr.com/photos/webtreatsetc/4563912234
"textures/name.jpg",// created by author
"textures/floor.jpg"// https://www.flickr.com/photos/webtreatsetc/4459642745
};

std::string Texture::GetTag(textures texture) {
    if (texture == Texture::LAST) return tags[texture - 1];
    return tags[texture];
}
std::string Texture::GetFile(textures texture) {
    if (texture == Texture::LAST) return tags[texture - 1];
    return fileNames[texture];
}
