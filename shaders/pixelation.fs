#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform float pixelSize;
uniform vec2 textureSize;

out vec4 finalColor;

void main() {
    // Calculate pixelated UV coordinates
    vec2 uv = fragTexCoord * textureSize;
    uv = floor(uv / pixelSize) * pixelSize;
    uv /= textureSize;

    vec4 texColor = texture(texture0, uv);

    finalColor = texColor;
}
