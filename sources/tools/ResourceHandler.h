#ifndef RESOURCEHANDLER_H
#define RESOURCEHANDLER_H

#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

struct Files 
{
    struct Shaders
    {
        std::string vertexShaderPath;
        std::string fragmentShaderPath;
        std::string simpleVertexShaderPath;
        std::string simpleFragmentShaderPath;
        std::string terrainVertexShaderPath;
        std::string terrainFragmentShaderPath;
    } shaders;
    struct HeightMaps
    {
        std::string icelandHeightMapPath;
    } heightMaps;
}; 

class ResourceHandler 
{
    public:
        ResourceHandler(const std::filesystem::path& startPath);
        
        const Files& getFiles() const;

    private:
        std::filesystem::path findProgramRoot(const std::filesystem::path& startPath);
        void loadFiles(const std::filesystem::path& physicsEngineRoot);

        Files files_;
};

#endif