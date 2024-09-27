#version 330

// Input texture and attributes
uniform sampler2D texture0;
uniform vec2 resolution;
uniform vec3 glowColor;
uniform float glowThreshold;  // This value is now oscillating

// Varying from vertex shader
in vec2 fragTexCoord;

// Output color
out vec4 fragColor;

void main() {
    // Flip the Y-coordinate to fix the upside-down rendering
    vec2 uv = vec2(fragTexCoord.x, fragTexCoord.y - 1);

    // Get the color from the texture
    vec4 texColor = texture(texture0, uv);

    // If the color is brighter than the threshold, apply glow
    float brightness = max(texColor.r, max(texColor.g, texColor.b));
    if (brightness > glowThreshold) {
        texColor.rgb += glowColor * (brightness - glowThreshold);
    }

    // Output the final color
    fragColor = texColor;
}
