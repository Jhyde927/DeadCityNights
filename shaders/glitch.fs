#version 330

uniform float time;        // Current time, for animating the glitch effect
uniform float intensity;   // Glitch intensity (controls how many lines are affected)
uniform vec2 resolution;   // Screen resolution

in vec2 fragTexCoord;      // Texture coordinate
out vec4 finalColor;       // Output fragment color

uniform sampler2D texture0; // The game's main screen texture

void main() {
    // Compute the current line in screen coordinates
    float yCoord = fragTexCoord.y * resolution.y;

    // Generate a random value based on the line number and time
    float glitchValue = fract(sin(yCoord * 0.1 + time) * 43758.5453123);

    // Discard some lines based on glitch intensity
    if (glitchValue < intensity) {
        discard;
    }

    // Apply the texture color for unaffected pixels
    finalColor = texture(texture0, fragTexCoord);
}