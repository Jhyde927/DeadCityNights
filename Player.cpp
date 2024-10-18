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

    velocity = {0.0f, 0.0f};
    gravity = 800.0f;    
    isOnGround = true;
    jumpForce = 200.0f;  
    maxSpeedX = 50;
    maxSpeedY = 1000;
    acceleration = 800;
    deceleration = 600;
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
    hasShovel = false;
    hasBadge = false;
    enter_car = false;
    can_take_damage = true;

    shells = 25;

    LastTapTimeLeft = 0;
    LastTapTimeRight = 0;
    tapInterval = 0.3;
    
    runFrameSpeed = 1.5;
    walkFrameSpeed = 1;
    bulletCount = 6;
    revolverBulletCount = 6;
    shotgunBulletCount = 2;  // For Shotgun
    shotgunReloadTime = 0.7f;  // Reload time for Shotgun
    currentWeapon = REVOLVER;  // Start with Revolver


}



void Player::take_damage(int damage) {
    
    if (!enter_car){ //dont take damage if inside car

        if (can_take_damage && !isDead){
            hitTimer = 0.9f; // tint the sprite red for .3 seconds
            can_take_damage = false;
            currentHealth -= damage;

            if (rand() % 2 == 0){
                PlaySound(SoundManager::getInstance().GetSound("phit1"));

            }else{
                PlaySound(SoundManager::getInstance().GetSound("phit2"));
            }
        }
        
        if (currentHealth <= 0) {

            // Handle player death, like resetting position to apartment
            // Handled elsewhere
        }
    }

}


float GetRightBoundary(GameState gameState){
    if (gameState == OUTSIDE){
        return 4000.0f;
    }else if (gameState == CEMETERY){
        return 4000;
    }else if (gameState == LOT){
        return 3214;
    }else if (gameState == GRAVEYARD){
        return 4563;
    }else if (gameState == APARTMENT){
        return 4000;
    }else if (gameState == WORK){
        return 4000;
    }else if (gameState == ASTRAL){
        return 3550;
    }
}

float GetLeftBoundary(GameState gameState){
    if (gameState == OUTSIDE){
        return 1064;
    }else if (gameState == CEMETERY){
        return 1700;
    }else if (gameState == LOT){
        return 2218;
    }else if (gameState == GRAVEYARD){
        return 1500;
    }else if (gameState == APARTMENT){
        return 1064;
    }else if (gameState == WORK){
        return 1064;

    }else if (gameState == ASTRAL){
        return 1064;
    }
}

void Player::HandleInput(float speed){
        double currentTime = GetTime();
        float deltaTime = GetFrameTime();
        // Double tap to run (for A, D, LEFT, RIGHT)
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            if (currentTime - LastTapTimeLeft < tapInterval) {
                isRunning = true;  // Double-tap detected, start running
            }
            LastTapTimeLeft = currentTime;  // Update last tap time
        }

        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            if (currentTime - LastTapTimeRight < tapInterval) {
                isRunning = true;  // Double-tap detected, start running
            }
            LastTapTimeRight = currentTime;  // Update last tap time
        }
        
        // Movement logic
        // if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        //     position.x += speed * deltaTime;
        //     isMoving = true;
        //     facingRight = true;
        // }
        // if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        //     position.x -= speed * deltaTime;
        //     isMoving = true;
        //     facingRight = false;
        // }

        // Horizontal movement with acceleration
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            velocity.x += acceleration * deltaTime;
            if (velocity.x > maxSpeedX) velocity.x = maxSpeedX;
            isMoving = true;
            facingRight = true;
        }
        else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            velocity.x -= acceleration * deltaTime;
            if (velocity.x < -maxSpeedX) velocity.x = -maxSpeedX;
            isMoving = true;
            facingRight = false;
        }
        else {
            // Apply deceleration when no input is detected
            if (velocity.x > 0.0f) {
                velocity.x -= deceleration * deltaTime;
                if (velocity.x < 0.0f) velocity.x = 0.0f;
            } else if (velocity.x < 0.0f) {
                velocity.x += deceleration * deltaTime;
                if (velocity.x > 0.0f) velocity.x = 0.0f;
            }
        }
        
        // Jumping logic
        if (IsKeyPressed(KEY_SPACE) && isOnGround) {
            velocity.y = -jumpForce;  // Negative because y increases downward
            isOnGround = false;
        }
  
        // Check for shift key to run
        if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && !isAiming) {
            isRunning = true;
        } else if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && !isAiming) {
            isRunning = false;  // Stop running if no movement keys are pressed
        }

        //change facing direction while stopped. 
        if (isAiming && !isReloading) {
            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
                facingRight = true;
            }
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
                facingRight = false;
            }
        }
}

void Player::UpdateMovement(const GameResources& resources,  GameState& gameState, Vector2& mousePosition, Camera2D& camera) {
    isMoving = false;
    float deltaTime = GetFrameTime();
    if (IsKeyPressed(KEY_ONE)) {
        currentWeapon = REVOLVER;
    } else if (IsKeyPressed(KEY_TWO)) {
        currentWeapon = SHOTGUN;
    }

    // Apply gravity if the player is not on the ground
    if (!isOnGround) {
        velocity.y += gravity * deltaTime;
    } else {
        velocity.y = 0.0f;  // Ensure vertical velocity is zero when on the ground
    }

    // Clamp horizontal velocity
    if (velocity.x > maxSpeedX) {
        velocity.x = maxSpeedX;
    } else if (velocity.x < -maxSpeedX) {
        velocity.x = -maxSpeedX;
    }

    // Clamp vertical velocity (for downward movement)
    if (velocity.y > maxSpeedY) {
        velocity.y = maxSpeedY;
    } else if (velocity.y < -maxSpeedY) {
        velocity.y = -maxSpeedY;
    }

    // Update player position based on velocity
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // Collision detection with the ground (assuming ground at y = groundLevel)
    float groundLevel = 700.0f;  // Adjust based on your game's ground position

    if (position.y >= groundLevel) {
        position.y = groundLevel;
        isOnGround = true;
        velocity.y = 0.0f;

    }

    if (IsKeyPressed(KEY_R) && (gameState == CEMETERY || gameState == GRAVEYARD || gameState == ASTRAL)){
        //RefillBullets(player, (MAX_BULLETS - player.bulletCount));
        if (currentWeapon == REVOLVER){
            if (!isReloading){
                isReloading = true;    
                reloadTimer = 0.5f;
                revolverBulletCount = 6;
                bulletCount = MAX_BULLETS;
                PlaySound(SoundManager::getInstance().GetSound("reload"));

            }
         

        }else if (currentWeapon == SHOTGUN && shotgunBulletCount == 0){
            if (!isReloading && shotgunBulletCount + shells >= 1){
                if (shells == 1){
                    shells -= 1;
                    shotgunBulletCount = 1;
                }else{
                    shells -= 2;
                    shotgunBulletCount = 2;

                }

                isReloading = true;
                shotgunReloadTime = 0.7f;
 
                //shotgunBulletCount = 2;
                bulletCount = MAX_BULLETS;//shotgun uses same bullets array
                PlaySound(SoundManager::getInstance().GetSound("ShotgunReload"));

            }

        }

    }
    ///////////RELOAD//LOGIC///////////////
    if (reloadTimer > 0){
        
        reloadTimer -= deltaTime;
        isReloading = true;
        canShoot = false;
        isAiming = false;
    }else{
        //isReloading = false;
        canShoot = true;
    }

    if (shotgunReloadTime > 0){
        shotgunReloadTime -= deltaTime;
        isReloading = true;
        canShoot = false;
        isAiming = false;
    }else{
        //isReloading = false;
        canShoot = true;
    }

    //AIMING
    isAiming = (hasGun || hasShotgun) && (IsKeyDown(KEY_F) || IsKeyDown(KEY_LEFT_CONTROL) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) && !isShooting && !isReloading && (gameState == CEMETERY || gameState == GRAVEYARD || gameState == ASTRAL);

    if (currentWeapon == REVOLVER && (gameState == CEMETERY || gameState == GRAVEYARD || gameState == ASTRAL)){

        if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && revolverBulletCount <= 0){
            //SoundManager::getInstance().GetSound("dryFire");
            PlaySound(SoundManager::getInstance().GetSound("dryFire"));

        }

    
        if (hasGun && revolverBulletCount > 0 && isAiming && (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
            isShooting = true;
            canShoot = false;
            currentFrame = 0;
            frameCounter = 0.0f;
            revolverBulletCount--;
            //SoundManager::getInstance().GetSound("gunShot");  // Access the sound directly
            PlaySound(SoundManager::getInstance().GetSound("gunShot")); 

            FireBullet(*this, false);
            
        }
    }else if (currentWeapon == SHOTGUN && (gameState == CEMETERY || gameState == GRAVEYARD || gameState == ASTRAL)){
        if ((IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && shotgunBulletCount <= 0){
            //SoundManager::getInstance().GetSound("dryFire");
            PlaySound(SoundManager::getInstance().GetSound("dryFire"));

        }


        if (hasShotgun && shotgunBulletCount > 0 && isAiming && (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && canShoot) {
            isShooting = true;
            canShoot = false;
            currentFrame = 0;
            frameCounter = 0.0f;
            shotgunBulletCount--;

            PlaySound(SoundManager::getInstance().GetSound("ShotGun"));
            // Shotgun fires multiple bullets (spread effect)
            for (int i = 0; i < 3; i++) {  // Simulate shotgun spread with 3 bullets
                FireBullet(*this, true);  // Modify FireBullet to allow spread by adjusting directions

            }

        }
    }       

    maxSpeedX = isRunning ? runSpeed : walkSpeed;
    frameSpeed = isRunning ? runFrameSpeed : walkFrameSpeed;

    //keep player in bounds

    if (position.x < GetLeftBoundary(gameState)){
        position.x = GetLeftBoundary(gameState) + 1;
    }else if (position.x > GetRightBoundary(gameState)){
        position.x = GetRightBoundary(gameState)-1;
    }

 
    if (!isAiming && !isShooting && !isReloading) {
        //KEYBOARD MOVEMENT CODE
        HandleInput(maxSpeedX);
    
    }

    if (isShooting) {
        isRunning = false; // fixed bug where isrunning was causing framespeed to be higher so you could shoot 1.5 times as fast. 
        frameCounter += GetFrameTime() * frameSpeed;
        int numFrames = (resources.shootSheet.width / 64);

        if (frameCounter >= 0.1) { //update frames
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
        frameSpeed = 1; //ensure framespeed isn't 1.5 because of running
        frameCounter += GetFrameTime() * frameSpeed;
        int numFrames = (resources.reloadSheet.width/ 64);
        if (frameCounter >= 0.1) {
            currentFrame++;
            frameCounter = 0;
            

            if (currentFrame >= numFrames) {
                currentFrame = 0;
                isShooting = false;
                isAiming = true;
                isReloading = false; //reload animation is done reset isreloading what if reload time is still going?
                reloadTimer = 0; //reloadTimer doesn't match the actual reload speed, so set it to 0 here. 
                shotgunReloadTime = 0; // setting timer to 0 here seemed to fix the reload anim playing twice.  
                canShoot = true;
            }
        }
    } else if (isMoving) {
        frameCounter += GetFrameTime() * frameSpeed;
        int numFrames = (maxSpeedX == runSpeed) ? (resources.runSheet.width / 64) : (resources.walkSheet.width / 64);

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
    
        if (hasGun && isShooting && (gameState == CEMETERY || gameState == GRAVEYARD || gameState == ASTRAL)) { //need a way to allow guns outside cemetery at a certain point in the game. 
            currentSheet = resources.shootSheet;
            sourceRec = { static_cast<float>(currentFrame * frameWidth), 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }else if (hasGun && isReloading && (gameState == CEMETERY || gameState == GRAVEYARD || gameState == ASTRAL)){
        
            currentSheet = resources.reloadSheet;
            sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }else if (hasGun && isAiming && !isReloading && (gameState == CEMETERY || gameState == GRAVEYARD || gameState == ASTRAL)) {
            // Aiming but not shooting: use the first frame of the shootSheet
            currentSheet = resources.shootSheet;
            sourceRec = { 0, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };  // First frame for aiming

        } else if (isMoving) {
            // Walking or running animation
            currentSheet = isRunning ? resources.runSheet : resources.walkSheet;  // Use runSheet if running, else walkSheet
            sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };
        } else {
            // Idle pose
            currentSheet = resources.manTexture;  // Idle pose
            sourceRec = { 0, 0, static_cast<float>(currentSheet.width), static_cast<float>(currentSheet.height) };
        }



    /////////////////shotgun//////////////
    }else if (currentWeapon == SHOTGUN){
        
         if (hasShotgun && isShooting && (gameState == CEMETERY || gameState == GRAVEYARD || gameState == ASTRAL)){
            currentSheet = resources.ShotGunSheet;
            sourceRec = {static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        } else if (hasShotgun && isReloading && (gameState == CEMETERY || gameState == GRAVEYARD || gameState == ASTRAL)){
            currentSheet = resources.ShotgunReload;
            sourceRec = {static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }else if (hasShotgun && isAiming && !isReloading && (gameState == CEMETERY || gameState == GRAVEYARD || gameState == ASTRAL)) {
            // Aiming but not shooting: use the first frame of the shootSheet
            currentSheet = resources.ShotGunSheet;
            sourceRec = { 0, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth)};  // First frame for aiming

        } else if (isMoving) {
            // Walking or running animation
            currentSheet = isRunning ? resources.runSheet : resources.walkSheet;  // Use runSheet if running, else walkSheet
            sourceRec = {static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };
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


