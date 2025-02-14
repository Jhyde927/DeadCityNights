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
    MONEY,


};

class Pickup {
public:
    Vector2 position;
    PickupType type;
    bool isCollected = false;
    float pickupRadius = 24.0f;
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
                {position.x+8, position.y, 32, 32}, // Draw at position, scale to 32x32
                {0, 0}, 0, WHITE
            );

           
        }
    }

    // Check if player is close enough to pick up the item
    void Update(Player& player) {
        float distance_to = abs(player.position.x - position.x);
        if (!isCollected && distance_to < 10) {

            ApplyEffect(player);
           
            isCollected = true;
        }
    }

private:
    void ApplyEffect(Player& player) {
        switch (type) {
            case PickupType::SHOTGUN_AMMO:
                PlaySound(SoundManager::getInstance().GetSound("reload"));
                player.shells += value;
                break;
            case PickupType::NINE_MM_AMMO:
                PlaySound(SoundManager::getInstance().GetSound("reload"));
                player.autoAmmo += value;
                break;

            case PickupType::MONEY:
                player.money += 100;
                PlaySound(SoundManager::getInstance().GetSound("moneyUp"));       
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
        case PickupType::NINE_MM_AMMO: value = 15; break;
        case PickupType::MONEY: value = 100; break;


    }
    pickups.emplace_back(position, type, texture, value);
}

// Function to update all pickups
void UpdatePickups() {
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
