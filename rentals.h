#ifndef rentals_h
#define rentals_h

#include <string>
#include "accounts.h" // Needed because viewMyRentals uses the Customer struct

using namespace std;

struct Rental {
    string customerIC, carID, carModel, status, dateRented, dateReturned;
    int days;
};

// Function Prototypes
void viewMyRentals(Customer c);
void viewAllRentals();
void rentCar(Customer c);
void returnCar(Customer c);

// Date Helpers (moved here since they relate to rental calculations)
int daysBetween(std::string start, std::string end);

#endif