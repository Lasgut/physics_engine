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

int main(int argc, char* argv[]) 
{
    Window window("Physics Engine", 900, 900);
    Context context(window);
    EventState eventState;
    EventHandler eventHandler(eventState);
    ShaderHandler simpleShaderHandler("/home/lasse/free/ws/physics_engine/shaders/vertex_shader_simple.glsl", 
                                      "/home/lasse/free/ws/physics_engine/shaders/fragment_shader_simple.glsl");
    ShaderHandler shaderHandler("/home/lasse/free/ws/physics_engine/shaders/vertex_shader.glsl", 
                                "/home/lasse/free/ws/physics_engine/shaders/fragment_shader.glsl");
    Triangle triangle;
    Floor floor;
    Drone drone;
    
    Clock  clock;
    Camera camera(eventState);
    Light  light;
    Axes   axes(0.5f);

    while (!eventState.quit) 
    {
        clock.setPreviousTime();

        eventHandler.update();
        context.clear();

        camera.update();

        simpleShaderHandler.use(camera);
        axes.update(simpleShaderHandler);

        shaderHandler.use(camera);
        light.update(shaderHandler, camera);

        drone.update(shaderHandler, clock);
        floor.update(shaderHandler);

        window.swapBuffers();
    }

    return 0;
}


