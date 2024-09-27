// glitch.fs

#ifdef GL_ES
precision mediump float;
#endif

varying vec2 fragTexCoord;
varying vec4 fragColor;

uniform sampler2D texture0;
uniform float time;

float rand(vec2 co) {
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
    vec2 uv = fragTexCoord;

    // Glitch strength and maximum offset
    float strength = 0.1; //0.3;
    float maxOffset = 0.01; //0.02;

    // Horizontal glitch offset
    float yOffset = rand(vec2(uv.y, time)) * maxOffset * strength;
    uv.x += yOffset;

    // Sample the texture with the modified UVs
    vec4 color = texture2D(texture0, uv);

    // Randomly discard some lines to create a glitch effect
    float glitch = step(0.02, rand(vec2(time, uv.y)));
    color.rgb *= glitch;

    gl_FragColor = color;
}
