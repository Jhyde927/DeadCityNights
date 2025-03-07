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
    MAC10
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
    float stunTimer;
    float walkSpeed;
    float runSpeed;
    int currentFrame;
    float frameCounter;
    float frameSpeed;
    float maxSpeedX;
    float maxSpeedY;
    float acceleration;
    float deceleration;
    
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
    bool canShoot;
    bool hasWatch;
    bool hasGun;
    bool hasShotgun;
    bool hasMac10;
    bool hasShovel;
    bool hasBadge;
    bool hasWhiskey;
    bool outline;
    bool holdingDown;
    bool dropping;
    bool enter_car;
    bool enter_train;
    bool arriving;
    bool can_take_damage;
    bool AllowGuns;
    bool validatedPassword;
    bool necroTechSearched;
    bool onElevator;
    bool hasPills;
    bool step;
    bool hasCrowbar;
    bool canSwing;
    bool swinging;
    float swingTimer;

    // Timers & counters
    float dropTimer;
    int bulletCount;
    int shells;
    int autoAmmo;
    int revolverAmmo;
    int maxHealth;
    int currentHealth;
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



    // Constructor
    Player();

    

    // Methods
    void take_damage(int damage);
    void UpdateMovement();
    void DrawPlayer();
    void HandleInput(float speed);
    void Reload();
    void reloadLogic(float deltaTime);
    void playerPhysics(float deltaTime);
    void updateAnimations();
    bool CheckIfOnPlatform();
    bool CheckHit(Vector2 previousBulletPosition, Vector2 currentBulletPosition, Vector2 bulletSize);
    void shootLogic();
 

    
};

extern Player player; // Declare the player globally

#endif  // PLAYER_H
