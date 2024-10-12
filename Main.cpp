#include "Window.h"
#include "Context.h"
#include "Camera.h"
#include "Axes.h"
#include "EventHandler.h"
#include "ShaderHandler.h"
#include "Triangle.h"
#include "Cube.h"
#include "Light.h"

int main(int argc, char* argv[]) 
{
    Window window("Physics Engine", 900, 900);
    Context context(window);
    EventState eventState;
    EventHandler eventHandler(eventState);
    ShaderHandler shaderHandler("/home/lasse/free/ws/physics_engine/shaders/vertex_shader.glsl", 
                                "/home/lasse/free/ws/physics_engine/shaders/fragment_shader.glsl");
    Triangle triangle;
    Cube cube;
    
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

        //axes.drawAxes(shaderHandler, camera.getViewMatrix(), camera.getProjectionMatrix());

        shaderHandler.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        shaderHandler.setVec3("ambient", glm::vec3(0.5f, 0.5f, 0.5f));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        //model = glm::rotate(model, (float)SDL_GetTicks()/1000, glm::vec3(0.0f, 1.0f, 0.0f));

        shaderHandler.setMat4("model",model);

        //triangle.draw();
        cube.draw();

        window.swapBuffers();
    }

    return 0;
}


