#version 330 core
layout(location = 0) in vec3 position; // Vertex position
layout(location = 1) in vec3 normal;   // Vertex normal

out vec3 FragPos;   // Position to pass to the fragment shader
out vec3 Normal;    // Normal to pass to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(position, 1.0)); // Transform vertex position
    Normal = normal; // Transform normal
    gl_Position = projection * view * vec4(FragPos, 1.0); // Final position
}
