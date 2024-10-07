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
    float speed;
    int currentFrame;
    float frameCounter;
    float frameSpeed;
    bool facingRight;
    bool patrollingRight;
    bool patrolling;
    float idleTime;
    bool isActive;
    bool isZombie;
    bool isDying;      // Flag to check if NPC is in dying state
    float deathTimer;  // Timer for death animation
    float riseTimer;
    bool interacting;
    Vector2 destination;
    Texture2D texture;
    AnimationState currentAnimation;
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
    int clickCount;
    int interactions;


    NPC(Texture2D npcTexture, Vector2 startPos, float npcSpeed, AnimationState initialAnimation, bool isActive, bool isZombie);
    void Update(Player& player);
    void Render();
    void ClickNPC(Vector2 mousePosition, Camera2D& camera, Player& player);
    void SetAnimationState(AnimationState newState);
    void SetDestination(float minX, float maxX);
    bool CheckHit(Vector2 previousPosition, Vector2 bulletPosition, Vector2 bulletSize);
    void HandleNPCInteraction(Player& player);
    void HandlePolice(Player& player, float& distanceToPlayer, bool& hasTarget);
    void HandleZombie(Player& player, float& distanceToPlayer, bool& hasTarget);
    void HandleGhost(Player& player, float& distanceToPlayer, bool& hasTarget);
    void TakeDamage(int damage);
};

#endif
