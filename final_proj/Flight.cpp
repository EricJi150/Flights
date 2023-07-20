/**
 * @file Flight.cpp
 * Implementations of flight path creation functions.
 */

#include "Flight.h"
using namespace std;


Flight::Flight(string input) {
    // Loads in string
    istringstream s(input);
    int count = 0;
    string field;

    // Break up string into different parts using commas
    while (getline(s, field, ',')) {
        // Count is associated with a cell in the excel sheet
        // 0 = Source IATA, 2 = Source Longitude, 3 = Source Longitude
        // 4 = Destination IATA, 6 = Destination Latitude, 7 = Destination Longitude
        // 8 = Distance
        if (count == 0) {
            this-> source_iata = field;
		}

        if (count == 2) {
            this->source_lat = stold(field);
        }

        if (count == 3) {
            this->source_long = stold(field);
        }

        if (count == 4) {
            this->dest_iata = field;
        }

        if (count == 6) {
            this->dest_lat = stold(field);
        }

        if( count == 7) {
            this->dest_long = stold(field);
        }

        if (count == 8) {
            this->distance = stold(field);
        }

        count++;
	}
}

Flight::Flight(string start, string end):source_lat(1), source_long(1),distance(100) {
    source_iata = start; 
    dest_iata = end; 
}

std::string Flight::getSource() {
    return source_iata;
}

std::string Flight::getDestination() {
    return dest_iata;
}