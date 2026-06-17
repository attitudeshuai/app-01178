#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>

using namespace std;

bool isValidInput(const string& s) {
    for (char c : s) {
        if (c < 'a' || c > 'z') {
            return false;
        }
    }
    return true;
}

#endif
