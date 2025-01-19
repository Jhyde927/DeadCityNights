// NPC.h
#ifndef NPC_H
#define NPC_H

#include <raylib.h>
#include "Player.h"
#include <string>


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

    NPC* targetNPC;
 


    NPC(Texture2D npcTexture, Vector2 startPos, float npcSpeed, AnimationState initialAnimation, bool isActive, bool isZombie);
    
    void Update(Player& player, GameState& gameState);
    void Render(ShaderResources& shaders);
    void ClickNPC(Vector2 mousePosition, Camera2D& camera, Player& player, GameState& gameState);
    void SetAnimationState(AnimationState newState);
    void SetDestination(float minX, float maxX);
    bool CheckHit(Vector2 previousPosition, Vector2 bulletPosition, Vector2 bulletSize);
    void HandleNPCInteraction(Player& player, GameState& gameState);
    void HandlePolice(Player& player, float& distanceToPlayer);
    void HandleZombie(Player& player, float& distanceToPlayer);
    void HandleGhost(Player& player, float& distanceToPlayer);
    void HandleMiB(Player& player, float& distanceToPlayer);
    void HandleRobot(Player& player, float& distanceToPlayer);
    void TakeDamage(int damage, Player& player);
    void HandleAnimationLogic();
    //void MoveNPC(Player& player, GameState& gameState);
};

#endif
