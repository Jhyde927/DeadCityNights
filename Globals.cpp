#include "Globals.h"

GlobalState globalState;

//define the instances of the structs
PlayerCar player_car;
Earth earth;
MagicDoor magicDoor;
UFO ufo;
Train train;
Elevator elevator;
Tank tank;
Console console;
Monitor monitor;

std::vector<Explosion> explosions;
std::vector<Platform> platforms;
std::vector<Box> boxes; 
std::vector<MagicDoor> magicDoors;
std::vector<Elevator> elevators;

std::vector<Tank> Tanks;
std::vector<Console> consoles;
std::vector<Monitor> monitors;

//NPC groups
std::vector<NPC> npcs; //outside // subway
std::vector<NPC> zombies; //one global zombie vector for all zombies spawning in. 
std::vector<NPC>hobos; //lot
std::vector<NPC>ghosts; //graveyard friendly ghost
std::vector<NPC>bats; //not used
std::vector<NPC>mibs; //outside
std::vector<NPC>astralGhosts;
std::vector<NPC>astralBats;
std::vector<NPC>ParkNpcs;
std::vector<NPC>robots; //necrotech outside security. 
std::vector<NPC>lobbyRobots;
std::vector<NPC>lobbyNPCs;
std::vector<NPC>lobbyMibs;
std::vector<NPC>officeWorkers;
std::vector<NPC>scientists;
std::vector<NPC>cyberZombies;
std::vector<NPC>aliens;
std::vector<NPC>CEOs;
std::vector<NPC>Boss;

//Define global enemies vector, see InitializeNPCgroups()
std::vector<std::vector<NPC>*> enemies;

// Define the global NPC group list
std::vector<std::vector<NPC>*> allNPCGroups;

Emitter explosionEmitter;  

Camera2D camera = { 0 };
float targetZoom = 1.0f; 
float totalTime = 0.0f; //total elapsed time from starting game. Needed for sin waves
Vector2 mousePosition = {0, 0}; 

void InitCamera() {
//init camera, and targetZoom, delcared in Globals.h
    int GAME_SCREEN_WIDTH = 1024;
    int GAME_SCREEN_HEIGHT = 1024;
    camera.offset = (Vector2){ GAME_SCREEN_WIDTH / 2.0f, GAME_SCREEN_HEIGHT / 2.0f + 188.0f }; //offset 188 below middle for bigger sky
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    targetZoom = camera.zoom;  // Sync with initial zoom
    }

// Function to initialize allNPCGroups and enemies
void InitializeNPCGroups() {

    enemies =     //all the NPC groups that can be attacked by the player. 
    {
       &zombies, &cyberZombies, &ghosts, &bats, &lobbyMibs, 
       &robots, &lobbyRobots, &astralBats, &astralGhosts, &Boss
    }; //omit mib on main street, and ceo. they are added to the vector later

    //every NPC, just iterate group in groups and pick the one you need.  
    allNPCGroups = {
        &npcs, &zombies, &hobos, &ghosts, &bats, &mibs, 
        &astralGhosts, &astralBats, &ParkNpcs, &robots, 
        &lobbyRobots, &lobbyNPCs, &lobbyMibs, &officeWorkers, 
        &scientists, &cyberZombies, &aliens, &CEOs, &Boss
    };
}


//Destructible tanks in laboratory
void InitTank(Vector2 position){
    tank.position = position;
    tank.currentFrame = rand() % 6; //start on a random frame to offset animations. 
    tank.frameTimer = 0.0f;
    tank.frameTime = 0.15f;
    tank.health = 1;
    tank.explode = false;
    tank.canSpawn = true;
    Tanks.push_back(tank);


}

//consoles in lab and penthouse
void InitConsole(Vector2 position, GameState scene){
    console.position = position;
    console.currentFrame = 0;
    console.frameTimer = 0.0f;
    console.frameTime = 0.1f;
    console.scene = scene;
    consoles.push_back(console);


}
//monitors in lab or penthouse
void InitMonitor(Vector2 position, GameState scene){
    monitor.position = position;
    monitor.currentFrame = 0;
    monitor.frameTimer = 0.0f;
    monitor.frameTime = 0.1f;
    monitor.scene = scene;

    monitors.push_back(monitor);
}


//player car on main street park cemetery necrotech
void InitializePlayerCar(){
    player_car.position = {1710, 700-32};
    player_car.carSpeed = 100;
    player_car.currentFrame = 0;
}

//magic door to and from the astral realm
void InitializeMagicDoor(Vector2 position){
    magicDoor.position = position;//{2089, 700};
    magicDoor.currentFrame = 0;
    magicDoor.frameTimer = 0.0f;
    magicDoor.DoorframeTime = 0.1f;
    magicDoors.push_back(magicDoor);
}

//spinning globe in astral realm and ufo interior. 
void InitEarth(){
    earth.position = {2600, 300};
    earth.frameWidth = 48;
    earth.frameHeight = 48;
    earth.currentFrame = 0;
    earth.totalFrames = 94;
    earth.frameTimer = 0.0;
    earth.frameTime = .1;
}

//lobby, office, lab, penthouse
void InitElevator(Vector2 position){
   
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

    elevators.push_back(elevator); //add to global elevators vector
}

//UFO on mainstreet and cemetery
void InitUFO(){
    //animation perameters
    ufo.frameWidth = 144;
    ufo.frameHeight = 144;
    ufo.currentFrame = 0;
    ufo.totalFrames = 4;
    ufo.frameTimer = 0.0;
    ufo.frameTime = 0.1;

    ufo.basePosition = { -94.0, 0.0f }; //base position stays the same. When moving UFO, move base position.
    ufo.position = ufo.basePosition;

    // Set motion parameters
    ufo.bobAmplitudeX = 5.0f;   // Moves 10 pixels left and right
    ufo.bobAmplitudeY = 2.0f;    // Moves 5 pixels up and down
    ufo.bobSpeedX = 1.0f;        // Side-to-side speed
    ufo.bobSpeedY = 1.5f;        // Up-and-down speed
    ufo.bobOffsetX = 0.0f;       // No initial phase offset
    ufo.bobOffsetY = 0.0f;       // No initial phase offset
}
//init train in subeway. 
void InitializeTrain() {
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
    train.postLoopWaitDuration = 5.0f; // Time to wait after reaching x = 0
    train.postLoopWaitTimer = 0.0f;
    train.state = MovingToStation;

    // Calculate the distance needed to stop
    float stoppingDistance = (train.maxSpeed * train.maxSpeed) / (2.0f * train.deceleration);
    train.slowDownStartX = 2500.0f + stoppingDistance;
}

//destructible boxes.
void InitBoxes(){
    // boxes are stored in one big vector "boxes", and assigned to a specific scene on initiation. 
    //renderBoxes() called from render fucntions then renders the appropriate boxes for each scene. 
    Texture2D boxSheet = resources.boxSheet;

    //LOT
    
    boxes.emplace_back(Vector2 {2938, 724},boxSheet, LOT);
    boxes.emplace_back(Vector2 {2988, 724}, boxSheet, LOT);
    boxes.emplace_back(Vector2 {2988+50, 724}, boxSheet, LOT);

    //CEMETERY
    boxes.emplace_back(Vector2 {3550, 724}, boxSheet, CEMETERY);
    boxes.emplace_back(Vector2 {3600, 724}, boxSheet, CEMETERY);//right
    boxes.emplace_back(Vector2 {3500, 724}, boxSheet, CEMETERY);

    //GRAVEYARD
    boxes.emplace_back(Vector2 {4404, 724}, boxSheet, GRAVEYARD);//far right

    boxes.emplace_back(Vector2 {1600, 724}, boxSheet, GRAVEYARD);//far left
    boxes.emplace_back(Vector2 {1650, 724}, boxSheet, GRAVEYARD);
    boxes.emplace_back(Vector2 {1700, 724}, boxSheet, GRAVEYARD);

    //OUTSIDE
    boxes.emplace_back(Vector2 {-57, 724}, boxSheet, OUTSIDE); //left

    boxes.emplace_back(Vector2 {3980, 724}, boxSheet, OUTSIDE); //far right
    boxes.emplace_back(Vector2 {4030, 724}, boxSheet, OUTSIDE);
    boxes.emplace_back(Vector2 {4080, 724}, boxSheet, OUTSIDE);

    //SUBWAY
    boxes.emplace_back(Vector2 {1740, 724}, boxSheet, SUBWAY);
    boxes.emplace_back(Vector2 {1790, 724}, boxSheet, SUBWAY);

    //PARK
    boxes.emplace_back(Vector2 {1237, 724}, boxSheet, PARK);

    //NECROTECH EXTERIOR
    boxes.emplace_back(Vector2 {2500, 724}, boxSheet, NECROTECH);
    boxes.emplace_back(Vector2 {2450, 724}, boxSheet, NECROTECH);

    //OFFICE
    boxes.emplace_back(Vector2 {1210, 724}, boxSheet, OFFICE);
    boxes.emplace_back(Vector2 {1260, 724}, boxSheet, OFFICE);


}

//astral platforms
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
    //platforms.emplace_back(1600.0f, 100.0f, 200.0f, 20.0f, WHITE); //jump the gap
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

void InitPenthouseObjects(){
    //InitMonitor(Vector2 {1965, 668});
    InitMonitor(Vector2 {2005, 668}, PENTHOUSE);
    InitMonitor(Vector2 {2045, 668}, PENTHOUSE);
    InitMonitor(Vector2 {2085, 668}, PENTHOUSE);

    InitMonitor(Vector2 {2005, 628}, PENTHOUSE);
    InitMonitor(Vector2 {2045, 628}, PENTHOUSE);
    InitMonitor(Vector2 {2085, 628}, PENTHOUSE);

    InitConsole(Vector2 {2013, 668}, PENTHOUSE);

    InitMonitor(Vector2 {3081, 668}, PENTHOUSE);
    InitMonitor(Vector2 {3120, 668}, PENTHOUSE);
    InitMonitor(Vector2 {3160, 668}, PENTHOUSE);
    InitConsole(Vector2 {3089, 668}, PENTHOUSE);
}


void InitLabObjects(){

    for (int i = 0; i < 5; i++){
        InitTank(Vector2 {2200.0f + i * 100, 668});
    }

    InitConsole(Vector2 {2700, 668}, LAB);

    for (int i = 0; i < 4; i++){
        InitTank(Vector2 {2800.0f + i * 100, 668});
    }

    for (int i = 0; i < 5; i++){
        InitTank(Vector2 {3370.0f + i * 100, 668});
    }

    InitConsole(Vector2 {3900, 668}, LAB);

    InitMonitor(Vector2 {2750, 668}, LAB);
    InitMonitor(Vector2 {2126, 668},LAB);
    InitMonitor(Vector2 {3900, 668},LAB);

    for (int i = 0; i < 5; i++){
        InitTank(Vector2 {4000.0f + i * 100, 668});
    }
}

NPC* FindClosestNPC(NPC& zombie, std::vector<NPC>& TargetedNPCs) {
    //find closest npc to zombie
    NPC* closestNPC = nullptr;
    float minDist = 500.0f; // Large initial distance //but not too large. 500 is max distance to give chase. otherwise we dont bother. 
    //prevents NPCs running off screen because a zombie targeting them 1000 pixels away. 

    for (NPC& npc : TargetedNPCs) {
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



