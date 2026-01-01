#include "rentals.h"
#include "cars.h"
#include "admin.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <ctime>

using namespace std;

// Helper from main
void clearScreen();

// Helper for date conversion
time_t toTime(string date) {
    tm t = {};
    t.tm_mday = stoi(date.substr(0, 2));
    t.tm_mon  = stoi(date.substr(3, 2)) - 1;
    t.tm_year = stoi(date.substr(6, 4)) - 1900;
    return mktime(&t);
}

int daysBetween(string start, string end) {
    time_t d1 = toTime(start);
    time_t d2 = toTime(end);
    return difftime(d2, d1) / (60 * 60 * 24);
}

void viewMyRentals(Customer c) {
    ifstream file("rental.txt");
    Rental r;
    cout << "\n--- YOUR HISTORY ---" << endl;
    cout << left
         << setw(10) << "CAR ID"
         << setw(15) << "CAR NAME"
         << setw(20) << "STATUS"
         << setw(15) << "RENT DATE"
         << setw(15) << "RETURN DATE"
         << endl;    
    while (file >> r.customerIC >> r.carID >> r.carModel >> r.status
                >> r.dateRented >> r.dateReturned >> r.days) {
        if (r.customerIC == c.ic) {
        cout << left
             << setw(10) << r.carID
             << setw(15) << r.carModel
             << setw(20) << r.status
             << setw(15) << r.dateRented
             << setw(15) << r.dateReturned
             << endl;  
        }
    }
    file.close();
}

void viewAllRentals() {
    clearScreen();
    ifstream file("rental.txt");
    Rental r;
    cout << "\n--- ALL CUSTOMER RENTALS ---" << endl;
    cout << left
         << setw(15) << "CUSTOMER IC"
         << setw(10) << "CAR ID"
         << setw(15) << "CAR NAME"
         << setw(20) << "STATUS"
         << setw(15) << "RENT DATE"
         << setw(15) << "RETURN DATE"
         << endl;
    while (file >> r.customerIC >> r.carID >> r.carModel >> r.status
                >> r.dateRented >> r.dateReturned >> r.days) {
        cout << left
             << setw(15) << r.customerIC
             << setw(10) << r.carID
             << setw(15) << r.carModel
             << setw(20) << r.status
             << setw(15) << r.dateRented
             << setw(15) << r.dateReturned
             << endl;    
    }
    file.close();
}