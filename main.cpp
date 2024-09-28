#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "NPC.h"
#include "Player.h"
#include "GameResources.h"
#include "Bullet.h"
#include "GameEnums.h"
#include "SoundManager.h"
#include "GameCalendar.h"
#include <string>
#include <cstdlib>  // For rand and srand
#include <ctime>    // For seeding rand

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"



//Remember: The Law is One. 

//start_pos = 1922, 700
//apartment_pos = 2256, 700
//car_start = 1710, 700 - 32
//Enter_car = 1738, 700
//Enter_road = 1340, 700
//key_pos 380, 666
//street_light = 1913, 500?
int apartmentX = 2256;
int vacantLotX = 2753;
int vacantExitX = 2762;
bool over_lot = false;
bool over_exit = false;
//cemetery_start 1743, 700
bool runOnce = true;
bool streetSounds = false;
bool over_apartment = false;
bool over_car = false;
bool over_shotgun = false;
bool show_carUI = false;
bool leave_apartment = false;
bool leave_cemetery = false;
bool buttonCemetery = false;
bool drawShovel = true;
bool drawShotgun = true;
bool buttonWork = false;
bool buttonTavern = false;
bool gotoWork = false;
bool hasWorked = false;
bool buttonSleep = false;
bool hasSlept = false;
bool showAPUI = false;
bool playOwl = false;
bool can_talk = true;
bool dealer = false;
bool can_sell_drugs = true;
bool applyShader = false;
bool drunk = false;
bool glitch = false;
//bool enter_car = false;
bool move_car = false;
bool showHealthbar = false;
bool reverse_road = false;
bool has_car_key = false;
bool npcWalk = false;
bool openDrawer = false;
bool raiseZombies = true;
bool zombieWave2 = false;
bool zombieWave3 = false;
bool show_dbox = false;
float dboxTime = 10.0;
float inventoryPositionX = 0.0f;
float inventoryPositionY = 0.0f;
float inventoryTargetX = 0.0f;
float inventoryTargetY = 0.0f;

int remainingZombiesToSpawn = 0;    // Tracks remaining zombies to spawn
float spawnTimer = 0.0f;            // Timer for spawning
float nextSpawnDelay = 0.0f;        // Time delay between spawns

float blackoutTime = 2.0f;  // Time to stay blacked out
float blackoutTimer = 0.0f; // Timer to keep track of blackout period

Color customBackgroundColor = {32, 42, 63, 255};  //Same Color as street background image. 

int money = 100;
int displayMoney = 100;
bool showInventory = false;
const int INVENTORY_SIZE = 6;  // Define the size of the inventory
std::string inventory[INVENTORY_SIZE] = {"", "", "", "", "", ""};

std::string phrase = "Hello";

const int screenWidth = 1024;
const int screenHeight = 1024;

Color purplishGrey = {128, 96, 128, 255};  // RGBA format: (R, G, B, A)

Vector2 carKeysPos = {(screenWidth/2) - 100, 655}; // remember positions need to based on screenwidth incase of resolution change. 
Vector2 drawerPos = {screenWidth/2 + 129, 730};
Vector2 cemetery_start{2746, 700};
Vector2 car_pos = {3000, 710};
Vector2 truck_pos = {512, 710};

Vector2 pc_start_pos = Vector2{1710, 668};
Vector2 pstart_by_car = Vector2{1738, 700};
Vector2 dboxPosition;
Color ApartmentBgColor {41, 48, 63, 255};
std::vector<NPC> npcs;
std::vector<NPC> zombies;
std::vector<NPC>hobos;

GameState gameState = OUTSIDE;

TransitionState transitionState = NONE;
float fadeAlpha = 1.0f;  // Starts fully opaque
float fadeSpeed = 0.02f; // Speed of fade (adjust as needed)
bool firstTransition = true;



void PrintVector2(const Vector2& vec) {
    std::cout << "(" << vec.x << ", " << vec.y << ")" << "\n";
}


struct PlayerCar {
    Vector2 position;
    float carSpeed;
    int currentFrame = 0;
    bool facingLeft = true;

};


// Function to initialize and load resources
void LoadGameResources(GameResources& resources) {
    resources.background = LoadTexture("assets/Background.png");
    resources.foreground = LoadTexture("assets/Foreground.png");
    resources.midground = LoadTexture("assets/Midground.png");
    resources.manTexture = LoadTexture("assets/Man.png");
    resources.walkSheet = LoadTexture("assets/WalkSheet.png");
    resources.runSheet = LoadTexture("assets/RunSheet.png");
    resources.apartment = LoadTexture("assets/Apartment.png");
    resources.road = LoadTexture("assets/Road.png");
    resources.car = LoadTexture("assets/Car.png");
    resources.carSheet = LoadTexture("assets/Car-Sheet.png");
    resources.reloadSheet = LoadTexture("assets/reloadSheet.png");
    resources.lightBeam = LoadTexture("assets/LightBeam.png");
    resources.lightCone = LoadTexture("assets/LightCone.png");
    resources.cemetery = LoadTexture("assets/Cemetery.png");
    resources.inventorySlot = LoadTexture("assets/InventorySlot.png");
    resources.cemeteryBackground = LoadTexture("assets/Cemetery(backGround).png");
    resources.cemeteryTrees = LoadTexture("assets/Cemetery(Trees).png");
    resources.cemeteryMidground = LoadTexture("assets/Cemetery(midGround).png");
    resources.cemeteryForeground = LoadTexture("assets/Cemetery(forground).png");
    resources.carKey = LoadTexture("assets/carKey.png");
    resources.npcTexture = LoadTexture("assets/npcSheet.png");
    resources.breakLight = LoadTexture("assets/breakLight.png");
    resources.truck = LoadTexture("assets/Truck.png");
    resources.businessSheet = LoadTexture("assets/businessSheet.png");
    resources.womanSheet = LoadTexture("assets/womanSheet.png");
    resources.dealerSheet = LoadTexture("assets/DealerSheet.png");
    resources.zombieSheet = LoadTexture("assets/zombieSheet.png");
    resources.shootSheet = LoadTexture("assets/shootSheet.png");
    resources.OpenDrawer = LoadTexture("assets/OpenDrawer.png");
    resources.Revolver = LoadTexture("assets/Revolver.png");
    resources.CarKeys = LoadTexture("assets/CarKeys.png");
    resources.handCursor = LoadTexture("assets/hand.png");
    resources.reticle = LoadTexture("assets/reticle.png");
    resources.ShotGunSheet = LoadTexture("assets/ShotGunSheet.png");
    resources.ShotgunReload = LoadTexture("assets/ShotGunReload.png");
    resources.Drugs = LoadTexture("assets/Drugs.png");
    resources.policeSheet = LoadTexture("assets/PoliceSheet.png");
    resources.vacantLot = LoadTexture("assets/EmptyLot.png");
    resources.hoboSheet = LoadTexture("assets/HoboSheet.png");
    resources.shovel = LoadTexture("assets/shovel.png");
    resources.shovelWorld = LoadTexture("assets/shovelWorld.png");
    resources.shotgunPickup = LoadTexture("assets/ShotGunPickup.png");
    resources.shotgunIcon = LoadTexture("assets/shotgunIcon.png");
}

void UnloadGameResources(GameResources& resources){
    UnloadTexture(resources.background);
    UnloadTexture(resources.foreground);
    UnloadTexture(resources.midground);
    UnloadTexture(resources.walkSheet);
    UnloadTexture(resources.runSheet);
    UnloadTexture(resources.manTexture);
    UnloadTexture(resources.apartment);
    UnloadTexture(resources.carSheet);
    UnloadTexture(resources.car);
    UnloadTexture(resources.road);
    UnloadTexture(resources.cemetery);
    UnloadTexture(resources.inventorySlot);
    UnloadTexture(resources.cemeteryBackground);
    UnloadTexture(resources.cemeteryTrees);
    UnloadTexture(resources.cemeteryMidground);
    UnloadTexture(resources.cemeteryForeground);
    UnloadTexture(resources.npcTexture);
    UnloadTexture(resources.lightBeam);
    UnloadTexture(resources.lightCone);
    UnloadTexture(resources.breakLight);
    UnloadTexture(resources.truck);
    UnloadTexture(resources.businessSheet);
    UnloadTexture(resources.womanSheet);
    UnloadTexture(resources.zombieSheet);
    UnloadTexture(resources.shootSheet);
    UnloadTexture(resources.OpenDrawer);
    UnloadTexture(resources.Revolver);
    UnloadTexture(resources.CarKeys);
    UnloadTexture(resources.handCursor);
    UnloadTexture(resources.reticle);
    UnloadTexture(resources.ShotGunSheet);
    UnloadTexture(resources.ShotgunReload);
    UnloadTexture(resources.Drugs);
    UnloadTexture(resources.policeSheet);
    UnloadTexture(resources.vacantLot);
    UnloadTexture(resources.hoboSheet);
    UnloadTexture(resources.shovel);
    UnloadTexture(resources.shovelWorld);
    UnloadTexture(resources.shotgunPickup);
    UnloadTexture(resources.shotgunIcon);
   
}


void InitializePlayerCar(PlayerCar& player_car){
    player_car.position = {1710, 700-32};
    player_car.carSpeed = 100;
    player_car.currentFrame = 0;
}

// Function to add an item to the first available slot in the inventory
void AddItemToInventory(const std::string& item, std::string inventory[], int inventorySize) {
    for (int i = 0; i < inventorySize; i++) {
        if (inventory[i].empty()) {
            inventory[i] = item;  // Add the item to the first empty slot
            break;
        }
    }
}

void EraseInventoryItem(std::string inventory[], int index, int inventorySize) {
    if (index >= 0 && index < inventorySize) {
        inventory[index] = "";  // Erase the item by setting it to an empty string
    }
}


void MonitorMouseClicks(Player& player, GameCalendar& calendar){

    //Debug mousePosition
    // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    //     Vector2 mousePosition = GetMousePosition();
    //     std::cout << "MousePos: ";
    //     PrintVector2(mousePosition);
    // }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if (gameState == APARTMENT){

            Vector2 mousePosition = GetMousePosition();  // Get the mouse position
            Vector2 computerPos = {screenWidth/2 - 10, 512+75};
            if (buttonSleep && !hasSlept){
                calendar.AdvanceDay(); ////Go to sleep
                buttonSleep = false;
                hasWorked = false;
                hasSlept = true;
                drunk = false;  //Effects ware off when you sleep
                applyShader = false;
                glitch = false;
                transitionState = FADE_OUT; //fades out to street for now.
                player.currentHealth = player.maxHealth; //recover hitpoints after sleeping. 
                for (NPC& npc : npcs){
                    if (npc.police){
                        npc.agro = false; // loose the cops after sleeping. 
                        
                    }
                } 
            }
            
            // key Rectangle 
            Rectangle textureBounds = {
                carKeysPos.x,      // X position
                carKeysPos.y,      // Y position
                static_cast<float>(64),  // Width of the texture
                static_cast<float>(64)  // Height of the texture
            };

            
            // drawer rec
            Rectangle drawerBounds = {
                drawerPos.x,      // X position
                drawerPos.y,      // Y position
                static_cast<float>(128),  // Width of the texture
                static_cast<float>(64)  // Height of the texture
            };
            // computer rec
            Rectangle ComputerBounds = {
                computerPos.x,      // X position
                computerPos.y,      // Y position
                static_cast<float>(64),  // Width of the texture
                static_cast<float>(64)  // Height of the texture
            };

            // Check if the mouse is over the texture
            if (CheckCollisionPointRec(mousePosition, textureBounds)&& !has_car_key) {
                showInventory = true;
                AddItemToInventory("carKeys", inventory, INVENTORY_SIZE);
                has_car_key = true;
                PlaySound(SoundManager::getInstance().GetSound("Keys"));
            }

            if (CheckCollisionPointRec(mousePosition, drawerBounds)&& !openDrawer){
                openDrawer = true;
                PlaySound(SoundManager::getInstance().GetSound("OpenDrawer"));
                if (!player.hasGun){
                    AddItemToInventory("Gun", inventory, INVENTORY_SIZE);
                    showInventory = true;
                    player.hasGun = true;
                    PlaySound(SoundManager::getInstance().GetSound("reload"));

                }
                

            }else if (CheckCollisionPointRec(mousePosition, drawerBounds) && openDrawer){
                openDrawer = false;
                PlaySound(SoundManager::getInstance().GetSound("CloseDrawer"));
            }

            if (CheckCollisionPointRec(mousePosition, ComputerBounds) && !showAPUI){
                showAPUI = true;
            }else{
                showAPUI = false;
            }



    }else if (gameState == OUTSIDE){
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if (player.enter_car && buttonCemetery){ //press buttons cemetery
                move_car = true;
                show_carUI = false;
            }else if (player.enter_car && buttonWork){//button press work
                //do something
                gotoWork = true;
                move_car = true;
                hasWorked = true;
            }
        }

    }else if (gameState == CEMETERY){
        if (player.enter_car && buttonCemetery){//button press street
           //move_car = true;
            transitionState = FADE_OUT;
            raiseZombies = true; //reset zombie waves. So returning player will trigger them again. 
            zombieWave2 = false;
            zombieWave3 = false;

        }else if (player.enter_car && buttonWork){ //button press work
            gameState = WORK;
            transitionState = FADE_OUT;
        }
    }


    }

}

void addMoney(int amount){
    money += amount;
}

void updateMoney(){
    if (displayMoney < money){
        displayMoney++;
    }else if (displayMoney > money){
        displayMoney--;
    }

}
void DrawMoney(){
    std::string smoney = "$ " + std::to_string(displayMoney);
    DrawText(smoney.c_str(), screenWidth/2+400, 25, 30, WHITE);
    updateMoney();
}

//Factory function to creat NPCs
NPC CreateNPC(Texture2D texture, Vector2 position, float speed, AnimationState initialState, bool isActive, bool isZombie) {
    return NPC(texture, position, speed, initialState, isActive, isZombie);
}


// Generates a random position along the x-axis, relative to the player's position
Vector2 GetRandomSpawnPositionX(Vector2 playerPos, float minDistance, float maxDistance) {
    // Randomly pick an x offset within the given distance range
    float randomXOffset = minDistance + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxDistance - minDistance)));

    // Randomly decide whether the zombie spawns to the left or right of the player
    bool spawnOnRight = rand() % 2 == 0;

    // Adjust the spawn position based on the player's position and direction
    float spawnX = spawnOnRight ? playerPos.x + randomXOffset : playerPos.x - randomXOffset;

    return Vector2{spawnX, playerPos.y};  // Keep the same y position as the player
}

void StartZombieSpawn(int zombie_count){
    remainingZombiesToSpawn = zombie_count;
    spawnTimer = 0.0f; //reset timer
    nextSpawnDelay = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 3.0f));  // Random delay between 1-4 seconds

    glitch = true; //Activate glitch shader to make things more dramatic
}

void UpdateZombieSpawning(GameResources& resources, Player& player){
    if (remainingZombiesToSpawn > 0){
        spawnTimer += GetFrameTime();

        if (spawnTimer >= nextSpawnDelay){ // 
            Vector2 z_pos = GetRandomSpawnPositionX(player.position, 50.0f, 200.0f);  // Min/max distance from player
            int zombie_speed = 25;
            NPC zombie_npc = CreateNPC(resources.zombieSheet, z_pos, zombie_speed, RISING, true, true);
            zombie_npc.SetDestination(1000, 4000);
            zombies.push_back(zombie_npc);

            int soundIndex = rand() % 3; //zombie moans while rising.
            switch (soundIndex){  
                case 0:
                    PlaySound(SoundManager::getInstance().GetSound("moan1"));
                    break;
                
                case 1:
                    PlaySound(SoundManager::getInstance().GetSound("moan2"));
                    break;

                case 2:
                    PlaySound(SoundManager::getInstance().GetSound("moan3"));
                    break;
            }
 
            // Reset the spawn timer and set a new random delay
            spawnTimer = 0.0f;
            nextSpawnDelay = 1.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.0f));  // Random delay for the next zombie

            // Decrease the number of zombies left to spawn
            remainingZombiesToSpawn--;
        }
    }else{
        glitch = false; //glitch only runs if zombies are actively spawning. 
    }

}



void spawnZombies(GameResources& resources,int zombie_count){
    //spawn zombie
    int zombie_speed = 25;
    
    for (int i = 0; i < zombie_count; i++){
        Vector2 z_pos = {2500 + i * 200, 700};
        NPC zombie_npc = CreateNPC(resources.zombieSheet, z_pos, zombie_speed,RISING, true, true);
        zombie_npc.SetDestination(1000, 4000);
        zombies.push_back(zombie_npc);
        
        
    }

}



void HandleTransition(Player& player, PlayerCar& player_car, GameCalendar& calendar) {
    if (firstTransition) {
        fadeAlpha = 0.0f;  // Ensure it starts at 0 for the first fade
        firstTransition = false;  // Reset flag after first transition
    }


    if (transitionState == FADE_IN) {
        fadeAlpha -= fadeSpeed;  // Fade in gradually
        if (fadeAlpha <= 0.0f) {
            fadeAlpha = 0.0f;
            transitionState = NONE;  // Fade-in complete
        }
    } else if (transitionState == FADE_OUT) { //TRANSITION TO FADEOUT TO TRANSITION TO NEW SCENE, transition logic done here. 
        fadeAlpha += fadeSpeed;  // Fade out gradually
        if (fadeAlpha >= 1.0f) {
            fadeAlpha = 1.0f;

            // Start blackout timer when fully faded out // wait while blacked out for things to happen.
            blackoutTimer += GetFrameTime();
            if (blackoutTimer >= blackoutTime) {
                blackoutTimer = 0.0f;  // Reset blackout timer

                // Transition to the next state
                if (gameState == OUTSIDE) {
                    if (move_car && !gotoWork) { //car is moving, go to road
                        gameState = ROAD;
                        player_car.facingLeft = true; //leaving outside = face left
                        if (!reverse_road){
                            player_car.position.x = 900;
                        }
                        
                    } else if (move_car && gotoWork){ //movecar and gotowork = go to work
                    
                        gameState = WORK;
                        //do nothing
                        
                    } 
                    else if (gameState == OUTSIDE && player.isDead){ //Die outside to police, got to apartment
                        gameState = APARTMENT;
                        player.position.x = apartmentX;
                        player.currentHealth = player.maxHealth;
                        for (NPC& npc : npcs){
                            if (npc.police){
                                npc.agro = false; //turn off police agro if killed by police.
                                npc.attacking = false;
                                 
                            }
                        }
                    }else if (over_apartment) { //over apartment, go to apartment
                        gameState = APARTMENT;

                    }else if (over_lot){
                        gameState = LOT;
                    }

                } else if (gameState == APARTMENT) {
                    gameState = OUTSIDE; //go back oustide


                } else if (gameState == ROAD) {
                    //not reverseRoad go to cemetery

                    if (!reverse_road){
                        gameState = CEMETERY;
                        player_car.position.x = 3000;
                    }else{
                        //if reverseRoad go back to outside
                        gameState = OUTSIDE;
                        player_car.position.x = pc_start_pos.x;
                        player.position.x = 1738;
                        reverse_road = false;
                        leave_cemetery = false;
                    }




                } else if (gameState == CEMETERY) {
                    reverse_road = true;
                    player_car.facingLeft = false;
                    move_car = false;

                    //if not dead go to road
                    if (!player.isDead){
                        gameState = ROAD;
                        player_car.position.x = 100;
                    //if you die in the cemetery, go to apartment
                    }else{
                        gameState = APARTMENT;
                        player.position.x = apartmentX;
                        player.isDead = false;
                        player.currentHealth = player.maxHealth; //wait untill fade out to reset health
                        
                    }
             
                }else if (gameState == WORK){
                    //dont fade in or out. Let it fall through with gameState equaling outside
                    gotoWork = false;
                    move_car = false;
                    hasWorked = true;
                    gameState = OUTSIDE;
                    player.position.x = pstart_by_car.x;
                    addMoney(100);
                    
                }else if (gameState == LOT){
                    gameState = OUTSIDE;
                    player.position.x = vacantLotX;
                }

                
                if (!gotoWork){//dont fade in when at work. Fade in later
                    transitionState = FADE_IN;  // Start fading back in
                }
                
            }
        }
    }

    //Reset player position and health on death
    if (player.currentHealth <= 0) {
        
        player.isDead = true;
        transitionState = FADE_OUT;
        calendar.AdvanceDay();
        
    
    }

    // Draw the fade mask
    if (transitionState != NONE) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, fadeAlpha));
    }
}


Vector2 Lerp(Vector2 start, Vector2 end, float t) {
    return Vector2{
        start.x + t * (end.x - start.x),
        start.y + t * (end.y - start.y)
    };
}

void UpdateInventoryPosition(const Camera2D& camera, GameState& gameState) {
    // Static inventory position, relative to the camera offset
    inventoryPositionX = camera.offset.x;  // Adjust the X position relative to the screen (e.g., 200 pixels left of the center)
    if (gameState == APARTMENT){
        inventoryPositionY = camera.offset.y + 228;
    }else{
        inventoryPositionY = camera.offset.y + 228;  // Adjust the Y position (e.g., 300 pixels below the center)
    }
    
}



void RenderInventory(const GameResources& resources, std::string inventory[], int inventorySize, Player& player, Vector2& mousePosition) {
    int slotWidth = resources.inventorySlot.width;

    // Use integer values to snap to the nearest pixel, based on the camera-relative inventory position
    int startX = static_cast<int>(inventoryPositionX) - (slotWidth * inventorySize / 2);
    int startY = static_cast<int>(inventoryPositionY);

    // Draw each inventory slot
    for (int i = 0; i < inventorySize; i++) {
        int x = startX + (i * (slotWidth + 10));  // Offset each slot horizontally
        int y = startY;

        // Draw the inventory slot texture
        DrawTexture(resources.inventorySlot, x, y, WHITE);
        
       // Draw the item name if there's an item in the slot
        if (!inventory[i].empty()) {

            if (inventory[i] == "carKeys"){
                DrawTexture(resources.CarKeys, x, y, WHITE);
                
            }
            if (inventory[i] == "Gun"){
                DrawTexture(resources.Revolver, x, y, WHITE);
            }
            if (inventory[i] == "shotgun"){
                DrawTexture(resources.shotgunIcon, x, y, WHITE);
            }
            if (inventory[i] == "shovel"){
                DrawTexture(resources.shovel, x, y, WHITE);

                Rectangle shovelBounds = { //shovel button
                    x,      
                    y,      
                    static_cast<float>(64),  
                    static_cast<float>(64)  
                };

                if (CheckCollisionPointRec(mousePosition, shovelBounds)){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                     
                        if (player.position.x > 1890 && player.position.x < 1910){
                            std::cout << "DIGUP pills";
                        }
                    }
                }

            }

            if (inventory[i] == "Drugs"){
                DrawTexture(resources.Drugs, x, y, WHITE);
                Rectangle textureBounds = { //drug button
                    x,      
                    y,      
                    static_cast<float>(64),  
                    static_cast<float>(64)  
                };

                if (CheckCollisionPointRec(mousePosition, textureBounds)){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        inventory[i] = std::string("");  // erase drugs from the string
                        applyShader = true;
                    }
                }
            }

            //DrawText(inventory[i].c_str(), x + 10, y + 10, 20, WHITE);  // Display item name inside the slot
        }
    }
     
    //DrawText("Inventory", inventoryPositionX - 64, inventoryPositionY-22, 20, WHITE);
}



void CheckBulletNPCCollisions(std::vector<NPC>& npcs) {
    Vector2 bulletSize = {1, 1};  // Size of the bullet hitbox

    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].isActive) {  // Only check active bullets
            for (NPC& npc : npcs) {
                if (npc.isActive && npc.CheckHit(bullets[i].previousPosition, bullets[i].position, bulletSize)) {
                    // Collision detected
                    bullets[i].isActive = false;  // Deactivate the bullet
                    npc.TakeDamage(25);  // Apply 25 damage to the NPC
                    break;  // Exit loop since the bullet is deactivated
                }
            }
        }
    }
}


void DrawHUD(const Player& player) {
    float ammoY = 875.0;
    float ammoX = 140.0;
    if (player.currentWeapon == REVOLVER){
        DrawText(TextFormat("Ammo: %d", player.revolverBulletCount), screenWidth/2 + ammoX, ammoY, 20, WHITE); //screen space coordiantes
    }else if (player.currentWeapon == SHOTGUN){
        DrawText(TextFormat("Ammo: %d", player.shotgunBulletCount), screenWidth/2 + ammoX, ammoY, 20, WHITE); //screen space coordiantes 
    }
    
}


void MoveTraffic(GameResources resources){
    //TODO: rename function to MoveTraffic and add more vehicles. 
    int car_start = 4500;
    

    car_pos.x -= 150 * GetFrameTime();
    truck_pos.x += 150 * GetFrameTime();

    if (car_pos.x < 0) car_pos.x = car_start; //Loop back to car_start
 
    if (truck_pos.x > 4500) truck_pos.x = 512;
    
    DrawTexture(resources.car, car_pos.x, car_pos.y, WHITE);
    DrawTexture(resources.truck, truck_pos.x, truck_pos.y + 32, WHITE);
    
}

void DrawApartmentUI(GameCalendar&, Vector2& mousePosition, Camera2D& camera){
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);

    Vector2 ui_pos = {screenWidth/2-68, 512};
    DrawRectangle(ui_pos.x, ui_pos.y, 128, 64, customBackgroundColor);
    Color tint = WHITE;
    Rectangle textureBounds = {
        ui_pos.x,      // X position
        ui_pos.y,      // Y position
        static_cast<float>(128),  // Width of the texture
        static_cast<float>(16)  // Height of the texture
    };

    if (CheckCollisionPointRec(mousePosition, textureBounds)){
        tint = RED;
        
        buttonSleep = true;
    }else{
        buttonSleep = false;
    }

    if (hasSlept) tint = BLACK;
    DrawText("     Sleep", ui_pos.x, ui_pos.y, 20, tint);
    DrawText("     Email", ui_pos.x, ui_pos.y+21, 20, WHITE);
}



void DrawCarUI(PlayerCar& player_car, Vector2 mousePosition, Camera2D& camera, GameState& gameState){
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);
    Vector2 ui_pos = player_car.position;
    int ui_width = 96;
    int ui_height = 50;


    DrawRectangle(ui_pos.x, ui_pos.y - 17, ui_width, ui_height, customBackgroundColor);
    Color work_tint = WHITE;
    Color cemetery_tint = WHITE;
    Color tavern_tint = WHITE;
    Rectangle textureBounds = { //cemetery
        player_car.position.x,      
        player_car.position.y,      
        static_cast<float>(96),  
        static_cast<float>(16)  
    };

    Rectangle textureBounds2 = { //work
        player_car.position.x,      
        player_car.position.y+16,      
        static_cast<float>(96),  
        static_cast<float>(16)  
    };

    Rectangle textureBounds3 = { //Tavern
        player_car.position.x,      
        player_car.position.y-16,      
        static_cast<float>(96),  
        static_cast<float>(16)  
    };

    if (CheckCollisionPointRec(mouseWorldPos, textureBounds)){ //middle //cemetery/street
        cemetery_tint = RED;
        buttonCemetery = true;
    }else{
        buttonCemetery = false;
    }

    if (CheckCollisionPointRec(mouseWorldPos, textureBounds2) && !hasWorked && gameState == OUTSIDE){ //bottom
        work_tint = RED;
        buttonWork = true;
    }else{
        buttonWork = false;
    }

    if (CheckCollisionPointRec(mouseWorldPos, textureBounds3)){ //top
        tavern_tint = RED;
        buttonTavern = true;
    }else{
        buttonTavern = false;
    }
    if (gameState == OUTSIDE){
        DrawText("   Tavern", ui_pos.x, ui_pos.y-17, 16, tavern_tint);
        DrawText("   Cemetery", ui_pos.x, ui_pos.y, 16, cemetery_tint);
        if (!hasWorked){
            DrawText("   Work", ui_pos.x, ui_pos.y+17, 16, work_tint);
        }else{
            DrawText("    Work", ui_pos.x, ui_pos.y+17, 16, BLACK);
            
        }
        

    }else if (gameState == CEMETERY){
        
        DrawText("   Street", ui_pos.x, ui_pos.y, 16, cemetery_tint);
        //DrawText("Work", ui_pos.x, ui_pos.y+17, 16, work_tint);
    }

}

void DrawHealthBar(Vector2 position, int maxHealth, int currentHealth, int barWidth, int barHeight) {
    // Calculate health percentage
    float healthPercent = (float)currentHealth / maxHealth;

    // Define bar colors
    Color borderColor = WHITE;  // Border color
    Color barColor = WHITE;       // Color of the health bar itself

    if (healthPercent <= 0.3f){
        barColor = RED;
        borderColor = RED;
    }else{
        barColor = WHITE;
        borderColor = WHITE;
    }
    

    // Draw border
    //DrawText("HEALTH", position.x, position.y+30, 20, barColor);
    DrawRectangleLines(position.x, position.y+50, barWidth, barHeight, borderColor);
    // Draw health bar (adjust width based on health percentage)
    DrawRectangle(position.x, position.y+50, (int)(barWidth * healthPercent), barHeight, barColor);
}

void DrawDialogBox(Camera2D camera, int boxWidth, int boxHeight,int textSize){
    //int boxWidth = 256;
    //int boxHeight = 64;

    int offset = -64;
    int screen_offsetX = 16;
    int screen_offsetY = -55;
    Color tint = WHITE;
    if (dealer){
        boxWidth = 256;
        boxHeight = 128;
        offset = -135;
        screen_offsetX = 16;
        screen_offsetY = -128;

    }


    Vector2 screen_pos = GetWorldToScreen2D(dboxPosition, camera); // position to draw text and rectangle at. position is set to npc position
    DrawRectangle(screen_pos.x, screen_pos.y + offset, boxWidth, boxHeight, customBackgroundColor);
    DrawText(phrase.c_str(), screen_pos.x+ screen_offsetX, screen_pos.y + screen_offsetY, textSize, tint);
    
    if (money >= 100 && dealer && GuiButton((Rectangle){ screen_pos.x+16, screen_pos.y-64, 64,48 }, "BUY"))
        {
            if (can_sell_drugs){
                can_sell_drugs = false; // Dealer only has 1 drug for now. 
                addMoney(-100);
                AddItemToInventory("Drugs", inventory, INVENTORY_SIZE);
                for (NPC& npc : npcs)
                    if (npc.interacting){
                        npc.interacting = false;
                        npc.idleTime = 1;
                    }
                

            }
        }
}


void RenderCemetery(GameResources& resources,Player& player, PlayerCar& player_car, Camera2D& camera,Vector2 mousePosition, Shader& drunkShader, Shader& glowShader, Shader& glitchShader){
    int carMax = 2800;
    int carMin = 2765;
    
    playOwl = false; //reset owl
    // Maybe zombiewaves can be reset to false when exiting cemetery. 
    if (player.isAiming && IsKeyDown(KEY_F)) {
        // Handle keyboard-only aiming (e.g., using arrow keys or player movement keys)
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            player.facingRight = true;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            player.facingRight = false;
        }
    }else if (player.isAiming && !IsKeyDown(KEY_F)) {// If the player is not aiming with keyboard, allow mouse control to set the facing direction
        // Set facing direction based on mouse position
        player.facingRight = mousePosition.x > player.position.x; //this code does not seem to run
    }
    

    if (!player.enter_car && player.position.x < 1900 && !zombieWave3){ // walk to far left and zombies spawn again
        zombieWave3 = true;
        StartZombieSpawn(10);
    }
    if (!player.enter_car && player.position.x > 3000 && !zombieWave2){ //walk too far right and zombies spawn again
        zombieWave2 = true;
        StartZombieSpawn(10);
    }

    if (move_car){
        player_car.carSpeed = 100;
        
        player_car.position.x -= player_car.carSpeed * GetFrameTime();
        camera.target = Vector2{player_car.position.x, 700}; // offset camera target to be equal to player_pos.y
        player.position.x = player_car.position.x;
        //EndBlendMode();
    }
    
    if (!player.enter_car && raiseZombies){
        raiseZombies = false;
        
        StartZombieSpawn(5);
    }
        
    

    if (player_car.position.x < carMin && !leave_cemetery){
        move_car = false;
    }

   if (player.position.x > carMin && player.position.x < carMax){
        over_car = true;
        
   }else{
        over_car = false; 
   }
    // if (IsKeyPressed(KEY_SPACE)){//drive the car back to outside
    //     if (player.enter_car){
    //         transitionState = FADE_OUT;
            
    //         raiseZombies = true; //reset zombie waves. So returning player will trigger them again. 
    //         zombieWave2 = false;
    //         zombieWave3 = false;
    //         player.position = pstart_by_car;
    //         leave_cemetery = true;
    //         move_car = true;
            
    //     }
    // }

    BeginMode2D(camera);
    Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera);
    if (!IsKeyDown(KEY_F)){
        if (player.isAiming) player.facingRight = worldMousePosition.x > player.position.x;//Hack to make aiming work both ways
    }
    
    
    ClearBackground(customBackgroundColor);
    if (!move_car && !player.enter_car){
        camera.target = player.position;
    }
    
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxTrees = camera.target.x * .8;
    float parallaxBackground = camera.target.x * 0.9f;  // Background moves even slower 

    //BeginShaderMode(shader);


    if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }

    // Draw the background layers
    DrawTexturePro(resources.cemeteryBackground, {0, 0, static_cast<float>(resources.cemeteryBackground.width), static_cast<float>(resources.cemeteryBackground.height)},
                    {parallaxBackground, 0, static_cast<float>(resources.cemeteryBackground.width), static_cast<float>(resources.cemeteryBackground.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.cemeteryTrees, {0, 0, static_cast<float>(resources.cemeteryTrees.width), static_cast<float>(resources.cemeteryTrees.height)},
                    {parallaxTrees-1024, 0, static_cast<float>(resources.cemeteryTrees.width), static_cast<float>(resources.cemeteryTrees.height)}, {0, 0}, 0.0f, WHITE);

    DrawTexturePro(resources.cemeteryMidground, {0, 0, static_cast<float>(resources.cemeteryMidground.width), static_cast<float>(resources.cemeteryMidground.height)},
                    {parallaxMidground, 0, static_cast<float>(resources.cemeteryMidground.width), static_cast<float>(resources.cemeteryMidground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),  offset by 1024 to center relative to midground. 
    DrawTexturePro(resources.cemeteryForeground, {0, 0, static_cast<float>(resources.cemeteryForeground.width), static_cast<float>(resources.cemeteryForeground.height)},
                    {1024, 0, static_cast<float>(resources.cemeteryForeground.width), static_cast<float>(resources.cemeteryForeground.height)}, {0, 0}, 0.0f, WHITE);

    //EndShaderMode();

    EndShaderMode(); ////////////////////////////SHADER OFF
    int CarFrameWidth = 128;
    Rectangle sourceRecCar = { static_cast<float>(player_car.currentFrame * CarFrameWidth), 0.0f, static_cast<float>(CarFrameWidth), static_cast<float>(CarFrameWidth) };

    //render player car
    DrawTextureRec(resources.carSheet, sourceRecCar, player_car.position, WHITE);
    if (player.enter_car){
        //render headlight/breaklight
        Vector2 breakLight_pos = {player_car.position.x + 88, player_car.position.y + 53};
        Vector2 light_pos = {player_car.position.x - 225, player_car.position.y + 32};

        BeginBlendMode(BLEND_ADDITIVE);
        DrawTextureV(resources.breakLight, breakLight_pos, WHITE);
        DrawTextureV(resources.lightBeam, light_pos, WHITE);
        EndBlendMode();

    }


    //render shovel. Click the shovel to pick it up. 

    Vector2 shovelPos = {1900, 700};
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);
    float distance = abs(shovelPos.x - player.position.x);
    if (drawShovel){ //shovel pickup
        DrawTexture(resources.shovelWorld, shovelPos.x, shovelPos.y, WHITE);
        Rectangle shovelBounds = { //shovel button
            shovelPos.x,      
            shovelPos.y,     
            static_cast<float>(32),  
            static_cast<float>(64)  
        };

    
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& distance < 20){ //pickup shovel
            if (CheckCollisionPointRec(mouseWorldPos, shovelBounds)){
                //add shovel in inventory
                if (!player.hasShovel){
                    drawShovel = false;
                    AddItemToInventory("shovel", inventory, INVENTORY_SIZE);
                    showInventory = true;
                    player.hasShovel = true;
                
                }
            
            }


        }
        //Press up key or W to pickup shovel when close enough
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) && distance < 20){
            if (!player.hasShovel){
                drawShovel = false;
                AddItemToInventory("shovel", inventory, INVENTORY_SIZE);
                showInventory = true;
                player.hasShovel = true;
            
            }
                

        }

    }


    for (NPC& zombie : zombies){ //update and draw zombies in cemetery
        zombie.Update(player);
        zombie.Render();
    }

    if (show_carUI && !move_car && player.enter_car){ //destination menu
        DrawCarUI(player_car, mousePosition, camera, gameState);
    }

    if (player.enter_car == false){// if enter car is false, dont render player or update position camera should stay focused on player pos. 
        player.DrawPlayer(resources, gameState, camera);

    }
    DrawBullets(); //draw bullets in cemetery after everything else. 

    EndMode2D();
    DrawMoney(); //draw money after EndMode2d()
    if (showInventory){
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);  // Render the inventory 
    }

    if (player.hasGun){//DRAW RETICLE IF AIMING AND HAS GUN
        DrawTexture(IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ? resources.reticle : resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // if aiming draw reticle
    }else{
        DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE);
    }
    
    //if (player.hasGun && (IsKeyDown(KEY_F) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT))) DrawHUD(player); //only show ammo when aiming

    if ((player.hasGun || player.hasShotgun) && !player.enter_car) DrawHUD(player); //always show ammo when outside of car in the cemetery

    //DrawText("Cemetery", screenWidth/2 - 100, 60, 50, WHITE);

    //draw healthbar below EndMode2D() so it's position is based on camera offset. 
    if (gameState == CEMETERY && !player.enter_car){
        Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
        DrawHealthBar(barPos, player.maxHealth, player.currentHealth, 128, 16);

    }

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){//exit car
        if (player.enter_car && !move_car){
            SoundManager::getInstance().StopMusic("CarRun"); //turn off car audio when exiting car
            PlaySound(SoundManager::getInstance().GetSound("CarDoorClose"));
            player.enter_car = false;
            player_car.currentFrame = 0;
            player.position = Vector2{player_car.position.x + 32, 700};
            
        }
    }
    
}



void RenderRoad(const GameResources& resources, PlayerCar& player_car,Player& player, Camera2D& camera, Vector2 mousePosition, Shader& drunkShader, Shader& glowShader, Shader& glitchShader){
    if (player_car.position.x < 200 && !reverse_road){//transition to cemetery
        
        transitionState = FADE_OUT;
        move_car = true;

    if (rand() % 2 == 0 && !playOwl){
        playOwl = true;
        PlaySound(SoundManager::getInstance().GetSound("Owl"));
    }

    }
    if (player_car.position.x > 800 && reverse_road){
        transitionState = FADE_OUT;

    }


    hasSlept = false; // player can sleep if they have traveled.

    if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }



    BeginMode2D(camera);
    DrawTexture(resources.road, screenWidth/2 - 1280, 0, WHITE);
    camera.target = Vector2 {512, 700};
    player_car.carSpeed = 200;

    if (!reverse_road){
        player_car.position.x -= player_car.carSpeed * GetFrameTime();
    }else{
        
        player_car.position.x += player_car.carSpeed * GetFrameTime();

    }
    
    
    float CarFrameWidth = 128.0;
    Rectangle sourceRecCar = {player_car.currentFrame * CarFrameWidth, 0, CarFrameWidth, CarFrameWidth};
    //Draw player car
    if (!player_car.facingLeft){
        sourceRecCar.width = -CarFrameWidth;       
    }
    DrawTextureRec(resources.carSheet, sourceRecCar, player_car.position, WHITE);

    if (player.enter_car){
        //render headlight/breaklight
        if (!reverse_road){
            Vector2 breakLight_pos = {player_car.position.x + 88, player_car.position.y + 53};
            Vector2 light_pos = {player_car.position.x - 225, player_car.position.y + 32};
            BeginBlendMode(BLEND_ADDITIVE);
            DrawTextureV(resources.breakLight, breakLight_pos, WHITE);
            DrawTextureV(resources.lightBeam, light_pos, WHITE);
            EndBlendMode();

        } // move the headlight and breaklight and flip the headlight. 
  

    }
    EndShaderMode();
    EndMode2D();
    DrawMoney(); //draw money after EndMode2d()
    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // render mouse cursor outside Mode2D
   
}

void RenderApartment(const GameResources& resources, Player player, Vector2 mousePosition, GameCalendar& calendar, Camera2D camera, Shader& drunkShader, Shader& glowShader, Shader& glitchShader){
    player.position.x -= 20; //ensure over_apartment = false
    int screen_center = (screenWidth - resources.apartment.width)/2;
    
     //Vector2 drawerPos = {screenWidth/2 + 160, 730};


   if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }

    ClearBackground(ApartmentBgColor);

    DrawTexture(resources.apartment, screen_center, 0, WHITE);
    EndShaderMode(); ////////////////////////////SHADER OFF

    DrawMoney(); //draw money after EndMode2d()
    if (showAPUI){
        DrawApartmentUI(calendar, mousePosition, camera);
    }
    
    
    //DrawText("Apartment", screenWidth/2 - 128, 60, 50, WHITE);
    if (!has_car_key){
        DrawTexture(resources.carKey, carKeysPos.x, carKeysPos.y, WHITE);
    }
    

    if (showInventory){
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);
        
    }

    if (openDrawer){
        DrawTexture(resources.OpenDrawer, drawerPos.x, drawerPos.y, WHITE);
    }
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        transitionState = FADE_OUT;
        showInventory = false;
        PlaySound(SoundManager::getInstance().GetSound("mainDoor"));
        
    }
    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE);
    
}

void renderLot(GameResources& resources, Player& player, Camera2D& camera, Vector2& mousePosition, Shader& drunkShader, Shader& glowShader, Shader& glitchShader){
    Vector2 mouseWorldPos = GetScreenToWorld2D(mousePosition, camera);
    if (player.position.x < 2782 && player.position.x > 2742){
        over_exit = true;
    }else{
        over_exit = false;
    }



    over_lot = false;
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){
        if (over_exit){
            transitionState = FADE_OUT;

        }
    }    

    //camera.target = player.position;
    //float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxBackground = camera.target.x * 0.7f;  // Background moves even slower
    
    SoundManager::getInstance().UpdateMusic("StreetSounds"); //only update street sounds when oustide
    if (!streetSounds){ 
        streetSounds = true; //Why do we need this bool? incase we need to turn it off?
        SoundManager::getInstance().PlayMusic("StreetSounds");
        //SoundManager::getInstance().PlayMusic("Schumann");
    }

    if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }

    BeginMode2D(camera);
     // Draw the background (sky)
    DrawTexturePro(resources.background, {0, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)},
                    {parallaxBackground, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the midground (silhouettes)
    // DrawTexturePro(resources.midground, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
    //                 {parallaxMidground, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),  offset by 1024 to center relative to midground. 
    DrawTexturePro(resources.vacantLot, {0, 0, static_cast<float>(resources.vacantLot.width), static_cast<float>(resources.vacantLot.height)},
                    {705, 0, static_cast<float>(resources.vacantLot.width), static_cast<float>(resources.vacantLot.height)}, {0, 0}, 0.0f, WHITE);

    show_dbox = false;  //turn off dbox if no one is interacting
    for (NPC& hobo : hobos){
        hobo.Update(player);
        hobo.Render();
        hobo.ClickNPC(mousePosition, camera, player);

        if (hobo.interacting){
            dboxPosition = hobo.position;
            dealer = false; // dealer gets left on somewhere
            show_dbox = true;   //dialogBox
        
            phrase = hobo.speech;
                      
        }else{
            // show_dbox = false;
        }
    }
    
    player.DrawPlayer(resources, gameState, camera);
    //drawshotgun pickup
    Vector2 shotgunPos = {3181, 700};
    int distance = abs(shotgunPos.x - player.position.x);

    if (drawShotgun){
        DrawTexture(resources.shotgunPickup, 3181, 700, WHITE);
        Rectangle shotgunBounds = { //Shotgun Button
            shotgunPos.x,
            shotgunPos.y,     
            static_cast<float>(64),  
            static_cast<float>(64)  
        };

        if (CheckCollisionPointRec(mouseWorldPos, shotgunBounds)){
            //click on shotgun to pickup if close 
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && distance < 20){
                if (!player.hasShotgun){
                    AddItemToInventory("shotgun", inventory, INVENTORY_SIZE);
                    player.hasShotgun = true;
                    showInventory = true;
                    drawShotgun = false;
                    //play sound effect
                    PlaySound(SoundManager::getInstance().GetSound("shotgunReload"));
                }
            }
        }

        //press up or W to pickup shotgun if close enough
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) && distance < 20){

            if (!player.hasShotgun){
                AddItemToInventory("shotgun", inventory, INVENTORY_SIZE);
                player.hasShotgun = true;
                showInventory = true;
                drawShotgun = false;
                //play sound effect
                PlaySound(SoundManager::getInstance().GetSound("shotgunReload"));
            }

            }
        

    }

    
    EndMode2D();  // End 2D mode 
 
    DrawMoney(); //draw money after EndMode2d()

    if (show_dbox){      
        DrawDialogBox(camera, 0, 0, 20); // draw box size of 0x0. hobo has no border box
    }  

    if (showInventory){
         
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);  // Render the inventory 
    }

    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // render mouse cursor outside Mode2D. Do this last
}

// Example function to render the outside scene with dynamic camera
void RenderOutside(const GameResources& resources, Camera2D& camera,Player& player, PlayerCar& player_car,std::vector<NPC>& npcs,Vector2 mousePosition, Shader& drunkShader, Shader& glowShader, Shader& glitchShader) {
    // Update the camera target to follow the player
    int ap_min = 2246;//over apartment
    int ap_max = 2266;

    int pc_min = 1728; // over player_car
    int pc_max = 1748;
    int road_min = 1340; //exiting outside via road

    int lot_min = vacantLotX - 20;
    int lot_max = vacantLotX + 20;

    int dist = abs(player.position.x - ap_max);
    if (dist > 1000){
        hasSlept = false;
    }


    SoundManager::getInstance().UpdateMusic("StreetSounds"); //only update street sounds when oustide
    if (!streetSounds){ 
        streetSounds = true; //Why do we need this bool? incase we need to turn it off?
        SoundManager::getInstance().PlayMusic("StreetSounds");
        //SoundManager::getInstance().PlayMusic("Schumann");
    }


    if (player_car.position.x < road_min && move_car){
        transitionState = FADE_OUT;
        
        //player_car.position = Vector2 {900, 700 - 32};

    }

    show_dbox = false; // reset to false if it falls through
    if (player.position.x > pc_min && player.position.x < pc_max){
        over_car = true;
        phrase = "PRESS UP TO ENTER";
        show_dbox = true;
        dboxPosition = player.position;
        
        
    }else{
        over_car = false;
    }

    
    if (player.position.x > lot_min && player.position.x < lot_max){
        over_lot = true;
        phrase = "PRESS UP TO ENTER";
        dboxPosition = player.position;
        
        show_dbox = true;

    }else{
        over_lot = false;
        
    }
    
    if (player.position.x > ap_min  && player.position.x < ap_max){
        over_apartment = true;
        phrase = "PRESS UP TO ENTER";
        dboxPosition = player.position;
        dboxPosition.y = player.position.y + 10;
        show_dbox = true;
        
    }else{
        over_apartment = false;
    }

    camera.target = player.position;
    float parallaxMidground = camera.target.x * 0.5f;  // Midground moves slower
    float parallaxBackground = camera.target.x * 0.7f;  // Background moves even slower
    
    BeginMode2D(camera);  // Begin 2D mode with the camera
    ClearBackground(customBackgroundColor);
    //BeginShaderMode(shader); /////////////////////////////////////// UNCOMMENT FOR CRT SHADER



    if (applyShader){
        
        BeginShaderMode(glowShader);
        
    }

    if (drunk){
        BeginShaderMode(drunkShader);
    }
    
    if (glitch){
        BeginShaderMode(glitchShader);
    }
    
     // Draw the background (sky)
    DrawTexturePro(resources.background, {0, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)},
                    {parallaxBackground, 0, static_cast<float>(resources.background.width), static_cast<float>(resources.background.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the midground (silhouettes)
    DrawTexturePro(resources.midground, {0, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)},
                    {parallaxMidground, 0, static_cast<float>(resources.midground.width), static_cast<float>(resources.midground.height)}, {0, 0}, 0.0f, WHITE);

    // Draw the foreground (main scene),  offset by 1024 to center relative to midground. 
    DrawTexturePro(resources.foreground, {0, 0, static_cast<float>(resources.foreground.width), static_cast<float>(resources.foreground.height)},
                    {512, 0, static_cast<float>(resources.foreground.width), static_cast<float>(resources.foreground.height)}, {0, 0}, 0.0f, WHITE);
    
    EndShaderMode(); ////////////////////////////SHADER OFF
    
    if (move_car){
        player_car.position.x -= player_car.carSpeed * GetFrameTime();
    }else{
        player_car.position = Vector2{1710, 668};
    }
    
    //show_dbox = false;  //turn off dbox if no one is interacting
    for (NPC& npc : npcs){
        npc.Update(player);
        npc.Render();
        npc.ClickNPC(mousePosition, camera, player);
    

        if (npc.interacting){ //Take the first one you find. 
            dboxPosition = npc.position;
            
            show_dbox = true;   //dialogBox
            if (npc.dealer){
                phrase = "I gOt wHat YoU NEEd\n\nDrugs: $100";
                dealer = true;
                showInventory = true;

            }else{
                phrase = npc.speech; //randomized speech
                dealer = false;
                
                
            }
            

        }else{
            dealer = false;
            // show_dbox = false;
        }
    
    }
    
    //DrawStreetLight
    BeginBlendMode(BLEND_ADDITIVE);
    DrawTexture(resources.lightCone, 1884, 610, WHITE);
    DrawTexture(resources.lightCone, 3188, 610, WHITE);
    
    EndBlendMode();
    
    DrawBullets();
    UpdateBullets();
    //DrawPlayerCar
    int CarFrameWidth = 128;
    Rectangle sourceRecCar = {player_car.currentFrame * CarFrameWidth, 0, CarFrameWidth, CarFrameWidth};
    DrawTextureRec(resources.carSheet, sourceRecCar, player_car.position, WHITE); //draw player_car
    if (player.enter_car){
        //render headlight/breaklight
        
        Vector2 breakLight_pos = {player_car.position.x + 88, player_car.position.y + 53};
        Vector2 light_pos = {player_car.position.x - 225, player_car.position.y + 32};
        BeginBlendMode(BLEND_ADDITIVE);
        DrawTextureV(resources.breakLight, breakLight_pos, WHITE);
        DrawTextureV(resources.lightBeam, light_pos, WHITE);
        EndBlendMode();
        show_carUI = true;    

    }
   

    if (player.enter_car == false){// if enter car is false, dont render player or update position. camera should stay focused on player pos. 
        SoundManager::getInstance().StopMusic("CarRun");
        //DRAW PLAYER
        if (!player.enter_car) { // if enter_car is false, don't render player or update position; camera should stay focused on player pos.
            player.DrawPlayer(resources, gameState, camera);


        }
    }
    
    MoveTraffic(resources);//Draw Traffic


    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){
        if (player.enter_car && !move_car){ // dont exit car if it's still moving.
            PlaySound(SoundManager::getInstance().GetSound("CarDoorClose")); 
            player.enter_car = false;
            player_car.currentFrame = 0;
        }
    }

    // if (IsKeyPressed(KEY_SPACE)){
    //     if (player.enter_car){
    //         move_car = true;
    //     }
    // }
    if (show_carUI && !move_car && player.enter_car){
        DrawCarUI(player_car, mousePosition, camera, gameState);
    }

    EndMode2D();  // End 2D mode 

    if (player.currentHealth < 100) showHealthbar = true; // dont show healthbar until youve taken damage, when on street
    Vector2 barPos = {camera.offset.x - 32, camera.offset.y + 128};
    if (showHealthbar) DrawHealthBar(barPos, player.maxHealth, player.currentHealth, 128, 16);

    
    

    if (show_dbox && !player.enter_car){
        if (over_lot || over_apartment || over_car){
            DrawDialogBox(camera, 0, 0, 20);
        }else{
            DrawDialogBox(camera, 128, 64, 20);
        }
        
    }

    //DrawText("Paper Street", screenWidth/2 - 128, 60, 50, WHITE);
    DrawMoney(); //draw money after EndMode2d()
    if (showInventory){
         
        RenderInventory(resources, inventory, INVENTORY_SIZE, player, mousePosition);  // Render the inventory 
    }
    //Draw cursor last so it's on top
    DrawTexture(resources.handCursor, mousePosition.x, mousePosition.y, WHITE); // render mouse cursor outside Mode2D. Do this last
}


//NPC zombie(zombieTexture, startPos, 50.0f, WALK, true, true); 

// Factory function to create an NPC with default properties

void spawnNPCs(GameResources& resources){
    // Create NPCs outside and set there starting desitnations. 
    float speed = 50.0f;

    //spawn generic NPCs
    int generic = 3;
    for (int i = 0; i < generic; ++i) {
        Vector2 startPosition = { static_cast<float>(512 + i * 200), 700 };  // positions spread out along the x axis    
        NPC npc = CreateNPC(resources.npcTexture, startPosition, speed, IDLE,  true, false);
        npc.SetDestination(512, 4000);
        npcs.push_back(npc);  // Add the NPC to the vector
    }

    //spawn businessMan
    int b_men = 2;
    for (int i = 0; i < b_men; i++){
        Vector2 b_pos = { static_cast<float>(2300 + i * 100), 700};
        NPC business_npc = CreateNPC(resources.businessSheet, b_pos, speed,IDLE, true, false);
        business_npc.SetDestination(1000, 4000);
        npcs.push_back(business_npc);

    }


    //spawn woman
    int women = 2;
    for (int i = 0; i < women; i++){
        Vector2 w_pos = {static_cast<float>(2050 + i * 100), 700};
        NPC woman_npc = CreateNPC(resources.womanSheet, w_pos, speed,IDLE, true, false);
        woman_npc.SetDestination(1000, 4000);
        npcs.push_back(woman_npc);

    }

    //spawn hobo update and draw only in vacant lot
    
    Vector2 h_pos = {2900, 700};
    NPC hobo_npc = CreateNPC(resources.hoboSheet, h_pos, speed, IDLE, true, false);
    hobo_npc.SetDestination(2800, 3200);
    hobo_npc.hobo = true;
    hobos.push_back(hobo_npc);//hobo is in it's own vector of hobos
    

    //spawn policemen
   int police = 1;
    for (int i = 0; i < police; i++){
        Vector2 w_pos = {static_cast<float>(2100 + i * 100), 700};
        NPC police_npc = CreateNPC(resources.policeSheet, w_pos, speed,IDLE, true, false);
        police_npc.SetDestination(1000, 4000);
        police_npc.police = true;
        npcs.push_back(police_npc);

    }

    //spawn dealer
    int dealer = 1;

    for (int i = 0; i < dealer; i++){
        Vector2 d_pos = {static_cast<float>(2200 + i * 100), 700};
        NPC dealer_npc = CreateNPC(resources.dealerSheet, d_pos, speed, IDLE, true, false);
        dealer_npc.SetDestination(1000, 4000);
        dealer_npc.dealer = true;
        npcs.push_back(dealer_npc);
    }

}

void DisplayDate(GameCalendar& calendar){
    DrawText(calendar.GetDate().c_str(), screenWidth/2 - 450, 25, 20, WHITE);
}

void glowEffect(Shader& glowShader){
        float time = GetTime();  // Get the total elapsed time

        // Use a sine wave to oscillate glowThreshold between 0.1 and 0.3 over 1 second
        float minThreshold = 0.2f;
        float maxThreshold = 0.6f;
        float oscillationSpeed = 0.9f;  // 1 second duration

        // Calculate the oscillating glow threshold using a sine wave
        float glowThreshold = minThreshold + (maxThreshold - minThreshold) * (0.5f * (1.0f + sin(oscillationSpeed * time)));

        // Set the glowThreshold uniform in the shader
        int glowThresholdLocation = GetShaderLocation(glowShader, "glowThreshold");
        SetShaderValue(glowShader, glowThresholdLocation, &glowThreshold, SHADER_UNIFORM_FLOAT);

}



void InitSounds(SoundManager& soundManager){
    //We use our own custom sound manager. We have an array of sounds, and an array of musticTracks.
    SetMasterVolume(1.0f);  // Sets the master volume to maximum
    
    SoundManager::getInstance().LoadMusic("CarRun", "assets/sounds/CarRun.ogg"); // load CarRun.ogg into music tracks with the name CarRun
    //music tracks automatically loop.The car running sound needs to loop, so we call it music.
    SoundManager::getInstance().LoadMusic("StreetSounds", "assets/sounds/StreetSounds.ogg"); 
    SoundManager::getInstance().LoadMusic("Schumann", "assets/sounds/Schumann.ogg");
    soundManager.LoadSound("gunShot", "assets/sounds/gunShot.ogg");   //misc sounds
    soundManager.LoadSound("BoneCrack", "assets/sounds/BoneCrack.ogg");
    soundManager.LoadSound("reload", "assets/sounds/revolvercock.ogg");
    soundManager.LoadSound("dryFire", "assets/sounds/DryFire.ogg");
    soundManager.LoadSound("CarStart", "assets/sounds/CarStart.ogg");
    soundManager.LoadSound("CarDoorOpen", "assets/sounds/CarDoorOpen.ogg");
    soundManager.LoadSound("CarDoorClose", "assets/sounds/CarDoorClose.ogg");
    soundManager.LoadSound("mainDoor", "assets/sounds/mainDoor.ogg");
    soundManager.LoadSound("OpenDrawer", "assets/sounds/OpenDrawer.ogg");
    soundManager.LoadSound("CloseDrawer", "assets/sounds/CloseDrawer.ogg");
    soundManager.LoadSound("Keys", "assets/sounds/Keys.ogg");
    soundManager.LoadSound("Owl", "assets/sounds/Owl.ogg");

    soundManager.LoadSound("ShotGun", "assets/sounds/ShotGun.ogg");
    soundManager.LoadSound("ShotgunReload", "assets/sounds/ShotgunReload.ogg");

    soundManager.LoadSound("Step1", "assets/sounds/Step1.ogg");
    soundManager.LoadSound("Step2", "assets/sounds/Step2.ogg");
    
    soundManager.LoadSound("moan1", "assets/sounds/ZombieMoan1.ogg"); //zombie VA
    soundManager.LoadSound("moan2", "assets/sounds/ZombieMoan2.ogg");
    soundManager.LoadSound("moan3", "assets/sounds/ZombieMoan3.ogg");
    soundManager.LoadSound("zhit1", "assets/sounds/ZombieHit1.ogg");
    soundManager.LoadSound("zhit2", "assets/sounds/ZombieHit2.ogg");
    soundManager.LoadSound("zhit3", "assets/sounds/ZombieHit3.ogg");
    soundManager.LoadSound("zhit4", "assets/sounds/ZombieHit4.ogg");

    soundManager.LoadSound("zombieDeath", "assets/sounds/zombieDeath.ogg");


    soundManager.LoadSound("phit1", "assets/sounds/PlayerHit1.ogg"); //player VA hits
    soundManager.LoadSound("phit2", "assets/sounds/PlayerHit2.ogg");

    //Volume edits
    SoundManager::getInstance().SetSoundVolume("CarStart", .5);
    SoundManager::getInstance().SetSoundVolume("BoneCrack", 0.3f);
    SoundManager::getInstance().SetMusicVolume("CarRun", 0.25f);
    SoundManager::getInstance().SetMusicVolume("Schumann", 0.25f);
}






int main() {
    //God speed  
    InitWindow(screenWidth, screenHeight, "Adventure Game");
    //PUT NOTHING ABOVE THIS ^^ CAN CAUSE SEG FAULT
    InitAudioDevice();
    SoundManager& soundManager = SoundManager::getInstance();
    InitSounds(soundManager);
    HideCursor();
    SetExitKey(0);  // Disable escape key from closing the window
    srand(static_cast<unsigned>(time(0))); //randomize seed based on time
    
    // Initialize game resources
    GameResources resources;
    GameCalendar calendar;
    LoadGameResources(resources);
    spawnNPCs(resources); //spawn NPCs before rendering them outside


  ///////////////////SHADERS????????????????????????????????????????????????  
    // Shader shader = LoadShader("shaders/shaderGlitch.vs", "shaders/shaderGlitch.fs"); //CRT SHADER. Consider a load shader function
    
    // ///ripple shader
    // Shader rippleShader = LoadShader(0, "shaders/ripple.fs");

    Shader glowShader = LoadShader(0, "shaders/glow.fs");
 
    float resolution[2] = { (float)screenWidth, (float)screenHeight }; //reuse resolution for multiper shaders
    float glowThreshold = 0.01f; //threshold for both drunk and glow
    float glowIntensity = 2.0f; // same intensity for drunk and glow
    float glowColor[3] = { 0.5f, 1.0f, 2.0f }; //color is for glow

    //Glow 1 animated color
    SetShaderValue(glowShader, GetShaderLocation(glowShader, "resolution"), resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(glowShader, GetShaderLocation(glowShader, "glowColor"), glowColor, SHADER_UNIFORM_VEC3);
    SetShaderValue(glowShader, GetShaderLocation(glowShader, "glowThreshold"), &glowThreshold, SHADER_UNIFORM_FLOAT);

    //glitch
    Shader glitchShader = LoadShader(0, "shaders/glitch.fs");

    //Drunk aka glowshader2
    Shader glowShader2 = LoadShader(0, "shaders/glow2.fs");
    // Shader wave_distortion = LoadShader(0, "wave_distortion.fs");
    // Shader blurShader = LoadShader(0, "shaders/blur.fs");
    // Shader crt_effect = LoadShader(0, "shaders/crt_effect.fs");
    // // Get the location of the 'time' uniform variable in the shader

    int timeLoc = GetShaderLocation(glitchShader, "time"); //used for glitch
    float totalTime = 0.0f; // Variable to keep track of time


    //Drunk shader AKA glowshader2
    int glowThresholdLoc = GetShaderLocation(glowShader2, "glowThreshold");
    int glowIntensityLoc = GetShaderLocation(glowShader2, "glowIntensity");
    int resolutionLoc = GetShaderLocation(glowShader2, "resolution");

    SetShaderValue(glowShader2, glowThresholdLoc, &glowThreshold, SHADER_UNIFORM_FLOAT);   
    SetShaderValue(glowShader2, glowIntensityLoc, &glowIntensity, SHADER_UNIFORM_FLOAT);
    SetShaderValue(glowShader2, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
    


    // Set the glow color (e.g., a bright blue)
    //float glowColor[3] = { 0.0f, 0.5f, 1.0f };  // RGB values between 0.0 and 1.0
    //SetShaderValue(glowShader2, glowColorLoc, glowColor, SHADER_UNIFORM_VEC3);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////shaders



    // Initialize player
    Player player;
    PlayerCar player_car;

    InitializePlayerCar(player_car);
  
    // Initialize the camer
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f + 188.0f };  // Screen center + y offset 188 lower ground for bigger sky
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    float targetZoom = camera.zoom;  // Initialize targetZoom to the initial zoom value

    inventoryPositionX = player.position.x; //init inventory position
    inventoryPositionY = player.position.y;  
    SetTargetFPS(60);
 
    // Main game loop
    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();
        if (!player.enter_car) player.UpdateMovement(resources, gameState, mousePosition, camera);  // Update player position and animation
        UpdateInventoryPosition(camera, gameState);
        SoundManager::getInstance().UpdateMusic("CarRun");
        SoundManager::getInstance().UpdateMusic("Schumann");
        
        UpdateBullets();
        CheckBulletNPCCollisions(zombies); 
        MonitorMouseClicks(player, calendar);
        UpdateZombieSpawning(resources, player);
        glowEffect(glowShader);
        
        float deltaTime = GetFrameTime();
        totalTime += deltaTime;  //glitch timer

        //glitchshader
        SetShaderValue(glitchShader, timeLoc, &totalTime, SHADER_UNIFORM_FLOAT);


        ////DEBUG/////////////////DEBUG///////////
        if (IsKeyPressed(KEY_SPACE)){
            std::cout << "Player Position: ";
            PrintVector2(player.position);
            if (!drunk){
                //applyShader = true;
                drunk = true;
            }else{
                //applyShader = false;
                drunk = false;
            }
   
        }

        if (IsKeyPressed(KEY_L)){
            if (!glitch){
                glitch = true;
            }else{
                glitch = false;
            }
        }

        if (IsKeyPressed(KEY_K)){
            if (!has_car_key){
                AddItemToInventory("carKeys", inventory, 4);
                has_car_key = true;
                PlaySound(SoundManager::getInstance().GetSound("Keys"));

            }

        }

        if (IsKeyPressed(KEY_G)){
            if (!player.hasGun){
                AddItemToInventory("Gun", inventory, INVENTORY_SIZE);
                player.hasGun = true;
                PlaySound(SoundManager::getInstance().GetSound("reload"));

            }
            if (!player.hasShotgun){
                AddItemToInventory("shotgun", inventory, INVENTORY_SIZE);
                player.hasShotgun = true;
            }

        }
        //////////////////////////////////////////////

        //I for inventory
        if (IsKeyPressed(KEY_I)){
            if (!showInventory){
                showInventory = true;
            }else{
                showInventory = false;
            }
            
        }
        //enter places by pressing up
        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){

            if (over_apartment && gameState == OUTSIDE){
                transitionState = FADE_OUT; //Transition to apartment
                PlaySound(SoundManager::getInstance().GetSound("mainDoor"));
                over_apartment = false;
                showInventory = false;
                //player.position.x = 512; //move player, to move inventory to the middle of the screen. 
                
            }
            if (over_car && !player.enter_car && has_car_key){
                //player inside idling car
                SoundManager::getInstance().PlayMusic("CarRun");
                PlaySound(SoundManager::getInstance().GetSound("CarStart"));
                PlaySound(SoundManager::getInstance().GetSound("CarDoorOpen"));
                player.enter_car = true;
                over_car = false;
                player_car.currentFrame = 1;


            }
            if (over_lot){
                transitionState = FADE_OUT;
            }    
        }
        // Handle zoom input
        if (GetMouseWheelMove() > 0) {
            targetZoom += 0.2f;
        } else if (GetMouseWheelMove() < 0) {
            targetZoom -= 0.2f;
        }

        // Smoothly interpolate the current zoom towards the target zoom
        camera.zoom = Lerp(camera.zoom, targetZoom, 0.1f);
        float maxZoom = 2.5;
        float minZoom = 1.0;
        // Apply boundary checks for the zoom level
        if (camera.zoom > maxZoom) camera.zoom = maxZoom;
        if (camera.zoom < minZoom) camera.zoom = minZoom;
        if (targetZoom > maxZoom) targetZoom = maxZoom;
        if (targetZoom < minZoom) targetZoom = minZoom;

        BeginDrawing(); //NEEDED
        // All the games draw calls need to be inside the main beginDrawing?

        if (gameState == OUTSIDE){
               
            RenderOutside(resources, camera, player, player_car,npcs,mousePosition, glowShader2, glowShader, glitchShader); //glowshader2 = drunkshader
            DisplayDate(calendar);

        }else if (gameState == APARTMENT){
            RenderApartment(resources, player, mousePosition, calendar, camera, glowShader2, glowShader, glitchShader);
            DisplayDate(calendar);
        }else if (gameState == ROAD){
            RenderRoad(resources, player_car, player, camera, mousePosition, glowShader2, glowShader, glitchShader);
            DisplayDate(calendar);
        }else if (gameState == CEMETERY){
            RenderCemetery(resources, player, player_car, camera,mousePosition, glowShader2, glowShader, glitchShader);
            DisplayDate(calendar);

        }else if (gameState == WORK){
            ClearBackground(BLACK);

        }else if (gameState == LOT){ // vacant lot
            renderLot(resources, player, camera, mousePosition, glowShader2, glowShader, glitchShader);
            DisplayDate(calendar);
        }
        
        HandleTransition(player, player_car, calendar);
        EndDrawing();

        EndShaderMode();
        
        
    }

    // Unload resources and close the window
    UnloadGameResources(resources);
    soundManager.UnloadAllSounds();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
