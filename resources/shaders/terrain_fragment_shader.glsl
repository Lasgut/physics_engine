#version 330 core
in float gHeight;
out vec4 FragColor;

void main() {
    // Normalize height from [-16, 47.75] to [0, 1]
    float h = (gHeight + 16.0) / (47.75 + 16.0); // = (gHeight + 16) / 63.75
    h = pow(h, 1.5); // Optional: exaggerate terrain contrast

    // Define terrain gradient colors
    vec3 low   = vec3(0.1, 0.4, 0.1); // dark green
    vec3 high  = vec3(0.9, 0.9, 0.9); // light gray
    vec3 terrainColor = mix(low, high, h);

    // Gaussian water color fade — peak at gHeight = -16
    float waterFactor = exp(-pow((gHeight + 16.0) / 3.0, 2.0)); // Width ~3 units
    vec3 waterColor = vec3(0.1, 0.2, 0.8); // deep blue
    vec3 blendedColor = mix(terrainColor, waterColor, waterFactor);

    // Slope shading
    float slopeDarkening = clamp(1.0 - abs(dFdx(gHeight)) - abs(dFdy(gHeight)), 0.0, 1.0);

    FragColor = vec4(blendedColor * slopeDarkening, 1.0);
}
