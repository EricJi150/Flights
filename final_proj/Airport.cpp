/**
 * @file Airport.cpp
 * Implementations of airport creation functions.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <map>

#include "Airport.h"

using namespace std;

Airport::Airport() {
    this->iata = "";
    this->latitude = -200.0;
    this->longitude = -200.0;
}

Airport::Airport(string input) {
    // Loads in string
    istringstream s(input);
    int count = 0;
    string field;

    // Break up string into different parts
    while (getline(s, field,',')) {
        // Count is associated with a cell in the excel sheet
        // 0 = IATA, 1 = Latitude, 2 = Longitude
        if (count == 0) {
           this->iata = field;
		}

        if (count == 1) {
            this->latitude = std::stold(field);
        }

        if (count == 2) {
            this->longitude = std::stold(field);
        }
        
        count++;
	}
    
}