#include "Explosion.h"

void Explosion::Start(Vector2 pos, Texture2D* tex) {
    position = pos;
    isActive = true;
    currentFrame = 0;
    frameTimer = 0.0f;
    spriteSheet = tex;
    remainingLife = postAnimLifetime;
    Vector2 offset = {pos.x+28, pos.y+28};
    emitter = Emitter(offset);
    emitter.SetMaxParticles(50);
    emitter.SpawnExplosion(50, ORANGE);
    
    
}

void Explosion::Update(float deltaTime) {
    if (!isActive) return;
    emitter.UpdateParticles(deltaTime);
    frameTimer += deltaTime;
    if (frameTimer >= frameTime) {
        frameTimer = 0.0f;
        currentFrame++;

        if (currentFrame >= maxFrames) {
            currentFrame = maxFrames - 1; // stay on last frame
            remainingLife -= deltaTime;
            if (remainingLife <= 0.0f) {
                isActive = false; //after they are flagged inactive, they are erased from the vector in updateExplosions()
            }
        } else {
            frameTimer += deltaTime;
            if (frameTimer >= frameTime) {
                frameTimer = 0.0f;
                currentFrame++;
            }
        }
        
    }

   
}

void Explosion::Draw() const {
    if (!isActive) return;
    emitter.DrawParticles();
    if (spriteSheet) {
        //Rectangle srcRect = { currentFrame * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameHeight) };
        Rectangle srcRect = {
            static_cast<float>(currentFrame) * static_cast<float>(frameWidth),
            0.0f,
            static_cast<float>(frameWidth),
            static_cast<float>(frameHeight)
        };
        
        DrawTextureRec(*spriteSheet, srcRect, position, WHITE);
    }

   
}
