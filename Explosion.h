#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Particle.h"
#include <raylib.h>

struct Explosion {
    Vector2 position;
    Emitter emitter;

    float frameTime = 0.15f;
    int currentFrame = 0;
    int maxFrames = 7;
    float frameTimer = 0.0f;
    bool isActive = false;

    float postAnimLifetime = 0.5f; // How long to stay alive after animation ends, to let particles do there thing. 
    float remainingLife = 0.0f;    // Countdown timer

    float radius = 32;

    Texture2D* spriteSheet = nullptr;
    int frameWidth = 64;
    int frameHeight = 64;

    void Start(Vector2 pos, Texture2D* tex);
    void Update(float deltaTime);
    void Draw() const;
};

#endif
