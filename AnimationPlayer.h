#ifndef ANIMATIONPLAYER_H
#define ANIMATIONPLAYER_H

#include <raylib.h>

// Enum for different animation states
enum AnimationState {
    IDLE,
    WALK,
    RUN,
    DEATH,
    ATTACKING,
    RISING,
    DEATH2
};

class AnimationPlayer {
public:
    Texture2D* spriteSheet;   // Pointer to texture (each NPC should pass its own texture)
    int frameWidth = 64;      // Each frame width (fixed size)
    int frameHeight = 64;     // Each frame height (fixed size)
    int maxFrames = 7;        // Max frames per row
    float frameSpeed = 0.1f;  // Time per frame
    float frameTimer = 0.0f;  // Tracks animation timing
    int currentFrame = 0;     // Current frame in the row
    AnimationState currentState = IDLE; // Default animation state

    AnimationPlayer() {}

    AnimationPlayer(Texture2D* texture) {
        spriteSheet = texture;
    }

    // Update animation frame logic
    void Update(float deltaTime) {
        frameTimer += deltaTime;
        if (frameTimer >= frameSpeed) {
            frameTimer -= frameSpeed;
            currentFrame++;

            // Reset to first frame if we go beyond max
            if (currentFrame >= maxFrames) {
                currentFrame = 0;
            }
        }
    }

    // Draw animation at given position
    void Draw(Vector2 position, bool facingRight) {
        if (!spriteSheet) return;  // Safety check

        int row = static_cast<int>(currentState); // Get row from enum
        Rectangle sourceRec = {
            static_cast<float>(currentFrame * frameWidth),  // X position in sprite sheet
            static_cast<float>(row * frameHeight),          // Y position (animation row)
            static_cast<float>(frameWidth),                 // Width
            static_cast<float>(frameHeight)                 // Height
        };

        // Flip horizontally if facing left
        if (!facingRight) {
            sourceRec.width = -frameWidth; 
        }

        Rectangle destRec = { position.x, position.y, frameWidth, frameHeight };

        DrawTexturePro(*spriteSheet, sourceRec, destRec, { 0, 0 }, 0.0f, WHITE);
    }

    // Set the animation state
    void SetAnimation(AnimationState state) {
        if (state != currentState) {
            currentState = state;
            currentFrame = 0;  // Reset animation when switching states
            frameTimer = 0.0f;
        }
    }
};

#endif // ANIMATIONPLAYER_H
