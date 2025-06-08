#include "Window.h"
#include "Context.h"
#include "GuiSettings.h"
#include "Visualizer.h"
#include "Entity.h"
#include "Clock.h"
#include "ResourceHandler.h"
#include "EventHandler.h"

int main(int argc, char* argv[]) 
{
    try 
    {
        // Extracting file paths in resources
        ResourceHandler resourceHandler(std::filesystem::path(argv[0]).parent_path());
        auto& shaders          = resourceHandler.getFiles().shaders;
        auto& heightMaps       = resourceHandler.getFiles().heightMaps;
        auto& meshes           = resourceHandler.getFiles().meshes; 
        auto& entityKinematics = resourceHandler.getFiles().entityKinematics;

        // GUI stuff
        Window        window("Physics Engine", 1200, 1200);
        Context       context(window);
        EventHandler  eventHandler;
        GuiSettings   guiSettings(window, context);
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
        Floor         floor;
        Entity        drone(meshes.fpvDrone, entityKinematics.generalAircraftKinematicsPath);
        Terrain       terrain(heightMaps.icelandHeightMapPath.c_str());
        Axes          axes(1.0f);
        Axes          droneCenterAxes(0.1f);

        while (!EventState::getInstance().quit) 
        {
            eventHandler.update();
            context.clear();

            camera.update(drone.getPositionAsGlm(), drone.getOrientationAsGlm());

            terrainShaderHandler.use(camera);
            terrain.update(terrainShaderHandler);

            shaderHandler.use(camera);
            light.update(shaderHandler, camera);

            simpleShaderHandler.use(camera);
            droneCenterAxes.setPosition(drone.getPosition());
            droneCenterAxes.setOrientation(drone.getOrientation());
            droneCenterAxes.update(simpleShaderHandler);

            shaderHandler.use(camera);
            drone.update(shaderHandler);
            floor.update(shaderHandler);
            camera.setLookAt(drone.getPositionAsGlm());

            simpleShaderHandler.use(camera);
            axes.update(simpleShaderHandler);

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


