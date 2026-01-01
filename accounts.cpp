#include "accounts.h"
#include "errorhandling.h"
#include <iostream>
#include <fstream>

using namespace std;

void clearScreen(); 

void customerinterface(){
    clearScreen(); 
    int custChoice;
    cout << "------------------------------------" << endl;
    cout << "     Already have an account?       " << endl;
    cout << "------------------------------------" << endl;
    cout << "1. Login\n2. Register\n\nChoice: ";
    cin >> custChoice;
    if (custChoice == 1) customerLogin();
    else if (custChoice == 2) customerRegister();
}

void customerRegister() {
    Customer c;
    cout << "\n------------------------------------" << endl;
    cout << "        Create your Account         " << endl;
    cout << "------------------------------------" << endl;
    cout << "\nDo you have a valid driving license? (y/n): ";
    char lic;
    cin >> lic;

    if (lic != 'y' && lic != 'Y') {
        cout << "\nYou must have a valid driving license to register.";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "Enter Name: "; cin >> c.name;

    do {
        cout << "Enter IC (12 digits): ";
        cin >> c.ic;
        if (!isValidIC(c.ic))
            cout << "Invalid IC. Must be exactly 12 digits.\n";} 

    while (!isValidIC(c.ic));{
        cout << "Enter Name: "; cin >> c.name;
        cout << "Enter IC: "; cin >> c.ic;
        cout << "Enter Contact: "; cin >> c.contact;
        cout << "Create Password: "; cin >> c.password;

        ofstream file("customer.txt", ios::app);
        file << c.name << " " << c.ic << " " << c.contact << " " << c.password << endl;
        file.close();
        cout << "Registration Successful!";
        cin.ignore(); cin.get();}
}

void customerLogin() {
    string ic, pass;
    cout << "\n------------------------------------" << endl;
    cout << "     Login into your Account        " << endl;
    cout << "------------------------------------" << endl;
    cout << "Enter IC: "; cin >> ic;
    cout << "Enter Password: "; cin >> pass;

    ifstream file("customer.txt");
    Customer c, foundCust;
    bool found = false;
    while (file >> c.name >> c.ic >> c.contact >> c.password) {
        if (c.ic == ic && c.password == pass) {
            found = true;
            foundCust = c;
            break;
        }
    }
    file.close();
    if (found) customerMenu(foundCust);
    else { cout << "Invalid Login!"; cin.ignore(); cin.get(); }
}