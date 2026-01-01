#include "errorhandling.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool isValidIC(const string& ic) {
    if (ic.length() != 12) return false;
    for (char c : ic) {
        if (!isdigit(c)) return false;
    }
    return true;
}