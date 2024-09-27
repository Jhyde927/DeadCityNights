// glow.fs

#ifdef GL_ES
precision mediump float;
#endif

varying vec2 fragTexCoord;
uniform sampler2D texture0;
uniform float glowThreshold; // The threshold above which pixels will glow
uniform float glowIntensity; // Intensity of the glow
uniform vec2 resolution;     // Resolution of the screen

void main() {
    vec2 uv = fragTexCoord;
    vec4 color = texture2D(texture0, uv);

    // Calculate the luminance of the pixel
    float luminance = dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));

    if (luminance > glowThreshold) {
        // Apply a simple blur around the bright pixel
        vec4 glow = vec4(0.0);
        float total = 0.0;
        float offset = 1.0 / resolution.x * glowIntensity; // Adjust based on intensity

        // Simple blur kernel (3x3)
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                vec2 samplePos = uv + vec2(float(x), float(y)) * offset;
                glow += texture2D(texture0, samplePos);
                total += 1.0;
            }
        }
        glow /= total;

        // Combine the original color with the glow
        color = mix(color, glow, 0.5);
    }

    gl_FragColor = color;
}
