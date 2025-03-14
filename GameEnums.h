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
    NECROTECH,
    LOBBY,
    OFFICE,
    LAB,
    ALIEN,
};

enum class NPCType {
    //not used yet. Refactor createNPC to take a NPCType as a parameter instead of isZombie. 
    GENERIC,
    BUSINESSMAN,
    HOBO,
    POLICEMAN, 
    DEALER,
    TELLER,
    WOMAN,
    WOMAN2,
    ZOMBIE,
    CYBER_ZOMBIE,
    MIB,
    GHOST,
    BAT,
    ALIEN,
    SCIENTIST,
    JR_SCIENTIST,


    // Add more NPC types as needed
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

extern GameState gameState;  // Declare global gameState
//extern PauseState currentPauseState;

#endif // GAME_ENUMS_H
