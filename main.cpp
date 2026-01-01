#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

//including files
#include "accounts.h"
#include "admin.h"
#include "billing.h"
#include "cars.h"
#include "menu.h"
#include "rentals.h"
#include "errorhandling.h"

using namespace std;

// Global Helper
void clearScreen() { system("cls"); }

int main() {
    int choice;
    while (true) {
        clearScreen();
        cout << "====================================" << endl;
        cout << "         CAR RENTAL SYSTEM          " << endl;
        cout << "====================================" << endl;
        cout << "1. Admin Mode\n2. Customer Mode\n3. Exit\n\nChoice: ";
        cin >> choice;

        if (choice == 1) adminLogin();
        else if (choice == 2) customerinterface();
        else break;
    }
    return 0;
}



