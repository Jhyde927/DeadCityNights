#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "GameResources.h"
#include "GameEnums.h"
#include "platform.h"
#include <vector>
#include "shaderControl.h"
#include "Particle.h"
#include <string>

enum WeaponType {
    REVOLVER,
    SHOTGUN,
    MAC10,
    RAYGUN
};

class Player {
public:  
    // Player attributes
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
    float gravity;
    bool isOnGround;
    float jumpForce;
    bool jumping;
    bool onPlatform;
    float fallTimer;

    float walkSpeed;
    float runSpeed;
    int currentFrame;
    float frameCounter;
    float frameSpeed;
    float maxSpeedX;
    float maxSpeedY;
    float acceleration;
    float deceleration;

    int maxHealth;
    int currentHealth;
    float armor;
    float maxArmor;
    bool hasArmor;
    bool abduction;
    float abductionTimer;


    // Animation speeds
    float walkFrameSpeed;
    float runFrameSpeed;

    // Player state flags
    bool isMoving;
    bool facingRight;
    bool isRunning;
    bool isAiming;
    bool isShooting;
    bool isDead;
    bool isReloading;
    bool isRolling;
    bool canShoot;
    bool hasWatch;
    bool hasGun;
    bool hasRaygun;
    bool hasShotgun;
    bool hasMac10;
    bool hasShovel;
    bool hasCrowbar;
    bool hasBadge;
    bool hasWhiskey;
    bool outline;
    bool holdingDown;
    bool dropping;
    bool enter_car;
    bool enter_train;
    bool arriving;
    bool can_take_damage;
    bool canRoll;
    bool AllowGuns;
    bool validatedPassword;
    bool necroTechSearched;
    bool onElevator;
    bool hasPills;
    bool step;

    bool canSwing;
    bool swinging;
    float swingTimer;
    bool chargeSoundPlayed;

    // Timers & counters
    float rollTimer;
    float chargeTimer;
    int raygunSize;
    float dropTimer;
    int bulletCount;
    int shells;
    int autoAmmo;
    int revolverAmmo;
    float hitTimer;
    float reloadTimer;
    double LastTapTimeLeft;
    double LastTapTimeRight;
    double tapInterval;
    float shotgunReloadTime;
    int money;
    Emitter bloodEmitter;

    // Weapon variables
    WeaponType currentWeapon;
    int shotgunBulletCount;
    int revolverBulletCount;
    int mac10BulletCount;

    bool charging;
    float maxChargeTime;


    // Constructor
    Player();

    
    //make what can be private private. 

    // public Methods

    void take_damage(int damage);
    void UpdateMovement();
    void DrawPlayer();
    bool CheckIfOnPlatform();
    bool CheckHit(Vector2 previousBulletPosition, Vector2 currentBulletPosition, Vector2 bulletSize);

 
private:
    void HandleInput(float speed);
    void DrawChargeBar(Vector2 offset);
    void UpdateCharge(float deltaTime, bool charging);
    void reloadLogic(float deltaTime);
    void playerPhysics(float deltaTime);
    void updateAnimations();
    void shootLogic();
    void Reload();
    
};

extern Player player; // Declare the player globally

#endif  // PLAYER_H
