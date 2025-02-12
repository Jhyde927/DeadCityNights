#ifndef PICKUP_H
#define PICKUP_H

#include <raylib.h>
#include <vector>
#include "Player.h"
#include <algorithm>
#include <iostream>
#include "SoundManager.h"

// Enum for different types of pickups
enum class PickupType {
    SHOTGUN_AMMO,
    NINE_MM_AMMO,
    PAIN_PILLS
};

class Pickup {
public:
    Vector2 position;
    PickupType type;
    bool isCollected = false;
    float pickupRadius = 32.0f;
    Texture2D texture;
    int value; // Amount of ammo/health this pickup gives

    
    // Constructor
    Pickup(Vector2 pos, PickupType type, Texture2D tex, int val) {
        position = pos;
        this->type = type;
        texture = tex;
        value = val;
    }


    // Draw the pickup
    void Draw() {
        if (!isCollected) {
            DrawTexturePro(
                texture,
                {0, 0, (float)texture.width, (float)texture.height}, // Full texture source
                {position.x, position.y, 32, 32}, // Draw at position, scale to 32x32
                {0, 0}, 0, WHITE
            );
        }
    }

    // Check if player is close enough to pick up the item
    void Update(Player& player) {
        if (!isCollected && CheckCollisionPointCircle(player.position, position, pickupRadius)) {
            std::cout << "pickup\n";
            ApplyEffect(player);
            PlaySound(SoundManager::getInstance().GetSound("reload"));
            isCollected = true;
        }
    }

private:
    void ApplyEffect(Player& player) {
        switch (type) {
            case PickupType::SHOTGUN_AMMO:
                player.shells += value;
                break;
            case PickupType::NINE_MM_AMMO:
                player.autoAmmo += value;
                break;
            case PickupType::PAIN_PILLS:
                player.currentHealth = player.maxHealth; // Fully heals the player
                break;
        }
    }
};

// Global vector to store active pickups
std::vector<Pickup> pickups;

// Function to spawn a pickup
void SpawnPickup(Vector2 position, PickupType type, Texture2D texture) {
    int value = 0;
    switch (type) {
        case PickupType::SHOTGUN_AMMO: value = 4; break;
        case PickupType::NINE_MM_AMMO: value = 10; break;
        case PickupType::PAIN_PILLS: value = 1; break;
    }
    pickups.emplace_back(position, type, texture, value);
}

// Function to update all pickups
void UpdatePickups(Player& player) {
    for (auto& pickup : pickups) {
        pickup.Update(player);
    }
    // Remove collected pickups
    pickups.erase(std::remove_if(pickups.begin(), pickups.end(), 
                 [](const Pickup& p) { return p.isCollected; }), 
                 pickups.end());
}

// Function to draw all pickups
void DrawPickups() {
    for (auto& pickup : pickups) {
        pickup.Draw();
    }
}

#endif // PICKUP_H
