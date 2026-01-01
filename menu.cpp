#include "menu.h"
#include "cars.h"
#include "admin.h"
#include "accounts.h"
// If you have a separate Rental header, include it here:
// #include "Rentals.h" 

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Helper from main
void clearScreen();

// Prototypes for functions that might still be in main or other files
void viewAllRentals();
void rentCar(Customer c);
void returnCar(Customer c);
void viewMyRentals(Customer c);

void adminMenu() {
    int choice;
    while (true) {
        clearScreen();
        cout << "------------------------------------" << endl;
        cout << "         [ ACCESS GRANTED ]         " << endl;
        cout << "------------------------------------" << endl;
        cout << "1. View Car Details\n2. View Customer Details\n3. Add New Cars\n4. View All Rental History\n5. Logout\n\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            clearScreen(); 
            viewCars(true); 
            cin.ignore(); cin.get(); 
        }
        else if (choice == 2) {
            clearScreen();
            ifstream file("customer.txt");
            string n, i, co, p;
            cout << left << setw(15) << "NAME" << setw(15) << "IC NUMBER" << setw(15) << "CONTACT" << endl;
            cout << "---------------------------------------------" << endl;
            while (file >> n >> i >> co >> p)
                cout << left << setw(15) << n << setw(15) << i << setw(15) << co << endl;
            file.close();
            cin.ignore(); cin.get();
        }
        else if (choice == 3) {
            clearScreen();
            addCar();
        }
        else if (choice == 4) {
            viewAllRentals(); 
            cin.ignore(); cin.get(); 
        }
        else break;
    }
}

void customerMenu(Customer currentCust) {
    int choice;
    while (true) {
        clearScreen();
        cout << "------------------------------------" << endl;
        cout << "       Hello, " << currentCust.name << endl;
        cout << "------------------------------------" << endl;
        cout << "1. Rent a Car\n2. Return a Car\n3. View My History\n4. Logout\n\nChoice: ";
        cin >> choice;
        if (choice == 1) rentCar(currentCust);
        else if (choice == 2) returnCar(currentCust);
        else if (choice == 3) { 
            viewMyRentals(currentCust); 
            cin.ignore(); cin.get(); 
        }
        else break;
    }
}