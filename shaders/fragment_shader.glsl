#version 330 core

in vec3 FragPos;  // Position from vertex shader
in vec3 Normal;   // Normal from vertex shader

out vec4 FragColor;  // Output color to the framebuffer

uniform vec3 objectColor;  // Color of the object
uniform vec3 lightColor;   // Color of the light
uniform vec3 lightPos;     // Position of the light
uniform vec3 ambient;      // Ambient color

void main()
{   
    // Ambient
    vec3 ambientColor = ambient * objectColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseColor = diff * lightColor * objectColor;

    // Combine
    vec3 result = ambientColor + diffuseColor;
    FragColor = vec4(result, 1.0);
}

