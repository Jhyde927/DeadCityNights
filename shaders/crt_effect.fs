// crt_effect.fs

#ifdef GL_ES
precision mediump float;
#endif

varying vec2 fragTexCoord;
uniform sampler2D texture0;
uniform vec2 resolution;

void main() {
    vec2 uv = fragTexCoord;
    vec3 color = texture2D(texture0, uv).rgb;

    // Apply scanlines
    float scanline = sin(uv.y * resolution.y * 1.5) * 0.1;
    color -= scanline;

    // Apply vignette
    vec2 position = uv - vec2(0.5);
    float vignette = smoothstep(0.8, 0.5, length(position));
    color *= vignette;

    gl_FragColor = vec4(color, 1.0);
}
