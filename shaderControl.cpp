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







}

void UnloadShaders(ShaderResources& shaders) {
    UnloadShader(shaders.glowShader);
    UnloadShader(shaders.glitchShader);
    UnloadShader(shaders.glowShader2);
}

void UpdateShaders(ShaderResources& shaders, float deltaTime, GameState& gameState) {
    // Update time for glitch shader
    shaders.totalTime += deltaTime;
    SetShaderValue(shaders.glitchShader, shaders.timeLoc, &shaders.totalTime, SHADER_UNIFORM_FLOAT);

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


