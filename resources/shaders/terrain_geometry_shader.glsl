#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in float vHeight[];
out float gHeight;

void main() {
    for (int i = 0; i < 3; i++) {
        gHeight = vHeight[i];
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}



