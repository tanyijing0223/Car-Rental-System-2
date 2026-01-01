#ifndef admin_h
#define admin_h
#include <string>

// Declarations
void adminLogin();
void adminMenu();
// Since these are admin actions, we'll keep them here as requested
void updateCarQuantity(std::string id, int change);
void addCar();

#endif