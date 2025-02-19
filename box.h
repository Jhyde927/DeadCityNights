#ifndef BOX_H
#define BOX_H


#include "GameResources.h"
#include <raylib.h>
#include "Particle.h"
#include "SoundManager.h"
#include "Pickup.h"
#include <iostream>
#include "Inventory.h"



class Box {
public:
    Vector2 position;
    GameState scene; //store which scene the box belongs to. 
    bool destroyed = false;
    bool canTakeDamage = true;
    int health = 4;  // Number of hits before breaking, 
    Texture2D texture;
    int frameWidth = 32;  // Width of each frame
    int frameHeight = 32; // Height of each frame
    int maxFrames = 4;    // Number of frames in the sprite sheet, it's actualy 5, but we dont use the last frame because we lowered health by 1
    float cooldownTimer = 0.0;
    float damageCooldown = 0.2f;

    Emitter boxEmitter; //each box has it's own emitter

    // ✅ **Add a Default Constructor**
    Box() = default;

    Box(Vector2 pos, Texture2D tex, GameState sceneType){
        position = pos;
        texture = tex;
        scene = sceneType;
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
        //still draw the last frame of the box even after it's destroyed. 
        int currentFrame = maxFrames - health;  // Calculate frame based on remaining health
        if (currentFrame >= maxFrames) currentFrame = maxFrames - 1; // Clamp to last frame
        
        Rectangle sourceRect = { (float)(currentFrame * frameWidth), 0, (float)frameWidth, (float)frameHeight };
        Rectangle destRect = { position.x, position.y, 24, 24 };
        Vector2 origin = { 0, 0 };

        DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
        if (!destroyed){
            boxEmitter.DrawParticles();
        }
        
            
        
    }

    void TakeDamage(int damage) {
        if (canTakeDamage && !destroyed) {  // Only take damage if allowed
            health -= damage;
            canTakeDamage = false;
            cooldownTimer = damageCooldown; // Start cooldown timer
            boxEmitter.position = position+ Vector2 {8, 8};
            boxEmitter.SpawnExplosion(10, BROWN);
            PlaySound(SoundManager::getInstance().GetSound("woodBreak"));
            Vector2 center_pos = {position.x - 8, position.y};
            if (health <= 0) {
                destroyed = true;
                int number = rand()%4; // 0,1,2,3
                switch (number)
                {
                
                case 0:
                    SpawnPickup(center_pos, PickupType::REVOLVER_AMMO, resources.special38);
                    break;
                case 1:
                    SpawnPickup(center_pos, PickupType::SHOTGUN_AMMO, resources.shellsPickup);
                    break;

                case 2:
                    SpawnPickup(center_pos, PickupType::NINE_MM_AMMO, resources.autoPickup);
                    break;

                case 3:
                    SpawnPickup(center_pos, PickupType::MONEY, resources.money);
                    break;
                
                }
                
            }
        }
    }

};

#endif
