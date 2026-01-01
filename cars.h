#ifndef cars_h
#define cars_h

#include <string>
#include <vector>

struct Car {
    std::string id, model, color, gear;
    double price;
    int quantity;
};

// Function Prototypes
void viewCars(bool showDetails);
void addCar();
void updateCarQuantity(std::string id, int change);

#endif