#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "NPC.h"
#include "Player.h"
#include "GameResources.h"
#include "Bullet.h"
#include "GameEnums.h"
#include "SoundManager.h"
#include "GameCalendar.h"
#include "Platform.h"
#include <string>
#include <cstdlib>  // For rand and srand
#include <ctime>    // For seeding rand
#include "shaderControl.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"



//Remember: The Law is One. 

//start_pos = 1922, 700
//apartment_pos = 2256, 700
//car_start = 1710, 700 - 32
//Enter_car = 1738, 700
//Enter_road = 1340, 700
//key_pos 380, 666
//street_light = 1913, 500?
int apartmentX = 2256;
int vacantLotX = 2753;
int vacantExitX = 2762;
bool over_lot = false;
bool over_exit = false;
//cemetery_start 1743, 700
bool runOnce = true;
bool streetSounds = false;
bool over_apartment = false;
bool over_car = false;
bool over_gate = false;
bool over_shotgun = false;
bool show_carUI = false;
bool leave_apartment = false;
bool leave_cemetery = false;
bool buttonCemetery = false;
bool buttonInternet = false;
bool hasCemeteryKey = false;
bool canGiveFortune = true;
bool firstHobo = true;
bool firstBlood = false;
bool drawShovel = false;
bool drawShotgun = true;
bool buttonWork = false;
bool hasPills = false;
bool digSpot = false;
bool start = true;
bool buttonTavern = false;
bool gotoWork = false;
bool debug = true; ///////////////////////////////////////DEBUG KEYS ON/OFF
bool hasWorked = false;
bool buttonSleep = false;
bool hasSlept = false;
bool showAPUI = false;
bool playOwl = false;
bool can_talk = true;
bool buyFortune = false;
bool teller = false;
bool dealer = false;
bool can_sell_drugs = true;
bool applyShader = false;
bool drunk = false;
bool glitch = false;
bool openMagicDoor = false;
bool move_car = false;
bool showHealthbar = false;
bool reverse_road = false;
bool has_car_key = false;
bool npcWalk = false;
bool openDrawer = false;
bool raiseZombies = false;
bool zombieWave2 = false;
bool zombieWave3 = false;
bool show_dbox = true;
float dboxTime = 10.0;
float inventoryPositionX = 0.0f;
float inventoryPositionY = 0.0f;
float inventoryTargetX = 0.0f;
float inventoryTargetY = 0.0f;
float DoorframeTimer = 0.0f;
float astralThreshold = 0.5f;
float DoorframeTime = 0.1f;
float badgeTimer = 0.0f;
float fortuneTimer = 0.0f;
int remainingZombiesToSpawn = 0;    // Tracks remaining zombies to spawn
float spawnTimer = 0.0f;            // Timer for spawning
float nextSpawnDelay = 0.0f;        // Time delay between spawns

float blackoutTime = 2.0f;  // Time to stay blacked out
float blackoutTimer = 0.0f; // Timer to keep track of blackout period

Color customBackgroundColor = {32, 42, 63, 255};  //Same Color as street background image. 
Color shovelTint = WHITE;

int money = 100;
int displayMoney = 100;
bool showInventory = false;
const int INVENTORY_SIZE = 10;  // Define the size of the inventory
std::string inventory[INVENTORY_SIZE] = {"", "", "", "", "", "", "", "", "", ""}; //Inventory is a fixed array for no particular reason. 
//possibly make it a vector and inventory size could grow over time. Or a backpack item 

std::string phrase = "A and D or Arrows\n\nto move left and right"; //initial tutorial phrase

const int screenWidth = 1024;
const int screenHeight = 1024;

Color purplishGrey = {128, 96, 128, 255};  // RGBA format: (R, G, B, A)

Vector2 carKeysPos = {(screenWidth/2) - 100, 655}; // remember positions need to based on screenwidth incase of resolution change. 
Vector2 drawerPos = {screenWidth/2 + 129, 730};
Vector2 cemetery_start{2746, 700};
Vector2 car_pos = {3000, 710};
Vector2 truck_pos = {512, 710};
Vector2 dz_pos = {0, 0};
Vector2 pc_start_pos = Vector2{1710, 668};
Vector2 pstart_by_car = Vector2{1738, 700};
Vector2 dboxPosition;
Color ApartmentBgColor {41, 48, 63, 255};

//containers
std::vector<NPC> npcs;
std::vector<NPC> zombies;
std::vector<NPC>hobos;
std::vector<NPC>ghosts;
std::vector<NPC>bats;
std::vector<NPC>mibs;
std::vector<NPC>astralGhosts;

std::vector<Platform> platforms;

GameState gameState = OUTSIDE;

TransitionState transitionState = NONE;
float fadeAlpha = 1.0f;  // Starts fully opaque
float fadeSpeed = 0.02f; // Speed of fade (adjust as needed)
bool firstTransition = true;



void PrintVector2(const Vector2& vec) {
    std::cout << "(" << vec.x << ", " << vec.y << ")" << "\n";
}


struct PlayerCar {
    Vector2 position;
    float carSpeed;
    int currentFrame = 0;
    bool facingLeft = true;

};

struct MagicDoor {
    Vector2 position;
    int currentFrame = 0;

};

struct Earth {
    Vector2 position = {3500, 400};
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int totalFrames;
    float frameTime; // Time between frames in seconds
    float frameTimer;
};




// Function to initialize and load resources
void LoadGameResources(GameResources& resources) {
    resources.background = LoadTexture("assets/Background.png");
    resources.foreground = LoadTexture("assets/Foreground.png");
    resources.midground = LoadTexture("assets/Midground.png");
    resources.manTexture = LoadTexture("assets/Man.png");
    resources.walkSheet = LoadTexture("assets/WalkSheet.png");
    resources.runSheet = LoadTexture("assets/RunSheet.png");
    resources.apartment = LoadTexture("assets/Apartment.png");
    resources.road = LoadTexture("assets/Road.png");
    resources.car = LoadTexture("assets/Car.png");
    resources.carSheet = LoadTexture("assets/Car-Sheet.png");
    resources.reloadSheet = LoadTexture("assets/reloadSheet.png");
    resources.lightBeam = LoadTexture("assets/LightBeam.png");
    resources.lightCone = LoadTexture("assets/LightCone.png");
    resources.cemetery = LoadTexture("assets/Cemetery.png");
    resources.inventorySlot = LoadTexture("assets/InventorySlot.png");
    resources.cemeteryBackground = LoadTexture("assets/Cemetery(backGround).png");
    resources.cemeteryTrees = LoadTexture("assets/Cemetery(Trees).png");
    resources.cemeteryMidground = LoadTexture("assets/Cemetery(midGround).png");
    resources.cemeteryForeground = LoadTexture("assets/Cemetery(forground).png");
    resources.carKey = LoadTexture("assets/carKey.png");
    resources.npcTexture = LoadTexture("assets/npcSheet.png");
    resources.breakLight = LoadTexture("assets/breakLight.png");
    resources.truck = LoadTexture("assets/Truck.png");
    resources.businessSheet = LoadTexture("assets/businessSheet.png");
    resources.womanSheet = LoadTexture("assets/womanSheet.png");
    resources.dealerSheet = LoadTexture("assets/DealerSheet.png");
    resources.zombieSheet = LoadTexture("assets/zombieSheet.png");
    resources.shootSheet = LoadTexture("assets/shootSheet.png");
    resources.OpenDrawer = LoadTexture("assets/OpenDrawer.png");
    resources.Revolver = LoadTexture("assets/Revolver.png");
    resources.CarKeys = LoadTexture("assets/CarKeys.png");
    resources.handCursor = LoadTexture("assets/hand.png");
    resources.reticle = LoadTexture("assets/reticle.png");
    resources.ShotGunSheet = LoadTexture("assets/ShotGunSheet.png");
    resources.ShotgunReload = LoadTexture("assets/ShotGunReload.png");
    resources.Drugs = LoadTexture("assets/Drugs.png");
    resources.policeSheet = LoadTexture("assets/PoliceSheet.png");
    resources.vacantLot = LoadTexture("assets/EmptyLot.png");
    resources.hoboSheet = LoadTexture("assets/HoboSheet.png");
    resources.shovel = LoadTexture("assets/shovel.png");
    resources.shovelWorld = LoadTexture("assets/shovelWorld.png");
    resources.shotgunPickup = LoadTexture("assets/ShotGunPickup.png");
    resources.shotgunIcon = LoadTexture("assets/shotgunIcon.png");
    resources.pills = LoadTexture("assets/pills.png");
    resources.FortuneTellerSheet = LoadTexture("assets/FortuneTellerSheet.png");
    resources.woman2Sheet = LoadTexture("assets/woman2Sheet.png");
    resources.cemeteryKey = LoadTexture("assets/CemeteryKey.png");
    resources.GraveyardGate = LoadTexture("assets/GraveyardGate.png");
    resources.GraveyardForeground = LoadTexture("assets/GraveyardForeground.png");
    resources.GreaveyardMidground= LoadTexture("assets/GraveyardMidground.png");
    resources.deadZombie = LoadTexture("assets/DeadZombie.png");
    resources.Badge = LoadTexture("assets/Badge.png");
    resources.ComputerScreen = LoadTexture("assets/ComputerScreen.png");
    resources.ghostSheet = LoadTexture("assets/ghostSheet.png");
    resources.magicDoorSheet = LoadTexture("assets/MagicDoorSheet.png");
    resources.AstralBackground = LoadTexture("assets/AstralBackground.png");
    resources.AstralMidground = LoadTexture("assets/AstralMidGround.png");
    resources.AstralClouds = LoadTexture("assets/AstralClouds.png");
    resources.AstralForeground = LoadTexture("assets/AstralForeground.png");
    resources.AstralClouds2 = LoadTexture("assets/AstralClouds2.png");
    resources.EarthSheet = LoadTexture("assets/EarthSpin-Sheet.png");
    resources.jumpSheet = LoadTexture("assets/JumpSheet.png");
    resources.healthBorder = LoadTexture("assets/HealthBoarder.png");
    resources.batSheet = LoadTexture("assets/batSheet.png");
    resources.platformTexture = LoadTexture("assets/platform(128x32).png");
    resources.mibSheet = LoadTexture("assets/mibSheet.png");
}

void UnloadGameResources(GameResources& resources){
    UnloadTexture(resources.background);
    UnloadTexture(resources.foreground);
    UnloadTexture(resources.midground);
    UnloadTexture(resources.walkSheet);
    UnloadTexture(resources.runSheet);
    UnloadTexture(resources.manTexture);
    UnloadTexture(resources.apartment);
    UnloadTexture(resources.carSheet);
    UnloadTexture(resources.car);
    UnloadTexture(resources.road);
    UnloadTexture(resources.cemetery);
    UnloadTexture(resources.inventorySlot);
    UnloadTexture(resources.cemeteryBackground);
    UnloadTexture(resources.cemeteryTrees);
    UnloadTexture(resources.cemeteryMidground);
    UnloadTexture(resources.cemeteryForeground);
    UnloadTexture(resources.npcTexture);
    UnloadTexture(resources.lightBeam);
    UnloadTexture(resources.lightCone);
    UnloadTexture(resources.breakLight);
    UnloadTexture(resources.truck);
    UnloadTexture(resources.businessSheet);
    UnloadTexture(resources.womanSheet);
    UnloadTexture(resources.zombieSheet);
    UnloadTexture(resources.shootSheet);
    UnloadTexture(resources.OpenDrawer);
    UnloadTexture(resources.Revolver);
    UnloadTexture(resources.CarKeys);
    UnloadTexture(resources.handCursor);
    UnloadTexture(resources.reticle);
    UnloadTexture(resources.ShotGunSheet);
    UnloadTexture(resources.ShotgunReload);
    UnloadTexture(resources.Drugs);
    UnloadTexture(resources.policeSheet);
    UnloadTexture(resources.vacantLot);
    UnloadTexture(resources.hoboSheet);
    UnloadTexture(resources.shovel);
    UnloadTexture(resources.shovelWorld);
    UnloadTexture(resources.shotgunPickup);
    UnloadTexture(resources.shotgunIcon);
    UnloadTexture(resources.pills);
    UnloadTexture(resources.FortuneTellerSheet);
    UnloadTexture(resources.woman2Sheet);
    UnloadTexture(resources.cemeteryKey);
    UnloadTexture(resources.GraveyardGate);
    UnloadTexture(resources.GraveyardForeground);
    UnloadTexture(resources.GreaveyardMidground);
    UnloadTexture(resources.deadZombie);
    UnloadTexture(resources.Badge);
    UnloadTexture(resources.ComputerScreen);
    UnloadTexture(resources.ghostSheet);
    UnloadTexture(resources.magicDoorSheet);
    UnloadTexture(resources.AstralBackground);
    UnloadTexture(resources.AstralMidground);
    UnloadTexture(resources.AstralClouds);
    UnloadTexture(resources.AstralForeground);
    UnloadTexture(resources.AstralClouds2);
    UnloadTexture(resources.EarthSheet);
    UnloadTexture(resources.jumpSheet);
    UnloadTexture(resources.healthBorder);
    UnloadTexture(resources.batSheet);
    UnloadTexture(resources.platformTexture);
    UnloadTexture(resources.mibSheet);
   
}


void InitializePlayerCar(PlayerCar& player_car){
    player_car.position = {1710, 700-32};
    player_car.carSpeed = 100;
    player_car.currentFrame = 0;
}

void InitializeMagicDoor(MagicDoor& magicDoor){
    magicDoor.position = {2089, 700};
    magicDoor.currentFrame = 0;
}

void InitEarth(Earth& earth){
    earth.position = {2600, 300};
    earth.frameWidth = 48;
    earth.frameHeight = 48;
    earth.currentFrame = 0;
    earth.totalFrames = 94;
    earth.frameTimer = 0.0;
    earth.frameTime = .1;
}


void InitPlatforms() {
    //initialize platforms before drawing them in astral

    platforms.emplace_back(2300.0f, 675.0f, 200.0f, 20.0f, WHITE);

    // Add more platforms as needed
    platforms.emplace_back(2500.0f, 600.0f, 150.0f, 20.0f, WHITE);
    platforms.emplace_back(2800.0f, 550.0f, 250.0f, 20.0f, WHITE);
    platforms.emplace_back(2600.0f, 450.0f, 150.0f, 20.0f, WHITE);
    platforms.emplace_back(2400.0f, 400.0f, 150.0f, 20.0f, WHITE);
    platforms.emplace_back(2100.0f, 350.0f, 250.0f, 20.0f, WHITE);
}


// Function to add an item to the first available slot in the inventory
void AddItemToInventory(const std::string& item, std::string inventory[], int inventorySize) {
    for (int i = 0; i < inventorySize; i++) {
        if (inventory[i].empty()) {
            inventory[i] = item;  // Add the item to the first empty slot
            break;
        }
    }
}

std::string GetTellerPhrase() {
    std::vector<std::string> tellerPhrases = {
        "Beware of a stranger's advice\n\n trust your own instincts.",
        "Your courage will lead you\n\n to unexpected rewards.",
        "Fortune smiles upon you\n\nin your next endeavor.",
        "A difficult choice \n\nwill test your resolve.",
        "Beware of the shadows\n\n not all is as it seems.",
        "Fortune favors the bold\n\n take the leap.",

    };

    int randomIndex = rand() % tellerPhrases.size();
    return tellerPhrases[randomIndex];
}


void MonitorMouseClicks(Player& player, GameCalendar& calendar){

    //Debug mousePosition
    // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    //     Vector2 mousePosition = GetMousePosition();
    //     std::cout << "MousePos: ";
    //     PrintVector2(mousePosition);
    // }
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if (gameState == APARTMENT){

            Vector2 mousePosition = GetMousePosition();  // Get the mouse position
            Vector2 computerPos = {screenWidth/2 - 10, 587};


            if (buttonSleep && !hasSlept){ ////Go to sleep
                calendar.AdvanceDay(); 
                buttonSleep = false;
                hasWorked = false;
                hasSlept = true;
                buyFortune = false;
                canGiveFortune = true; //fortune teller is reset 
                drunk = false;  //Effects ware off when you sleep
                applyShader = false;
                over_apartment = false;
                glitch = false;
                transitionState = FADE_OUT; //fades out to street for now.
                player.currentHealth = player.maxHealth; //recover hitpoints after sleeping. 
                for (NPC& npc : npcs){
                    if (npc.police){
                        npc.agro = false; // loose the cops after sleeping. 
                        
                    }
                } 
            }
            
            //Draw a rectangle over interactive objects and check for mouse collision with said rectangle. 
            // Car key Rectangle 
            Rectangle textureBounds = {
                carKeysPos.x,      // X position
                carKeysPos.y,      // Y position
                static_cast<float>(64),  // Width of the texture
                static_cast<float>(64)  // Height of the texture
            };

            
            // drawer rec
            Rectangle drawerBounds = {
                drawerPos.x,      // X position
                drawerPos.y,      // Y position
                static_cast<float>(128),  // Width of the texture
                static_cast<float>(64)  // Height of the texture
            };
            // computer rec
            Rectangle ComputerBounds = {
                computerPos.x,      // X position
                computerPos.y,      // Y position
                static_cast<float>(64),  // Width of the texture
                static_cast<float>(64)  // Height of the texture
            };

            // Check if the mouse is over the texture
            if (CheckCollisionPointRec(mousePosition, textureBounds)&& !has_car_key) {
                showInventory = true;
                AddItemToInventory("carKeys", inventory, INVENTORY_SIZE);
                has_car_key = true;
                PlaySound(SoundManager::getInstance().GetSound("Keys"));
            }

            if (CheckCollisionPointRec(mousePosition, drawerBounds)&& !openDrawer){
                openDrawer = true;
                PlaySound(SoundManager::getInstance().GetSound("OpenDrawer"));
                if (!player.hasGun){
                    AddItemToInventory("Gun", inventory, INVENTORY_SIZE);
                    showInventory = true;
                    player.hasGun = true;
                    PlaySound(SoundManager::getInstance().GetSound("reload"));

                }
                

            }else if (CheckCollisionPointRec(mousePosition, drawerBounds) && openDrawer){
                openDrawer = false;
                PlaySound(SoundManager::getInstance().GetSound("CloseDrawer"));
            }

            if (CheckCollisionPointRec(mousePosition, ComputerBounds) && !showAPUI){
                showAPUI = true;
            }else{
                showAPUI = false;
            }



        }else if (gameState == OUTSIDE){
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                if (player.enter_car && buttonCemetery){ //press buttons cemetery
                    move_car = true;
                    show_carUI = false;
                }else if (player.enter_car && buttonWork){//button press work
                    //do something
                    gotoWork = true;
                    move_car = true;
                    hasWorked = true;
                }
            }

        }else if (gameState == CEMETERY){
            if (player.enter_car && buttonCemetery){//button press street
            //move_car = true;
                transitionState = FADE_OUT;
                //dont reset yet
                raiseZombies = false; //reset zombie waves. So returning player will trigger them again. 
                zombieWave2 = false;
                zombieWave3 = false;

            }
        }   

    }

}

void addMoney(int amount){
    money += amount;
}

void updateMoney(){
    if (displayMoney < money){
        displayMoney++;
    }else if (displayMoney > money){
        displayMoney--;
    }

}
void DrawMoney(){
    std::string smoney = "$ " + std::to_string(displayMoney);
    DrawText(smoney.c_str(), screenWidth/2+400, 25, 30, WHITE);
    updateMoney();
}

//Factory function to creat NPCs
NPC CreateNPC(Texture2D texture, Vector2 position, float speed, AnimationState initialState, bool isActive, bool isZombie) {
    return NPC(texture, position, speed, initialState, isActive, isZombie);
}


// Generates a random position along the x-axis, relative to the player's position
Vector2 GetRandomSpawnPositionX(Vector2 playerPos, float minDistance, float maxDistance) {
    // Randomly pick an x offset within the given distance range
    float randomXOffset = minDistance + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxDistance - minDistance)));

    // Randomly decide whether the zombie spawns to the left or right of the player
    bool spawnOnRight = rand() % 2 == 0;

    // Adjust the spawn position based on the player's position and direction
    float spawnX = spawnOnRight ? playerPos.x + randomXOffset : playerPos.x - randomXOffset;

    return Vector2{spawnX, playerPos.y};  // Keep the same y position as the player
}

void StartZombieSpawn(int zombie_count){
    remainingZombiesToSpawn = zombie_count;
    spawnTimer = 0.0f; //reset timer
    nextSpawnDelay = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 3.0f));  // Random delay between 1-4 seconds

    glitch = true; //Activate glitch shader to make things more dramatic
}

void UpdateZombieSpawning(GameResources& resources, Player& player){
    if (remainingZombiesToSpawn > 0){
        spawnTimer += GetFrameTime();

        if (spawnTimer >= nextSpawnDelay){ // spawn zombies at randomm position around the player
            Vector2 z_pos = GetRandomSpawnPositionX(player.position, 50.0f, 200.0f);  // Min/max distance from player
            int zombie_speed = 25;
            NPC zombie_npc = CreateNPC(resources.zombieSheet, z_pos, zombie_speed, RISING, true, true);
            zombie_npc.SetDestination(1000, 4000);
            zombies.push_back(zombie_npc);
            

            int soundIndex = rand() % 3; //zombie moans while rising.
            switch (soundIndex){  
                case 0:
                    PlaySound(SoundManager::getInstance().GetSound("moan1"));
                    break;
                
                case 1:
                    PlaySound(SoundManager::getInstance().GetSound("moan2"));
                    break;

                case 2:
                    PlaySound(SoundManager::getInstance().GetSound("moan3"));
                    break;
            }
 
            // Reset the spawn timer and set a new random delay
            spawnTimer = 0.0f;
            nextSpawnDelay = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.0f));  // Random delay for the next zombie

            // Decrease the number of zombies left to spawn
            remainingZombiesToSpawn--;
        }
    }else{
        glitch = false; //glitch only runs if zombies are actively spawning.

    }

}


void spawnZombies(GameResources& resources,int zombie_count){
    //spawn zombies in balk
    int zombie_speed = 25;
    
    for (int i = 0; i < zombie_count; i++){
        Vector2 z_pos = {2500 + i * 200, 700};
        NPC zombie_npc = CreateNPC(resources.zombieSheet, z_pos, zombie_speed,RISING, true, true);
        zombie_npc.SetDestination(1000, 4000);
        zombies.push_back(zombie_npc);
        
        
    }

}


void HandleOutsideTransition(Player& player, PlayerCar& player_car, std::vector<NPC>& npcs) {
    if (move_car && !gotoWork) {  // Car is moving, go to road
        gameState = ROAD;
        player_car.facingLeft = true;  // Leaving outside = face left
        if (!reverse_road) {
            player_car.position.x = 900;
        }
    } else if (move_car && gotoWork) {  // Move car and go to work
        gameState = WORK;
        // Additional logic if needed
    } else if (player.isDead) {  // Died outside, go to apartment
        gameState = APARTMENT;
        player.position.x = apartmentX;
        player.currentHealth = player.maxHealth;
        for (NPC& npc : npcs) {
            if (npc.police) {
                npc.agro = false;  // Turn off police aggression
                npc.attacking = false;
            }
        }
    } else if (over_apartment) {  // Over apartment, go to apartment
        gameState = APARTMENT;
    } else if (over_lot) { // over_lot go to Vacant Lot
        gameState = LOT;
    }else if (openMagicDoor){
        gameState = ASTRAL;
        
        //player.position.x = 3000;
        
    }
}

void HandleApartmentTransition(Player& player) {
    gameState = OUTSIDE;  // Go back outside
}

void HandleRoadTransition(Player& player, PlayerCar& player_car) {
    if (!reverse_road) {
        gameState = CEMETERY;
        player_car.position.x = 3000;
    } else {
        gameState = OUTSIDE;
        player_car.position.x = pc_start_pos.x;
        player.position.x = 1738;
        reverse_road = false;
        leave_cemetery = false;
        move_car = false;  // Prevent double fade-outs maybe
    }
}

void HandleCemeteryTransition(Player& player, PlayerCar& player_car, GameCalendar& calendar) {
    reverse_road = true;
    player_car.facingLeft = false;
    move_car = false;

    if (!player.isDead && player.enter_car) {
        gameState = ROAD;
        player_car.position.x = 100;
    } else if (!player.enter_car && over_gate) {
        gameState = GRAVEYARD;
        raiseZombies = true;  // Queue up more zombies for graveyard
    } else if (player.isDead) {
        gameState = APARTMENT;//wake up back at your apartment with full health. 
        player.position.x = apartmentX;
        player.isDead = false;
        player.currentHealth = player.maxHealth;
        calendar.AdvanceDay();
    }
}

void HandleGraveyardTransition(Player& player, GameCalendar& calendar, std::vector<NPC>& ghosts){
    if (player.isDead){
        gameState = APARTMENT;//wake up back at your apartment with full health.
        player.position.x = apartmentX;
        player.isDead = false;

        player.currentHealth = player.maxHealth;
        calendar.AdvanceDay();

    }else{ //presumably over gate and fading out
        gameState = CEMETERY;
        for (NPC& ghost : ghosts)
            if (ghost.agro){
                ghost.agro = false; //ghost looses agro when you leave graveyard. 
            }
        
    }
}

void HandleWorkTransition(Player& player) {
    gotoWork = false;
    move_car = false;
    hasWorked = true;
    gameState = OUTSIDE;
    player.position.x = pstart_by_car.x;
    addMoney(100);
}

void HandleLotTransition(Player& player) {
    gameState = OUTSIDE;
    player.position.x = vacantLotX;
}

void HandleAstralTransition(Player& player, GameCalendar& calendar){
    if (player.isDead){
        gameState = APARTMENT;//wake up back at your apartment with full health.
        player.position.x = apartmentX;
        player.isDead = false;
        applyShader = false; //drugs ware off if you advanced the day
        player.currentHealth = player.maxHealth;
        calendar.AdvanceDay();
        for (NPC& ghost : astralGhosts){
            ghost.agro = false; //ghost lose agro after dying. 

        }
    }else{
        gameState = OUTSIDE;
        player.gravity = 800; //reset gravity on leaving astral plane. 
        for (NPC& ghost : astralGhosts){
            ghost.agro = false; //ghost lose agro after leaving the plane. 
        }
    }

}

void PerformStateTransition(Player& player, PlayerCar& player_car, GameCalendar& calendar, std::vector<NPC>& npcs) {
    //if we are fading out switch to the next area depending on the situation. 
    switch (gameState) {
        case OUTSIDE:
            HandleOutsideTransition(player, player_car, npcs);
            break;
        case APARTMENT:
            HandleApartmentTransition(player);
            break;
        case ROAD:
            HandleRoadTransition(player, player_car);
            break;
        case CEMETERY:
            HandleCemeteryTransition(player, player_car, calendar);
            break;
        case WORK:
            HandleWorkTransition(player);
            break;
        case LOT:
            HandleLotTransition(player);
            break;
        case GRAVEYARD:
            HandleGraveyardTransition(player, calendar, ghosts);
            break;

        case ASTRAL:
            HandleAstralTransition(player, calendar);
            break;
  
    }
}

void DrawFadeMask() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, fadeAlpha));
}



void HandleFadeIn() {
    fadeAlpha -= fadeSpeed;  // Fade in gradually
    if (fadeAlpha <= 0.0f) {
        fadeAlpha = 0.0f;
        transitionState = NONE;  // Fade-in complete
    }
}

void HandleFadeOut(Player& player, PlayerCar& player_car, GameCalendar& calendar, std::vector<NPC>& npcs) {
    fadeAlpha += fadeSpeed;  // Fade out gradually
    if (fadeAlpha >= 1.0f) {
        fadeAlpha = 1.0f;

        // Start blackout timer when fully faded out
        blackoutTimer += GetFrameTime();
        if (blackoutTimer >= blackoutTime) {
            blackoutTimer = 0.0f;  // Reset blackout timer

            // Transition to the next state
            PerformStateTransition(player, player_car, calendar, npcs);

            if (!gotoWork) {  // Don't fade in when at work; fade in later
                transitionState = FADE_IN;  // Start fading back in
            }
        }
    }
}



void HandleTransition(Player& player, PlayerCar& player_car, GameCalendar& calendar, std::vector<NPC>& npcs) {
    if (firstTransition) {
        fadeAlpha = 0.0f;  // Ensure it starts at 0 for the first fade
        firstTransition = false;  // Reset flag after first transition
    }

    if (transitionState == FADE_IN) {
        HandleFadeIn();
    } else if (transitionState == FADE_OUT) {
        HandleFadeOut(player, player_car, calendar, npcs);
    }

    // Reset player position and health on death
    if (player.currentHealth <= 0 && !player.isDead) {
        player.isDead = true;
        transitionState = FADE_OUT;
    }

    // Draw the fade mask
    if (transitionState != NONE) {
        DrawFadeMask();
    }
}


void Dig(Player& player){
   if (player.position.x > 1860 && player.position.x < 1880 && !hasPills && gameState == CEMETERY){ //over dig spot
        hasPills = true; //if you dont have pill you can allways get more here. 
        AddItemToInventory("pills", inventory, INVENTORY_SIZE);
        showInventory = true;
        PlaySound(SoundManager::getInstance().GetSound("ShovelDig"));
        shovelTint = RED;
    }

    if (digSpot && gameState == LOT){
        PlaySound(SoundManager::getInstance().GetSound("ShovelDig"));
        shovelTint = RED;
        if (!player.hasShotgun){
            AddItemToInventory("shotgun", inventory, INVENTORY_SIZE);
            player.hasShotgun = true;
            PlaySound(SoundManager::getInstance().GetSound("ShotgunReload"));
        }

    }

    //far right side of cemetery is an item. 
                // if (player.position.x > 3986 && player.position.x < 4016 && gameState == CEMETERY && !hasCemeteryKey){
                //     PlaySound(SoundManager::getInstance().GetSound("ShovelDig"));
                //     shovelTint = RED;
                //     hasCemeteryKey = true;
                //     AddItemToInventory("cemeteryKey", inventory, INVENTORY_SIZE);

                // }
}




Vector2 Lerp(Vector2 start, Vector2 end, float t) {
    return Vector2{
        start.x + t * (end.x - start.x),
        start.y + t * (end.y - start.y)
    };
}

void UpdateInventoryPosition(const Camera2D& camera, GameState& gameState) {
    // Static inventory position, relative to the camera offset
    inventoryPositionX = camera.offset.x;  // Adjust the X position relative to the screen (e.g., 200 pixels left of the center)
    if (gameState == APARTMENT){
        inventoryPositionY = camera.offset.y + 228;
    }else{
        inventoryPositionY = camera.offset.y + 228;  // Adjust the Y position (e.g., 300 pixels below the center)
    }
    
}

void drawDeadZombie(GameResources& resources,Player& player, Vector2 bodyPosition,Vector2& mouseWorldPos){
    //The first zombie that is killed in the graveyard drops a dead body you can click on and get the ID badge. 
    DrawTexture(resources.deadZombie, bodyPosition.x, bodyPosition.y, WHITE);
    Rectangle bodyBounds = {
        bodyPosition.x,      // X position
        bodyPosition.y,      // Y position
        static_cast<float>(64),  // Width of the texture
        static_cast<float>(64)  // Height of the texture
    };
    int distance = abs(player.position.x - bodyPosition.x);
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){ //if key up next to body
        if (distance < 30 && !player.hasBadge){
            AddItemToInventory("Badge", inventory, INVENTORY_SIZE);
            player.hasBadge = true;
            showInventory = true;
            show_dbox = true;
            phrase = "ID card of an employee\n\nA company named NecroTech";
            badgeTimer = 7.0; //show text for 7 seconds
            dboxPosition = player.position;
        }
    }
    if (CheckCollisionPointRec(mouseWorldPos, bodyBounds)){ //if click on body
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            if (distance < 30 && !player.hasBadge){
                AddItemToInventory("Badge", inventory, INVENTORY_SIZE);
                player.hasBadge = true;
                showInventory = true;
                show_dbox = true;
                phrase = "ID card of an employee\n\nA company named NecroTech";
                badgeTimer = 7.0;
                dboxPosition = player.position;
            }
        }
        
    }

}


void RenderInventory(const GameResources& resources, std::string inventory[], int inventorySize, Player& player, Vector2& mousePosition) {
    int slotWidth = resources.inventorySlot.width;
    shovelTint = WHITE;
    Color gunTint = WHITE;
    Color shotgunTint = WHITE;
    // Use integer values to snap to the nearest pixel, based on the camera-relative inventory position
    //casting to int was to prevent stutter. not needed no mo.
    int startX = static_cast<int>(inventoryPositionX) - (slotWidth * inventorySize / 2);
    int startY = static_cast<int>(inventoryPositionY);

    // Draw each inventory slot
    for (int i = 0; i < inventorySize; i++) {
        int x = startX + (i * (slotWidth + 10));  // Offset each slot horizontally
        int y = startY;

        // Draw the inventory slot texture
        DrawTexture(resources.inventorySlot, x, y, WHITE);
        Color customTint = {255, 100, 100, 255}; // light red
        if (player.currentWeapon == SHOTGUN) shotgunTint = customTint;
        if (player.currentWeapon == REVOLVER) gunTint = customTint;
       // Draw the icon at x, y
        if (!inventory[i].empty()) { //inventory buttons are all done in the same for loop we use to draw it. 

            if (inventory[i] == "carKeys"){
                DrawTexture(resources.CarKeys, x, y, WHITE);
                
            }
            if (inventory[i] == "Badge"){
                DrawTexture(resources.Badge, x, y, WHITE);
            }
            if (inventory[i] == "Gun"){
                DrawTexture(resources.Revolver, x, y, gunTint);
            }
            if (inventory[i] == "shotgun"){
                DrawTexture(resources.shotgunIcon, x, y, shotgunTint);
            }

            if (inventory[i] == "cemeteryKey"){
                DrawTexture(resources.cemeteryKey, x, y, WHITE);
            }

            if (inventory[i] == "pills"){ // click on pills to take them 
                DrawTexture(resources.pills, x, y, WHITE);
                Rectangle pillBounds = { //pill button
                    x,      
                    y,      
                    static_cast<float>(64),  
                    static_cast<float>(64)  
                };

                if (CheckCollisionPointRec(mousePosition, pillBounds)){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        if (player.currentHealth < player.maxHealth && hasPills){
                            inventory[i] = std::string("");  // erase pills from the string
                            player.currentHealth = player.maxHealth;
                            hasPills = false;
                            PlaySound(SoundManager::getInstance().GetSound("Pills"));

                        }
                    }
                }

            }

            if (inventory[i] == "shovel"){
                Rectangle shovelBounds = { //shovel button
                    x,      
                    y,      
                    static_cast<float>(64),  
                    static_cast<float>(64)  
                };

                if (CheckCollisionPointRec(mousePosition, shovelBounds)){ //dig
                    
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        Dig(player);
                     
                    }
                }
                DrawTexture(resources.shovel, x, y, shovelTint); //draw shovel after button to tint the color on press

            }

            if (inventory[i] == "Drugs"){
                DrawTexture(resources.Drugs, x, y, WHITE);
                Rectangle textureBounds = { //drug button
                    x,      
                    y,      
                    static_cast<float>(64),  
                    static_cast<float>(64)  
                };

                if (CheckCollisionPointRec(mousePosition, textureBounds)){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        inventory[i] = std::string("");  // erase drugs from the string
                        applyShader = true;
                        can_sell_drugs = true;
                    }
                }
            }
        
        }
    }
     
    
}



void CheckBulletNPCCollisions(std::vector<NPC>& npcs) {
    Vector2 bulletSize = {1, 1};  // Size of the bullet hitbox

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {  // Only check active bullets
            for (NPC& npc : npcs) { //zombies is passed as npcs
                if (npc.isActive && npc.CheckHit(bullets[i].previousPosition, bullets[i].position, bulletSize)) { //
                    // Collision detected
                    bullets[i].isActive = false;  // Deactivate the bullet
                    npc.TakeDamage(25);  // Apply 25 damage to the NPC
                    break;  // Exit loop since the bullet is deactivated
                }
            }
        }
    }
}


void DrawHUD(const Player& player) {
    float ammoY = 875.0;
    float ammoX = 140.0;
    if (player.currentWeapon == REVOLVER && player.hasGun){
        DrawText(TextFormat("Ammo: %d", player.revolverBulletCount), screenWidth/2 + ammoX, ammoY, 20, WHITE); //screen space coordiantes
    }else if (player.currentWeapon == SHOTGUN && player.hasShotgun){
        DrawText(TextFormat("Ammo: %d", player.shotgunBulletCount), screenWidth/2 + ammoX, ammoY, 20, WHITE); //screen space coordiantes
        DrawText(TextFormat("SHELLS: %d", player.shells), screenWidth/2 + ammoX, ammoY+20, 20, WHITE); //screen space coordiantes
    }
    
}


void MoveTraffic(GameResources resources){
    
    int car_start = 4500;
    car_pos.x -= 150 * GetFrameTime();
    truck_pos.x += 150 * GetFrameTime();

    if (car_pos.x < 0) car_pos.x = car_start; //Loop back to car_start
 
    if (truck_pos.x > 4500) truck_pos.x = 512;
    
    DrawTexture(resources.car, car_pos.x, car_pos.y, WHITE);
    DrawTexture(resources.truck, truck_pos.x, truck_pos.y + 32, WHITE);
    
}

void DrawApartmentUI(GameResources& resources, GameCalendar&, Vector2& mousePosition, Camera2D& camera){
    Vector2 ui_pos = {screenWidth/2-100, 440};
    DrawTexture(resources.ComputerScreen, ui_pos.x, ui_pos.y, WHITE);
    Color tint = WHITE;
    Color Itint = WHITE;
    Vector2 TextPos = {ui_pos.x + 85, ui_pos.y + 60};
    Rectangle textureBounds = {
        TextPos.x,      // X position
        TextPos.y,      
        static_cast<float>(128),  // Width of the texture
        static_cast<float>(16)  // Height of the texture
    };

    Rectangle internetBounds = {
        TextPos.x,
        TextPos.y+20,
        static_cast<float>(128),
        static_cast<float>(16)

    };

    if (CheckCollisionPointRec(mousePosition, textureBounds)){
        tint = RED;
        
        buttonSleep = true;
    }else{
        buttonSleep = false;
    }

    if (CheckCollisionPointRec(mousePosition, internetBounds)){
        Itint = RED;
        buttonInternet = true;

    }else{
        buttonInternet = false;
    }



    if (hasSlept) tint = BLACK;
    DrawText("     Sleep", TextPos.x, TextPos.y, 20, tint);
    DrawText("    Internet", TextPos.x, TextPos.y + 21, 20, Itint);
}



void DrawCarUI(PlayerCar& player_car, Vector2 mousePosition, Camera2D& camera, GameState& gameState){
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);
    Vector2 ui_pos = player_car.position;
    int ui_width = 96;
    int ui_height = 50;


    DrawRectangle(ui_pos.x, ui_pos.y - 17, ui_width, ui_height, customBackgroundColor);
    Color work_tint = WHITE;
    Color cemetery_tint = WHITE;
    Color tavern_tint = WHITE;
    Rectangle textureBounds = { //cemetery
        player_car.position.x,      
        player_car.position.y,      
        static_cast<float>(96),  
        static_cast<float>(16)  
    };

    Rectangle textureBounds2 = { //work
        player_car.position.x,      
        player_car.position.y+16,      
        static_cast<float>(96),  
        static_cast<float>(16)  
    };

    Rectangle textureBounds3 = { //Tavern
        player_car.position.x,      
        player_car.position.y-16,      
        static_cast<float>(96),  
        static_cast<float>(16)  
    };

    if (CheckCollisionPointRec(mouseWorldPos, textureBounds)){ //middle //cemetery/street
        cemetery_tint = RED;
        buttonCemetery = true;
    }else{
        buttonCemetery = false;
    }

    if (CheckCollisionPointRec(mouseWorldPos, textureBounds2) && !hasWorked && gameState == OUTSIDE){ //bottom
        work_tint = RED;
        buttonWork = true;
    }else{
        buttonWork = false;
    }

    if (CheckCollisionPointRec(mouseWorldPos, textureBounds3)){ //top
        tavern_tint = RED;
        buttonTavern = true;
    }else{
        buttonTavern = false;
    }
    if (gameState == OUTSIDE){
        DrawText("   Tavern", ui_pos.x, ui_pos.y-17, 16, tavern_tint);
        DrawText("   Cemetery", ui_pos.x, ui_pos.y, 16, cemetery_tint);

        work_tint = hasWorked ? BLACK : work_tint;
        DrawText("    Work", ui_pos.x, ui_pos.y+17, 16, work_tint);


        

    }else if (gameState == CEMETERY){
        
        DrawText("   Street", ui_pos.x, ui_pos.y, 16, cemetery_tint);
        //DrawText("Work", ui_pos.x, ui_pos.y+17, 16, work_tint);
    }

}

void DrawMagicDoor(GameResources& resources,Player& player, MagicDoor& magicDoor){
        int doorFrame = 64;
        Rectangle sourceDoorRec = {magicDoor.currentFrame * doorFrame, 0, doorFrame, doorFrame};
        DrawTextureRec(resources.magicDoorSheet, sourceDoorRec, magicDoor.position, WHITE);
        if (player.position.x > magicDoor.position.x -10 && player.position.x < magicDoor.position.x +10){ //over magic door
            if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
                openMagicDoor = true;
                transitionState = FADE_OUT;
            }
        }
        if (openMagicDoor){
            float deltaTime = GetFrameTime();

            // Update animation timer
            DoorframeTimer += deltaTime;

            // Check if it's time to move to the next frame
            if (DoorframeTimer >= DoorframeTime)
            {
                DoorframeTimer -= DoorframeTime;           // Reset the timer
                magicDoor.currentFrame++;                    // Move to the next frame

                if (magicDoor.currentFrame > 6)              // Loop back to the first frame if necessary
                {
                    magicDoor.currentFrame = 6; //stop at last frame when door is open. 
                }
            }
        }

}

void DrawEarth(GameResources& resources, Earth& earth, Camera2D& camera){
    // Calculate delta time
    float deltaTime = GetFrameTime();
    //printf("Camera Target X: %f\n", camera.target.x);
    // Update animation timer
    earth.frameTimer += deltaTime;

    // Check if it's time to move to the next frame
    if (earth.frameTimer >= earth.frameTime)
    {
        earth.frameTimer -= earth.frameTime;
        earth.currentFrame++;

        if (earth.currentFrame >= earth.totalFrames)
        {
            earth.currentFrame = 0; // Loop back to the first frame
        }
    }

    // Calculate current frame's row and column
    int frameRow = earth.currentFrame / 10; // Each row has up to 10 frames
    int frameCol = earth.currentFrame % 10;

    // Adjust for the last row, which has only 4 frames
    if (frameRow == 9 && frameCol >= 4)
    {
        // Reset to the first frame since there are only 4 frames in the last row
        earth.currentFrame = 0;
        frameRow = 0;
        frameCol = 0;
    }

    
    
    
    // Define the source rectangle
    Rectangle sourceRect = {
        static_cast<float>(frameCol * earth.frameWidth),
        static_cast<float>(frameRow * earth.frameHeight),
        static_cast<float>(earth.frameWidth),
        static_cast<float>(earth.frameHeight)
    };

    // Calculate parallax offset for the earth
    float parallaxFactor = 0.99f; // Adjust this value between 0.0f and 1.0f

    float parallaxOffset = (camera.target.x - earth.position.x) * parallaxFactor; //playerpos - earthpos = distance * .99
    

    Vector2 earthDrawPosition = {
        earth.position.x + parallaxOffset, //offset x by 99 percent of the distance to it moves at 1 percent of player speed
        earth.position.y 
    };

    
    
    // Draw the current frame of the earth with the adjusted position
    DrawTextureRec(resources.EarthSheet, sourceRect, earthDrawPosition, WHITE); 



}


void DrawHealthBar(GameResources resources, Vector2 position, int maxHealth, int currentHealth, int barWidth, int barHeight) {
    // Calculate health percentage
    float healthPercent = (float)currentHealth / maxHealth;
    Color veryLightGreen = { 150, 255, 150, 255 };  // RGBA values
    // Define bar colors
    Color borderColor = veryLightGreen;  // Border color
    Color barColor = veryLightGreen;       // Color of the health bar itself

    if (healthPercent <= 0.3f){
        barColor = RED;
        borderColor = RED;
    }else{
        barColor = veryLightGreen;
        borderColor = veryLightGreen;
    }

    Texture2D texture = resources.healthBorder;

    // Define the source rectangle (the part of the texture to draw)
    Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle destRec = { 
        position.x, // x position on screen
        position.y+50, // y position on screen
        static_cast<float>(barWidth), // width on screen
        static_cast<float>(barHeight)  // height on screen
    };
    Vector2 origin = { 0.0f, 0.0f };

    // Rotation angle in degrees
    float rotation = 0.0f;

    //stretch texture to fit barwidth and height,
    DrawTexturePro(texture, sourceRec, destRec, origin, rotation, borderColor);


    //DrawRectangleLines(position.x, position.y+50, barWidth, barHeight, borderColor);

    // Draw health bar (adjust width based on health percentage)
    DrawRectangle(position.x, position.y+50, (int)(barWidth * healthPercent), barHeight, barColor);
}

void DrawDialogBox(Camera2D camera, int boxWidth, int boxHeight,int textSize){
    //int boxWidth = 256;
    //int boxHeight = 64;
    int offset = -64;
    int screen_offsetX = 16;
    int screen_offsetY = -55;

    if (fortuneTimer > 0){

;        fortuneTimer -= GetFrameTime();
    }
    Vector2 screen_pos = GetWorldToScreen2D(dboxPosition, camera); // position to draw text and rectangle at. position is set to npc position
    Color tint = WHITE;
    if (dealer){
        boxWidth = 256;
        boxHeight = 128;
        offset = -135;
        screen_offsetX = 16;
        screen_offsetY = -128;

    }
    if (teller){
        boxWidth = 300;
        boxHeight = 128;
        offset = -135;
        screen_offsetX = 16;
        screen_offsetY = -128;
       
    }

    if (teller && buyFortune && fortuneTimer <= 0){
        phrase = "Namaste";
    }

    
    DrawRectangle(screen_pos.x, screen_pos.y + offset, boxWidth, boxHeight, customBackgroundColor);
    DrawText(phrase.c_str(), screen_pos.x+ screen_offsetX, screen_pos.y + screen_offsetY, textSize, tint); //Draw Phrase
    
    if (money >= 100 && dealer && GuiButton((Rectangle){ screen_pos.x+16, screen_pos.y-64, 64,48 }, "BUY")) //button pressed
        {
            if (can_sell_drugs){ //can sell drugs gets reset once you take the drug
                can_sell_drugs = false; // Dealer only has 1 drug for now. 
                addMoney(-100);
                AddItemToInventory("Drugs", inventory, INVENTORY_SIZE);
                for (NPC& npc : npcs)
                    if (npc.interacting){
                        npc.interacting = false;
                        npc.idleTime = 1;
                    }
            }
        }

    if (teller && !buyFortune && money >= 100 &&  GuiButton((Rectangle){ screen_pos.x+16, screen_pos.y-64, 64,48 }, "BUY")){

        if (canGiveFortune){
            canGiveFortune = false;
            buyFortune = true;
            fortuneTimer = 5;
            
            addMoney(-100);
            phrase = GetTellerPhrase();
            for (NPC& npc: npcs)
                if (npc.teller){
                    npc.idleTime = 10;
                    npc.talkTimer = 30;
                } 
        }


    }

}

void RenderAstral(GameResources& resources, Player& player, Camera2D& camera, Vector2& mousePosition,Earth& earth,MagicDoor& magicDoor, Shader& drunkShader, Shader& glowShader, Shader& glitchShader){
    player.gravity = 200;
    if (player.isAiming && IsKeyDown(KEY_F)) {
        // Handle keyboard-only aiming (e.g., using arrow keys or player movement keys)
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            player.facingRight = true;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            player.facingRight = false;
        }
    }else if (player.isAiming && !IsKeyDown(KEY_F)) {// If the player is not aiming with keyboard, allow mouse control to set the facing direction
        // Set facing direction based on mouse position
        player.facingRight = mousePosition.x > player.position.x; //facing right is true if mousepos.x > playerPos.x
    }

    magicDoor.position.x = 2089;
    camera.target = player.position;
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxClouds2 = camera.target.x * .7;
    float parallaxClouds = camera.target.x * .8;
    float parallaxBackground = camera.target.x * 0.9f;  // Background moves even slower 
    
    show_dbox = false;
    
    BeginMode2D(camera);
    
    ClearBackground(customBackgroundColor);
    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera);
    if (!IsKeyDown(KEY_F)){
        if (player.isAiming) player.facingRight = worldMousePosition.x > player.position.x;//Hack to make aiming work both ways
    } 

    if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }

    // Draw the background layers
    DrawTexturePro(resources.AstralBackground, {0, 0, static_cast<float>(resources.AstralBackground.width), static_cast<float>(resources.AstralBackground.height)},
                    {parallaxBackground-1024, -2000, static_cast<float>(resources.AstralBackground.width), static_cast<float>(resources.AstralBackground.height)}, {0, 0}, 0.0f, WHITE);

    

    DrawTexturePro(resources.AstralClouds, {0, 0, static_cast<float>(resources.AstralBackground.width), static_cast<float>(resources.AstralBackground.height)},
                    {parallaxClouds -1024, 0, static_cast<float>(resources.AstralBackground.width), static_cast<float>(resources.AstralBackground.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.AstralClouds2, {0, 0, static_cast<float>(resources.AstralBackground.width), static_cast<float>(resources.AstralBackground.height)},
                    {parallaxClouds2 -1024, 0, static_cast<float>(resources.AstralBackground.width), static_cast<float>(resources.AstralBackground.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.AstralMidground, {0, 0, static_cast<float>(resources.AstralMidground.width), static_cast<float>(resources.AstralMidground.height)},
                    {parallaxMidground -1024, 0, static_cast<float>(resources.AstralMidground.width), static_cast<float>(resources.AstralMidground.height)}, {0, 0}, 0.0f, WHITE);
    

    EndShaderMode(); ////////////////////////////SHADER OFF
    DrawEarth(resources, earth, camera);
    
    DrawMagicDoor(resources, player, magicDoor);
    player.DrawPlayer(resources, gameState, camera);

    DrawTexturePro(resources.AstralForeground, {0, 0, static_cast<float>(resources.AstralMidground.width), static_cast<float>(resources.AstralMidground.height)},
                    {0, 0, static_cast<float>(resources.AstralMidground.width), static_cast<float>(resources.AstralMidground.height)}, {0, 0}, 0.0f, WHITE);


        // Draw platforms
    for (Platform& platform : platforms) {
     
        //platform.Draw();
       
        platform.DrawPlatformTexture(resources.platformTexture, platform.rect);
        
    }


    for (NPC& ghost: astralGhosts){
        ghost.Update(player);
        ghost.Render();
        
        if (ghost.health > 0) ghost.isActive = true;

    }

    
    DrawBullets(); //draw bullets in cemetery after everything else. 
    
    
    EndMode2D();
    DrawMoney(); //draw money after EndMode2d()
    Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
    if (player.currentHealth < 100){
        DrawHealthBar(resources,barPos, player.maxHealth, player.currentHealth, 128, 16);  
    }
    

    if (showInventory){
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);  // Render the inventory 
    }
    if (player.hasGun){//DRAW RETICLE IF AIMING AND HAS GUN
        DrawTexture(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ? resources.reticle : resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // if aiming draw reticle
    }else{
        DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE);
    }

    if ((player.hasGun || player.hasShotgun) && !player.enter_car) DrawHUD(player);

    if (show_dbox){
        DrawDialogBox(camera, 0, 0, 20);
    }

    
}


void RenderCemetery(GameResources& resources,Player& player, PlayerCar& player_car, Camera2D& camera,Vector2 mousePosition, Shader& drunkShader, Shader& glowShader, Shader& glitchShader){
    int carMax = 2800;
    int carMin = 2765;
    
    
    playOwl = false; //reset owl
    // Maybe zombiewaves can be reset to false when exiting cemetery. 
    if (player.isAiming && IsKeyDown(KEY_F)) {
        // Handle keyboard-only aiming (e.g., using arrow keys or player movement keys)
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            player.facingRight = true;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            player.facingRight = false;
        }
    }else if (player.isAiming && !IsKeyDown(KEY_F)) {// If the player is not aiming with keyboard, allow mouse control to set the facing direction
        // Set facing direction based on mouse position
        player.facingRight = mousePosition.x > player.position.x; //facing right is true if mousepos.x > playerPos.x
    }
    
    //dont spawn unless raise zombies is true. raise zombies is set to true by talking to the hobo. 
    if (!player.enter_car && player.position.x < 1900 && !zombieWave3 && !firstHobo){ // walk to far left and zombies spawn again
        zombieWave3 = true;
        StartZombieSpawn(10);
    }
    if (!player.enter_car && player.position.x > 3500 && !zombieWave2 && !firstHobo){ //walk too far right and zombies spawn again
        zombieWave2 = true;
        StartZombieSpawn(10);
    }

    if (move_car){
        player_car.carSpeed = 100;
        
        player_car.position.x -= player_car.carSpeed * GetFrameTime();
        camera.target = Vector2{player_car.position.x, 700}; // offset camera target to be equal to player_pos.y
        player.position.x = player_car.position.x;
        //EndBlendMode();
    }
    
    if (!player.enter_car && raiseZombies){
        //zombies that spawn when you exit car
        raiseZombies = false;
        if (hasCemeteryKey){
            StartZombieSpawn(10); //you should have the shotgun here so spawn more. 
        }else{
            StartZombieSpawn(5);

        }
        
        
    }

    show_dbox = false;
    over_gate = false;
    if (player.position.x > 3069 && player.position.x < 3089 && hasCemeteryKey){
            phrase = "UP TO ENTER";
            over_gate = true;
            show_dbox = true;
            dboxPosition = player.position;

        }
    
        
    

    if (player_car.position.x < carMin && !leave_cemetery){
        move_car = false;
    }

   if (player.position.x > carMin && player.position.x < carMax){
        over_car = true;
        
   }else{
        over_car = false; 
   }

    BeginMode2D(camera);
    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera);
    if (!IsKeyDown(KEY_F)){
        if (player.isAiming) player.facingRight = worldMousePosition.x > player.position.x;//Hack to make aiming work both ways
    }
    
    
    ClearBackground(customBackgroundColor);
    if (!move_car && !player.enter_car){
        camera.target = player.position;
    }
    
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxTrees = camera.target.x * .8;
    float parallaxBackground = camera.target.x * 0.9f;  // Background moves even slower 

    //BeginShaderMode(shader);


    if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }

    // Draw the background layers
    DrawTexturePro(resources.cemeteryBackground, {0, 0, static_cast<float>(resources.cemeteryBackground.width), static_cast<float>(resources.cemeteryBackground.height)},
                    {parallaxBackground-1024, 0, static_cast<float>(resources.cemeteryBackground.width), static_cast<float>(resources.cemeteryBackground.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.cemeteryTrees, {0, 0, static_cast<float>(resources.cemeteryTrees.width), static_cast<float>(resources.cemeteryTrees.height)},
                    {parallaxTrees-1024, 0, static_cast<float>(resources.cemeteryTrees.width), static_cast<float>(resources.cemeteryTrees.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.cemeteryMidground, {0, 0, static_cast<float>(resources.cemeteryMidground.width), static_cast<float>(resources.cemeteryMidground.height)},
                    {parallaxMidground, 0, static_cast<float>(resources.cemeteryMidground.width), static_cast<float>(resources.cemeteryMidground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),  offset by 1024 to center relative to midground. 
    DrawTexturePro(resources.cemeteryForeground, {0, 0, static_cast<float>(resources.cemeteryForeground.width), static_cast<float>(resources.cemeteryForeground.height)},
                    {1024, 0, static_cast<float>(resources.cemeteryForeground.width), static_cast<float>(resources.cemeteryForeground.height)}, {0, 0}, 0.0f, WHITE);

    //EndShaderMode();

    EndShaderMode(); ////////////////////////////SHADER OFF
    int CarFrameWidth = 128;
    Rectangle sourceRecCar = { static_cast<float>(player_car.currentFrame * CarFrameWidth), 0.0f, static_cast<float>(CarFrameWidth), static_cast<float>(CarFrameWidth) };

    //render player car
    DrawTextureRec(resources.carSheet, sourceRecCar, player_car.position, WHITE);
    if (player.enter_car){
        //render headlight/breaklight
        Vector2 breakLight_pos = {player_car.position.x + 88, player_car.position.y + 53};
        Vector2 light_pos = {player_car.position.x - 225, player_car.position.y + 32};

        BeginBlendMode(BLEND_ADDITIVE);
        DrawTextureV(resources.breakLight, breakLight_pos, WHITE);
        DrawTextureV(resources.lightBeam, light_pos, WHITE);
        EndBlendMode();

    }

    


    //render shovel. Click the shovel to pick it up. 

    Vector2 shovelPos = {1870, 700}; // render within 1900. where zombies trigger
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);
    float distance_to_shovel = abs(shovelPos.x - player.position.x);
    if (drawShovel){ //shovel pickup
        DrawTexture(resources.shovelWorld, shovelPos.x, shovelPos.y, WHITE);
        Rectangle shovelBounds = { //shovel button
            shovelPos.x,      
            shovelPos.y,     
            static_cast<float>(32),  
            static_cast<float>(64)  
        };

    
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& distance_to_shovel < 20){ //pickup shovel 
            if (CheckCollisionPointRec(mouseWorldPos, shovelBounds)){
                //add shovel in inventory
                if (!player.hasShovel){
                    drawShovel = false;
                    AddItemToInventory("shovel", inventory, INVENTORY_SIZE);
                    PlaySound(SoundManager::getInstance().GetSound("shovelPickup"));
                    showInventory = true;
                    player.hasShovel = true;
                
                }
            
            }


        }
        //Press up key or W to pickup shovel when close enough
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
            if (!player.hasShovel && distance_to_shovel < 20){
                drawShovel = false;
                AddItemToInventory("shovel", inventory, INVENTORY_SIZE);
                PlaySound(SoundManager::getInstance().GetSound("shovelPickup"));
                showInventory = true;
                player.hasShovel = true;
            
            }
        }
    }


    for (NPC& zombie : zombies){ //update and draw zombies in cemetery
        zombie.Update(player);
        zombie.Render();

    }

    if (hasCemeteryKey){
        for (NPC& bat : bats){
            bat.Update(player);
            bat.Render();
            bat.agro = true;
            if (bat.health > 0) bat.isActive = true;
        }

    }


    if (show_carUI && !move_car && player.enter_car){ //destination menu
        DrawCarUI(player_car, mousePosition, camera, gameState);
    }

    if (player.enter_car == false){// if enter car is false, dont render player or update position camera should stay focused on player pos. 
        player.DrawPlayer(resources, gameState, camera);

    }
    DrawBullets(); //draw bullets in cemetery after everything else. 

    EndMode2D();
    DrawMoney(); //draw money after EndMode2d()
    if (showInventory){
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);  // Render the inventory 
    }

    if (player.hasGun){//DRAW RETICLE IF AIMING AND HAS GUN
        DrawTexture(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ? resources.reticle : resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // if aiming draw reticle
    }else{
        DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE);
    }

    if (show_dbox){
        DrawDialogBox(camera, 0, 0, 20);
    }

    if (over_gate && hasCemeteryKey){
        DrawDialogBox(camera, 0, 0, 20);

    }
    
    

    if ((player.hasGun || player.hasShotgun) && !player.enter_car) DrawHUD(player); //always show ammo when outside of car in the cemetery

    //DrawText("Cemetery", screenWidth/2 - 100, 60, 50, WHITE);

    //draw healthbar 
    if (gameState == CEMETERY && !player.enter_car){
        Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
        DrawHealthBar(resources,barPos, player.maxHealth, player.currentHealth, 128, 16);

    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){//exit car
        if (player.enter_car && !move_car){
            SoundManager::getInstance().StopMusic("CarRun"); //turn off car audio when exiting car
            PlaySound(SoundManager::getInstance().GetSound("CarDoorClose"));
            player.enter_car = false;
            player_car.currentFrame = 0;
            player.position = Vector2{player_car.position.x + 32, 700};
            
        }
    }
    
}



void RenderRoad(const GameResources& resources, PlayerCar& player_car,Player& player, Camera2D& camera, Vector2 mousePosition, Shader& drunkShader, Shader& glowShader, Shader& glitchShader){
    if (player_car.position.x < 200 && !reverse_road){//transition to cemetery
        
        transitionState = FADE_OUT;
        move_car = true;

    if (!firstHobo && !playOwl){ // only play owl sound if zombies are going to spawn
        playOwl = true;
        PlaySound(SoundManager::getInstance().GetSound("Owl"));
    }

    }
    if (player_car.position.x > 800 && reverse_road){
        transitionState = FADE_OUT;

    }


    hasSlept = false; // player can sleep if they have traveled.

    if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }



    BeginMode2D(camera);
    DrawTexture(resources.road, screenWidth/2 - 1280, 0, WHITE);
    camera.target = Vector2 {512, 700};
    player_car.carSpeed = 200;

    if (!reverse_road){
        player_car.position.x -= player_car.carSpeed * GetFrameTime();
    }else{
        
        player_car.position.x += player_car.carSpeed * GetFrameTime();

    }
    
    
    float CarFrameWidth = 128.0;
    Rectangle sourceRecCar = {player_car.currentFrame * CarFrameWidth, 0, CarFrameWidth, CarFrameWidth};
    //Draw player car
    if (!player_car.facingLeft){
        sourceRecCar.width = -CarFrameWidth;       
    }
    DrawTextureRec(resources.carSheet, sourceRecCar, player_car.position, WHITE);

    if (player.enter_car){
        // Render headlight/brake light
        Vector2 breakLight_pos;
        Vector2 light_pos;
        float light_scale = 1.0f; // Default scale

        if (!reverse_road){
            // Positions when not reversing
            breakLight_pos = {player_car.position.x + 88, player_car.position.y + 53};
            light_pos = {player_car.position.x - 225, player_car.position.y + 32};
            light_scale = 1.0f; // Normal scale
        } else {
            // Positions when reversing
            breakLight_pos = {player_car.position.x+7, player_car.position.y + 54}; 
            light_pos = {player_car.position.x + 360, player_car.position.y + 108};   
            light_scale = -1.0f; // Negative scale to flip horizontally
        }

        BeginBlendMode(BLEND_ADDITIVE);
        DrawTextureV(resources.breakLight, breakLight_pos, WHITE);

        // Use DrawTextureEx to allow flipping
        DrawTextureEx(resources.lightBeam, light_pos, 0.0f, light_scale, WHITE);
        EndBlendMode();
    }
    
    EndShaderMode();
    EndMode2D();
    DrawMoney(); //draw money after EndMode2d()
    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // render mouse cursor outside Mode2D
   
}

void RenderGraveyard(GameResources resources,Player& player,Camera2D& camera,Vector2 mousePosition,Shader& drunkShader,Shader& glowShader,Shader& glitchShader){
    if (player.isAiming && IsKeyDown(KEY_F)) {
        // Handle keyboard-only aiming (e.g., using arrow keys or player movement keys)
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            player.facingRight = true;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            player.facingRight = false;
        }
    }else if (player.isAiming && !IsKeyDown(KEY_F)) {// If the player is not aiming with keyboard, allow mouse control to set the facing direction
        // Set facing direction based on mouse position
        player.facingRight = mousePosition.x > player.position.x; //facing right is true if mousepos.x > playerPos.x
    }

    if (player.position.x > 3437 and raiseZombies){
        raiseZombies = false;
        StartZombieSpawn(20);
    }

    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);


    BeginMode2D(camera);
    camera.target = player.position;
    //Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera);
    if (!IsKeyDown(KEY_F)){
        if (player.isAiming) player.facingRight = mouseWorldPos.x > player.position.x;//Hack to make aiming work both ways
    }
    float parallaxforeground = camera.target.x * 0.4;
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxTrees = camera.target.x * 0.8;
    float parallaxBackground = camera.target.x * 0.9f;  // Background moves even slower 
    
    if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }

    // Draw the background layers
    DrawTexturePro(resources.cemeteryBackground, {0, 0, static_cast<float>(resources.cemeteryBackground.width), static_cast<float>(resources.cemeteryBackground.height)},
                    {parallaxBackground-1024, 0, static_cast<float>(resources.cemeteryBackground.width), static_cast<float>(resources.cemeteryBackground.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.cemeteryTrees, {0, 0, static_cast<float>(resources.cemeteryTrees.width), static_cast<float>(resources.cemeteryTrees.height)},
                    {parallaxTrees-1024, 0, static_cast<float>(resources.cemeteryTrees.width), static_cast<float>(resources.cemeteryTrees.height)}, {0, 0}, 0.0f, WHITE);


    // Draw cemetery gate AKA midground
    DrawTexturePro(resources.GraveyardGate, {0, 0, static_cast<float>(resources.GraveyardGate.width), static_cast<float>(resources.GraveyardGate.height)},
                    {parallaxMidground-512, -64, static_cast<float>(resources.GraveyardGate.width), static_cast<float>(resources.GraveyardGate.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.GreaveyardMidground, {0, 0, static_cast<float>(resources.GraveyardGate.width), static_cast<float>(resources.GraveyardGate.height)},
                    {parallaxforeground, +136, static_cast<float>(resources.GraveyardGate.width), static_cast<float>(resources.GraveyardGate.height)}, {0, 0}, 0.0f, WHITE);

    //EndShaderMode();

    EndShaderMode(); ////////////////////////////SHADER OFF
    if (player.enter_car == false){// if enter car is false, dont render player or update position camera should stay focused on player pos. 
        player.DrawPlayer(resources, gameState, camera);

    }
    for (NPC& zombie : zombies){
        zombie.Update(player);
        zombie.Render();

        if (zombie.isDying && !firstBlood && gameState == GRAVEYARD){ //first zombie that is dying in the graveyard
            firstBlood = true;
            dz_pos = zombie.position;
            
        }
    }


    if (!start) show_dbox = false; //set to false to hide dbox when not over spot unless start where we first show tutorial text

    for (NPC& ghost: ghosts){
        ghost.Update(player);
        ghost.Render();
        ghost.ClickNPC(mousePosition, camera, player);
        if (ghost.health > 0) ghost.isActive = true;
        if (ghost.interacting){
            show_dbox = true;
            dboxPosition = ghost.position;
            phrase = ghost.speech;
        }
    }

    DrawBullets(); //draw bullets in cemetery after everything else. 

    //foreforeground. infront of player
    DrawTexturePro(resources.GraveyardForeground, {0, 0, static_cast<float>(resources.GraveyardGate.width), static_cast<float>(resources.GraveyardGate.height)},
                {1024, 70, static_cast<float>(resources.GraveyardGate.width), static_cast<float>(resources.GraveyardGate.height)}, {0, 0}, 0.0f, WHITE);

    if (firstBlood && !player.hasBadge){
        drawDeadZombie(resources,player, dz_pos, mouseWorldPos);
    }

    EndMode2D();

    DrawMoney(); //draw money after EndMode2d()

    if (badgeTimer > 0){ //show badge explanation
        show_dbox = true;
        DrawDialogBox(camera, 0, 0, 20);
        badgeTimer -= GetFrameTime();
    }

    if (showInventory){
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);  // Render the inventory 
    }

    if (player.hasGun){//DRAW RETICLE IF AIMING AND HAS GUN
        DrawTexture(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ? resources.reticle : resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // if aiming draw reticle
    }else{
        DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE);
    }

    
    if (player.position.x > 3067 && player.position.x < 3087){

        phrase = "PRESS UP TO EXIT";
        show_dbox = true;
        dboxPosition = player.position;
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
            transitionState = FADE_OUT;
            //fadeout to cemetery. Handled in handleTransition function
        }
        
    }
    if (show_dbox){
        DrawDialogBox(camera, 0, 0, 20);

    }


    if ((player.hasGun || player.hasShotgun) && !player.enter_car) DrawHUD(player); //always show ammo when outside of car in the cemetery


    //draw healthbar 

    Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
    DrawHealthBar(resources, barPos, player.maxHealth, player.currentHealth, 128, 16);

    
}




void RenderApartment(GameResources& resources, Player player, Vector2 mousePosition, GameCalendar& calendar, Camera2D camera, Shader& drunkShader, Shader& glowShader, Shader& glitchShader){
    player.position.x -= 20; //ensure over_apartment = false
    int screen_center = (screenWidth - resources.apartment.width)/2;
    
     //Vector2 drawerPos = {screenWidth/2 + 160, 730};

   if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }

    ClearBackground(ApartmentBgColor);

    DrawTexture(resources.apartment, screen_center, 0, WHITE);
    EndShaderMode(); ////////////////////////////SHADER OFF

    DrawMoney(); //draw money after EndMode2d()
    if (showAPUI){
        DrawApartmentUI(resources, calendar, mousePosition, camera);
    }
    
    
    //DrawText("Apartment", screenWidth/2 - 128, 60, 50, WHITE);
    if (!has_car_key){
        DrawTexture(resources.carKey, carKeysPos.x, carKeysPos.y, WHITE);
    }
    

    if (showInventory){
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);
        
    }

    if (openDrawer){
        DrawTexture(resources.OpenDrawer, drawerPos.x, drawerPos.y, WHITE);
    }

    //UP DOWN OR ESCAPE TO EXIT APARTMENT
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_ESCAPE)){
        transitionState = FADE_OUT;
        showInventory = false;
        PlaySound(SoundManager::getInstance().GetSound("mainDoor"));
        
    }

    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); //draw cursor last
    
}

void RenderLot(GameResources& resources, Player& player, Camera2D& camera, Vector2& mousePosition, Shader& drunkShader, Shader& glowShader, Shader& glitchShader){
    //Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);
    int digPos = 2600;
    if (player.position.x < 2782 && player.position.x > 2742){
        over_exit = true;
    }else{
        over_exit = false;
    }

    if (player.position.x > digPos - 10 && player.position.x < digPos + 10){
        digSpot = true;
    }else{
        digSpot = false;
    }


    over_lot = false;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        if (over_exit){
            transitionState = FADE_OUT;

        }
    }    

    //camera.target = player.position;
    //float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxBackground = camera.target.x * 0.7f;  // Background moves even slower
    
    SoundManager::getInstance().UpdateMusic("StreetSounds"); //only update street sounds when oustide
    if (!streetSounds){ 
        streetSounds = true; //Why do we need this bool? incase we need to turn it off?
        SoundManager::getInstance().PlayMusic("StreetSounds");
        
    }

    if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }

    BeginMode2D(camera);
     // Draw the background (sky)
    DrawTexturePro(resources.background, {0, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)},
                    {parallaxBackground, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the midground (silhouettes)
    // DrawTexturePro(resources.midground, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
    //                 {parallaxMidground, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),  offset by 1024 to center relative to midground. 
    DrawTexturePro(resources.vacantLot, {0, 0, static_cast<float>(resources.vacantLot.width), static_cast<float>(resources.vacantLot.height)},
                    {705, 0, static_cast<float>(resources.vacantLot.width), static_cast<float>(resources.vacantLot.height)}, {0, 0}, 0.0f, WHITE);

    show_dbox = false; //turn off dbox if no one is interacting
    for (NPC& hobo : hobos){
        hobo.Update(player);
        hobo.Render();
        hobo.ClickNPC(mousePosition, camera, player);

        if (hobo.interacting){ 
            if (firstHobo){ // only raise zombie and draw shovel if it's the fist visit to the hobo
                firstHobo = false;
                raiseZombies = true; // zombies don't spawn until you talk to hobo. 
                drawShovel = true; //shovel isn't in cemetery until you talk to hobo.
            }

            if (hobo.interactions == 1 && hobo.clickCount == 6 && !hasCemeteryKey){
                //give cemetery key
                AddItemToInventory("cemeteryKey", inventory, INVENTORY_SIZE);
                hasCemeteryKey = true;
                showInventory = true;
                raiseZombies = true;
                PlaySound(SoundManager::getInstance().GetSound("Keys"));
            }

            dboxPosition = hobo.position;
            dealer = false; // dealer gets left on somewhere
            show_dbox = true;   //dialogBox
        
            phrase = hobo.speech;
                      
        }else{
            // show_dbox = false;
        }
    }
    
    player.DrawPlayer(resources, gameState, camera);

    
    EndMode2D();  // End 2D mode 
 
    DrawMoney(); //draw money after EndMode2d()

    if (show_dbox){      
        DrawDialogBox(camera, 0, 0, 20); // draw box size of 0x0. hobo has no border box
    }  

    if (showInventory){
         
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);  // Render the inventory 
    }

    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // render mouse cursor outside Mode2D. Do this last
}

// Example function to render the outside scene with dynamic camera
void RenderOutside(GameResources& resources, Camera2D& camera,Player& player, PlayerCar& player_car,MagicDoor& magicDoor, std::vector<NPC>& npcs,Vector2 mousePosition, Shader& drunkShader, Shader& glowShader, Shader& glitchShader) {
    // Update the camera target to follow the player
    int ap_min = 2246;//over apartment
    int ap_max = 2266;

    int pc_min = 1728; // over player_car
    int pc_max = 1748;
    int road_min = 1340; //exiting outside via road

    int lot_min = vacantLotX - 20;
    int lot_max = vacantLotX + 20;

    int dist = abs(player.position.x - ap_max);

    if (dist > 1000){ //get far enough away from the apartment and you can sleep again. 
        hasSlept = false;
    }


    SoundManager::getInstance().UpdateMusic("StreetSounds"); //only update street sounds when oustide or in vacant lot

    if (!streetSounds){ 
        streetSounds = true; //Why do we need this bool? incase we need to turn it off?
        SoundManager::getInstance().PlayMusic("StreetSounds");
        
    }


    if (player_car.position.x < road_min && move_car){
        transitionState = FADE_OUT;
        
        //player_car.position = Vector2 {900, 700 - 32};

    }



    if (!start) show_dbox = false; // reset to false so it can fall through unless start where we first show tutorial text
    over_apartment = false;
    over_lot = false;
    over_car = false;
    if (player.position.x > pc_min && player.position.x < pc_max){
        over_car = true;
        phrase = "PRESS UP TO ENTER";
        show_dbox = true;
        dboxPosition = player.position;
        
        
    }

    
    if (player.position.x > lot_min && player.position.x < lot_max){
        over_lot = true;
        phrase = "PRESS UP TO ENTER";
        dboxPosition = player.position;
        
        show_dbox = true;

    }
    
    if (player.position.x > ap_min  && player.position.x < ap_max){
        over_apartment = true;
        phrase = "PRESS UP TO ENTER";
        dboxPosition = player.position;
        dboxPosition.y = player.position.y + 10;
        show_dbox = true;
        
    }

    camera.target = player.position;
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxBackground = camera.target.x * 0.7f;  // Background moves even slower
    
    BeginMode2D(camera);  // Begin 2D mode with the camera
    ClearBackground(customBackgroundColor);
    //BeginShaderMode(shader); /////////////////////////////////////// UNCOMMENT FOR CRT SHADER



    if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }
    
     // Draw the background (sky)
    DrawTexturePro(resources.background, {0, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)},
                    {parallaxBackground, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the midground (silhouettes)
    DrawTexturePro(resources.midground, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
                    {parallaxMidground, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),  offset by 1024 to center relative to midground. 
    DrawTexturePro(resources.foreground, {0, 0, static_cast<float>(resources.foreground.width), static_cast<float>(resources.foreground.height)},
                    {512, 0, static_cast<float>(resources.foreground.width), static_cast<float>(resources.foreground.height)}, {0, 0}, 0.0f, WHITE);
    
    EndShaderMode(); ////////////////////////////SHADER OFF
    
    if (move_car){
        player_car.position.x -= player_car.carSpeed * GetFrameTime();
    }else{
        player_car.position = Vector2{1710, 668};
    }
    //mibs show up after you get cemetery key. They don't do anything yet. 
    if (hasCemeteryKey){
        for (NPC& mib : mibs){
            mib.Update(player);
            mib.Render();
            
        }

    }


    teller = false;
    for (NPC& npc : npcs){
        npc.Update(player);
        npc.Render();
        npc.ClickNPC(mousePosition, camera, player);
    

        if (npc.interacting){ //Take the first one you find. 
            dboxPosition = npc.position;    
            show_dbox = true;   //dialogBox
            if (npc.dealer){
                phrase = "I gOt wHat YoU NEEd\n\nDrugs: $100";
                dealer = true;
                showInventory = true;

            }else if (npc.teller){
                if (!buyFortune){
                    phrase = "Fortune: $100";
                    teller = true;
                }else if (buyFortune){
                    if (fortuneTimer <= 0){
                        phrase = npc.speech;
                    }
                    
                    teller = true;
                }
                

            } else{
                phrase = npc.speech; //randomized speech
                dealer = false;
            }
        }else{
            dealer = false;
        
            // show_dbox = false;
        }
    
    }
    
    //DrawStreetLight
    BeginBlendMode(BLEND_ADDITIVE);
    DrawTexture(resources.lightCone, 1884, 610, WHITE);
    DrawTexture(resources.lightCone, 3188, 610, WHITE);
    EndBlendMode();
    
    DrawBullets();
    UpdateBullets();
    //DrawPlayerCar
    int CarFrameWidth = 128;
    Rectangle sourceRecCar = {player_car.currentFrame * CarFrameWidth, 0, CarFrameWidth, CarFrameWidth};
    DrawTextureRec(resources.carSheet, sourceRecCar, player_car.position, WHITE); //draw player_car

    //Draw MagicDoor
    if (applyShader){
        DrawMagicDoor(resources, player, magicDoor);

        
    }


    if (player.enter_car){
        //render headlight/breaklight
        
        Vector2 breakLight_pos = {player_car.position.x + 88, player_car.position.y + 53};
        Vector2 light_pos = {player_car.position.x - 225, player_car.position.y + 32};
        BeginBlendMode(BLEND_ADDITIVE);
        DrawTextureV(resources.breakLight, breakLight_pos, WHITE);
        DrawTextureV(resources.lightBeam, light_pos, WHITE);
        EndBlendMode();
        show_carUI = true;    

    }
   

    if (player.enter_car == false){// if enter car is false, dont render player or update position. camera should stay focused on player pos. 
        SoundManager::getInstance().StopMusic("CarRun");
        //DRAW PLAYER
        if (!player.enter_car) { // if enter_car is false, don't render player or update position; camera should stay focused on player pos.
            player.DrawPlayer(resources, gameState, camera);


        }
    }
    
    MoveTraffic(resources);//Draw Traffic


    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        if (player.enter_car && !move_car){ // dont exit car if it's still moving.
            PlaySound(SoundManager::getInstance().GetSound("CarDoorClose")); 
            player.enter_car = false;
            player_car.currentFrame = 0;
        }
    }

    // if (IsKeyPressed(KEY_SPACE)){
    //     if (player.enter_car){
    //         move_car = true;
    //     }
    // }
    if (show_carUI && !move_car && player.enter_car){
        DrawCarUI(player_car, mousePosition, camera, gameState);
    }


    EndMode2D();  // End 2D mode 

    if (player.currentHealth < 100) showHealthbar = true; // dont show healthbar until youve taken damage, when on street
    Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
    if (showHealthbar) DrawHealthBar(resources, barPos, player.maxHealth, player.currentHealth, 128, 16);

    


    if (show_dbox && !player.enter_car){

        if (over_lot || over_apartment || over_car || start){
            DrawDialogBox(camera, 0, 0, 20);
            
        }else{
            DrawDialogBox(camera, 0, 0, 20);
        }
        
    }

    //DrawText("Paper Street", screenWidth/2 - 128, 60, 50, WHITE);
    DrawMoney(); //draw money after EndMode2d()
    if (showInventory){
         
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);  // Render the inventory 
    }
    //Draw cursor last so it's on top
    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // render mouse cursor outside Mode2D. Do this last
}




// Factory function to create an NPC with default properties

void spawnNPCs(GameResources& resources){
    // Create NPCs outside and set there starting desitnations. 
    float speed = 50.0f;

    //spawn generic NPCs
    int generic = 3;
    for (int i = 0; i < generic; ++i) {
        Vector2 startPosition = { static_cast<float>(512 + i * 200), 700 };  // positions spread out along the x axis    
        NPC npc = CreateNPC(resources.npcTexture, startPosition, speed, IDLE,  true, false);
        npc.SetDestination(512, 4000);
        npcs.push_back(npc);  // Add the NPC to the vector
    }

    //spawn businessMan
    int b_men = 2;
    for (int i = 0; i < b_men; i++){
        Vector2 b_pos = { static_cast<float>(2300 + i * 100), 700};
        NPC business_npc = CreateNPC(resources.businessSheet, b_pos, speed,IDLE, true, false);
        business_npc.SetDestination(1000, 4000);
        npcs.push_back(business_npc);

    }


    //spawn woman
    int women = 1;
    for (int i = 0; i < women; i++){
        Vector2 w_pos = {static_cast<float>(2050 + i * 100), 700};
        NPC woman_npc = CreateNPC(resources.womanSheet, w_pos, speed,IDLE, true, false);
        woman_npc.SetDestination(1000, 4000);
        npcs.push_back(woman_npc);

    }

    //spawn woman2
    int women2 = 2;
    for (int i = 0; i < women2; i++){
        Vector2 w_pos = {static_cast<float>(2220 + i * 100), 700};
        NPC woman2_npc = CreateNPC(resources.woman2Sheet, w_pos, speed, IDLE, true, false);
        woman2_npc.SetDestination(1000, 4000);
        npcs.push_back(woman2_npc);
    }

    //create mibs
    int m = 1;
    for (int i = 0; i < m; i++){
        Vector2 mib_pos = {static_cast<float>(2220 + i * 100), 700};
        NPC mib = CreateNPC(resources.mibSheet, mib_pos, speed, IDLE, true, false);
        mib.SetDestination(2000, 2400);
        mib.MiB = true;
        mibs.push_back(mib);
    }

    //create Bats
    int b = 3;
    for (int i = 0; i < b; i++){
        Vector2 b_pos = {static_cast<float>(2220 + i * 100), 700};
        NPC bat = CreateNPC(resources.batSheet, b_pos, speed, IDLE, false, false);
        bat.SetDestination(2000, 2200);
        bat.bat = true;
        bats.push_back(bat);

    }



    //create ghost // call update on ghost where ever needed like graveyard or cemetery
    Vector2 g_pos = {2000, 700};
    NPC ghost_npc = CreateNPC(resources.ghostSheet, g_pos, speed, IDLE, false, false);
    ghost_npc.SetDestination(2000, 2200);
    ghost_npc.ghost = true;
    ghost_npc.maxHealth = 500;
    ghost_npc.health = 500;
    ghosts.push_back(ghost_npc);

    //spawn astral ghosts
    int ap = 2;
    for (int i = 0; i < ap; i++){
        Vector2 ag_pos = {static_cast<float>(2220 + i * 100), 700};;
        NPC astralGhost = CreateNPC(resources.ghostSheet, ag_pos, speed, IDLE, false, false);
        ghost_npc.SetDestination(2000, 2200);
        astralGhost.ghost = true;
        astralGhost.maxHealth = 500;
        astralGhost.health = 500;
        astralGhost.agro = true;
        astralGhosts.push_back(astralGhost);

    }

    //fortune teller 

    Vector2 tellerPos = {2700, 700};
    NPC FortuneTeller = CreateNPC(resources.FortuneTellerSheet, tellerPos, speed, IDLE, true, false);
    FortuneTeller.SetDestination(1000, 4000);
    FortuneTeller.teller = true;
    npcs.push_back(FortuneTeller);
    FortuneTeller.speech = "Fortune: $100";
    

    //spawn hobo update and draw only in vacant lot
    
    Vector2 h_pos = {2600, 700};
    NPC hobo_npc = CreateNPC(resources.hoboSheet, h_pos, speed, IDLE, true, false);
    hobo_npc.SetDestination(2500, 2600);
    hobo_npc.hobo = true;
    hobos.push_back(hobo_npc);//hobo is in it's own vector of hobos. incase we need another hobo
    

    //spawn policemen
   int police = 1;
    for (int i = 0; i < police; i++){
        Vector2 w_pos = {static_cast<float>(2100 + i * 100), 700};
        NPC police_npc = CreateNPC(resources.policeSheet, w_pos, speed,IDLE, true, false);
        police_npc.SetDestination(1000, 4000);
        police_npc.police = true;
        npcs.push_back(police_npc);

    }

    //spawn dealer
    int dealer = 1;

    for (int i = 0; i < dealer; i++){
        Vector2 d_pos = {static_cast<float>(2200 + i * 100), 700};
        NPC dealer_npc = CreateNPC(resources.dealerSheet, d_pos, speed, IDLE, true, false);
        dealer_npc.SetDestination(1000, 4000);
        dealer_npc.dealer = true;
        npcs.push_back(dealer_npc);
    }

}

void DisplayDate(GameCalendar& calendar){
    DrawText(calendar.GetDate().c_str(), screenWidth/2 - 450, 25, 20, WHITE);
}

// void glowEffect(Shader& glowShader, GameState gameState){
//         float time = GetTime();  // Get the total elapsed time
//         float minThreshold = 0.2f;
//         float maxThreshold = 0.6f;
//         float oscillationSpeed = 0.9f;  // 1 second duration

//         if (gameState == ASTRAL){ //Customized look for astral plane. 
//             minThreshold = 0.2f;
//             maxThreshold = 0.3f;
//             oscillationSpeed = 0.9f;  // 1 second duration

//         }

//     // Calculate the oscillating glow threshold using a sine wave
//         float glowThreshold = minThreshold + (maxThreshold - minThreshold) * (0.5f * (1.0f + sin(oscillationSpeed * time)));    

//         // Set the glowThreshold uniform in the shader
//         int glowThresholdLocation = GetShaderLocation(glowShader, "glowThreshold");
//         SetShaderValue(glowShader, glowThresholdLocation, &glowThreshold, SHADER_UNIFORM_FLOAT);

// }

void handleCamera(Camera2D& camera, float& targetZoom){
        // Handle zoom input
        if (GetMouseWheelMove() > 0) {
            targetZoom += 0.2f;
        } else if (GetMouseWheelMove() < 0) {
            targetZoom -= 0.2f;
        }

        // Smoothly interpolate the current zoom towards the target zoom
        camera.zoom = Lerp(camera.zoom, targetZoom, 0.1f);
        float maxZoom = 2.5;
        float minZoom = 1.0;
        // Apply boundary checks for the zoom level
        if (camera.zoom > maxZoom) camera.zoom = maxZoom;
        if (camera.zoom < minZoom) camera.zoom = minZoom;
        if (targetZoom > maxZoom) targetZoom = maxZoom;
        if (targetZoom < minZoom) targetZoom = minZoom;

}

void debugKeys(Player& player){
        if (IsKeyPressed(KEY_SPACE)){
            std::cout << "Player Position: ";
            PrintVector2(player.position);
            // if (!drunk){
            //     //applyShader = true;
            //     drunk = true;
            // }else{
            //     //applyShader = false;
            //     drunk = false;
            }

        if (IsKeyPressed(KEY_K)){
            if (!has_car_key || !hasCemeteryKey){
                AddItemToInventory("carKeys", inventory, INVENTORY_SIZE);
                AddItemToInventory("cemeteryKey", inventory, INVENTORY_SIZE);
                has_car_key = true;
                hasCemeteryKey = true;
                PlaySound(SoundManager::getInstance().GetSound("Keys"));

            }

        }

        if (IsKeyPressed(KEY_H)){
            if (!player.hasShovel){
                player.hasShovel = true;
                AddItemToInventory("shovel", inventory, INVENTORY_SIZE);
                PlaySound(SoundManager::getInstance().GetSound("shovelPickup"));
            }
        }

        if (IsKeyPressed(KEY_G)){
            if (!player.hasGun){
                AddItemToInventory("Gun", inventory, INVENTORY_SIZE);
                player.hasGun = true;
                PlaySound(SoundManager::getInstance().GetSound("reload"));

            }
            if (!player.hasShotgun){
                AddItemToInventory("shotgun", inventory, INVENTORY_SIZE);
                player.hasShotgun = true;
            }

        }

}

void InitSounds(SoundManager& soundManager){
    //We use our own custom sound manager. We have an array of sounds, and an array of musticTracks.
    SetMasterVolume(1.0f);  // Sets the master volume to maximum
    
    SoundManager::getInstance().LoadMusic("CarRun", "assets/sounds/CarRun.ogg"); // load CarRun.ogg into music tracks with the name CarRun
    //music tracks automatically loop.The car running sound needs to loop, so we call it music.
    SoundManager::getInstance().LoadMusic("StreetSounds", "assets/sounds/StreetSounds.ogg"); 
    SoundManager::getInstance().LoadMusic("Jangwa", "assets/sounds/Jangwa.ogg");
    SoundManager::getInstance().LoadMusic("Neon", "assets/sounds/Neon.ogg");


    soundManager.LoadSound("gunShot", "assets/sounds/gunShot.ogg");   //misc sounds
    soundManager.LoadSound("BoneCrack", "assets/sounds/BoneCrack.ogg");
    soundManager.LoadSound("reload", "assets/sounds/revolvercock.ogg");
    soundManager.LoadSound("dryFire", "assets/sounds/DryFire.ogg");
    soundManager.LoadSound("CarStart", "assets/sounds/CarStart.ogg");
    soundManager.LoadSound("CarDoorOpen", "assets/sounds/CarDoorOpen.ogg");
    soundManager.LoadSound("CarDoorClose", "assets/sounds/CarDoorClose.ogg");
    soundManager.LoadSound("mainDoor", "assets/sounds/mainDoor.ogg");
    soundManager.LoadSound("OpenDrawer", "assets/sounds/OpenDrawer.ogg");
    soundManager.LoadSound("CloseDrawer", "assets/sounds/CloseDrawer.ogg");
    soundManager.LoadSound("Keys", "assets/sounds/Keys.ogg");
    soundManager.LoadSound("Owl", "assets/sounds/Owl.ogg");
    soundManager.LoadSound("ShovelDig", "assets/sounds/ShovelDig.ogg");
    soundManager.LoadSound("shovelPickup", "assets/sounds/shovelPickup.ogg");
    soundManager.LoadSound("Pills", "assets/sounds/Pills.ogg");

    soundManager.LoadSound("ShotGun", "assets/sounds/ShotGun.ogg");
    soundManager.LoadSound("ShotgunReload", "assets/sounds/ShotgunReload.ogg");

    soundManager.LoadSound("Step1", "assets/sounds/Step1.ogg");
    soundManager.LoadSound("Step2", "assets/sounds/Step2.ogg");
    
    soundManager.LoadSound("moan1", "assets/sounds/ZombieMoan1.ogg"); //zombie VA
    soundManager.LoadSound("moan2", "assets/sounds/ZombieMoan2.ogg");
    soundManager.LoadSound("moan3", "assets/sounds/ZombieMoan3.ogg");
    soundManager.LoadSound("zhit1", "assets/sounds/ZombieHit1.ogg");
    soundManager.LoadSound("zhit2", "assets/sounds/ZombieHit2.ogg");
    soundManager.LoadSound("zhit3", "assets/sounds/ZombieHit3.ogg");
    soundManager.LoadSound("zhit4", "assets/sounds/ZombieHit4.ogg");

    soundManager.LoadSound("zombieDeath", "assets/sounds/zombieDeath.ogg");


    soundManager.LoadSound("phit1", "assets/sounds/PlayerHit1.ogg"); //player VA hits
    soundManager.LoadSound("phit2", "assets/sounds/PlayerHit2.ogg");

    //Volume edits
    SoundManager::getInstance().SetSoundVolume("CarStart", 0.5);
    SoundManager::getInstance().SetSoundVolume("BoneCrack", 0.3f);
    SoundManager::getInstance().SetMusicVolume("CarRun", 0.25f);
    SoundManager::getInstance().SetMusicVolume("Schumann", 0.25f);
    SoundManager::getInstance().SetSoundVolume("Owl", 0.5);
}


int main() {
    InitWindow(screenWidth, screenHeight, "Adventure Game");
    
    //PUT NOTHING ABOVE THIS ^^ CAN CAUSE SEG FAULT
    InitAudioDevice();
    SoundManager& soundManager = SoundManager::getInstance();
    InitSounds(soundManager);
    HideCursor();
    SetExitKey(0);  // Disable escape key from closing the window
    srand(static_cast<unsigned>(time(0))); //randomize seed based on time
    
    // Initialize game resources
    GameResources resources;
    GameCalendar calendar;
    LoadGameResources(resources);
    spawnNPCs(resources); //spawn NPCs before rendering them outside
    InitPlatforms();

    // Initialize shaders
    ShaderResources shaders; //struct holding all the shaders. 
    InitShaders(shaders, screenWidth, screenHeight); //refactored shader setup to shaderControl.cpp
    
    // Initialize player
    Player player;
    PlayerCar player_car;
    Earth earth;
    MagicDoor magicDoor;
    InitializePlayerCar(player_car);
    InitializeMagicDoor(magicDoor);
    InitEarth(earth);
  
    // Initialize the camer
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f + 188.0f };  // Screen center + y offset 188 lower ground for bigger sky
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    float targetZoom = camera.zoom;  // Initialize targetZoom to the initial zoom value
   
    inventoryPositionX = player.position.x; //init inventory position
    inventoryPositionY = player.position.y;  
    SetTargetFPS(60);
    dboxPosition = player.position;
    AddItemToInventory("Drugs", inventory, INVENTORY_SIZE);
    //PlayMusicStream(SoundManager::getInstance().GetMusic("Jangwa"));
    PlayMusicStream(SoundManager::getInstance().GetMusic("Neon"));

    Shader glowShader = shaders.glowShader;
    Shader glitchShader = shaders.glitchShader;
    Shader glowShader2 = shaders.glowShader2;
    //int timeLoc = shaders.timeLoc;
    //float totalTime = 0.0f; // Variable to keep track of time //glitch shader
    // Main game loop
    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();
        if (!player.enter_car) player.UpdateMovement(resources, gameState, mousePosition, camera, platforms);  // Update player position and animation
        UpdateInventoryPosition(camera, gameState);
        SoundManager::getInstance().UpdateMusic("Neon");
        SoundManager::getInstance().UpdateMusic("CarRun");
        
        UpdateBullets();
        CheckBulletNPCCollisions(zombies); //check each enemy group
        CheckBulletNPCCollisions(ghosts);
        CheckBulletNPCCollisions(astralGhosts);
        CheckBulletNPCCollisions(bats);
        MonitorMouseClicks(player, calendar);
        UpdateZombieSpawning(resources, player);
        //glowEffect(glowShader, gameState); //update glow shader
        
        float deltaTime = GetFrameTime();
    
        UpdateShaders(shaders, deltaTime, gameState);
        
        if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)){ //tutorial text
            start = false; //turn off dbox if any movement
        }

        if (IsKeyPressed(KEY_M)){ //MUTE MUSIC
            if (SoundManager::getInstance().IsMusicPlaying("Neon")){
                SoundManager::getInstance().PauseMusic("Neon");

            }else{
                SoundManager::getInstance().ResumeMusic("Neon");
            }
        }

        ////DEBUG/////////////////DEBUG///////////
        if (debug){
            debugKeys(player);

        }
        
        //////////////////////////////////////////////

        //I for inventory
        if (IsKeyPressed(KEY_I)){
            if (!showInventory){
                showInventory = true;
            }else{
                showInventory = false;
            }
            
        }
        //enter places by pressing up
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){

            if (over_apartment && gameState == OUTSIDE){
                transitionState = FADE_OUT; //Transition to apartment
                PlaySound(SoundManager::getInstance().GetSound("mainDoor"));
                over_apartment = false;
                showInventory = false;
                //player.position.x = 512; //move player, to move inventory to the middle of the screen. 
                
            }
            //enter car for both outside and cemetery
            if (over_car && !player.enter_car && has_car_key){
                //player inside idling car
                SoundManager::getInstance().PlayMusic("CarRun");
                PlaySound(SoundManager::getInstance().GetSound("CarStart"));
                PlaySound(SoundManager::getInstance().GetSound("CarDoorOpen"));
                player.enter_car = true;
                over_car = false;
                player_car.currentFrame = 1;


            }
            if (over_lot && gameState == OUTSIDE){
                transitionState = FADE_OUT;
            }
            if (over_gate && gameState == CEMETERY){
                transitionState = FADE_OUT;
                
            }

        }

        handleCamera(camera, targetZoom);

        BeginDrawing(); 

        if (gameState == OUTSIDE){     
            RenderOutside(resources, camera, player, player_car, magicDoor, npcs,mousePosition, glowShader2, glowShader, glitchShader); //glowshader2 = drunkshader
            DisplayDate(calendar);//why not display date once globally? there are reasons 

        }else if (gameState == APARTMENT){
            RenderApartment(resources, player, mousePosition, calendar, camera, glowShader2, glowShader, glitchShader);
            DisplayDate(calendar);

        }else if (gameState == ROAD){
            RenderRoad(resources, player_car, player, camera, mousePosition, glowShader2, glowShader, glitchShader);
            DisplayDate(calendar);

        }else if (gameState == CEMETERY){
            RenderCemetery(resources, player, player_car, camera,mousePosition, glowShader2, glowShader, glitchShader);
            DisplayDate(calendar);

        }else if (gameState == WORK){
            ClearBackground(BLACK);

        }else if (gameState == LOT){ // vacant lot
            RenderLot(resources, player, camera, mousePosition, glowShader2, glowShader, glitchShader);
            DisplayDate(calendar);

        }else if (gameState == GRAVEYARD){
            RenderGraveyard(resources, player, camera, mousePosition, glowShader2, glowShader, glitchShader);
            DisplayDate(calendar);
            
        }else if (gameState == ASTRAL){
            DisplayDate(calendar);
            RenderAstral(resources, player, camera, mousePosition, earth, magicDoor, glowShader2, glowShader, glitchShader);
        }

        
        HandleTransition(player, player_car, calendar, npcs); //Check everyframe for gamestate transition
        EndDrawing();

        EndShaderMode();
        
        
    }

    // Unload resources and close the window
    UnloadGameResources(resources);
    soundManager.UnloadAllSounds();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
