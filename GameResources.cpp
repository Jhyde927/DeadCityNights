#include "GameResources.h"

GameResources resources;  // Define the global instance

// Load all game resources
void GameResources::Load() {
    background = LoadTexture("assets/Background.png");
    foreground = LoadTexture("assets/Foreground.png");
    midground = LoadTexture("assets/Midground.png");
    manTexture = LoadTexture("assets/Man.png");
    walkSheet = LoadTexture("assets/WalkSheet.png");
    runSheet = LoadTexture("assets/RunSheet.png");
    apartment = LoadTexture("assets/Apartment.png");
    road = LoadTexture("assets/Road.png");
    car = LoadTexture("assets/Car.png");
    carSheet = LoadTexture("assets/Car-Sheet.png");
    reloadSheet = LoadTexture("assets/reloadSheet.png");
    lightBeam = LoadTexture("assets/LightBeam.png");
    lightCone = LoadTexture("assets/LightCone.png");
    cemetery = LoadTexture("assets/Cemetery.png");
    inventorySlot = LoadTexture("assets/InventorySlot.png");
    cemeteryBackground = LoadTexture("assets/Cemetery(backGround).png");
    cemeteryTrees = LoadTexture("assets/Cemetery(Trees).png");
    cemeteryMidground = LoadTexture("assets/Cemetery(midGround).png");
    cemeteryForeground = LoadTexture("assets/Cemetery(forground).png");
    carKey = LoadTexture("assets/carKey.png");
    npcTexture = LoadTexture("assets/npcSheet.png");
    breakLight = LoadTexture("assets/breakLight.png");
    truck = LoadTexture("assets/Truck.png");
    businessSheet = LoadTexture("assets/businessSheet.png");
    womanSheet = LoadTexture("assets/womanSheet.png");
    dealerSheet = LoadTexture("assets/DealerSheet.png");
    zombieSheet = LoadTexture("assets/zombieSheet.png");
    shootSheet = LoadTexture("assets/shootSheet.png");
    OpenDrawer = LoadTexture("assets/OpenDrawer.png");
    Revolver = LoadTexture("assets/Revolver.png");
    CarKeys = LoadTexture("assets/CarKeys.png");
    handCursor = LoadTexture("assets/hand.png");
    reticle = LoadTexture("assets/reticle.png");
    ShotGunSheet = LoadTexture("assets/ShotGunSheet.png");
    ShotgunReload = LoadTexture("assets/ShotGunReload.png");
    Drugs = LoadTexture("assets/Drugs.png");
    policeSheet = LoadTexture("assets/PoliceSheet.png");
    vacantLot = LoadTexture("assets/EmptyLot.png");
    hoboSheet = LoadTexture("assets/HoboSheet.png");
    shovel = LoadTexture("assets/shovel.png");
    shovelWorld = LoadTexture("assets/shovelWorld.png");
    shotgunPickup = LoadTexture("assets/ShotGunPickup.png");
    shotgunIcon = LoadTexture("assets/shotgunIcon.png");
    pills = LoadTexture("assets/pills.png");
    FortuneTellerSheet = LoadTexture("assets/FortuneTellerSheet.png");
    woman2Sheet = LoadTexture("assets/woman2Sheet.png");
    cemeteryKey = LoadTexture("assets/CemeteryKey.png");
    GraveyardGate = LoadTexture("assets/GraveyardGate.png");
    GraveyardForeground = LoadTexture("assets/GraveyardForeground.png");
    GreaveyardMidground= LoadTexture("assets/GraveyardMidground.png");
    deadZombie = LoadTexture("assets/DeadZombie.png");
    Badge = LoadTexture("assets/Badge.png");
    ComputerScreen = LoadTexture("assets/ComputerScreen.png");
    ghostSheet = LoadTexture("assets/ghostSheet.png");
    magicDoorSheet = LoadTexture("assets/MagicDoorSheet.png");
    AstralBackground = LoadTexture("assets/AstralBackground.png");
    AstralMidground = LoadTexture("assets/AstralMidGround.png");
    AstralClouds = LoadTexture("assets/AstralClouds.png");
    AstralForeground = LoadTexture("assets/AstralForeground.png");
    AstralClouds2 = LoadTexture("assets/AstralClouds2.png");
    EarthSheet = LoadTexture("assets/EarthSpin-Sheet.png");
    jumpSheet = LoadTexture("assets/JumpSheet.png");
    healthBorder = LoadTexture("assets/HealthBoarder.png");
    batSheet = LoadTexture("assets/batSheet.png");
    platformTexture = LoadTexture("assets/platform(128x32).png");
    mibSheet = LoadTexture("assets/mibSheet.png");
    whiskey = LoadTexture("assets/Whiskey.png");
    midgroundLot = LoadTexture("assets/MidGroundLot.png");
    UFOsheet = LoadTexture("assets/UFOsheet.png");
    lightBar = LoadTexture("assets/lightBar.png");
    ParkForeground = LoadTexture("assets/Park(foreground).png");
    ParkMidground = LoadTexture("assets/Park(midground).png");
    ParkBuildings = LoadTexture("assets/Park(buildings).png");
    MidBuildings = LoadTexture("assets/MidBuildings.png");
    shootSheetAuto = LoadTexture("assets/shootSheetAuto.png");
    reloadSheetAuto = LoadTexture("assets/reloadSheetAuto.png");
    Mac10 = LoadTexture("assets/Mac10.png");
    Mac10pickup = LoadTexture("assets/Mac10pickup.png");
    subwayForeground = LoadTexture("assets/subwayForground.png");
    subwayBackground = LoadTexture("assets/subwayBackground.png");
    subwayMidground = LoadTexture("assets/subwayMidground.png");
    train = LoadTexture("assets/Train.png");
    ntForeground = LoadTexture("assets/NTforeground.png");
    robotSheet = LoadTexture("assets/robotSheet.png");
    LobbyForeground = LoadTexture("assets/LobbyForeground.png");
    elevatorSheet = LoadTexture("assets/elevatorSheet.png");
    floorNumberSheet = LoadTexture("assets/floorNumberSheet.png");
    officeBackground = LoadTexture("assets/officeBackground.png");
    officeSheet = LoadTexture("assets/officeSheet.png");
    frankSheet = LoadTexture("assets/frankSheet.png");
    crowbarSheet = LoadTexture("assets/crowbarSheet.png");
    crowbarIcon = LoadTexture("assets/crowbarIcon.png");
    boxSheet = LoadTexture("assets/boxSheet.png");
    shellsPickup = LoadTexture("assets/shellsPickup.png");
    autoPickup = LoadTexture("assets/9mm.png");
    BigBadge = LoadTexture("assets/BigBadge.png");
    money = LoadTexture("assets/money.png");
    pocketWatch = LoadTexture("assets/pocketWatchIcon.png");
    crowbarWorld = LoadTexture("assets/crowbarWorld.png");
    pocketWatchWorld = LoadTexture("assets/pocketWatchWorld.png");
    cyberZombieSheet = LoadTexture("assets/cyberZombieSheet.png");
    grenadeSheet = LoadTexture("assets/grenadeSheet.png");
    special38 = LoadTexture("assets/38special.png");
    labBackground = LoadTexture("assets/LaboratoryBackground.png");
    tankSheet = LoadTexture("assets/tankSheet.png");
    consoleSheet = LoadTexture("assets/consoleSheet.png");
    monitorSheet = LoadTexture("assets/monitorSheet.png");
    scienceSheet = LoadTexture("assets/scienceSheet.png");
    scienceJrSheet = LoadTexture("assets/scienceJrSheet.png");
    explosionSheet = LoadTexture("assets/explosionSheet.png");
    armorIcon = LoadTexture("assets/armor.png");
    UFObackground = LoadTexture("assets/UFObackground.png");
    alienSheet = LoadTexture("assets/AlienSheet.png");
    tankExplodeSheet = LoadTexture("assets/tankExplodeSheet.png");
    menuButton = LoadTexture("assets/MenuButton.png");
    shootRaygunSheet = LoadTexture("assets/shootRaygunSheet.png");
    raygunIcon = LoadTexture("assets/rayGun.png");
    raygunPickup = LoadTexture("assets/raygunPickup.png");
    light64 = LoadTexture("assets/Light(64).png");
    penthouseBackground = LoadTexture("assets/PenthouseBackground.png");
    penthouseForeground = LoadTexture("assets/PenthouseForeground.png");
    penthouseMidground = LoadTexture("assets/PenthouseMidground.png");
    penthouseMidBack = LoadTexture("assets/PenthouseMidBack.png");
    CEOsheet = LoadTexture("assets/CEOsheet.png");
    flipSheet = LoadTexture("assets/flipSheet.png");
    demonSheet = LoadTexture("assets/demonSheet.png");
    fireballSheet = LoadTexture("assets/fireballSheet.png");
    energyBallSheet = LoadTexture("assets/energyBallSheet.png");
}

// Unload all game resources
void GameResources::Unload() {
    UnloadTexture(background);
    UnloadTexture(foreground);
    UnloadTexture(midground);
    UnloadTexture(walkSheet);
    UnloadTexture(runSheet);
    UnloadTexture(manTexture);
    UnloadTexture(apartment);
    UnloadTexture(carSheet);
    UnloadTexture(car);
    UnloadTexture(road);
    UnloadTexture(cemetery);
    UnloadTexture(inventorySlot);
    UnloadTexture(cemeteryBackground);
    UnloadTexture(cemeteryTrees);
    UnloadTexture(cemeteryMidground);
    UnloadTexture(cemeteryForeground);
    UnloadTexture(npcTexture);
    UnloadTexture(lightBeam);
    UnloadTexture(lightCone);
    UnloadTexture(breakLight);
    UnloadTexture(truck);
    UnloadTexture(businessSheet);
    UnloadTexture(womanSheet);
    UnloadTexture(zombieSheet);
    UnloadTexture(shootSheet);
    UnloadTexture(OpenDrawer);
    UnloadTexture(Revolver);
    UnloadTexture(CarKeys);
    UnloadTexture(handCursor);
    UnloadTexture(reticle);
    UnloadTexture(ShotGunSheet);
    UnloadTexture(ShotgunReload);
    UnloadTexture(Drugs);
    UnloadTexture(policeSheet);
    UnloadTexture(vacantLot);
    UnloadTexture(hoboSheet);
    UnloadTexture(shovel);
    UnloadTexture(shovelWorld);
    UnloadTexture(shotgunPickup);
    UnloadTexture(shotgunIcon);
    UnloadTexture(pills);
    UnloadTexture(FortuneTellerSheet);
    UnloadTexture(woman2Sheet);
    UnloadTexture(cemeteryKey);
    UnloadTexture(GraveyardGate);
    UnloadTexture(GraveyardForeground);
    UnloadTexture(GreaveyardMidground);
    UnloadTexture(deadZombie);
    UnloadTexture(Badge);
    UnloadTexture(ComputerScreen);
    UnloadTexture(ghostSheet);
    UnloadTexture(magicDoorSheet);
    UnloadTexture(AstralBackground);
    UnloadTexture(AstralMidground);
    UnloadTexture(AstralClouds);
    UnloadTexture(AstralForeground);
    UnloadTexture(AstralClouds2);
    UnloadTexture(EarthSheet);
    UnloadTexture(jumpSheet);
    UnloadTexture(healthBorder);
    UnloadTexture(batSheet);
    UnloadTexture(platformTexture);
    UnloadTexture(mibSheet);
    UnloadTexture(whiskey);
    UnloadTexture(midgroundLot);
    UnloadTexture(UFOsheet);
    UnloadTexture(lightBar);
    UnloadTexture(ParkForeground);
    UnloadTexture(ParkMidground);
    UnloadTexture(ParkBuildings);
    UnloadTexture(MidBuildings);
    UnloadTexture(shootSheetAuto);
    UnloadTexture(reloadSheetAuto);
    UnloadTexture(Mac10);
    UnloadTexture(Mac10pickup);
    UnloadTexture(subwayBackground);
    UnloadTexture(subwayForeground);
    UnloadTexture(subwayMidground);
    UnloadTexture(train);
    UnloadTexture(ntForeground);
    UnloadTexture(robotSheet);
    UnloadTexture(LobbyForeground); 
    UnloadTexture(elevatorSheet);
    UnloadTexture(floorNumberSheet);
    UnloadTexture(officeBackground);
    UnloadTexture(officeSheet);
    UnloadTexture(frankSheet);
    UnloadTexture(crowbarSheet);
    UnloadTexture(crowbarIcon);
    UnloadTexture(boxSheet);
    UnloadTexture(shellsPickup);
    UnloadTexture(autoPickup);
    UnloadTexture(BigBadge);
    UnloadTexture(money);
    UnloadTexture(pocketWatch);
    UnloadTexture(crowbarWorld);
    UnloadTexture(pocketWatchWorld);
    UnloadTexture(cyberZombieSheet);
    UnloadTexture(grenadeSheet);
    UnloadTexture(special38);
    UnloadTexture(labBackground);
    UnloadTexture(tankSheet);
    UnloadTexture(consoleSheet);
    UnloadTexture(monitorSheet);
    UnloadTexture(scienceSheet);
    UnloadTexture(scienceJrSheet);
    UnloadTexture(explosionSheet);
    UnloadTexture(armorIcon);
    UnloadTexture(UFObackground);
    UnloadTexture(alienSheet);
    UnloadTexture(tankExplodeSheet);
    UnloadTexture(menuButton);
    UnloadTexture(shootRaygunSheet);
    UnloadTexture(raygunIcon);
    UnloadTexture(raygunPickup);
    UnloadTexture(light64);
    UnloadTexture(penthouseBackground);
    UnloadTexture(penthouseForeground);
    UnloadTexture(penthouseMidground);
    UnloadTexture(penthouseMidBack);
    UnloadTexture(CEOsheet);
    UnloadTexture(flipSheet);
    UnloadTexture(demonSheet);
    UnloadTexture(fireballSheet);
    UnloadTexture(energyBallSheet);
}
