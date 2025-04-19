#include "ResourceHandler.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>


ResourceHandler::ResourceHandler(const std::filesystem::path& startPath)
{
    auto programRoot = findProgramRoot(startPath);
    loadFiles(programRoot);
}


const Files& 
ResourceHandler::getFiles() const
{
    return files_;
}


std::filesystem::path
ResourceHandler::findProgramRoot(const std::filesystem::path &startPath)
{
    std::filesystem::path currentPath = startPath;

    while (!currentPath.empty()) {
        if (currentPath.filename() == "physics_engine") {
            return currentPath;
        }
        currentPath = currentPath.parent_path();
    }

    throw std::runtime_error("ERROR: Could not find 'physics_engine' directory.");
}


void 
ResourceHandler::loadFiles(const std::filesystem::path& physicsEngineRoot)
{
    std::filesystem::path shadersDir    = physicsEngineRoot / "resources/shaders";
    std::filesystem::path heightMapsDir = physicsEngineRoot / "resources/height_maps";
    std::filesystem::path meshesDir     = physicsEngineRoot / "resources/meshes";
    loadShaders   (shadersDir);
    loadHeightMaps(heightMapsDir);
    loadMeshes    (meshesDir);
}


void 
ResourceHandler::loadShaders(const std::filesystem::path &shadersDir)
{
    if (!std::filesystem::exists(shadersDir)) 
    {
        throw std::runtime_error("ERROR: Shaders directory does not exist: " + shadersDir.string());
    }

    std::string vertexShaderPath          = (shadersDir / "vertex_shader.glsl").string();
    std::string fragmentShaderPath        = (shadersDir / "fragment_shader.glsl").string();
    std::string simpleVertexShaderPath    = (shadersDir / "vertex_shader_simple.glsl").string();
    std::string simpleFragmentShaderPath  = (shadersDir / "fragment_shader_simple.glsl").string();
    std::string terrainVertexShaderPath   = (shadersDir / "terrain.vs").string();
    std::string terrainFragmentShaderPath = (shadersDir / "terrain.fs").string();

    files_.shaders.vertexShaderPath          = vertexShaderPath;
    files_.shaders.fragmentShaderPath        = fragmentShaderPath;
    files_.shaders.simpleVertexShaderPath    = simpleVertexShaderPath;
    files_.shaders.simpleFragmentShaderPath  = simpleFragmentShaderPath;
    files_.shaders.terrainVertexShaderPath   = terrainVertexShaderPath;
    files_.shaders.terrainFragmentShaderPath = terrainFragmentShaderPath;
}


void 
ResourceHandler::loadHeightMaps(const std::filesystem::path &heightMapsDir)
{
    if (!std::filesystem::exists(heightMapsDir)) 
    {
        throw std::runtime_error("ERROR: Height maps directory does not exist: " + heightMapsDir.string());
    }

    std::string icelandHeightMapPath    = (heightMapsDir / "iceland_heightmap.png").string();

    files_.heightMaps.icelandHeightMapPath   = icelandHeightMapPath;
}


void 
ResourceHandler::loadMeshes(const std::filesystem::path &meshesDir)
{
    if (!std::filesystem::exists(meshesDir)) 
    {
        throw std::runtime_error("ERROR: Meshes directory does not exist: " + meshesDir.string());
    }

    std::string blueRov2Heavy = (meshesDir / "BlueROV2Heavy.stl").string();
    std::string fpv_drone     = (meshesDir / "drone-Frame.stl").string();

    files_.meshes.blueRov2HeavyPath = blueRov2Heavy;
    files_.meshes.fpvDrone          = fpv_drone;
}
