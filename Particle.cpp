#include "Particle.h"
#include <raymath.h>
#include <cmath>

// Constructor
Emitter::Emitter(Vector2 pos) : position(pos) {}

// **Blood spray effect** (spawns particles in one direction)
void Emitter::SpawnBlood(int amount, bool facingRight) {
    float baseAngle = facingRight ? 0.0f : 180.0f; // Right = 0°, Left = 180°

    for (int i = 0; i < amount; i++) {
        Particle p;
        p.position = position;

        // Randomized spread angle
        float randomAngle = baseAngle + GetRandomValue(-angleSpread, angleSpread);
        float radians = randomAngle * DEG2RAD;

        // Set velocity based on angle
        float speed = GetRandomValue(speedMin, speedMax) / 100.0f;
        p.velocity = { cosf(radians) * speed, sinf(radians) * speed };

        p.lifetime = particleLifetime;
        p.color = RED;

        particles.push_back(p);
    }
}

// **Explosion effect** (spawns particles in all directions)
void Emitter::SpawnExplosion(int amount, Color explosionColor) {
    for (int i = 0; i < amount; i++) {
        Particle p;
        p.position = position;

        // Generate random direction (0° to 360°)
        float randomAngle = GetRandomValue(0, 360);
        float radians = randomAngle * DEG2RAD;

        // Set velocity in all directions
        float speed = GetRandomValue(speedMin, speedMax) / 100.0f;
        p.velocity = { cosf(radians) * speed, sinf(radians) * speed };

        p.lifetime = particleLifetime;
        p.color = explosionColor;

        particles.push_back(p);
    }
}

// Update particle movement
void Emitter::UpdateParticles(float deltaTime) {
    for (size_t i = 0; i < particles.size();) {
        particles[i].position.x += particles[i].velocity.x * deltaTime * 60;
        particles[i].position.y += particles[i].velocity.y * deltaTime * 60;

        //particles[i].velocity.y += 50 * deltaTime; // Apply gravity  NO GRAVITY

        particles[i].lifetime -= deltaTime;

        // Remove expired particles
        if (particles[i].lifetime <= 0) {
            particles.erase(particles.begin() + i);
        } else {
            i++;
        }
    }
}

// Draw all particles
void Emitter::DrawParticles() const {
    for (const auto& p : particles) {
        DrawPixel(p.position.x, p.position.y, p.color);
    }
}
