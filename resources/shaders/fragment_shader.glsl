#version 330 core

in vec3 FragPos;  
in vec3 Normal;   

out vec4 FragColor;  

uniform vec3 objectColor;  
uniform vec3 lightColor;   
uniform vec3 lightPos;     
uniform vec3 viewPos;      
uniform vec3 lightDir;

void main()
{   
    // Ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 toLight = normalize(lightPos - FragPos);
    float diff = max(dot(norm, toLight), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-toLight, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    // Spotlight (flashlight effect)
    float theta = dot(normalize(-lightDir), toLight);
    float cutoff = cos(radians(22.5));
    float outerCutoff = cos(radians(27.5));

    float intensity = clamp((theta - outerCutoff) / (cutoff - outerCutoff), 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;

    // Combine
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}


