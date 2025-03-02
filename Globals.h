#ifndef GLOBALS_H
#define GLOBALS_H

#include <raylib.h>
#include "GameEnums.h"
#include "platform.h"
#include <vector>
#include "NPC.h"

//A place to put random structs and vectors. That isn't main. 

// Declare global Camera2D
extern Camera2D camera;
extern float targetZoom;

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

// Extern declaration of the master NPC group list
extern std::vector<std::vector<NPC>*> allNPCGroups;


struct Tank {
    Vector2 position;
    int currentFrame = 0;
    float frameTimer = 0.0f;
    float frameTime = 0.0f;
};

struct Console {
    Vector2 position;
    int currentFrame = 0;
    float frameTimer = 0.0f;
    float frameTime = 0.0f;

};

struct Monitor {
    Vector2 position;
    int currentFrame = 0;
    float frameTimer = 0.0f;
    float frameTime = 0.0f;

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
    Vector2 position;
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
    float postLoopWaitDuration;
    float postLoopWaitTimer;     
    float stopTimer;
    float slowDownStartX;
    TrainState state;
};

extern PlayerCar player_car;

extern Earth earth;
extern UFO ufo;
extern Train train;

extern Vector2 mousePosition; // Global mouse position, updated in main.
extern float totalTime; // total elapsed time, used for sine waves

extern std::vector<Platform> platforms;
extern std::vector<MagicDoor> magicDoors;
extern std::vector<Elevator> elevators;

extern std::vector<Tank> Tanks;
extern std::vector<Console> consoles;
extern std::vector<Monitor> monitors;

void InitCamera();
void InitializePlayerCar();
void InitializeMagicDoor(Vector2 position);
void InitTank(Vector2 position);
void InitConsole(Vector2 position);
void InitMonitor(Vector2 position);
void InitEarth();
void InitElevator(Vector2 position); 
void InitUFO();
void InitializeTrain();
void InitPlatforms();
void InitBoxes();
void InitializeNPCGroups();



#endif // GLOBALS_H
