#version 330 core

layout(location = 0) in vec3 aPos;  // Assume (x, height, z)

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out float vHeight;

void main() {
    vHeight = aPos.y;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

