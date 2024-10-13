#version 330 core

in vec3 FragPos;  // Position from vertex shader
in vec3 Normal;   // Normal from vertex shader

out vec4 FragColor;  // Output color to the framebuffer

uniform vec3 objectColor;  // Color of the object
uniform vec3 lightColor;   // Color of the light
uniform vec3 lightPos;     // Position of the light
uniform vec3 viewPos;      // Camera Position

void main()
{   
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
