#include "Particle.h"
#include <raymath.h>
#include <cmath>
#include <iostream>

//constructor
Emitter::Emitter(Vector2 pos) {
    position = pos;
}

// **Set max particles**
void Emitter::SetMaxParticles(int max) {
    maxParticles = max;
}


// **Blood spray effect** 
void Emitter::SpawnBlood(int amount, Color color, bool facingRight) {
    float baseAngle = facingRight ? 0.0f : 180.0f; 

    for (int i = 0; i < amount; i++) {
        if (static_cast<int>(particles.size()) >= maxParticles) {
            particles.erase(particles.begin()); // Remove oldest particle if over limit
        }

        Particle p;
        p.position = position;

        float randomAngle = baseAngle + GetRandomValue(-angleSpread, angleSpread);
        float radians = randomAngle * DEG2RAD;

        float speed = GetRandomValue(speedMin, speedMax) / 100.0f;
        p.velocity = { cosf(radians) * speed, sinf(radians) * speed };

        p.lifetime = particleLifetime;
        p.color = color;

        particles.push_back(p);
        
        
    }
}

// **Explosion effect** 
void Emitter::SpawnExplosion(int amount, Color explosionColor) {
    for (int i = 0; i < amount; i++) {
        if (static_cast<int>(particles.size()) >= maxParticles) {
            particles.erase(particles.begin()); // Remove oldest particle
        }

        Particle p;
        p.position = position;

        float randomAngle = GetRandomValue(0, 360);
        float radians = randomAngle * DEG2RAD;

        float speed = GetRandomValue(speedMin, speedMax) / 100.0f;
        if (explosionColor.r == YELLOW.r && explosionColor.g == YELLOW.g && explosionColor.b == YELLOW.b){
            speed = speed * 4; //if the color is yellow, it's a grenade explosion and should be faster
        }
        p.velocity = { cosf(radians) * speed, sinf(radians) * speed };

        p.lifetime = particleLifetime;
        p.color = explosionColor;

        particles.push_back(p);
    }
}

void Emitter::UpdateParticles(float deltaTime) {
    for (size_t i = 0; i < particles.size(); ) {
        particles[i].position.x += particles[i].velocity.x * deltaTime * 60;
        particles[i].position.y += particles[i].velocity.y * deltaTime * 60;
        particles[i].velocity.y += 1.0f * deltaTime; //possibly higher gravity would look better. 
        particles[i].lifetime -= deltaTime;

        if (particles[i].position.y > 750 || particles[i].lifetime <= 0) { //if life time <= 0 or particle is below ground level, erase it. 
            particles.erase(particles.begin() + i); // don't increment i, I guess removing mid loop messes with the indexes
        } else {
            i++; // safe to move to next
        }
    }
}


// Draw all particles
void Emitter::DrawParticles() const {
    for (const auto& p : particles) {
        DrawRectangle(p.position.x, p.position.y, 2, 2, p.color); //2x2 square for thicker pixelated blood
    
    }
}
