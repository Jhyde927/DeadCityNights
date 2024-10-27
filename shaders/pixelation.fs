#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform sampler2D texture0;    // The texture sampler
uniform float pixelSize;       // Size of the pixelation effect (in pixels)
uniform vec2 screenSize;       // Screen resolution

void main()
{
    // Get the fragment's screen coordinates
    vec2 screenPos = gl_FragCoord.xy;

    // Calculate the size of each "pixel" in screen coordinates
    float size = pixelSize;

    // Adjust the screen position to the center of the pixel grid
    vec2 pixelPos = floor(screenPos / size) * size + size * 0.5;

    // Flip the Y-coordinate to match the texture coordinate system
    pixelPos.y = screenSize.y - pixelPos.y;

    // Convert back to normalized texture coordinates
    vec2 uv = pixelPos / screenSize;

    // Sample the texture at the adjusted UV coordinates
    vec4 color = texture(texture0, uv);

    finalColor = color * fragColor;
}
