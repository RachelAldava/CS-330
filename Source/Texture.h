///////////////////////////////////////////////////////////////////////////////
// Texture.cpp
// ============
//  Houses some basic information about the textures used in this project. 
//  Namely, where they are located in the directory and what tags this program will use.
// 
//  AUTHOR: Rachel Aldava - SNHU Student / Computer Science
//	Created for CS-330-Computational Graphics and Visualization, June, 2024
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
class Texture
{
    static std::string tags[];
    static std::string fileNames[];
public:
    static enum textures {
        blackABS,
        blackABSalt,
        inklabel,
        woodLight,
        woodDark,
        woodCherry,
        wall,
        stainless,
        nylonGlitter,
        leather,
        name,
        floor,
        LAST
    };

    static std::string GetFile(textures);
    static std::string GetTag(textures);
};

