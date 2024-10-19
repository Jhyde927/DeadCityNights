// Platform.h

#ifndef PLATFORM_H
#define PLATFORM_H

#include "raylib.h"

class Platform {
public:
    Rectangle rect;  // The rectangle representing the platform's position and size
    Color color;     // The color of the platform

    Platform(float x, float y, float width, float height, Color color);
    void Draw() const;
};

#endif  // PLATFORM_H
