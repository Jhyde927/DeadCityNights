// pixelation.fs

#ifdef GL_ES
precision mediump float;
#endif

varying vec2 fragTexCoord;
uniform sampler2D texture0;
uniform float pixelSize;

void main() {
    vec2 uv = fragTexCoord;

    // Calculate the size of each pixel block
    uv = floor(uv * pixelSize) / pixelSize;

    vec4 color = texture2D(texture0, uv);
    gl_FragColor = color;
}
