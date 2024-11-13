#version 330

in vec2 fragTexCoord;

uniform sampler2D texture0;
uniform float time;
uniform vec2 resolution;
uniform float grainIntensity;
uniform float sepiaIntensity;
uniform float flickerIntensity;
uniform float scratchIntensity;

out vec4 finalColor;

// Function to generate random noise based on coordinates
float rand(vec2 co)
{
    return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
    // Sample the scene texture
    vec4 color = texture(texture0, fragTexCoord);

    // Apply flickering effect
    float flicker = (rand(vec2(time, 0.0)) - 0.5) * flickerIntensity + 1.0;
    color.rgb *= flicker;

    // Apply sepia tone
    vec3 sepiaColor = vec3(
        dot(color.rgb, vec3(0.393, 0.769, 0.189)),
        dot(color.rgb, vec3(0.349, 0.686, 0.168)),
        dot(color.rgb, vec3(0.272, 0.534, 0.131))
    );
    color.rgb = mix(color.rgb, sepiaColor, sepiaIntensity);

    // Add film grain
    float grain = rand(fragTexCoord * resolution + time) - 0.5;
    color.rgb += grain * grainIntensity;

    // Add procedural scratches (optional)
    float scratch = step(0.995, rand(vec2(fragTexCoord.y * 1000.0, time))) * scratchIntensity;
    color.rgb = mix(color.rgb, vec3(1.0), scratch);

    // Clamp the final color
    finalColor = vec4(clamp(color.rgb, 0.0, 1.0), color.a);
}
