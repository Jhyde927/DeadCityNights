// Player.cpp
#include "Player.h"
#include <iostream>
#include "GameResources.h"
#include <raylib.h>
#include "Bullet.h"
#include "GameEnums.h"
#include "SoundManager.h"


WeaponType currentWeapon;  // To track the current weapon
int shotgunBulletCount;
float shotgunReloadTime;

bool step = false;

Player::Player() {
    position = {1922.0, 700.0};
    walkSpeed = 50.0f;
    runSpeed = 100.0f;
    maxHealth = 100;
    currentHealth = maxHealth;
    hitTimer = 0.0f;
    reloadTimer = 0.0f;
    currentFrame = 0;
    frameCounter = 0.0f;
    frameSpeed = 12.0f;
    isDead = false;
    isMoving = false;
    facingRight = true;
    isRunning = false;
    isAiming = false;
    isShooting = false;
    isReloading = false;
    canShoot = true;
    hasGun = false;
    hasShotgun = false;
    enter_car = false;
    can_take_damage = true;

    LastTapTimeLeft = 0;
    LastTapTimeRight = 0;
    tapInterval = 0.3;
    
    runFrameSpeed = 1.5;
    walkFrameSpeed = 1;
    bulletCount = 6;
    revolverBulletCount = 6;
    shotgunBulletCount = 2;  // For Shotgun
    shotgunReloadTime = 2.0f;  // Reload time for Shotgun
    currentWeapon = REVOLVER;  // Start with Revolver


}



void Player::take_damage(int damage) {
    if (!enter_car){ //dont take damage if inside car
        
        if (rand() % 2 == 0){
            PlaySound(SoundManager::getInstance().GetSound("phit1"));

        }else{
            PlaySound(SoundManager::getInstance().GetSound("phit2"));
        }

        
        if (can_take_damage){
            hitTimer = 0.9f; // tint the sprite red for .3 seconds
            can_take_damage = false;
            currentHealth -= damage;
        }
        
        if (currentHealth <= 0) {

            // Handle player death, like resetting position to apartment
            // Handled elsewhere
        }
    }

}


void Player::UpdateMovement(const GameResources& resources,  GameState& gameState, Vector2& mousePosition, Camera2D& camera) {
    isMoving = false;
    //Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);

    if (IsKeyPressed(KEY_ONE)) {
        currentWeapon = REVOLVER;
    } else if (IsKeyPressed(KEY_TWO)) {
        currentWeapon = SHOTGUN;
    }

    if (IsKeyPressed(KEY_R) && gameState == CEMETERY){
        //RefillBullets(player, (MAX_BULLETS - player.bulletCount));
        if (currentWeapon == REVOLVER){
            if (!isReloading){
                isReloading = true;    
                reloadTimer = 0.5f;
                revolverBulletCount = 6;
                bulletCount = MAX_BULLETS;
                PlaySound(SoundManager::getInstance().GetSound("reload"));

            }
         

        }else if (currentWeapon == SHOTGUN && shotgunBulletCount < 2){
            if (!isReloading){
                isReloading = true;
                shotgunReloadTime = 0.7f;
                shotgunBulletCount = 2;
                bulletCount = MAX_BULLETS;//shotgun uses same bullets array
                PlaySound(SoundManager::getInstance().GetSound("ShotgunReload"));

            }

        }

        //PlaySound(reload);
    }
    ///////////RELOAD//LOGIC///////////////
    if (reloadTimer > 0){
        
        reloadTimer -= GetFrameTime();
        isReloading = true;
        canShoot = false;
        isAiming = false;
    }else{
        //isReloading = false;
        canShoot = true;
    }

    if (shotgunReloadTime > 0){
        shotgunReloadTime -= GetFrameTime();
        isReloading = true;
        canShoot = false;
    }else{
        //isReloading = false;
        canShoot = true;
    }

    
    //isRunning = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT));


    
    isAiming = (hasGun || hasShotgun) && (IsKeyDown(KEY_F) || IsKeyDown(KEY_LEFT_CONTROL) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) && !isShooting && !isReloading;
   



    if (currentWeapon == REVOLVER){

        if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && revolverBulletCount <= 0 && gameState == CEMETERY){
            //SoundManager::getInstance().GetSound("dryFire");
            PlaySound(SoundManager::getInstance().GetSound("dryFire"));

        }

    
        if (hasGun && revolverBulletCount > 0 && isAiming && (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && canShoot && gameState == CEMETERY) {
            isShooting = true;
            canShoot = false;
            currentFrame = 0;
            frameCounter = 0.0f;
            revolverBulletCount--;
            //SoundManager::getInstance().GetSound("gunShot");  // Access the sound directly
            PlaySound(SoundManager::getInstance().GetSound("gunShot")); 

            FireBullet(*this, false);
            
        }
    }else if (currentWeapon == SHOTGUN){
        if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && shotgunBulletCount <= 0 && gameState == CEMETERY){
            //SoundManager::getInstance().GetSound("dryFire");
            PlaySound(SoundManager::getInstance().GetSound("dryFire"));

        }


        if (hasShotgun && shotgunBulletCount > 0 && isAiming && (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && canShoot && gameState == CEMETERY) {
            isShooting = true;
            canShoot = false;
            currentFrame = 0;
            frameCounter = 0.0f;
            shotgunBulletCount--;
            //SoundManager::getInstance().GetSound("shotgunBlast");
            //PlaySound(SoundManager::getInstance().GetSound("shotgunBlast"));
            PlaySound(SoundManager::getInstance().GetSound("ShotGun"));
            // Shotgun fires multiple bullets (spread effect)
            for (int i = 0; i < 3; i++) {  // Simulate shotgun spread with 5 bullets
                FireBullet(*this, true);  // Modify FireBullet to allow spread by adjusting directions

            }

        }
    }       




    float speed = isRunning ? runSpeed : walkSpeed;
    frameSpeed = isRunning ? runFrameSpeed : walkFrameSpeed;

    //keep player in bounds
    if (gameState == OUTSIDE){
        if (position.x < 1064){
            position.x = 1065;
        }else if (position.x > 4000){
            position.x = 3999;
        }

    }
    else if (gameState == CEMETERY){
        if (position.x < 1700){
            position.x = 1701;
        }else if (position.x > 4000){
            position.x = 3999;
        }
    }else if (gameState == LOT){
        if (position.x < 2218){
            position.x = 2219;
        }else if (position.x > 3214){
            position.x = 3213;
        }
    }


 
    if (!isAiming && !isShooting && !isReloading) {
        //KEYBOARD MOVEMENT CODE

        double currentTime = GetTime();

        // Double tap to run
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            if (currentTime - LastTapTimeLeft < tapInterval) {
                isRunning = true;  // Double-tap detected, start running
            }
            LastTapTimeLeft = currentTime;  // Update last tap time
        }

        
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            if (currentTime - LastTapTimeRight < tapInterval) {
                isRunning = true;  
            }
            LastTapTimeRight = currentTime;  
        }
        
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            position.x += speed * GetFrameTime();
            isMoving = true;
            facingRight = true;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            position.x -= speed * GetFrameTime();
            isMoving = true;
            facingRight = false;
        }


            // Check for shift key to run
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT) && !isAiming) {
            isRunning = true;
        } else if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !isAiming) {
            isRunning = false;  // Stop running if no movement keys are pressed
        }




    } else if (isAiming && !isReloading) {
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            facingRight = true;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            facingRight = false;
        }
    
    }

    if (isShooting) {
        isRunning = false; // fixed bug where isrunning was causing framespeed to be higher so you could shoot 1.5 times as fast. 
        frameCounter += GetFrameTime() * frameSpeed;
        int numFrames = (resources.shootSheet.width / 64);

        if (frameCounter >= 0.1) {
            currentFrame++;
            frameCounter = 0;

            if (currentFrame >= numFrames) {
                currentFrame = 0;
                isShooting = false;
                isAiming = true;
                canShoot = true;
            }
        }
    }else if (isReloading){
        frameCounter += GetFrameTime() * frameSpeed;
        int numFrames = (resources.reloadSheet.width/ 64);
        if (frameCounter >= 0.1) {
            currentFrame++;
            frameCounter = 0;
            

            if (currentFrame >= numFrames) {
                currentFrame = 0;
                isShooting = false;
                isAiming = true;
                isReloading = false;
                canShoot = true;
            }
        }
    } else if (isMoving) {
        frameCounter += GetFrameTime() * frameSpeed;
        int numFrames = (speed == runSpeed) ? (resources.runSheet.width / 64) : (resources.walkSheet.width / 64);

        if (frameCounter >= 0.1) {
            
            currentFrame++;
            frameCounter = 0;

            if (currentFrame >= numFrames) {
                currentFrame = 0;  // loop back to the first frame
                if (!step){
                    PlaySound(SoundManager::getInstance().GetSound("Step1"));
                    step = true;
                }else{
                    PlaySound(SoundManager::getInstance().GetSound("Step2"));

                }
                
            }
        }
    } else if (!isAiming) {
        currentFrame = 0;
    }
}



// Method for drawing the player
void Player::DrawPlayer(const GameResources& resources, GameState& gameState, Camera2D& camera) {
    Texture2D currentSheet;
    Rectangle sourceRec;
    int frameWidth = 64; // Assuming each frame is 64 pixels wide
    
    // Prioritize drawing states: Shooting > Aiming > Moving > Idle
    if (currentWeapon == REVOLVER){

    
        if (hasGun && isShooting && gameState == CEMETERY) { //need a way to allow guns outside cemetery at a certain point in the game. 
            currentSheet = resources.shootSheet;
            sourceRec = { static_cast<float>(currentFrame * frameWidth), 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }else if (hasGun && isReloading && gameState == CEMETERY){
        
            currentSheet = resources.reloadSheet;
            sourceRec = { currentFrame * frameWidth, 0, frameWidth, frameWidth };

        }else if (hasGun && isAiming && !isReloading && gameState == CEMETERY) {
            // Aiming but not shooting: use the first frame of the shootSheet
            currentSheet = resources.shootSheet;
            sourceRec = { 0, 0, frameWidth, frameWidth };  // First frame for aiming

        } else if (isMoving) {
            // Walking or running animation
            currentSheet = isRunning ? resources.runSheet : resources.walkSheet;  // Use runSheet if running, else walkSheet
            sourceRec = { currentFrame * frameWidth, 0, frameWidth, frameWidth };
        } else {
            // Idle pose
            currentSheet = resources.manTexture;  // Idle pose
            sourceRec = { 0, 0, static_cast<float>(currentSheet.width), static_cast<float>(currentSheet.height) };
        }



    /////////////////shotgun//////////////
    }else if (currentWeapon == SHOTGUN){
         if (hasShotgun && isShooting && gameState == CEMETERY) {
            currentSheet = resources.ShotGunSheet;
            sourceRec = { currentFrame * frameWidth, 0, frameWidth, frameWidth };

        } else if (hasShotgun && isReloading && gameState == CEMETERY){
            currentSheet = resources.ShotgunReload;
            sourceRec = { currentFrame * frameWidth, 0, frameWidth, frameWidth };

        }else if (hasShotgun && isAiming && !isReloading && gameState == CEMETERY) {
            // Aiming but not shooting: use the first frame of the shootSheet
            currentSheet = resources.ShotGunSheet;
            sourceRec = { 0, 0, frameWidth, frameWidth };  // First frame for aiming

        } else if (isMoving) {
            // Walking or running animation
            currentSheet = isRunning ? resources.runSheet : resources.walkSheet;  // Use runSheet if running, else walkSheet
            sourceRec = { currentFrame * frameWidth, 0, frameWidth, frameWidth };
        } else {
            // Idle pose
            currentSheet = resources.manTexture;  // Idle pose
            sourceRec = { 0, 0, static_cast<float>(currentSheet.width), static_cast<float>(currentSheet.height) };
        }      

    }
    


    // Adjust source rectangle for direction
    if (!facingRight) {
        sourceRec.width = -frameWidth;  // Flip the texture if facing left
    }


    
    if (hitTimer > 0){
        hitTimer -= GetFrameTime();
        
    }else{
        can_take_damage = true;
    }
    // Draw the player
    Color tint = (hitTimer > 0) ? RED : WHITE;
    Vector2 castPos = {(float) position.x, (float) position.y};
    DrawTextureRec(currentSheet, sourceRec, castPos, tint);  // Draw the player based on the current state


}


