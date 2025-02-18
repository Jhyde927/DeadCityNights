#ifndef GRENADE_H
#define GRENADE_H

#include <vector>
#include "raylib.h"
#include "Particle.h"


class Grenade {
public:
    Vector2 position;
    Vector2 velocity;
    bool exploded = false;
    float lifetime = 2.0f;  // Time before explosion
    float explosionRadius = 40.0f; // Area of effect
    float gravity = 500.0f; // Simulated gravity effect
    float frameTimer = 0.0f; 
    int currentFrame = 0;
    float frameSpeed = 0.1f; // Time per frame
    int maxFrames = 4; // Assuming 4 frames in your sprite sheet
    float explosionTimer = 0.0f; // Grenade stays alive for 300ms after exploding
    bool isActive = true;
    bool facingRight = true;

    Emitter exEmitter;


    Grenade(Vector2 pos, Vector2 vel);  // Constructor

    void Update(float deltaTime);  // Updates grenade physics
    void Draw();                   // Draws the grenade
    void Explode();                 // Handles explosion

private:
    bool hasBounced = false; // Only allow one bounce
};

// Global grenade vector for tracking all grenades
extern std::vector<Grenade> grenades;

#endif // GRENADE_H
