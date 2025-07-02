// Platform.h

#pragma once

#include "raylib.h"

class Platform {
public:
    Rectangle rect;  // The rectangle representing the platform's position and size
    Color color;     // The color of the platform

    Platform(float x, float y, float width, float height, Color color);

    void DrawPlatformTexture(Texture2D& texture, Rectangle& platformRect);
    void Draw() const;
};
