#include "cars.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

void viewCars(bool showDetails) {
    ifstream file("car.txt");
    vector<Car> cars;
    Car c;
    cout << "\n--- AVAILABLE CARS ---" << endl;
    cout << left << setw(5) << "ID" << setw(15) << "MODEL" << setw(10) << "STOCK" << endl;
    
    while (file >> c.id >> c.model >> c.color >> c.price >> c.gear >> c.quantity) {
        cout << left << setw(5) << c.id << setw(15) << c.model << setw(10) << c.quantity << endl;
        cars.push_back(c);
    }
    file.close();

    if (showDetails) {
        string searchID;
        cout << "\nEnter ID for full details (0 to back): ";
        cin >> searchID;
        for (auto const& car : cars) {
            if (car.id == searchID) {
                cout << "\n[ " << car.model << " Full Details ]" << endl;
                cout << "Color: " << car.color << "\nPrice/Day: RM" << car.price
                     << "\nGear: " << car.gear << "\nStock Left: " << car.quantity << endl;
            }
        }
    }
}