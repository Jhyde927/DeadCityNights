#ifndef PARTICLE_H
#define PARTICLE_H

#include <raylib.h>
#include <vector>

struct Particle {
    Vector2 position;
    Vector2 velocity;
    float lifetime;
    Color color;
};

class Emitter {
public:
    Vector2 position;
    std::vector<Particle> particles;

    Emitter(Vector2 pos);
    
    void SpawnBlood(int amount, bool facingRight); // Blood spray in one direction
    void SpawnExplosion(int amount, Color explosionColor); // Full circular explosion

    void UpdateParticles(float deltaTime);
    void DrawParticles() const;

private:
    float particleLifetime = 0.8f;
    float speedMin = 25.0f, speedMax = 150.0f;
    float angleSpread = 30.0f; // Used for blood spray
};

#endif // PARTICLE_H
