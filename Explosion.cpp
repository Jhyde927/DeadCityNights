#include "Explosion.h"

void Explosion::Start(Vector2 pos, Texture2D* tex) {
    position = pos;
    isActive = true;
    currentFrame = 0;
    timeSinceLastFrame = 0.0f;
    spriteSheet = tex;
    remainingLife = postAnimLifetime;
    Vector2 offset = {pos.x+28, pos.y+28};
    emitter = Emitter(offset);
    emitter.SetMaxParticles(50);
    emitter.SpawnExplosion(50, ORANGE);
    
    
}

void Explosion::Update(float deltaTime) {
    if (!isActive) return;

    timeSinceLastFrame += deltaTime;
    if (timeSinceLastFrame >= frameTime) {
        timeSinceLastFrame = 0.0f;
        currentFrame++;

        if (currentFrame >= maxFrames) {
            currentFrame = maxFrames - 1; // stay on last (possibly empty) frame
            remainingLife -= deltaTime;
            if (remainingLife <= 0.0f) {
                isActive = false; //after they are flagged inactive, they are erased from the vector in updateExplosions()
            }
        } else {
            timeSinceLastFrame += deltaTime;
            if (timeSinceLastFrame >= frameTime) {
                timeSinceLastFrame = 0.0f;
                currentFrame++;
            }
        }
        
    }

    emitter.UpdateParticles(deltaTime);
}

void Explosion::Draw() const {
    if (!isActive) return;

    if (spriteSheet) {
        Rectangle srcRect = { currentFrame * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameHeight) };
        DrawTextureRec(*spriteSheet, srcRect, position, WHITE);
    }

    emitter.DrawParticles();
}
