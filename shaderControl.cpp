// shaderControl.cpp
#include "shaderControl.h"
#include <cstdlib>  // For srand and rand
#include <ctime>    // For time
#include "GameEnums.h"
#include <raymath.h>
#include <iostream>
#include "Player.h"



ShaderResources shaders;

void InitShaders(int screenWidth, int screenHeight) {
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
    shaders.rainbowOutlineShader = LoadShader(0, "shaders/rainbowOutline.fs");
    shaders.oldFilmShader = LoadShader(0, "shaders/oldFilm.fs");
    shaders.redVignetteShader = LoadShader(0, "shaders/redVignette.fs");
    shaders.highlightShader = LoadShader(0, "shaders/highlight.fs");
    shaders.sharpenShader = LoadShader(0, "shaders/sharpen.fs");

    


    float resolution[2] = { static_cast<float>(screenWidth), static_cast<float>(screenHeight) }; //used for everything

    //sharpen Shader
    int texelSizeLoc = GetShaderLocation(shaders.sharpenShader, "texelSize");

    Vector2 texelSize = { 1.0f / screenWidth, 1.0f / screenHeight };
    SetShaderValue(shaders.sharpenShader, texelSizeLoc, &texelSize, SHADER_UNIFORM_VEC2);



    float glowThreshold = 0.01f;
    float drunkGlowThreshold = .15f;
  
    float glowColor[3] = { 0.5f, 0.5f, 2.0f }; //blue

    // Glow Shader 1 //we use the shader struct's vars here and no where else
    SetShaderValue(shaders.glowShader, GetShaderLocation(shaders.glowShader, "resolution"), resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(shaders.glowShader, GetShaderLocation(shaders.glowShader, "glowColor"), glowColor, SHADER_UNIFORM_VEC3);
    SetShaderValue(shaders.glowShader, GetShaderLocation(shaders.glowShader, "glowThreshold"), &glowThreshold, SHADER_UNIFORM_FLOAT);


    // Glow Shader 2 (Drunk Shader)
    int glowThresholdLoc = GetShaderLocation(shaders.glowShader2, "glowThreshold");
    int glowIntensityLoc = GetShaderLocation(shaders.glowShader2, "glowIntensity");
    int drunkResolutionLoc = GetShaderLocation(shaders.glowShader2, "resolution");

    float drunkglowIntensity = 0.5f;
    SetShaderValue(shaders.glowShader2, glowThresholdLoc, &drunkGlowThreshold, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.glowShader2, glowIntensityLoc, &drunkglowIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.glowShader2, drunkResolutionLoc, resolution, SHADER_UNIFORM_VEC2);


    //setup outline shader


    // Get uniform locations
    int outlineColorLoc = GetShaderLocation(shaders.outlineShader, "outlineColor");
    int thresholdLoc = GetShaderLocation(shaders.outlineShader, "threshold");

    // Set uniform values
    float outlineColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };  // White color
    SetShaderValue(shaders.outlineShader, outlineColorLoc, outlineColor, SHADER_UNIFORM_VEC4);

    float threshold = 0.5f;
    SetShaderValue(shaders.outlineShader, thresholdLoc, &threshold, SHADER_UNIFORM_FLOAT);



    //setup vignette////////////////////////////////////////////////////////////////

    int resolutionLoc = GetShaderLocation(shaders.vignetteShader, "resolution");
    int radiusLoc = GetShaderLocation(shaders.vignetteShader, "radius");
    int softnessLoc = GetShaderLocation(shaders.vignetteShader, "softness");
    int vignetteColorLoc = GetShaderLocation(shaders.vignetteShader, "vignetteColor");

    // Set the uniform values
   
    SetShaderValue(shaders.vignetteShader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    // Vignette effect parameters
    float radius = 0.9f;    // Starting radius (0.0 to 1.0)
    float softness = 0.5f;  // Softness of the edges

    SetShaderValue(shaders.vignetteShader, radiusLoc, &radius, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.vignetteShader, softnessLoc, &softness, SHADER_UNIFORM_FLOAT);

        // Set the initial vignette color (e.g., black)
    float vignetteColor[3] = { 0.0f, 0.0f, 0.0f }; // Black color
    SetShaderValue(shaders.vignetteShader, vignetteColorLoc, vignetteColor, SHADER_UNIFORM_VEC3);


    //setup glitchVignetteShader
    //int offsetLoc = GetShaderLocation(shaders.glitchVignetteShader, "offset");
    int glitchStrengthLoc = GetShaderLocation(shaders.glitchVignetteShader, "glitchStrength");
    int maxGlitchOffsetLoc = GetShaderLocation(shaders.glitchVignetteShader, "maxGlitchOffset");


    //int timeLoc = GetShaderLocation(shaders.glitchVignetteShader, "time");
    int resolutionLoc2 = GetShaderLocation(shaders.glitchVignetteShader, "resolution");
    int radiusLoc2 = GetShaderLocation(shaders.glitchVignetteShader, "radius");
    int softnessLoc2 = GetShaderLocation(shaders.glitchVignetteShader, "softness");
    float softness2 = 0.1;

    SetShaderValue(shaders.glitchVignetteShader, resolutionLoc2, resolution, SHADER_UNIFORM_VEC2);

    SetShaderValue(shaders.glitchVignetteShader, radiusLoc2, &radius, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.glitchVignetteShader, softnessLoc2, &softness2, SHADER_UNIFORM_FLOAT);

    float glitchStrength = 0.03f;   // Adjust as needed
    float maxGlitchOffset = 0.01f; // Adjust as needed

    SetShaderValue(shaders.glitchVignetteShader, glitchStrengthLoc, &glitchStrength, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.glitchVignetteShader, maxGlitchOffsetLoc, &maxGlitchOffset, SHADER_UNIFORM_FLOAT);


    //regular glitch

    //int timeLocGlitch = GetShaderLocation(shaders.glitchShader, "time");

    // Declare variables for resolution and intensity
    //float resolution[2] = {screenWidth, screenHeight};
    float intensity = 0.01f;

    // Set shader uniforms
    SetShaderValue(shaders.glitchShader, GetShaderLocation(shaders.glitchShader, "resolution"), resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(shaders.glitchShader, GetShaderLocation(shaders.glitchShader, "intensity"), &intensity, SHADER_UNIFORM_FLOAT);




    //rainbowOutline
    int outlineColorLoc2 = GetShaderLocation(shaders.rainbowOutlineShader, "outlineColor");
    int thresholdLoc2 = GetShaderLocation(shaders.rainbowOutlineShader, "threshold");
    //int timeLoc = GetShaderLocation(shaders.rainbowOutlineShader, "time");
    int textureSizeLoc2 = GetShaderLocation(shaders.rainbowOutlineShader, "textureSize");

   
    float outlineColor2[4] = { 0.0f, 0.0f, 0.0f, 1.0f };  // Black outline
    SetShaderValue(shaders.rainbowOutlineShader, outlineColorLoc2, outlineColor2, SHADER_UNIFORM_VEC4);

    float threshold2 = 1.0f;
    SetShaderValue(shaders.rainbowOutlineShader, thresholdLoc2, &threshold2, SHADER_UNIFORM_FLOAT);



    // Set texture size (ensure you use the correct texture)
    float textureSize[2] = { (float)512.0, (float)512.0 };
    SetShaderValue(shaders.rainbowOutlineShader, textureSizeLoc2, textureSize, SHADER_UNIFORM_VEC2);
    

        //pixelation shader
    float ptextureSize[2] = {(float)1024.0, (float)1024.0};
    float pixelSize = 5.0f;
    SetShaderValue(shaders.pixelationShader, GetShaderLocation(shaders.pixelationShader, "pixelSize"), &pixelSize, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.pixelationShader, GetShaderLocation(shaders.pixelationShader, "textureSize"), ptextureSize, SHADER_UNIFORM_VEC2);




    //old Film

    //int timeLocFilm = GetShaderLocation(shaders.oldFilmShader, "time");
    int resolutionLoc3 = GetShaderLocation(shaders.oldFilmShader, "resolution");
    int grainIntensityLoc = GetShaderLocation(shaders.oldFilmShader, "grainIntensity");
    int sepiaIntensityLoc = GetShaderLocation(shaders.oldFilmShader, "sepiaIntensity");

    int flickerIntensityLoc = GetShaderLocation(shaders.oldFilmShader, "flickerIntensity");
    int scratchIntensityLoc = GetShaderLocation(shaders.oldFilmShader, "scratchIntensity");

    // Set initial uniform values
    //float resolution[2] = { (float)GAME_SCREEN_WIDTH, (float)GAME_SCREEN_HEIGHT };
    SetShaderValue(shaders.oldFilmShader, resolutionLoc3, resolution, SHADER_UNIFORM_VEC2);

    // Set initial effect intensities
    float grainIntensity = 0.2f;      // Adjust as desired (keep small to avoid overpowering)
    float sepiaIntensity = 0.01f;       // Adjust as desired
    float flickerIntensity = 0.01f;    // Adjust as desired (keep small)
    float scratchIntensity = 0.1f;     // Adjust as desired (keep small)

    SetShaderValue(shaders.oldFilmShader, grainIntensityLoc, &grainIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.oldFilmShader, sepiaIntensityLoc, &sepiaIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.oldFilmShader, flickerIntensityLoc, &flickerIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.oldFilmShader, scratchIntensityLoc, &scratchIntensity, SHADER_UNIFORM_FLOAT);

    //red vignette


    int resolutionLocRed = GetShaderLocation(shaders.redVignetteShader, "resolution");
    int vignetteIntensityLoc = GetShaderLocation(shaders.redVignetteShader, "vignetteIntensity");
    int tintColorLoc = GetShaderLocation(shaders.redVignetteShader, "tintColor");

    SetShaderValue(shaders.redVignetteShader, resolutionLocRed, resolution, SHADER_UNIFORM_VEC2);

    float vignetteIntensity = 0.8f; // Range from 0.0 (no vignette) to 1.0 (strong vignette)
    SetShaderValue(shaders.redVignetteShader, vignetteIntensityLoc, &vignetteIntensity, SHADER_UNIFORM_FLOAT);

    float tintColor[4] = { 20.0f, 2.0f, 2.0f, 0.3f }; // RGBA values
    SetShaderValue(shaders.redVignetteShader, tintColorLoc, tintColor, SHADER_UNIFORM_VEC4);


    //highlight
    // Set uniform values
    float outlineColor3[4] = { 1.0f, 1.0f, 1.0f, 1.0f };  // color WHITE
    SetShaderValue(shaders.highlightShader, outlineColorLoc, outlineColor3, SHADER_UNIFORM_VEC4);

    float Othreshold = 0.5f;
    SetShaderValue(shaders.highlightShader, thresholdLoc, &Othreshold, SHADER_UNIFORM_FLOAT);

}

void UnloadShaders() {
    UnloadShader(shaders.glowShader);
    UnloadShader(shaders.glitchShader);
    UnloadShader(shaders.glowShader2);
    UnloadShader(shaders.outlineShader);
    UnloadShader(shaders.rainbowOutlineShader);
    UnloadShader(shaders.vignetteShader);
    UnloadShader(shaders.glitchVignetteShader);
    UnloadShader(shaders.oldFilmShader);
    UnloadShader(shaders.sharpenShader);
    

}

void UpdateShaders(float deltaTime, bool fullscreen, GameState& gameState) {
    // Update time for glitch shader
    float time_ = GetTime();
    //float renderWidth = 1024.0f;
    shaders.totalTime += deltaTime;
    int timeLoc = GetShaderLocation(shaders.rainbowOutlineShader, "time");
    int timeLoc2 = GetShaderLocation(shaders.oldFilmShader, "time");
    int timeLoc3 = GetShaderLocation(shaders.glitchVignetteShader, "time");
    //int timeLoc4 = GetShaderLocation(shaders.glitchShader, "time");
    //SetShaderValue(shaders.glitchShader, shaders.timeLoc, &shaders.totalTime, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.glitchVignetteShader, timeLoc3, &shaders.totalTime, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shaders.rainbowOutlineShader, timeLoc, &shaders.totalTime, SHADER_UNIFORM_FLOAT);
    //SetShaderValue(shaders.glitchShader, timeLoc4, &shaders.totalTime, SHADER_UNIFORM_FLOAT);

    SetShaderValue(shaders.glitchShader, GetShaderLocation(shaders.glitchShader, "time"), &time_, SHADER_UNIFORM_FLOAT);

    int useWhiteOutlineLoc = GetShaderLocation(shaders.outlineShader, "useWhiteOutline");
    int whiteOutline = 1;
    int blackOutline = 0;

    if (gameState == OFFICE){ //outline the player in black when in the office. 
        player.outline = true;
        SetShaderValue(shaders.outlineShader, useWhiteOutlineLoc, &blackOutline, SHADER_UNIFORM_INT); //black
    }else{
         SetShaderValue(shaders.outlineShader, useWhiteOutlineLoc, &whiteOutline, SHADER_UNIFORM_INT);
    }


    ///update glowShader
    float time = GetTime();  // Get the total elapsed time
    float minThreshold = 0.1f;
    float maxThreshold = 0.4f;
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

    SetShaderValue(shaders.oldFilmShader, timeLoc2, &time, SHADER_UNIFORM_FLOAT);

    
}


