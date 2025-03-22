#include "box.h"

Box::Box(Vector2 pos, Texture2D tex, GameState sceneType)
    : position(pos), texture(tex), scene(sceneType) {}

void Box::Update(float deltaTime) {
    boxEmitter.UpdateParticles(deltaTime);

    if (!canTakeDamage) {
        cooldownTimer -= deltaTime;
        if (cooldownTimer <= 0.0f) {
            canTakeDamage = true;
        }
    }
}

void Box::Draw() {
    int currentFrame = maxFrames - health;
    if (currentFrame >= maxFrames) currentFrame = maxFrames;

    Rectangle sourceRect = {
        (float)(currentFrame * frameWidth), 0, 
        (float)frameWidth, (float)frameHeight
    };
    Rectangle destRect = { position.x, position.y, 24, 24 };
    Vector2 origin = { 0, 0 };

    DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);

    if (!destroyed){
        boxEmitter.DrawParticles();
    }
}

void Box::TakeDamage(int damage) {
    if (canTakeDamage && !destroyed) {
        health -= damage;
        canTakeDamage = false;
        cooldownTimer = damageCooldown;
        boxEmitter.position = position + Vector2{8, 8};
        boxEmitter.SpawnExplosion(10, BROWN);
        PlaySound(SoundManager::getInstance().GetSound("woodBreak"));
        
        Vector2 center_pos = {position.x - 8, position.y};

        if (health <= 0) {
            destroyed = true;

            int number = rand() % 4;
            switch (number) {
                case 0:
                    SpawnPickup(center_pos, PickupType::REVOLVER_AMMO, resources.special38);
                    break;
                case 1:
                    SpawnPickup(center_pos, PickupType::SHOTGUN_AMMO, resources.shellsPickup);
                    break;
                case 2:
                    SpawnPickup(center_pos, PickupType::NINE_MM_AMMO, resources.autoPickup);
                    break;
                case 3:
                    SpawnPickup(center_pos, PickupType::MONEY, resources.money);
                    break;
            }
        }
    }
}
