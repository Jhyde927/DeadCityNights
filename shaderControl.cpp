// shaderControl.cpp
#include "shaderControl.h"
#include <cstdlib>  // For srand and rand
#include <ctime>    // For time
#include "GameEnums.h"
#include <raymath.h>

void InitShaders(ShaderResources& shaders, int screenWidth, int screenHeight) {
    // Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    // Load shaders
    shaders.glowShader = LoadShader(0, "shaders/glow.fs");
    shaders.glitchShader = LoadShader(0, "shaders/glitch.fs");
    shaders.glowShader2 = LoadShader(0, "shaders/glow2.fs");
    shaders.outlineShader = LoadShader(0, "shaders/outline.fs");
    shaders.vignetteShader = LoadShader(0, "shaders/vignette.fs");
    shaders.glitchVignetteShader = LoadShader(0, "shaders/glitchVignetteShader.fs");
    shaders.pixelationShader = LoadShader(0, "shaders/pixelation.fs");
    shaders.outlineGlowShader = LoadShader(0, "shaders/outlineGlow.fs");
    
    shaders.rainbowOutlineShader = LoadShader(0, "shaders/rainbowOutline.fs");

    // Set up shader uniforms
    float resolution[2] = { static_cast<float>(screenWidth), static_cast<float>(screenHeight) };
    float glowThreshold = 0.01f;
    float glowIntensity = 2.0f;
    float glowColor[3] = { 0.5f, 1.0f, 2.0f };

    // Glow Shader 1
    SetShaderValue(shaders.glowShader, GetShaderLocation(shaders.glowShader, "resolution"), resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(shaders.glowShader, GetShaderLocation(shaders.glowShader, "glowColor"), glowColor, SHADER_UNIFORM_VEC3);
    SetShaderValue(shaders.glowShader, GetShaderLocation(shaders.glowShader, "glowThreshold"), &glowThreshold, SHADER_UNIFORM_FLOAT);

    // Glitch Shader
    shaders.timeLoc = GetShaderLocation(shaders.glitchShader, "time");
    shaders.totalTime = 0.0f;

    // Glow Shader 2 (Drunk Shader)
    shaders.glowThresholdLoc = GetShaderLocation(shaders.glowShader2, "glowThreshold");
    shaders.glowIntensityLoc = GetShaderLocation(shaders.glowShader2, "glowIntensity");
    shaders.resolutionLoc = GetShaderLocation(shaders.glowShader2, "resolution");

    SetShaderValue(shaders.glowShader2, shaders.glowThresholdLoc, &glowThreshold, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.glowShader2, shaders.glowIntensityLoc, &glowIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.glowShader2, shaders.resolutionLoc, resolution, SHADER_UNIFORM_VEC2);


    //setup outline shader

    // Get uniform locations
    int outlineColorLoc = GetShaderLocation(shaders.outlineShader, "outlineColor");
    int thresholdLoc = GetShaderLocation(shaders.outlineShader, "threshold");

    // Set uniform values
    float outlineColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };  // White color
    SetShaderValue(shaders.outlineShader, outlineColorLoc, outlineColor, SHADER_UNIFORM_VEC4);

    float threshold = 0.5f;
    SetShaderValue(shaders.outlineShader, thresholdLoc, &threshold, SHADER_UNIFORM_FLOAT);

    //setup vignette

    int resolutionLoc = GetShaderLocation(shaders.vignetteShader, "resolution");
    int radiusLoc = GetShaderLocation(shaders.vignetteShader, "radius");
    int softnessLoc = GetShaderLocation(shaders.vignetteShader, "softness");

    // Set the uniform values
    //float resolution[2] = { (float)screenWidth, (float)screenHeight };
    SetShaderValue(shaders.vignetteShader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    // Vignette effect parameters
    float radius = 1.0f;    // Starting radius (0.0 to 1.0)
    float softness = 0.6f;  // Softness of the edges

    SetShaderValue(shaders.vignetteShader, radiusLoc, &radius, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.vignetteShader, softnessLoc, &softness, SHADER_UNIFORM_FLOAT);


    //setup glitchVignetteShader

    int glitchStrengthLoc = GetShaderLocation(shaders.glitchVignetteShader, "glitchStrength");
    int maxGlitchOffsetLoc = GetShaderLocation(shaders.glitchVignetteShader, "maxGlitchOffset");


    shaders.timeLoc = GetShaderLocation(shaders.glitchVignetteShader, "time");
    resolutionLoc = GetShaderLocation(shaders.glitchVignetteShader, "resolution");
    int radiusLoc2 = GetShaderLocation(shaders.glitchVignetteShader, "radius");
    int softnessLoc2 = GetShaderLocation(shaders.glitchVignetteShader, "softness");


    SetShaderValue(shaders.glitchVignetteShader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    SetShaderValue(shaders.glitchVignetteShader, radiusLoc2, &radius, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.glitchVignetteShader, softnessLoc2, &softness, SHADER_UNIFORM_FLOAT);

    float glitchStrength = 0.05f;   // Adjust as needed
    float maxGlitchOffset = 0.01f; // Adjust as needed

    SetShaderValue(shaders.glitchVignetteShader, glitchStrengthLoc, &glitchStrength, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.glitchVignetteShader, maxGlitchOffsetLoc, &maxGlitchOffset, SHADER_UNIFORM_FLOAT);

    // Get uniform locations //rainbowOutline
    int outlineColorLoc2 = GetShaderLocation(shaders.rainbowOutlineShader, "outlineColor");
    int thresholdLoc2 = GetShaderLocation(shaders.rainbowOutlineShader, "threshold");
    //int timeLoc = GetShaderLocation(shaders.rainbowOutlineShader, "time");
    int textureSizeLoc2 = GetShaderLocation(shaders.rainbowOutlineShader, "textureSize");

    // Set uniform values
    float outlineColor2[4] = { 0.0f, 0.0f, 0.0f, 1.0f };  // White outline
    SetShaderValue(shaders.rainbowOutlineShader, outlineColorLoc2, outlineColor2, SHADER_UNIFORM_VEC4);

    float threshold2 = 0.9f;
    SetShaderValue(shaders.rainbowOutlineShader, thresholdLoc2, &threshold2, SHADER_UNIFORM_FLOAT);

    // Initialize time
    //float totalTime = 0.0f;

    // Set texture size (ensure you use the correct texture)
    float textureSize[2] = { (float)512.0, (float)512.0 };
    SetShaderValue(shaders.rainbowOutlineShader, textureSizeLoc2, textureSize, SHADER_UNIFORM_VEC2);
    

        //pixelation shader
    float ptextureSize[2] = {(float)1024.0, (float)1024.0};
    float pixelSize = 4.0f;
    SetShaderValue(shaders.pixelationShader, GetShaderLocation(shaders.pixelationShader, "pixelSize"), &pixelSize, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.pixelationShader, GetShaderLocation(shaders.pixelationShader, "textureSize"), ptextureSize, SHADER_UNIFORM_VEC2);


    //outline glow
    float glowSize = 2.0f;
    float threshold3 = 0.05f;
    float glowColor2[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    SetShaderValue(shaders.outlineGlowShader, GetShaderLocation(shaders.outlineGlowShader, "glowColor"), glowColor2, SHADER_UNIFORM_VEC4); // Orange glow
    SetShaderValue(shaders.outlineGlowShader, GetShaderLocation(shaders.outlineGlowShader, "threshold"), &threshold3, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.outlineGlowShader, GetShaderLocation(shaders.outlineGlowShader, "glowSize"), &glowSize, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.outlineGlowShader, GetShaderLocation(shaders.outlineGlowShader, "textureSize"), ptextureSize, SHADER_UNIFORM_VEC2);




}

void UnloadShaders(ShaderResources& shaders) {
    UnloadShader(shaders.glowShader);
    UnloadShader(shaders.glitchShader);
    UnloadShader(shaders.glowShader2);
    UnloadShader(shaders.outlineShader);
    UnloadShader(shaders.rainbowOutlineShader);
}

void UpdateShaders(ShaderResources& shaders, float deltaTime, GameState& gameState) {
    // Update time for glitch shader
    shaders.totalTime += deltaTime;
    int timeLoc = GetShaderLocation(shaders.rainbowOutlineShader, "time");
    //SetShaderValue(shaders.glitchShader, shaders.timeLoc, &shaders.totalTime, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.glitchVignetteShader, shaders.timeLoc, &shaders.totalTime, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.rainbowOutlineShader, timeLoc, &shaders.totalTime, SHADER_UNIFORM_FLOAT);

    ///update glowShader
    float time = GetTime();  // Get the total elapsed time
    float minThreshold = 0.2f;
    float maxThreshold = 0.6f;
    float oscillationSpeed = 0.9f;  // 1 second duration

    if (gameState == ASTRAL){ //Customized look for astral plane. 
        minThreshold = 0.2f;
        maxThreshold = 0.3f;
        oscillationSpeed = 0.9f;  // 1 second duration

    }
    // Calculate the oscillating glow threshold using a sine wave
    float glowThreshold = minThreshold + (maxThreshold - minThreshold) * (0.5f * (1.0f + sin(oscillationSpeed * time)));    

    // Set the glowThreshold uniform in the shader
    int glowThresholdLocation = GetShaderLocation(shaders.glowShader, "glowThreshold");
    SetShaderValue(shaders.glowShader, glowThresholdLocation, &glowThreshold, SHADER_UNIFORM_FLOAT);
    
}


