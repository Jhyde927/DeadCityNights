// shaderControl.h
#ifndef SHADERCONTROL_H
#define SHADERCONTROL_H

#include "raylib.h"
#include "GameEnums.h"
//#include "Player.h"



// Structure to hold all shaders and related variables
struct ShaderResources {
    Shader glowShader;
    Shader glitchShader;
    Shader glowShader2;
    Shader outlineShader;
    Shader vignetteShader;
    Shader glitchVignetteShader;
    Shader pixelationShader;
    Shader rainbowOutlineShader;
    Shader oldFilmShader;
    Shader redVignetteShader;
    
    int timeLoc;
    int glowThresholdLoc;
    int glowIntensityLoc;
    int resolutionLoc;
    int vignetteColorLoc;
    int radiusLoc;

    
    float totalTime;
};


void InitShaders(ShaderResources& shaders, int screenWidth, int screenHeight);


void UnloadShaders(ShaderResources& shaders);

// Function to update shader variables (e.g., time)
void UpdateShaders(ShaderResources& shaders, float deltaTime, GameState& gameState);



#endif // SHADERCONTROL_H
