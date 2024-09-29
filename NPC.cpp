// NPC.cpp
#include "NPC.h"
#include "Player.h"
#include <raylib.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <raymath.h>
#include "SoundManager.h"
#include <vector>
#include <string>
#include <cstdlib>  // For rand and srand
#include <ctime>    // For seeding rand

float detectionRange = 200.0f;  // Set detection range for zombies
float talkTimer = 0.0f;

// Constructor with additional parameters for isActive and isZombie
NPC::NPC(Texture2D npcTexture, Vector2 startPos, float npcSpeed, AnimationState initialAnimation, bool active, bool zombie)
    : texture(npcTexture), position(startPos), speed(npcSpeed), currentAnimation(initialAnimation), isActive(active), isZombie(zombie) {
    frameCounter = 0;
    frameSpeed = 8.0f;
    currentFrame = 0;
    facingRight = true;
    patrollingRight = rand() % 2 == 0;  // Randomly set initial direction
    patrolling = false;  // Default to not patrolling
    idleTime = 0;  // Initialize idle time
    maxHealth = 75;  // Initialize max health
    health = maxHealth;  // Initialize current health
    hitTimer = 0.0f;  // Initialize hit timer to 0
    isDying = false;  // Initialize dying state to false
    riseTimer = 0.9f;
    interacting = false;
    talked = false;
    speech = " ";
    dealer = false;
    police = false;
    agro = false;
    attacking = false;
    hobo = false;
    clickCount = 0;

    
    
}

// Function to get a random phrase
std::string GetRandomPhrase() {
    std::vector<std::string> phrases = {
        "Hello!",
        "Hi, there!",
        "Buzz off!",
        "How's it\n going?",
        "Good day!",
        "Leave me\n alone!",
        "Nice\nweather",
        "What's up?"
    };

    // Seed the random number generator (only needs to be called once, typically in main)
    

    // Get a random index
    int randomIndex = rand() % phrases.size();

    // Return a random phrase

    return phrases[randomIndex];
}

void NPC::HandleNPCInteraction(){
        destination = position;//Stop NPC
        interacting = true;
        idleTime = 5;
        if (dealer) idleTime = 10;
        
        SetAnimationState(IDLE);
        if (police && !talked){
            talked = true;
            speech = (rand() % 2 == 0) ? "Freeze!" : "Halt!";
            talkTimer = 1;
            idleTime = 1;
            agro = true;
        }
        if (hobo && !talked){
            talked = true;
            clickCount += 1;
            idleTime = 3; //stops NPC while talking
            talkTimer = 3; // ensures this only runs once
            switch (clickCount){
                case 1:
                    speech = "GaaHh, what do you want?";
                    break;
                case 2:
                    speech = "wait, you're not like the others";
                    break;
                case 3:
                    speech = "maybe you'll believe me";
                    break;

                case 4:
                    speech = "I was in the graveyard last night.\n\nI saw something...";
                    break;

                case 5:
                    speech = "..."; //pause for dramatic effect. 
                    
                    break;

                case 6:
                    speech = "The DEAD were RISING\n\nfrom their GRAVES!";
                    break;

                case 7:
                    speech = "I dropped my SHOVEL and\n\ngot the hell out of there";
                    break;

                case 8:
                    speech = "I'd stay away from there\n\nif I was you";
                    break;

                case 9:
                    speech = "...";
                    break;


            }
                
            
            
        }
        if (!talked && !hobo && !police){
            talked = true;
            speech = GetRandomPhrase(); // NPC greets player
            talkTimer = 30; //limit talking. 30 second cooldown
        }
        
    }



// Function to set a new random destination within a specified range
void NPC::SetDestination(float minX, float maxX) {
    destination.x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxX - minX)));
    destination.y = position.y;  // Keep the same y position
    facingRight = (destination.x > position.x);  // Determine facing direction
}

void NPC::Update(Player& player) {
    if (!isActive) return;  // Skip update if the NPC is not active
    float distance_to_player = abs(player.position.x - position.x);
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        if (distance_to_player < 20){
            HandleNPCInteraction();
        }
    }



    // Check if the zombie is still rising
    if (riseTimer > 0) {
        riseTimer -= GetFrameTime();
        //SetAnimationState(RISING);  // Ensure the animation is set to RISING during this time
        
        // Update frame counter and animation logic for RISING
        frameCounter += GetFrameTime() * frameSpeed;
        if (frameCounter >= 1.0f) {
            frameCounter = 0.0f;
            currentFrame++;

            // 7 frames in the RISING animation
            if (currentFrame >= 7) {
                currentFrame = 0;  // Loop back to the first frame of the rising animation
            }
        }

        return;  // Skip further logic until the zombie finishes rising
    }


    // Update hit timer if the NPC has been hit
    if (hitTimer > 0) {
        hitTimer -= GetFrameTime();
        
    }

    // Handle death logic
    if (isDying) {
        deathTimer -= GetFrameTime();
        if (deathTimer <= 0.0f) {
            isActive = false;  // Set NPC as inactive after death animation
            return;
        }
    }



    // Update frame counter and animation logic
    frameCounter += GetFrameTime() * frameSpeed;
    if (frameCounter >= 1.0f) {
        frameCounter = 0.0f;
        currentFrame++;

        // Determine the number of frames based on the current animation
        int numFrames = 0;
        switch (currentAnimation) {
            case IDLE:
                
                numFrames = 1;  // Only one frame for idle
                break;
            case WALK:
                numFrames = 7;  // 7 frames for walking
                break;
            case RUN:
                numFrames = 7;  // 7 frames for running
                break;
            case DEATH:
                numFrames = 7;  // 7 frames for dying
                break;

            case ATTACKING:
                numFrames = 7;
                break;

            case RISING:
             
                numFrames = 7;
                break;


        }

        // Loop back to the first frame if currentFrame exceeds numFrames
        if (currentFrame >= numFrames) {
            currentFrame = 0;
        }
    }

    // If NPC is idle, reduce idle time
    if (idleTime > 0) {
        idleTime -= GetFrameTime();
        return;  // Remain idle until idleTime runs out
    }
    if (idleTime <= 0) interacting = false; // NPCs stop  when IdleTime is up. 



    // Check if the player is within a certain range to chase
    float distanceToPlayer = Vector2Distance(position, player.position);
    bool hasTarget = false;
    attacking = false;

    

    if (isZombie && distanceToPlayer < detectionRange && riseTimer <= 0) {
        hasTarget = true; //if hasTarget dont go idle
        destination = player.position;  // Move towards the player
        
    }

    if (police && distanceToPlayer < detectionRange && agro){ //police chase player
        hasTarget = true;
        destination = player.position;
        speed = 75;
        frameSpeed = 14; //speed up animation for attacking and chasing. 
        

    }else if (police && distanceToPlayer >= detectionRange){ //police loose player
        agro = false;
        speed = 50;
        hasTarget = false;
        destination = position;
        idleTime = 1;
        frameSpeed = 8.0; //reset animation speed
    }


    if (police && distanceToPlayer < 20.0f && hasTarget && agro && !isDying){ // police attack player
        idleTime = 0.1f; //transition to idle before attacking so it doesn't flicker. 
        
        attacking = true;
        if (player.can_take_damage && currentFrame == 5){ //only hit on frame 5. 
            player.take_damage(10);
            
            PlaySound(SoundManager::getInstance().GetSound("BoneCrack"));
        }

        SetAnimationState(ATTACKING);
    }else if (police && distanceToPlayer >= 20.0f && hasTarget){ //player leaves attack area
        
        attacking = false;
    }



    if (isZombie && distanceToPlayer > 15 && riseTimer <= 0){ //player leaves attack area
        attacking = false;
    }
   
    if (isZombie && distanceToPlayer < 15.0f && riseTimer <= 0 && !isDying) { //zombie attack
        attacking = true;
        if (player.hitTimer <= 0){
            player.take_damage(10);
            PlaySound(SoundManager::getInstance().GetSound("BoneCrack")); 
        }
        
        SetAnimationState(ATTACKING);  // Switch to attacking animation

    }


    //NPCs choose a random position called destination. they move toward destination until they arrive then repeat. 
    if (!isDying && riseTimer <= 0 && !attacking) { //MOVE NPCs and Police and Zombies. 
        // Move towards the destination
        if (position.x < destination.x) {
            position.x += speed * GetFrameTime();
            facingRight = true;
            SetAnimationState(WALK);
        } else if (position.x > destination.x) {
            position.x -= speed * GetFrameTime();
            facingRight = false;
            SetAnimationState(WALK);
        }



        // Check if destination is reached
        if (fabs(position.x - destination.x) < 5.0f && !hasTarget) {
            // Reached destination, go idle for a moment, then set a new destination
            idleTime = 3.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f));  // 3-6 seconds of idle time
            
            SetAnimationState(IDLE);

            // Only set a new random destination if not chasing the player
            if (!isZombie || distanceToPlayer >= detectionRange) {
                if (!hobo){
                    SetDestination(1800, 3000);  // Set a new destination within the range
                }else{
                    SetDestination(2600, 2800); // hobo stays near center
                }
                
            }
        
        }

    }
}

void NPC::Render() {
    if (!isActive) return;  // Skip rendering if the NPC is not active

    // Calculate the source rectangle for the current frame of the animation
    int frameWidth = 64;  // Each frame is 64 pixels wide
    int frameHeight = 64; // Each frame is 64 pixels tall

    // Set y-coordinate based on current animation state
    int row = 0;
    switch (currentAnimation) {
        case IDLE:
            row = 0;  // First row for idle
            break;
        case WALK:
            row = 1;  // Second row for walking
            break;
        case RUN:
            row = 2;  // Third row for running
            break;
        case DEATH:
            row = 3;  // Fourth row for dying
            break;

        case ATTACKING:
            row = 4; //fifth row for attacking
            break;

        case RISING:
            row = 5; //sixth row for rising
            

    }

    Rectangle sourceRec = {
        static_cast<float>(currentFrame * frameWidth),  // x position in the sprite sheet
        static_cast<float>(row * frameHeight),          // y position in the sprite sheet
        static_cast<float>(frameWidth),                 // Width of the frame
        static_cast<float>(frameHeight)                 // Height of the frame
    };

    // Flip the texture if the NPC is facing left
    if (!facingRight) {
        sourceRec.width = -frameWidth;  // Flip horizontally
    }

    // Draw the texture at the NPC's position
    // Tint the NPC red if recently hit
    Color tint = (hitTimer > 0) ? RED : WHITE;
    DrawTextureRec(texture, sourceRec, position, tint);
}

void NPC::SetAnimationState(AnimationState newState) {
    if (currentAnimation != newState) {
        currentAnimation = newState;
        currentFrame = 0;  // Reset to the first frame of the new animation
        frameCounter = 0.0f;  // Reset the frame counter
    }
}

void NPC::ClickNPC(Vector2 mousePosition, Camera2D& camera, Player& player){

    if (talkTimer > 0){
        talkTimer -= GetFrameTime();
        talked = true;
    }else{
        talked = false;
        interacting = false;
    }

    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera); // Oustide we need to get screentoworld
    float hitboxWidth = 16.0f;   // Width of the hitbox 
    float hitboxHeight = 32.0f; 
    
    Rectangle npcHitbox = {
        position.x+16,   // Center horizontally
        position.y,  
        hitboxWidth,  // Width of hitbox
        hitboxHeight                    
    };

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ // it seems dumb to get input inside the NPC class, but here we are.  
        if (CheckCollisionPointRec(mouseWorldPos, npcHitbox)){
            float distance = abs(mouseWorldPos.x - player.position.x);
            if (distance < 75){ // NPC must be close to interact
                HandleNPCInteraction();
                
            }

        }
    }
}

bool NPC::CheckHit(Vector2 previousBulletPosition, Vector2 currentBulletPosition, Vector2 bulletSize) {
    // Define a hitbox around the NPC (centered on the NPC's position)
    float hitboxWidth = 8.0f;   // Width of the hitbox (adjust as needed)
    float hitboxHeight = 32.0f; // Height of the hitbox (adjust as needed)

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


void NPC::TakeDamage(int damage) {
    health -= damage;
    hitTimer = 0.3f; // Tint the sprite red for 0.3 seconds
    int soundIndex = rand() % 4;
    switch (soundIndex){
        case 0:
            //SoundManager::getInstance().GetSound("zhit1");  // Access the sound directly
            PlaySound(SoundManager::getInstance().GetSound("zhit1"));
            break;
        case 1:
            PlaySound(SoundManager::getInstance().GetSound("zhit2"));
            break;

        case 2:
            PlaySound(SoundManager::getInstance().GetSound("zhit3"));
            break;
        
        case 3:
            PlaySound(SoundManager::getInstance().GetSound("zhit4"));
            break;

    }


    if (health <= 0 && !isDying) {
        PlaySound(SoundManager::getInstance().GetSound("zombieDeath"));
        riseTimer = 0; //if killed while still rising set the risetimer back to 0 as to not play rise animation
        isDying = true;           // Start dying process
        SetAnimationState(DEATH);  // Set to death animation
        deathTimer = 0.85f;        // Set death animation duration
        destination = position; //zombie is at it's destination on death as to not play walk animation
    }
}
