#include "Grenade.h"
#include "SoundManager.h"
#include "GameResources.h"
#include "Player.h"
#include "Globals.h"
#include "NPC.h"
#include <iostream>


// Define the global grenade vector
std::vector<Grenade> grenades;

Emitter exEmitter;
Emitter smokeEmitter;

float showCircleTImer = 0.0;
float showCircle = true;
bool canSpawnSmoke = true;
float smokeTimer = 0.0;
// Constructor: Initialize grenade position and velocity
Grenade::Grenade(Vector2 pos, Vector2 vel) {
    position = pos;
    velocity = vel;
}

// Update grenade movement and explosion timer
void Grenade::Update(float deltaTime) {
    if (isActive){
        exEmitter.UpdateParticles(GetFrameTime());
        smokeEmitter.UpdateParticles(GetFrameTime());
        if (exploded && explosionTimer > 0){
            explosionTimer -= GetFrameTime();
        }else if (exploded && explosionTimer <= 0){
            isActive = false;
        }
        if (!exploded) {
            // Apply gravity
            velocity.y += gravity * deltaTime;

            // Update position
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;

            // Check for ground collision (basic floor detection)
            if (position.y >= 750.0f) { // Example ground level
                position.y = 750.0f; // Keep it on ground level
            
                if (!hasBounced) {
                    velocity.y *= -0.5f; // Bounce effect (lose velocity)
                    velocity.x *= 0.5f;  // Reduce horizontal speed
                    //hasBounced = true; // Only allow one bounce
                } else {
                    //Explode(); // If already bounced, explode
                }
            }

            // Update animation timer
            frameTimer += deltaTime;
            if (frameTimer >= frameSpeed) {
                frameTimer -= frameSpeed;
                currentFrame++;
                if (currentFrame >= maxFrames) {
                    currentFrame = 0; // Loop animation
                }
            }

            // Countdown to explosion
            lifetime -= deltaTime;
            if (lifetime <= 0.0f) {
                Explode();
            }

            Rectangle grenadeHitbox = { position.x-16, position.y-16, 16, 16 }; // Small hitbox
            Rectangle playerHitbox = { player.position.x, player.position.y, player.size.x, player.size.y }; 

            if (CheckCollisionRecs(grenadeHitbox, playerHitbox)) {  
                //Explode(); // Immediate explosion explode on hit
            }

            if (smokeTimer > 0){
                smokeTimer -= GetFrameTime();
            }else{
                canSpawnSmoke = true;
            }

            


        }
    }
}

// Handle grenade explosion
void Grenade::Explode() {
    if (!exploded && isActive) {
        exploded = true;
        explosionTimer = 0.9;
        
        exEmitter.position = position;
        exEmitter.SpawnExplosion(50, YELLOW);
        
        PlaySound(SoundManager::getInstance().GetSound("explosion"));
        Vector2 centerPos = {player.position.x + 24, player.position.y + 24}; //center the hit circle on player
        if (CheckCollisionCircles(position, explosionRadius, centerPos, 32)) {
            player.take_damage(30);
            
            
        }

        //lab scientists
        for (NPC& scientist : scientists){
            Vector2 centerPos = {scientist.position.x + 24, scientist.position.y + 24};
            if (CheckCollisionCircles(position, explosionRadius, centerPos, 32)) {
                if (scientist.isActive) scientist.TakeDamage(100);
                
            }

        }



        for (NPC& zombie : zombies){
            Vector2 centerPos = {zombie.position.x + 24,zombie.position.y + 24};
            if (CheckCollisionCircles(position, explosionRadius, centerPos, 32)) {
                if (zombie.isActive) zombie.TakeDamage(100);

            }

        }

        for (NPC& czom : cyberZombies){ //damage self
            Vector2 centerPos = {czom.position.x + 24, czom.position.y + 24};
            if (CheckCollisionCircles(position, explosionRadius, centerPos, 32)) {
                if (czom.isActive) czom.TakeDamage(100);
                
            }

        }

        for (NPC& robot : robots){ //necrotech security robot
            Vector2 centerPos = {robot.position.x + 24, robot.position.y + 24};
            if (CheckCollisionCircles(position, explosionRadius, centerPos, 32)) {
                if (robot.isActive) robot.TakeDamage(100);
                
            }

        }

        
    }
}

// Draw the grenade
void Grenade::Draw() {
    if (isActive){
        
        if (canSpawnSmoke){
            canSpawnSmoke = false;
            smokeEmitter.SpawnBlood(50, WHITE, !facingRight); //smoke not working
            smokeTimer = 1.0f;
        }
        
        if (!exploded) {
            facingRight = (velocity.x > 0);
            
            float frameWidth = 64;
            float frameHeight = 64;
            Rectangle sourceRect = { currentFrame * frameWidth, 0, frameWidth, frameHeight };
            Rectangle destRect = { position.x-16, position.y-16, 32, 32 };
            DrawTexturePro(resources.grenadeSheet, sourceRect, destRect, { 0, 0 }, 0.0f, WHITE);
            //DrawRectangle(position.x-16, position.y-16, 16, 16, RED);
            smokeEmitter.DrawParticles();
        } else {
            exEmitter.DrawParticles();
            if (showCircle){
                showCircle = false;
                showCircleTImer = .1;
                
                
            }
            if (showCircleTImer > 0){
                showCircleTImer -= GetFrameTime();
                //DrawCircle(position.x, position.y, explosionRadius, Fade(RED, 0.5f));
                DrawCircleLines(position.x, position.y, explosionRadius, Fade(RED, 1.0f));
            }else{
                showCircle = true;
            }
            
            
        }

    }

}

