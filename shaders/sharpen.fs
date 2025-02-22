#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;  // The screen texture
uniform vec2 texelSize;      // Size of one pixel in UV coordinates

void main() {
    // Define the sharpening kernel
    float kernel[9] = float[](
         0.0, -1.0,  0.0,
        -1.0,  5.2, -1.0,
         0.0, -1.0,  0.0
    );

    // float kernel[9] = float[](
    //     0.0,  -1.5,  0.0,
    //     -1.5,  7.0, -1.5,
    //     0.0,  -1.5,  0.0
    // );

    // Offsets for sampling neighboring pixels
    vec2 offsets[9] = vec2[](
        vec2(-texelSize.x, -texelSize.y), vec2(0.0, -texelSize.y), vec2(texelSize.x, -texelSize.y),
        vec2(-texelSize.x,  0.0),         vec2(0.0,  0.0),         vec2(texelSize.x,  0.0),
        vec2(-texelSize.x,  texelSize.y), vec2(0.0,  texelSize.y), vec2(texelSize.x,  texelSize.y)
    );

    // Apply the kernel to the pixel and its neighbors
    vec4 color = vec4(0.0);
    for (int i = 0; i < 9; i++) {
        color += texture(texture0, fragTexCoord + offsets[i]) * kernel[i];
    }

    finalColor = color;
}
