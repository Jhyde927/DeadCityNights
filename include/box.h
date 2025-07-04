#pragma once

#include "GameResources.h"
#include <raylib.h>
#include "Particle.h"
#include "SoundManager.h"
#include "Pickup.h"
#include <iostream>


class Box {
public:
    Vector2 position;
    Texture2D texture;
    GameState scene;
    bool destroyed = false;
    bool canTakeDamage = true;
    int health = 3;
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
