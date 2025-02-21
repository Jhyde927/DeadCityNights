#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;      // The texture sampler
uniform vec4 outlineColor;       // Color of the outline
uniform float threshold;         // Alpha threshold
uniform bool useWhiteOutline;    // Determines if the outline is white or black

out vec4 finalColor;

void main() {
    // Sample the current pixel color and alpha
    vec4 texColor = texture(texture0, fragTexCoord);
    float alpha = texColor.a;

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
        vec2(-texelSize.x/2, 0.0),   // Left
        vec2(texelSize.x/2, 0.0),    // Right
        vec2(0.0, -texelSize.y/2),   // Up
        vec2(0.0, texelSize.y/2)     // Down
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
        // Choose outline color based on uniform
        vec3 finalOutlineColor = useWhiteOutline ? vec3(1.0, 1.0, 1.0) : vec3(0.0, 0.0, 0.0);
        finalColor = vec4(finalOutlineColor, 1.0);
    } else {
        if (useWhiteOutline) {
            discard; // Discard interior pixels when using a white outline
        } else {
            //finalColor = texColor; // Keep original sprite color when using a black outline
            finalColor = vec4(1.0, 1.0, 1.0, 1.0); // Make the interior completely white for black outline mode
        }
    }
}
