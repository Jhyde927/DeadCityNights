#include "Bullet.h"
#include "Player.h"
#include "NPC.h"
#include <raylib.h>
#include <cstdlib>
#include <raymath.h>
#include <cmath>
#include "GameResources.h"


Bullet bullets[MAX_BULLETS];  // Define the global bullets array



// Function to generate a random float between 0 and 1
// float randf() {
//     return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
// }

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
            bullets[i].position = Vector2{player.position.x + 32, player.position.y + 23};  // Adjust bullet position to match player
            bullets[i].direction = player.facingRight ? Vector2{1, 0} : Vector2{-1, 0};    // Set direction based on player facing
            bullets[i].damage = damage; //take different damage for different guns
            bullets[i].speed = 1000.0f;  // Set bullet speed
            bullets[i].lifeTime = 1.0f;  // Bullet will last for 2 seconds
            bullets[i].isActive = true;
            bullets[i].laser = laser;
            bullets[i].raygun = raygun;
            bullets[i].health = 1;
            bullets[i].size = Vector2 {1, 1};
            player.bulletCount--;  // Decrease player's bullet count

            if (spread){ //shotgun spread
                bullets[i].direction = ApplySpread(bullets[i].direction, 2);
                bullets[i].position.y += rand() % 4;
            }

            if (raygun){
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

void NPCfireBullet(NPC& npc, bool spread, float damage, bool laser) { //robots shoot lasers
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].isActive) {
            bullets[i].position = Vector2{npc.position.x + 32, npc.position.y + 26}; //center bullet on Robot gun
            bullets[i].direction = npc.facingRight ? Vector2{1, 0} : Vector2{-1, 0};    
            bullets[i].damage = damage; //take different damage for different guns
            bullets[i].speed = 1000.0f;  // Set bullet speed
            bullets[i].lifeTime = 1.0f;  // Bullet will last for 2 seconds
            bullets[i].isActive = true;
            bullets[i].laser = laser;
            bullets[i].size = Vector2 {1, 1};
            //player.bulletCount--;  // Decrease player's bullet count //robots have infinite ammo
            if (spread){
                bullets[i].direction = ApplySpread(bullets[i].direction, 2);
                bullets[i].position.y += rand() % 4;
            }

            
            break;  // Use the first available (inactive) bullet
        }
    }
}

void UpdateBullets() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            bullets[i].previousPosition = bullets[i].position; //save the bullets previous position for better hit detection. 
            // Update bullet position based on direction and speed
            bullets[i].position.x += bullets[i].direction.x * bullets[i].speed * GetFrameTime();
            bullets[i].lifeTime -= GetFrameTime();  // Reduce bullet's lifetime

            // Deactivate the bullet if it goes off-screen or its lifetime runs out
            if (bullets[i].position.x < -100 || bullets[i].position.x > 7000 || bullets[i].lifeTime <= 0 || bullets[i].health < 0) {
                //bullets[i].isActive = false;
                ResetBullet(bullets[i]);
            }
        }
    }
}

void DrawBullets() {
    //BeginShaderMode(shaders.highlightShader);
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {
            if (bullets[i].laser){
                DrawRectangleV(bullets[i].position, Vector2 {5, 2}, RED); // Draw laser as a wide rectangle
            }else if (bullets[i].raygun){ //raygun bullet
                    //change the size of the projectile depending on damage.  
                if (bullets[i].damage == 10){
                    //a circle with a ring around it. Best I can do for now. 
                    DrawCircleV(bullets[i].position, 1, RED);
                    DrawCircleSectorLines(bullets[i].position, 3, 0, 360, 8, RED);
                }else if (bullets[i].damage == 30){
                    DrawCircleV(bullets[i].position, 3, RED);
                    DrawCircleSectorLines(bullets[i].position, 5, 0, 360, 8, RED);
                }else if (bullets[i].damage == 50){
                    DrawCircleV(bullets[i].position, 5, RED);
                    DrawCircleSectorLines(bullets[i].position, 10, 0, 360, 8, RED);
                }else if (bullets[i].damage == 100){
                    DrawCircleV(bullets[i].position, 10, RED);
                    DrawCircleSectorLines(bullets[i].position, 15, 0, 360, 8, RED);
                }
                
            } else{
                DrawCircleV(bullets[i].position, 1, WHITE);  // Draw each bullet as a small circle

            }
            
        }
    }

    //EndShaderMode();
}
