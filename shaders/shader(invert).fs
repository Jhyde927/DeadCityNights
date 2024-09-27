#version 330

in vec2 fragTexCoord;  // Texture coordinate passed from the vertex shader
in vec4 fragColor;     // Color passed from the vertex shader

out vec4 finalColor;

uniform sampler2D texture0;  // Texture sampler

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord); // Get the color from the texture
    finalColor = vec4(1.0 - texelColor.rgb, texelColor.a); // Invert color
}
