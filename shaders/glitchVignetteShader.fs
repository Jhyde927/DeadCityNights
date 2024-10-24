#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform sampler2D texture0;
uniform float time;

// Glitch effect uniforms
uniform float glitchStrength;  // Glitch strength
uniform float maxGlitchOffset; // Maximum offset

// Vignette uniforms
uniform vec2 resolution;     // Screen resolution (in pixels)
uniform float radius;        // Radius where the vignette starts (0.0 to 0.5)
uniform float softness;      // Softness of the vignette edges (0.0 to 0.5)

// Random function for glitch effect
float rand(vec2 co) {
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    vec2 uv = fragTexCoord;

    // Horizontal glitch offset
    float yOffset = rand(vec2(uv.y, time)) * maxGlitchOffset * glitchStrength;
    uv.x += yOffset;

    // Clamp UV coordinates to prevent out-of-bounds sampling
    uv.x = clamp(uv.x, 0.0, 1.0);

    // Sample the texture with the modified UVs
    vec4 color = texture(texture0, uv);

    // Randomly discard some lines to create a glitch effect
    float glitch = step(0.02, rand(vec2(time, uv.y)));
    color.rgb *= glitch;

    // Vignette effect
    vec2 position = gl_FragCoord.xy / resolution;
    position = position - vec2(0.5); // Shift origin to center of screen
    float len = length(position);

    float vignette = smoothstep(radius, radius - softness, len);

    // Apply the vignette effect by reducing the color intensity
    color.rgb *= vignette;

    finalColor = color;
}
