#version 330 core

layout (triangles) in;                          // Input primitive is a triangle
layout (triangle_strip, max_vertices = 3) out;  // Output primitive is a triangle strip

// Lighting related uniforms
uniform vec3 lightDirection;        // Direction of the light
uniform vec3 lightColour;           // Color of the light
uniform vec2 lightBias;             // Bias for light calculation
uniform mat4 projectionViewMatrix;  // Projection + View matrix

out vec3 finalColour;   // Final color to pass to fragment shader

// Lighting calculation function
vec3 
calculateLighting(vec3 normal) 
{
    float brightness = max(dot(-lightDirection, normal), 0.0);
    return (lightColour * lightBias.x) + (brightness * lightColour * lightBias.y);
}

// Calculate the normal of the triangle using the cross product
vec3
calcTriangleNormal() 
{
    vec3 tangent1 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 tangent2 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 normal = cross(tangent1, tangent2);
    return normalize(normal);
}

void 
main(void) 
{
    vec3 normal = calcTriangleNormal();   // Calculate the normal for this triangle
    vec3 lighting = calculateLighting(normal);   // Calculate lighting based on the normal
    
    // Loop over all vertices of the triangle
    for (int i = 0; i < 3; i++) {
        gl_Position = projectionViewMatrix * gl_in[i].gl_Position;  // Apply the projection and view matrix to position
        
        // Use the height (y-coordinate) to calculate the color
        float height = gl_in[i].gl_Position.y;  // Extract the height (y-coordinate)
        float normalizedHeight = (height + 5.0) / 21.0;  // Normalize height to [0, 1] range (adjust based on your terrain's height range)
        finalColour = vec3(normalizedHeight, 1.0 - normalizedHeight, 0.5);  // Map height to a gradient (red-green-blue)

        EmitVertex();  // Emit vertex to the next stage
    }

    EndPrimitive();  // End the triangle
}


