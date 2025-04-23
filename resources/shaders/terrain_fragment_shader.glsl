#version 330 core
in float gHeight;
out vec4 FragColor;

void main() {
    float h = (gHeight + 5.0) / 21.0;  // normalize [-5, 16] to [0, 1]
    h = pow(h, 1.5); // Exaggerate contrast, adjust exponent as needed

    vec3 low   = vec3(0.1, 0.4, 0.1);   // dark green
    vec3 high  = vec3(0.9, 0.9, 0.9);  // light gray/white
    vec3 color = mix(low, high, h);
    FragColor  = vec4(color, 1.0);

	float slopeDarkening = clamp(1.0 - abs(dFdx(gHeight)) - abs(dFdy(gHeight)), 0.0, 1.0);
	FragColor = vec4(color * slopeDarkening, 1.0);
}


