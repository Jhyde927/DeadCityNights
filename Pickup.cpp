#include "Pickup.h"
#include <algorithm>

// Define the global pickups vector (memory allocated here)
std::vector<Pickup> pickups;

// Constructor definition
Pickup::Pickup(Vector2 pos, PickupType type, Texture2D tex, int val)
    : position(pos), type(type), texture(tex), value(val) {}

// Draw the pickup
void Pickup::Draw() {
    if (!isCollected) {
        DrawTexturePro(
            texture,
            {0, 0, (float)texture.width, (float)texture.height}, // Full texture source
            {position.x + 8, position.y, 32, 32}, // Draw at position, scale to 32x32
            {0, 0}, 0, WHITE
        );
    }
}

// Update pickup state
void Pickup::Update(Player& player) {
    float distance_to = abs(player.position.x - position.x);
    if (!isCollected && distance_to < 10) {
        ApplyEffect(player);
        isCollected = true;
    }
}

// Apply effect when picked up
void Pickup::ApplyEffect(Player& player) {
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
            player.money += value;
            PlaySound(SoundManager::getInstance().GetSound("moneyUp"));       
            break;
        case PickupType::REVOLVER_AMMO:
            player.revolverAmmo += value;
            PlaySound(SoundManager::getInstance().GetSound("reload"));
            break;
    }
}

// Function to spawn a pickup
void SpawnPickup(Vector2 position, PickupType type, Texture2D texture) {
    int value = 0;
    switch (type) {
        case PickupType::SHOTGUN_AMMO: value = 8; break;
        case PickupType::NINE_MM_AMMO: value = 30; break;
        case PickupType::MONEY: value = 100; break;
        case PickupType::REVOLVER_AMMO: value = 18; break;
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
