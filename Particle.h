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
    
    void SpawnBlood(int amount, bool facingRight); // Blood spray in one direction, opposite of facingRight
    void SpawnExplosion(int amount, Color explosionColor); // Full circular explosion

    void UpdateParticles(float deltaTime);
    void DrawParticles() const;
    void SetMaxParticles(int max); 

private:
    float particleLifetime = 2.0f;
    float speedMin = 1.0f, speedMax = 30.0f;
    float angleSpread = 30.0f; // Used for blood spray
    int maxParticles = 200; 
};

#endif // PARTICLE_H
