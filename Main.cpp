#include "Window.h"
#include "Context.h"
#include "Camera.h"
#include "Axes.h"
#include "EventHandling.h"
#include "ShaderHandler.h"

int main(int argc, char* argv[]) 
{
    Window window("Physics Engine", 1000, 1000);
    Context context(window);
    EventState eventState;
    EventHandling eventHandling(eventState);
    ShaderHandler shaderHandler("vertex_shader.glsl", "fragment_shader.glsl");
    Camera camera(eventState);
    Axes axes;

    while (!eventState.quit) 
    {
        eventHandling.update();

        //shaderHandler.use();

        //camera.update(shaderHandler);

        //axes.drawAxes(shaderHandler, camera.getViewMatrix(), camera.getProjectionMatrix());

        context.clear();
        window.swapBuffers();
    }

    return 0;
}


