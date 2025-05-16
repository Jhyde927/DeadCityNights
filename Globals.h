#ifndef GLOBALS_H
#define GLOBALS_H

#include <raylib.h>
#include "GameEnums.h"
#include "platform.h"
#include <vector>
#include "NPC.h"
#include "box.h"
#include "Particle.h"
#include "Explosion.h"
//Global containers

// Declare global Camera2D
extern Camera2D camera;
extern float targetZoom;

extern std::vector<Explosion> explosions;

extern Emitter explosionEmitter;  

extern std::vector<NPC> npcs; //outside // subway
extern std::vector<NPC> zombies; //cemetery/graveyard
extern std::vector<NPC>hobos; //lot
extern std::vector<NPC>ghosts; //graveyard friendly ghost
extern std::vector<NPC>bats; //not used
extern std::vector<NPC>mibs; //outside
extern std::vector<NPC>astralGhosts;
extern std::vector<NPC>astralBats;
extern std::vector<NPC>ParkNpcs;
extern std::vector<NPC>robots; //necrotech
extern std::vector<NPC>lobbyRobots;
extern std::vector<NPC>lobbyNPCs;
extern std::vector<NPC>lobbyMibs;
extern std::vector<NPC>officeWorkers;
extern std::vector<NPC>scientists;
extern std::vector<NPC>cyberZombies;
extern std::vector<NPC>aliens;
extern std::vector<NPC>CEOs;
extern std::vector<NPC>Boss;

//enemy NPC groups. 
extern std::vector<std::vector<NPC>*> enemies;

//Every NPC group. Used for clearing pointers on exit. 
extern std::vector<std::vector<NPC>*> allNPCGroups;

struct GlobalState { //store random bools and timers that have accumulated over the months. just prefix everything with globalState is the price we pay for cleaner code. 
    float apartmentX = 2256;
    int vacantLotX = 2753;
    int vacantExitX = 2762;
    bool over_lot = false;
    bool over_exit = false;
    bool runOnce = true;
    bool quitRequested = false;
    bool canPlaySound = true;
    float playSoundTimer = 0.0;                        
    bool streetSounds = false;
    bool over_apartment = false; 
    bool over_car = false;
    bool over_elevator = false;
    bool over_elevator2 = false;
    bool over_Ebutton = false;
    bool over_Ebutton2 = false;
    bool over_necro = false;
    bool over_gate = false;
    bool over_shotgun = false;
    bool over_console = false;
    bool bossDefeated = false; //testing
    bool overSDconsole = false;
    bool showBadge = false;
    bool show_carUI = false;
    bool leave_apartment = false;
    bool leave_cemetery = false;
    bool sharpen = false;
    bool buttonNecro = false;
    bool showConsoleText = false;
    bool lockElevator2 = true;
    bool lockElevtorLab = true;
    bool playAlarm = false;

    bool triggerOutsideZombies = false; //set true for immediate zombies. 
    bool zombiesTriggered = false;
    bool outsideHobo = false;
    
    bool robotsTriggered = false;
    bool badEnding = false;
    bool buttonCemetery = false;
    bool buttonInternet = false;
    bool hasCemeteryKey = false;
    bool showTutorialText = false;
    bool canGiveFortune = true;
    bool can_spawn_zombies = true;
    bool visitedOffice = false;
    bool showInternet = false;
    bool borderlessWindow = false;
    bool windowStateChanged = false;
    bool fullscreen = false;
    bool usingController = false; 
    bool move_ufo = false;
    bool canMoveUfo = true;
    bool globalAgro = false;
    bool firstHobo = true;
    bool can_spawn_robots = true;
    bool spawning_zombies = false;
    bool can_spawn_mibs = true;
    bool firstBlood = false;
    bool drawShovel = false;
    bool drawCrowbar = true;
    bool explodeTanks = false;
    bool drawMac10 = true;
    bool drawShotgun = true;
    bool dealerButtonAdded = false;
    bool subwayToPark = false;
    bool carToPark = false;
    bool buttonWork = false;
    bool fading = false;
    bool over_medkit = false;
    bool digSpot = false;
    bool NecroTech = false;
    bool playerOffsetX = 0;
    bool film = false;
    bool start = true;
    bool buttonPark = false;
    bool drawingSubwayUI = false;
    bool gotoWork = false;
    bool gotoPark = false;
    bool gotoStreet = false;
    bool gotoNecro = false;
    bool gotoCemetery = false;
    bool debug = false; ///////////////////////////////////////DEBUG KEYS ON/OFF
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
    bool canSpawnCyberZombies = true;
    bool applyShader = false;
    bool drunk = false;
    bool glitch = false;
    bool openMagicDoor = false;
    bool move_car = false;
    bool trainAtStation = false;
    bool reverse_road = false;
    bool has_car_key = false;
    bool overLiquor = false;
    bool overSubway = false;
    bool subwayExit = false;
    bool openDrawer = false;
    bool raiseZombies = false;
    bool spawn_frank = true;
    bool zombieWave2 = false;
    bool zombieWave3 = false;
    bool abductionBeam = false;
    bool raiseParkZombies = false;
    bool show_dbox = true;
    float fadeAlpha = 1.0f;  // Starts transparent
    float fadeSpeed = 0.02f; // Speed of fade 
    float ufoTimer = 0.0;
    float internetTimer = 0.0;
    float inventoryPositionX = 0.0f;
    float inventoryPositionY = 0.0f;
    float passwordTimer = 0.0;
    float crowbarDialogTimer = 0.0;
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
    float maxSpawnDelay = 3;
    float tutorialTimer = 0.0;
    int selectedSlot = -1;
    int displayMoney = 100;
    bool canGlitch = true;
    float startTimer = 0.0f;
    bool startGame = false;

    //leftovers, refactor these, just define where they are used.
    Vector2 carKeysPos = {(1024/2) - 100, 655}; // remember positions need to based on screenwidth incase of resolution change. 
    Vector2 drawerPos = {1024/2 + 129, 730};
    Vector2 cemetery_start{2746, 700};
    Vector2 car_pos = {3000, 710};
    Vector2 truck_pos = {512, 710};
    Vector2 dz_pos = {0, 0};
    Vector2 pc_start_pos = Vector2{1710, 668};
    Vector2 pstart_by_car = Vector2{1738, 700};
    Vector2 dboxPosition;
    Color ApartmentBgColor {41, 48, 63, 255};
    Color customBackgroundColor = {32, 42, 63, 255};  //Same Color as sky background image. 
    // Variables for password input
    std::string enteredPassword = "";
    const std::string correctPassword = "666";
    bool passwordValidated = false;
    bool showPasswordInterface = false;

};

struct Tank { //bubbling tanks filled with hideous zombie clones. 
    Vector2 position;
    int currentFrame = 0;
    float frameTimer = 0.0f;
    float frameTime = 0.0f;
    int health;
    bool explode;
    bool canSpawn; //spawn a zombie on tank destruction. 
};

struct Console { //interactable termincal
    Vector2 position;
    int currentFrame = 0;
    float frameTimer = 0.0f;
    float frameTime = 0.0f;
    GameState scene; // scene specific props. One vector holds all the props, we draw only the ones set to the current scene. 

};

struct Monitor {
    Vector2 position;
    int currentFrame = 0;
    float frameTimer = 0.0f;
    float frameTime = 0.0f;
    GameState scene;

};

struct PlayerCar {
    Vector2 position;
    float carSpeed;
    int currentFrame = 0;
    bool facingLeft = true;

};

struct MagicDoor {
    Vector2 position;
    int currentFrame;
    float frameTimer;  // Each door gets its own timer
    float DoorframeTime;

};

struct Earth {
    Vector2 position;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int totalFrames;
    float frameTime; // Time between frames in seconds
    float frameTimer;
};

struct Elevator {
    Vector2 position;    
    int currentFrame;     
    float frameTimer;   
    float frameTime;       
    bool isOpen;           
    bool isOccupied;// Tracks if the player is on the elevator
    int totalFrames;       
    int currentFloorFrame;
    float floorFrameTimer;
    float floorFrameTime;
    Vector2 floorOffset;
};

struct UFO {
    Vector2 position;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int totalFrames;
    float frameTime;
    float frameTimer;

    Vector2 basePosition;  //center of UFO
    float bobAmplitudeX;   //ufo wobbles around base position. 
    float bobAmplitudeY;   
    float bobSpeedX;       
    float bobSpeedY;       
    float bobOffsetX;      
    float bobOffsetY;      
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
    float postLoopWaitDuration;
    float postLoopWaitTimer;     
    float stopTimer;
    float slowDownStartX;
    TrainState state;
};

extern GlobalState globalState;

extern PlayerCar player_car;

extern Earth earth;
extern UFO ufo;
extern Train train;

extern Vector2 mousePosition; // Global mouse position, updated in main.
extern float totalTime; // total elapsed time, used for sine waves

extern std::vector<Platform> platforms;
extern std::vector<Box> boxes; 
extern std::vector<MagicDoor> magicDoors;
extern std::vector<Elevator> elevators;

extern std::vector<Tank> Tanks;
extern std::vector<Console> consoles;
extern std::vector<Monitor> monitors;

NPC* FindClosestNPC(NPC& zombie, std::vector<NPC>& targetedNPCs); //called by zombie targeting NPCs, or Hobo targeting zombies. 

//init global objects
void InitCamera();
void InitializePlayerCar();
void InitializeMagicDoor(Vector2 position);
//void initExplosion(Vector2 position);
void InitTank(Vector2 position);
void InitConsole(Vector2 position, GameState scene);
void InitMonitor(Vector2 position, GameState scene);
void InitEarth();
void InitElevator(Vector2 position); 
void InitUFO();
void InitializeTrain();
void InitPlatforms();
void InitBoxes();
void InitializeNPCGroups();
void InitPenthouseObjects();
void InitLabObjects();

#endif // GLOBALS_H
