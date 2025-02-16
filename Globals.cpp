#include "Globals.h"


PlayerCar player_car;
Earth earth;
MagicDoor magicDoor;
UFO ufo;
Train train;
Elevator elevator;

std::vector<Platform> platforms;

Camera2D camera = { 0 };
float targetZoom = 1.0f; 
float totalTime = 0.0f;
Vector2 mousePosition = {0, 0}; 









void InitCamera() {
//init camera, and targetZoom, delcared in Globals.h
    int GAME_SCREEN_WIDTH = 1024;
    int GAME_SCREEN_HEIGHT = 1024;
    camera.offset = (Vector2){ GAME_SCREEN_WIDTH / 2.0f, GAME_SCREEN_HEIGHT / 2.0f + 188.0f }; //offset 188 from middle for bigger sky
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    targetZoom = camera.zoom;  // Sync with initial zoom
    }


void InitializePlayerCar(){
    player_car.position = {1710, 700-32};
    player_car.carSpeed = 100;
    player_car.currentFrame = 0;
}

void InitializeMagicDoor(MagicDoor& magicDoor, Vector2 position){
    magicDoor.position = position;//{2089, 700};
    magicDoor.currentFrame = 0;
}

void InitEarth(){
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



void InitUFO(){
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


