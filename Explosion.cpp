#include "Explosion.h"
#include "NPC.h"
#include "Globals.h"

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
    
    //AOE damage on zombies. not the player though. 
    for (NPC& zombie : zombies){ //maybe loop through all NPCs? so even pedestrians are damaged by fireballs. 
        float hitboxWidth = 8.0f;
        float hitboxHeight = 32.0f; 
    
        // Offset the hitbox so it's centered on the zombie's position
        Rectangle npcHitbox = {
            zombie.position.x + 32-4,   
            zombie.position.y + 16,  
            hitboxWidth,                    
            hitboxHeight                   
        };

        if (CheckCollisionCircleRec(offset, radius, npcHitbox)){
            zombie.TakeDamage(100);
            
        }
    }
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
