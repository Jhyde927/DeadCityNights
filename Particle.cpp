#include "Particle.h"
#include <raymath.h>
#include <cmath>

//constructor
Emitter::Emitter(Vector2 pos) {
    position = pos;
}

// **Set max particles**
void Emitter::SetMaxParticles(int max) {
    maxParticles = max;
}

// **Blood spray effect** (limited number of particles)
void Emitter::SpawnBlood(int amount, bool facingRight) {
    float baseAngle = facingRight ? 0.0f : 180.0f; 

    for (int i = 0; i < amount; i++) {
        if (particles.size() >= maxParticles) {
            particles.erase(particles.begin()); // Remove oldest particle if over limit
        }

        Particle p;
        p.position = position;

        float randomAngle = baseAngle + GetRandomValue(-angleSpread, angleSpread);
        float radians = randomAngle * DEG2RAD;

        float speed = GetRandomValue(speedMin, speedMax) / 100.0f;
        p.velocity = { cosf(radians) * speed, sinf(radians) * speed };

        p.lifetime = particleLifetime;
        p.color = RED;

        particles.push_back(p);
    }
}

// **Explosion effect** (limited number of particles)
void Emitter::SpawnExplosion(int amount, Color explosionColor) {
    for (int i = 0; i < amount; i++) {
        if (particles.size() >= maxParticles) {
            particles.erase(particles.begin()); // Remove oldest particle
        }

        Particle p;
        p.position = position;

        float randomAngle = GetRandomValue(0, 360);
        float radians = randomAngle * DEG2RAD;

        float speed = GetRandomValue(speedMin, speedMax) / 100.0f;
        p.velocity = { cosf(radians) * speed, sinf(radians) * speed };

        p.lifetime = particleLifetime;
        p.color = explosionColor;

        particles.push_back(p);
    }
}

// Update particles and remove expired ones
void Emitter::UpdateParticles(float deltaTime) {
    for (size_t i = 0; i < particles.size();) {
        particles[i].position.x += particles[i].velocity.x * deltaTime * 60;
        particles[i].position.y += particles[i].velocity.y * deltaTime * 60;
        particles[i].velocity.y += .1 * deltaTime;//very low gravity seems to work best. 

        particles[i].lifetime -= deltaTime;

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
        //DrawPixel(p.position.x, p.position.y, p.color);
        DrawRectangle(p.position.x, p.position.y, 2, 2, RED); //2x2 square for thicker pixelated blood
    }
}
