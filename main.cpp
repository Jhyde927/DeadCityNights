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
bool showInternet = false;
bool move_ufo = false;
bool canMoveUfo = true;
bool firstHobo = true;
bool firstBlood = false;
bool drawShovel = false;
bool drawShotgun = true;
bool buttonWork = false;
bool hasPills = false;
bool digSpot = false;
bool NecroTech = false;
bool start = true;
bool buttonTavern = false;
bool gotoWork = false;
bool gotoPark = false;
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
bool showLiquor = false;
bool can_sell_drugs = true;
bool applyShader = false;
bool drunk = false;
bool glitch = false;
bool vignette = true; //start vignette
bool openMagicDoor = false;
bool move_car = false;
bool showHealthbar = false;
bool reverse_road = false;
bool has_car_key = false;
bool overLiquor = false;
bool npcWalk = false;
bool openDrawer = false;
bool raiseZombies = false;
bool zombieWave2 = false;
bool zombieWave3 = false;
bool abductionBeam = false;
bool show_dbox = true;
float ufoTimer = 0.0;
float dboxTime = 10.0;
float internetTimer = 0.0;
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

//const int INVENTORY_SIZE = 10;
//std::vector<std::string> inventory(INVENTORY_SIZE, "");  // Vector of size 10, filled with empty strings



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
std::vector<NPC>astralBats;
std::vector<NPC>ParkNpcs;

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

struct UFO {
    Vector2 position = {3500, 400};
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int totalFrames;
    float frameTime;
    float frameTimer;

    Vector2 basePosition;  // Original position where the UFO is placed
    float bobAmplitudeX;   // Amplitude of side-to-side movement
    float bobAmplitudeY;   // Amplitude of up-and-down movement
    float bobSpeedX;       // Speed of side-to-side movement
    float bobSpeedY;       // Speed of up-and-down movement
    float bobOffsetX;      // Phase offset for side-to-side movement
    float bobOffsetY;      // Phase offset for up-and-down movement
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
    resources.whiskey = LoadTexture("assets/Whiskey.png");
    resources.midgroundLot = LoadTexture("assets/MidGroundLot.png");
    resources.UFOsheet = LoadTexture("assets/UFOsheet.png");
    resources.lightBar = LoadTexture("assets/lightBar.png");
    resources.ParkForeground = LoadTexture("assets/Park(foreground).png");
    resources.ParkMidground = LoadTexture("assets/Park(midground).png");
    resources.ParkBuildings = LoadTexture("assets/Park(buildings).png");
    resources.MidBuildings = LoadTexture("assets/MidBuildings.png");
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
    UnloadTexture(resources.whiskey);
    UnloadTexture(resources.midgroundLot);
    UnloadTexture(resources.UFOsheet);
    UnloadTexture(resources.lightBar);
    UnloadTexture(resources.ParkForeground);
    UnloadTexture(resources.ParkMidground);
    UnloadTexture(resources.ParkBuildings);

   
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

void InitUFO(UFO& ufo){
    //animation perameters
    ufo.frameWidth = 144;
    ufo.frameHeight = 144;
    ufo.currentFrame = 0;
    ufo.totalFrames = 4;
    ufo.frameTimer = 0.0;
    ufo.frameTime = 0.1;

    ufo.basePosition = { -94.0, 0.0f }; //base position stays the same. When moving UFO move base position.
    ufo.position = ufo.basePosition;

    // Set motion parameters
    ufo.bobAmplitudeX = 5.0f;   // Moves 10 pixels left and right
    ufo.bobAmplitudeY = 2.0f;    // Moves 5 pixels up and down
    ufo.bobSpeedX = 1.0f;        // Side-to-side speed
    ufo.bobSpeedY = 1.5f;        // Up-and-down speed
    ufo.bobOffsetX = 0.0f;       // No initial phase offset
    ufo.bobOffsetY = 0.0f;       // No initial phase offset
}


void InitPlatforms() {
    //initialize platforms before drawing them in astral

    platforms.emplace_back(2300.0f, 675.0f, 200.0f, 20.0f, WHITE);

    // Add more platforms as needed
    platforms.emplace_back(2500.0f, 600.0f, 150.0f, 20.0f, WHITE);
    platforms.emplace_back(2800.0f, 550.0f, 250.0f, 20.0f, WHITE);
    platforms.emplace_back(2600.0f, 450.0f, 150.0f, 20.0f, WHITE);
    platforms.emplace_back(2400.0f, 400.0f, 150.0f, 20.0f, WHITE);
    platforms.emplace_back(2100.0f, 350.0f, 200.0f, 20.0f, WHITE);
    platforms.emplace_back(1900.0f, 300.0f, 150.0f, 20.0f, WHITE);
    platforms.emplace_back(1600.0f, 250.0f, 200.0f, 20.0f, WHITE);
    platforms.emplace_back(1400.0f, 150.0f, 250.0f, 20.0f, WHITE);
    //platforms.emplace_back(1600.0f, 100.0f, 200.0f, 20.0f, WHITE);
    platforms.emplace_back(1800.0f, 75.0f, 300.0f, 20.0f, WHITE);
    platforms.emplace_back(2100.0f, 0.0f, 200.0f, 20.0f, WHITE);
    platforms.emplace_back(2300.0f, -100.0f, 200.0f, 20.0f, WHITE);
    platforms.emplace_back(2500.0f, -200.0f, 200.0f, 20.0f, WHITE);
    platforms.emplace_back(2700.0f, -300.0f, 200.0f, 20.0f, WHITE);
    platforms.emplace_back(2800.0f, -400.0f, 200.0f, 20.0f, WHITE);
    platforms.emplace_back(2700.0f, -500.0f, 150.0f, 20.0f, WHITE);
    platforms.emplace_back(2500.0f, -550.0f, 200.0f, 20.0f, WHITE);
    platforms.emplace_back(2400.0f, -650.0f, 200.0f, 20.0f, WHITE);
    platforms.emplace_back(1400.0f, -700.0f, 2000.0f, 20.0f, WHITE);
}


// Function to add an item to the first available slot in the inventory
void AddItemToInventory(const std::string& item, std::string inventory[], int inventorySize) {
    //what happens if inventory is full and we add to it? nothing?

    for (int i = 0; i < inventorySize; i++) {
        if (inventory[i].empty()) {
            inventory[i] = item;  // Add the item to the first empty slot
            break;
        }
    }
}

std::string GetTellerPhrase() {
    std::vector<std::string> tellerPhrases = {
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

            if (buttonInternet && player.hasBadge && !showInternet){
                showInternet = true;
                NecroTech = true;
                internetTimer = 5.0f;
            }else{
                showInternet = false;
            }

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
                    if (firstHobo == false){ 
                        raiseZombies = true; //only raise zombies if the player has the gun and first hobo = false
                    }

                }
                

            }else if (CheckCollisionPointRec(mousePosition, drawerBounds) && openDrawer){
                openDrawer = false;
                PlaySound(SoundManager::getInstance().GetSound("CloseDrawer"));
            }

            if (CheckCollisionPointRec(mousePosition, ComputerBounds) && !showAPUI){
                showAPUI = true;
            }else{
                if (!showInternet){
                    showAPUI = false;
                }
                
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
                }else if (player.enter_car && buttonTavern){
                    gotoPark = true;
                    move_car = true;
                    
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
        }else if (gameState == PARK){
            if (player.enter_car && buttonCemetery){ //street button in park
                transitionState = FADE_OUT;
            }
        } 

    }

}

void PlayPositionalSound(Sound sound, Vector2 soundPos, Vector2 listenerPos, float maxDistance) {
    // Calculate distance between listener and sound source
    float dx = listenerPos.x - soundPos.x;
    float dy = listenerPos.y - soundPos.y;
    float distance = sqrtf(dx * dx + dy * dy);

    // Calculate volume based on distance
    float volume = 1.0f - (distance / maxDistance);
    if (volume < 0.0f) volume = 0.0f;

    // Set the sound volume
    SetSoundVolume(sound, volume);

    // Play the sound if volume is greater than zero
    if (volume > 0.0f) {
        if (!IsSoundPlaying(sound)) {
            PlaySound(sound);
        }
    } else {
        // Stop the sound if it's playing but volume is zero
        if (IsSoundPlaying(sound)) {
            StopSound(sound);
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


void HandleOutsideTransition(Player& player, PlayerCar& player_car, std::vector<NPC>& npcs, GameCalendar calendar) {
    if (move_car && !gotoWork && !gotoPark) {  // Car is moving, go to road
        gameState = ROAD;
        player_car.facingLeft = true;  // Leaving outside = face left
        if (!reverse_road) {
            player_car.position.x = 900;
        }
    } else if (move_car && gotoWork) {  // Move car and go to work
        gameState = WORK;
        // Additional logic if needed
    }else if (move_car && gotoPark){
        gameState = PARK;
        player_car.position.x = 1800;
        player.position.x = player_car.position.x;
        
        move_car = false;

    } else if (player.isDead) {  // Died outside, go to apartment
        gameState = APARTMENT;
        player.position.x = apartmentX;
        player.currentHealth = player.maxHealth;
        showHealthbar = false;
        player.isDead = false;
        calendar.AdvanceDay();
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
        showHealthbar = false;
        calendar.AdvanceDay();
    }
}

void HandleGraveyardTransition(Player& player, GameCalendar& calendar, std::vector<NPC>& ghosts){
    if (player.isDead){
        gameState = APARTMENT;//wake up back at your apartment with full health.
        player.position.x = apartmentX;
        player.isDead = false;
        showHealthbar = false;
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
        showHealthbar = false;
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

void HandleParkTransition(GameState& gamestate, Player& player, PlayerCar player_car){
        gameState = OUTSIDE;
        player.position.x = player_car.position.x-64; //center of car
        gotoPark = false; //reset gotopark

}

void PerformStateTransition(Player& player, PlayerCar& player_car, GameCalendar& calendar, std::vector<NPC>& npcs) {
    //if we are fading out switch to the next area depending on the situation. 
    switch (gameState) {
        case OUTSIDE:
            HandleOutsideTransition(player, player_car, npcs, calendar);
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

        case PARK:
            HandleParkTransition(gameState, player, player_car);
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

    if (player.position.x > 82.0 && player.position.x < 102 && gameState == OUTSIDE){
        PlaySound(SoundManager::getInstance().GetSound("ShovelDig"));
        shovelTint = RED;
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
        if (!inventory[i].empty()) { //inventory buttons are all done in the same for loop we use to draw it. Consider abstracting this somehow. 

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

            if (inventory[i] == "whiskey"){
                DrawTexture(resources.whiskey, x, y, WHITE);
                Rectangle whiskeyBounds = { 
                    static_cast<float>(x),      
                    static_cast<float>(y),      
                    static_cast<float>(64),  
                    static_cast<float>(64)  
                };

                if (CheckCollisionPointRec(mousePosition, whiskeyBounds)){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        if (player.hasWhiskey){
                            inventory[i] = std::string("");  // erase pills from the string
                            player.currentHealth = player.maxHealth;
                            player.hasWhiskey = false;
                            drunk = true;
                            PlaySound(SoundManager::getInstance().GetSound("gulp"));

                        }
                    }
                }


            }

            if (inventory[i] == "pills"){ // click on pills to take them 
                DrawTexture(resources.pills, x, y, WHITE);
                Rectangle pillBounds = { //pill button
                    static_cast<float>(x),      
                    static_cast<float>(y),      
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
                    static_cast<float>(x),      
                    static_cast<float>(y),      
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
                    static_cast<float>(x),      
                    static_cast<float>(y),      
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
    
    int car_start = 5500;
    car_pos.x -= 150 * GetFrameTime();
    truck_pos.x += 150 * GetFrameTime();

    if (car_pos.x < -500) car_pos.x = car_start; //Loop back to car_start
 
    if (truck_pos.x > 5500) truck_pos.x = -500;
    
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
    
    if (internetTimer > 0){
        internetTimer -= GetFrameTime();
    }

    if (showInternet){
        if (internetTimer > 0){
            DrawText("\n\nSEARCHING...\n\nNECRO-TECH", TextPos.x+12, TextPos.y-20, 20, WHITE);
        }else{
            DrawText("Adress: \n\n 123 Paper St", TextPos.x, TextPos.y, 20, WHITE);
            //TODO Once you have the address of necrotech it shows up in the car's destinations menu
            
        }
        
    }else{
        DrawText("     Sleep", TextPos.x, TextPos.y, 20, tint);
        DrawText("    Internet", TextPos.x, TextPos.y + 21, 20, Itint);
    }
}



void DrawCarUI(PlayerCar& player_car, Vector2 mousePosition, Camera2D& camera, GameState& gameState){
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);
    Vector2 ui_pos = player_car.position;
    int ui_width = 116;
    int ui_height = 64;

    //DrawRectangle(player_car.position.x, player_car.position.y, 200, 200, WHITE);
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
        DrawText("   Park", ui_pos.x, ui_pos.y-17, 16, tavern_tint);
        DrawText("   Cemetery", ui_pos.x, ui_pos.y, 16, cemetery_tint);

        work_tint = hasWorked ? BLACK : work_tint;
        DrawText("    Work", ui_pos.x, ui_pos.y+17, 16, work_tint);

        if (NecroTech) DrawText("  NecroTech", ui_pos.x, ui_pos.y+32, 16, WHITE);


        

    }else if (gameState == CEMETERY){
        
        DrawText("   Street", ui_pos.x, ui_pos.y, 16, cemetery_tint);
       //DrawText("Work", ui_pos.x, ui_pos.y+17, 16, work_tint);

    }else if (gameState == PARK){
        DrawText("    Street", ui_pos.x, ui_pos.y, 16, cemetery_tint);
        
    }

}

void DrawMagicDoor(GameResources& resources,Player& player, MagicDoor& magicDoor){
        float doorFrame = 64.0;
        Rectangle sourceDoorRec = {static_cast<float>(magicDoor.currentFrame) * doorFrame, 0, static_cast<float>(doorFrame), static_cast<float>(doorFrame)};
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

void moveUFO(UFO& ufo){
    if (canMoveUfo){
        //UFO drops down from the sky, hovers a few seconds, then darts off super fast.
        float deltaTime = GetFrameTime();
        int moveSpeed = 100;
        int stopPos = 400;
        if (ufo.basePosition.y < stopPos && move_ufo && ufoTimer > 0){ //go from starting position to 400 y and wait for timer
            ufo.basePosition.y += moveSpeed * deltaTime;
        
        }else if (ufoTimer <= 0){ //times up, shoot to the left fast
            ufo.basePosition.x -= 2000 * deltaTime;
            ufo.basePosition.y -= 2000 * deltaTime;
            
        }

        if (ufo.basePosition.x < -1000){
            ufo.basePosition = {-94.0, -200.0}; // reset ufo position if too far left.
            canMoveUfo = false; 
        }
    }

}

void DrawUFO(GameResources& resources, UFO& ufo, Camera2D& camera, float& time, ShaderResources& shaders){

    float deltaTime = GetFrameTime();
    ufo.frameTimer += deltaTime;

    if (ufo.frameTimer >= ufo.frameTime){
        ufo.frameTimer -= ufo.frameTime;
        ufo.currentFrame++;

        if (ufo.currentFrame >= ufo.totalFrames){
            ufo.currentFrame = 0; //loop
        }
    }
    // Calculate current frame's row and column
    int frameRow = 0; // Each row has 4 frames
    int frameCol = ufo.currentFrame % 4;

    // Define the source rectangle
    Rectangle sourceRect = {
        static_cast<float>(frameCol * ufo.frameWidth),
        static_cast<float>(frameRow * ufo.frameHeight),
        static_cast<float>(ufo.frameWidth),
        static_cast<float>(ufo.frameHeight)
    };

    // Update horizontal (X-axis) movement
    ufo.position.x = ufo.basePosition.x + ufo.bobAmplitudeX * sinf(ufo.bobSpeedX * time + ufo.bobOffsetX);

    // Update vertical (Y-axis) movement
    ufo.position.y = ufo.basePosition.y + ufo.bobAmplitudeY * sinf(ufo.bobSpeedY * time + ufo.bobOffsetY);

    Vector2 UFODrawPosition = {
        ufo.position.x, 
        ufo.position.y 
    };

    if (abductionBeam){
        //show abduction beam. if player is under UFO
        
        Rectangle sourceRec = { 0.0f, 0.0f, (float)resources.lightBar.width, (float)resources.lightBar.height };
        Rectangle destRec = { 
            ufo.position.x+37, // x position on screen
            ufo.position.y+96, // y position on screen
            static_cast<float>(64), // width on screen
            static_cast<float>(256)  // height on screen
        };
        Vector2 origin = { 0.0f, 0.0f };

        // Rotation angle in degrees
        float rotation = 0.0f;

        //stretch texture to fit barwidth and height,
        BeginBlendMode(BLEND_ADDITIVE);
        DrawTexturePro(resources.lightBar, sourceRec, destRec, origin, rotation, WHITE);
        EndBlendMode();

    
    }
    
    BeginShaderMode(shaders.pixelationShader); //TODO find a good shader for UFO
    DrawTextureRec(resources.UFOsheet, sourceRect, UFODrawPosition, WHITE); 
    EndShaderMode();
    
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

void DrawDialogBox(Player& player, Camera2D camera, int boxWidth, int boxHeight,int textSize){
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

    if (overLiquor){
    
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
                    npc.talkTimer = 10;
                } 
        }
    }
    if (overLiquor && showLiquor && money >= 100 &&  GuiButton((Rectangle){ screen_pos.x+16, screen_pos.y-64, 64,48 }, "BUY")){
        addMoney(-100);
        AddItemToInventory("whiskey", inventory, INVENTORY_SIZE);
        player.hasWhiskey = true;
        
    }

}

void RenderAstral(GameResources& resources, Player& player, Camera2D& camera, Vector2& mousePosition,Earth& earth,MagicDoor& magicDoor, ShaderResources& shaders){
    player.gravity = 200;
    player.outline = true;//turn on outline shader in asteral plane
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

    if (vignette){ //vignette first so others can override. 
        BeginShaderMode(shaders.vignetteShader);
    }

    if (applyShader){

        BeginShaderMode(shaders.glowShader);
        
    }

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }
    
    if (glitch){
        BeginShaderMode(shaders.glitchVignetteShader);

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
    DrawEarth(resources, earth, camera); //draw earth outside of shader. 
    
    DrawMagicDoor(resources, player, magicDoor);

    player.DrawPlayer(resources, gameState, camera, shaders);


    DrawTexturePro(resources.AstralForeground, {0, 0, static_cast<float>(resources.AstralMidground.width), static_cast<float>(resources.AstralMidground.height)},
                    {0, 0, static_cast<float>(resources.AstralMidground.width), static_cast<float>(resources.AstralMidground.height)}, {0, 0}, 0.0f, WHITE);


        // Draw platforms
    for (Platform& platform : platforms) {
     
        //platform.Draw();
       
        platform.DrawPlatformTexture(resources.platformTexture, platform.rect);
        
    }

    for (NPC& ghost: astralGhosts){
        ghost.Update(player, gameState);
        ghost.Render(shaders);
        
        if (ghost.health > 0) ghost.isActive = true;

    }

    for (NPC& bat : astralBats){
        bat.Update(player, gameState);
        bat.Render(shaders);
        //bat.agro = true;
        if (bat.health > 0) bat.isActive = true;
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
        DrawDialogBox(player, camera, 0, 0, 20);
    }

    
}


void RenderCemetery(GameResources& resources,Player& player, PlayerCar& player_car, UFO& ufo, float& time, Camera2D& camera,Vector2 mousePosition, ShaderResources& shaders){
    int carMax = 2800;
    int carMin = 2765;
    if (hasCemeteryKey){
        //playe UFO hum when ufo is present. 
        PlayPositionalSound(SoundManager::getInstance().GetSound("energyHum"), ufo.position, player.position, 800.0f);
    }
    
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
    //Cemetery Gate
    if (player.position.x > 3069 && player.position.x < 3089 && !hasCemeteryKey){
        phrase = "Locked";
        show_dbox = true;
        dboxPosition = player.position;
    }


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


    if (vignette){ //vignette first so others can override. 
        BeginShaderMode(shaders.vignetteShader);
    }

    if (applyShader){
        //drug shader
        BeginShaderMode(shaders.glowShader);
        
    }

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }
    
    if (glitch){
        //BeginShaderMode(shaders.glitchShader);
        BeginShaderMode(shaders.glitchVignetteShader);
 
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
    abductionBeam = false;
    if (player.position.x > 3929 && player.position.x < 3949){
        abductionBeam = true;
    }

    if (hasCemeteryKey){ // dont show UFO until later in the game
        ufo.basePosition = {3900, 400};
        DrawUFO(resources, ufo, camera, time, shaders);
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
        zombie.Update(player, gameState);
        zombie.Render(shaders);

    }

    //cemetery bats
    // if (hasCemeteryKey){
    //     for (NPC& bat : bats){
    //         bat.Update(player);
    //         bat.Render(shaders);
    //         bat.agro = true;
    //         if (bat.health > 0) bat.isActive = true;
    //     }

    // }


    if (show_carUI && !move_car && player.enter_car){ //destination menu //draw UI inside mode2d
        DrawCarUI(player_car, mousePosition, camera, gameState);
    }

    if (player.enter_car == false){// if enter car is false, dont render player or update position camera should stay focused on player pos. 
        player.DrawPlayer(resources, gameState, camera, shaders);

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
        DrawDialogBox(player, camera, 0, 0, 20);
    }

    if (over_gate && hasCemeteryKey){
        DrawDialogBox(player, camera, 0, 0, 20);

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

void RenderRoad(const GameResources& resources, PlayerCar& player_car,Player& player, Camera2D& camera, Vector2 mousePosition, ShaderResources& shaders){
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
    hasWorked = false; //player can go to work if he has traveled. 


    if (vignette){ //vignette first so others can override. 
        BeginShaderMode(shaders.vignetteShader);
    }

    if (applyShader){
        //drug shader
        BeginShaderMode(shaders.glowShader);
        
    }

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }
    
    if (glitch){
        BeginShaderMode(shaders.glitchVignetteShader);

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

void RenderGraveyard(GameResources resources,Player& player,Camera2D& camera,Vector2 mousePosition, ShaderResources& shaders){
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
    
    if (vignette){ //vignette first so others can override. 
        BeginShaderMode(shaders.vignetteShader);
    }

    if (applyShader){

        BeginShaderMode(shaders.glowShader);
        
    }

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }
    
    if (glitch){
        BeginShaderMode(shaders.glitchVignetteShader);

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
        player.DrawPlayer(resources, gameState, camera, shaders);

    }
    for (NPC& zombie : zombies){
        zombie.Update(player, gameState);
        zombie.Render(shaders);

        if (zombie.isDying && !firstBlood && gameState == GRAVEYARD){ //first zombie that is dying in the graveyard
            firstBlood = true;
            dz_pos = zombie.position;
            
        }
    }


    if (!start) show_dbox = false; //set to false to hide dbox when not over spot unless start where we first show tutorial text

    for (NPC& ghost: ghosts){
        ghost.Update(player, gameState);
        ghost.Render(shaders);
        ghost.ClickNPC(mousePosition, camera, player, gameState);
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
        DrawDialogBox(player, camera, 0, 0, 20);
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
        DrawDialogBox(player, camera, 0, 0, 20);

    }


    if ((player.hasGun || player.hasShotgun) && !player.enter_car) DrawHUD(player); //always show ammo when outside of car in the cemetery


    //draw healthbar 

    Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
    DrawHealthBar(resources, barPos, player.maxHealth, player.currentHealth, 128, 16);

    
}




void RenderApartment(GameResources& resources, Player player, Vector2 mousePosition, GameCalendar& calendar, Camera2D camera, ShaderResources& shaders){
    player.position.x -= 20; //ensure over_apartment = false
    int screen_center = (screenWidth - resources.apartment.width)/2;
    
     //Vector2 drawerPos = {screenWidth/2 + 160, 730};

    if (vignette){ //vignette first so others can override. 
        BeginShaderMode(shaders.vignetteShader);
    }

    if (applyShader){

        BeginShaderMode(shaders.glowShader);
        
    }

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }
    
    if (glitch){
        BeginShaderMode(shaders.glitchVignetteShader);

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

void RenderLot(GameResources& resources, Player& player, Camera2D& camera, Vector2& mousePosition,ShaderResources& shaders){
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
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxBackground = camera.target.x * 0.7f;  // Background moves even slower
    
    SoundManager::getInstance().UpdateMusic("StreetSounds"); //only update street sounds when oustide

    int cameraMinX = 2677;
    int cameraMaxX = 3048;
    
    if (player.position.x > 2677 && player.position.x < 3048){
        camera.target.x = player.position.x;

    }else{
        camera.target.x = Clamp(player.position.x, cameraMinX, cameraMaxX); //clamp camera to the center of the scene. 
    }
    

   if (vignette){ //vignette first so others can override. 
        BeginShaderMode(shaders.vignetteShader);
    }

    if (applyShader){

        BeginShaderMode(shaders.glowShader);
        
    }

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }
    
    if (glitch){
        //BeginShaderMode(shaders.glitchShader);
        BeginShaderMode(shaders.glitchVignetteShader);
 
    }

    BeginMode2D(camera);
     // Draw the background (sky)
    DrawTexturePro(resources.background, {0, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)},
                    {parallaxBackground, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)}, {0, 0}, 0.0f, WHITE);

    //Draw the midground (silhouettes)
    DrawTexturePro(resources.midgroundLot, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
                    {parallaxMidground, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),  offset by 1024 to center relative to midground. 
    DrawTexturePro(resources.vacantLot, {0, 0, static_cast<float>(resources.vacantLot.width), static_cast<float>(resources.vacantLot.height)},
                    {705+1024, 0, static_cast<float>(resources.vacantLot.width), static_cast<float>(resources.vacantLot.height)}, {0, 0}, 0.0f, WHITE);

    show_dbox = false; //turn off dbox if no one is interacting
    for (NPC& hobo : hobos){
        hobo.Update(player, gameState);
        hobo.Render(shaders);
        hobo.ClickNPC(mousePosition, camera, player, gameState);

        if (hobo.interacting){ 
            if (firstHobo){ // only raise zombie and draw shovel if you have talked the hobo
                firstHobo = false;
                
                drawShovel = true; //shovel isn't in cemetery until you talk to hobo.
                if (player.hasGun){
                    raiseZombies = true; // zombies don't spawn until you talk to hobo. 
                }
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
    
    player.DrawPlayer(resources, gameState, camera, shaders);

    
    EndMode2D();  // End 2D mode 
 
    DrawMoney(); //draw money after EndMode2d()

    if (show_dbox){      
        DrawDialogBox(player, camera, 0, 0, 20); // draw box size of 0x0. hobo has no border box
    }  

    if (showInventory){
         
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);  // Render the inventory 
    }

    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // render mouse cursor outside Mode2D. Do this last
}

void RenderPark(GameResources& resources, Player& player, PlayerCar& player_car, Camera2D& camera,Vector2& mousePosition, ShaderResources& shaders){
    BeginMode2D(camera);  // Begin 2D mode with the camera
    ClearBackground(customBackgroundColor);
    
    
    float parallaxBackground = camera.target.x * 0.9f;  // Background moves even slower
    float ParallaxBuildings = camera.target.x * 0.7;
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    over_car = false;
    if (player.position.x > player_car.position.x && player.position.x < player_car.position.x +30){
        over_car = true;
    }
    

    camera.target.x = player.position.x;
    


    if (vignette){ //vignette first so others can override. 
        BeginShaderMode(shaders.vignetteShader);
    }

    if (applyShader){

        BeginShaderMode(shaders.glowShader);
        
    }

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }

    if (glitch){
        BeginShaderMode(shaders.glitchVignetteShader);
   

    }

    BeginMode2D(camera);
    
     // Draw the background (sky)
    DrawTexturePro(resources.background, {0, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)},
                    {-512 + parallaxBackground, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the midground (silhouettes)
    DrawTexturePro(resources.ParkBuildings, {0, 0, static_cast<float>(resources.ParkBuildings.width), static_cast<float>(resources.midground.height)},
                    {-512 + ParallaxBuildings, 0, static_cast<float>(resources.ParkBuildings.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.ParkMidground, {0, 0, static_cast<float>(resources.ParkMidground.width), static_cast<float>(resources.midground.height)},
                    {-512+parallaxMidground, 0, static_cast<float>(resources.ParkMidground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),   
    DrawTexturePro(resources.ParkForeground, {0, 0, static_cast<float>(resources.ParkForeground.width), static_cast<float>(resources.foreground.height)},
                    {512, 0, static_cast<float>(resources.ParkForeground.width), static_cast<float>(resources.foreground.height)}, {0, 0}, 0.0f, WHITE);
    


    //DrawPlayerCar
    float CarFrameWidth = 128.0;
    Rectangle sourceRecCar = {player_car.currentFrame * CarFrameWidth, 0, CarFrameWidth, CarFrameWidth};
    DrawTextureRec(resources.carSheet, sourceRecCar, player_car.position, WHITE); //draw player_car

    if (player.enter_car == false){// if enter car is false, dont render player or update position. camera should stay focused on player pos. 
        SoundManager::getInstance().StopMusic("CarRun");

        //DRAW PLAYER
        player.DrawPlayer(resources, gameState, camera, shaders);

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
    show_dbox = false;//reset box
    for (NPC& npc : ParkNpcs){  
        if (npc.MiB){
            if (hasCemeteryKey){
                npc.Update(player, gameState);
                npc.Render(shaders);
                npc.ClickNPC(mousePosition, camera, player, gameState);

                if (npc.interacting){
                    dboxPosition = npc.position;
                    dealer = false; // dealer gets left on somewhere
                    show_dbox = true;   //dialogBox
                
                    phrase = npc.speech;
                }
            }else{
                //dont show mib until you have the cemetery key
            }

        }else{
            npc.Update(player, gameState);
            npc.Render(shaders);
            npc.ClickNPC(mousePosition, camera, player, gameState);
            if (npc.interacting){
                dboxPosition = npc.position;
                show_dbox = true;
                phrase = npc.speech;
            }

        }

    }



    if (show_carUI && !move_car && player.enter_car){ //destination menu //Draw inside mode2d
        DrawCarUI(player_car, mousePosition, camera, gameState);
        //drawingCarUI
        
    }

    //DrawStreetLight
    BeginBlendMode(BLEND_ADDITIVE);
    DrawTexture(resources.lightCone, 1013, 610, WHITE);
    DrawTexture(resources.lightCone, 1492, 610, WHITE);
    DrawTexture(resources.lightCone, 1967, 610, WHITE);
    EndBlendMode();

    EndMode2D();

    DrawMoney(); //draw money after EndMode2d()
    if (showInventory){
         
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);  // Render the inventory 
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        if (player.enter_car && !move_car){ // dont exit car if it's still moving.
            PlaySound(SoundManager::getInstance().GetSound("CarDoorClose")); 
            player.enter_car = false;
            player_car.currentFrame = 0;
            //player.position.x = player_car.position.x + 32;
        }
    }

    if (show_dbox){
        DrawDialogBox(player, camera, 0, 0, 20);

    }

    


    //Draw cursor last so it's on top
    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // render mouse cursor outside Mode2D. Do this last

}

//Main Street
void RenderOutside(GameResources& resources, Camera2D& camera,Player& player, PlayerCar& player_car,MagicDoor& magicDoor, float& totalTime,  std::vector<NPC>& npcs, UFO& ufo, Vector2 mousePosition, ShaderResources& shaders) {
    //play ufo sound when outside. 
    PlayPositionalSound(SoundManager::getInstance().GetSound("energyHum"), ufo.position, player.position, 800.0f);

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



    SoundManager::getInstance().PlayMusic("StreetSounds");
        
    


    if (player_car.position.x < road_min && move_car){
        transitionState = FADE_OUT;
        
        //player_car.position = Vector2 {900, 700 - 32};

    }



    if (!start) show_dbox = false; // reset to false so it can fall through unless start where we first show tutorial text
    over_apartment = false;
    over_lot = false;
    over_car = false;
    overLiquor = false;
    if (player.position.x > pc_min && player.position.x < pc_max){ //over_car
        over_car = true;
        if (fortuneTimer <= 0) phrase = "PRESS UP TO ENTER"; //Don't interupt the fortune teller
        show_dbox = true;
        dboxPosition = player.position;
        
        
    }

    
    if (player.position.x > lot_min && player.position.x < lot_max){ //over_lot
        over_lot = true;
        if (fortuneTimer <= 0) phrase = "PRESS UP TO ENTER";
        dboxPosition = player.position;
        
        show_dbox = true;

    }
    
    if (player.position.x > ap_min  && player.position.x < ap_max){ //over_apartment
        over_apartment = true;
        if (fortuneTimer <= 0) phrase = "PRESS UP TO ENTER";
        dboxPosition = player.position;
        dboxPosition.y = player.position.y + 10;
        show_dbox = true;
        
    }

    if (player.position.x > 1124 && player.position.x < 1144){
        overLiquor = true;
        dboxPosition = player.position;
        show_dbox = true;
    }

    
    if (player.position.x > -94 && player.position.x < -84 && !move_ufo){
        move_ufo = true;
        ufoTimer = 10;
        std::cout << "Moving UFO";

    }
    if (move_ufo){
        ufoTimer -= GetFrameTime();
        DrawUFO(resources, ufo, camera, totalTime, shaders);
        moveUFO(ufo);
    }

    camera.target = player.position;
    float parallaxMidBuildings = camera.target.x * 0.4;
    float parallaxMidground = camera.target.x * 0.6f;  // Midground moves slower
    float parallaxBackground = camera.target.x * 0.8f;  // Background moves even slower
    
    BeginMode2D(camera);  // Begin 2D mode with the camera
    ClearBackground(customBackgroundColor);
    
    if (vignette){ //vignette first so others can override. 
        BeginShaderMode(shaders.vignetteShader);
    }

    if (applyShader){

        BeginShaderMode(shaders.glowShader);
        
    }

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }

    if (glitch){
        BeginShaderMode(shaders.glitchVignetteShader);
   

    }
    
    //background/midground width = 6400

     // Draw the background (sky)
    DrawTexturePro(resources.background, {0, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)},
                    {-1000 + parallaxBackground, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the midground (silhouettes)
    DrawTexturePro(resources.midground, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
                    {-3000 + parallaxMidground, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.MidBuildings, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
                    {-3000 + parallaxMidBuildings, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),  offset by 1024 to center relative to midground. 
    DrawTexturePro(resources.foreground, {0, 0, static_cast<float>(resources.foreground.width), static_cast<float>(resources.foreground.height)},
                    {-639, 0, static_cast<float>(resources.foreground.width), static_cast<float>(resources.foreground.height)}, {0, 0}, 0.0f, WHITE);
    
    
   
    if (move_ufo){
        DrawUFO(resources, ufo, camera, totalTime, shaders);
    }
    if (move_car){
        player_car.position.x -= player_car.carSpeed * GetFrameTime();
    }else{
        player_car.position = Vector2{1710, 668};
    }
    //mibs show up after you get cemetery key. They don't do anything yet. 
    if (hasCemeteryKey){
        for (NPC& mib : mibs){
            mib.Update(player, gameState);
            mib.Render(shaders);
            
        }

    }


    teller = false;
    for (NPC& npc : npcs){
        npc.Update(player, gameState);
        npc.Render(shaders);
        npc.ClickNPC(mousePosition, camera, player, gameState);
    

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
                if (fortuneTimer <= 0 && !teller && !dealer){
                    phrase = npc.speech; //randomized speech
                    dealer = false;

                }
             
            }
        }else{
            dealer = false;
        
            // show_dbox = false;
        }
    
    }

    EndShaderMode(); ////////////////////////////SHADER OFF
    
    //DrawStreetLight
    BeginBlendMode(BLEND_ADDITIVE);
    DrawTexture(resources.lightCone, 1884, 610, WHITE);
    DrawTexture(resources.lightCone, 3188, 610, WHITE);
    DrawTexture(resources.lightCone, 456, 610, WHITE);
    EndBlendMode();
    
    DrawBullets();
    UpdateBullets();
    //DrawPlayerCar
    float CarFrameWidth = 128;
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
        
           
        player.DrawPlayer(resources, gameState, camera, shaders);
            
        
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
    if (show_carUI && !move_car && player.enter_car){ //draw carUI inside Mode2d for reasons
        DrawCarUI(player_car, mousePosition, camera, gameState);
    }


    EndMode2D();  // End 2D mode 

    if (player.currentHealth < 100) showHealthbar = true; // dont show healthbar until youve taken damage, when on street
    Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
    if (showHealthbar) DrawHealthBar(resources, barPos, player.maxHealth, player.currentHealth, 128, 16);




    if (show_dbox && !player.enter_car){

        if (over_lot || over_apartment || over_car || start || overLiquor){
            DrawDialogBox(player, camera, 0, 0, 20);
            
            
        }else{
            DrawDialogBox(player, camera, 0, 0, 20);
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
    int generic = 2;
    for (int i = 0; i < generic; ++i) {
        Vector2 startPosition = { static_cast<float>(512 + i * 200), 700 };  // positions spread out along the x axis    
        NPC npc = CreateNPC(resources.npcTexture, startPosition, speed, IDLE,  true, false);
        npc.SetDestination(-94, 4000);
        npcs.push_back(npc);  // Add the NPC to the vector
        ParkNpcs.push_back(npc);
    }

    //spawn businessMan
    int b_men = 2;
    for (int i = 0; i < b_men; i++){
        Vector2 b_pos = { static_cast<float>(1000 + i * 100), 700};
        NPC business_npc = CreateNPC(resources.businessSheet, b_pos, speed,IDLE, true, false);
        business_npc.SetDestination(1000, 4000);
        npcs.push_back(business_npc);
        ParkNpcs.push_back(business_npc);

    }


    //spawn woman
    int women = 1;
    for (int i = 0; i < women; i++){
        Vector2 w_pos = {static_cast<float>(1000 + i * 100), 700};
        NPC woman_npc = CreateNPC(resources.womanSheet, w_pos, speed,IDLE, true, false);
        woman_npc.SetDestination(0, 4000);
        npcs.push_back(woman_npc);

    }

    //spawn woman2
    int women2 = 2;
    for (int i = 0; i < women2; i++){
        Vector2 w_pos = {static_cast<float>(2220 + i * 100), 700};
        NPC woman2_npc = CreateNPC(resources.woman2Sheet, w_pos, speed, IDLE, true, false);
        woman2_npc.SetDestination(0, 4000);
        npcs.push_back(woman2_npc);
        ParkNpcs.push_back(woman2_npc);
    }

    //create mibs
    int m = 1;
    for (int i = 0; i < m; i++){
        Vector2 mib_pos = {static_cast<float>(2220 + i * 100), 700};
        NPC mib = CreateNPC(resources.mibSheet, mib_pos, speed, IDLE, true, false);
        mib.SetDestination(2000, 2400);
        mib.MiB = true;
        mibs.push_back(mib);
        ParkNpcs.push_back(mib);
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

    //create astral bats
    int ba = 5;
    for (int i = 0; i < ba; i++){
        Vector2 b_pos = {static_cast<float>(1800 + i * 200), 100};
        NPC bat = CreateNPC(resources.batSheet, b_pos, speed, IDLE, false, false);
        bat.SetDestination(1500, 3000);
        bat.bat = true;
        astralBats.push_back(bat);
    }



    //create ghost // call update on ghost where ever needed like graveyard or cemetery
    Vector2 g_pos = {2100, 700};
    NPC ghost_npc = CreateNPC(resources.ghostSheet, g_pos, speed, IDLE, false, false);
    ghost_npc.SetDestination(2100, 2200);
    ghost_npc.ghost = true;
    ghost_npc.maxHealth = 500;
    ghost_npc.health = 500;
    ghosts.push_back(ghost_npc);

    //spawn astral ghosts
    int ap = 0;
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
        police_npc.SetDestination(0, 4000);
        police_npc.police = true;
        npcs.push_back(police_npc);

    }

    //spawn dealer
    int dealer = 1;

    for (int i = 0; i < dealer; i++){
        Vector2 d_pos = {static_cast<float>(2200 + i * 100), 700};
        NPC dealer_npc = CreateNPC(resources.dealerSheet, d_pos, speed, IDLE, true, false);
        dealer_npc.SetDestination(0, 4000);
        dealer_npc.dealer = true;
        npcs.push_back(dealer_npc);
    }

}

void DisplayDate(GameCalendar& calendar){
    DrawText(calendar.GetDate().c_str(), screenWidth/2 - 450, 25, 20, WHITE);
}


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
            }

        if (IsKeyPressed(KEY_O)){
            if (!player.outline){
                player.outline = true;
            }else{
                player.outline = false;
            }
        }

        if (IsKeyPressed(KEY_P)){
            AddItemToInventory("Drugs", inventory, INVENTORY_SIZE);
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



void UptoEnter(Player& player, PlayerCar& player_car){
    //enter places by pressing up 
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){

        if (overLiquor && gameState == OUTSIDE){
            show_dbox = true;
            showLiquor = true;
            
            
            phrase = "Whiskey: $100";
        }

        if (over_apartment && gameState == OUTSIDE){
            transitionState = FADE_OUT; //Transition to apartment
            PlaySound(SoundManager::getInstance().GetSound("mainDoor"));
            over_apartment = false;
            showInventory = false;
            //player.position.x = 512; //move player, to move inventory to the middle of the screen. 
            
        }
        //enter car for both outside and cemetery and Park
        if (over_car && !player.enter_car && has_car_key){
            //player inside idling car
            SoundManager::getInstance().PlayMusic("CarRun");
            //PlayPositionalSound(SoundManager::getInstance().GetSound("carRun"), player_car.position, player.position, 800);
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
}

void InitSounds(SoundManager& soundManager){
    //We use our own custom sound manager. We have an array of sounds, and an array of musticTracks.
    SetMasterVolume(1.0f);  // Sets the master volume to maximum
    
    SoundManager::getInstance().LoadMusic("CarRun", "assets/sounds/CarRun.ogg"); // load CarRun.ogg into music tracks with the name CarRun
    //music tracks automatically loop.The car running sound needs to loop, so we call it music.
    
    SoundManager::getInstance().LoadMusic("enchantedNight", "assets/sounds/enchantedNight.ogg");
    
    SoundManager::getInstance().LoadMusic("StreetSounds", "assets/sounds/StreetSounds.ogg"); 
    //SoundManager::getInstance().LoadMusic("Jangwa", "assets/sounds/Jangwa.ogg");
    SoundManager::getInstance().LoadMusic("Neon", "assets/sounds/Neon.ogg");
    SoundManager::getInstance().LoadMusic("NewNeon", "assets/sounds/Neon(noDrum).ogg");
    soundManager.LoadSound("carRun", "assets/sounds/CarRun.ogg");
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
    soundManager.LoadSound("gulp", "assets/sounds/gulp.ogg");
    soundManager.LoadSound("energyHum", "assets/sounds/energyHum.ogg");

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
    SoundManager::getInstance().SetMusicVolume("CarRun", 0.25f);
    SoundManager::getInstance().SetMusicVolume("Schumann", 0.25f);
    SoundManager::getInstance().SetMusicVolume("enchantedNight", 0.5f);

    SoundManager::getInstance().SetSoundVolume("CarStart", 0.5);
    SoundManager::getInstance().SetSoundVolume("BoneCrack", 0.3f);
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

    // Initialize shaders
    ShaderResources shaders; //struct holding all the shaders. 
    InitShaders(shaders, screenWidth, screenHeight); //refactored shader setup to shaderControl.cpp
    
    // Initialize player
    Player player;
    PlayerCar player_car;
    Earth earth;
    MagicDoor magicDoor;
    UFO ufo;


    InitializePlayerCar(player_car);
    InitializeMagicDoor(magicDoor);
    InitEarth(earth);
    InitUFO(ufo);
    spawnNPCs(resources); //spawn NPCs before rendering them outside
    InitPlatforms();



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

    //AddItemToInventory("Drugs", inventory, INVENTORY_SIZE);


    //PlayMusicStream(SoundManager::getInstance().GetMusic("Jangwa"));
    PlayMusicStream(SoundManager::getInstance().GetMusic("NewNeon"));
    //PlayMusicStream(SoundManager::getInstance().GetMusic("enchantedNight"));
   
  
 

    
    //int timeLoc = shaders.timeLoc;
    float totalTime = 0.0f; // time elapsed from start of game //glitch shader/ufo
    // Main game loop
    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();
        if (!player.enter_car) player.UpdateMovement(resources, gameState, mousePosition, camera, platforms);  // Update player position and animation
        UpdateInventoryPosition(camera, gameState);
        SoundManager::getInstance().UpdateMusic("NewNeon");
        //SoundManager::getInstance().UpdateMusic("enchantedNight");
        SoundManager::getInstance().UpdateMusic("CarRun");
      
        UpdateBullets();
        CheckBulletNPCCollisions(zombies); //check each enemy group for bullet collisions
        CheckBulletNPCCollisions(ghosts);
        CheckBulletNPCCollisions(astralGhosts);
        CheckBulletNPCCollisions(bats);
        CheckBulletNPCCollisions(astralBats);

        MonitorMouseClicks(player, calendar);
        UpdateZombieSpawning(resources, player);
        //glowEffect(glowShader, gameState); //update glow shader
        
        float deltaTime = GetFrameTime();
        totalTime += deltaTime; // used for UFO sine wave
        if (totalTime > 10000.0f) totalTime -= 10000.0f; //reset total time just in case. 
            
        UpdateShaders(shaders, deltaTime, gameState);
        if (player.hitTimer > 0){
            float redVignetteColor[3] = { 1.0f, 0.0f, 0.0f }; // Red color
            float sradius = 0.5; //lower radius to make the vignette more visible
            // Set the vignette color in the shader
            SetShaderValue(shaders.vignetteShader, shaders.radiusLoc, &sradius, SHADER_UNIFORM_FLOAT);
            SetShaderValue(shaders.vignetteShader, shaders.vignetteColorLoc, redVignetteColor, SHADER_UNIFORM_VEC3);
        }

        
        if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)){ //tutorial text
            start = false; //turn off dbox if any movement
        }

        if (IsKeyPressed(KEY_M)){ //MUTE MUSIC
            if (SoundManager::getInstance().IsMusicPlaying("NewNeon")){
                SoundManager::getInstance().PauseMusic("NewNeon");
                //SoundManager::getInstance().PauseMusic("enchantedNight");

            }else{
                SoundManager::getInstance().ResumeMusic("NewNeon");
                //SoundManager::getInstance().ResumeMusic("enchantedNight");
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

        UptoEnter(player, player_car);//enter different areas by pressing up
        handleCamera(camera, targetZoom);

        BeginDrawing();

        if (gameState == OUTSIDE){
            RenderOutside(resources, camera, player, player_car, magicDoor, totalTime, npcs, ufo, mousePosition, shaders); 
            DisplayDate(calendar);//why not display date once globally? there are reasons 

        }else if (gameState == APARTMENT){
            RenderApartment(resources, player, mousePosition, calendar, camera, shaders);
            DisplayDate(calendar);

        }else if (gameState == ROAD){
            RenderRoad(resources, player_car, player, camera, mousePosition, shaders);
            DisplayDate(calendar);

        }else if (gameState == CEMETERY){
            RenderCemetery(resources, player, player_car, ufo, totalTime, camera,mousePosition, shaders);
            DisplayDate(calendar);

        }else if (gameState == WORK){
            ClearBackground(BLACK);//do nothing at the moment

        }else if (gameState == LOT){ // vacant lot
            RenderLot(resources, player, camera, mousePosition, shaders);
            DisplayDate(calendar);

        }else if (gameState == GRAVEYARD){
            RenderGraveyard(resources, player, camera, mousePosition, shaders);
            DisplayDate(calendar);
            
        }else if (gameState == ASTRAL){
            DisplayDate(calendar);
            RenderAstral(resources, player, camera, mousePosition, earth, magicDoor, shaders);
        }else if (gameState == PARK){
            DisplayDate(calendar);
            RenderPark(resources, player,player_car, camera, mousePosition, shaders);

        }

        //show FPS
        int fps = GetFPS();
        Vector2 fpos = {935, 935}; //bottom right
        DrawText(std::to_string(fps).c_str(), fpos.x, fpos.y, 25, WHITE);
        
        HandleTransition(player, player_car, calendar, npcs); //Check everyframe for gamestate transitions, inside draw to handle fadeouts
        EndDrawing();
        EndShaderMode();
        
        
    }

    // Unload resources and close the window
    UnloadGameResources(resources);
    soundManager.UnloadAllSounds();
    UnloadShaders(shaders);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
