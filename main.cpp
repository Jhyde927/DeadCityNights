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
#include <cstdlib>  
#include <ctime>
#include "shaderControl.h"
#include <random>
#include <algorithm>

#include "raygui.h"


//Remember: The Law is One. 


float apartmentX = 2256;
int vacantLotX = 2753;
int vacantExitX = 2762;
bool over_lot = false;
bool over_exit = false;
//cemetery_start 1743, 700
bool runOnce = true;
bool quitRequested = false;
bool streetSounds = false;
bool over_apartment = false;
bool over_car = false;
bool over_elevator = false;
bool over_Ebutton = false;
bool over_necro = false;
bool over_gate = false;
bool over_shotgun = false;
bool show_carUI = false;
bool leave_apartment = false;
bool leave_cemetery = false;
bool buttonNecro = false;
bool buttonCemetery = false;
bool buttonInternet = false;
bool hasCemeteryKey = false;
bool canGiveFortune = true;
bool can_spawn_zombies = true;
bool visitedOffice = false;
bool showInternet = false;
bool borderlessWindow = false;
bool windowStateChanged = false;
bool fullscreen = false;
bool move_ufo = false;
bool canMoveUfo = true;
bool globalAgro = false;
bool firstHobo = true;
bool can_spawn_robots = true;
bool can_spawn_mibs = true;
bool firstBlood = false;
bool drawShovel = false;
bool drawMac10 = true;
bool drawShotgun = true;
bool dealerButtonAdded = false;
bool subwayToPark = false;
bool carToPark = false;
bool buttonWork = false;

bool over_medkit = false;
bool digSpot = false;
bool NecroTech = false;
bool playerOffsetX = 0;
bool film = false;
bool start = true;
bool buttonPark = false;
bool gotoWork = false;
bool gotoPark = false;
bool gotoStreet = false;
bool gotoNecro = false;
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
bool menuOpen = false;
bool controlsMenu = false;
bool showLiquor = false;
bool can_sell_drugs = true;
bool applyShader = false;
bool drunk = false;
bool glitch = false;
bool vignette = true; //start vignette
bool openMagicDoor = false;
bool move_car = false;
bool trainAtStation = false;
bool reverse_road = false;
bool has_car_key = false;
bool overLiquor = false;
bool overSubway = false;
bool subwayExit = false;
bool npcWalk = false;
bool openDrawer = false;
bool raiseZombies = false;
bool zombieWave2 = false;
bool zombieWave3 = false;
bool abductionBeam = false;
bool raiseParkZombies = false;
bool show_dbox = true;
float ufoTimer = 0.0;
float dboxTime = 10.0;
float internetTimer = 0.0;
float inventoryPositionX = 0.0f;
float inventoryPositionY = 0.0f;
float inventoryTargetX = 0.0f;
float inventoryTargetY = 0.0f;
float passwordTimer = 0.0;
float DoorframeTimer = 0.0f;
float astralThreshold = 0.5f;
float DoorframeTime = 0.1f;
float badgeTimer = 0.0f;
float fortuneTimer = 0.0f;
int remainingZombiesToSpawn = 0;    // Tracks remaining zombies to spawn
float spawnTimer = 0.0f;            // Timer for spawning
float nextSpawnDelay = 0.0f;        // Time delay between spawns
float mibTimer = 3.0f;
float blackoutTime = 2.0f;  // Time to stay blacked out
float blackoutTimer = 0.0f; // Timer to keep track of blackout period

float minDistToPlayer = 50;
float maxDistToPlayer = 200;

int gameWidth = 1024; // game resolution width
int gameHeight = 1024; // game resolution height


Color customBackgroundColor = {32, 42, 63, 255};  //Same Color as sky background image. 
Color shovelTint = WHITE;

int money = 100;
int displayMoney = 100;
bool showInventory = false;
const int INVENTORY_SIZE = 10;  // Define the size of the inventory
std::string inventory[INVENTORY_SIZE] = {"", "", "", "", "", "", "", "", "", ""}; //Inventory is a fixed array for no particular reason.

const int GAME_SCREEN_WIDTH = 1024;
const int GAME_SCREEN_HEIGHT = 1024;

// Variables for password input
std::string enteredPassword = "";
const std::string correctPassword = "666";
bool passwordValidated = false;
bool showPasswordInterface = false;

std::string phrase = "A and D to move, hold shift to run"; //initial tutorial phrase

const int screenWidth = 1024; //screen is square for gameplay reasons, we don't want to reveal to much of the screen at one time. 
const int screenHeight = 1024; // is it crazy to keep the resolution square? Implement full screen that keeps sqaure rotation.

int offsetX = (screenWidth - gameWidth) / 2;
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


std::vector<NPC> npcs; //outside // subway
std::vector<NPC> zombies; //cemetery/graveyard
std::vector<NPC>hobos; //lot
std::vector<NPC>ghosts; //graveyard friendly ghost
std::vector<NPC>bats; //not used
std::vector<NPC>mibs; //outside
std::vector<NPC>astralGhosts;
std::vector<NPC>astralBats;
std::vector<NPC>ParkNpcs;
std::vector<NPC>robots; //necrotech
std::vector<NPC>lobbyRobots;
std::vector<NPC>lobbyNPCs;
std::vector<NPC>lobbyMibs;
std::vector<NPC>officeWorkers;


std::vector<Platform> platforms;


GameState gameState = OUTSIDE;

TransitionState transitionState = NONE;
float fadeAlpha = 1.0f;  // Starts fully opaque
float fadeSpeed = 0.02f; // Speed of fade (adjust as needed)
bool firstTransition = true;

// Initialize random number generator
std::random_device rd;   // Seed for the random number engine
std::mt19937 gen(rd());  // Mersenne Twister engine
std::uniform_real_distribution<float> dis(0.0f, 4000.0f); // Uniform distribution between 1000 and 4000 for NPC distribution


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

struct Elevator {
    Vector2 position;      // Position of the elevator
    int currentFrame;      // Current frame for animation
    float frameTimer;      // Timer for frame updates
    float frameTime;       // Duration of each frame
    bool isOpen;           // Tracks if the elevator is open
    bool isOccupied;       // Tracks if the player is on the elevator
    int totalFrames;       // Total number of animation frames
    int currentFloorFrame;
    float floorFrameTimer;
    float floorFrameTime;
    Vector2 floorOffset;
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


struct Train {
    Vector2 position;
    float speed;
    float maxSpeed;
    float minSpeed;
    float stopPosition; //middle of the subway 2500
    float acceleration;
    float deceleration;
    float stopDuration;
    float postLoopWaitDuration;  // New
    float postLoopWaitTimer;     // New
    float stopTimer;
    float slowDownStartX;
    TrainState state;
};

std::vector<Elevator> elevators;

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
    resources.shootSheetAuto = LoadTexture("assets/shootSheetAuto.png");
    resources.reloadSheetAuto = LoadTexture("assets/reloadSheetAuto.png");
    resources.Mac10 = LoadTexture("assets/Mac10.png");
    resources.Mac10pickup = LoadTexture("assets/Mac10pickup.png");
    resources.subwayForeground = LoadTexture("assets/subwayForground.png");
    resources.subwayBackground = LoadTexture("assets/subwayBackground.png");
    resources.subwayMidground = LoadTexture("assets/subwayMidground.png");
    resources.train = LoadTexture("assets/Train.png");
    resources.ntForeground = LoadTexture("assets/NTforeground.png");
    resources.robotSheet = LoadTexture("assets/robotSheet.png");
    resources.LobbyForeground = LoadTexture("assets/LobbyForeground.png");
    resources.elevatorSheet = LoadTexture("assets/elevatorSheet.png");
    resources.floorNumberSheet = LoadTexture("assets/floorNumberSheet.png");
    resources.officeBackground = LoadTexture("assets/officeBackground.png");
    resources.officeSheet = LoadTexture("assets/officeSheet.png");

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
    UnloadTexture(resources.MidBuildings);
    UnloadTexture(resources.shootSheetAuto);
    UnloadTexture(resources.reloadSheetAuto);
    UnloadTexture(resources.Mac10);
    UnloadTexture(resources.Mac10pickup);
    UnloadTexture(resources.subwayBackground);
    UnloadTexture(resources.subwayForeground);
    UnloadTexture(resources.subwayMidground);
    UnloadTexture(resources.train);
    UnloadTexture(resources.ntForeground);
    UnloadTexture(resources.robotSheet);
    UnloadTexture(resources.LobbyForeground); 
    UnloadTexture(resources.elevatorSheet);
    UnloadTexture(resources.floorNumberSheet);
    UnloadTexture(resources.officeBackground);
    UnloadTexture(resources.officeSheet);

  
}

void InitializePlayerCar(PlayerCar& player_car){
    player_car.position = {1710, 700-32};
    player_car.carSpeed = 100;
    player_car.currentFrame = 0;
}

void InitializeMagicDoor(MagicDoor& magicDoor, Vector2 position){
    magicDoor.position = position;//{2089, 700};
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

void InitElevator(Elevator& elevator, Vector2 position){
    elevator.position = position;
    elevator.currentFrame = 0;
    elevator.frameTimer = 0.0;
    elevator.frameTime = 0.05;
    elevator.isOpen = false;
    elevator.isOccupied = false;
    elevator.totalFrames = 7;

    elevator.currentFloorFrame = 0;
    elevator.floorFrameTimer = 0.0; //ticks up when fading out and elevator is occupied and closed. 
    elevator.floorFrameTime= 0.18; //stops on floor 7. 0.01667 second per loop 
    elevator.floorOffset = Vector2 {32, -10}; //floorNumbers offset from elevator position
    
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

void InitializeTrain(Train &train) {
    // Set train parameters
    train.position = {5500.0f, 700};
    train.maxSpeed = 400;
    train.stopPosition = 2500.0f;
    train.speed = train.maxSpeed;
    train.minSpeed = 0.0f;
    train.acceleration =  300;
    train.deceleration = 300;
    train.stopDuration = 5;
    train.stopTimer = 0.0f;
    train.postLoopWaitDuration = 10.0f; // Time to wait after reaching x = 0
    train.postLoopWaitTimer = 0.0f;
    train.state = MovingToStation;

    // Calculate the distance needed to stop


    float stoppingDistance = (train.maxSpeed * train.maxSpeed) / (2.0f * train.deceleration);
    train.slowDownStartX = 2500.0f + stoppingDistance;
}

void InitPlatforms() {
    //initialize platforms before drawing them in astral
    //emplace_back: Constructs the Platform object directly in the vector without creating a temporary object.
    
    platforms.emplace_back(2300.0f, 675.0f, 200.0f, 20.0f, WHITE);
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
        "Your courage will lead you\n\n to unexpected rewards.\n\n The password is: 666",
        "Fortune smiles upon you\n\nin your next endeavor.\n\n The password is: 666",
        "A difficult choice \n\nwill test your resolve.\n\n The password is: 666",
        "Beware of the shadows\n\n not all is as it seems.\n\n The password is: 666",
        "Fortune favors the bold\n\n take the leap.\n\n The password is: 666",

    };

    int randomIndex = rand() % tellerPhrases.size();
    return tellerPhrases[randomIndex];
}

// Render and update logic
void RenderPasswordInterface() {
    // Draw three rectangles for the password slots
    int slotWidth = 50, slotHeight = 70;
    int startX = 512, startY = 512; // Adjust based on screen size
    for (int i = 0; i < 3; i++) {
        int x = startX + i * (slotWidth + 10);
        DrawRectangle(x, startY, slotWidth, slotHeight, BLACK);
        if (i < enteredPassword.size()) {
            DrawText(std::string(1, enteredPassword[i]).c_str(), x + 15, startY + 15, 40, WHITE);
        }
    }

    // Prompt message
    if (!passwordValidated) {
        DrawText("Enter 3-digit password:", startX, startY - 40, 20, WHITE);
    } else {
        DrawText("Access Granted!", startX, startY - 40, 20, GREEN);
    }
}

void UpdatePasswordInterface(Player& player) {



    // Handle digit input (main number keys and numpad keys)
    int key = GetKeyPressed();
    if ((key >= KEY_ZERO && key <= KEY_NINE) || (key >= KEY_KP_0 && key <= KEY_KP_9)) {
        if (enteredPassword.size() < 3) {
            // Normalize input: for numpad keys, subtract `KEY_KP_0` to get the digit
            int digit = (key >= KEY_KP_0 && key <= KEY_KP_9) ? key - KEY_KP_0 : key - KEY_ZERO;
            enteredPassword += std::to_string(digit);
        }
    }

    // Handle backspace for correction
    if (IsKeyPressed(KEY_BACKSPACE) && !enteredPassword.empty()) {
        enteredPassword.pop_back();
    }

    // Validate password once all 3 digits are entered
    if (enteredPassword.size() == 3) {
        if (enteredPassword == correctPassword && !passwordValidated) {
            passwordValidated = true;
            player.validatedPassword = true;
            
            for (NPC& robot : robots){ //set validPassword to true for all robots. once password is entered. 
                robot.validPassword = true;
            }

            for (NPC& robot : lobbyRobots){ 
                robot.validPassword = true;
            }

            passwordTimer = 2.0f;
            
        } else {
            enteredPassword = ""; // Reset on incorrect password
            robots[0].idleTime = 0;
            //play a sound
        }
    }
}

bool AreAllNPCsDeactivated(const std::vector<NPC>& npcs) {
    return std::all_of(npcs.begin(), npcs.end(), [](const NPC& npc) {
        return !npc.isActive; // Return true if isActive is false
    });
}



void DrawElevator(Elevator& elevator, Texture2D elevatorTexture, Texture2D floorTexture, int frameWidth, int frameHeight, float deltaTime) {
    // Update animation only if the elevator is opening or closing

    if (gameState == OFFICE) elevator.currentFloorFrame = 7;
    if (gameState == LOBBY) elevator.currentFloorFrame = 0;

    if (elevator.isOccupied && !elevator.isOpen){ //animate floor numbers
        
        // elevator.floorFrameTimer += deltaTime;
        // if (elevator.floorFrameTimer >= elevator.floorFrameTime){
        //     elevator.floorFrameTimer -= elevator.floorFrameTime;
        //     elevator.currentFloorFrame++;
        // }

        //dont count up floors

     

    }
    if (elevator.isOpen && elevator.currentFrame < elevator.totalFrames - 1) { //animate opening door
        elevator.frameTimer += deltaTime;
        if (elevator.frameTimer >= elevator.frameTime) {
            elevator.frameTimer -= elevator.frameTime;
            elevator.currentFrame++;  // Play forward
        }
    } 
    else if (!elevator.isOpen && elevator.currentFrame > 0) { //animate closing door
        elevator.frameTimer += deltaTime;
        if (elevator.frameTimer >= elevator.frameTime) {
            elevator.frameTimer -= elevator.frameTime;
            elevator.currentFrame--;  // Play backward
        }
    }

    // Source rectangle for sprite animation
    Rectangle sourceRectFloor = {
        static_cast<float>(elevator.currentFloorFrame * 64.0f), 0.0f,
        static_cast<float>(64), static_cast<float>(64)
    };

    // Destination rectangle
    Rectangle destRectFloor = {
        elevator.position.x + elevator.floorOffset.x, elevator.position.y + elevator.floorOffset.y, //add offset to elevator position to get floor number pos
        static_cast<float>(64), static_cast<float>(64)
    };


    // Source rectangle for sprite animation
    Rectangle sourceRect = {
        static_cast<float>(elevator.currentFrame * frameWidth), 0.0f,
        static_cast<float>(frameWidth), static_cast<float>(frameHeight)
    };

    // Destination rectangle
    Rectangle destRect = {
        elevator.position.x, elevator.position.y,
        static_cast<float>(frameWidth), static_cast<float>(frameHeight)
    };

    DrawTexturePro(floorTexture, sourceRectFloor, destRectFloor, {0.0f, 0.0f}, 0.0f, WHITE);

    DrawTexturePro(elevatorTexture, sourceRect, destRect, {0.0f, 0.0f}, 0.0f, WHITE);
}




void MonitorMouseClicks(Player& player, GameCalendar& calendar){

    //monitors mouse clicks for all scenes. Consider moving item pickup left clicks here. 

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
                player.necroTechSearched = true;
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
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){ //we are already checking for mouseclick
                if (player.enter_car && buttonCemetery){ //press buttons cemetery
                    move_car = true;
                    show_carUI = false;
                }else if (player.enter_car && buttonWork){//button press work
                    //do something
                    gotoWork = true;
                    move_car = true;
                    hasWorked = true;
                }else if (player.enter_car && buttonPark){ //button press Park
                    gotoPark = true;
                    
                    move_car = true;
                    
                }else if (player.enter_car && buttonNecro){ //button press NecroTech
                    move_car = true;
                    gotoNecro = true;
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
        }else if (gameState == SUBWAY){
            if (buttonPark){
                //do something
            }
        }else if (gameState == NECROTECH){
            if (buttonCemetery){
                transitionState = FADE_OUT;
            }
        }

    }

}

void HandleKeyboardAiming(Player& player, Vector2 mousePosition){
    //mousePosition is screen2world(mousePosition)
    if (player.isAiming && IsKeyDown(KEY_F)) {
        // Handle keyboard-only aiming (e.g., using arrow keys or player movement keys)
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            player.facingRight = true;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            player.facingRight = false;
        }
    }else if (player.isAiming && !IsKeyDown(KEY_F)) {// If the player is not aiming with keyboard, allow mouse control to set the facing direction
        // Set facing direction based on world mouse position
        player.facingRight = mousePosition.x > player.position.x; //facing right is true if mousepos.x > playerPos.x

    }
}


void PlayPositionalSound(Sound sound, Vector2 soundPos, Vector2 listenerPos, float maxDistance) {
    //There are 2 ways to play positional sounds, this function and one built into sound manager.
    //This function loops and is used for UFO energyHum, and posible player_car. Sound manager positional sound is for non looping sounds. 


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


void DrawMoney(){
    std::string smoney = "$ " + std::to_string(displayMoney);

    DrawText(smoney.c_str(), screenWidth/2+400, 25, 30, WHITE);
    //Animate money ticking up or down. 
    if (displayMoney < money){
        displayMoney++;
    }else if (displayMoney > money){
        displayMoney--;
    }
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
    //film = true;
    if (gameState != OFFICE) glitch = true; //Activate glitch shader to make things more dramatic
    
}

void spawnRobot(GameResources& resources, Player& player, Vector2 position){
    //spawn more robots in the lobby on first robot death
    int speed = 50;
    NPC robot_npc = CreateNPC(resources.robotSheet, position, speed, RISING, true, false);
    robot_npc.robot = true;
    robot_npc.maxHealth = 300;
    robot_npc.health = 300;
    robot_npc.agro = true; //robots spawn angry
    robot_npc.SetDestination(player.position.x, player.position.x + 100);
    lobbyRobots.push_back(robot_npc);

}

void spawnMib(GameResources& resources, Player& player, Vector2 position){
    //spawn more mibsin the lobby on first agro
    int speed = 50;
    NPC mib_npc = CreateNPC(resources.mibSheet, position, speed, IDLE, true, false);
    mib_npc.MiB = true;
    mib_npc.maxHealth = 100;
    mib_npc.health = 100;
    mib_npc.agro = true; //robots mibs angry
    mib_npc.SetDestination(player.position.x, player.position.x + 100);
    lobbyMibs.push_back(mib_npc);

}

void spawnZombie(GameResources& resources, Vector2 position){
    //spawn a zombie at the dead NPC position
    
    int zombie_speed = 25;
    NPC zombie_npc = CreateNPC(resources.zombieSheet, position, zombie_speed, RISING, true, true);
    zombie_npc.SetDestination(1000, 3000);
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
    
    
}

void UpdateZombieSpawning(GameResources& resources, Player& player){
    if (remainingZombiesToSpawn > 0){
        spawnTimer += GetFrameTime();

        if (gameState == LOBBY || gameState == OFFICE){ //play alarm sound when zombies are spawning inside the building. 
            if (!SoundManager::getInstance().IsSoundPlaying("alarm")){
                PlaySound(SoundManager::getInstance().GetSound("alarm"));
            }
        }

        if (spawnTimer >= nextSpawnDelay){ // spawn zombies at randomm position around the player
        
            if (gameState == OFFICE) maxDistToPlayer = 400;//spawn zombies further away, more of a chance they find a target. 

            Vector2 z_pos = GetRandomSpawnPositionX(player.position, minDistToPlayer, maxDistToPlayer);  // Min/max distance from player, set globally so it can change
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
            float minDelay = 1.0f;
            float maxDelay = 3.0f; 
            nextSpawnDelay = minDelay + ((float)rand() / (float)RAND_MAX) * (maxDelay - minDelay);
            
            // Decrease the number of zombies left to spawn
            remainingZombiesToSpawn--;
        }
    }else{
        glitch = false; //glitch only runs if zombies are actively spawning.
        //film = false;
        
    }

}

void UpdateTrain(Train &train,Player& player, float deltaTime) {
    switch (train.state) {
        case MovingToStation:
            if (train.position.x < 5500 && gameState == SUBWAY){
                PlayPositionalSound(SoundManager::getInstance().GetSound("TrainArriving"), train.position, {3011, 700}, 700);
            }
            
            train.position.x -= train.speed * deltaTime;
            if (train.position.x <= train.slowDownStartX) {
                train.state = SlowingDown;
            }
            break;

        case SlowingDown:
            train.speed -= train.deceleration * deltaTime;
            if (train.speed <= train.minSpeed || train.position.x <= train.stopPosition) {
                train.speed = train.minSpeed;
                train.position.x = train.stopPosition; // Ensure exact stop position
                train.state = StoppedAtStation;
                train.stopTimer = 0.0f;
            } else {
                train.position.x -= train.speed * deltaTime;
            }
            break;

        case StoppedAtStation:
            if (player.enter_train && player.arriving){ //if arriving, kick out of train. 
                player.enter_train = false;
                player.arriving = false;
                
            } 
            trainAtStation = true;
            train.stopTimer += deltaTime;
            if (train.stopTimer >= train.stopDuration) {
                train.state = SpeedingUp;
            }
            break;

        case SpeedingUp:
            
            trainAtStation = false;
            PlayPositionalSound(SoundManager::getInstance().GetSound("TrainLeaving"), train.position, player.position, 700);
            train.speed += train.acceleration * deltaTime;
            if (train.speed >= train.maxSpeed) {
                train.speed = train.maxSpeed;
                train.state = MovingFromStation;
            }
            train.position.x -= train.speed * deltaTime;
            break;

        case MovingFromStation:
            if (player.enter_train) transitionState = FADE_OUT; //leaving station with player onboard,
            train.position.x -= train.speed * deltaTime;
            if (train.position.x <= 0.0f) {
                train.position.x = 0.0f; // Ensure train stops exactly at x = 0
                train.speed = 0.0f;      // Stop the train
                train.state = WaitingBeforeLoop;
                train.postLoopWaitTimer = 0.0f;
            }
            break;

        case WaitingBeforeLoop:
            if (player.enter_train){
                train.position.x = 5500.0f;
                train.state = MovingToStation;
                train.stopTimer = 0.0f;
                train.postLoopWaitTimer = 0.0f;
                train.speed = train.maxSpeed;
                break;

            }


            train.postLoopWaitTimer += deltaTime;
            if (train.postLoopWaitTimer >= train.postLoopWaitDuration) {
                // Reset train to starting position
                train.position.x = 5500.0f; // Starting position
                train.speed = train.maxSpeed;
                train.state = MovingToStation;
                train.stopTimer = 0.0f;
                train.postLoopWaitTimer = 0.0f;

                // Recalculate stopping distance
                float stoppingDistance = (train.speed * train.speed) / (2.0f * train.deceleration);
                train.slowDownStartX = train.stopPosition + stoppingDistance;
            }
            break;
    }


    if (player.enter_train){
        player.position.x = train.position.x + 480;

    }

    // Optional: Debug output
    // printf("State: %d, Position: %f, Speed: %f\n", train.state, train.position.x, train.speed);
}

void Flocking(Player& player, std::vector<NPC>& npcs) {
    Vector2 separationForce = {0.0f, 0.0f};

    for (size_t i = 0; i < npcs.size(); i++) {
        NPC& npcA = npcs[i];

        // Update and render the current NPC
        //npcA.Update(player, gameState);
        //npcA.Render(shaders);

        // Check if NPC is active
        if (npcA.health > 0) npcA.isActive = true;

        

        // Check distances to all other NPCs in the same vector
        for (size_t j = 0; j < npcs.size(); j++) {
            if (j == i) continue; // Skip self-comparison

            NPC& npcB = npcs[j];
            if (npcA.isActive && npcB.isActive) { // Only consider active NPCs
                float dx = npcA.position.x - npcB.position.x;
                float dy = npcA.position.y - npcB.position.y;
                float distance = sqrt(dx * dx + dy * dy);

                if (distance < 30.0f && distance > 0.0f) {
                    // Compute repulsion force
                    float force = 1.0f - (distance / 30.0f); 
                    float nx = dx / distance;
                    float ny = dy / distance;

                    // Add to separationForce
                    separationForce.x += nx * force;
                    separationForce.y += ny * force;
                }
            }
        }

        // Apply separation force to the current NPC
        float separationStrength = 50.0f;
        npcA.position.x += separationForce.x * separationStrength * GetFrameTime();
        npcA.position.y += separationForce.y * separationStrength * GetFrameTime();

        // Reset separationForce for the next NPC
        separationForce = {0.0f, 0.0f};
    }
}

void UpdateNPCActivity(GameState previousState, GameState newState) {
    //Activate/DeActivate NPCs depending on the game state. 
    // Map game states to multiple NPC groups
    std::map<GameState, std::vector<std::vector<NPC>*>> npcGroups = { //key = gameState, val = vector of vectors 
        { NECROTECH, { &robots } },
        { LOBBY, { &lobbyRobots, &lobbyNPCs, &lobbyMibs, &zombies } },  // Multiple NPC groups in LOBBY
        { ASTRAL, { &astralBats, &astralGhosts } },    
        { OUTSIDE, { &npcs, &mibs } }, //sigular mib outside
        { SUBWAY, { &npcs } }, //same NPCs as outside, so when going from outside to subway they are switched off then back on. 
        { CEMETERY, { &zombies } }, //zombies in the cemetery, graveyard, and park are in the same vector, because they aren't created until they spawn in. 
        { GRAVEYARD, { &zombies, &ghosts } },//we switch them all off when not in one of those 3 scenes. This means zombies will be retained for those scenes.
        //so if you spawn zombies in the park(and dont kill them all), they will also be in the graveyard and cemetery. 
        { PARK, { &ParkNpcs, &zombies }},
        { OFFICE, {&officeWorkers, &zombies}},

    };

    // Deactivate NPCs from previous scene
    if (npcGroups.count(previousState)) {
        for (std::vector<NPC>* group : npcGroups[previousState]) {
            for (NPC& npc : *group) {
                npc.isActive = false;
            }
        }
    }

    // Activate NPCs in the new scene
    if (npcGroups.count(newState)) {
        for (std::vector<NPC>* group : npcGroups[newState]) {
            for (NPC& npc : *group) {
                if (npc.health > 0) {
                    npc.isActive = true;
                }
            }
        }
    }
}




void DrawMac10Pickup(GameResources& resources, Player& player, Vector2 mousePosition, Camera2D& camera){
    //Mac10 pickup in asteral plane
    Vector2 macPos = {2445, -735}; // 
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);
    float distance_to_mac = abs(macPos.x - player.position.x);
    float distance_to_macY = abs(macPos.y - player.position.y);
    if (drawMac10){ //mac10 pickup
        DrawTexture(resources.Mac10pickup, macPos.x, macPos.y, WHITE);
        Rectangle macBounds = { //shovel button
            macPos.x,      
            macPos.y,     
            static_cast<float>(64),  
            static_cast<float>(64)  
        };
        //pickup mac10
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && distance_to_mac < 20 && distance_to_macY < 20){ //check for Y distance as well because its on platform
            if (CheckCollisionPointRec(mouseWorldPos, macBounds)){
                //add shovel in inventory
                if (!player.hasMac10){
                    drawMac10 = false;
                    AddItemToInventory("mac10", inventory, INVENTORY_SIZE);
                    PlaySound(SoundManager::getInstance().GetSound("reload"));
                    showInventory = true;
                    player.hasMac10 = true;
                }
            }
        }
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
            if (!player.hasMac10 && distance_to_mac < 20 && distance_to_macY < 20){//check for Y distance as well because its on a platform
                drawMac10 = false;
                AddItemToInventory("mac10", inventory, INVENTORY_SIZE);
                PlaySound(SoundManager::getInstance().GetSound("reload"));
                showInventory = true;
                player.hasMac10= true;
            
            }
        }

    }
    
}

void DrawShovelPickup(GameResources& resources, Player& player, Vector2 mousePosition, Camera2D& camera){
    //render shovel. Click or keyUP the shovel to pick it up. 

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
}

void HandleLobbyTransition(Player& player, GameCalendar& calendar){
    if (over_exit && player.currentHealth > 0){
        gameState = NECROTECH;
        over_exit = false;
        player.position.x = 2138;
        UpdateNPCActivity(LOBBY, NECROTECH);//turn off NPCs in the scene you are leaving, turn on NPCs in the scene you are entering. 
    }else if (player.onElevator){
        gameState = OFFICE;
        UpdateNPCActivity(LOBBY, OFFICE); //turn on office workers
        player.onElevator = false;
        if (!visitedOffice){
            can_spawn_zombies = true; //queue up more zombies to be spawned in the office.
            visitedOffice = true;
        } else{
            can_spawn_zombies = false; //already visited office so don't spawn anymore zombies. 
        }
        

    }else{
        //death in lobby, goto apartment
        gameState = APARTMENT;
        UpdateNPCActivity(LOBBY, APARTMENT);
        player.position.x = apartmentX;
        player.isDead = false;
        player.currentHealth = player.maxHealth;

        calendar.AdvanceDay();

    }
}

void HandleNecroTransition(Player& player, PlayerCar& player_car, GameCalendar calendar){
    //faded out
    if (over_necro and passwordValidated && !player.isDead){
        gameState = LOBBY; //over enterance goto lobby
        UpdateNPCActivity(NECROTECH,LOBBY); //turn off NPCs in the scene you are leaving, turn on NPCs in the scene you are entering. 

    }else if (player.isDead){
        gameState = APARTMENT;
        player.position.x = apartmentX;
        player.isDead = false;
        player.currentHealth = player.maxHealth;
        calendar.AdvanceDay();
        UpdateNPCActivity(NECROTECH,APARTMENT);


    } else{ //leave by car back to street. 
        gameState = OUTSIDE;
        player_car.position.x = 1710;
        player.position.x = player_car.position.x; //center of car
        gotoNecro = false;
        UpdateNPCActivity(NECROTECH,OUTSIDE);

    }

 
}



void HandleOutsideTransition(Player& player, PlayerCar& player_car, std::vector<NPC>& npcs, GameCalendar calendar) {
    if (move_car && !gotoWork && !gotoPark && !gotoNecro) {  // Car is moving, go to road
        gameState = ROAD;
        UpdateNPCActivity(OUTSIDE, ROAD);
        player_car.facingLeft = true;  // Leaving outside = face left
        if (!reverse_road) {
            player_car.position.x = 900;
        }
    } else if (move_car && gotoWork) {  // Move car and go to work
        gameState = WORK;
        UpdateNPCActivity(OUTSIDE, WORK);
        // Additional logic if needed
    }else if (move_car && gotoPark && !gotoWork){ //move car and go to park
        gameState = PARK;
        UpdateNPCActivity(OUTSIDE, PARK);
        player_car.position.x = 1800;
        player.position.x = player_car.position.x;
        carToPark = true; //true?
        move_car = false;

    }else if (gotoNecro && move_car){
        gameState = NECROTECH;
        move_car = false;
        player_car.position.x = 1623;
        player.position.x = player_car.position.x;
        UpdateNPCActivity(OUTSIDE, NECROTECH);
        
        //gotoNecro = false;

    } else if (player.isDead) {  // Died outside, go to apartment
        gameState = APARTMENT;
        UpdateNPCActivity(OUTSIDE, APARTMENT);
        player.position.x = apartmentX;
        player.currentHealth = player.maxHealth;

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
        UpdateNPCActivity(OUTSIDE, APARTMENT);
    } else if (over_lot) { // over_lot go to Vacant Lot
        UpdateNPCActivity(OUTSIDE, LOT);
        gameState = LOT;
        
    }else if (openMagicDoor){ //over magic door, go to astral
        UpdateNPCActivity(OUTSIDE, ASTRAL);
        gameState = ASTRAL;
        openMagicDoor = false; //we set it back to false here because it doesn't work any other way. 
    }else if (overSubway){
        UpdateNPCActivity(OUTSIDE, SUBWAY);
        gameState = SUBWAY;
        player.position.x = 3100;
        
    }
}

void HandleApartmentTransition(Player& player) {
    gameState = OUTSIDE;  // Go back outside
    UpdateNPCActivity(APARTMENT, OUTSIDE);
}

void HandleRoadTransition(Player& player, PlayerCar& player_car) {
    if (!reverse_road) {
        gameState = CEMETERY;
        player_car.position.x = 3000;
        UpdateNPCActivity(ROAD, CEMETERY);
    } else {
        gameState = OUTSIDE;
        UpdateNPCActivity(ROAD, OUTSIDE);
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
        UpdateNPCActivity(CEMETERY, ROAD);
    } else if (!player.enter_car && over_gate) {
        UpdateNPCActivity(CEMETERY, GRAVEYARD);
        gameState = GRAVEYARD;
        raiseZombies = true;  // Queue up more zombies for graveyard
    } else if (player.isDead) {
        UpdateNPCActivity(CEMETERY, APARTMENT);
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
        UpdateNPCActivity(GRAVEYARD, APARTMENT);
        player.currentHealth = player.maxHealth;
        calendar.AdvanceDay();

    }else{ //presumably over gate and fading out
        gameState = CEMETERY;
        UpdateNPCActivity(GRAVEYARD, CEMETERY);
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
    UpdateNPCActivity(WORK, OUTSIDE);
}

void HandleLotTransition(Player& player) {
    gameState = OUTSIDE;
    player.position.x = vacantLotX;
    UpdateNPCActivity(LOT, OUTSIDE);
}

void HandleAstralTransition(Player& player, GameCalendar& calendar){
    if (player.isDead){ //player dies on the astral plane, reset back to apartment.
        gameState = APARTMENT;//wake up back at your apartment with full health.
        player.position = Vector2 {apartmentX, 700}; // consider the Y
        player.position.y = 700; //incase player dies on a platform. reset to ground level
        player.isDead = false;
        player.gravity = 800; //reset gravity to normal. 
        player.outline = false; //set outline off when exiting astral
        applyShader = false; //drugs ware off if you advanced the day
        player.currentHealth = player.maxHealth;
        UpdateNPCActivity(ASTRAL, APARTMENT);

        calendar.AdvanceDay();
        for (NPC& ghost : astralGhosts){
            ghost.agro = false; //ghost lose agro after dying. 

        }
    }else{ //call fade out in astral, presumably magic door exit
        gameState = OUTSIDE;
        UpdateNPCActivity(ASTRAL, OUTSIDE);
        openMagicDoor = false; //We set it back to false when entering astral, we should set it false when leaving astral aswell
        player.gravity = 800; //reset gravity on leaving astral plane.
        player.outline = false; //set outline off when exiting astral
        applyShader = false; //drugs ware off when exiting astral.
        player.position = Vector2 {apartmentX, 700.0f}; //move back to ground level.  
        for (NPC& ghost : astralGhosts){
            ghost.agro = false; //ghost lose agro after leaving the plane. regain agro when inside detection radius
        }
    }

}

void HandleOfficeTransition(Player& player, GameCalendar calender){
    if (player.onElevator){
        gameState = LOBBY;
        UpdateNPCActivity(OFFICE, LOBBY);
        player.onElevator = false;
        can_spawn_zombies = false; //only spawn zombies once. 
    }else if (player.isDead){
        //death in office return to apartment
        gameState = APARTMENT;
        UpdateNPCActivity(OFFICE, APARTMENT);
        player.position.x = apartmentX;
        player.onElevator = false;

    }
}

void HandleParkTransition(GameState& gamestate, Player& player, PlayerCar player_car){
    if (player.isDead){ //player dies in park, reset to apartment.
        gameState = APARTMENT;
        player.position.x = apartmentX;
        player.isDead = false;
        player.currentHealth = player.maxHealth;
        applyShader = false; //if you die, you are no longer high when respawning
        UpdateNPCActivity(PARK, APARTMENT);

    }else if (overSubway){ //exit to subway
        gameState = SUBWAY;
        player.position.x = 3011;
        gotoStreet = true;
        // gotoPark = false; //turn off elsewhere incase play changes there mind and goes back to park from subway
        UpdateNPCActivity(PARK, SUBWAY);
       

    } else{ //call fade out in park, leaving by car to outside. 
        gameState = OUTSIDE; //call fadeout in park
        player.position.x = player_car.position.x-64; //center of car
        gotoPark = false; //reset gotopark
        carToPark = false; //take the car back from the park and render it outside. 
        UpdateNPCActivity(PARK, OUTSIDE);

    }


}

void HandleSubwayTransition(GameState& gameState, Player& player){
    //the car magically teleports back to the street if you take the car to the park and take the subway back. 

    if (subwayExit && !subwayToPark && !gotoPark){ //your at outside subway so exit to outside
        gameState = OUTSIDE;
        player.position.x = 4579;
        UpdateNPCActivity(SUBWAY, OUTSIDE);
        gotoPark = false;
    }

    if (subwayExit && (subwayToPark || gotoPark)){ //your at the parksubway so exit to park, either took the train or drove. 
        gameState = PARK;
        UpdateNPCActivity(SUBWAY, PARK);
    }

    if (player.enter_train && !subwayToPark && !carToPark){ //Riding train to park
        player.enter_train = false;
        subwayToPark = true; //travel to park from subway, 
        gameState = PARK;
        player.position.x = 3000;
        UpdateNPCActivity(SUBWAY, PARK);

    }else if (player.enter_train && subwayToPark){ //Riding train to outside
        player.enter_train = false;
        subwayToPark = false;
        gameState = OUTSIDE;
        gotoPark = false;
        gotoStreet = false;
        player.position.x = 4500;
        UpdateNPCActivity(SUBWAY, OUTSIDE);

    }else if (player.enter_train && carToPark){ //riding train to outside
        player.enter_train = false;
        carToPark = false; //car magically teleports back to to the street following the player, simplifying things drastically
        gameState = OUTSIDE;
        UpdateNPCActivity(SUBWAY, OUTSIDE);
        gotoStreet = false;
        player.position.x = 4500;
    }
}

void PerformStateTransition(Player& player, PlayerCar& player_car, GameCalendar& calendar, std::vector<NPC>& npcs) {
    //if we are fading out, we are transitioning, switch to the next area depending on the gameState. 
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

        case SUBWAY:
            HandleSubwayTransition(gameState, player);
            break;

        case NECROTECH:
            HandleNecroTransition(player, player_car, calendar);
            break;

        case LOBBY:
            HandleLobbyTransition(player, calendar);
            break;

        case OFFICE:
            HandleOfficeTransition(player, calendar);
            break;
  
    }
}

void DrawFadeMask() {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, fadeAlpha)); //fade to black
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
    //if you want to tranision to a new scene, just say FADEOUT = TRUE
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
    //check if player is over dig spot, while clicking. Then add item to inventory
   if (player.position.x > 1860 && player.position.x < 1880 && !player.hasPills && gameState == CEMETERY){ //over dig spot
        player.hasPills = true; //if you dont have pill you can allways get more here. 
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

    if (player.position.x > 82.0 && player.position.x < 102 && gameState == OUTSIDE && !player.hasPills){
        PlaySound(SoundManager::getInstance().GetSound("ShovelDig")); //far left outside
        player.hasPills = true;
        AddItemToInventory("pills", inventory, INVENTORY_SIZE);
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


NPC* FindClosestNPC(NPC& zombie, std::vector<NPC>& npcs) {
    //find closest npc to zombie
    NPC* closestNPC = nullptr;
    float minDist = 1000.0f; // Large initial distance

    for (NPC& npc : npcs) {
        if (npc.isActive && zombie.isActive) { //make sure the zombie is also active
            float dist = fabs(zombie.position.x - npc.position.x);

            if (dist < minDist) {
                minDist = dist;
                closestNPC = &npc;
            }
        }
    }
    return closestNPC;
}

void UpdateZombieTarget(NPC& zombie, std::vector<NPC>& npcs) {
    zombie.targetNPC = FindClosestNPC(zombie, npcs);

    if (zombie.targetNPC != nullptr) {
        zombie.hasTarget = true; //dont go idle
        zombie.destination = { zombie.targetNPC->position.x, zombie.position.y }; //chase NPC

        // Make the NPC run away

        if (zombie.targetNPC->targetedTimer <= 0){ //if the NPC isn't targeted, 
            zombie.targetNPC->targetedTimer = 2.0f;
            //change npc direction if neccesary, only every 2 seconds to prevent flip flop
            zombie.targetNPC->zRight = zombie.targetNPC->position.x < zombie.position.x; 
            
            zombie.targetNPC->isTargeted = true;
            
        }

    } else {
        zombie.hasTarget = false;
    }
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
    Color macTint = WHITE;

    int startX = (inventoryPositionX - (slotWidth * inventorySize/2));
    int startY = inventoryPositionY;

    // Draw each inventory slot 
    for (int i = 0; i < inventorySize; i++) {
        int x = startX + (i * (slotWidth + 10));  // Offset each slot horizontally
        int y = startY;

        // Draw the inventory slot texture
        DrawTexture(resources.inventorySlot, x, y, WHITE);
        Color customTint = {255, 50, 50, 255}; // light red
        if (player.currentWeapon == SHOTGUN) shotgunTint = customTint;
        if (player.currentWeapon == REVOLVER) gunTint = customTint;
        if (player.currentWeapon == MAC10) macTint = customTint;

       // Draw the icon at x, y
        if (!inventory[i].empty()) { //inventory buttons are all done in the same for loop we use to draw it. Consider abstracting this somehow. 
        //chatGPT suggests using enum ItemType and struct inventoryDefinitions, just makes it more spread out and complicated.

            if (inventory[i] == "carKeys"){
                DrawTexture(resources.CarKeys, x, y, WHITE);
                
            }
            if (inventory[i] == "Badge"){
                DrawTexture(resources.Badge, x, y, WHITE);
            }

            if (inventory[i] == "cemeteryKey"){
                DrawTexture(resources.cemeteryKey, x, y, WHITE);
            }

            if (inventory[i] == "Gun"){ //click on the gun icon to switch weapons
                DrawTexture(resources.Revolver, x, y, gunTint);
                Rectangle RevolverBounds = { 
                    static_cast<float>(x),      
                    static_cast<float>(y),      
                    static_cast<float>(64),  
                    static_cast<float>(64)  
                };

                if (CheckCollisionPointRec(mousePosition, RevolverBounds)){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        if (player.currentWeapon != REVOLVER){
                            player.currentWeapon = REVOLVER;
                        }
                    }

                }
            }
            if (inventory[i] == "shotgun"){
                DrawTexture(resources.shotgunIcon, x, y, shotgunTint);
                Rectangle ShotGunBounds = { 
                    static_cast<float>(x),      
                    static_cast<float>(y),      
                    static_cast<float>(64),  
                    static_cast<float>(64)  
                };

                if (CheckCollisionPointRec(mousePosition, ShotGunBounds)){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        if (player.currentWeapon != SHOTGUN){
                            player.currentWeapon = SHOTGUN;
                        }
                    }

                }

            }

            if (inventory[i] == "mac10"){
                DrawTexture(resources.Mac10, x, y, macTint);
                Rectangle MacBounds = { 
                    static_cast<float>(x),      
                    static_cast<float>(y),      
                    static_cast<float>(64),  
                    static_cast<float>(64)  
                };

                if (CheckCollisionPointRec(mousePosition, MacBounds)){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        if (player.currentWeapon != MAC10){
                            player.currentWeapon = MAC10;
                        }
                    }

                }
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
                            inventory[i] = std::string("");  // erase whiskey from the string
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
                        if (player.currentHealth < player.maxHealth && player.hasPills){
                            inventory[i] = std::string("");  // erase pills from the string
                            player.currentHealth = player.maxHealth;
                            player.hasPills = false;
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
                        Dig(player); //click shovel icon to dig
                     
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

void CheckBulletPlayerCollisions(Player& player) {
    Vector2 bulletSize = {5, 2};
    for (int i = 0; i < MAX_BULLETS; i++){
        if (bullets[i].isActive && bullets[i].laser){ //only lasers hurt player
            if (player.CheckHit(bullets[i].previousPosition, bullets[i].position, bulletSize)){
                player.take_damage(bullets[i].damage);
                bullets[i].isActive = false; //desteroy the bullet on hit
            }


        }
    }
}

void CheckLaserNPCCollisions(std::vector<NPC>& npcs, Player& player){
    Vector2 laserSize = {5, 2};
    int laserDamage = 50; //lasers do more damage to NPCs

    for (int i = 0; i < MAX_BULLETS; i++){//check for laser non robot NPC collision
        if (bullets[i].isActive && bullets[i].laser){ 
            for (NPC& npc : npcs){
                if (npc.isActive && !npc.robot && npc.CheckHit(bullets[i].previousPosition, bullets[i].position, laserSize)) {
                    bullets[i].isActive = false;
                    npc.TakeDamage(laserDamage, player);
                    break;
                }
            }

        }
    }
}

void CheckBulletNPCCollisions(std::vector<NPC>& npcs, Player& player) { //Bullet collision with zombies, bats, and ghosts
    Vector2 bulletSize = {1, 1};  // Size of the bullet hitbox

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive && !bullets[i].laser) {  // Only check active bullets and not lasers
            for (NPC& npc : npcs) { //zombies vector is passed to this func which calls them npcs
                if (npc.isActive && npc.CheckHit(bullets[i].previousPosition, bullets[i].position, bulletSize)) { //
                    // Collision detected
                    bullets[i].isActive = false;  // Deactivate the bullet
                    npc.TakeDamage(bullets[i].damage, player);  // Bullets can do more or less damage, use the bullet's damage, it's set when firing
                    
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
    }
    else if (player.currentWeapon == SHOTGUN && player.hasShotgun){
        DrawText(TextFormat("Ammo: %d", player.shotgunBulletCount), screenWidth/2 + ammoX, ammoY, 20, WHITE);
        DrawText(TextFormat("SHELLS: %d", player.shells), screenWidth/2 + ammoX, ammoY+20, 20, WHITE);
    }
    else if (player.currentWeapon == MAC10 && player.hasMac10){
        DrawText(TextFormat("Ammo: %d", player.mac10BulletCount), screenWidth/2 + ammoX, ammoY, 20, WHITE); 
        DrawText(TextFormat("9mm: %d", player.autoAmmo), screenWidth/2 + ammoX, ammoY+20, 20, WHITE);
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
    //laptop computer interface
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

void DrawSubwayUI(Player& player, Vector2 mousePosition, Camera2D& camera, GameState& gameState){
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);
    Vector2 ui_pos = {3011, 600};
    int ui_width = 116;
    int ui_height = 64;
    int fontSize = 16;
    //DrawRectangle(player_car.position.x, player_car.position.y, 200, 200, WHITE);
    DrawRectangle(ui_pos.x, ui_pos.y, ui_width, ui_height, Fade(BLACK, .6));
    Color parkTint = WHITE;


    Rectangle parkBounds = { //cemetery / street
        ui_pos.x,    
        ui_pos.y,      
        static_cast<float>(96),  
        static_cast<float>(16)  
    };

    if (CheckCollisionPointRec(mouseWorldPos, parkBounds)){ //middle //cemetery/street
        parkTint = RED;
        buttonPark = true;
    }else{
        buttonPark = false;
    }

    if (gotoStreet){
        DrawText("   Street", ui_pos.x, ui_pos.y, fontSize, parkTint);

    }else{
        DrawText("   Park", ui_pos.x, ui_pos.y, fontSize, parkTint);
    }




    // if (subwayToPark || carToPark){
    //     DrawText("   Street", ui_pos.x, ui_pos.y, fontSize, parkTint);
    // }else{
    //     DrawText("   Park", ui_pos.x, ui_pos.y, fontSize, parkTint);
    // }

}


//Destinations Menu for car. Click on where you want to travel. 
void DrawCarUI(PlayerCar& player_car, Vector2 mousePosition, Camera2D& camera, GameState& gameState){
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);
    Vector2 ui_pos = player_car.position;
    int ui_width = 116;
    int ui_height = 64;

    //DrawRectangle(player_car.position.x, player_car.position.y, 200, 200, WHITE);
    DrawRectangle(ui_pos.x, ui_pos.y - 20, ui_width, ui_height, Fade(BLACK, .60));
    Color work_tint = WHITE;
    Color cemetery_tint = WHITE;
    Color tavern_tint = WHITE;
    Color necro_tint = WHITE;

    Rectangle textureBounds = { //cemetery / street
        player_car.position.x,      
        player_car.position.y,      
        static_cast<float>(96),  
        static_cast<float>(16)  
    };

    Rectangle workBounds = { //work
        player_car.position.x,      
        player_car.position.y+16,      
        static_cast<float>(96),  
        static_cast<float>(16)  
    };

    Rectangle ParkBounds = { //Park
        player_car.position.x,      
        player_car.position.y-16,      
        static_cast<float>(96),  
        static_cast<float>(16)  
    };

    Rectangle NecroBounds = { //Park
        player_car.position.x,      
        player_car.position.y+32,      
        static_cast<float>(96),  
        static_cast<float>(16)  
    };

    if (CheckCollisionPointRec(mouseWorldPos, textureBounds)){ //middle //cemetery/street
        cemetery_tint = RED;
        buttonCemetery = true;
    }else{
        buttonCemetery = false;
    }

    if (CheckCollisionPointRec(mouseWorldPos, workBounds) && !hasWorked && gameState == OUTSIDE){ //bottom Work
        work_tint = RED;
        buttonWork = true;
    }else{
        buttonWork = false;
    }

    if (CheckCollisionPointRec(mouseWorldPos, ParkBounds)){ //top Park
        tavern_tint = RED;
        buttonPark = true;  
    }else{
        buttonPark = false;
    }

    if (CheckCollisionPointRec(mouseWorldPos, NecroBounds)){ //very bottom NecroTech
        necro_tint = RED;
        buttonNecro = true;  
    }else{
        buttonNecro = false;
    }


    if (gameState == OUTSIDE){
        DrawText("   Park", ui_pos.x, ui_pos.y-17, 16, tavern_tint);
        DrawText("   Cemetery", ui_pos.x, ui_pos.y, 16, cemetery_tint);

        work_tint = hasWorked ? BLACK : work_tint; //turn off work option if you have recently worked. Render button black. 
        DrawText("   Work", ui_pos.x, ui_pos.y+17, 16, work_tint);

        if (NecroTech) DrawText("  NecroTech", ui_pos.x, ui_pos.y+32, 16, necro_tint); //TODO: implement final level. I've been putting it off because
        //i don't like it. Then change it. 


        

    }else if (gameState == CEMETERY){
        
        DrawText("   Street", ui_pos.x, ui_pos.y, 16, cemetery_tint);
       //DrawText("Work", ui_pos.x, ui_pos.y+17, 16, work_tint);

    }else if (gameState == PARK){
        DrawText("    Street", ui_pos.x, ui_pos.y, 16, cemetery_tint);
        
    }else if (gameState == NECROTECH){
        DrawText("    Street", ui_pos.x, ui_pos.y, 16, cemetery_tint);
    }

}

void DrawMagicDoor(GameResources& resources,Player& player, MagicDoor& magicDoor, ShaderResources& shaders){
        float doorFrame = 64.0;
        Rectangle sourceDoorRec = {static_cast<float>(magicDoor.currentFrame) * doorFrame, 0, static_cast<float>(doorFrame), static_cast<float>(doorFrame)};
        //BeginShaderMode(shaders.rainbowOutlineShader);
        DrawTextureRec(resources.magicDoorSheet, sourceDoorRec, magicDoor.position, WHITE);
        //EndShaderMode();
         
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

void moveUFO(UFO& ufo, Player& player){
    if (canMoveUfo){
        //UFO drops down from the sky, hovers a few seconds, then darts off super fast.
        float deltaTime = GetFrameTime();
        int moveSpeed = 100;
        int stopPos = 400;

        
        if (ufo.basePosition.y < stopPos && move_ufo && ufoTimer > 0){ //go from starting position to 400 y and wait for timer
            ufo.basePosition.y += moveSpeed * deltaTime;
            ufo.basePosition.x = player.position.x-32;
        
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
    
    BeginShaderMode(shaders.glitchShader); //TODO find a good shader for UFO
    DrawTextureRec(resources.UFOsheet, sourceRect, UFODrawPosition, WHITE); 
    EndShaderMode();
    
}

void DrawEarth(GameResources& resources, Earth& earth, Camera2D& camera){
    // Draw rotating pixel earth floating in the astral sky, accounting for parallax
    float deltaTime = GetFrameTime();
    earth.frameTimer += deltaTime;

    while (earth.frameTimer >= earth.frameTime) //while loop handles cases where deltaTime > frameTime
    {
        earth.frameTimer -= earth.frameTime; //subtracting frameTime preserves the excess time for smoothing animations apparently
        earth.currentFrame++;

        if (earth.currentFrame >= earth.totalFrames)
        {
            earth.currentFrame = 0;
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
    
    int offset = -63; //default offsets for regular NPCs
    int screen_offsetX = 16;
    int screen_offsetY = -55;

    if (fortuneTimer > 0){
        //nothing can interupt your fortune. 
;        fortuneTimer -= GetFrameTime();
    }
    Vector2 screen_pos = GetWorldToScreen2D(dboxPosition, camera); // position to draw text and rectangle at. position is set to npc position
    //different NPCs have different sized Dialog boxes. Adjust size and offsets before drawing. 
    Color tint = WHITE;
    if (gameState == OUTSIDE || gameState == SUBWAY){
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

    }
    int textHeight = 32;
    int padding = 20;
    int textWidth = MeasureText(phrase.c_str(), textSize); //find the length of the string in pixels
    if (phrase.find('\n') != std::string::npos) { //check for a \n character, if so, double the height of the box, there is never more than 2 lines
            textHeight = 64;
    }
    DrawRectangle(screen_pos.x+5, screen_pos.y+offset, textWidth + padding, textHeight, Fade(BLACK, 0.3f));
    DrawRectangle(screen_pos.x, screen_pos.y + offset, boxWidth, boxHeight, Fade(BLACK, 0.3f));
    DrawText(phrase.c_str(), screen_pos.x+ screen_offsetX, screen_pos.y + screen_offsetY, textSize, tint); //Draw Phrase
    
    //GUI buttons for certain NPC interactions. 
    if (money >= 100 && dealer && GuiButton((Rectangle){ screen_pos.x+16, screen_pos.y-64, 64,48 }, "BUY") ) //button pressed
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

    if (teller && !buyFortune && money >= 100 &&  GuiButton((Rectangle){ screen_pos.x+16, screen_pos.y-64, 64,48 }, "BUY") ){

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

void EnterCar(GameResources& resources, Player& player, PlayerCar& player_car){
        //render headlight/breaklight and show carUI
        
    Vector2 breakLight_pos = {player_car.position.x + 88, player_car.position.y + 53};
    Vector2 light_pos = {player_car.position.x - 225, player_car.position.y + 32};
    BeginBlendMode(BLEND_ADDITIVE);
    DrawTextureV(resources.breakLight, breakLight_pos, WHITE);
    DrawTextureV(resources.lightBeam, light_pos, WHITE);
    EndBlendMode();
    show_carUI = true;    

    
}

void playerOutsideInteraction(Player& player, PlayerCar& player_car){
    //on main street there are lots of different interactable things. Handle them here. 
    int ap_min = 2246;//over apartment
    int ap_max = 2266;
    int pc_min = 1728; // over player_car
    int pc_max = 1748;
    int road_min = 1340; //exiting outside via road

    int dist = abs(player.position.x - ap_max);

    if (dist > 1000){ //get far enough away from the apartment and you can sleep again. 
        hasSlept = false;
    }



    int lot_min = vacantLotX - 20;
    int lot_max = vacantLotX + 20;

    if (player_car.position.x < road_min && move_car){
        transitionState = FADE_OUT;
        
        //player_car.position = Vector2 {900, 700 - 32};

    }



    if (!start) show_dbox = false; // reset to false so it can fall through unless start where we first show tutorial text
    over_apartment = false;
    over_lot = false;
    over_car = false;
    overLiquor = false;
    overSubway = false;

    

    //consider abstracting this into a seperate function. is_interacting, return true if any of these checks 
    if (player.position.x > pc_min && player.position.x < pc_max && has_car_key){ //over_car with keys
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
        if (!showLiquor && fortuneTimer <=0){
            phrase = "Up to Enter";
        }
        //dont set phrase here, because it will override showing whiskey button. 
        dboxPosition = player.position;
        show_dbox = true;
    }

    
    if (player.position.x < 64 && !move_ufo && gameState == OUTSIDE){
        move_ufo = true;
        ufoTimer = 10; //it takes 10 seconds for the UFO to move into position and hover before shooting off. 
        std::cout << "Moving UFO";

    }

    if (player.position.x > 4579 && player.position.x < 4599){
        overSubway = true;
        if (!showLiquor && fortuneTimer <=0){
            phrase = "PRESS UP TO ENTER SUBWAY";
        }
        dboxPosition = player.position;
        show_dbox = true;
    }

}



void RenderSubway(GameResources& resources, Player& player, Camera2D& camera, Vector2& mousePosition,Train& train, ShaderResources& shaders){
    SoundManager::getInstance().UpdatePositionalSounds(player.position);//call this wherever zombies spawn to update positional audio

    show_dbox = false;

    
    float parallaxBackground = camera.target.x * 0.5f;  // Background moves even slower
    float parallaxMidground = camera.target.x * 0.25f;  // benches and poles
    camera.target.x = player.position.x;
    if (!SoundManager::getInstance().IsMusicPlaying("subwayAmbience")){
        SoundManager::getInstance().PlayMusic("subwayAmbience");
    }
  

    BeginMode2D(camera);  // Begin 2D mode with the camera
    ClearBackground(customBackgroundColor);

    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);

    HandleKeyboardAiming(player, mouseWorldPos);


    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }


    BeginMode2D(camera);
    
     // Draw the background (sky)
    DrawTexturePro(resources.subwayBackground, {0, 0, static_cast<float>(resources.subwayBackground.width), static_cast<float>(resources.subwayBackground.height)},
                    {parallaxBackground, 0, static_cast<float>(resources.subwayBackground.width), static_cast<float>(resources.subwayBackground.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.subwayMidground, {0, 0, static_cast<float>(resources.subwayMidground.width), static_cast<float>(resources.subwayMidground.height)},
                    {parallaxMidground, 0, static_cast<float>(resources.subwayMidground.width), static_cast<float>(resources.subwayMidground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),   
    DrawTexturePro(resources.subwayForeground, {0, 0, static_cast<float>(resources.subwayForeground.width), static_cast<float>(resources.subwayForeground.height)},
                    {1024, 0, static_cast<float>(resources.subwayForeground.width), static_cast<float>(resources.subwayForeground.height)}, {0, 0}, 0.0f, WHITE);
    
    player.DrawPlayer(resources, gameState, camera, shaders); //draw player in front of background and behind train

    for (NPC& npc : npcs){
        npc.Update(player, gameState);
        npc.Render(shaders);
        npc.ClickNPC(mousePosition, camera, player, gameState);

        if (npc.interacting){ //Take the first one you find. only one npc should be able to interact. If you click on multiple NPCs really fast
        //the dialog box jumps around depending on the timer. Need a way to cancel all interaction except the last one. 
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
            teller = false;
        
        }
        
    }


    float deltaTime = GetFrameTime();
    UpdateTrain(train, player, deltaTime);
    DrawTexture(resources.train, train.position.x, train.position.y-27, WHITE); //draw train in front of NPCs and player



    if (player.position.x > 3001 && player.position.x < 3021 && trainAtStation){
        DrawSubwayUI(player, mousePosition, camera, gameState); // inside draw for whatever reason
        train.stopTimer = 0;//hold the train
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (buttonPark && !player.enter_train){ //hovering button street or park
                //player.ontrain = true
                player.enter_train = true;
                player.position.x = train.position.x + 480;
                
                
            
            }
        }
    }
   

    EndMode2D();

    //draw healthbar 
    if (player.currentHealth < 100 &&  !player.enter_car){
        Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
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

    subwayExit = false;
    if ((player.position.x > 3700 && player.position.x < 3720 || player.position.x > 1900 && player.position.x < 1920)&& gameState == SUBWAY){ //far right or far left of subway, both have exit

        phrase = "Up TO EXIT SUBWAY";
        show_dbox = true;
        dboxPosition = player.position;
        subwayExit = true;
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
            transitionState = FADE_OUT;
            
        }
    }

    if (show_dbox){
        DrawDialogBox(player, camera, 0, 0, 20);
    }



}




void RenderAstral(GameResources& resources, Player& player, Camera2D& camera, Vector2& mousePosition,Earth& earth,MagicDoor& magicDoor, MagicDoor& magicdoor2, ShaderResources& shaders){
    player.gravity = 200;
    player.outline = true;//turn on outline shader in asteral plane


    magicDoor.position.x = 2089;
    camera.target = player.position;
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxClouds2 = camera.target.x * .7;
    float parallaxClouds = camera.target.x * .8;
    float parallaxBackground = camera.target.x * 0.9f;  // Background moves even slower 
    
    show_dbox = false;
    
    BeginMode2D(camera);
    
    ClearBackground(customBackgroundColor);

    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera); //put this after draw and it works now?
    HandleKeyboardAiming(player, worldMousePosition);


    if (drunk){
        BeginShaderMode(shaders.glowShader2);

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
    
    DrawMagicDoor(resources, player, magicDoor, shaders);
    DrawMagicDoor(resources, player, magicdoor2, shaders);

    player.DrawPlayer(resources, gameState, camera, shaders);


    DrawTexturePro(resources.AstralForeground, {0, 0, static_cast<float>(resources.AstralMidground.width), static_cast<float>(resources.AstralMidground.height)},
                    {0, 0, static_cast<float>(resources.AstralMidground.width), static_cast<float>(resources.AstralMidground.height)}, {0, 0}, 0.0f, WHITE);


        // Draw platforms
    for (Platform& platform : platforms) {
     
        //platform.Draw();
       
        platform.DrawPlatformTexture(resources.platformTexture, platform.rect);
        
    }


    //MOVE ENEMIES 
    for (NPC& ghost : astralGhosts){
        ghost.Update(player, gameState);
        ghost.Render(shaders);
        
        if (ghost.agro){
            Flocking(player, astralGhosts);
        }

        if (abs(ghost.position.y - player.position.y) < 50){
            if (!ghost.agro){
                ghost.agro = true;
            }
        }
    }

    for (NPC& bat : astralBats){
        bat.Update(player, gameState);
        bat.Render(shaders);
        
        if (bat.agro){
            Flocking(player,astralBats);
        }
    }
    


    DrawMac10Pickup(resources, player, mousePosition, camera);

    
    DrawBullets(); //draw bullets in cemetery after everything else. 
    
    
    EndMode2D();


    
    //draw healthbar 
    if (player.currentHealth < 100 &&  !player.enter_car){
        Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
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

    //UFO shows up in the begining at the far left outside, and once you have the cemetery key in the cemetery. 
    if (hasCemeteryKey) {
        //playe UFO hum when ufo is present. Use UFO.baseposition not position

        PlayPositionalSound(SoundManager::getInstance().GetSound("energyHum"), ufo.basePosition, player.position, 800.0f);
        
    }
    
    playOwl = false; //reset owl

    
    //dont spawn unless raise zombies is true. raise zombies is set to true by talking to the hobo, and finding the gun
    if (!player.enter_car && player.position.x < 1900 && !zombieWave3 && !firstHobo){ // walk to far left and zombies spawn again
        zombieWave3 = true;
        StartZombieSpawn(10);
        minDistToPlayer = 50;
        maxDistToPlayer = 200;
    }

    //too many zombie encounters not enough ammo, uncomment for more zombies on the right side of cemetery
    // if (!player.enter_car && player.position.x > 3500 && !zombieWave2 && !firstHobo){ //walk too far right and zombies spawn again
    //     zombieWave2 = true;
    //     StartZombieSpawn(10);

    //     minDistToPlayer = 50;
    //     maxDistToPlayer = 200;
    // }

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
            minDistToPlayer = 50;
            maxDistToPlayer = 200;
        }else{
            StartZombieSpawn(5);
            minDistToPlayer = 50;
            maxDistToPlayer = 200;
        }       
    }

    show_dbox = false;
    over_gate = false;
    over_car = false;
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
        phrase = "UP TO ENTER";
        show_dbox = true;
        dboxPosition = player.position;
        
   }

    BeginMode2D(camera);

    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera);
    HandleKeyboardAiming(player, worldMousePosition);
    
    // if (!IsKeyDown(KEY_F)){
    //     if (player.isAiming) player.facingRight = worldMousePosition.x > player.position.x;//Hack to make aiming work both ways
    // }
    
    
    ClearBackground(customBackgroundColor);
    if (!move_car && !player.enter_car){
        camera.target = player.position;
    }
    
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxTrees = camera.target.x * .8;
    float parallaxBackground = camera.target.x * 0.9f;  // Background moves even slower 

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

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
    if (player.enter_car) EnterCar(resources, player, player_car);

    abductionBeam = false;
    if (player.position.x > 3929 && player.position.x < 3949){
        abductionBeam = true;
    }

    if (hasCemeteryKey){ // dont show UFO until later in the game
        ufo.basePosition = {3900, 400};
        DrawUFO(resources, ufo, camera, time, shaders);
    }

    DrawShovelPickup(resources, player, mousePosition, camera);

    for (NPC& zombie : zombies){ //update and draw zombies in cemetery
        zombie.Update(player, gameState);
        zombie.Render(shaders);

    }

    if (show_carUI && !move_car && player.enter_car){ //destination menu //draw UI inside mode2d
        DrawCarUI(player_car, mousePosition, camera, gameState);
    }

    if (player.enter_car == false){// if enter car is false, dont render player or update position camera should stay focused on player pos. 
        player.DrawPlayer(resources, gameState, camera, shaders);

    }
    DrawBullets(); //draw bullets in cemetery after everything else. 

    EndMode2D();

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
    if (player.currentHealth < 100 &&  !player.enter_car){
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

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

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
            //light positions when not reversing
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
 
    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // render mouse cursor outside Mode2D
   
}

void RenderGraveyard(GameResources resources,Player& player,Camera2D& camera,Vector2 mousePosition, ShaderResources& shaders){
    


    if (player.position.x > 3437 and raiseZombies){
        raiseZombies = false;
        StartZombieSpawn(20);
        minDistToPlayer = 50;
        maxDistToPlayer = 200;
    }


    BeginMode2D(camera);
    camera.target = player.position;
    //Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera);

    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);

    HandleKeyboardAiming(player, mouseWorldPos);

    float parallaxforeground = camera.target.x * 0.4;
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxTrees = camera.target.x * 0.8;
    float parallaxBackground = camera.target.x * 0.9f;  // Background moves even slower 
    

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }

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
        //if (ghost.health > 0) ghost.isActive = true; <- this caused some major pains
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
    if (player.currentHealth < 100 &&  !player.enter_car){
        Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
        DrawHealthBar(resources,barPos, player.maxHealth, player.currentHealth, 128, 16);

    }
    
}




void RenderApartment(GameResources& resources, Player player, Vector2 mousePosition, GameCalendar& calendar, Camera2D camera, ShaderResources& shaders){
    player.position.x -= 20; //ensure over_apartment = false
    int screen_center = (screenWidth - resources.apartment.width)/2;

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }
    

    ClearBackground(ApartmentBgColor);

    DrawTexture(resources.apartment, screen_center, 0, WHITE);
    EndShaderMode(); ////////////////////////////SHADER OFF

    
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
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        transitionState = FADE_OUT;
        showInventory = false;
        PlaySound(SoundManager::getInstance().GetSound("mainDoor"));
        
    }

    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); //draw cursor last
    
}

void RenderLot(GameResources& resources, Player& player, Camera2D& camera, Vector2& mousePosition,ShaderResources& shaders){

    show_dbox = false; //turn off dbox if no one is interacting
    int digPos = 2600;
    if (player.position.x < 2782 && player.position.x > 2742){
        over_exit = true;
        phrase = "UP TO EXIT";
        dboxPosition = player.position;
        show_dbox = true;
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
    float parallaxMidground = camera.target.x * 0.6f;  // Midground moves slower
    float parallaxMidBuilding = camera.target.x * 0.4;
    float parallaxBackground = camera.target.x * 0.8f;  // Background moves even slower
    
    SoundManager::getInstance().UpdateMusic("StreetSounds"); //only update street sounds when oustide

    int cameraMinX = 2677;
    int cameraMaxX = 3048;
    
    if (player.position.x > 2677 && player.position.x < 3048){
        camera.target.x = player.position.x;

    }else{
        camera.target.x = Clamp(player.position.x, cameraMinX, cameraMaxX); //clamp camera to the center of the scene. 
    }
    

    BeginMode2D(camera);


    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera); //put this after draw and it works now?
    HandleKeyboardAiming(player, worldMousePosition);
    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }
    


     // Draw the background (sky)
    DrawTexturePro(resources.background, {0, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)},
                    {parallaxBackground, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)}, {0, 0}, 0.0f, WHITE);

    //Draw the midground (silhouettes)
    DrawTexturePro(resources.midgroundLot, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
                    {parallaxMidground, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);
            
    //mid grouind buildings 
    DrawTexturePro(resources.MidBuildings, {0, 0, static_cast<float>(resources.MidBuildings.width), static_cast<float>(resources.midground.height)},
                    {parallaxMidBuilding, 0, static_cast<float>(resources.MidBuildings.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),  offset by 1024 to center relative to midground. 
    DrawTexturePro(resources.vacantLot, {0, 0, static_cast<float>(resources.vacantLot.width), static_cast<float>(resources.vacantLot.height)},
                    {705+1024, 0, static_cast<float>(resources.vacantLot.width), static_cast<float>(resources.vacantLot.height)}, {0, 0}, 0.0f, WHITE);

    
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
    DrawBullets();
    
    EndMode2D();  // End 2D mode 
 
    

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
    SoundManager::getInstance().UpdatePositionalSounds(player.position);//call this wherever zombies spawn to update positional audio

    float parallaxBackground = camera.target.x * 0.9f;  // Background moves even slower
    float ParallaxBuildings = camera.target.x * 0.7;
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    over_car = false;
    if (player.position.x > player_car.position.x && player.position.x < player_car.position.x +30 && !subwayToPark){
        over_car = true;
    }
    

    camera.target.x = player.position.x;
    

    if (drunk){
        BeginShaderMode(shaders.glowShader2);

    }


    BeginMode2D(camera);


    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera); //put this after draw and it works now?
    HandleKeyboardAiming(player, worldMousePosition);
    
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
    if (!subwayToPark){
        float CarFrameWidth = 128.0;
        Rectangle sourceRecCar = {player_car.currentFrame * CarFrameWidth, 0, CarFrameWidth, CarFrameWidth};
        DrawTextureRec(resources.carSheet, sourceRecCar, player_car.position, WHITE); //draw player_car

    }


    if (player.enter_car == false){// if enter car is false, dont render player or update position. camera should stay focused on player pos. 
        SoundManager::getInstance().StopMusic("CarRun");

        //DRAW PLAYER
        player.DrawPlayer(resources, gameState, camera, shaders);

    }

    if (player.enter_car) EnterCar(resources, player, player_car); //draws headlights and such

    show_dbox = false;//reset box
    
    for (NPC& npc : ParkNpcs){  
        if (npc.MiB){//update mibs if cemeterykey and no zombies. Mib activates zombies, then disapears
            if (hasCemeteryKey && mibTimer > 0){//mibTimer is initially set to 3 seconds
                npc.Update(player, gameState);
                npc.Render(shaders);
                npc.ClickNPC(mousePosition, camera, player, gameState);
                //mib shows up in park, interacting with him spawns zombies and he vanishes
                if (npc.interacting){
                    dboxPosition = npc.position;
                    show_dbox = true;   //dialogBox
                    raiseParkZombies = true;
                    mibTimer -= GetFrameTime(); //mib timer tics down when interacting for 3 seconds then deactivate 
                    phrase = npc.speech;//WE are Watching You
                    if (mibTimer <= 0){
                        npc.isActive = false;
                    }
                }
                
            }

        }else{//update and render all other NPCs in the Park, zombies can attack NPCs in the park
            npc.Update(player, gameState);
            npc.Render(shaders);
            npc.ClickNPC(mousePosition, camera, player, gameState);
            if (npc.interacting){
                dboxPosition = npc.position;
                show_dbox = true;
                phrase = npc.speech;
            }
            if (!npc.isActive && npc.CanSpawnZombie){ //wait untill NPC is not active before raising zombie, so death animation can finish.  
                npc.CanSpawnZombie = false;
                
                spawnZombie(resources, npc.position); //NPC is transformed into a zombie. 
            }

      

        }

    }

    for (NPC& zombie : zombies){
        zombie.Update(player, gameState);
        zombie.Render(shaders);
        UpdateZombieTarget(zombie, ParkNpcs);
    }

    if (show_carUI && !move_car && player.enter_car){ //destination menu //Draw inside mode2d
        DrawCarUI(player_car, mousePosition, camera, gameState);
        //drawingCarUI
        
    }
    DrawBullets(); 
    //DrawStreetLight
    BeginBlendMode(BLEND_ADDITIVE);
    DrawTexture(resources.lightCone, 1013, 610, WHITE);
    DrawTexture(resources.lightCone, 1492, 610, WHITE);
    DrawTexture(resources.lightCone, 1967, 610, WHITE);
    EndBlendMode();

    EndMode2D();

    DrawMoney(); //draw money after EndMode2d()
    overSubway = false;
    if (player.position.x > 2025 && player.position.x < 2045 && gameState == PARK){
        phrase = "Up TO ENTER SUBWAY";
        show_dbox = true;
        dboxPosition = player.position;
        overSubway = true;
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
            transitionState = FADE_OUT;
        }

    }

    if (showInventory){ // this could be done globally, there is never a time when we don't want to show inventory
         
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);  // Render the inventory 
    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        if (player.enter_car && !move_car){ // dont exit car if it's still moving.
            PlaySound(SoundManager::getInstance().GetSound("CarDoorClose")); 
            player.enter_car = false;
            player_car.currentFrame = 0;
           
        }
    }

    if (player.hasGun){//DRAW RETICLE IF AIMING AND HAS GUN
        DrawTexture(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ? resources.reticle : resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // if aiming draw reticle
    }else{
        DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE);
    }

    if (show_dbox){
        DrawDialogBox(player, camera, 0, 0, 20);

    }


    if (raiseParkZombies){
        raiseParkZombies = false;
        StartZombieSpawn(10);
        minDistToPlayer = 200; //zombies can spawn further away
        maxDistToPlayer = 400;

    }


   if ((player.hasGun || player.hasShotgun) && !player.enter_car) DrawHUD(player); //always show ammo when outside of car in the cemetery

    //DrawText("Cemetery", screenWidth/2 - 100, 60, 50, WHITE);

    //draw healthbar 
    if (player.currentHealth < 100 &&  !player.enter_car){
        Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
        DrawHealthBar(resources,barPos, player.maxHealth, player.currentHealth, 128, 16);

    }

}

//Office
void RenderOffice(GameResources& resources, Camera2D& camera, Player& player, Elevator& elevator, Vector2& mousePosition, ShaderResources& shaders){
    show_dbox = false;
    over_elevator = false;
    over_Ebutton = false;
    elevator.isOccupied = false;
    float deltaTime = GetFrameTime();


    if (can_spawn_zombies){
        can_spawn_zombies = false;
        StartZombieSpawn(15);
    }

    if (player.position.x < 2540 && player.position.x > 2520){
        over_Ebutton = true;
        phrase = "Call Elevator";
        show_dbox = true;
        dboxPosition = player.position;
    
    }

    if (player.position.x < 3295 && player.position.x > 3275){
        over_Ebutton = true;
        phrase = "Call Elevator";
        show_dbox = true;
        dboxPosition = player.position;
    
    }

    if (player.position.x < 2488 && player.position.x > 2468){
        if (elevator.isOpen){
            over_elevator = true;
            phrase = "Up to Enter";
            show_dbox = true;
            dboxPosition = player.position;

        } 

    }

    camera.target = player.position;
    BeginMode2D(camera);  // Begin 2D mode with the camera, things drawn inside Mode2D have there own coordinates based on the camera. 
    ClearBackground(customBackgroundColor);
    
    if (drunk) BeginShaderMode(shaders.glowShader2); //drunk doesn't work globally for whatever reason.
        
    

    //No parallax for lobby
    DrawTexturePro(resources.officeBackground, {0, 0, static_cast<float>(resources.officeBackground.width), static_cast<float>(resources.officeBackground.height)},
                    {300, 0, static_cast<float>(resources.officeBackground.width), static_cast<float>(resources.officeBackground.height)}, {0, 0}, 0.0f, WHITE);


    DrawElevator(elevator, resources.elevatorSheet, resources.floorNumberSheet, 128, 128, deltaTime);
    DrawElevator(elevators[1], resources.elevatorSheet, resources.floorNumberSheet, 128, 128, deltaTime);
    // for (Elevator& el : elevators){ //draw multiple elevator with the same properties exept for position. 
    //     DrawElevator(el, resources.elevatorSheet, resources.floorNumberSheet, 128, 128, deltaTime);
    // }



    //DRAW PLAYER
    if (!player.onElevator) player.DrawPlayer(resources, gameState, camera, shaders);

    for (NPC& office_npc : officeWorkers){
        office_npc.Update(player, gameState);
        office_npc.Render(shaders);
        office_npc.ClickNPC(mousePosition, camera, player, gameState);

        if (office_npc.interacting){
            phrase = office_npc.speech;
            show_dbox = true;
            dboxPosition = office_npc.position;
            
        }

        if (!office_npc.isActive && office_npc.CanSpawnZombie && !can_spawn_zombies){ //wait for can_spawn_zombies the global var triggered by no active robots. 
            office_npc.CanSpawnZombie = false;
            spawnZombie(resources, office_npc.position); //NPC is transformed into a zombie. 
        }
    }


    for (NPC& zombie : zombies){
        zombie.Update(player, gameState);
        zombie.Render(shaders);
        UpdateZombieTarget(zombie, officeWorkers);
    }

    DrawBullets();
    EndShaderMode(); ////////////////////////////SHADER OFF
    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera); //put this after draw and it works now?
    HandleKeyboardAiming(player, worldMousePosition);
    EndMode2D();

    //draw healthbar 
    if (player.currentHealth < 100 &&  !player.enter_car){
        Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
        DrawHealthBar(resources,barPos, player.maxHealth, player.currentHealth, 128, 16);

    }

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

    if ((player.hasGun || player.hasShotgun) && !player.enter_car) DrawHUD(player); //always show ammo when outside of car in the cemetery or NecroT



}

//Lobby
void RenderLobby(GameResources& resources, Camera2D& camera, Player& player, Elevator& elevator, Vector2& mousePosition, ShaderResources shaders){
    show_dbox = false;   
    over_exit = false;
    over_Ebutton = false;
    over_elevator = false;
    over_medkit = false;
    //elevator.isOccupied = false;
    float deltaTime = GetFrameTime();

    
    if (player.position.x < 2051 && player.position.x > 2031){
        over_medkit = true;
        phrase = "Pills Here";
        show_dbox = true;
        dboxPosition = player.position;
    }


    if (player.position.x < 2770 && player.position.x > 2750){ //exit lobby to necrotech exterior, triggered in uptoEnter()
        over_exit = true;
        phrase = "UP TO EXIT";
        show_dbox = true;
        dboxPosition = player.position;
        
    }

    if (player.position.x < 1330 && player.position.x > 1310){ //exit lobby to necrotech exterior, triggered in uptoEnter()
        over_exit = true;
        phrase = "UP TO EXIT";
        show_dbox = true;
        dboxPosition = player.position;
    }

    if (player.position.x < 2539 && player.position.x > 2519){
        over_Ebutton = true;
        phrase = "Call Elevator";
        show_dbox = true;
        dboxPosition = player.position;

    }

    if (player.position.x < 2488 && player.position.x > 2468){
        if (elevator.isOpen){
            over_elevator = true;
            phrase = "Up to Enter";
            show_dbox = true;
            dboxPosition = player.position;

        } 

    }

    camera.target = player.position;
    BeginMode2D(camera);  // Begin 2D mode with the camera, things drawn inside Mode2D have there own coordinates based on the camera. 
    ClearBackground(customBackgroundColor);
    
    if (drunk) BeginShaderMode(shaders.glowShader2); //drunk doesn't work globally for whatever reason.
        
    

    //No parallax for lobby
    DrawTexturePro(resources.subwayBackground, {0, 0, static_cast<float>(resources.subwayBackground.width), static_cast<float>(resources.subwayBackground.height)},
                    {0, 0, static_cast<float>(resources.subwayBackground.width), static_cast<float>(resources.subwayBackground.height)}, {0, 0}, 0.0f, WHITE);

  
    DrawTexturePro(resources.LobbyForeground, {0, 0, static_cast<float>(resources.LobbyForeground.width), static_cast<float>(resources.LobbyForeground.height)},
                    {64, 0, static_cast<float>(resources.LobbyForeground.width), static_cast<float>(resources.LobbyForeground.height)}, {0, 0}, 0.0f, WHITE);

    DrawElevator(elevator, resources.elevatorSheet, resources.floorNumberSheet, 128, 128, deltaTime);



    //DRAW PLAYER
    if (!player.onElevator) player.DrawPlayer(resources, gameState, camera, shaders);



    if (AreAllNPCsDeactivated(lobbyMibs) && can_spawn_robots){ //if all the lobby mibs are dead, spawn robots
        can_spawn_robots = false;
        spawnRobot(resources, player, player.position + Vector2 {300, 0});
        spawnRobot(resources, player, player.position + Vector2 {-300, 0});
        if (can_spawn_zombies){
            can_spawn_zombies = false;
            StartZombieSpawn(10); //spawn zombies when robots spawn, spawning zombies in the lobby triggers the alarm. 

        }

    }

    // if (AreAllNPCsDeactivated(lobbyRobots) && lobbyRobots.size() > 0 && can_spawn_zombies){ //robots are spawned and killed. so spawn zombies. 
    //     can_spawn_zombies = false;
    //     StartZombieSpawn(10);
        


    // }

    if (globalAgro && can_spawn_mibs){
        can_spawn_mibs = false;
        //spawnMib(resources, player, player.position + Vector2 {300, 0});
        spawnMib(resources, player, player.position + Vector2 {-300, 0});
        
    }
    
    //DRAW ROBOTS
    for (NPC& robot : lobbyRobots){ //No lobby robots at the moment. robots are spawned in later though so keep this. 
        if (robot.isActive){
            robot.Update(player, gameState);
            robot.Render(shaders);
            robot.ClickNPC(mousePosition, camera, player, gameState);

            if (globalAgro) robot.agro = true; //if one robot is angry they all are

            if (robot.agro){
                robot.destination = player.position;
                Flocking(player, lobbyRobots); //repulsion force if NPCs get too close. 
            }

            if (robot.interacting && !robot.agro){
                phrase = robot.speech;
                show_dbox = true;
                dboxPosition = player.position;
            
            }

        }
    }

    //DRAW MIBS

    for (NPC& mib : lobbyMibs){
        if (mib.isActive){
            mib.Update(player, gameState); 
            mib.Render(shaders);
            mib.ClickNPC(mousePosition, camera, player, gameState);

            if (globalAgro) mib.agro = true; //set other mibs to agro 

            if (mib.interacting && !mib.agro){
                phrase = mib.speech;
                show_dbox = true;
                dboxPosition = mib.position;

            }

            if (mib.agro){ 
                //mib.idleTime = 0;
                mib.hasTarget = true;
                mib.destination = player.position;
                mib.facingRight = player.position.x > mib.position.x;
                Flocking(player, lobbyMibs); //only flock if agro. flocking = repulsion force. 
                globalAgro = true; //if 1 mib is agro, alert everyone else. 


            
            }

        }
    }

    //Draw lobby NPC
    for (NPC& npc : lobbyNPCs){
        if (npc.isActive){
            npc.Update(player, gameState);
            npc.Render(shaders);

            //Lobby NPCs can't talk, it interferes with Mib Convo

        if (!npc.isActive && npc.CanSpawnZombie){ //spawn a zombie when the NPC dies even if they are not killed by a zombie. 
            npc.CanSpawnZombie = false;
            spawnZombie(resources, npc.position); //NPC is transformed into a zombie. 
        }

        }
    }

    for (NPC& zombie : zombies){
        zombie.Update(player, gameState);
        zombie.Render(shaders);
        UpdateZombieTarget(zombie, lobbyNPCs);
    }

    // for (NPC& zombie : zombies){
    //     zombie.Update(player, gameState);
    //     zombie.Render(shaders);
    //     float minDist = 1000;
    //     float closestNPCPositionX = 0.0f;
    //     zombie.targetNPC = nullptr;

    //     for (NPC& npc : lobbyNPCs) { //find the cloeset NPC and chase them. 
    //         if (npc.isActive){
    //             float dist = fabs(zombie.position.x - npc.position.x);

    //             if (dist < minDist) {
    //                 minDist = dist;
    //                 closestNPCPositionX = npc.position.x;
    //                 zombie.targetNPC = &npc;  

    //                 npc.zRight = npc.position.x < zombie.position.x; 
    //                 npc.isTargeted = true; //if npc is targeted, run away from the zombie targeting it. We needed isTargeted after all. 
    //                 npc.targetedTimer = 5.0f;  
    //             }
    //         }
    //     }

    //     if (zombie.targetNPC != nullptr) {
    //         zombie.hasTarget = true;
    //         zombie.destination = { closestNPCPositionX, zombie.position.y };

    //     } else {
    //         //zombie.hasTarget = false;
    //         // Optional behavior when no target is found
    //     }
    // }

    DrawBullets();
    EndShaderMode(); ////////////////////////////SHADER OFF
    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera); //put this after draw and it works now?
    HandleKeyboardAiming(player, worldMousePosition);
    EndMode2D();


    //draw healthbar 
    if (player.currentHealth < 100 &&  !player.enter_car){
        Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
        DrawHealthBar(resources,barPos, player.maxHealth, player.currentHealth, 128, 16);

    }

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

    if ((player.hasGun || player.hasShotgun) && !player.enter_car) DrawHUD(player); //always show ammo when outside of car in the cemetery or NecroT


}

//NecroTech
void RenderNecroTech(GameResources& resources, Camera2D& camera, Player& player, PlayerCar& player_car, Vector2& mousePosition, ShaderResources& shaders){

    show_dbox = false;
    
    SoundManager::getInstance().UpdateMusic("StreetSounds"); //only update street sounds when oustide or in vacant lot

    camera.target = player.position;
    float parallaxMidBuildings = camera.target.x * 0.4;
    float parallaxMidground = camera.target.x * 0.6f;  // Midground moves slower
    float parallaxBackground = camera.target.x * 1.0f;  // Background moves even slower

    over_car = false;
    if (player.position.x > player_car.position.x && player.position.x < player_car.position.x +30){
        over_car = true;
    }


    //Over building entrance
    over_necro = false;
    showPasswordInterface = false; //you can interact with either the door or the robot outside, to enter password. 
    if (player.position.x < 2144 && player.position.x > 2124){
        if (passwordValidated){
            over_necro = true;
            phrase = "UP TO ENTER";
            show_dbox = true;
            dboxPosition = player.position;

        }else{
            phrase = "LOCKED";
            show_dbox = true;
            dboxPosition = player.position;
            showPasswordInterface = true; //show password UI when over door
        }

    }

    
    BeginMode2D(camera);  // Begin 2D mode with the camera, things drawn inside Mode2D have there own coordinates based on the camera. 
    //Outside of Mode2D is screen space coords. 
   
    ClearBackground(customBackgroundColor);
    
    if (drunk){
        BeginShaderMode(shaders.glowShader2); //drunk doesn't work globally for whatever reason.
        //player.outline = true;

    }

    //background/midground width = 6400

     // Draw the background (sky)
    DrawTexturePro(resources.background, {0, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)},
                    {-1000 + parallaxBackground, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the midground (silhouettes)
    DrawTexturePro(resources.midground, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
                    {-3000 + parallaxMidground, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.MidBuildings, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
                    {-3050 + parallaxMidBuildings, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

  
    DrawTexturePro(resources.ntForeground, {0, 0, static_cast<float>(resources.ntForeground.width), static_cast<float>(resources.ntForeground.height)},
                    {1064, 0, static_cast<float>(resources.ntForeground.width), static_cast<float>(resources.ntForeground.height)}, {0, 0}, 0.0f, WHITE);



    //EXIT CAR
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        if (player.enter_car && !move_car){ // dont exit car if it's still moving.
            PlaySound(SoundManager::getInstance().GetSound("CarDoorClose")); 
            player.enter_car = false;
            player_car.currentFrame = 0;
        }
    }

    //Draw player_car
    float CarFrameWidth = 128;
    Rectangle sourceRecCar = {player_car.currentFrame * CarFrameWidth, 0, CarFrameWidth, CarFrameWidth};
    DrawTextureRec(resources.carSheet, sourceRecCar, player_car.position, WHITE); //draw player_car
    if (player.enter_car) EnterCar(resources, player, player_car);

    if (player.enter_car == false){// if enter car is false, dont render player or update position. camera should stay focused on player pos. 
        SoundManager::getInstance().StopMusic("CarRun");
    //DRAW PLAYER
        player.DrawPlayer(resources, gameState, camera, shaders);
    }

    if (show_carUI && !move_car && player.enter_car){ //destination menu //draw UI inside mode2d
        DrawCarUI(player_car, mousePosition, camera, gameState);
    }

    if (robots[0].agro && robots[0].isActive) showPasswordInterface = false; //hide interface on shots fired. 

    //showPasswordInterface = false; //dont show interface if not interacting. 
    for (NPC& robot : robots){
        if (robot.isActive){
            robot.Update(player, gameState);
            robot.Render(shaders);
            robot.ClickNPC(mousePosition, camera, player, gameState);
            if (robot.interacting){
                phrase = robot.speech;
                show_dbox = true;
                dboxPosition = robot.position;
                showPasswordInterface = true;


            }
        }
        
  
    }

    DrawBullets();
    EndShaderMode(); ////////////////////////////SHADER OFF
    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera); //put this after draw and it works now?
    HandleKeyboardAiming(player, worldMousePosition);
    EndMode2D();

    //draw healthbar 
    if (player.currentHealth < 100 &&  !player.enter_car){
        Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
        DrawHealthBar(resources,barPos, player.maxHealth, player.currentHealth, 128, 16);

    }

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

    if ((player.hasGun || player.hasShotgun) && !player.enter_car) DrawHUD(player); //always show ammo when outside of car in the cemetery or NecroT

    if (passwordTimer > 0){
        passwordTimer -= GetFrameTime();
    }

    //This delays turning off password interface so player has time to read the message. Make this logic better. 
    if (!passwordValidated && showPasswordInterface && passwordTimer <= 0){
        UpdatePasswordInterface(player); //show password interface
        RenderPasswordInterface();

    }else if (passwordValidated && showPasswordInterface && passwordTimer > 0){
        RenderPasswordInterface(); //show interface for a few seconds before not rendering it. 
    }else{
        //don't render nothin
    }



}
    


//Main Street
void RenderOutside(GameResources& resources, Camera2D& camera,Player& player, PlayerCar& player_car,MagicDoor& magicDoor, float& totalTime,  std::vector<NPC>& npcs, UFO& ufo, Vector2 mousePosition, ShaderResources& shaders) {

    SoundManager::getInstance().UpdateMusic("StreetSounds"); //only update street sounds when oustide or in vacant lot
    SoundManager::getInstance().PlayMusic("StreetSounds");
    PlayPositionalSound(SoundManager::getInstance().GetSound("energyHum"), ufo.basePosition, player.position, 800);

    playerOutsideInteraction(player, player_car);

    camera.target = player.position;
    float parallaxMidBuildings = camera.target.x * 0.4;
    float parallaxMidground = camera.target.x * 0.6f;  // Midground moves slower
    float parallaxBackground = camera.target.x * 0.8f;  // Background moves even slower
    
    BeginMode2D(camera);  // Begin 2D mode with the camera, things drawn inside Mode2D have there own coordinates based on the camera. 
    //Outside of Mode2D is screen space coords. 
    ClearBackground(customBackgroundColor);

    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera); //put this after draw and it works now?
    HandleKeyboardAiming(player, worldMousePosition);
    
    if (drunk){
        BeginShaderMode(shaders.glowShader2); //drunk doesn't work globally for whatever reason. TODO: fix drunk shader, make it global and look good.
        //player.outline = true;

    }

    //background/midground width = 6400

     // Draw the background (sky)
    DrawTexturePro(resources.background, {0, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)},
                    {-1000 + parallaxBackground, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the midground (silhouettes)
    DrawTexturePro(resources.midground, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
                    {-3000 + parallaxMidground, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.MidBuildings, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
                    {-3050 + parallaxMidBuildings, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),  offset by 1024 to center relative to midground. 
    DrawTexturePro(resources.foreground, {0, 0, static_cast<float>(resources.foreground.width), static_cast<float>(resources.foreground.height)},
                    {-639, 0, static_cast<float>(resources.foreground.width), static_cast<float>(resources.foreground.height)}, {0, 0}, 0.0f, WHITE);
    
    
   

    if (move_ufo){
        ufoTimer -= GetFrameTime();
        DrawUFO(resources, ufo, camera, totalTime, shaders);
        moveUFO(ufo, player);
    }

    abductionBeam = false;
    if (player.position.x > ufo.position.x && player.position.x < ufo.position.x + 64){
        if (ufo.position.y > 395){ //if the UFO is low enough, and the player is under, show beam.
            abductionBeam = true;
        }
        
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

    dealer = false;
    teller = false;
    for (NPC& npc : npcs){ //iterate NPCs, update/render, check for player interaction.
        npc.Update(player, gameState);
        npc.Render(shaders);
        npc.ClickNPC(mousePosition, camera, player, gameState);

        if (npc.interacting){ //Take the first one you find. only one npc should be able to interact. If you click on multiple NPCs really fast
        //the dialog box jumps around depending on the timer. Need a way to cancel all interaction except the last one. 
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
        
        }
    
    }
    
    //DrawStreetLight
    BeginBlendMode(BLEND_ADDITIVE);
    DrawTexture(resources.lightCone, 1884, 610, WHITE);
    DrawTexture(resources.lightCone, 3188, 610, WHITE);
    DrawTexture(resources.lightCone, 456, 610, WHITE);
    DrawTexture(resources.lightCone, 4550, 610, WHITE);
    EndBlendMode();
    
    DrawBullets();

    //DrawPlayerCar
    if (!carToPark){ //you took the car to the park and the subway back, car is still at the park
        float CarFrameWidth = 128;
        Rectangle sourceRecCar = {player_car.currentFrame * CarFrameWidth, 0, CarFrameWidth, CarFrameWidth};
        DrawTextureRec(resources.carSheet, sourceRecCar, player_car.position, WHITE); //draw player_car

    }


    //Draw MagicDoor
    if (applyShader){
        DrawMagicDoor(resources, player, magicDoor, shaders);  
    }


    if (player.enter_car) EnterCar(resources, player, player_car);
   

    if (player.enter_car == false){// if enter car is false, dont render player or update position. camera should stay focused on player pos. 
        SoundManager::getInstance().StopMusic("CarRun");

        //DRAW PLAYER
        
           
        player.DrawPlayer(resources, gameState, camera, shaders);
            
        
    }
    
    MoveTraffic(resources);//Draw Traffic
    EndShaderMode(); ////////////////////////////SHADER OFF

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

    
    //draw healthbar 
    if (player.currentHealth < 100 &&  !player.enter_car){
        Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
        DrawHealthBar(resources,barPos, player.maxHealth, player.currentHealth, 128, 16);

    }
   
    if (show_dbox && !player.enter_car){

        if (over_lot || over_apartment || over_car || start || overLiquor || overSubway){
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


void spawnNPCs(GameResources& resources){
    // Create NPCs and set there starting desitnations. 

    float speed = 50.0f; //normal NPC speed

    //spawn generic NPCs
    int generic = 5;
    for (int i = 0; i < generic; ++i) {
        float randomX = dis(gen); //random distrabution using RNG
        Vector2 g_pos = {randomX, 700.0f};   
        NPC npc = CreateNPC(resources.npcTexture, g_pos, speed, IDLE,  true, false);
        if (gameState == OUTSIDE){
            npc.SetDestination(0, 4000.0f);
        }else if (gameState == PARK){
            npc.SetDestination(1000, 2100);
        }
        npcs.push_back(npc);  // Add the NPC to the vector
        //ParkNpcs.push_back(npc); //no generic NPCs in park, too many people
    }

    //spawn office workers outside

    int workers = 3;
    for (int i = 0; i < workers; i++){
        float randomX = dis(gen);
        Vector2 w_pos = {randomX, 700.0f};
        NPC worker_npc = CreateNPC(resources.officeSheet, w_pos, speed, IDLE, true, false);
        worker_npc.SetDestination(0, 4000.0f);
        npcs.push_back(worker_npc);
    }

    //spawn businessMan

    int b_men = 5;
    for (int i = 0; i < b_men; i++){
        // Generate a random X position between 1000 and 4000
        float randomX = dis(gen);
        Vector2 b_pos = { randomX, 700.0f };
        
        NPC business_npc = CreateNPC(resources.businessSheet, b_pos, speed, IDLE, true, false);

        if (gameState == OUTSIDE){
            business_npc.SetDestination(0, 4000.0f);
        }else if (gameState == PARK){
            business_npc.SetDestination(1000, 2100);
        }
        
        
        npcs.push_back(business_npc);
        ParkNpcs.push_back(business_npc);
    }


    //spawn woman
    int women = 2;
    for (int i = 0; i < women; i++){
        float randomX = dis(gen);
        Vector2 w_pos = {randomX, 700};
        NPC woman_npc = CreateNPC(resources.womanSheet, w_pos, speed,IDLE, true, false);
        if (gameState == OUTSIDE){
            woman_npc.SetDestination(0, 4000.0f);
        }else if (gameState == PARK){
            woman_npc.SetDestination(1000, 2100);
        }
        npcs.push_back(woman_npc);

    }

    //spawn woman2
    int women2 = 3;
    for (int i = 0; i < women2; i++){
        float randomX = dis(gen);
        Vector2 w_pos = {randomX, 700};
        NPC woman2_npc = CreateNPC(resources.woman2Sheet, w_pos, speed, IDLE, true, false);
        if (gameState == OUTSIDE){
            woman2_npc.SetDestination(0, 4000.0f);
        }else if (gameState == PARK){
            woman2_npc.SetDestination(1000, 2100);
        }
        npcs.push_back(woman2_npc);
        ParkNpcs.push_back(woman2_npc);
    }

    //create mibs
    int m = 1;
    for (int i = 0; i < m; i++){
        Vector2 mib_pos = {static_cast<float>(2220 + i * 100), 700};
        NPC mib = CreateNPC(resources.mibSheet, mib_pos, speed, IDLE, true, false); //this mib starts active
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

    int ab = 5; //second row of bats higher up
    for (int i = 0; i < ab; i++){
        Vector2 b_pos = {static_cast<float>(1800 + i * 200), -500};
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

    //spawn astral ghosts, bosses of astral realm for now. 
    int ap = 2;
    for (int i = 0; i < ap; i++){
        Vector2 ag_pos = {static_cast<float>(2220 + i * 100), -751}; // spawn at the top of the atral plane. 
        NPC astralGhost = CreateNPC(resources.ghostSheet, ag_pos, speed, IDLE, false, false);
        ghost_npc.SetDestination(2000, 2200);
        astralGhost.ghost = true;
        astralGhost.maxHealth = 500;
        astralGhost.health = 500;
        astralGhost.agro = false;
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
    hobo_npc.SetDestination(2600, 2650);
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

    //spawn robots
    int rs = 1;
    for (int i = 0; i < rs; i++){
        Vector2 r_pos = {static_cast<float>(2200 + i * 100), 700};
        NPC robot_npc = CreateNPC(resources.robotSheet, r_pos, speed, IDLE, false, false);
        robot_npc.SetDestination(2100, 2300);
        robot_npc.robot = true;
        robot_npc.maxHealth = 300;
        robot_npc.health = 300;
        
        robots.push_back(robot_npc);
    }

    //spawn lobby robots
    int lr = 0;
    for (int i = 0; i < lr; i++){
        Vector2 r_pos = {static_cast<float>(2000 + i * 300), 700};
        NPC robot_npc = CreateNPC(resources.robotSheet, r_pos, speed, IDLE, false, false);
        robot_npc.SetDestination(2000, 2500);
        robot_npc.robot = true;
        robot_npc.maxHealth = 300;
        robot_npc.health = 300;

        lobbyRobots.push_back(robot_npc);

    }

    //spawn lobby NPCs
    int bmen = 3;
    for (int i = 0; i < bmen; i++){
        Vector2 b_pos = {static_cast<float>(2200 + i * 100), 700};
        NPC businessman = CreateNPC(resources.businessSheet, b_pos, speed, IDLE, false, false);
        businessman.SetDestination(2000, 2500);
        businessman.lobbyNPC = true;
        
        lobbyNPCs.push_back(businessman);
        officeWorkers.push_back(businessman); //business men in the office are the management lets say. 
    }

    int wm = 3;
    for (int i = 0; i < wm; i++){
        Vector2 w_pos = {static_cast<float>(2200 + i * 100), 700};
        NPC woman = CreateNPC(resources.woman2Sheet, w_pos, speed, IDLE, false, false);
        woman.SetDestination(2000, 2500);
        woman.lobbyNPC = true;
        lobbyNPCs.push_back(woman);
    }

    //spawn lobby MiBs
    int mb = 3;
    for (int i = 0; i < mb; i++){
        Vector2 m_pos = {static_cast<float>(2000 + i * 200), 700}; 
        NPC mib_npc = CreateNPC(resources.mibSheet, m_pos, speed, IDLE, false, false);
        mib_npc.MiB = true;
        
        lobbyMibs.push_back(mib_npc);
    }

    int of = 7;
    for (int i = 0; i < of; i++){
        Vector2 o_pos = {static_cast<float>(2000 + i * 200), 700};
        NPC officeWorker = CreateNPC(resources.officeSheet, o_pos, speed, IDLE, false, false);
        officeWorker.office = true;

        officeWorkers.push_back(officeWorker);

    }


}

void DisplayDate(GameCalendar& calendar){

    DrawText(calendar.GetDate().c_str(), screenWidth/2 - 450, 25, 20, WHITE);
    
}


void handleCamera(Camera2D& camera, float& targetZoom){
        // Handle zoom input
        if (GetMouseWheelMove() > 0) {
            targetZoom += 0.1f;
        } else if (GetMouseWheelMove() < 0) {
            targetZoom -= 0.1f;
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
    //Debug keys, disable for release. 
    if (IsKeyPressed(KEY_SPACE)){
        std::cout << "Player Position: "; //print player position on key_space for debug purposes
        PrintVector2(player.position);       
        
    }

    if (IsKeyPressed(KEY_EQUAL)){
        if (!borderlessWindow){
            borderlessWindow = true;
            ToggleBorderlessWindowed();
            windowStateChanged = true;
        

        }else{
            borderlessWindow = false;
            windowStateChanged = true;
            ToggleBorderlessWindowed();
        }

    }

    if (IsKeyPressed(KEY_ESCAPE)){ 
        if (!menuOpen){
            menuOpen = true;


        }else{
            menuOpen = false;
        }
        
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
            
            raiseZombies = true; // giving yourself keys also triggers zombies if you talk to the hobo first. 
            
            PlaySound(SoundManager::getInstance().GetSound("Keys"));

        }
    }
    if (IsKeyPressed(KEY_N)){
        if (!NecroTech){
            NecroTech = true;
            player.necroTechSearched = true;
        }
    }

    if (IsKeyPressed(KEY_B)){
        if (!player.hasBadge){
            player.hasBadge = true;
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

        if (!player.hasMac10){
            AddItemToInventory("mac10", inventory, INVENTORY_SIZE);
            player.hasMac10 = true;
        }

    }

}



void UptoEnter(Player& player, PlayerCar& player_car, Elevator& elevator){
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
        if (over_lot && gameState == OUTSIDE){ //over_lot = true
            transitionState = FADE_OUT;//transition to lot
        }
        if (over_gate && gameState == CEMETERY){
            transitionState = FADE_OUT;
            
        }
        if (overSubway && gameState == OUTSIDE){
            transitionState = FADE_OUT;
        }
        if (over_necro && gameState == NECROTECH){
            transitionState = FADE_OUT;
        }
        if (over_exit && gameState == LOBBY){
            transitionState = FADE_OUT;
        }
        if (over_Ebutton && gameState == LOBBY){
            if (elevator.isOpen){
                elevator.isOpen = false;
            }else{
                elevator.isOpen = true;
            }
            
        }

        if (over_Ebutton && gameState == OFFICE){ //open and close all elevators. shouldn't matter because they are offscreen. 
            if (elevator.isOpen){
                elevator.isOpen = false;
                elevators[1].isOpen = false;
            
            }else{
                elevator.isOpen = true;
                elevators[1].isOpen = true;
                
            }
        }

        if (over_elevator && gameState == OFFICE){
            if (elevator.isOpen){
                elevator.isOpen = false;
                elevator.isOccupied = true;
                player.onElevator = true;
                transitionState = FADE_OUT; //go to lobby
            }
        }


        if (over_elevator && gameState == LOBBY){
            if (elevator.isOpen){
                 elevator.isOccupied = true; //Enter elevator
                 player.onElevator = true;
                 elevator.isOpen = false;    //close the door and fade out. 
                 transitionState = FADE_OUT; //goes to office 

            } 

        }

        if (over_medkit && gameState == LOBBY){
            if (!player.hasPills){
                player.hasPills = true;
                AddItemToInventory("pills", inventory, INVENTORY_SIZE);
                showInventory = true;
               

            }
        }

    }
}


void UpdateDrawRectangle(Rectangle* destRect) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    float gameAspectRatio = (float)GAME_SCREEN_WIDTH / (float)GAME_SCREEN_HEIGHT;
    float screenAspectRatio = (float)screenWidth / (float)screenHeight;

    float scale = 1.0f;

    if (screenAspectRatio > gameAspectRatio) {
        // Screen is wider than the game aspect ratio (pillarbox)
        scale = (float)screenHeight / (float)GAME_SCREEN_HEIGHT;
        float scaledWidth = GAME_SCREEN_WIDTH * scale;
        float xOffset = ((float)screenWidth - scaledWidth) / 2.0f;
        *destRect = (Rectangle){ xOffset, 0, scaledWidth, (float)screenHeight };
    } else {
        // Screen is taller than the game aspect ratio (letterbox)
        scale = (float)screenWidth / (float)GAME_SCREEN_WIDTH;
        float scaledHeight = GAME_SCREEN_HEIGHT * scale;
        float yOffset = ((float)screenHeight - scaledHeight) / 2.0f;
        *destRect = (Rectangle){ 0, yOffset, (float)screenWidth, scaledHeight };
    }
}

void setButtonColors(){
    //GuiSetStyle is global for all buttons, this could be an issue for future buttons.
    Color LightBlue = {85, 160, 255, 255};//

    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(BLACK));
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(WHITE));
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(Fade(LightBlue, .80)));
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(LightBlue));
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(LightBlue));
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(LightBlue));
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(LightBlue));

    

}

void ShowControls(){
    float offsetX = 664 - (1024.0f / 2.0f); // Offset relative to the center of the 1024x1024 window
    Vector2 controlsRectPos = { (GetScreenWidth() / 2.0f) + offsetX, 212 };
    //Vector2 controlsRectPos = { 664, 212 };
    Vector2 controlsRectSize = { 300, 600 };
    DrawRectangle(controlsRectPos.x, controlsRectPos.y, controlsRectSize.x, controlsRectSize.y, Fade(BLACK, 0.7f)); // Semi-transparent background
    DrawText("\nControls:\n\n\nEsc - Menu\n\nD - Move Right\n\nA - Move Left\n\nShift - Run\n\nW - Interact\n\nS - Exit Car/Apartment\n\nSpace - Jump\n\nI - Open Inventory\n\nRightClick - Aim\n\nLeftClick - Fire\n\nM - Mute Music\n\n\n\nDebug Keys:\n\nK - Give Keys\n\nG - Give Guns\n\nH - Give Shovel\n\nP - Give Drugs", 
            controlsRectPos.x + 32, controlsRectPos.y, 20, WHITE); 

}

void MainMenu(GameResources& resources, Vector2 mousePosition, PauseState& currentPauseState, Rectangle& destRect){
    // Draw semi-transparent background overlay
        if (menuOpen) {
            float offset_x = 0;
            if (borderlessWindow) offset_x = (screenWidth - GAME_SCREEN_WIDTH)/2;
        
            // Draw semi-transparent background overlay
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.3f));

            // Calculate positions for buttons
            // Let's center them vertically and place them near the center of the screen
            float btnWidth = 200;
            float btnHeight = 40;
            float spacing = 20;
            int totalButtons = 4;

            // Total vertical space needed = totalButtons * btnHeight + (totalButtons - 1) * spacing
            float totalHeight = totalButtons * btnHeight + (totalButtons - 1) * spacing;
            float startY = (screenHeight - totalHeight) / 2.0f;
            float centerX = (GetScreenWidth() - btnWidth) / 2.0f;

            // Button rectangles
            Rectangle btnPlayRec = { centerX, startY, btnWidth, btnHeight };
            Rectangle btnControlsRec = { centerX,startY + (btnHeight + spacing), btnWidth, btnHeight };
            Rectangle btnFullRec = { centerX, startY + 2*(btnHeight + spacing), btnWidth, btnHeight };
            Rectangle btnQuitRec = { centerX, startY + 3*(btnHeight + spacing), btnWidth, btnHeight };

            // Draw buttons
            if (GuiButton(btnPlayRec, "Play")) {
                // Close menu, resume game
                menuOpen = false;
                currentPauseState = GAME_RUNNING;
                controlsMenu = false; //disable controls menu, maybe leave it up and have a x button to close controls page
            }

            if (GuiButton(btnControlsRec, "Controls")){
                if (!controlsMenu){
                    controlsMenu = true;
                }else{
                    controlsMenu = false;
                }

            }

            if (GuiButton(btnFullRec, "FullScreen")) {
                if (!borderlessWindow){
                    borderlessWindow = true;
                    offsetX = 1024;
                    ToggleBorderlessWindowed();
                    windowStateChanged = true;
                

                }else{
                    borderlessWindow = false;
                    windowStateChanged = true;
                    ToggleBorderlessWindowed();
                }
            }

            if (GuiButton(btnQuitRec, "Quit")) {
                // Close the window
                quitRequested = true;
            }

            DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); //draw cursor again overtop of buttons. 
        }
}

void pauseLogic(PauseState& currentPauseState, RenderTexture2D& pauseTexture, RenderTexture2D& finalTexture){
    if (IsKeyPressed(KEY_ESCAPE)){
        if (currentPauseState == GAME_RUNNING){
            // Save the current frame
            //capture and display the last frame when the game enters the pause state.
            BeginTextureMode(pauseTexture);
            ClearBackground(BLACK);
            DrawTexturePro(
                finalTexture.texture,
                (Rectangle){0, 0, (float)finalTexture.texture.width, -(float)finalTexture.texture.height},
                (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
            EndTextureMode();
            
            currentPauseState = GAME_PAUSED;

        }else{
            currentPauseState = GAME_RUNNING;
        }
    }
}

Vector2 clampMouseCursor(Vector2& mousePosition){
    int winWidth = GetScreenWidth(); 
    int winHeight = GetScreenHeight();
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();

    // Clamp to window dimensions
    if (mouseX < 0) mouseX = 0;
    if (mouseX > winWidth - 1) mouseX = winWidth - 1;

    if (borderlessWindow){ //lock the cursor to the window only when in fullscreen AKA borderless window. 
        if (mouseX > winWidth){
            mouseX = winWidth - 1;
            SetMousePosition(mouseX, mouseY); //SetMousePosition overrides the mouse, keeping the cursor inside the screen. 
        }
    }

    if (mouseY < 0) mouseY = 0;
    if (mouseY > winHeight - 1) mouseY = winHeight - 1;

    // If we changed anything, set the mouse position:
    mousePosition = Vector2 {static_cast<float>(mouseX),static_cast<float>(mouseY)};
    return mousePosition;
}

void InitSounds(SoundManager& soundManager){
    //We use our own custom sound manager. We have an array of sounds, and an array of musticTracks.
    SetMasterVolume(1.0f);  // Sets the master volume to maximum
    
    SoundManager::getInstance().LoadMusic("CarRun", "assets/sounds/CarRun.ogg"); // load CarRun.ogg into music tracks with the name CarRun
    //music tracks automatically loop.The car running sound needs to loop, so we call it music.

    
    
    SoundManager::getInstance().LoadMusic("subwayAmbience", "assets/sounds/SubwayAmbience.ogg");
    
    SoundManager::getInstance().LoadMusic("StreetSounds", "assets/sounds/StreetSounds.ogg"); 
    //SoundManager::getInstance().LoadMusic("Jangwa", "assets/sounds/Jangwa.ogg");
    
    SoundManager::getInstance().LoadMusic("NewNeon", "assets/sounds/Neon(noDrum).ogg");
    soundManager.LoadSound("carRun", "assets/sounds/CarRun.ogg");
    soundManager.LoadSound("gunShot", "assets/sounds/gunShot.ogg");   //misc sounds
    soundManager.LoadSound("BoneCrack", "assets/sounds/BoneCrack.ogg");
    soundManager.LoadSound("boneBreak", "assets/sounds/boneBreak.ogg");
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
    soundManager.LoadSound("deathScream", "assets/sounds/deathScream.ogg");
    soundManager.LoadSound("Mac10", "assets/sounds/Mac10.ogg");
    soundManager.LoadSound("TrainArriving", "assets/sounds/TrainArriving.ogg");
    soundManager.LoadSound("TrainLeaving", "assets/sounds/TrainLeaving.ogg");
    //soundManager.LoadSound("subwayAmbience", "assets/sounds/SubwayAmbience.ogg");

    soundManager.LoadSound("alarm", "assets/sounds/alarm1.ogg");

    soundManager.LoadSound("ShotGun", "assets/sounds/ShotGun.ogg");
    soundManager.LoadSound("ShotgunReload", "assets/sounds/ShotgunReload.ogg");
    soundManager.LoadSound("laser", "assets/sounds/laser.ogg");
    soundManager.LoadSound("explosion", "assets/sounds/explosion27.ogg");

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

    //random gibberish clips - removed voice 1-7
    soundManager.LoadVoice("voice8", "assets/sounds/v1.ogg"); //load voices into sound managers's voices vector
    soundManager.LoadVoice("voice9", "assets/sounds/v2.ogg");
    soundManager.LoadVoice("voice10", "assets/sounds/v3.ogg");
    soundManager.LoadVoice("voice11", "assets/sounds/v4.ogg");
    soundManager.LoadVoice("voice12", "assets/sounds/v5.ogg");
    soundManager.LoadVoice("voice13", "assets/sounds/v6.ogg");
    soundManager.LoadVoice("voice14", "assets/sounds/v7.ogg");
    soundManager.LoadVoice("voice15", "assets/sounds/v8.ogg");
    soundManager.LoadVoice("voice16", "assets/sounds/v9.ogg");
    soundManager.LoadVoice("voice17", "assets/sounds/v10.ogg");
    soundManager.LoadVoice("voice18", "assets/sounds/v11.ogg");
    soundManager.LoadVoice("voice19", "assets/sounds/v12.ogg");
    soundManager.LoadVoice("voice20", "assets/sounds/v13.ogg");
    soundManager.LoadVoice("voice21", "assets/sounds/v14.ogg");
    soundManager.LoadVoice("voice22", "assets/sounds/v15.ogg");
    soundManager.LoadVoice("voice23", "assets/sounds/v16.ogg");
    soundManager.LoadVoice("voice24", "assets/sounds/v17.ogg");
    soundManager.LoadVoice("voice25", "assets/sounds/v18.ogg");

    //robot voices
    soundManager.LoadRobotVoice("robot1", "assets/sounds/robot1.ogg");
    soundManager.LoadRobotVoice("robot2", "assets/sounds/robot2.ogg");
    soundManager.LoadRobotVoice("robot3", "assets/sounds/robot3.ogg");
    soundManager.LoadRobotVoice("robot4", "assets/sounds/robot4.ogg");
    soundManager.LoadRobotVoice("robot5", "assets/sounds/robot5.ogg");


    soundManager.LoadSound("phit1", "assets/sounds/PlayerHit1.ogg"); //player VA hits
    soundManager.LoadSound("phit2", "assets/sounds/PlayerHit2.ogg");

    //Volume edits
    
    //music
    SoundManager::getInstance().SetMusicVolume("CarRun", 0.25f);
    //SoundManager::getInstance().SetMusicVolume("Schumann", 0.25f);
    
    //sounds
    SoundManager::getInstance().SetSoundVolume("Mac10", 0.5f);    
    SoundManager::getInstance().SetSoundVolume("CarStart", 0.5f);
    SoundManager::getInstance().SetSoundVolume("BoneCrack", 0.3f);
    SoundManager::getInstance().SetSoundVolume("Owl", 0.5f);
    SoundManager::getInstance().SetSoundVolume("alarm", 0.5f);
}


int main() {
    InitWindow(screenWidth, screenHeight, "Adventure Game");
    //PUT NOTHING ABOVE THIS ^^ CAN CAUSE SEG FAULT
    //SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();
    SoundManager& soundManager = SoundManager::getInstance();
    InitSounds(soundManager);
    HideCursor();
    SetExitKey(0);  // Disable escape key from closing the window
    // Set global text size for buttons
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25); 

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
    MagicDoor magicDoor2;
    UFO ufo;
    Train train;
    Elevator elevator;
    Elevator elevator2;


    InitializePlayerCar(player_car);
    InitializeMagicDoor(magicDoor,Vector2 {2089, 700});
    InitializeMagicDoor(magicDoor2, Vector2{2000, -747});
    InitEarth(earth);
    InitElevator(elevator, Vector2 {2446, 648});
    InitElevator(elevator2, Vector2 {3200, 648});

    InitUFO(ufo);
    spawnNPCs(resources); //spawn NPCs before rendering them outside
    InitPlatforms();
    InitializeTrain(train);
    
    setButtonColors(); //main menu button colors, sets globally for all rayGUI buttons

    elevators.push_back(elevator);
    elevators.push_back(elevator2);
    // Initialize the camer
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ GAME_SCREEN_WIDTH / 2.0f, GAME_SCREEN_HEIGHT / 2.0f + 188.0f };  // Screen center + y offset 188 lower ground for bigger sky
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    float targetZoom = camera.zoom;  // Initialize targetZoom to the initial zoom value
   
    inventoryPositionX = player.position.x; //init inventory position
    inventoryPositionY = player.position.y;  
    SetTargetFPS(60);
    dboxPosition = player.position;

    //AddItemToInventory("Drugs", inventory, INVENTORY_SIZE);
    // Font RubicBold = LoadFontEx("assets/fonts/Rubik-Bold.ttf", 32, NULL, 0);
    // Font Righteous = LoadFontEx("assets/fonts/Righteous-Regular.ttf", 32, NULL, 0);

    //GuiSetFont(RubicBold); // Set the loaded font as the default GUI font

    //PlayMusicStream(SoundManager::getInstance().GetMusic("Jangwa"));
    PlayMusicStream(SoundManager::getInstance().GetMusic("NewNeon"));
    
    RenderTexture2D targetTexture = LoadRenderTexture(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT); //render target. Draw to rendertexture2d first
    RenderTexture2D vignetteTexture = LoadRenderTexture(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
    RenderTexture2D finalTexture = LoadRenderTexture(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
    RenderTexture2D pauseTexture = LoadRenderTexture(screenWidth, screenHeight);

    Rectangle destRect = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };
    UpdateDrawRectangle(&destRect);

    PauseState currentPauseState = GAME_RUNNING;

    
    float totalTime = 0.0f; // time elapsed from start of game //glitch shader/ufo
    // Main game loop
    while (!WindowShouldClose() && !quitRequested) {
        pauseLogic(currentPauseState, pauseTexture, finalTexture);

        Vector2 mousePosition = GetMousePosition();

        mousePosition = clampMouseCursor(mousePosition); //stop mouse from going offscreen when in fullscreen. 
        

        if (!player.enter_car) player.UpdateMovement(resources, gameState, mousePosition, camera, platforms);  // Update player position and animation
        UpdateInventoryPosition(camera, gameState);

        
        SoundManager::getInstance().UpdateMusic("NewNeon");
        SoundManager::getInstance().UpdateMusic("subwayAmbience");
        SoundManager::getInstance().UpdateMusic("CarRun");

        if (gameState != SUBWAY){//stop subway sounds outside subway
            SoundManager::getInstance().ManagerStopSound("TrainArriving");
            SoundManager::getInstance().ManagerStopSound("TrainLeaving");
            SoundManager::getInstance().StopMusic("subwayAmbience");
        }
  
        //HandleActiveNPC();

        UpdateBullets();
        //check each enemy group for bullet collisions
        CheckBulletNPCCollisions(zombies, player);
        CheckBulletNPCCollisions(ghosts, player);
        CheckBulletNPCCollisions(astralGhosts, player);
        CheckBulletNPCCollisions(bats, player);
        CheckBulletNPCCollisions(astralBats, player);
        
        CheckBulletNPCCollisions(robots, player); //player shoots necroTech robot
        CheckBulletNPCCollisions(lobbyRobots, player); //player shoots lobby robots
        CheckBulletNPCCollisions(lobbyMibs, player); // player shoots mibs
        
        CheckLaserNPCCollisions(lobbyNPCs, player); //robots can shoot regular NPCs if they happen to be in the way
        CheckLaserNPCCollisions(zombies, player); //mibs can shoot zombies if they get in the way.


        CheckBulletPlayerCollisions(player); //NPCs shoot player
        MonitorMouseClicks(player, calendar); 
        UpdateZombieSpawning(resources, player);
        //glowEffect(glowShader, gameState); //update glow shader

       
        
        float deltaTime = GetFrameTime();
        totalTime += deltaTime; // used for UFO sine wave
        if (totalTime > 10000.0f) totalTime -= 10000.0f; //reset total time just in case. 
            
        UpdateShaders(shaders, deltaTime, borderlessWindow,  gameState);
        SoundManager::getInstance().UpdateRandomVoices(deltaTime);

        if (windowStateChanged) { //toggle full screen    
            UpdateDrawRectangle(&destRect); 
            windowStateChanged = false;


            
        }
        
        if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)){ //tutorial text
            if (start){
                start = false; //turn off dbox if any movement
                phrase = "UP to Enter"; //set phrase to uptoenter cause liquor store doesn't set it

            }

        }

        if (IsKeyPressed(KEY_M)){ //MUTE MUSIC
            if (SoundManager::getInstance().IsMusicPlaying("NewNeon")){
                SoundManager::getInstance().PauseMusic("NewNeon");
                

            }else{
                SoundManager::getInstance().ResumeMusic("NewNeon");
                
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
       
        UptoEnter(player, player_car, elevator);//enter different areas by pressing up
        

        if (currentPauseState == GAME_PAUSED){ //if game is paused, save the last frame of the game running, and draw it behind the menus
            BeginDrawing();
            ClearBackground(BLACK);
            UpdateDrawRectangle(&destRect);
            // Draw the saved frame
            DrawTexturePro(
                pauseTexture.texture,
                (Rectangle){0, 0, (float)pauseTexture.texture.width, -(float)pauseTexture.texture.height},
                destRect,
                (Vector2){0, 0},
                0.0f,
                WHITE
            );
            setButtonColors(); //set menu button color and text size. 
            // Draw the pause menu
            MainMenu(resources, mousePosition, currentPauseState, destRect); //draw main menu over the saved frame.

            if (controlsMenu) ShowControls();
            EndDrawing();
            continue;  // Skip the rest of the loop, dont update or render the game. 

        }else if (currentPauseState == GAME_RUNNING){ //only update the game if it's not paused
            handleCamera(camera, targetZoom); //Can't update zoom when paused. So handle camera only when game is running. 
            GuiSetStyle(DEFAULT, TEXT_SIZE, 20); //set text size smaller for dealer and teller buttons. 
            //MULTIPASS RENDERING. Everything inside BeginTextureMode is saved to a RenderTexture2D. This makes it possible to stack shaders.   
            BeginTextureMode(targetTexture); //Render to targetTexture. First Pass/////////////////////////////
            
            switch (gameState){//Depending on the gameState, render the scene. 
                case OUTSIDE:
                    RenderOutside(resources, camera, player, player_car, magicDoor, totalTime, npcs, ufo, mousePosition, shaders); 
                    break;
                case APARTMENT:
                    RenderApartment(resources, player, mousePosition, calendar, camera, shaders);
                    break;
                case ROAD:
                    RenderRoad(resources, player_car, player, camera, mousePosition, shaders);
                    break;
                case CEMETERY:
                    RenderCemetery(resources, player, player_car, ufo, totalTime, camera,mousePosition, shaders);
                    break;
                case WORK:
                    ClearBackground(BLACK);//do nothing at the moment
                    break;
                case LOT:
                    RenderLot(resources, player, camera, mousePosition, shaders);
                    break;
                case GRAVEYARD:
                    RenderGraveyard(resources, player, camera, mousePosition, shaders);
                    break;
                case ASTRAL:
                    RenderAstral(resources, player, camera, mousePosition, earth, magicDoor, magicDoor2, shaders);
                    break;
                case PARK:
                    RenderPark(resources, player,player_car, camera, mousePosition, shaders);
                    break;

                case SUBWAY:
                    RenderSubway(resources, player, camera, mousePosition, train, shaders);
                    break;

                case NECROTECH:
                    RenderNecroTech(resources, camera, player, player_car, mousePosition, shaders);
                    break;

                case LOBBY:
                    RenderLobby(resources, camera, player, elevator, mousePosition, shaders);
                    break;

                case OFFICE:
                    RenderOffice(resources, camera, player, elevator, mousePosition, shaders);
                    break;
                    
            }

            HandleTransition(player, player_car, calendar, npcs); //Check everyframe for gamestate transitions, inside draw to handle fadeouts
            EndTextureMode(); 

        }

        //Render to texture //////////////////////////// Second Pass: Apply vignette shader seperate so we can stack effects. 
        BeginTextureMode(vignetteTexture);
            ClearBackground(BLACK);
            BeginShaderMode(shaders.vignetteShader);
                DrawTextureRec( //Drawing the target texture inside texture mode saves it to what ever RenderTextur2D you provide. 
                    targetTexture.texture, 
                    (Rectangle){ 0, 0, (float)targetTexture.texture.width, -(float)targetTexture.texture.height }, 
                    (Vector2){ 0, 0 },
                     WHITE);
            EndShaderMode();
        EndTextureMode();


        BeginTextureMode(finalTexture);
            ClearBackground(BLACK);
            if (player.hitTimer > 0) BeginShaderMode(shaders.redVignetteShader); //apply hurt shader if hit
            
                DrawTextureRec( 
                    vignetteTexture.texture, 
                    (Rectangle){ 0, 0, (float)vignetteTexture.texture.width, -(float)vignetteTexture.texture.height }, 
                    (Vector2){ 0, 0 },
                     WHITE);
            EndShaderMode();
            DrawMoney(); //render UI to texture over top of vignette shaders, outside of camera mode
            //DisplayDate(calendar);

            //show FPS
            int fps = GetFPS();
            Vector2 fpos = {screenWidth/2 + 450, 935}; //bottom right
            DrawText(std::to_string(fps).c_str(), fpos.x, fpos.y, 25, WHITE);

        EndTextureMode();

        // Draw the target texture //////FINAL PASS: Draw finalTexture to screen. 
        BeginDrawing();
            ClearBackground(BLACK);

            //drunk shader is set inside render functions      
            if (applyShader) BeginShaderMode(shaders.glowShader);     //Apply various shaders before rendering to screen
            if (glitch) BeginShaderMode(shaders.glitchShader);
            //BeginShaderMode(shaders.oldFilmShader);
            DrawTexturePro(
                finalTexture.texture, 
                (Rectangle){ 0, 0, (float)finalTexture.texture.width, -(float)finalTexture.texture.height },
                destRect,
                (Vector2){ 0, 0 },
                0.0f,
                WHITE
            );

            
        EndShaderMode();
        EndDrawing();
        
        
    }

    // Unload resources and close the window
    UnloadGameResources(resources);
    soundManager.UnloadAllSounds();
    UnloadShaders(shaders);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
