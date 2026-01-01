#ifndef accounts_h
#define accounts_h

#include <string>
#include <vector>

struct Customer {
    std::string name, ic, contact, password;
};

// Declarations only
void customerRegister();
void customerLogin();
void customerMenu(Customer currentCust);
void customerinterface();

#endif