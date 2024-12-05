#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>  // Assuming Vector2 is used from raylib
#include "GameResources.h" // Include resources for the method
#include "GameEnums.h"
#include "platform.h"
#include <vector>
#include "shaderControl.h"

enum WeaponType {
    REVOLVER,
    SHOTGUN,
    MAC10
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
    float stunTimer;
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
    bool hasMac10;
    bool hasShovel;
    bool hasBadge;
    bool hasWhiskey;
    bool outline;
    bool holdingDown;
    bool dropping;
    float dropTimer;
    bool enter_car;
    bool enter_train;
    bool arriving;
    int bulletCount;
    int shells;
    int autoAmmo;
    bool can_take_damage; 
    int maxHealth;
    int currentHealth;
    float hitTimer;
    float reloadTimer;
    double LastTapTimeLeft;
    double LastTapTimeRight;
    double tapInterval;
    bool AllowGuns;
    float shotgunReloadTime;

    bool step = false;

    //declare class
    Player();

    // Methods
    public:
        WeaponType currentWeapon;  
        int shotgunBulletCount;
        int revolverBulletCount;
        int mac10BulletCount;
        void take_damage(int damage);
        void UpdateMovement(GameResources& resources, GameState& gameState, Vector2& mousePosition, Camera2D& camera,std::vector<Platform> platforms);  // Move the update movement here
        void DrawPlayer(const GameResources& resources, GameState& gameState, Camera2D& camera, ShaderResources& shaders);  // Draw player method
        void HandleInput(float speed);
        void Reload();
        void reloadLogic(float deltaTime);
        void playerPhysics(float deltaTime, std::vector<Platform> platforms);
        void updateAnimations(GameResources& resources);
        bool CheckIfOnPlatform(const std::vector<Platform>& platforms);
        void stunPlayer(float& time);


        

            





    
};

#endif
