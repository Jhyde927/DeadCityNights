#include "Bullet.h"
#include "Globals.h"
#include "Player.h"
#include "NPC.h"
#include <raylib.h>
#include <cstdlib>
#include <raymath.h>
#include <cmath>
#include "GameResources.h"
#include"Particle.h"
#include <iostream>
#include "SoundManager.h"
#include "Explosion.h"


Bullet bullets[MAX_BULLETS];  // Define the global bullets array




Vector2 RotateTowards(Vector2 current, Vector2 target, float maxAngle) {
    float angle = atan2f(target.y, target.x) - atan2f(current.y, current.x);

    // Clamp the angle
    if (angle > PI) angle -= 2 * PI;
    if (angle < -PI) angle += 2 * PI;
    angle = Clamp(angle, -maxAngle, maxAngle);

    float currentAngle = atan2f(current.y, current.x) + angle;
    return Vector2Normalize(Vector2{ cosf(currentAngle), sinf(currentAngle) });
}


// Function to add spread to a bullet's direction
Vector2 ApplySpread(Vector2 direction, float spreadAngle) {
    // Convert the direction vector to an angle in radians
    float baseAngle = atan2f(direction.y, direction.x);

    // Generate a random angle offset for the spread, in radians
    float angleOffset = (rand() / (float)RAND_MAX) * spreadAngle - (spreadAngle / 2.0f);

    // Add the spread offset to the base angle
    float finalAngle = baseAngle + angleOffset;

    // Convert the angle back to a direction vector
    Vector2 spreadDirection = { cosf(finalAngle), sinf(finalAngle) };

    return spreadDirection;
}

void ResetBullet(Bullet& bullet) {
    bullet.isActive = false;
    bullet.hitNPCs.clear();  // Clear the hit NPCs so the bullet can work correctly next time
}


void FireBullet(Player& player, bool spread, float damage, bool laser, bool raygun) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].isActive) {
            bullets[i].isFireball = false;
            bullets[i].position = Vector2{player.position.x + 32, player.position.y + 23};  // Adjust bullet position to match player
            bullets[i].direction = player.facingRight ? Vector2{1, 0} : Vector2{-1, 0};    // Set direction based on player facing
            bullets[i].damage = damage; //take different damage for different guns
            bullets[i].speed = 1000.0f;  // Set bullet speed
            bullets[i].lifeTime = 1.0f;  // Bullet will last for 2 seconds
            bullets[i].isActive = true;
            bullets[i].canExplode = true;
            bullets[i].laser = laser;
            bullets[i].raygun = raygun;
            bullets[i].health = 1; //default health
            bullets[i].size = Vector2 {1, 1}; //default bullet size. 
            player.bulletCount--;  // Decrease player's bullet count

            if (spread){ //shotgun spread
                bullets[i].direction = ApplySpread(bullets[i].direction, 2);
                bullets[i].position.y += rand() % 4;
            }

            if (raygun){ //Charging up the raygun increases it's damage, we use this value to determine the size of the bullet. and health.
                bullets[i].speed = 300;
                bullets[i].health = 1;
                bullets[i].lifeTime = 3;
                //change the size of bullets depending on damage, in check hit make sure your getting bullets[i].size
                if (damage >= 100){
                    bullets[i].size = Vector2 {10, 10}; // the hitbox is square, unlike the projectile
                    bullets[i].health = 4; //kill up to 4 zombies in a row. 
                } 
                
                if (damage == 50){
                    bullets[i].size = Vector2 {5, 5}; // needs more testing, make it OP?
                    bullets[i].health = 4;
                } 
                if (damage == 30){
                    bullets[i].size = Vector2 {3, 3};
                    bullets[i].health = 3;
                } 
                if (damage == 10){
                    bullets[i].size = Vector2 {1, 1};
                    bullets[i].health = 1;
                } 


            } 

            break;  // Use the first available (inactive) bullet
        }
    }
}

void NPCfireBullet(NPC& npc, bool spread, float damage, bool laser, bool fireBall) { //robots shoot lasers
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].isActive) {
            bullets[i].position = Vector2{npc.position.x + 32, npc.position.y + 26};

            bullets[i].damage = damage;
            bullets[i].speed = fireBall ? 300.0f : 1000.0f;
            bullets[i].lifeTime = fireBall ? 2.0f : 1.0f;
            bullets[i].isActive = true;
            bullets[i].laser = laser;
            bullets[i].isFireball = fireBall;
            bullets[i].size = fireBall ? Vector2{8, 8} : Vector2{1, 1};
            
            if (fireBall) {
                
                Vector2 target = player.position;
                target.y += 32; // offset to aim lower
                bullets[i].direction = Vector2Normalize(Vector2Subtract(target, bullets[i].position));
            } else {
                bullets[i].direction = npc.facingRight ? Vector2{1, 0} : Vector2{-1, 0};
                if (spread) {
                    bullets[i].direction = ApplySpread(bullets[i].direction, 2);
                    bullets[i].position.y += rand() % 4;
                }
            }

            break; //use first inactive bullet
            
        }
    }
}



void UpdateBullets() {

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            bullets[i].previousPosition = bullets[i].position; //save the bullets previous position for better hit detection. 
            // Update bullet position based on direction and speed
            bullets[i].position.x += bullets[i].direction.x * bullets[i].speed * GetFrameTime();     
            if (bullets[i].isFireball) bullets[i].position.y += bullets[i].direction.y * bullets[i].speed * GetFrameTime(); //y axis for fireballs. 
            bullets[i].lifeTime -= GetFrameTime();  // Reduce bullet's lifetime

            if (bullets[i].isFireball) {
                Vector2 target = player.position;
                target.y += 32;
                Vector2 desiredDir = Vector2Normalize(Vector2Subtract(target, bullets[i].position));
            
                float maxTurn = 0.01f; // Radians per frame (~2.8°)
                bullets[i].direction = RotateTowards(bullets[i].direction, desiredDir, maxTurn);
            
                //update fireball animation, drawn in drawBullets
                bullets[i].frameTimer += GetFrameTime(); 
            
                if (bullets[i].frameTimer >= bullets[i].frameTime) {
                    bullets[i].frameTimer = 0.0f;
                    bullets[i].currentFrame++;
            
                    if (bullets[i].currentFrame >= bullets[i].maxFrames) {
                        bullets[i].currentFrame = 0;
                    }
                }
            }

            // Deactivate the bullet if it goes off-screen or its lifetime runs out
            if (bullets[i].position.x < -100 || bullets[i].position.x > 7000 || bullets[i].lifeTime <= 0 || bullets[i].health < 0) {
                //bullets[i].isActive = false;
                ResetBullet(bullets[i]);
            }



        }
    }
}

void DrawRaygunProjectile(Bullet& bullet, Texture2D spriteSheet, float deltaTime) {
    bullet.frameTimer += deltaTime;
    bullet.maxFrames = 7;

    if (bullet.frameTimer >= bullet.frameTime) {
        bullet.frameTimer = 0.0f;
        bullet.currentFrame = (bullet.currentFrame + 1) % bullet.maxFrames;
    }

    float frameWidth = 64.0f;
    float frameHeight = 64.0f;

    float scale = 0.25f;
    if (bullet.damage == 30) scale = 0.4f;
    else if (bullet.damage == 50) scale = 0.6f;
    else if (bullet.damage == 100) scale = 0.8f;

    Rectangle sourceRect = {
        bullet.currentFrame * frameWidth, 0,
        frameWidth, frameHeight
    };

    float destSize = frameWidth * scale;
    Rectangle destRect = {
        bullet.position.x - destSize / 2,
        bullet.position.y - destSize / 2,
        destSize, destSize
    };

    DrawTexturePro(spriteSheet, sourceRect, destRect, {0, 0}, 0.0f, WHITE);
}



void DrawBullets() {
    explosionEmitter.DrawParticles();

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            if (bullets[i].laser && !bullets[i].isFireball){
                DrawRectangleV(bullets[i].position, Vector2 {5, 2}, RED); // Draw laser as a wide rectangle

            }else if (bullets[i].isFireball && bullets[i].laser){ //fireball is also a laser for collision purposes. 
                DrawCircleV(bullets[i].position, 8, RED);
                float frameWidth = 64;
                float frameHeight = 64;
               
                Rectangle sourceRect = { bullets[i].currentFrame * frameWidth, 0, frameWidth, frameHeight };
                Rectangle destRect = { bullets[i].position.x-16, bullets[i].position.y-16, 32, 32};
                DrawTexturePro(resources.fireballSheet, sourceRect, destRect, { 0, 0 }, 0.0f, WHITE);

            } else if (bullets[i].raygun) {
                DrawRaygunProjectile(bullets[i], resources.energyBallSheet, GetFrameTime());
            
            }else{
                DrawCircleV(bullets[i].position, 1, WHITE);
            }
        }
    }
}

