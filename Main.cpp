#include "Window.h"
#include "Context.h"
#include "Camera.h"
#include "Axes.h"
#include "EventHandler.h"
#include "ShaderHandler.h"
#include "Triangle.h"

int main(int argc, char* argv[]) 
{
    Window window("Physics Engine", 1000, 1000);
    Context context(window);
    EventState eventState;
    EventHandler eventHandling(eventState);
    ShaderHandler shaderHandler("/home/lasse/free/ws/physics_engine/shaders/triangle_vertex_shader.glsl", 
                                "/home/lasse/free/ws/physics_engine/shaders/triangle_fragment_shader.glsl");
    Triangle triangle;
    
    // Camera camera(eventState);
    // Axes axes;

    while (!eventState.quit) 
    {
        eventHandling.update();
        context.clear();
        shaderHandler.use();
        
        //camera.update(shaderHandler);
        //axes.drawAxes(shaderHandler, camera.getViewMatrix(), camera.getProjectionMatrix());

        triangle.draw();

        window.swapBuffers();
    }

    return 0;
}


