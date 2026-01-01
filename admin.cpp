#include "admin.h"
#include "cars.h"      // Needed for Car struct and viewCars()
#include "accounts.h"  // Needed if you call customer functions
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Forward declaration of clearScreen if it's still in main.cpp
void clearScreen(); 

void adminLogin() {
    clearScreen();
    string pin;
    cout << "------------------------------------" << endl;
    cout << "        ADMIN VERIFICATION          " << endl;
    cout << "------------------------------------" << endl;
    cout << "Enter Admin PIN: ";
    cin >> pin;

    if (pin == "5555") {
        adminMenu();
    } else {
        cout << "\n[ ACCESS DENIED ]" << endl;
        cin.ignore(); cin.get();
    }
}

void updateCarQuantity(string id, int change) {
    ifstream file("car.txt");
    vector<Car> cars;
    Car c;
    while (file >> c.id >> c.model >> c.color >> c.price >> c.gear >> c.quantity) {
        if (c.id == id) c.quantity += change;
        cars.push_back(c);
    }
    file.close();

    ofstream outFile("car.txt");
    for (auto const& car : cars) {
        outFile << car.id << " " << car.model << " " << car.color << " "
                << car.price << " " << car.gear << " " << car.quantity << endl;
    }
    outFile.close();
}

void addCar() {
    Car c;
    cout << "Car ID: "; cin >> c.id;
    cout << "Model: "; cin >> c.model;
    cout << "Color: "; cin >> c.color;
    cout << "Price/Day: "; cin >> c.price;
    cout << "Gear: "; cin >> c.gear;
    cout << "Quantity: "; cin >> c.quantity;

    ofstream file("car.txt", ios::app);
    file << c.id << " " << c.model << " " << c.color << " "
         << c.price << " " << c.gear << " " << c.quantity << endl;
    file.close();
}