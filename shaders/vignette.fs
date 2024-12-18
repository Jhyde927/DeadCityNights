#version 330 // vignette of just screen

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;    // The texture sampler
uniform vec2 resolution;       // Screen resolution (in pixels)
uniform float radius;          // Radius where the vignette starts (0.0 to 0.5)
uniform float softness;        // Softness of the vignette edges (0.0 to 0.5)
uniform vec3 vignetteColor;    // Vignette color parameter (added)

out vec4 finalColor;

void main()
{
    // Get the color from the texture
    vec4 color = texture(texture0, fragTexCoord);

    // Calculate the normalized position using gl_FragCoord
    vec2 position = gl_FragCoord.xy / resolution;
    position = position - vec2(0.5); // Shift origin to center of screen
    float len = length(position);

    // Calculate the vignette factor using smoothstep for smooth transition
    float vignette = smoothstep(radius, radius - softness, len);

    // Apply the vignette effect by blending towards the vignetteColor
    color.rgb = mix(color.rgb, vignetteColor, 1.0 - vignette); // Modified line

    finalColor = color * fragColor;
}





// #version 330 //vignette of just screen

// in vec2 fragTexCoord;
// in vec4 fragColor;

// uniform sampler2D texture0;  // The texture sampler
// uniform vec2 resolution;     // Screen resolution (in pixels)
// uniform float radius;        // Radius where the vignette starts (0.0 to 0.5)
// uniform float softness;      // Softness of the vignette edges (0.0 to 0.5)

// out vec4 finalColor;

// void main()
// {
//     // Get the color from the texture
//     vec4 color = texture(texture0, fragTexCoord);

//     // Calculate the normalized position using gl_FragCoord
//     vec2 position = gl_FragCoord.xy / resolution;
//     position = position - vec2(0.5); // Shift origin to center of screen
//     float len = length(position);

//     // Calculate the vignette factor using smoothstep for smooth transition
//     float vignette = smoothstep(radius, radius - softness, len);

//     // Apply the vignette effect by reducing the color intensity
//     color.rgb *= vignette;

//     finalColor = color * fragColor;
// }


