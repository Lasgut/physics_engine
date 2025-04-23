#include "Window.h"
#include "Context.h"
#include "Camera.h"
#include "Axes.h"
#include "EventHandler.h"
#include "ShaderHandler.h"
#include "Triangle.h"
#include "Drone.h"
#include "Light.h"
#include "Rectangle.h"
#include "Floor.h"
#include "Clock.h"
#include "Terrain.h"
#include "GuiSettings.h"
#include "ResourceHandler.h"

int main(int argc, char* argv[]) 
{
    try 
    {
        // Extracting file paths in resources
        ResourceHandler resourceHandler(std::filesystem::path(argv[0]).parent_path());
        auto shaders    = resourceHandler.getFiles().shaders;
        auto heightMaps = resourceHandler.getFiles().heightMaps;
        auto meshes     = resourceHandler.getFiles().meshes; 

        // GUI stuff
        Window        window("Physics Engine", 900, 900);
        Context       context(window);
        EventHandler  eventHandler;
        GuiSettings   guiSettings(window, context);
        Clock         clock;
        Camera        camera;
        Light         light;

        // Shaders
        ShaderHandler simpleShaderHandler(shaders.simpleVertexShaderPath.c_str(), shaders.simpleFragmentShaderPath.c_str());
        ShaderHandler shaderHandler(shaders.vertexShaderPath.c_str(), shaders.fragmentShaderPath.c_str());
        ShaderHandler terrainShaderHandler(
            shaders.terrainVertexShaderPath.c_str(), 
            shaders.terrainFragmentShaderPath.c_str(),
            shaders.terrainGeometryShaderPath.c_str()
        );

        // Objects
        Triangle      triangle;
        Floor         floor;
        Drone         drone(meshes.fpvDrone);
        Terrain       terrain(heightMaps.icelandHeightMapPath.c_str());
        Axes          axes(1.0f);

        while (!EventState::getInstance().quit) 
        {
            clock.setPreviousTime();

            eventHandler.update();
            context.clear();

            camera.update();

            terrainShaderHandler.use(camera);
            terrain.update(terrainShaderHandler);

            simpleShaderHandler.use(camera);
            axes.update(simpleShaderHandler);

            shaderHandler.use(camera);
            light.update(shaderHandler, camera);
            drone.update(shaderHandler, clock);
            floor.update(shaderHandler);

            guiSettings.update();

            window.swapBuffers();
        }
    } 
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}


