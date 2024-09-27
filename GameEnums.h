// GameEnums.h
#ifndef GAME_ENUMS_H
#define GAME_ENUMS_H

// Define GameState enum
enum GameState {
    OUTSIDE,
    APARTMENT,
    ROAD,
    CEMETERY,
    WORK, 
    LOT
};

enum TransitionState {
    NONE,
    FADE_IN,
    FADE_OUT,
    
};

#endif // GAME_ENUMS_H
