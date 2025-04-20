#ifndef BULLET_H
#define BULLET_H

#include <raylib.h>
#include "Player.h"  
#include "NPC.h"
#include "Particle.h"
#include <unordered_set> //for raygun



struct Bullet {
    Vector2 position;
    Vector2 previousPosition;
    Vector2 direction;
    Vector2 size;
    std::unordered_set<NPC*> hitNPCs; //save which NPC the bullet hit, as to only subtract bullet health once per NPC hit. (for raygun)
    
    float speed;
    bool isActive;
    float lifeTime;
    float damage;
    bool laser;
    bool raygun;
    bool isFireball;
    int health;
    bool canExplode = true;
    
    int currentFrame = 0; // bullets can have animated sprites. 
    float frameTimer = 0.0f;
    float frameTime = 0.1f;
    int maxFrames = 4;


    
    
};

const int MAX_BULLETS = 100;  // Max number of bullets // bullets are used for both the revolver and shotgun
//We have a pool of bullets that get actived when fired then deactivated after 2 seconds or on hit. 
//MAX_BULLETS is max for all bullets in world. 

extern Bullet bullets[MAX_BULLETS];  // Declare the global bullets array
Vector2 RotateTowards(Vector2 current, Vector2 target, float maxAngle); //homing fireballs
void FireBullet(Player& player, bool spread, float damage, bool laser, bool raygun);  // Declare the FireBullet function
void NPCfireBullet(NPC& npc, bool spread, float damage, bool laser, bool fireBall);
void UpdateBullets();             // Function to update bullet positions
void DrawBullets();   


         


#endif
