// shaderControl.h
#ifndef SHADERCONTROL_H
#define SHADERCONTROL_H

#include "raylib.h"
#include "GameEnums.h"
//#include "Player.h"



// Structure to hold all your shaders and related variables
struct ShaderResources {
    Shader glowShader;
    Shader glitchShader;
    Shader glowShader2;
    Shader outlineShader;
    Shader vignetteShader;
    Shader glitchVignetteShader;
    Shader pixelationShader;
    Shader outlineGlowShader; 
    Shader rainbowOutlineShader;
    Shader oldFilmShader;
 
    
    int timeLoc;
    int glowThresholdLoc;
    int glowIntensityLoc;
    int resolutionLoc;
    int vignetteColorLoc;
    int radiusLoc;

    // Add any other shader-related variables here
    float totalTime;
};

// Function to initialize shaders
void InitShaders(ShaderResources& shaders, int screenWidth, int screenHeight);

// Function to unload shaders when closing the application
void UnloadShaders(ShaderResources& shaders);

// Function to update shader variables (e.g., time)
void UpdateShaders(ShaderResources& shaders, float deltaTime, GameState& gameState);



#endif // SHADERCONTROL_H
