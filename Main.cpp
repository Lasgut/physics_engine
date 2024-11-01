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

int main(int argc, char* argv[]) 
{
    Window window("Physics Engine", 900, 900);
    Context context(window);
    EventState eventState;
    EventHandler eventHandler(eventState);
    ShaderHandler shaderHandler("/home/lasse/free/ws/physics_engine/shaders/vertex_shader.glsl", 
                                "/home/lasse/free/ws/physics_engine/shaders/fragment_shader.glsl");
    Triangle triangle;
    Floor floor;
    Drone drone;
    
    Camera camera(eventState);
    Light light;
    // Axes axes;

    while (!eventState.quit) 
    {
        eventHandler.update();
        context.clear();
        shaderHandler.use();
        
        camera.update(shaderHandler);
        light.update(shaderHandler, camera);

        floor.update(shaderHandler);
        drone.update(shaderHandler);

        window.swapBuffers();
    }

    return 0;
}


