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
#include "Particle.h"
#include "GameEnums.h"
#include "Globals.h"
#include "Grenade.h"



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
    agro = false;
    attacking = false;
    speech = " ";
    dealer = false;
    police = false;
    hobo = false;
    ghost = false;
    teller = false;
    bat = false;
    MiB = false;
    frank = false;
    scientist = false;
    scienceJr = false;
    cyberZombie = false;
 
    alien = false;
    robot = false;
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

    can_shoot = true;
    shootTimer = 0.0f;
    validPassword = false;
    trigger = false;
    lobbyNPC = false;
    zRight = false;
    targetedTimer = 0.0f;
    agroZombie = false;
    distanceToPlayer = 0;

    animationTimer = 0.0;
    isMoving = false;

    // switch(type){ //redundant halfway implemented NPCType. type is still set on creation except for isZombie which is set here. 
    //     case NPCType::ZOMBIE:isZombie = true; break;
    //     case NPCType::ROBOT: robot = true; break;
    //     case NPCType::ALIEN: alien = true; break;
    //     case NPCType::MIB: MiB = true; break;
    //     case NPCType::CYBER_ZOMBIE: cyberZombie = true; break;
    //     case NPCType::GHOST: ghost = true; break;
    //     case NPCType::BAT: bat = true; break;
    //     case NPCType::HOBO: hobo = true; break;
    //     case NPCType::POLICEMAN: police = true; break;
    //     case NPCType::DEALER: dealer = true; break;
    //     case NPCType::TELLER: teller = true; break;
    //     case NPCType::SCIENTIST: scientist = true; break;
    //     case NPCType::JR_SCIENTIST: scienceJr = true; break;
    //     case NPCType::FRANK: frank = true; break;
    //     case NPCType::GENERIC: break;
            
    // }


 
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

void NPC::HandleNPCInteraction(){ //Click or KEY_UP on NPC

        destination = position;//Stop NPC
        interacting = true;
        if (dealer) idleTime = 10;
        

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



        if (!talked && MiB && gameState == PARK){ 
            talked = true;
            speech = "We are Watching You";
            talkTimer = 5;
            idleTime = 5;
            //zombies triggered elsewhere

        }

        if (!talked && scientist){
            talked = true;
            talkTimer = 4;
            idleTime = 4;
            if (interactions == 0){
                clickCount += 1;
                switch (clickCount)
                {
                    case 1:
                        speech = "Ah... a visitor.";
                        break;
                    case 2:
                        speech = "You stand in the presence of progress\n\n of perfection!";
                        break;
                    case 3:
                        speech = "My children, no\n\nmy masterpieces are nearly complete!";
                        break;
                    case 4:
                        speech = "Flesh and steel\n\nmindless yet obedient.\n\nSoon you will see...";
                        break;
                    case 5:
                        speech = "Behold! \n\nMy cybernetically enhanced\n\nSuper soldier!";
                        trigger = true;
                
                        break;

                }
            }
           
        }

        if (!talked && frank && gameState == OFFICE){ //frank the office worker gives some plot
            talked = true;
            talkTimer = 3;
            idleTime = 3;
            if (interactions == 0){
                clickCount += 1;
                switch (clickCount)
                {
                case 1:
                    speech = "Are they all dead?";
                    break;

                case 2:
                    speech = "I just work here man!";
                    break;
                
                case 3:
                    speech = "The experiments with the undead\n\nThey went too far!";
                    break;

                case 4:
                    speech = "It's the new CEO\n\nThey say he's a Necromancer";
                    break;
                case 5:
                    speech = "Here is the code for the elevator\n\nThe name's frank by the way";
                    break;

                case 6:
                    speech = "Here, I found this box of ammo";
                    player.autoAmmo = 150;
                    player.shells = 30;
                    PlaySound(SoundManager::getInstance().GetSound("reload"));
                    break;

                case 7:
                    speech = "";
                    interactions += 1;
                    idleTime = 0;
                    talkTimer = 0;
                    break;
                    
                }
            }
        }

        if (!talked && MiB && !agro && gameState == LOBBY){ //talk to a mib in the lobby before fight
            talked = true;
            talkTimer = 3;
            idleTime = 3;
            
            if (interactions == 0 && !agro){
                clickCount += 1;
                switch (clickCount)
                {
                case 1:
                    speech = "You Fool!";
                    break;

                case 2:
                    speech = "You should have\n\nNever come here!";
                    break;

                case 3:
                    speech = "DIE!!!";
                    break;

                case 4:
                    speech = "";
                    agro = true;
                    idleTime = 0;
                    talkTimer = 0;
                    break;
                
                }
            }
        }

        if (!talked && robot && !agro){ //dont talk to angry robots
            talked = true;
            speech = "Beep Boop";
            talkTimer = 5;
            idleTime = 10;

           if (interactions == 0 && validPassword){
                SoundManager::getInstance().PlayRandomRobotVoice();
                speech = "Beep Boop";
           }

            if (interactions == 0 && !validPassword){ //an interaction is a series of sentences said by the NPC, once all the dialog is displayed we increment interactions
            //then wait to trigger the next set of dialogs. 

                clickCount += 1;
                switch (clickCount){
                    case 1:
                        SoundManager::getInstance().PlayRandomRobotVoice();
                        speech = "Password?";
                        break;
                    case 2:
                        SoundManager::getInstance().PlayRandomRobotVoice();
                        speech = "Invalid Password";
                        break;
                    case 3:
                        SoundManager::getInstance().PlayRandomRobotVoice();
                        speech = "Intruder Detected!";
                        break;
                    case 4:
                        if (!validPassword){
                            SoundManager::getInstance().PlayRandomRobotVoice();
                            speech = "Terminate Intruder";
                            agro = true;
                            idleTime = 2;
                            //trigger = true;
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
                        speech = "Six feet deep, my fate was spun \n\nBuried beside my smoking gun.";

                        break;

                    case 5:
                        speech = "BOOOO";
                        clickCount = 0;
                        interactions += 1;
                        break;
                }
            }if (interactions == 1 && player.hasWatch){
                clickCount += 1;
                switch(clickCount){
                    case 1:
                        speech = "The hands of fate now spin anew\n\nA relic lost returns with you.";
                        break;
                    case 2:
                        speech = "By silver light and whispered spell\n\nYou break the curse—I rise, farewell!";
                        break;
                        
                    case 3:
                        interactions = 2;
                        //isActive = false; turned off in main. 
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

        if (alien && !talked){
            talked = true;
            speech = "%^&*@#!";
            talkTimer = 2;
            idleTime = 2;
            SoundManager::getInstance().PlayRandomAlienVoice();

        }



        if (hobo && !talked){
            talked = true;

            idleTime = 3; //stops NPC while talking
            talkTimer = 3; // ensures this only runs once
            if (interactions == 0){
                clickCount += 1;
                switch (clickCount){
                    case 1:
                        //SoundManager::getInstance().PlayRandomVoice();
                        SoundManager::getInstance().StartRandomVoices(1);
                        speech = "GaaHh, what do you want?";
                        break;
                    case 2:
                        //SoundManager::getInstance().PlayRandomVoice();
                        SoundManager::getInstance().StartRandomVoices(2);
                        speech = "wait...\n\nyou're not like the others";
                        break;
                    case 3:
                        SoundManager::getInstance().StartRandomVoices(1);
                        speech = "maybe you'll believe me";
                        break;

                    case 4:
                        SoundManager::getInstance().StartRandomVoices(2);
                        speech = "I was in the graveyard last night\n\nI...saw something";
                        break;

                    case 5:
                        speech = "..."; //pause for dramatic effect. 
                        
                        break;

                    case 6:
                        SoundManager::getInstance().StartRandomVoices(2);
                        speech = "The DEAD were RISING\n\nfrom their GRAVES!";
                        break;

                    case 7:
                        SoundManager::getInstance().StartRandomVoices(2);
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
            }else if (interactions == 1 && player.hasShovel){ //youve seen all of the first interaction text, and you have the shovel. 
                clickCount += 1;
                switch(clickCount){
                    
                    case 1:
                        SoundManager::getInstance().PlayRandomVoice();
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
                        SoundManager::getInstance().StartRandomVoices(2);
                        break;
                    case 6:
                        SoundManager::getInstance().StartRandomVoices(2);
                        speech = "Here is the KEY to the cemetery";
                        
                        break;

                    case 7:
                        speech = "Find the source of the zombies";
                        SoundManager::getInstance().StartRandomVoices(2);
                        break;

                    case 8:
                        speech = "There is an old shotgun buried over there\n\nYour gonna need it";
                        SoundManager::getInstance().StartRandomVoices(2);
                        break;

                    case 9:
                        SoundManager::getInstance().PlayRandomVoice();
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
                        SoundManager::getInstance().StartRandomVoices(1);
                        break;

                    case 3:
                        speech = "I got fired when I wouldn't go along with their\n\nWorld domination plans";
                        SoundManager::getInstance().StartRandomVoices(2);
                        break;
                    
                    case 4:
                        speech = "I should have known they were behind this";
                        SoundManager::getInstance().StartRandomVoices(2);
                        break;

                    case 5:
                        speech = "You got a computer?\n\nSearch the internet";
                        SoundManager::getInstance().StartRandomVoices(2);
                        break;

                    case 6:
                        speech = "Find NecroTech HQ\n\nPut a stop to their evil plans"; 
                        SoundManager::getInstance().StartRandomVoices(2);
                        interactions = 3; //load the fourth interaction
                        clickCount = 0; //reset clickCount for another round. 
                        break;
                    

                }


            }else if (interactions == 3 && !player.validatedPassword && player.necroTechSearched){ //seen all of the 3rd interaction and have searched the internet. 
                clickCount += 1;
                switch (clickCount)
                {
                case 1:
                    SoundManager::getInstance().StartRandomVoices(1);
                    speech = "A 3 digit code you say?";
                    break;
                
                case 2:
                    SoundManager::getInstance().StartRandomVoices(1);
                    speech = "What's the most evil\n\nthree digit number";
                    break;

                case 3:
                    SoundManager::getInstance().StartRandomVoices(1);
                    speech = "You know...\n\nThe mark of the beast?";
                    break;

                case 4:
                    SoundManager::getInstance().StartRandomVoices(1);
                    speech = "...the password is\n\n666"; //repeats
                    break;
                }

            }    
        }

        if (!talked && !hobo && !police && !teller and !robot){ //all other NPCs
            //SoundManager::getInstance().StartRandomVoices(.5); normal NPCs dont talk anymore until I find better audio clips
            talked = true;
            speech = GetRandomPhrase(); // NPC greets player
            talkTimer = 3; //limit talking. 
            idleTime = 3;
        }
        
    }


void NPC::HandleAlien(){
    frameSpeed = 14;

}

void NPC::HandleGhost(){ //Also Bats. should probably rename or make it a seperate func handleBats()

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

void NPC::HandleZombie(){
    if (!isActive) return; 
    if (isZombie) hasTarget = false; //was setting hasTarget to false for police
    float distToDest = fabs(position.x - destination.x);
    if (isZombie) attacking = false;

    if (isZombie && distanceToPlayer < detectionRange && riseTimer <= 0) {
        hasTarget = true; //if hasTarget dont go idle
        destination = player.position;  // Move towards the player
        
    }

    if (isZombie && distanceToPlayer < 10.0f && riseTimer <= 0 && !isDying) { //zombie attack player
        attacking = true;
        destination = position;
        if (player.hitTimer <= 0){
            player.take_damage(10);
            if (player.armor <= 0){ //dont play hit sfx when player has armor. 
                PlaySound(rand() % 2 == 0 ? SoundManager::getInstance().GetSound("boneBreak") : SoundManager::getInstance().GetSound("squish"));
                //randomly play one sound or the other. 
            }

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
                targetNPC->TakeDamage(25);
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

void NPC::HandleMiB(){

    //MIB follow player up to a point then stops and waits. 
    if (gameState != LOBBY && MiB && distanceToPlayer < 1000 && !hasTarget && !attacking){
        destination = player.position; //move toward player
        hasTarget = true; //dont go idle
    }

    if (gameState == LOBBY && MiB && distanceToPlayer < 1000 && !hasTarget && agro){
        hasTarget = true;
        destination = player.position;
    }


    if (MiB && agro && distanceToPlayer < 150){
       destination = position;
       hasTarget = true;

       //shoot
       if (can_shoot && !isDying){
            can_shoot = false;
            attacking = true;
            SoundManager::getInstance().PlayPositionalSound("gunShot", position, player.position, 500); //mibs shoot lasers, but sound like guns. 
            SetAnimationState(ATTACKING);
            NPCfireBullet(*this, false, 10, true);
            shootTimer = 1.0f;
       }

    }


    if (MiB && distanceToPlayer <= 160 && hasTarget && !agro && gameState != LOBBY){
       
        destination = position; //stop a ways away
        if (!attacking) SetAnimationState(IDLE);
    }



    if (shootTimer > 0){
        shootTimer -= GetFrameTime();
    }else{
        can_shoot = true;
        //attacking = false;
    }
}

void NPC::HandleRobot(){
    attacking = false;
    //agro = true;
    if (robot && distanceToPlayer < detectionRange && agro){
        hasTarget = true;
        destination = player.position;
        speed = 75;

    }

    if (distanceToPlayer < 150 && agro){ //150 for longer distance, more of a chance for NPCs to get in the way
        destination = position;
        //shoot
        if (can_shoot && !isDying){
            SoundManager::getInstance().PlayPositionalSound("laser", position, player.position, 500);
            can_shoot = false;
            SetAnimationState(ATTACKING);
            NPCfireBullet(*this, false, 10, true); //laser = true
            shootTimer = 1.0f;

        }
        
    }

    

    if (shootTimer > 0){
        shootTimer -= GetFrameTime();
    }else{
        can_shoot = true;
    }

}

void NPC::HandleCyberZombie(){
    agro = true;
    if (distanceToPlayer < detectionRange && agro){
        hasTarget = true;
        destination = player.position;
        facingRight = player.position.x > position.x;
        speed = 75;

    }

    if (distanceToPlayer < 200 && agro){ //150 for longer distance, more of a chance for NPCs to get in the way
        destination = position;
        //shoot
        if (can_shoot && !isDying){
            //SoundManager::getInstance().PlayPositionalSound("laser", position, player.position, 500);
            can_shoot = false;
            animationTimer = 0.9;
            SetAnimationState(ATTACKING);
            attacking = true;
            float speed = 200.0f;
            Vector2 grenadeVelocity = {
                facingRight ? speed : -speed,  // Horizontal velocity based on facing direction
                -80.0f                             // Initial upward arc
            };

            

            // Add the grenade to the global grenades vector
            PlaySound(SoundManager::getInstance().GetSound("grenadeLauncher"));
            grenades.emplace_back(position + Vector2 {32, 16}, grenadeVelocity);
            //NPCfireBullet(*this, false, 10, true); //laser = true
            shootTimer = 3.0f;

        }
        
    }

    if (shootTimer > 0){
        shootTimer -= GetFrameTime();
        
        
    
    }else{
        can_shoot = true;
        attacking = false;
    }

    if (animationTimer > 0){ //only play grenade attack animation once. 
        animationTimer -= GetFrameTime();
    }else{

        if (!isDying && !isMoving) SetAnimationState(IDLE);
    }

}

void NPC::HandlePolice(){
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

    if (agroZombie && targetNPC != nullptr && targetNPC->isActive && targetNPC->isZombie){
        std::cout << "attacking zombie\n";
        //police attack zombie//doesn't work and I don't know why, police can be killed by zombies at least. 
        float distance_to = abs(targetNPC->position.x - position.x);
        if (distance_to < 30){ //police has longer reach than zombie
            destination = position;
            idleTime = 0.0f;
            attacking = true;
            frameSpeed = 12;
            SetAnimationState(ATTACKING);
            if (targetNPC->isActive && currentFrame == 4){
                targetNPC->TakeDamage(30);
                PlaySound(SoundManager::getInstance().GetSound("BoneCrack"));

            }

        }
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
    frameCounter += GetFrameTime() * frameSpeed; //accumulate frametime until it's time to switch. 
    //framecounter = time between frames, 0.0167 * 8 
    
    if (frameCounter >= 1.0f) { 
        frameCounter = 0.0f; //restet to 0, we dont want to save any frames do to lag,
        // causes NPCs to stutter at the beginning of game. 
        currentFrame++;

        // Determine the number of frames based on the current animation, all animations are 7 frames except idle
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

void NPC::ghostMoves(){
    if (agro && hasTarget) {
        float deltaTime = GetFrameTime(); 
        
        Vector2 direction = { destination.x - position.x, destination.y - position.y };
        float distance = sqrtf(direction.x * direction.x + direction.y * direction.y); // Get distance
        
        if (distance > 5.0f) { // Prevent jittering when close
            // Normalize direction vector (gives smooth diagonal movement)
            direction.x /= distance;
            direction.y /= distance;

            // Move ghost at a constant speed
            float moveSpeed = 75.0f;  
            position.x += direction.x * moveSpeed * deltaTime;
            position.y += direction.y * moveSpeed * deltaTime;

            // Set facing direction based on movement
            if (fabs(direction.x) > 0.1f) { // Only update facing when moving significantly in X
                facingRight = (direction.x > 0);
            }

            // Set animation state
            if (!isDying) SetAnimationState(WALK);
        } else {
            // Stop moving when very close
            SetAnimationState(IDLE);
        }
    } else {
        SetAnimationState(IDLE);
    }
}



void NPC::Update() {
    if (!isActive) return;  // Skip update if the NPC is not active
    if (!isZombie && !robot) riseTimer = 0;

    //animation.Update(GetFrameTime());

    distanceToPlayer = abs(player.position.x - position.x);

    bloodEmitter.UpdateParticles(GetFrameTime()); //update blood


    if (targetedTimer > 0){ //dont stay targeted forever, go back to normal after 5 seconds. 
        targetedTimer -= GetFrameTime();
        
        
    }else{
        isTargeted = false;
    }

    if (distanceToPlayer >= 30){
        highLight = false;//Turn off highlights on any interacting NPCs when far enough way. 
        interacting = false; // maybe this is a good idea too.
    }

    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)){
        if (distanceToPlayer < 20 && !police && !isZombie){ //dont key up on police. Could accidently agro them. 
            HandleNPCInteraction(); //talk to NPCs

        }
    }

    // Check if the zombie is still rising
    if (riseTimer > 0) {
        riseTimer -= GetFrameTime();
        //SetAnimationState(RISING);  // Ensure the animation is set to RISING during this time
        
        // Update frame counter and animation logic for RISING
        frameCounter += GetFrameTime() * frameSpeed;
        if (frameCounter >= 1.0f) {
            frameCounter = 0.0f; //0 instead of -= 1, to prevent glichiness. 
            currentFrame++;

        }

        return;  // Skip further logic until the zombie finishes rising
    }


    // Update hit timer if the NPC has been hit

    if (hitTimer > 0) {
        hitTimer -= GetFrameTime();
        if (ghost) {
            ghostAlpha = Clamp(hitTimer / 0.3f, 0.0f, 1.0f);  // ghost becomes transparent on hit, then fades back in
        }
    } else {
        ghostAlpha = 1.0f;  // Reset once hitTimer expires
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
    

    if (MiB) HandleMiB();
    if (police) HandlePolice(); //handle distance checks and attack logic. 
    if (isZombie) HandleZombie();
    if (cyberZombie) HandleCyberZombie();
    if (ghost || bat) HandleGhost(); //also bats
    if (alien) HandleAlien();
    if (robot) HandleRobot();

    Vector2 directionToPlayer = {
    player.position.x - position.x,
    player.position.y - position.y
    };

    directionToPlayer = Vector2Normalize(directionToPlayer);


    isMoving = false;

    //NPCs choose a random position called destination. they move toward destination until they arrive then wait a random amount of time and repeat 
    if (!isDying && riseTimer <= 0 && !attacking) { //MOVE NPCs and Police and Zombies and Ghosts. 
        // Move towards the destination

        if (!ghost && !bat){ //pedestrians on the street/zombies

            if (!isTargeted){ //not targeted regular npc movement
                if (position.x < destination.x) {
                    position.x += speed * GetFrameTime();
                    facingRight = true;
                    SetAnimationState(WALK);
                    isMoving = true;
                
                } else if (position.x > destination.x) {
                    position.x -= speed * GetFrameTime();
                    facingRight = false;
                    SetAnimationState(WALK);
                    isMoving = true;
                    
                }     

            }


            if (isTargeted && zRight){ //run away from zombies, zright only changes after targetedTimer is 0. to prevent flip flopping. 
                SetAnimationState(WALK);
                position.x -= speed * GetFrameTime();
                facingRight = false;
                 
            }else if (isTargeted && !zRight){ //zombie on the left, run right
                SetAnimationState(WALK);
                position.x += speed * GetFrameTime();
                facingRight = true;
            }


            
            
        }else if (bat || ghost) {
            ghostMoves(); // XY movement for ghosts and bats. 
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
                SetDestination(1600, 2500); //robots necrotech, and lobby.
            }else if (lobbyNPC){
                SetDestination(1600, 2500); //lobby npc
            }else if (scientist || scienceJr){
                SetDestination(2400, 3600); //lab scientists
            }else if (alien){
                SetDestination(1900, 2200);
            } else{
                SetDestination(1000, 3500);  //Pedestrians Outside, and park
                
            }

        
        }

        if (isZombie && distanceToPlayer >= detectionRange && fabs(position.x - destination.x) < 5){ //at destination and zombie and no target
            
            SetDestination(player.position.x - 100, player.position.x + 100); //move toward player as to not get lost. test this
        }

        if (fabs(position.x - destination.x) < 5.0f && hasTarget && isZombie){ //destination = targetNPC pos or player pos when has target is true
            destination = position; //zombie stop while attacking
        }

    }
}

void NPC::Render() {
    if (!isActive) return;  // Skip rendering if the NPC is not active. NPC still exists though

    //animation.Draw(position, facingRight);
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

    float hitboxWidth = 16.0f;   
    float hitboxHeight = 32.0f;  //Tall rectange to cover the sprite. 

    Rectangle npcHitbox = { //debug hitbox
        position.x+24,     
        position.y+16,      
        hitboxWidth,  
        hitboxHeight                    
    };
    
    // Draw the texture at the NPC's position
    // Tint the NPC red if recently hit
    Color tint = (hitTimer > 0) ? RED : WHITE;
    if (ghost) tint = ColorAlpha(WHITE, ghostAlpha);//use Color alpha to change alpha of ghost on hit
    if (bat) BeginShaderMode(shaders.rainbowOutlineShader); //raindbow bats
    if (highLight && !frank) BeginShaderMode(shaders.highlightShader);//highlight when talking except for frank, for reasons. I think this broke 
    //npc highlighting but I think I like it with out it. 
    
    //DrawRectangleLines(position.x+24, position.y+16, hitboxWidth, hitboxHeight, RED); // debug show hitbox
    DrawTextureRec(texture, sourceRec, position, tint);

    bloodEmitter.DrawParticles(); //draw blood in front of sprite, looks better IMO
    EndShaderMode();
}

void NPC::SetAnimationState(AnimationState newState) {
    if (currentAnimation != newState) {
        currentAnimation = newState;
        currentFrame = 0;  // Reset to the first frame of the new animation
        frameCounter = 0.0f;  // Reset the frame counter
        //animation.SetAnimation(newState);
    }
}

void NPC::handleDeath(){
    if (isZombie) {
        //PlaySound(SoundManager::getInstance().GetSound("zombieDeath"));
        SoundManager::getInstance().PlayPositionalSound("zombieDeath", position, player.position, 500);
        riseTimer = 0; //if killed while still rising set the risetimer back to 0 as to not play rise animation
        isDying = true;           // Start dying process
        bloodEmitter.SpawnExplosion(20, RED);
        if (rand() % 2 == 0){
            SetAnimationState(DEATH);  // Set to death animation
        }else{
            SetAnimationState(DEATH2); //randomize deaths
        }

        deathTimer = 0.85f;        // Set death animation duration // needs to be exact
        destination = position; //zombie is at it's destination on death as to not play walk animation
    }

    if (ghost){
        isDying = true;
        deathTimer = 0.3; // same as the fade out time. So the ghost just fades out for good on death. 
        destination = position;
        bloodEmitter.SpawnExplosion(20, WHITE);
    }

    if (bat){
        isDying = true;
        frameSpeed = 14;
        deathTimer = 0.5;
        destination = position;
        SetAnimationState(DEATH2);
    }

    if (robot){
        riseTimer = 0;
        isDying = true;
        SetAnimationState(DEATH);
        //play robot death sound
        //trigger = true; //summon more robots on death in lobby
        SoundManager::getInstance().PlayPositionalSound("explosion", position, player.position, 500);
        bloodEmitter.SpawnExplosion(20, YELLOW);
        destination = position;
        deathTimer = .85f;

    }
    if (cyberZombie){
        SoundManager::getInstance().PlayPositionalSound("zombieDeath", position, player.position, 500);
        riseTimer = 0;
        isDying = true;
        SetAnimationState(DEATH);
        deathTimer = .85f;
        destination = position;
    }

    if (!robot && !cyberZombie && !isZombie && !ghost && !bat){ //NPC killed by zombie
        riseTimer = 0; 
        isDying = true;           // Start dying process   
        SetAnimationState(DEATH);  // Set to death animation
        SoundManager::getInstance().PlayPositionalSound("deathScream", position, player.position, 500);
        deathTimer = 0.85f;        // Set death animation duration // needs to be exact
        destination = position; 
        
    }

}

void NPC::playZombieHit(int soundIndex)
{
    switch (soundIndex){ //zombie hits
        case 0:
            SoundManager::getInstance().PlayPositionalSound("zhit1", position, player.position, 500);
            
            break;
        case 1:

            SoundManager::getInstance().PlayPositionalSound("zhit2", position, player.position, 500);
            break;

        case 2:

            SoundManager::getInstance().PlayPositionalSound("zhit3", position, player.position, 500);
            break;
        
        case 3:

            SoundManager::getInstance().PlayPositionalSound("zhit4", position, player.position, 500);
            break;

    }

}

void NPC::ClickNPC(){
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
                HandleNPCInteraction();
                
            }

        }
    }
}

bool NPC::CheckHit(Vector2 previousBulletPosition, Vector2 currentBulletPosition, Vector2 bulletSize) { 
// Check hit between bullet hitbox and NPC hitbox. 
//         ______________ 
//        |      32-4 x  |
//        |     _|_  16y |
//        |     | 8|     |   
//        |     |32|     | 64
//        |     |__|     |   
//        |              |   
//        |______________|
//               64
    //raycasting for better collision detection
    // Define a hitbox around the NPC (centered on the NPC's position)
    float hitboxWidth = 8.0f;   // Width of the hitbox 
    float hitboxHeight = 32.0f; // Height of the hitbox 

    // Offset the hitbox so it's centered on the zombie's position
    Rectangle npcHitbox = {
        position.x + 32-4,   // Center horizontally
        position.y + 16,  // Center vertically
        hitboxWidth,                    // Width of hitbox
        hitboxHeight                    // Height of hitbox
    };

    
    Rectangle bulletRect = {
        currentBulletPosition.x,  // Bullet's x position
        currentBulletPosition.y,  // Bullet's y position
        bulletSize.x,             // Bullet's width
        bulletSize.y              // Bullet's height
    };

    // Check if the current or previous bullet position is inside the hitbox (normal check)
    if (CheckCollisionRecs(npcHitbox, bulletRect)) {
        return true;  // Return true indicating a hit
    }


    if (CheckCollisionPointRec(previousBulletPosition, npcHitbox)) {
        return true;
    }


    // Use raycasting to check for collisions between the previous and current bullet positions
    Vector2 bulletPath = Vector2Subtract(currentBulletPosition, previousBulletPosition);
    int steps = ceil(Vector2Length(bulletPath) / bulletSize.x);  // Steps depend on bullet size

    // Check along the bullet's path for a collision
    for (int i = 1; i < steps; i++) {  // Start at 1 to skip previousBulletPosition
        Vector2 interpolatedPosition = Vector2Lerp(previousBulletPosition, currentBulletPosition, i / (float)steps);
        if (CheckCollisionPointRec(interpolatedPosition, npcHitbox)) {
            return true;
        }
    }


    return false;  // Return false if no hit occurred
}



void NPC::TakeDamage(int damage) {

    if (!isDying){ //we don't limit how faster take damage can run. Usually you would have a canTakeDamage bool. if (npc.hitTimer <= 0) takeDamage() 
        health -= damage;
        hitTimer = 0.3f; // Tint the sprite red for 0.3 seconds

    }

    //handle particles
    bloodEmitter.position = Vector2 {position.x + 32, position.y + 20}; //head area

    if (robot || ghost){
        
        bloodEmitter.SpawnExplosion(5, WHITE);
    } 

    if (!robot && !ghost){
        bloodEmitter.SpawnBlood(5,RED, !facingRight); //everyone bleeds, except robots and ghosts
    
    } 

    if (ghost || bat || MiB || robot){
        if (!agro){
            agro = true; //trigger agro on hit
            destination = player.position;//move toward player
            idleTime = 0; //stop being idle 
            facingRight = (player.position.x > position.x); //face the player

        }

    } 

    if (!isZombie && !bat && !ghost && !robot){
        destination = position; //if your an NPC, stop when you take damage so we can play the death animation. 
        
    }

    int soundIndex = rand() % 4; //returns 0, 1, 2 or 3

    if (isZombie && !isDying){
        playZombieHit(soundIndex);
        
    }

    if (health <= 0 && !isDying){
        handleDeath();
    }

}
