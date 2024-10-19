// Platform.cpp

#include "Platform.h"

Platform::Platform(float x, float y, float width, float height, Color color) {
    rect = { x, y, width, height };
    this->color = color;
}

void Platform::Draw() const {
    DrawRectangleRec(rect, color);
    
}
