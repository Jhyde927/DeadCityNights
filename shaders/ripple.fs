#version 330

uniform sampler2D texture0;  // The game screen texture
uniform float time;          // Time variable to animate the ripples
uniform vec2 resolution;     // Screen resolution
uniform float intensity;     // Controls how strong the wave effect is

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;  // Normalize screen coordinates

    // Flip the y-coordinate to correct the upside-down effect
    uv.y = 1.0 - uv.y;

    // Adjust the intensity of the distortion (lower values will reduce zooming effect)
    float wave = sin(uv.x * 5.0 + time * 2.0) * intensity;  // Ripple on x-axis
    wave += sin(uv.y * 5.0 + time * 2.0) * intensity;       // Ripple on y-axis

    uv.y += wave;  // Apply wave distortion on y-coordinate
    uv.x += wave;  // Apply wave distortion on x-coordinate

    // Sample the texture at the distorted UV coordinates
    vec4 color = texture(texture0, uv);

    // Output the final color
    gl_FragColor = color;
}
