#version 460 core

layout(location = 0) in vec3 position; // Input vertex position

uniform mat4 model;      // Model matrix
uniform mat4 view;       // View matrix
uniform mat4 projection;  // Projection matrix

void main()
{
    // Transform the vertex position with the model, view, and projection matrices
    gl_Position = projection * view * model * vec4(position, 1.0);
}




