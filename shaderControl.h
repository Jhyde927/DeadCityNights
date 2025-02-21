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
    Shader highlightShader;
    Shader sharpenShader;
    
    int timeLoc;
    int glowThresholdLoc;
    int glowIntensityLoc;
    int resolutionLoc;
    int vignetteColorLoc;
    int radiusLoc;

    
    float totalTime;
};


void InitShaders(int screenWidth, int screenHeight);


void UnloadShaders();

// Function to update shader variables (e.g., time)
void UpdateShaders(float deltaTime, bool fullscreen, GameState& gameState);

extern ShaderResources shaders;

#endif // SHADERCONTROL_H
