#version 330

in vec2 fragTexCoord;

uniform sampler2D texture0;
uniform vec2 resolution;         // Resolution of the screen or render texture
uniform float vignetteIntensity; // Intensity of the vignette effect (0.0 to 1.0)
uniform vec4 tintColor;          // Color of the vignette tint (e.g., semi-transparent red)

out vec4 finalColor;

void main()
{
    // Sample the original texture color
    vec4 color = texture(texture0, fragTexCoord);

    // Calculate the distance from the center of the screen
    vec2 position = (fragTexCoord * resolution - resolution * 0.5) / resolution;
    float distance = length(position);

    // Calculate the vignette effect
    float vignette = smoothstep(0.5, vignetteIntensity + 0.5, distance);

    // Apply the tint color to the vignette effect
    vec4 vignetteColor = mix(vec4(1.0), tintColor, vignette);

    // Combine the original color with the vignette effect
    finalColor = color * vignetteColor;
}
