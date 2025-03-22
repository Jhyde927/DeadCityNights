#ifndef BOX_H
#define BOX_H

#include "GameResources.h"
#include <raylib.h>
#include "Particle.h"
#include "SoundManager.h"
#include "Pickup.h"
#include <iostream>
#include "Inventory.h"

class Box {
public:
    Vector2 position;
    GameState scene;
    bool destroyed = false;
    bool canTakeDamage = true;
    int health = 3;
    Texture2D texture;
    int frameWidth = 32;
    int frameHeight = 32;
    int maxFrames = 3;
    float cooldownTimer = 0.0f;
    float damageCooldown = 0.2f;

    Emitter boxEmitter;

    Box() = default;
    Box(Vector2 pos, Texture2D tex, GameState sceneType);

    void Update(float deltaTime);
    void Draw();
    void TakeDamage(int damage);
};

#endif
