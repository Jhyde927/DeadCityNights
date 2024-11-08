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
#include "shaderControl.h"

float detectionRange = 200.0f;  // Set detection range for zombies
float detectionRangeBat = 150;



// Constructor 
NPC::NPC(Texture2D npcTexture, Vector2 startPos, float npcSpeed, AnimationState initialAnimation, bool active, bool zombie)
{
    texture = npcTexture;
    position = startPos;
    speed = npcSpeed;
    currentAnimation = initialAnimation;
    isActive = active;
    isZombie = zombie;

    frameCounter = 0;
    frameSpeed = 8.0f;
    currentFrame = 0;
    facingRight = true;
    patrollingRight = rand() % 2 == 0;  // Randomly set initial direction
    patrolling = false;                 // Default to not patrolling
    idleTime = 0;                       // Initialize idle time
    maxHealth = 75;                     // Initialize max health
    health = maxHealth;                 // Initialize current health
    hitTimer = 0.0f;                    // Initialize hit timer to 0
    isDying = false;                    // Initialize dying state to false
    riseTimer = 0.9f;
    interacting = false;
    talked = false;
    speech = " ";
    dealer = false;
    police = false;
    agro = false;
    attacking = false;
    hobo = false;
    ghost = false;
    teller = false;
    bat = false;
    MiB = false;
    clickCount = 0;
    interactions = 0;
    talkTimer = 0.0f;
    ghostAlpha = 1.0f;
    deathTimer = 0.0;
    hasTarget = false;
    isTargeted = false;
    NPC* targetNPC = nullptr; //set in main
 
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
        "What's up?",
        
    }; 

    // Get a random index
    int randomIndex = rand() % phrases.size();

    return phrases[randomIndex];
}

void NPC::HandleNPCInteraction(Player& player, GameState& gameState){
        destination = position;//Stop NPC
        interacting = true;
        //idleTime = 5;
        if (dealer) idleTime = 10;
        //if (teller) idleTime = 10;

        if (talkTimer > 0){ //click while countdown is going// works for all NPCs? could be trouble
            talkTimer = 0; //If you click while the hobo is talking, skip the dialog by seting talk timer to 0
        } 

        SetAnimationState(IDLE);

        if (!talked && teller){
            talked = true;
            speech = "Fortune: $100";
            talkTimer = 5;
            idleTime = 5;
        }

        if (!talked && MiB && gameState == PARK){
            talked = true;
            speech = "We are Watching You";
            talkTimer = 5;
            idleTime = 5;

        }

        if (!talked && ghost){
            talked = true;
            idleTime = 4;
            talkTimer = 4;
            if (interactions == 0){
                clickCount += 1;
                switch (clickCount){
                    case 1:
                        speech = "BOOOOO";
                        break;

                    case 2:
                        speech = "My essence lingers bound by time\n\nunlock the door with altered mind.";
                        break;

                    case 3:
                        speech = "In shadows deep where spirits roam\n\na relic waits to lead me home.";
                        break;

                    case 4:
                        speech = "BOOOO!";
                        clickCount = 0;
                        break;
                }
            }



        }

        if (police && !talked){
            talked = true;
            speech = (rand() % 2 == 0) ? "Freeze!" : "Halt!";
            talkTimer = 1;
            idleTime = 1;
            agro = true;
        }



        if (hobo && !talked){
            talked = true;

            idleTime = 3; //stops NPC while talking
            talkTimer = 3; // ensures this only runs once
            if (interactions == 0){
                clickCount += 1;
                switch (clickCount){
                    case 1:
                        speech = "GaaHh, what do you want?";
                        break;
                    case 2:
                        speech = "wait...\n\nyou're not like the others";
                        break;
                    case 3:
                        speech = "maybe you'll believe me";
                        break;

                    case 4:
                        speech = "I was in the graveyard last night\n\nI saw something...";
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
                        interactions = 1;
                        clickCount = 0;
                        break;

                } 
            }else if (interactions == 1 && player.hasShovel){
                clickCount += 1;
                switch(clickCount){
                    
                    case 1:
                        speech = "I see you've found my shovel";
                        break;
                    case 2:
                        speech = "You saw them too...\n\nThe Walking Dead";
                        break;
                    case 3:
                        speech = "They are gathering\n\nin the cemetery before...";
                        break;
                    case 4: 
                        speech = "I've tried to warn the police\n\nthey just laughed at me";
                        break;
                    case 5:
                        speech = "You've got to stop them\n\n before they invade the city";
                        break;
                    case 6:
                        speech = "Here is the KEY to the cemetery";
                        
                        break;

                    case 7:
                        speech = "Find the source of the zombies";
                        break;

                    case 8:
                        speech = "There is an old shotgun buried over there\n\nYour gonna need it";
                        break;

                    case 9:
                        speech = "WE ARE DOOMED!";
                        interactions = 2;
                        clickCount = 0;
                        break;

                }
            }else if (interactions == 2 && player.hasBadge){
                clickCount += 1;
                switch(clickCount){
                    case 1:
                        speech = "Where did you find this ID card?";
                        break;

                    case 2:
                        speech = "NecroTech? That's my old employer";
                        break;

                    case 3:
                        speech = "I got fired when I wouldn't go along with their\n\nWorld domination plans";
                        break;
                    
                    case 4:
                        speech = "I should have known they were behind this";
                        break;

                    case 5:
                        speech = "You got a computer?";
                        break;

                    case 6:
                        speech = "Find NecroTech HQ\n\nPut a stop to their evil plans";
                        break;
                    

                }


            }      
        }

        if (!talked && !hobo && !police && !teller){
            talked = true;
            speech = GetRandomPhrase(); // NPC greets player
            talkTimer = 5; //limit talking. 30 second cooldown
            idleTime = 5;
        }
        
    }

void NPC::HandleGhost(Player& player, float& distanceToPlayer){

    float distanceY = abs(player.position.y - position.y); //flying enemies need a Y axis
    //float distanceToBat = Vector2Distance(position, player.position);
    
    if ((ghost || bat) && distanceToPlayer < 400){
        if ((ghost || bat)){
            hasTarget = true;
            if (bat) agro = true;
            
            destination = player.position;

        }

    }

    frameSpeed = 8;
    attacking = false;

    if ((bat || ghost) && distanceToPlayer <= 25 && distanceY < 25 && !isDying && agro){ //check distanceY as well
        
        attacking = true;

        if (player.hitTimer <= 0){
            player.take_damage(10);
            PlaySound(SoundManager::getInstance().GetSound("BoneCrack")); 
        }
        frameSpeed = 14; //faster swing
        SetAnimationState(ATTACKING);
    }


}

void NPC::HandleZombie(Player& player, float& distanceToPlayer){
    if (!isActive) return; 

    float distToDest = fabs(position.x - destination.x);
    attacking = false;

    if (isZombie && distanceToPlayer < detectionRange && riseTimer <= 0) {
        hasTarget = true; //if hasTarget dont go idle
        destination = player.position;  // Move towards the player
        
    }

    

   
    if (isZombie && distanceToPlayer < 10.0f && riseTimer <= 0 && !isDying) { //zombie attack
        attacking = true;
        destination = position;
        if (player.hitTimer <= 0){
            player.take_damage(10);
            PlaySound(SoundManager::getInstance().GetSound("BoneCrack")); 
        }
        
        SetAnimationState(ATTACKING);  // Switch to attacking animation

    }

    if (targetNPC == nullptr && !hasTarget && distToDest < 1){
        SetDestination(1000, 4000);
        
        
    }

    if (targetNPC != nullptr && riseTimer <= 0){
        //if (!targetNPC->isActive) return;
        float distToNPC = fabs(targetNPC->position.x - position.x);
        if (distToNPC < 15 && !isDying){
            
            attacking = true;

            
            if (targetNPC->hitTimer <= 0){
                targetNPC->TakeDamage(25);
            
                //PlaySound(SoundManager::getInstance().GetSound("BoneCrack"));
                
            }
            SetAnimationState(ATTACKING);  // Switch to attacking animation

            if (distToNPC < 10){  //wait till your within attack range before stopping. 
                destination = position;

            }

        if (targetNPC->health <= 0){
            //hasTarget = false;
            //targetNPC->isActive = false;
            targetNPC = nullptr;
            //attacking = false;
                

            }

            
        }
    }



}

void NPC::HandleMiB(Player& player, float& distanceToPlayer){
    //MIB follow player up to a point then stops and waits. 
    if (MiB && distanceToPlayer < 1000){
        destination = player.position; //move toward player
        hasTarget = true; //dont go idle
    }
    if (MiB && distanceToPlayer <= 125 && hasTarget){
        hasTarget = false;
        destination = position; //stop a ways away
        SetAnimationState(IDLE);
    }
}

void NPC::HandlePolice(Player& player, float& distanceToPlayer){
    if (police && distanceToPlayer < detectionRange && agro && !attacking){ //police chase player
        hasTarget = true;
        destination = player.position;
        speed = 75;
        frameSpeed = 14; //speed up animation for attacking and chasing. 
        

    }else if (police && distanceToPlayer >= detectionRange && agro && !attacking){ //police loose player
        agro = false;
        speed = 50;
        hasTarget = false;
        destination = position;
        idleTime = 1;
        frameSpeed = 8.0; //reset animation speed
    }

    if (police && distanceToPlayer < 10.0f && hasTarget && agro && !player.isDead){
        float t = 0.5;
        if (player.stunTimer <= 0){
            player.stunPlayer(t);
            

        }
        
    }


    if (police && distanceToPlayer < 20.0f && hasTarget && agro && !player.isDead){ // police attack player
        idleTime = 0.0f; //transition to idle before attacking so it doesn't flicker. 
        destination = position;
        attacking = true;
        frameSpeed = 24;
        if (player.can_take_damage && currentFrame == 5){ //only hit on frame 5. 
            player.take_damage(10);
            
            PlaySound(SoundManager::getInstance().GetSound("BoneCrack"));
        }

        SetAnimationState(ATTACKING);
    }else if (police && distanceToPlayer >= 20.0f && hasTarget){ //player leaves attack area
        
        attacking = false;
    }
}


// Function to set a new random destination within a specified range
void NPC::SetDestination(float minX, float maxX) {
    destination.x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxX - minX)));
    destination.y = position.y;  // Keep the same y position
    facingRight = (destination.x > position.x);  // Determine facing direction
}

void NPC::Update(Player& player, GameState& gameState) {
    if (!isActive) return;  // Skip update if the NPC is not active
    if (!isZombie) riseTimer = 0;
    float distance_to_player = abs(player.position.x - position.x);


    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        if (distance_to_player < 20 && !police && !isZombie){
            HandleNPCInteraction(player, gameState);
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
        if (ghost) ghostAlpha = hitTimer / .3; //ghost becomes fully transparent on hit. tics down with hit timer .3 seconds.
        if (ghost) ghostAlpha = Clamp(ghostAlpha, 0.0f, 1.0f); 
        
    }else{
        ghostAlpha += 0.1;
        
        if (ghostAlpha >= 1.0f){
            ghostAlpha = 1.0f;
        }
    }

    // Handle death logic
    if (isDying) { //death animation plays wile isDying is true
        deathTimer -= GetFrameTime();

        if (deathTimer <= 0.0f) {
            isActive = false;  // Set NPC as inactive after death animation
            isDying = false; //set dying back to false once dead.
            speech = ""; //dead men don't talk
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
                numFrames = 1; // 1 frame for idle
                if (ghost || bat) numFrames = 7; //ghost idle is 7 frames
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
                numFrames = 7; // 7 frames for attacking
                break;

            case RISING:    // 7 frame for rising      
                numFrames = 7;
                break;

            case DEATH2:
                numFrames = 7; // 7 frames for dying2
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
    hasTarget = false; //reset hasTarget before setting in below
    attacking = false;

    HandleMiB(player, distance_to_player);
    HandlePolice(player, distance_to_player); //handle distance checks and attack logic. 
    HandleZombie(player, distance_to_player);
    HandleGhost(player, distance_to_player); //also bats

    Vector2 directionToPlayer = {
    player.position.x - position.x,
    player.position.y - position.y
};

    directionToPlayer = Vector2Normalize(directionToPlayer);


    //NPCs choose a random position called destination. they move toward destination until they arrive then repeat. 
    if (!isDying && riseTimer <= 0 && !attacking) { //MOVE NPCs and Police and Zombies and Ghosts. 
        // Move towards the destination

        if (!ghost && !bat){
            if (position.x < destination.x) {
                position.x += speed * GetFrameTime();
                facingRight = true;
                SetAnimationState(WALK);
            } else if (position.x > destination.x) {
                position.x -= speed * GetFrameTime();
                facingRight = false;
                SetAnimationState(WALK);
            }
        }else if (bat) {
            if (agro && hasTarget) {
                float deltaTime = GetFrameTime(); // Get the frame time

                Vector2 velocity = {0.0f, 0.0f};

                float yDifference = destination.y - position.y;
                float xDifference = destination.x - position.x;

                float yThreshold = 5.0f; // Adjust as needed

                if (fabs(yDifference) > yThreshold) {
                    // Move vertically towards the player's Y position
                    velocity.y = (yDifference > 0 ? 1.0f : -1.0f) * 75;
                    // Do not move horizontally yet
                    velocity.x = 0.0f;
                } else {
                    // Once aligned in Y, move horizontally towards the player
                    velocity.x = (xDifference > 0 ? 1.0f : -1.0f) * 75;
                    velocity.y = 0.0f;

                    // Set facing direction
                    facingRight = (velocity.x > 0);
                }

                // Update position
                position.x += velocity.x * deltaTime;
                position.y += velocity.y * deltaTime;

                // Set animation state
                if (!isDying) SetAnimationState(WALK); // Or another appropriate state
            } else {
                SetAnimationState(IDLE);
            }
        }

        // Check if destination is reached
        if (fabs(position.x - destination.x) < 5.0f && !hasTarget && !isZombie) { //dont go idle if your zombie and you have reached destination
            // Reached destination, go idle for a moment, then set a new destination
            idleTime = 3.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f));  // 3-6 seconds of idle time
            
            SetAnimationState(IDLE);

            // Only set a new random destination if not chasing the player
            if (!isZombie || distanceToPlayer >= detectionRange) {
                if (hobo){                   
                    SetDestination(2550, 2600); // hobo stays near center
                }else if (ghost){
                    SetDestination(1024, 1800); //ghost stays on far left of cemetery
                }
                else{
                    SetDestination(1000, 3500);  //Pedestrians Outside 
                }
                
            }   
        
        }
        if (fabs(position.x - destination.x) < 5.0f && hasTarget && isZombie){
            destination = position;
        }

    }
}

void NPC::Render(ShaderResources& shaders) {
    if (!isActive) return;  // Skip rendering if the NPC is not active. NPC still exists though

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
            break;

        case DEATH2:
            row = 6; // seventh row for dying2
            break;
            

    }

    Rectangle sourceRec = { //
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
    if (ghost) tint = ColorAlpha(WHITE, ghostAlpha);//use Color alpha to change alpha of ghost on hit
    if (bat) BeginShaderMode(shaders.rainbowOutlineShader);
    DrawTextureRec(texture, sourceRec, position, tint);
    EndShaderMode();
}

void NPC::SetAnimationState(AnimationState newState) {
    if (currentAnimation != newState) {
        currentAnimation = newState;
        currentFrame = 0;  // Reset to the first frame of the new animation
        frameCounter = 0.0f;  // Reset the frame counter
    }
}

void NPC::ClickNPC(Vector2 mousePosition, Camera2D& camera, Player& player, GameState& gameState){

    if (talkTimer > 0){
        talkTimer -= GetFrameTime();
        talked = true; //talk and then wait for player to read message. 

    }else{
        talked = false;
        interacting = false; //NPC are only interacting if talk timer is positive.
    }

    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera); // Oustide we need to get screentoworld
    float hitboxWidth = 16.0f;   
    float hitboxHeight = 32.0f;  //Tall rectange to cover the sprite. 
    
    Rectangle npcHitbox = {// Hit box for mouse clicks
        position.x+24,   // Center horizontally
        position.y+16,  //Center vertically
        hitboxWidth,  // Width of hitbox
        hitboxHeight                    
    };

     //DrawRectangleLines(position.x+24, position.y+16, hitboxWidth, hitboxHeight, RED); // debug show hitbox

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ // it seems dumb to get input inside the NPC class, but here we are.  
        if (CheckCollisionPointRec(mouseWorldPos, npcHitbox)){
            float distance = abs(mouseWorldPos.x - player.position.x);
            if (distance < 75 && !isZombie){ // NPC must be close to interact
                HandleNPCInteraction(player, gameState);
                
            }

        }
    }
}

bool NPC::CheckHit(Vector2 previousBulletPosition, Vector2 currentBulletPosition, Vector2 bulletSize) { 
    //raycasting for better collision detection
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
    int soundIndex = rand() % 4; //returns 0, 1, 2 or 3
    if (ghost || bat) agro = true;
    if (!isZombie && !bat && !ghost){
        destination = position; //if your an NPC, stop when you take damage so we can play the death animation. 
        
    }
    if (isZombie){
        switch (soundIndex){ //zombie hits
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
    }


    if (health <= 0 && !isDying && isZombie) {
        PlaySound(SoundManager::getInstance().GetSound("zombieDeath"));
        riseTimer = 0; //if killed while still rising set the risetimer back to 0 as to not play rise animation
        isDying = true;           // Start dying process
        if (rand() % 2 == 0){
            SetAnimationState(DEATH);  // Set to death animation
        }else{
            SetAnimationState(DEATH2); //randomize deaths
        }

        deathTimer = 0.85f;        // Set death animation duration // needs to be exact
        destination = position; //zombie is at it's destination on death as to not play walk animation
    }

    if (health <= 0 && ghost && !isDying){
        isDying = true;
        deathTimer = 0.3; // same as the fade out time. So the ghost just fades out for good on death. 
        destination = position;
    }

    if (health <= 0 && bat && !isDying){
        isDying = true;
        frameSpeed = 14;
        deathTimer = 0.9;
        destination = position;
        SetAnimationState(DEATH2);
    }

    if (health <= 0 && !isDying && isTargeted){
        std::cout << "NPC DEATH";
        //PlaySound(SoundManager::getInstance().GetSound("zombieDeath"));
        riseTimer = 0; //if killed while still rising set the risetimer back to 0 as to not play rise animation
        isDying = true;           // Start dying process   
        SetAnimationState(DEATH);  // Set to death animation

        deathTimer = 0.85f;        // Set death animation duration // needs to be exact
        destination = position; //zombie is at it's destination on death as to not play walk animation
        
    }

}
