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


WeaponType currentWeapon;  // To track the current weapon


Player player;  // Define the player instance


Player::Player() {
    position = {1922.0, 700.0};

    velocity = {0.0f, 0.0f};
    size.x = 16;
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
    hasWatch = false;
    hasGun = false;
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
    revolverAmmo = 30;
    
    arriving = false;
    LastTapTimeLeft = 0;
    LastTapTimeRight = 0;
    tapInterval = 0.3;
    runFrameSpeed = 1.5;
    walkFrameSpeed = 1;
    bulletCount = 6;

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

    hasPills = false;

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
            can_take_damage = false;
            // Handle player death, like resetting position to apartment
            // Handled elsewhere
        }
    }

}


float GetRightBoundary(GameState gameState){
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
    }
}

float GetLeftBoundary(GameState gameState){
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
        return 1064;
    }else if (gameState == SUBWAY){
        return 1554;
    }else if (gameState == NECROTECH){
        return 1550;
    }else if (gameState == LOBBY){
        return 1300;
    }else if (gameState == OFFICE){
        return 1000;
    }
}

bool Player::CheckHit(Vector2 previousBulletPosition, Vector2 currentBulletPosition, Vector2 bulletSize) { 
    //raycasting for better collision detection
    // Define a hitbox around the NPC (centered on the NPC's position)
    float hitboxWidth = 8.0f;   // Width of the hitbox 
    float hitboxHeight = 32.0f; // Height of the hitbox 

    // Offset the hitbox so it's centered on the zombie's position
    Rectangle npcHitbox = {
        position.x + 32,   // Center horizontally
        position.y,  // Center vertically
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
            // Apply deceleration when no input is detected //need to decelerate when aiming, shooting, also
            if (velocity.x > 0.0f) {
                velocity.x -= deceleration * deltaTime;
                if (velocity.x < 0.0f) velocity.x = 0.0f;
            } else if (velocity.x < 0.0f) {
                velocity.x += deceleration * deltaTime;
                if (velocity.x > 0.0f) velocity.x = 0.0f;
            }
        }

        
        // Jumping logic

        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
            holdingDown = true;
            if (IsKeyPressed(KEY_SPACE)){ //hold down and press space to drop through platform. 
                isOnGround = false;
                dropping = true;
                jumping = true; //turn on jumping so we can turn it back off when hitting a platform. Needed to reset velocity.y
                dropTimer = 1.0;
            }

        }else{
            holdingDown = false;
            //dropping = false;
        }
       
       
        if (IsKeyPressed(KEY_SPACE) && isOnGround && !jumping && !holdingDown) {
            velocity.y = -jumpForce;  
            isOnGround = false;
            jumping = true;
            PlaySound(SoundManager::getInstance().GetSound("jump"));

        }


  
        // Check for shift key to run
        if ((IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && !isAiming) {
            isRunning = true;
        } else if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_D) && !isAiming) {
            isRunning = false;  // Stop running if no movement keys are pressed
        }

        //change facing direction while stopped, and aiming. 
        if (isAiming && !isReloading) {
            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
                facingRight = true;
            }
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
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
        

    }else if (currentWeapon == SHOTGUN && shotgunBulletCount < 2){// you can't reload unless fully empty, this simplifies things. 
        if (!isReloading && shells > 0) { // Ensure there are shells to reload
            int shellsNeeded = 2 - shotgunBulletCount; // How many shells we can load
            int shellsToUse = (shells >= shellsNeeded) ? shellsNeeded : shells; // Use available shells

            shells -= shellsToUse;
            shotgunBulletCount += shellsToUse;

            isReloading = true;
            shotgunReloadTime = 0.7f; //start the reload timer

            //shotgunBulletCount = 2;
            bulletCount = MAX_BULLETS;//shotgun uses same bullets array
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


bool Player::CheckIfOnPlatform(const std::vector<Platform>& platforms) {
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


void Player::playerPhysics(float deltaTime, std::vector<Platform> platforms){
    if (enter_train) return;
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
        if (CheckIfOnPlatform(platforms)){
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



void Player::updateAnimations(GameResources& resources){
    if (isShooting) {
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
    } else if (isMoving) {
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
    }else if (swinging){
        frameCounter += GetFrameTime() * frameSpeed;
        int numFrames = (maxSpeedX == runSpeed) ? (resources.runSheet.width / 64) : (resources.walkSheet.width / 64);

        if (frameCounter >= 0.1){
            currentFrame++;
            frameCounter = 0;

            if (currentFrame >= numFrames){
                currentFrame = 0;
            }
        }

    } else if (!isAiming) {
        currentFrame = 0;
    }

}

void Player::shootLogic(){

    if (IsKeyPressed(KEY_ONE)) {
        currentWeapon = REVOLVER;
    } else if (IsKeyPressed(KEY_TWO)) {
        currentWeapon = SHOTGUN;
    }else if (IsKeyPressed(KEY_THREE)){
        currentWeapon = MAC10;
    }

    if ((IsKeyPressed(KEY_V) || IsKeyPressed(KEY_LEFT_CONTROL)|| IsKeyPressed(KEY_RIGHT_CONTROL)) && canSwing && !isAiming && !isReloading && !isShooting && hasCrowbar){ //swing the crowbar
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
    isAiming = ((hasGun || hasShotgun || hasMac10) && (IsKeyDown(KEY_F) || IsKeyDown(KEY_LEFT_CONTROL) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) && !isShooting && !isReloading && AllowGuns);


    //SHOOTING REVOLVER
    if (currentWeapon == REVOLVER && AllowGuns){

        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && revolverBulletCount <= 0){
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

            FireBullet(*this, false, 25, false);
            
        }
    //SHOOTING SHOTGUN
    }else if (currentWeapon == SHOTGUN && AllowGuns){
        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && shotgunBulletCount <= 0){
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
                FireBullet(*this, true, 25, false);  // Modify FireBullet to allow spread by adjusting directions

            }

        }
        //SHOOTING MAC10
    }else if (currentWeapon == MAC10 && AllowGuns){
        if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && mac10BulletCount <= 0){
            //SoundManager::getInstance().GetSound("dryFire");
            PlaySound(SoundManager::getInstance().GetSound("dryFire"));

        }

        //IsKeyDown for automatic fire. 
        if (hasMac10 && mac10BulletCount > 0 && isAiming && (IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) && canShoot) {
            isShooting = true;
            canShoot = false;
            currentFrame = 0;
            frameCounter = 0.0f;
            mac10BulletCount--;

            PlaySound(SoundManager::getInstance().GetSound("Mac10"));
                
            FireBullet(*this, true, 20, false);  //mac10 does less damage. 10 instead of 25. it's a 9mm bullet instead of a 44 revolver, or shotgun pellet
            

        }
    }  
}

void Player::UpdateMovement(GameResources& resources,  GameState& gameState, Vector2& mousePosition, Camera2D& camera, std::vector<Platform> platforms) {
    isMoving = false; //reset is moving to false at the start of the frame. If it remains false all the way though to the next frame, we are not moving. 

    float deltaTime = GetFrameTime();
    
    reloadLogic(deltaTime);
    shootLogic(); //handle key presses for shooting and switching weapons. 
    
    if (IsKeyPressed(KEY_R) && AllowGuns){
        Reload();
    }



     

    maxSpeedX = isRunning ? runSpeed : walkSpeed; //if running, maxspeed = runspeed else walkspeed
    frameSpeed = isRunning ? runFrameSpeed : walkFrameSpeed;

    //keep player in bounds
    if (!enter_train){ // player can leave boundaries on the train
        if (position.x < GetLeftBoundary(gameState)){
            position.x = GetLeftBoundary(gameState) + 1;
        }else if (position.x > GetRightBoundary(gameState)){
            position.x = GetRightBoundary(gameState)-1;
        }

    }


    
    if (!isAiming && !isShooting && !isReloading) {
        //KEYBOARD MOVEMENT CODE
        HandleInput(maxSpeedX); //check input before physics
    
    }
    playerPhysics(deltaTime, platforms);

    
    updateAnimations(resources);
}



// Method for drawing the player
void Player::DrawPlayer(const GameResources& resources, GameState& gameState, Camera2D& camera, ShaderResources& shaders) {
    Texture2D currentSheet;
    Rectangle sourceRec;
    int frameWidth = 64; // Assuming each frame is 64 pixels wide
    
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
    Color tint = (hitTimer > 0) ? RED : WHITE;
    Vector2 castPos = {(float) position.x, (float) position.y};
    if (outline) BeginShaderMode(shaders.outlineShader);
    DrawTextureRec(currentSheet, sourceRec, castPos, tint);  // Draw the player based on the current state
    EndShaderMode();

}


