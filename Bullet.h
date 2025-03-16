#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>
#include "Player.h"  
#include "NPC.h"
#include <unordered_set> //for raygun

struct Bullet {
    Vector2 position;
    Vector2 previousPosition;
    Vector2 direction;
    Vector2 size;
    std::unordered_set<NPC*> hitNPCs; //save which NPC the bullet hit, as to only subtract bullet health once per NPC hit. 

    float speed;
    bool isActive;
    float lifeTime;
    float damage;
    bool laser;
    bool raygun;
    int health;
    
};

const int MAX_BULLETS = 50;  // Max number of bullets // bullets are used for both the revolver and shotgun
//We have a pool of bullets that get actived when fired then deactivated after 2 seconds or on hit. 
//MAX_BULLETS is max for all bullets in world. 

extern Bullet bullets[MAX_BULLETS];  // Declare the global bullets array

void FireBullet(Player& player, bool spread, float damage, bool laser, bool raygun);  // Declare the FireBullet function
void NPCfireBullet(NPC& npc, bool spread, float damage, bool laser);
void UpdateBullets();             // Function to update bullet positions
void DrawBullets();               // Function to draw bullets

#endif
