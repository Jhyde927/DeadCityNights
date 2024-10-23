// Platform.cpp

#include "Platform.h"


Platform::Platform(float x, float y, float width, float height, Color color) {
    rect = { x, y, width, height };
    this->color = color;
}

void Platform::Draw() const {
    DrawRectangleRec(rect, color);
    
    
}

void Platform::DrawPlatformTexture(Texture2D& texture, Rectangle& platformRect) {
    // Define the source rectangle (the portion of the texture to draw) // wait we can draw only a portion of textures..we could animate this parameter
    Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };

    // Define the destination rectangle (where and how big to draw the texture)
    Rectangle destRec = { 
        platformRect.x, //position
        platformRect.y, 
        platformRect.width, //destination rect width
        platformRect.height 
    };

    // The origin is (0, 0) since we're not rotating
    Vector2 origin = { 0.0f, 0.0f };

    // Draw the texture stretched to fit the platform rectangle
    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
}
