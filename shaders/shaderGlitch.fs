#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

out vec4 finalColor;

uniform sampler2D texture0;  // Main texture
uniform float time;          // Time uniform for dynamic effects

void main()
{
    vec2 uv = fragTexCoord;

    // Screen curvature effect
    uv = uv * 2.0 - 1.0;  // Transform uv coordinates to range [-1, 1]
    float len = length(uv);
    uv = uv + uv * len * 0.001;  // Apply radial distortion
    uv = uv * 0.5 + 0.5;  // Transform uv back to range [0, 1]

    // Check if uv is outside of the visible screen area after distortion
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0)
    {
        finalColor = vec4(0.0, 0.0, 0.0, 1.0);  // Black border for out-of-bounds
        return;
    }

    // Scanline effect
    float scanline = sin(uv.y * 800.0) * 0.04;  // Create scanlines
    vec4 color = texture(texture0, uv);

    // Color distortion for RGB channels
    color.r = texture(texture0, uv + vec2(0.001, 0.0)).r;
    color.g = texture(texture0, uv).g;
    color.b = texture(texture0, uv - vec2(0.001, 0.0)).b;

    // Combine effects
    finalColor = color * (1.0 - scanline);  // Apply scanlines to color
}
