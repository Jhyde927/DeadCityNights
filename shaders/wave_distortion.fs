// wave_distortion.fs

#ifdef GL_ES
precision mediump float;
#endif

varying vec2 fragTexCoord;
uniform sampler2D texture0;
uniform float time; // Uniform variable to receive time from the CPU

void main() {
    vec2 uv = fragTexCoord;

    // Wave parameters
    float frequency = 10.0;
    float amplitude = 1.0;

    // Apply wave distortion using the time variable
    uv.y += sin(uv.x * frequency + time * 2.0) * amplitude;
    uv.x += cos(uv.y * frequency + time * 2.0) * amplitude;

    vec4 color = texture2D(texture0, uv);
    gl_FragColor = color;
}
