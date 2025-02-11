#ifndef BOX_H
#define BOX_H

#include <raylib.h>
#include "Particle.h"
#include "SoundManager.h"



class Box {
public:
    Vector2 position;
    bool destroyed = false;
    bool canTakeDamage = true;
    int health = 5;  // Number of hits before breaking (5 frames, breaks after 4 hits)
    Texture2D texture;
    int frameWidth = 32;  // Width of each frame
    int frameHeight = 32; // Height of each frame
    int maxFrames = 5;    // Number of frames in the sprite sheet
    float cooldownTimer = 0.0;
    float damageCooldown = 0.2f;

    Emitter boxEmitter; // Now each box has its own emitter

    

    Box(Vector2 pos, Texture2D tex){
        position = pos;
        texture = tex;
    }

    void Update(float deltaTime) {
        // Reduce cooldown timer
        boxEmitter.UpdateParticles(deltaTime);

        if (!canTakeDamage) {
            cooldownTimer -= deltaTime;
            if (cooldownTimer <= 0.0f) {
                canTakeDamage = true;
            }
        }
    } 

    void Draw() {
        if (!destroyed) {
            int currentFrame = maxFrames - health;  // Calculate frame based on remaining health
            if (currentFrame >= maxFrames) currentFrame = maxFrames - 1; // Clamp to last frame
            
            Rectangle sourceRect = { (float)(currentFrame * frameWidth), 0, (float)frameWidth, (float)frameHeight };
            Rectangle destRect = { position.x, position.y, 24, 24 };
            Vector2 origin = { 0, 0 };

            DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
            boxEmitter.DrawParticles();
            
        }
    }

    void TakeDamage(int damage) {
        if (canTakeDamage && !destroyed) {  // Only take damage if allowed
            health -= damage;
            canTakeDamage = false;
            cooldownTimer = damageCooldown; // Start cooldown timer
            boxEmitter.position = position;
            boxEmitter.SpawnExplosion(10, BROWN);
            PlaySound(SoundManager::getInstance().GetSound("woodBreak"));
            if (health <= 0) {
                destroyed = true;
            }
        }
    }

};

#endif
