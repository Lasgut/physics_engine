#include "Window.h"
#include "Context.h"
#include "Camera.h"
#include "Axes.h"
#include "EventHandler.h"
#include "ShaderHandler.h"
#include "Triangle.h"
#include "Cube.h"

int main(int argc, char* argv[]) 
{
    Window window("Physics Engine", 900, 900);
    Context context(window);
    EventState eventState;
    EventHandler eventHandler(eventState);
    ShaderHandler shaderHandler("/home/lasse/free/ws/physics_engine/shaders/mat4_vertex_shader.glsl", 
                                "/home/lasse/free/ws/physics_engine/shaders/triangle_fragment_shader.glsl");
    Triangle triangle;
    Cube cube;
    
    // Camera camera(eventState);
    // Axes axes;

    while (!eventState.quit) 
    {
        eventHandler.update();
        context.clear();
        shaderHandler.use();
        
        //camera.update(shaderHandler);
        //axes.drawAxes(shaderHandler, camera.getViewMatrix(), camera.getProjectionMatrix());

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.0f, -0.3f, 0.0f));
        trans = glm::rotate(trans, (float)SDL_GetTicks()/1000, glm::vec3(0.0f, 1.0f, 0.0f));

        shaderHandler.setMat4("transform",trans);

        //triangle.draw();
        cube.draw();

        window.swapBuffers();
    }

    return 0;
}


