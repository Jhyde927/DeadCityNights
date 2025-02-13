// GameResources.h

#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include <raylib.h>  // Include Raylib to use Texture2D and Font types





// Struct to hold game resources
struct GameResources {
    Texture2D background;
    Texture2D foreground;
    Texture2D midground;
    Texture2D manTexture;
    Texture2D walkSheet;
    Texture2D runSheet;
    Texture2D reloadSheet;
    Texture2D apartment;
    Texture2D road;
    Texture2D car;
    Texture2D carSheet;
    Texture2D lightBeam;
    Texture2D lightCone;
    Texture2D cemetery;
    Texture2D inventorySlot;
    Texture2D cemeteryBackground;
    Texture2D cemeteryTrees;
    Texture2D cemeteryMidground;
    Texture2D cemeteryForeground;
    Texture2D carKey;
    Texture2D npcTexture;
    Texture2D breakLight;
    Texture2D truck;
    Texture2D businessSheet;
    Texture2D woman2Sheet;
    Texture2D womanSheet;
    Texture2D zombieSheet;
    Texture2D dealerSheet;
    Texture2D policeSheet;
    Texture2D shootSheet;
    Texture2D OpenDrawer;
    Texture2D Revolver;
    Texture2D CarKeys;
    Texture2D handCursor;
    Texture2D reticle;
    Texture2D ShotGunSheet;
    Texture2D ShotgunReload;
    Texture2D Drugs;
    Texture2D vacantLot;
    Texture2D hoboSheet;
    Texture2D shovel;
    Texture2D shovelWorld;
    Texture2D shotgunPickup;
    Texture2D shotgunIcon;
    Texture2D pills;
    Texture2D FortuneTellerSheet;
    Texture2D cemeteryKey;
    Texture2D GraveyardGate;
    Texture2D GraveyardForeground;
    Texture2D GreaveyardMidground;
    Texture2D deadZombie;
    Texture2D Badge;
    Texture2D ComputerScreen;
    Texture2D ghostSheet;
    Texture2D magicDoorSheet;
    Texture2D AstralBackground;
    Texture2D AstralMidground;
    Texture2D AstralClouds;
    Texture2D AstralForeground;
    Texture2D AstralClouds2;
    Texture2D EarthSheet;
    Texture2D jumpSheet;
    Texture2D healthBorder;
    Texture2D batSheet;
    Texture2D platformTexture;
    Texture2D mibSheet;
    Texture2D whiskey;
    Texture2D midgroundLot;
    Texture2D UFOsheet;
    Texture2D lightBar;
    Texture2D ParkForeground;
    Texture2D ParkMidground;
    Texture2D ParkBuildings;
    Texture2D MidBuildings;
    Texture2D shootSheetAuto;
    Texture2D reloadSheetAuto;
    Texture2D Mac10;
    Texture2D Mac10pickup;
    Texture2D subwayForeground;
    Texture2D subwayBackground;
    Texture2D subwayMidground;
    Texture2D train;
    Texture2D ntForeground;
    Texture2D robotSheet;
    Texture2D LobbyForeground;
    Texture2D elevatorSheet;
    Texture2D floorNumberSheet;
    Texture2D officeBackground;
    Texture2D officeSheet;
    Texture2D frankSheet;
    Texture2D crowbarSheet;
    Texture2D crowbarIcon;
    Texture2D boxSheet;
    Texture2D shellsPickup;
    Texture2D autoPickup;
    Texture2D BigBadge;
    

    Font defaultFont;


        // Load all game resources
    void Load();

    // Unload all game resources
    void Unload();

};

extern GameResources resources;  // ✅ Declare external global instance


#endif // GAMERESOURCES_H
