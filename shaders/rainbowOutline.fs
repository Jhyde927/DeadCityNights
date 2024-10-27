#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;      // The texture sampler
uniform vec4 outlineColor;       // Color of the outline
uniform float threshold;         // Alpha threshold
uniform float time;              // Time uniform for animation
uniform vec2 textureSize;        // Texture size in pixels

out vec4 finalColor;

vec3 HSLtoRGB(float h, float s, float l) {
    float c = (1.0 - abs(2.0 * l - 1.0)) * s;
    float x = c * (1.0 - abs(mod(h * 6.0, 2.0) - 1.0));
    float m = l - c / 2.0;
    vec3 rgb;

    if (h < 1.0 / 6.0) {
        rgb = vec3(c, x, 0.0);
    } else if (h < 2.0 / 6.0) {
        rgb = vec3(x, c, 0.0);
    } else if (h < 3.0 / 6.0) {
        rgb = vec3(0.0, c, x);
    } else if (h < 4.0 / 6.0) {
        rgb = vec3(0.0, x, c);
    } else if (h < 5.0 / 6.0) {
        rgb = vec3(x, 0.0, c);
    } else {
        rgb = vec3(c, 0.0, x);
    }

    rgb += vec3(m);
    return rgb;
}

void main() {
    // Sample the current pixel's alpha
    float alpha = texture(texture0, fragTexCoord).a;

    if (alpha < threshold) {
        discard;  // Discard fully transparent pixels
    }

    // Get texel size (size of one pixel in texture coordinates)
    vec2 texelSize = 1.0 / textureSize;

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
        vec2 offsetCoord = fragTexCoord + offsets[i];
        // Ensure the coordinates are within texture bounds
        if (offsetCoord.x < 0.0 || offsetCoord.x > 1.0 || offsetCoord.y < 0.0 || offsetCoord.y > 1.0) {
            continue;
        }

        float neighborAlpha = texture(texture0, offsetCoord).a;
        if (neighborAlpha < threshold) {
            isEdge = true;
            break;
        }
    }

    if (isEdge) {
        // Edge pixel; set the outline color
        finalColor = vec4(outlineColor.rgb, 1.0); //outline is half transparent
    } else {
        // Interior pixel; set to rainbow color

        // Generate hue based on texture coordinates and time
        float hue = mod(fragTexCoord.y + time * 0.2, 1.0);

        // Convert HSL to RGB
        vec3 rgb = HSLtoRGB(hue, 1.0, 0.5);

        finalColor = vec4(rgb, 0.40); //semi transparent
    }
}
