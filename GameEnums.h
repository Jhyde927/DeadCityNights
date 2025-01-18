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
    LOT, 
    GRAVEYARD,
    ASTRAL,
    PARK,
    SUBWAY,
    NECROTECH
};

enum TrainState {
    MovingToStation,
    SlowingDown,
    StoppedAtStation,
    SpeedingUp,
    MovingFromStation,
    WaitingBeforeLoop
};

enum TransitionState {
    NONE,
    FADE_IN,
    FADE_OUT,
    
};

enum PauseState {
    GAME_RUNNING,
    GAME_PAUSED
};

#endif // GAME_ENUMS_H
