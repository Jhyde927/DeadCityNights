#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;      // The texture sampler
uniform vec4 outlineColor;       // Color of the outline
uniform float threshold;         // Alpha threshold

out vec4 finalColor;

void main() {
    // Sample the current pixel's alpha
    float alpha = texture(texture0, fragTexCoord).a;

    if (alpha < threshold) {
        discard;  // Discard fully transparent pixels
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

    if (isEdge) {
        // Edge pixel; set the outline color
        finalColor = vec4(outlineColor.rgb, 1.0);
    } else {
        // Interior pixel; make it transparent
        discard;
    }
}
