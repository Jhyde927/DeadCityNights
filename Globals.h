#ifndef GLOBALS_H
#define GLOBALS_H

#include <raylib.h>
#include <vector>
#include "GameEnums.h"


// Declare global Camera2D
extern Camera2D camera;
extern float targetZoom; // So you can smoothly zoom in/out


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
    float postLoopWaitDuration;  // New
    float postLoopWaitTimer;     // New
    float stopTimer;
    float slowDownStartX;
    TrainState state;
};

extern PlayerCar player_car;
extern MagicDoor magicDoor;
extern Earth earth;
extern Elevator elevator;
extern UFO ufo;
extern Train train;

extern Vector2 mousePosition; // Global mouse position


#endif // GLOBALS_H
