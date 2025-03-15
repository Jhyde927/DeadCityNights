// Player.cpp
#include "Player.h"
#include <iostream>
#include "GameResources.h"
#include <raylib.h>
#include "Bullet.h"
#include "GameEnums.h"
#include "SoundManager.h"
#include <vector>
#include "platform.h"
#include "shaderControl.h"
#include "Globals.h"
#include "Platform.h"
#include "Particle.h"
#include <algorithm>


WeaponType currentWeapon;  // To track the current weapon

Player player;  // Define the player instance


Player::Player() {
    position = {1922.0, 700.0};
    velocity = {0.0f, 0.0f};
    size.x = 16; //hitbox size
    size.y = 32;
    gravity = 800.0f;    
    isOnGround = true;
    jumpForce = 200.0f;
    jumping = false;
    onPlatform = false;
    maxSpeedX = 50;
    maxSpeedY = 1000;
    acceleration = 800;
    deceleration = 600;
    walkSpeed = 50.0f;
    fallTimer = 0.0;
    runSpeed = 100.0f;
    maxHealth = 100;
    currentHealth = 100;
    hitTimer = 0.0f;
    reloadTimer = 0.0f;
    currentFrame = 0;
    frameCounter = 0.0f;
    frameSpeed = 12.0f;
    armor = 0.0f;
    maxArmor = 100.0f;
    hasArmor = false;
    isDead = false;
    isMoving = false;
    facingRight = true;
    isRunning = false;
    isAiming = false;
    isShooting = false;
    isReloading = false;
    canShoot = true;
    hasWatch = false;
    hasGun = false;
    hasRaygun = false;
    hasShotgun = false;
    hasMac10 = false;
    outline = false;
    hasShovel = false;
    hasWhiskey = false;
    hasBadge = false;
    enter_car = false;
    enter_train = false;
    can_take_damage = true;
    holdingDown = false;
    dropping = false;
    dropTimer = 0.0;
    step = false;
    shells = 16;
    autoAmmo = 150;
    revolverAmmo = 50;
    raygunSize = 1;
    arriving = false;
    chargeTimer = 0.0f;
    LastTapTimeLeft = 0;
    LastTapTimeRight = 0;
    tapInterval = 0.3;
    runFrameSpeed = 1.5;
    walkFrameSpeed = 1;
    bulletCount = 6;
    abductionTimer = 0.0;
    mac10BulletCount = 30;
    revolverBulletCount = 6;
    shotgunBulletCount = 2;  // For Shotgun
    shotgunReloadTime = 0.7f;  // Reload time for Shotgun
    currentWeapon = REVOLVER;  // Start with Revolver
    AllowGuns = true;
    hasCrowbar = false;
    canSwing = true;
    swinging = false;
    swingTimer = 0.0;
    money = 100;
    validatedPassword = false;
    necroTechSearched = false;
    onElevator = false;
    abduction = false;
    hasPills = false;
    chargeSoundPlayed = false;
    charging = false;
    maxChargeTime = 2.0;
    

}

void Player::take_damage(int damage) {

    if (armor > 0 && can_take_damage){     
        armor -= damage;
        can_take_damage = false;
        hitTimer = 0.9f;

        if (rand() & 2 == 0){
            PlaySound(SoundManager::getInstance().GetSound("armorHit2"));
        }else{
            PlaySound(SoundManager::getInstance().GetSound("armorHit"));
        }
    }
    
    if (!enter_car && armor <= 0){ //dont take damage if inside car

        if (can_take_damage && !isDead){
            hitTimer = 0.9f; // tint the sprite red for .3 seconds
        
            can_take_damage = false;
            currentHealth -= damage;
            bloodEmitter.position = position + Vector2 {28, 16};
            bloodEmitter.SpawnBlood(10, RED, !facingRight);
            

            if (rand() % 2 == 0){
                PlaySound(SoundManager::getInstance().GetSound("phit1"));

            }else{
                PlaySound(SoundManager::getInstance().GetSound("phit2"));
            }
            
        }
        
        if (currentHealth <= 0) {
            can_take_damage = false;
            // Handle player death, like resetting position to apartment
            // Handled elsewhere
        }
    }

}


float GetRightBoundary(){
    //level boundaries. 
    if (gameState == OUTSIDE){
        return 4707.0f;
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
    }else if (gameState == PARK){
        return 2043;
    }else if (gameState == SUBWAY){
        return 3900;
    }else if (gameState == NECROTECH){
        return 2631;
    }else if (gameState == LOBBY){
        return 2800;
    }else if (gameState == OFFICE){
        return 3800;
    }else if (gameState == LAB){
        return 3852;
    }else if (gameState == ALIEN){
        return 3400;
    }
}

float GetLeftBoundary(){
    if (gameState == OUTSIDE){
        return -94;
    }else if (gameState == CEMETERY){
        return 1700;
    }else if (gameState == LOT){
        return 2400;
    }else if (gameState == GRAVEYARD){
        return 1500;
    }else if (gameState == APARTMENT){
        return 1064;
    }else if (gameState == WORK){
        return 1064;
    }else if (gameState == ASTRAL){
        return 1064;
    }else if (gameState == PARK){
        return 1000;
    }else if (gameState == SUBWAY){
        return 1554;
    }else if (gameState == NECROTECH){
        return 1550;
    }else if (gameState == LOBBY){
        return 1300;
    }else if (gameState == OFFICE){
        return 1000;
    }else if (gameState == LAB){
        return 1575;
    }else if (gameState == ALIEN){
        return 1024;
    }
}

void Player::DrawChargeBar(Vector2 offset) {
    float chargePercentage = chargeTimer / maxChargeTime; // Normalize charge time

    int barWidth = 10;  // Width of progress bar
    int barHeight = 3;   // Height of progress bar
    Vector2 barPos = { position.x + offset.x, position.y + offset.y };

    //floating points were causing flickering, round to nearest whole number including startX

    int filledWidth = static_cast<int>(barWidth * chargePercentage + 0.5f); // Round to nearest whole pixel "Banker's rounding"

    if (facingRight) {
        // Normal left-to-right fill
        DrawRectangle(barPos.x, barPos.y, filledWidth, barHeight, RED);
    } else {
        // Ensure smooth right-to-left fill
        int startX = static_cast<int>(barPos.x + (barWidth - filledWidth) + 0.5f);
        DrawRectangle(startX, barPos.y, filledWidth, barHeight, RED);
    }
    
}

void Player::UpdateCharge(float deltaTime, bool charging) {
    if (charging) {
        //chargeTimer += deltaTime;
        if (chargeTimer > maxChargeTime) chargeTimer = maxChargeTime;
    } else {
        chargeTimer = 0.0f; // Reset charge when not holding fire
    }
}




bool Player::CheckHit(Vector2 previousBulletPosition, Vector2 currentBulletPosition, Vector2 bulletSize) { 
    //         ______|_______
    //        |      32-4 x  |
    //        |      __   16y|_
    //        |     | 8|     | 64  the image size is 64x64. the character is in the middle of the image. 
    //        |     |32|     | the character is 8x32. offset X by half image - half the character size, offset y by half character height.  
    //        |     |__|     |   
    //        |______________|
    //              64                                                     
    // Define a hitbox around the NPC 
    float hitboxWidth = 8.0f;   // Width of the hitbox                    
    float hitboxHeight = 32.0f; // Height of the hitbox                 
    ///                                                                  
    //                                                                    
    // Offset the hitbox so it's centered on the zombie's position        
    Rectangle npcHitbox = {
        position.x + 32 - 4,   // Center horizontally
        position.y+16,  // Center vertically
        hitboxWidth,                    // Width of hitbox
        hitboxHeight                    // Height of hitbox
    };

    // Check if the current or previous bullet position is inside the hitbox (normal check)
    Rectangle bulletRect = {
        currentBulletPosition.x,  // Bullet's x position
        currentBulletPosition.y,  // Bullet's y position
        bulletSize.x,             // Bullet's width
        bulletSize.y              // Bullet's height
    };

    if (CheckCollisionRecs(npcHitbox, bulletRect)) {
        return true;  // Return true indicating a hit
    }

    // Check if the bullet's path (line from previous to current position) intersects with the hitbox
    if (CheckCollisionPointRec(previousBulletPosition, npcHitbox) || CheckCollisionPointRec(currentBulletPosition, npcHitbox)) {
        return true;
    }

    // Use raycasting to check for collisions between the previous and current bullet positions
    Vector2 bulletPath = Vector2Subtract(currentBulletPosition, previousBulletPosition);
    int steps = ceil(Vector2Length(bulletPath) / bulletSize.x);  // Steps depend on bullet size

    // Check along the bullet's path for a collision
    for (int i = 0; i < steps; i++) {
        Vector2 interpolatedPosition = Vector2Lerp(previousBulletPosition, currentBulletPosition, i / (float)steps);
        if (CheckCollisionPointRec(interpolatedPosition, npcHitbox)) {
            return true;  // A hit is detected
        }
    }

    return false;  // Return false if no hit occurred
}

void Player::HandleInput(float speed) {
    if (abduction) return; // Can't move while being abducted by aliens.
    // Detect if a gamepad is connected
    bool isControllerConnected = IsGamepadAvailable(0);

    //weapon switching
    // 1,2 or 3, 4 or D-pad left, up, right, down. clockwise
    if ((IsKeyPressed(KEY_ONE) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) && hasGun) { //dpad left
        currentWeapon = REVOLVER;
    } else if ((IsKeyPressed(KEY_TWO) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) && hasShotgun) { //up
        currentWeapon = SHOTGUN;
    }else if ((IsKeyPressed(KEY_THREE) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) && hasMac10){ //right
        currentWeapon = MAC10;
    }else if (IsKeyPressed(KEY_FOUR) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN) && hasRaygun){ //dpad down
        currentWeapon = RAYGUN;
    }

    
    float deltaTime = GetFrameTime();

    // ------------------------------
    // MOVEMENT (Keyboard + Left Stick)
    // ------------------------------
    float moveX = 0.0f; // Movement direction
    float leftStickX = 0.0f;

    if (isControllerConnected) {
        leftStickX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
    }

    // Keyboard movement
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) moveX = 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) moveX = -1.0f;

    // Controller movement (if above deadzone threshold)
    float deadzone = 0.2f; // Ignore slight stick movements
    if (fabs(leftStickX) > deadzone) {
        moveX = leftStickX;
    }

    // Apply movement
    if (moveX != 0) {
        
        velocity.x += moveX * acceleration * deltaTime;
        velocity.x = std::clamp(velocity.x, -maxSpeedX, maxSpeedX);

        isMoving = true;
        facingRight = moveX > 0;
    } else {
        // Deceleration when no input
        if (velocity.x > 0.0f) {
            velocity.x = std::max(velocity.x - deceleration * deltaTime, 0.0f); // Stop at zero
        } else if (velocity.x < 0.0f) {
            velocity.x = std::min(velocity.x + deceleration * deltaTime, 0.0f); // Stop at zero
        }

        // Only set isMoving to false if velocity has actually stopped
        isMoving = (velocity.x != 0.0f);
    }

    // ------------------------------
    // RUNNING (Keyboard + Controller)
    // ------------------------------
    if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && !isAiming) {
        isRunning = true;
    }
    if (abs(leftStickX) > 0.7f) { //hold all the way left or right to run
        isRunning = true;

    }

    if (moveX == 0 && !isAiming) {
        isRunning = false;  // Stop running if no movement keys are pressed
    }

    // ------------------------------
    // JUMPING (Keyboard + Controller)
    // ------------------------------
    float leftStickY = 0.0f;
    if (isControllerConnected) {
        leftStickY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) || (isControllerConnected && leftStickY > 0.5f)) {
        holdingDown = true;
        if (IsKeyPressed(KEY_SPACE) || (isControllerConnected && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP))) {
            isOnGround = false;
            dropping = true;
            jumping = true; // Needed to reset velocity.y
            dropTimer = 1.0;
        }
    } else {
        holdingDown = false;
    }

    // Regular Jump
    if ((IsKeyPressed(KEY_SPACE) || (isControllerConnected && IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_UP)))
        && isOnGround && !jumping && !holdingDown) {
        velocity.y = -jumpForce;
        isOnGround = false;
        jumping = true;
        PlaySound(SoundManager::getInstance().GetSound("jump"));
    }

    // ------------------------------
    // AIMING (Keyboard + Controller)
    // ------------------------------
    if (isAiming && !isReloading) {
        if (moveX > 0) {
            facingRight = true;
        }
        if (moveX < 0) {
            facingRight = false;
        }
    }

    
}



void Player::reloadLogic(float deltaTime){
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

}

void Player::Reload(){
    if (currentWeapon == REVOLVER){
        if (!isReloading && revolverAmmo > 0 && revolverBulletCount < 6){
            isReloading = true;    
            reloadTimer = 0.5f;
            
            int bulletsNeeded = (6 - revolverBulletCount);
            int bulletsToReload = (revolverAmmo >= bulletsNeeded) ? bulletsNeeded : revolverAmmo; 
            PlaySound(SoundManager::getInstance().GetSound("reload"));

            // Update ammo counts
            revolverAmmo -= bulletsToReload;
            revolverBulletCount += bulletsToReload;

        }
        

    }else if (currentWeapon == SHOTGUN && shotgunBulletCount < 2){// reload anytime but full
        if (!isReloading && shells > 0) { // Ensure there are shells to reload
            int shellsNeeded = 2 - shotgunBulletCount; // How many shells we can load
            int shellsToUse = (shells >= shellsNeeded) ? shellsNeeded : shells; // Use available shells

            shells -= shellsToUse;
            shotgunBulletCount += shellsToUse;

            isReloading = true;
            shotgunReloadTime = 0.7f; //start the reload timer


            bulletCount = MAX_BULLETS;//shotgun uses same bullets array //refill bullets
            PlaySound(SoundManager::getInstance().GetSound("ShotgunReload"));

        }

    }
    else if (currentWeapon == MAC10) {
    // Check if not already reloading, there is reserve ammo, and the magazine is not full
        if (!isReloading && autoAmmo > 0 && mac10BulletCount < 30) {
            isReloading = true;
            reloadTimer = 0.5f; 

            // Calculate how many bullets are needed to fill the magazine
            int bulletsNeeded = 30 - mac10BulletCount;

            // Determine how many bullets we can actually reload
            int bulletsToReload = (autoAmmo >= bulletsNeeded) ? bulletsNeeded : autoAmmo; 

            // Update ammo counts
            autoAmmo -= bulletsToReload;
            mac10BulletCount += bulletsToReload;
            
            PlaySound(SoundManager::getInstance().GetSound("reload"));
    }
}

}


bool Player::CheckIfOnPlatform() {
    float hitboxWidth = 7.0;
    float hitboxHeight = 24.0f;
    // Create the player's collision rectangle
    Rectangle playerRect = {
        position.x + 30,
        position.y + 24,
        hitboxWidth,
        hitboxHeight //magic numbers to size hitbox smaller than texture
    };

    
    //isOnGround = false; //reset elsewhere

    // Check collision with platforms Simplified. 
    for (const Platform& platform : platforms) {
        if (CheckCollisionRecs(playerRect, platform.rect)) {
            if (velocity.y > 0) {
                // Moving down; landed on top of platform
                position.y = platform.rect.y - size.y - 16;
                //velocity.y = 0.0f;
                if (jumping){
                    jumping = false;
                    velocity.y = 0; //flush excess velocity, only if jumping so it only runs once. 
                } 
                isOnGround = true; 
                
                return true;

                
            
            }
            // Handle horizontal collisions (optional)
        }
    }

    return false;  // Player is not on a platform
}


void Player::playerPhysics(float deltaTime){
    if (enter_train || abduction) return;
    if (dropTimer > 0){ //drop through platforms for 1 second
        dropTimer -= GetFrameTime();
        
    }else{
        dropTimer = 0;
        dropping = false;
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

    if (isAiming || isShooting || isReloading){ // apply deceleration here, and when there is no input
        if (velocity.x > 0.0f) {
            velocity.x -= deceleration * deltaTime;
            if (velocity.x < 0.0f) velocity.x = 0.0f;
        } else if (velocity.x < 0.0f) {
            velocity.x += deceleration * deltaTime;
            if (velocity.x > 0.0f) velocity.x = 0.0f;
        }

    }



    position.x += velocity.x * deltaTime;
    
    
    position.y += velocity.y * deltaTime;
    isOnGround = false;
    //playerRect.y = position.y;
    if (!dropping){
        if (CheckIfOnPlatform()){
            isOnGround = true;
            
            
            
        }

    }

    // Collision with the ground (assuming ground at y = groundLevel)
    float groundLevel = 700.0f + size.y;  // Adjust based on your game's ground position
    if (position.y + size.y >= groundLevel) { //if below ground
        position.y = groundLevel - size.y;
        velocity.y = 0.0f;
        isOnGround = true;
        
        jumping = false;
    }

    if (!isOnGround) {
        velocity.y += gravity * deltaTime;
    }

}



void Player::updateAnimations(){
    if (gameState == APARTMENT) return;


    if (swinging){
        frameCounter += GetFrameTime() * frameSpeed;
        int numFrames = 7;//(maxSpeedX == runSpeed) ? (resources.runSheet.width / 64) : (resources.walkSheet.width / 64);

        if (frameCounter >= 0.1){
            currentFrame++;
            frameCounter = 0;

            if (currentFrame >= numFrames){
                currentFrame = 0;
            }
        }

    }
    else if (isShooting) {
        if (currentWeapon == MAC10) frameSpeed = frameSpeed * 10;
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
    } else if (isMoving && !isAiming) {
        frameCounter += GetFrameTime() * frameSpeed;
        int numFrames = (maxSpeedX == runSpeed) ? (resources.runSheet.width / 64) : (resources.walkSheet.width / 64);

        if (frameCounter >= 0.1) {
            
            currentFrame++;
            frameCounter = 0;

            if (currentFrame >= numFrames && isOnGround) {
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



void Player::shootLogic(){
    charging = false;



    //handle crowbar
    if ((IsKeyPressed(KEY_V) || IsKeyPressed(KEY_LEFT_CONTROL)|| IsKeyPressed(KEY_RIGHT_CONTROL) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) && canSwing && !isAiming &&  !isReloading && !isShooting && hasCrowbar && !isMoving && gameState != APARTMENT){ //swing the crowbar
        canSwing = false;
        swinging = true;
        swingTimer = 0.5f;


        if (rand() % 2 == 0){//multiple swing sounds
            PlaySound(SoundManager::getInstance().GetSound("crowbarSwing"));

        }else{
            PlaySound(SoundManager::getInstance().GetSound("crowbarSwing2"));
        }

    }

    if (swingTimer > 0){
        swingTimer -= GetFrameTime();
    }else{
        canSwing = true;
        swinging = false;
    }

    //AIMING
    isAiming = ((hasGun || hasShotgun || hasMac10 || hasRaygun) && (IsKeyDown(KEY_F) || IsKeyDown(KEY_LEFT_CONTROL) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_TRIGGER_2)) && !isShooting && !isReloading && AllowGuns);


    //SHOOTING REVOLVER
    if (currentWeapon == REVOLVER && AllowGuns){
        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && revolverBulletCount <= 0){
            //SoundManager::getInstance().GetSound("dryFire");
            PlaySound(SoundManager::getInstance().GetSound("dryFire"));

        }

    
        if (hasGun && revolverBulletCount > 0 && isAiming && (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_2))) {
            isShooting = true;
            canShoot = false;
            currentFrame = 0;
            frameCounter = 0.0f;
            revolverBulletCount--;
            //SoundManager::getInstance().GetSound("gunShot");  // Access the sound directly
            PlaySound(SoundManager::getInstance().GetSound("gunShot")); 

            FireBullet(*this, false, 25, false, false);
            
        }

    //SHOOTING SHOTGUN
    }else if (currentWeapon == SHOTGUN && AllowGuns){
        //Dry Fire
        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && shotgunBulletCount <= 0){
            //SoundManager::getInstance().GetSound("dryFire");
            PlaySound(SoundManager::getInstance().GetSound("dryFire"));

        }

        //Shoot shotgun
        if (hasShotgun && shotgunBulletCount > 0 && isAiming && (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) && canShoot) {
            isShooting = true;
            canShoot = false;
            currentFrame = 0;
            frameCounter = 0.0f;
            shotgunBulletCount--;

            PlaySound(SoundManager::getInstance().GetSound("ShotGun"));
            // Shotgun fires multiple bullets (spread effect)
            for (int i = 0; i < 3; i++) {  // Simulate shotgun spread with 3 bullets
                FireBullet(*this, true, 25, false, false);  // Modify FireBullet to allow spread by adjusting directions

            }

        }

        //SHOOTING MAC10
    }else if (currentWeapon == MAC10 && AllowGuns){
        //dry fire
        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && mac10BulletCount <= 0){
            //SoundManager::getInstance().GetSound("dryFire");
            PlaySound(SoundManager::getInstance().GetSound("dryFire"));

        }

        //IsKeyDown for automatic fire. 
        if (hasMac10 && mac10BulletCount > 0 && isAiming && (IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) && canShoot) {
            isShooting = true;
            canShoot = false;
            currentFrame = 0;
            frameCounter = 0.0f;
            mac10BulletCount--;

            PlaySound(SoundManager::getInstance().GetSound("Mac10"));
                
            FireBullet(*this, true, 20, false, false);  //mac10 does less damage. 10 instead of 25. it's a 9mm bullet instead of a 44 revolver, or shotgun pellet
            

        }
    }else if (currentWeapon == RAYGUN && AllowGuns){
        //no dry fire
        if (hasRaygun  && isAiming && (IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)) && canShoot) {
            chargeTimer += GetFrameTime();
            charging = true;

            if (!chargeSoundPlayed){
                PlaySound(SoundManager::getInstance().GetSound("chargeUp"));
                chargeSoundPlayed = true;

            }
            
        }

        if (isAiming && canShoot){
            if (IsKeyReleased(KEY_SPACE) || IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsGamepadButtonReleased(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_2)){
                SoundManager::getInstance().ManagerStopSound("chargeUp");
                PlaySound(SoundManager::getInstance().GetSound("plasma"));
                if (chargeTimer > 1.5) PlaySound(SoundManager::getInstance().GetSound("raygunFire"));
                chargeSoundPlayed = false;
                isShooting = true;
                canShoot = false;
                currentFrame = 0;
                frameCounter = 0.0f;
                //infinite bullets
                int rayDamage = 10;
                if (chargeTimer > 1.5){
                    rayDamage = 100;
                } 
                else if (chargeTimer > 1){
                    rayDamage = 50;
                } 
                else if (chargeTimer > 0.5){
                    rayDamage = 30;
                }
                //play laser sound. 

                FireBullet(*this, false, rayDamage, false, true);
                chargeTimer = 0;

            } 
        }    
    }   
}

void Player::UpdateMovement() {
    //isMoving = false; //reset is moving to false at the start of the frame. If it remains false all the way though to the next frame, we are not moving. 

    float deltaTime = GetFrameTime();
    if (currentWeapon == RAYGUN){
        UpdateCharge(deltaTime, charging);
    }
    
    reloadLogic(deltaTime);
    shootLogic(); //handle key presses for shooting and switching weapons. 
    
    if ((IsKeyPressed(KEY_R) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT)) && AllowGuns){
        Reload();
    }
     
    bloodEmitter.UpdateParticles(deltaTime);
    maxSpeedX = isRunning ? runSpeed : walkSpeed; //if running, maxspeed = runspeed else walkspeed
    frameSpeed = isRunning ? runFrameSpeed : walkFrameSpeed;

    if (abduction && abductionTimer <= 0){
        abductionTimer = 7.0f;
        
    }

    if (abductionTimer > 0){
        abductionTimer -= deltaTime;
        player.position.y -= walkSpeed/2 * deltaTime;
        
    }

    

    //keep player in bounds
    if (!enter_train){ // player can leave boundaries on the train
        if (position.x < GetLeftBoundary()){
            position.x = GetLeftBoundary() + 1;
        }else if (position.x > GetRightBoundary()){
            position.x = GetRightBoundary()-1;
        }

    }



    
    if (!isAiming && !isShooting && !isReloading) {
        //KEYBOARD MOVEMENT CODE
        HandleInput(maxSpeedX); //check input before physics
    
    }
    playerPhysics(deltaTime);

    
    updateAnimations();
}



// Method for drawing the player
void Player::DrawPlayer() {
    Texture2D currentSheet;
    Rectangle sourceRec;
    int frameWidth = 64; // Assuming each frame is 64 pixels wide
    if (currentWeapon == RAYGUN){
        if (facingRight){
            DrawChargeBar(Vector2 {40, 16});
        }else{
            DrawChargeBar(Vector2 {16, 16});
        } 
    }
    

    // Prioritize drawing states: Shooting > Reloading > Aiming > Moving > Idle
    if (currentWeapon == REVOLVER){
    
        if (hasGun && isShooting && (AllowGuns)) { //need a way to allow guns outside cemetery at a certain point in the game. 
            currentSheet = resources.shootSheet;
            sourceRec = { static_cast<float>(currentFrame * frameWidth), 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }
        else if (hasGun && isReloading && (AllowGuns)){
        
            currentSheet = resources.reloadSheet;
            sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }
        else if (hasGun && isAiming && !isReloading && (AllowGuns)) {
            // Aiming but not shooting: use the first frame of the shootSheet
            currentSheet = resources.shootSheet;
            sourceRec = { 0, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };  // First frame for aiming

        }
        else if (jumping){
            currentSheet = resources.jumpSheet;
            sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        } 
        else if (isMoving) {
            // Walking or running animation
            currentSheet = isRunning ? resources.runSheet : resources.walkSheet;  // Use runSheet if running, else walkSheet
            sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };
        }else {
            // Idle pose
            currentSheet = resources.manTexture;  // Idle pose
            sourceRec = { 0, 0, static_cast<float>(currentSheet.width), static_cast<float>(currentSheet.height) };
        }



    
    }
    else if (currentWeapon == SHOTGUN){/////////////////shotgun//////////////
        
         if (hasShotgun && isShooting && (AllowGuns)){
            currentSheet = resources.ShotGunSheet;
            sourceRec = {static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }
        else if (hasShotgun && isReloading && (AllowGuns)){
            currentSheet = resources.ShotgunReload;
            sourceRec = {static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }
        else if (hasShotgun && isAiming && !isReloading && (AllowGuns)) {
            // Aiming but not shooting: use the first frame of the shootSheet
            currentSheet = resources.ShotGunSheet;
            sourceRec = { 0, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth)};  // First frame for aiming

        } 
        else if (isMoving) {
            // Walking or running animation
            currentSheet = isRunning ? resources.runSheet : resources.walkSheet;  // Use runSheet if running, else walkSheet
            sourceRec = {static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };
        } 
        else {
            // Idle pose
            currentSheet = resources.manTexture;  // Idle pose
            sourceRec = { 0, 0, static_cast<float>(currentSheet.width), static_cast<float>(currentSheet.height) };
        }      

    }
    else if (currentWeapon == MAC10){
    
        if (hasMac10 && isShooting && (AllowGuns)) { //need a way to allow guns outside cemetery at a certain point in the game. 
            currentSheet = resources.shootSheetAuto;
            sourceRec = { static_cast<float>(currentFrame * frameWidth), 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }
        else if (hasMac10 && isReloading && (AllowGuns)){
        
            currentSheet = resources.reloadSheetAuto;
            sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }
        else if (hasMac10 && isAiming && !isReloading && (AllowGuns)) {
            // Aiming but not shooting: use the first frame of the shootSheet
            currentSheet = resources.shootSheetAuto;
            sourceRec = { 0, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };  // First frame for aiming

        }
        else if (jumping){
            currentSheet = resources.jumpSheet;
            sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        } 
        else if (isMoving) {
            // Walking or running animation
            currentSheet = isRunning ? resources.runSheet : resources.walkSheet;  // Use runSheet if running, else walkSheet
            sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };
        } 
        else {
            // Idle pose
            currentSheet = resources.manTexture;  // Idle pose
            sourceRec = { 0, 0, static_cast<float>(currentSheet.width), static_cast<float>(currentSheet.height) };
        }
    }
    else if (currentWeapon == RAYGUN){
    
        if (hasRaygun && isShooting && (AllowGuns)) { //need a way to allow guns outside cemetery at a certain point in the game. 
            currentSheet = resources.shootRaygunSheet;
            sourceRec = { static_cast<float>(currentFrame * frameWidth), 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }
        else if (hasRaygun && isReloading && (AllowGuns)){
        
            currentSheet = resources.reloadSheetAuto;
            sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        }
        else if (hasRaygun && isAiming && !isReloading && (AllowGuns)) {
            // Aiming but not shooting: use the first frame of the shootSheet
            currentSheet = resources.shootRaygunSheet;
            sourceRec = { 0, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };  // First frame for aiming

        }
        else if (jumping){
            currentSheet = resources.jumpSheet;
            sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };

        } 
        else if (isMoving) {
            // Walking or running animation
            currentSheet = isRunning ? resources.runSheet : resources.walkSheet;  // Use runSheet if running, else walkSheet
            sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };
        } 
        else {
            // Idle pose
            currentSheet = resources.manTexture;  // Idle pose
            sourceRec = { 0, 0, static_cast<float>(currentSheet.width), static_cast<float>(currentSheet.height) };
        }
    }

    if (swinging && !isMoving && !isAiming && !isShooting){
        currentSheet = resources.crowbarSheet;
        sourceRec = { static_cast<float>(currentFrame) * frameWidth, 0, static_cast<float>(frameWidth), static_cast<float>(frameWidth) };
    }    


    // Adjust source rectangle for direction
    if (!facingRight) {
        sourceRec.width = -frameWidth;  // Flip the texture if facing left
    }

    if (hitTimer > 0){ //tint player when taking damage for hitTimer number of seconds
        hitTimer -= GetFrameTime();
        //can_take_damage = false? must be done else where 
       
    }else{
        can_take_damage = true;

    }

    // Draw the player
    Color tint = (hitTimer > 0 && armor <= 0) ? RED : WHITE;
    Vector2 castPos = {(float) position.x, (float) position.y};
    if (outline) BeginShaderMode(shaders.outlineShader);
    bloodEmitter.DrawParticles();
    
    DrawTextureRec(currentSheet, sourceRec, castPos, tint);  // Draw the player based on the current state
    
    EndShaderMode();

}


