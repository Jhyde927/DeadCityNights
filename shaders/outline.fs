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

    // Define neighbor offsets (up, down, left, right)
    vec2 offsets[4];

    if (useWhiteOutline) { 
        // White outline (thicker)
        offsets[0] = vec2(-texelSize.x, 0.0);   // Left
        offsets[1] = vec2(texelSize.x, 0.0);    // Right
        offsets[2] = vec2(0.0, -texelSize.y);   // Up
        offsets[3] = vec2(0.0, texelSize.y);    // Down
    } else {
        // Black outline (thinner)
        offsets[0] = vec2(-texelSize.x/2, 0.0);   // Left
        offsets[1] = vec2(texelSize.x/2, 0.0);    // Right
        offsets[2] = vec2(0.0, -texelSize.y/2);   // Up
        offsets[3] = vec2(0.0, texelSize.y/2);    // Down
    }

    // Check neighboring pixels
    bool isEdge = false;
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
            finalColor = vec4(1.0, 1.0, 1.0, 1.0); // Make the interior completely white for black outline mode
        }
    }
}
