/**
 * @file Airport.h
 * Declarations of Airport creation functions
 */

#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <utility> 
#include <stdexcept> 
#include <sstream>
#include <map>

using namespace std;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;
using std::istringstream;

class Airport {
    public:
    /**
     * Creates Default Airport with empty IATA string and longitude and latitude -200.0
     */
    Airport();

    /**
     * Creates an Airport by splitting the input based on commas and initializing data 
     * @param input one excel line from airport excel sheet
     */
    Airport(string input);


    //Member variables
    string iata;
    double latitude;
    double longitude;
};