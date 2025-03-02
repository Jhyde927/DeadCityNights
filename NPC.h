// NPC.h
#ifndef NPC_H
#define NPC_H

#include <raylib.h>
#include "Player.h"
#include <string>
#include "Particle.h"
#include "Grenade.h"




class Player;  // Forward declaration of Player
enum AnimationState {
    IDLE,
    WALK,
    RUN, 
    DEATH,
    ATTACKING,
    RISING,
    DEATH2
};



class NPC {
public:
    Vector2 position;
    AnimationState currentAnimation;   
    Texture2D texture;

    int currentFrame;
    float frameCounter;
    float frameSpeed;
    bool facingRight;
    bool patrollingRight;
    bool patrolling;
    float idleTime;
    bool isZombie;
    bool isDying;      // Flag to check if NPC is in dying state
    float deathTimer;  // Timer for death animation
    float riseTimer;
    bool interacting;
    Vector2 destination;

    float distanceToPlayer;
    
    float speed;
    bool isActive;
    int maxHealth;
    int health;
    float hitTimer;  // New: Timer to track hit state
    bool talked;
    std::string speech;
    bool dealer;
    bool police;
    bool agro;
    bool attacking;
    bool hobo;
    bool ghost;
    bool teller;
    bool bat;
    bool MiB;
    bool office;
    bool frank;
    bool CanSpawnZombie;
    int clickCount;
    int interactions;
    float talkTimer;
    float ghostAlpha;
    bool hasTarget;
    bool isTargeted;
    float detectionRange; // Set detection range for zombies
    float detectionRangeBat;
    bool highLight;
    bool robot;
    bool can_shoot;
    float shootTimer;
    bool validPassword;
    bool trigger;
    bool lobbyNPC;
    bool zRight;
    float targetedTimer;
    bool agroZombie;
    bool cyberZombie;
    float animationTimer;
    bool isMoving;
    bool scientist;
    bool scienceJr;
    bool alien;

    // Add an emitter for each NPC
    Emitter bloodEmitter;

    NPC* targetNPC; //zombie's target
 
    NPC(Texture2D npcTexture, Vector2 startPos, float npcSpeed, AnimationState initialAnimation, bool isActive, bool isZombie);
    
    void Update();
    void Render();
    void ClickNPC();
    void SetAnimationState(AnimationState newState);
    void SetDestination(float minX, float maxX);
    bool CheckHit(Vector2 previousPosition, Vector2 bulletPosition, Vector2 bulletSize);
    void HandleNPCInteraction();
    void HandlePolice();
    void HandleZombie();
    void HandleGhost();
    void HandleAlien();
    void HandleCyberZombie();
    void HandleMiB();
    void HandleRobot();
    void TakeDamage(int damage);
    void HandleAnimationLogic();
    void ghostMoves();
    //void MoveNPC(Player& player, GameState& gameState);
};

#endif
