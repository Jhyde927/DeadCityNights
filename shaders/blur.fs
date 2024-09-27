// blur.fs

#ifdef GL_ES
precision mediump float;
#endif

#define KERNEL_SIZE 9

varying vec2 fragTexCoord;
uniform sampler2D texture0;
uniform vec2 resolution;
uniform float blurAmount; // New uniform variable

void main() {
    vec2 uv = fragTexCoord;
    vec4 color = vec4(0.0);

    // Blur kernel weights
    float kernel[KERNEL_SIZE];
    kernel[0] = 0.05;
    kernel[1] = 0.09;
    kernel[2] = 0.12;
    kernel[3] = 0.15;
    kernel[4] = 0.16;
    kernel[5] = 0.15;
    kernel[6] = 0.12;
    kernel[7] = 0.09;
    kernel[8] = 0.05;

    // Adjust offset based on blurAmount
    float offset = (blurAmount / resolution.x);

    for (int i = 0; i < KERNEL_SIZE; i++) {
        float x = float(i - (KERNEL_SIZE - 1) / 2) * offset;
        color += texture2D(texture0, uv + vec2(x, 0.0)) * kernel[i];
    }

    gl_FragColor = color;
}
