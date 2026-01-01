#include "billing.h"
#include "admin.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>

using namespace std;

// Forward declaration of helper
void clearScreen();

// --- Core Logic ---
void rentCar(Customer c) {
    clearScreen();
    viewCars(false); // From Cars.h
    string carID;
    cout << "\nEnter Car ID to select: "; cin >> carID;

    ifstream file("car.txt");
    Car car;
    bool found = false;
    while (file >> car.id >> car.model >> car.color >> car.price >> car.gear >> car.quantity) {
        if (car.id == carID) { found = true; break; }
    }
    file.close();

    if (!found || car.quantity <= 0) {
        cout << "Car unavailable or not found!"; cin.ignore(); cin.get(); return;
    }

    clearScreen();
    cout << "------------------------------------" << endl;
    cout << "        CAR SPECIFICATIONS          " << endl;
    cout << "------------------------------------" << endl;
    cout << "Model:      " << car.model << endl;
    cout << "Color:      " << car.color << endl;
    cout << "Gear Type:  " << car.gear << endl;
    cout << "Price/Day:  RM " << car.price << endl;
    cout << "Stock:      " << car.quantity << endl;
    cout << "------------------------------------" << endl;

    char confirm;
    cout << "Are you sure you want to rent this car? (y/n): ";
    cin >> confirm;

    if (tolower(confirm) != 'y') {
        cout << "\nReturning to menu...";
        cout << "\nPress any key to coninue";
        cin.ignore(); 
        cin.get(); 
        return; 
    }
    
    string dateR;
    int days;
    cout << "\nEnter Date Rented (dd/mm/yyyy): "; cin >> dateR;
    cout << "How many days are you renting? "; cin >> days;

    double addOnTotal = 0;
    char opt;
    cout << "--------------------" << endl;
    cout << "Add Ons (Optional)"<< endl;
    cout << "--------------------" << endl;
    cout << "Add Insurance (RM20)? (y/n): "; cin >> opt;
    if (opt == 'y') addOnTotal += 20;
    cout << "Add Child Seat (RM15)? (y/n): "; cin >> opt;
    if (opt == 'y') addOnTotal += 15;

    double rentTotal = car.price * days;
    double deposit = 100;
    
    clearScreen();
    cout << "------------------------------------" << endl;
    cout << "          RENTAL BILLING            " << endl;
    cout << "------------------------------------" << endl;
    cout << "Customer:      " << c.name << endl;
    cout << "Car Rented:    " << car.model << endl;
    cout << "Date Rented:   " << dateR << endl;
    cout << "------------------------------------" << endl;
    cout << "Rental Fee:    RM " << rentTotal << endl;
    cout << "Add-ons:       RM " << addOnTotal << endl;
    cout << "Deposit:       RM " << deposit << " (Refundable)" << endl;
    cout << "------------------------------------" << endl;
    cout << "TOTAL TO PAY:  RM " << (rentTotal + addOnTotal + deposit) << endl;
    cout << "------------------------------------" << endl;
    cout << "Confirm Transaction? (y/n): "; cin >> opt;
    if (opt == 'y') {
        ofstream rFile("rental.txt", ios::app);
        rFile << c.ic << " " << carID << " " << car.model << " " << " Not_Yet_Returned " << dateR << " N/A " << days << endl;
        rFile.close();
        updateCarQuantity(carID, -1); // From Admin.h
        cout << "\nCar Rented Successfully!";}
    else{
        cout << "\nTransaction Cancelled. Press any key to continue...";
    }
    cin.ignore(); cin.get();
}


void returnCar(Customer c) {
    clearScreen();
    ifstream file("rental.txt");
    vector<Rental> rentals;
    Rental r;
    bool foundAny = false;

    cout << "--- YOUR ACTIVE RENTALS ---" << endl;
    cout << left << setw(10) << "CAR ID" << setw(15) << "CAR MODEL" << setw(15) << "DATE RENTED" << endl;

    while (file >> r.customerIC >> r.carID >> r.carModel >> r.status >> r.dateRented >> r.dateReturned >> r.days) {
        if (r.customerIC == c.ic && r.status == "Not_Yet_Returned") {
            cout << left
                 << setw(10) << r.carID
                 << setw(15) << r.carModel
                 << setw(15) << r.dateRented << endl;
            foundAny = true;
        }
        rentals.push_back(r);
    }
    file.close();

    if (!foundAny) {
        cout << "No cars to return."; cin.ignore(); cin.get(); return;
    }

    string returnID, dateRet;
    cout << "\nEnter Car ID to return: "; cin >> returnID;
    cout << "Enter Today's Date (dd/mm/yyyy): "; cin >> dateRet;

    for (auto &rec : rentals) {
        if (rec.customerIC == c.ic && rec.carID == returnID && rec.status == "Not_Yet_Returned") {
            int actualDays = daysBetween(rec.dateRented, dateRet);
            int lateDays = actualDays - rec.days;

            if (lateDays > 0) {
                cout << "Late for " << lateDays << " days. Charge: RM " << lateDays * 20 << endl;
            } else {
                cout << "Returned on time." << endl;
            }

            rec.status = "Returned";
            rec.dateReturned = dateRet;
            updateCarQuantity(returnID, 1);
            cout << "\nCar Returned! Deposit of RM100 Refunded." << endl;
            cout << "\nThank you for choosing us." << endl;
            break;
        }
    }

    ofstream outFile("rental.txt");
    for (auto const& rec : rentals) {
        outFile << rec.customerIC << " " << rec.carID << " " << rec.carModel << " " << rec.status << " " 
                << rec.dateRented << " " << rec.dateReturned << " " << rec.days << endl;
    }
    outFile.close();
    cin.ignore(); cin.get();

}
