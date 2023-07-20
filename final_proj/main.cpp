/**
 * @file main.cpp
 * A simple C++ program that manipulates an image in a variety of ways.
 */

#include "cs225/PNG.h"
#include <string>
#include <fstream>
#include <vector>
#include <fstream>
#include "Airport.h"
#include "AirportGraph.h"
#include "Flight.h"
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <map>

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;
using std::istringstream;

using namespace std;




int main() {
    // Load in Airport aata
    string filename = "airports_only_neccesary_data.csv";
    ifstream myFile(filename);
    string line;
    string delim = ",";
    int count = 0;
    vector<Airport> airports;

    // Gets every line from Airport data as a single string
    while(getline(myFile, line)) {
        if (count > 0) {
            istringstream s(line);
            string field;
            vector<string> words;
            Airport example =  Airport(line);
            airports.push_back(example);
        }

        count++;
    }


    //Loading in Routes data to turn into Flights
    string filename2 = "routes_data_latest.csv";
    ifstream myFile2(filename2);
    string line2;
    string delim2 = ",";
    int count2 = 0;
    vector<Flight> flights;

    //Gets every line from Routes data as a single string
    while (getline(myFile2, line2)) {
        if (count2 > 0) {
        Flight example =  Flight(line2);
        flights.push_back(example);
		}

        count2++;
	}

    
    //Graph Creation
    AirportGraph graph; 

    //Iterates through airports vector and makes every airport a Node
    for (unsigned int i = 0; i < airports.size(); i++){
        Airport* newNode = &airports[i];
        graph.addNode(newNode);
    }

    //Iterates thorough flights vector and makes every flight path an edge
    for (unsigned int i = 0; i < flights.size(); i++){
        Flight* newEdge = &flights[i]; 
        graph.addEdge(newEdge); 
    }
  
    string source;
    string dest;
    cout << "Type a Departure Airport IATA: "; // Type a number and press enter
    cin >> source; // Get user input from the keyboard
    transform(source.begin(), source.end(), source.begin(), ::toupper); //Converts input to capitalization
    cout << "\n" << "The airport you are departing from is: " << source << endl; // Display the input value

    cout << "Type a Destination IATA: "; // Type a number and press enter
    cin >> dest; // Get user input from the keyboard
    transform(dest.begin(), dest.end(), dest.begin(), ::toupper); //Converts input to capitalization
    cout << "\n" << "Your destination airport is: " << dest << endl; // Display the input value
   
    cout << "\n" << "Press 1 for least transfers (BFS) or 0 for least distance (Dijkstra)" <<  endl; // Display the input value
    string pathChoice; 
    cin >> pathChoice;
    
    // If BFS is chosen
    if (pathChoice == "1") {
        vector<Flight*> BFSvec = graph.bfs(source,dest);
        //CASE: Path exists. Print out order of airports
        if (BFSvec.size() != 0 ) {
            cout << "The order of airports that you visit is:" << endl;
            cout << BFSvec[0]->source_iata; //Prints out first element of vector
            
            //Prints out rest of vector
            for (unsigned int i = 1; i < BFSvec.size(); i++) {
                cout << " -> " << BFSvec[i]->source_iata;
            }

            cout << " -> " << dest << endl;
            cout << "Your path can be viewed in drawnMap.png. Thank you for using our service." << endl;
        // If there is no path between the 2 chosen airports
        }
        else if (BFSvec.size() == 0) {
            cout << "There's no path between your airports in this dataset." << endl;
        }
        graph.visualization(BFSvec);

    // If Dijkstras Algorithm is chosen
    } else if (pathChoice == "0") { 
        vector<Flight*> dijkstraPath = graph.Dijkstra(source, dest);
        //If path exists, print out all of them
        if (dijkstraPath.size() != 0 ) {
            cout << "The order of airports that you visit is:" << endl;
            cout << dijkstraPath[0]->source_iata; //Prints out first element of vector
            
            //Prints out rest of vector
            for (unsigned int i = 1; i < dijkstraPath.size(); i++) {
                cout << " -> " << dijkstraPath[i]->source_iata;
            }

            cout << " -> " << dest << endl;
            cout << "Your path can be viewed in drawnMap.png. Thank you for using our service." << endl;
        //If there are no paths in the vector
        } else if (dijkstraPath.size() == 0 ) {
            cout<<"There's no path between your airports in this dataset."<<endl;
        }
        
        graph.visualization(dijkstraPath);

    // If there is an invalid input
    } else {
        cout << "INVALID INPUT. Please start over." << endl;
        
    }
	
  
    return 0; 

  
}
