// NPC.cpp
#include "NPC.h"
#include "Player.h"
#include "Bullet.h"
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
    targetNPC = nullptr; //set in main
    CanSpawnZombie = true; //everytime a NPC dies it spawns a zombie? //only in the park
    detectionRange = 300.0f;  // Set detection range for zombies
    detectionRangeBat = 150;
    highLight = false;
    robot = false;
    can_shoot = true;
    shootTimer = 0.0f;
    validPassword = false;
 
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

void NPC::HandleNPCInteraction(Player& player, GameState& gameState){ //Click or KEY_UP on NPC

        destination = position;//Stop NPC
        interacting = true;
        //idleTime = 5;
        if (dealer) idleTime = 10;
        //if (teller) idleTime = 10;

        if (talkTimer > 0){ //click while countdown is going// works for all NPCs? could be trouble
            talkTimer = 0; //If you click while the hobo is talking, skip the dialog by seting talk timer to 0
        } 

        if (!attacking) SetAnimationState(IDLE);

        if (!talked && teller){
            talked = true;
            speech = "Fortune: $100";
            talkTimer = 5;
            idleTime = 5; //do we really need both talktimer and idletime, talkTimer is the time the dialog is displayed before erasing. 
            //Idle time is how long the NPC stays stationary before picking a new destination. 
        }

        if (!talked && MiB && gameState == PARK){ //trigger zombies elsewhere? in renderpark, might make more sense here. 
            talked = true;
            speech = "We are Watching You";
            talkTimer = 5;
            idleTime = 5;

        }

        if (!talked && robot && !agro){ //dont talk to angry robots
            talked = true;
            speech = "Beep Boop";
            talkTimer = 5;
            idleTime = 10;

           

            if (interactions == 0 && !validPassword){ //an interaction is a series of sentences said by the NPC, once all the dialog is displayed we increment interactions
            //then wait to trigger the next set of dialogs. 


                clickCount += 1;
                switch (clickCount){
                    case 1:
                        speech = "Password?";
                        break;
                    case 2:

                        speech = "Invalid Password";
                        break;
                    case 3:
                        speech = "Intruder Detected!";
                        break;
                    case 4:
                        if (!validPassword){
                            speech = "Terminate Intruder";
                            agro = true;
                            idleTime = 2;
                            
                            facingRight = (player.position.x > position.x); //turn toward player
                            break;


                        }else{
                            interactions += 1;
                        }
                    
                }
                
            }
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
                        SoundManager::getInstance().StartRandomVoices(1);
                        speech = "GaaHh, what do you want?";
                        break;
                    case 2:
                        SoundManager::getInstance().StartRandomVoices(2);
                        speech = "wait...\n\nyou're not like the others";
                        break;
                    case 3:
                        SoundManager::getInstance().StartRandomVoices(1);
                        speech = "maybe you'll believe me";
                        break;

                    case 4:
                        SoundManager::getInstance().StartRandomVoices(2.5);
                        speech = "I was in the graveyard last night\n\nI saw something...";
                        break;

                    case 5:
                        speech = "..."; //pause for dramatic effect. 
                        
                        break;

                    case 6:
                        SoundManager::getInstance().StartRandomVoices(2);
                        speech = "The DEAD were RISING\n\nfrom their GRAVES!";
                        break;

                    case 7:
                        SoundManager::getInstance().StartRandomVoices(2.5);
                        speech = "I dropped my SHOVEL and\n\ngot the hell out of there";
                        break;

                    case 8:
                        SoundManager::getInstance().StartRandomVoices(2);
                        speech = "I'd stay away from there\n\nif I was you";
                        break;

                    case 9:
                        speech = "...";
                        interactions = 1; //load second interaction
                        clickCount = 0; //reset click count for another round
                        break;

                } 
            }else if (interactions == 1 && player.hasShovel){ //youve seen all of the first interaction text, and you have the shuffle. 
                clickCount += 1;
                switch(clickCount){
                    
                    case 1:
                        SoundManager::getInstance().StartRandomVoices(1);
                        speech = "I see you've found my shovel";
                        break;
                    case 2:
                        speech = "You saw them too...\n\nThe Walking Dead";
                        SoundManager::getInstance().StartRandomVoices(2);
                        break;
                    case 3:
                        SoundManager::getInstance().StartRandomVoices(2);
                        speech = "They are gathering\n\nin the cemetery before...";
                        break;
                    case 4: 
                        speech = "I've tried to warn the police\n\nthey just laughed at me";
                        SoundManager::getInstance().StartRandomVoices(2);
                        break;
                    case 5:
                        speech = "You've got to stop them\n\n before they invade the city";
                        SoundManager::getInstance().StartRandomVoices(2.5);
                        break;
                    case 6:
                        SoundManager::getInstance().StartRandomVoices(1);
                        speech = "Here is the KEY to the cemetery";
                        
                        break;

                    case 7:
                        speech = "Find the source of the zombies";
                        SoundManager::getInstance().StartRandomVoices(1);
                        break;

                    case 8:
                        speech = "There is an old shotgun buried over there\n\nYour gonna need it";
                        SoundManager::getInstance().StartRandomVoices(2);
                        break;

                    case 9:
                        SoundManager::getInstance().StartRandomVoices(1);
                        speech = "WE ARE DOOMED!"; // repeats we are dooomed.
                        interactions = 2; //load 3rd interaction
                        clickCount = 0; //reset click count for another round
                        break;

                }
            }else if (interactions == 2 && player.hasBadge){ //youve seen all of the second interaction text and you have the badge. 
                clickCount += 1;
                switch(clickCount){
                    case 1:
                        speech = "Where did you find this ID card?";
                        SoundManager::getInstance().StartRandomVoices(1);
                        break;

                    case 2:
                        speech = "NecroTech? That's my old employer";
                        SoundManager::getInstance().StartRandomVoices(1.5);
                        break;

                    case 3:
                        speech = "I got fired when I wouldn't go along with their\n\nWorld domination plans";
                        SoundManager::getInstance().StartRandomVoices(2);
                        break;
                    
                    case 4:
                        speech = "I should have known they were behind this";
                        SoundManager::getInstance().StartRandomVoices(1);
                        break;

                    case 5:
                        speech = "You got a computer?";
                        SoundManager::getInstance().StartRandomVoices(1);
                        break;

                    case 6:
                        speech = "Find NecroTech HQ\n\nPut a stop to their evil plans"; //repeats
                        SoundManager::getInstance().StartRandomVoices(2.5);
                        break;
                    

                }


            }      
        }

        if (!talked && !hobo && !police && !teller and !robot){ //all other NPCs
            SoundManager::getInstance().StartRandomVoices(.5);
            talked = true;
            speech = GetRandomPhrase(); // NPC greets player
            talkTimer = 3; //limit talking. 
            idleTime = 3;
        }
        
    }

void NPC::HandleGhost(Player& player, float& distanceToPlayer){ //Also Bats. should probably rename or make it a seperate func handleBats()

    float distanceY = abs(player.position.y - position.y); //flying enemies need a Y axis
    //float distanceToBat = Vector2Distance(position, player.position);
    
    if ((ghost || bat) && distanceToPlayer < 400){
        hasTarget = true;
        if (bat) agro = true; //bats are always angry
        
        if (agro){
            destination = player.position;
        }   

    }

    if (ghost){
        frameSpeed = 8;
        attacking = false;

    }



    if ((bat || ghost) && distanceToPlayer <= 25 && distanceY < 25 && !isDying && agro){ //check distanceY as well
        
        attacking = true;

        if (player.hitTimer <= 0){
            player.take_damage(10);
            PlaySound(SoundManager::getInstance().GetSound("boneBreak")); 
        }
        frameSpeed = 14; //faster swing
        SetAnimationState(ATTACKING);
    }


}

void NPC::HandleZombie(Player& player, float& distanceToPlayer){
    if (!isActive) return; 
    if (isZombie) hasTarget = false; //was setting hasTarget to false for police
    float distToDest = fabs(position.x - destination.x);
    if (isZombie) attacking = false;

    if (isZombie && distanceToPlayer < detectionRange && riseTimer <= 0) {
        hasTarget = true; //if hasTarget dont go idle
        destination = player.position;  // Move towards the player
        
    }

    if (isZombie && distanceToPlayer < 10.0f && riseTimer <= 0 && !isDying) { //zombie attack
        attacking = true;
        destination = position;
        if (player.hitTimer <= 0){
            player.take_damage(10);
            SoundManager::getInstance().PlayPositionalSound("boneBreak", position, player.position, 500);
            //PlaySound(SoundManager::getInstance().GetSound("BoneCrack")); 
        }
        
        SetAnimationState(ATTACKING);  // Switch to attacking animation

    }

    if (targetNPC == nullptr && isZombie && !hasTarget && distToDest < 1){
        //SetDestination(1000, 4000);
        idleTime = 1;
        
    }

    if (targetNPC != nullptr && riseTimer <= 0){
        //if (!targetNPC->isActive) return;
        float distToNPC = fabs(targetNPC->position.x - position.x);
        if (distToNPC < 15 && !isDying){
            
            attacking = true;

            
            if (targetNPC->hitTimer <= 0){
                targetNPC->TakeDamage(25, player);
                if (!SoundManager::getInstance().IsSoundPlaying("boneBreak")){
                     SoundManager::getInstance().PlayPositionalSound("boneBreak", position, player.position, 200);

                }
                
            }
            SetAnimationState(ATTACKING);  // Switch to attacking animation

            if (distToNPC < 10){  //wait till your within attack range before stopping. 
                destination = position;

            }

        if (targetNPC->health <= 0){

            targetNPC = nullptr;

            SetAnimationState(IDLE);
            
            return; //Needed return here to stop seg fault. because code continues to run if health <= 0.
            
                

            }

            
        }
    }

}

void NPC::HandleMiB(Player& player, float& distanceToPlayer){
    //MIB follow player up to a point then stops and waits. 
    if (MiB && distanceToPlayer < 1000 && !hasTarget){
        destination = player.position; //move toward player
        hasTarget = true; //dont go idle
    }
    if (MiB && distanceToPlayer <= 125 && hasTarget){
       
        destination = position; //stop a ways away
        SetAnimationState(IDLE);
    }
}

void NPC::HandleRobot(Player& player, float& distanceToPlayer){
    attacking = false;
    //agro = true;
    if (robot && distanceToPlayer < detectionRange && agro){
        hasTarget = true;
        destination = player.position;
        speed = 75;

    }

    if (distanceToPlayer < 150 && agro){
        destination = position;
        //shoot
        if (can_shoot && !isDying){
            SoundManager::getInstance().PlayPositionalSound("laser", position, player.position, 500);
            can_shoot = false;
            NPCfireBullet(*this, false, 10, true);
            shootTimer = 1.0f;

        }
        
    }

    if (shootTimer > 0){
        shootTimer -= GetFrameTime();
    }else{
        can_shoot = true;
    }

}

void NPC::HandlePolice(Player& player, float& distanceToPlayer){
    attacking = false;
    if (police && distanceToPlayer < detectionRange && agro){ //police chase player
        hasTarget = true;
        destination = player.position;
        speed = 75;
        frameSpeed = 14; //speed up animation for attacking and chasing. 
        

    }
    if (police && distanceToPlayer >= detectionRange && agro && !attacking){ //police loose player
        agro = false;
        speed = 50;
        hasTarget = false;
        destination = position;
        idleTime = 1;
        frameSpeed = 8.0; //reset animation speed
    }



    if (police && distanceToPlayer < 20.0f && hasTarget && agro && !player.isDead){ // police attack player
        idleTime = 0.0f; //transition to idle before attacking so it doesn't flicker. 
        destination = position;
        attacking = true;
        frameSpeed = 12; //faster swing.
        if (player.can_take_damage && currentFrame == 5){ //only hit on frame 5. 
            player.take_damage(10);
            
            PlaySound(SoundManager::getInstance().GetSound("BoneCrack"));
        }

        SetAnimationState(ATTACKING);
        
    }
}


// Function to set a new random destination within a specified range
void NPC::SetDestination(float minX, float maxX) {
    destination.x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxX - minX)));
    destination.y = position.y;  // Keep the same y position
    facingRight = (destination.x > position.x);  // Determine facing direction
}


void NPC::HandleAnimationLogic(){
        // Update frame counter and animation logic
    frameCounter += GetFrameTime() * frameSpeed; //Higher frameSpeed means frameCounter increases more each frame.
    
    if (frameCounter >= 1.0f) { 
        frameCounter = 0.0f;
        currentFrame++;

        // Determine the number of frames based on the current animation
        int numFrames = 0;
        switch (currentAnimation) {
            case IDLE:
                numFrames = 1; // 1 frame for idle
                if (ghost || bat || robot) numFrames = 7; //ghost idle is 7 frames
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

}

void NPC::Update(Player& player, GameState& gameState) {
    if (!isActive) return;  // Skip update if the NPC is not active
    if (!isZombie) riseTimer = 0;
    float distance_to_player = abs(player.position.x - position.x);

    if (distance_to_player >= 30){
        highLight = false;//Turn off highlights on any interacting NPCs when far enough way. 
        interacting = false; // maybe this is a good idea
    }

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
        if (ghost) ghostAlpha = hitTimer / .3; //ghost becomes fully transparent on hit. 
        if (ghost) ghostAlpha = Clamp(ghostAlpha, 0.0f, 1.0f); 
        
    }else{
        ghostAlpha += 0.1; //is this redundant? ghostAlpha should tic up as hitTimer becomes smaller.
        
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

    HandleAnimationLogic();

    // If NPC is idle, reduce idle time
    if (idleTime > 0) {
        idleTime -= GetFrameTime();
        return;  // Remain idle until idleTime runs out
    }
    if (idleTime <= 0) interacting = false; // NPCs stop interacting when IdleTime is up. 

  

    // Check if the player is within a certain range to chase
    float distanceToPlayer = Vector2Distance(position, player.position);
    hasTarget = false; //reset hasTarget incase we loose
    attacking = false;

    if (MiB) HandleMiB(player, distance_to_player);
    if (police) HandlePolice(player, distance_to_player); //handle distance checks and attack logic. 
    if (isZombie) HandleZombie(player, distance_to_player);
    if (ghost || bat) HandleGhost(player, distance_to_player); //also bats
    if (robot) HandleRobot(player, distance_to_player);

    Vector2 directionToPlayer = {
    player.position.x - position.x,
    player.position.y - position.y
};

    directionToPlayer = Vector2Normalize(directionToPlayer);


    //NPCs choose a random position called destination. they move toward destination until they arrive then wait a random amount of time and repeat 
    if (!isDying && riseTimer <= 0 && !attacking) { //MOVE NPCs and Police and Zombies and Ghosts. 
        // Move towards the destination

        if (!ghost && !bat){ //pedestrians on the street/zombies
           
            if (position.x < destination.x) {
                position.x += speed * GetFrameTime();
                facingRight = true;
                SetAnimationState(WALK);
               
            } else if (position.x > destination.x) {
                position.x -= speed * GetFrameTime();
                facingRight = false;
                SetAnimationState(WALK);
                
            
            }
        }else if (bat || ghost) {
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

        if (fabs(position.x - destination.x) < 5.0f && !hasTarget && !isZombie && !attacking) { //Pedestrians
            // Reached destination, go idle for a moment, then set a new destination
            idleTime = 3.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 2.0f));  // 3-6 seconds of idle time

            SetAnimationState(IDLE);
            
            
            if (hobo){
                SetDestination(2550, 2600); // hobo stays near middle
            }else if (ghost){
                SetDestination(1024, 1800); //ghost stays on far left of cemetery
            }else if (robot){
                SetDestination(1600, 2631);
            } else{
                SetDestination(1000, 3500);  //Pedestrians Outside
                
            }

        
        }

        if (isZombie && distanceToPlayer >= detectionRange && fabs(position.x - destination.x) < 5){ //at destination and zombie and no target
            
            SetDestination(1000, 4000); //wander around if player is far away
        }

        if (fabs(position.x - destination.x) < 5.0f && hasTarget && isZombie){ //destination = targetNPC pos or player pos when has target is true
            destination = position; //zombie stop while attacking
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

    Rectangle sourceRec = { //currentFrame gets cycled in handleAnimationLogic. 0-row.size()
    //we are looping through frames in a certain row depending on the gamestate
        static_cast<float>(currentFrame * frameWidth),  // x position in the sprite sheet
        static_cast<float>(row * frameHeight),          // y position in the sprite sheet
        static_cast<float>(frameWidth),                 // Width of the frame
        static_cast<float>(frameHeight)                 // Height of the frame
    };

    // Flip the texture if the NPC is facing left
    if (!facingRight) {
        sourceRec.width = -frameWidth;  // Flip horizontally
    }

    if (interacting){
        highLight = true;
    }

    // Draw the texture at the NPC's position
    // Tint the NPC red if recently hit
    Color tint = (hitTimer > 0) ? RED : WHITE;
    if (ghost) tint = ColorAlpha(WHITE, ghostAlpha);//use Color alpha to change alpha of ghost on hit
    if (bat) BeginShaderMode(shaders.rainbowOutlineShader); //raindbow bats
    if (highLight) BeginShaderMode(shaders.highlightShader);
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
    if (!isActive) return; //dont click on inactive NPCs 

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
    
    Rectangle npcHitbox = { // Hit box for mouse clicks
        position.x+24,      // Center horizontally
        position.y+16,      //Center vertically
        hitboxWidth,  
        hitboxHeight                    
    };

    //DrawRectangleLines(position.x+24, position.y+16, hitboxWidth, hitboxHeight, RED); // debug show hitbox
    //this looks cool. could we use it in game for something? instead of current highlight just draw a red box around interacting NPC, nah.

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


void NPC::TakeDamage(int damage, Player& player) {
    if (!isDying){
        health -= damage;
        hitTimer = 0.3f; // Tint the sprite red for 0.3 seconds

    }

    int soundIndex = rand() % 4; //returns 0, 1, 2 or 3
    
    if (ghost || bat) agro = true;
    if (!isZombie && !bat && !ghost && !robot){
        destination = position; //if your an NPC, stop when you take damage so we can play the death animation. 
        
    }

    if (robot && !agro){ //Robot agros on hit
        agro = true;
        destination = player.position;//move toward player
        idleTime = 0; //stop being idle 
        facingRight = (player.position.x > position.x); //face the player

    }

    if (isZombie){
        switch (soundIndex){ //zombie hits
            case 0:
                //SoundManager::getInstance().GetSound("zhit1");  // Access the sound directly
                //PlaySound(SoundManager::getInstance().GetSound("zhit1"));
                SoundManager::getInstance().PlayPositionalSound("zhit1", position, player.position, 500);
                break;
            case 1:
                //PlaySound(SoundManager::getInstance().GetSound("zhit2"));
                SoundManager::getInstance().PlayPositionalSound("zhit2", position, player.position, 500);
                break;

            case 2:
                //PlaySound(SoundManager::getInstance().GetSound("zhit3"));
                SoundManager::getInstance().PlayPositionalSound("zhit3", position, player.position, 500);
                break;
            
            case 3:
                //PlaySound(SoundManager::getInstance().GetSound("zhit4"));
                SoundManager::getInstance().PlayPositionalSound("zhit4", position, player.position, 500);
                break;

        }
    }


    if (health <= 0 && !isDying && isZombie) {
        //PlaySound(SoundManager::getInstance().GetSound("zombieDeath"));
        SoundManager::getInstance().PlayPositionalSound("zombieDeath", position, player.position, 500);
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

    if (health <= 0 && !isDying && robot){
        riseTimer = 0;
        isDying = true;
        SetAnimationState(DEATH);
        //play robot death sound
        SoundManager::getInstance().PlayPositionalSound("explosion", position, player.position, 500);
        destination = position;
        deathTimer = .85f;

    }

    if (health <= 0 && !isDying && !robot){ //NPC killed by zombie

        riseTimer = 0; 
        isDying = true;           // Start dying process   
        SetAnimationState(DEATH);  // Set to death animation
        SoundManager::getInstance().PlayPositionalSound("deathScream", position, player.position, 500);
        deathTimer = 0.85f;        // Set death animation duration // needs to be exact
        destination = position; 
        
    }

}
