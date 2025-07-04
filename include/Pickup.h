#pragma once

#include <raylib.h>
#include <vector>
#include "Player.h"
#include "SoundManager.h"

// Enum for different types of pickups
enum class PickupType {
    SHOTGUN_AMMO,
    NINE_MM_AMMO,
    REVOLVER_AMMO,
    MONEY
};

// Pickup class
class Pickup {
public:
    Vector2 position;
    PickupType type;
    bool isCollected = false;
    float pickupRadius = 16.0f;
    Texture2D texture;
    int value; // Amount of ammo/money

    // Constructor
    Pickup(Vector2 pos, PickupType type, Texture2D tex, int val);

    // Methods
    void Draw();
    void Update(Player& player);

private:
    void ApplyEffect(Player& player);
};

// Global vector to store active pickups (extern declaration)
extern std::vector<Pickup> pickups;

// Function declarations
void SpawnPickup(Vector2 position, PickupType type, Texture2D texture);
void UpdatePickups();
void DrawPickups();
