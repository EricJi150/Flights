/**
 * @file Flight.h
 * Declarations of flight path creation functions
 */

#pragma once
#include "Airport.h"
#include <string>

using std::string;

using namespace std;

class Flight {
    public:
        
        /**
         * Creates a Flight by splitting input based on commas and initializes data
         * @param start one excel line from flights excel sheet
         */ 
        Flight(string start);

        /**
         * Custom constructor that only sets source IATA and end IATA
         * Default sets longitude and latitude to 1
         * Mostly used for testing purposes
         * @param start Source IATA
         * @param end Destination IATA
         */
        Flight(string start, string end); 

        string getSource(); // Source IATA getter
        string getDestination(); // Destination IATA getter


        //Member Variables    
        string source_iata; 
        double source_lat;
        double source_long; 
        string dest_iata;
        double dest_lat;
        double dest_long; 
        double distance;         
};