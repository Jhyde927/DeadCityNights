#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

extern std::string inventory[]; // Declare inventory as extern
extern const int INVENTORY_SIZE; // Declare inventory size as extern

void AddItemToInventory(const std::string& item, std::string inventory[], int inventorySize);

#endif
