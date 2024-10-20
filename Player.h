#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>  // Assuming Vector2 is used from raylib
#include "GameResources.h" // Include resources for the method
#include "GameEnums.h"
#include "platform.h"
#include <vector>

enum WeaponType {
    REVOLVER,
    SHOTGUN
};


class Player {
public:
    // Public member variables
    Vector2 position;
    Vector2 velocity;      // New velocity vector
    Vector2 size;
    float gravity;         // Gravity force applied to the player
    bool isOnGround;       // Flag to check if the player is on the ground
    float jumpForce;       // The initial upward force when the player jumps
    bool jumping;
    bool onPlatform;
    float fallTimer;
    float walkSpeed;
    float runSpeed;
    int currentFrame;    // Current animation frame
    float frameCounter;  // Counter to track time between frames
    float frameSpeed;    // Speed of the animation (frames per second)
    float maxSpeedX;       // Maximum horizontal speed
    float maxSpeedY;       // Maximum vertical speed (terminal velocity)
    float acceleration;
    float deceleration;

    float walkFrameSpeed; // Slower animation speed for walking
    float runFrameSpeed;   // Faster animation speed for running

    bool isMoving;
    bool facingRight;
    bool isRunning;
    bool isAiming;
    bool isShooting;
    bool isDead;
    bool isReloading;
    bool canShoot;
    bool hasGun;
    bool hasShotgun;
    bool hasShovel;
    bool hasBadge;


    bool enter_car;
    int bulletCount;
    int shells;
    bool can_take_damage;

    // New health-related variables
    int maxHealth;
    int currentHealth;
    float hitTimer;
    float reloadTimer;
    double LastTapTimeLeft;
    double LastTapTimeRight;
    double tapInterval;


    // Constructor
    Player();

    // Methods
    public:
        void take_damage(int damage);
        WeaponType currentWeapon;  // Now accessible from outside the class 
        int shotgunBulletCount;
        int revolverBulletCount;
 


        
        void UpdateMovement(GameResources& resources, GameState& gameState, Vector2& mousePosition, Camera2D& camera,std::vector<Platform> platforms);  // Move the update movement here
        void DrawPlayer(const GameResources& resources, GameState& gameState, Camera2D& camera);  // Draw player method
        void HandleInput(float speed);
        void Reload();
        void reloadLogic(float deltaTime);
        void playerPhysics(float deltaTime, std::vector<Platform> platforms);
        void updateAnimations(GameResources& resources);
        bool CheckIfOnPlatform(const std::vector<Platform>& platforms);


        

            





    
};

#endif
