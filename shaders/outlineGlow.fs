#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 glowColor;
uniform float threshold;
uniform float glowSize;
uniform vec2 textureSize;

out vec4 finalColor;

void main() {
    float alpha = texture(texture0, fragTexCoord).a;

    if (alpha < threshold) {
        discard;
    }

    vec2 texelSize = 1.0 / textureSize;
    float glow = 0.0;

    // Sample neighboring pixels to create the glow effect
    for (int x = -int(glowSize); x <= int(glowSize); x++) {
        for (int y = -int(glowSize); y <= int(glowSize); y++) {
            vec2 offset = vec2(float(x), float(y)) * texelSize;
            float neighborAlpha = texture(texture0, fragTexCoord + offset).a;
            if (neighborAlpha > threshold) {
                glow = 1.0;
            }
        }
    }

    if (glow > 0.0) {
        // Blend the glow color with the sprite color
        vec4 spriteColor = texture(texture0, fragTexCoord);
        finalColor = mix(spriteColor, glowColor, 0.5);
    } else {
        finalColor = texture(texture0, fragTexCoord);
    }
}
