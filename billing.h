#ifndef BILLING_H
#define BILLING_H

#include "accounts.h"
#include "cars.h"
#include "rentals.h"
#include <string>
#include <vector>

// Transaction Functions
void rentCar(Customer c);
void returnCar(Customer c);

// Date Helpers (used for late fees)
int daysBetween(std::string start, std::string end);

#endif