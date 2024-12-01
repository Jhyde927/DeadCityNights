#version 330

in vec2 fragTexCoord;           // Texture coordinates
in vec4 fragColor;              // Input fragment color (unused in this shader)

uniform sampler2D texture0;     // The texture sampler
uniform vec4 outlineColor;      // Color of the outline
uniform float threshold;        // Alpha threshold for transparency

out vec4 finalColor;            // Output fragment color

void main() {
    // Sample the current pixel's color and alpha
    vec4 texColor = texture(texture0, fragTexCoord);

    // Discard fully transparent pixels
    if (texColor.a < threshold) {
        discard;
    }

    // Get texel size (size of one pixel in texture coordinates)
    vec2 texSize = textureSize(texture0, 0);
    vec2 texelSize = 1.0 / texSize;

    // Initialize edge detection flag
    bool isEdge = false;

    // Offsets for neighboring pixels (up, down, left, right)
    vec2 offsets[4] = vec2[](
        vec2(-texelSize.x, 0.0),   // Left
        vec2(texelSize.x, 0.0),    // Right
        vec2(0.0, -texelSize.y),   // Up
        vec2(0.0, texelSize.y)     // Down
    );

    // Check neighboring pixels
    for (int i = 0; i < 4; i++) {
        float neighborAlpha = texture(texture0, fragTexCoord + offsets[i]).a;
        if (neighborAlpha < threshold) {
            isEdge = true;
            break;
        }
    }

    // Combine interior pixels and edge pixels
    if (isEdge) {
        // Edge pixel: add the outline color on top
        finalColor = vec4(outlineColor.rgb, 0.99); // Control outline alpha here
    } else {
        // Interior pixel: render normally
        finalColor = texColor;
    }
}
