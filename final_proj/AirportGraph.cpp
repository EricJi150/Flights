/**
 * @file AirportGraph.cpp
 * Implementations of airport graph creation functions.
 */

#include "AirportGraph.h"
#include <iostream> 
#include <cmath>
#include <queue> 
#include <stack>

using std::string;
using std::vector;
using std::queue;
using std::map;

AirportGraph::AirportGraph() {

}

void AirportGraph::addNode(Airport* node) {
    //set the iata of node mapped to the number of added airports and incrementing size
    IndexMap[node->iata] = size;
    IATAMap[size] = node->iata;
    size++;

    //add extra column of NULL to matrix
    vector<Flight*> newCol;
    for (int i = 0; i < size; i++) {
        if (size != 1) newCol.push_back(NULL);
    }
    matrix.push_back(newCol);

    //add extra row to every column of matrix
    for (unsigned int col = 0; col < matrix.size(); col++) {
        matrix[col].push_back(NULL);
    }

}

void AirportGraph::addEdge(Flight* edge) {
    
    //get Iata of Source and Destination
    string sourceIata = edge->getSource();
    string destinationIata = edge->getDestination();

    //find index of source and destination on matrix
    int sourceIndex = IndexMap[sourceIata];
    int destinationIndex = IndexMap[destinationIata];

    //set index to the pointer to the edge
    matrix[sourceIndex][destinationIndex] = edge;
    
}

vector<int> AirportGraph::adjacentNodes(string IATA_) {
    //find the index of the airport using the IATA
    int AirportIndex = IndexMap[IATA_];

    //create empty vector that will contain neighbors
    vector<int> neighbors;

    //iterate through the index and add none null indexes as neighbors
    for (unsigned int i = 0; i < matrix[AirportIndex].size(); i++) {
        if (matrix[AirportIndex][i] != NULL) {
            neighbors.push_back(i);
            std::cout<<i<<std::endl;
        }
    }

    //return vector filled with neighbor indexes
    return neighbors;
}

vector<Flight*> AirportGraph::bfs(string start, string end)
{
    // Visited vector sets all values to false
    vector<bool> visited(size, false);
    queue<int> q;
    map<string, string> routes; //(Key, Value) = (Destination IATA, Source IATA)
    vector<string> path;
    vector<Flight*> flightsVector;

    //Checks if the start value is in matrix
    if (IndexMap.find(start) == IndexMap.end()) {
        return flightsVector;
    }

    //Checks if end value is in matrix
    if (IndexMap.find(end) == IndexMap.end()) {
        return flightsVector;
    }

    int startInt = IndexMap[start];

    // Pushes source airport onto the queue
    q.push(startInt);
    int destInt = IndexMap[end];

    // Set source as visited
    visited[startInt] = true;
    int current;

    // Loops until either queue is empty or destination has been hit
    while (!q.empty() && current != destInt) {
        // Sets current as the front of the queue
        current = q.front();
        // Pops the first value
        q.pop();         
  
        // Traverses entire row of matrix and pushes all routes to queue
        for (unsigned int i = 0; i < matrix[current].size(); i++) {
            // Adds routes to queue if current isnt the destination, 
            // it hasnt been visited, and there is a route between the two airports.
            if (current != destInt && matrix[current][i] != NULL && (!visited[i])) {     
                // Push the adjacent node to the queue
                q.push(i);

                // Set visited to true
                visited[i] = true;

                //Finds IATA of source and destination
                string sourceStr = IATAMap[current];
                string destStr = IATAMap[i];
                
                //(Key, Value) = (Destination IATA, Source IATA)
                routes[destStr] = sourceStr;
            }
        }
    }

    //Checks if the destination was found or not
    if (IATAMap[current] != end) {
        return flightsVector;
    }

    string currentAirport = end;
    path.push_back(currentAirport);

    //Starts from destination airport and goes backwards to find path to airport from destination airport
    while (currentAirport != start) {
        currentAirport = routes.find(currentAirport)->second;
        path.push_back(currentAirport);
    }

    //Reverses path vector to go from source to destination
    reverse(path.begin(), path.end());

    //Converts vector that contains airports to a vector of Flight* 
    for (unsigned i = 0; i < path.size() - 1; i++) {
        string sourceStr = path[i];
        int sourceIndex = IndexMap[sourceStr];

        string destStr = path[i + 1];
        int destIndex = IndexMap[destStr];

        Flight* newFlight = matrix[sourceIndex][destIndex];

        flightsVector.push_back(newFlight);     
    }

    return flightsVector;

}
//returns shortest distance
vector<Flight*> AirportGraph::Dijkstra(string src, string dest) {
    //Number of vertices
    int V = size; 
    vector<Flight*> pathResult; 
    
    
    
    //Checks if the start value is in matrix
    if (IndexMap.find(src) == IndexMap.end()) {
        return pathResult;
    }

    //Checks if end value is in matrix
    if (IndexMap.find(dest) == IndexMap.end()) {
        return pathResult;
    }
    int destInt = IndexMap[dest];
    int srcInt = IndexMap[src];
    int dist[V]; //Output array for distances
    bool sptSet[V]; // i.e the "visited" array
    
    //Initialize distances to infinity, 'visited' to none
    for (int i = 0; i < V; i++) {
        pathResult.push_back(NULL); 
        dist[i] = INT_MAX; //INT_Max is essential infinity
        sptSet[i] = false;
    }

    //Distance from source to itself = 0
    dist[srcInt] = 0; 
   
    //Find shortest path for vertices
    for (int count = 0; count < V ; count++) {
        //Pick min dist vertex from set not processed
        int u = minDistance(dist, sptSet);
        
    
        //At destination node
        if (u == destInt) {
            std::cout<<"The shortest path between "<<src<<" and "<<dest<<" is "<<dist[u]<<" km "<<endl;
            std::cout<<"Estimated gas fees for this flight are "<<int(dist[u] *5 * 1.69 * .62)<< " dollars "<<endl;
            
            break;
        }
        //Mark as visited
        sptSet[u] = true;

        //Update dist of neighbor vertices
        for (int v = 0; v < V; v++) {

            //Avoid segfault with if statement
            if (matrix[u][v] != NULL) {
                if (!sptSet[v]  && dist[u] != INT_MAX && dist[u] + matrix[u][v]->distance < dist[v]) {
                    //at the index of the vertex, update dist array to cheaper value
                    pathResult.at(v) = matrix[u][v]; 
                    
                    dist[v] = dist[u] + matrix[u][v]->distance; 

                }
            }

        }
        


    }
    stack<Flight*> s; 
    
    stack<Flight*> path = printPath(pathResult,destInt,dest,s);
    vector<Flight*> pathVector;

  //Stack of flights is added to vector
    while(path.size() != 0){
        
        pathVector.push_back(path.top());
        path.pop();
      
    }
  

    return pathVector;


}

//Creates a stack of flights visited to be added into the vector
stack<Flight*> AirportGraph::printPath(vector<Flight*> pathResult, int j, string dest, stack<Flight*> s){
    if (pathResult[j] == NULL){
        
        return s; 
    }
    if (pathResult[j] != NULL){
    
     s.push(pathResult[j]);
    }
   
    j = IndexMap[pathResult[j]->source_iata]; 
    return printPath(pathResult,j,dest,s); 
    

}




int AirportGraph::minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX;
    int min_index;
    for (int v = 0; v < size; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v]; 
            min_index = v; 
        }

    }
    return min_index; 
}

void AirportGraph::visualization(vector<Flight*> path) {

    //read png as the map png
    cs225::PNG map;
    map.readFromFile("map.png");

    //if no flights then return blank map
    if (path.size() == 0){
        map.writeToFile("drawnMap.png");
        return;
    }
    //get start location on map
    int sourceX = round(longDegToPixel(path[0]->source_long));
    int sourceY = round(latDegToPixel(path[0]->source_lat));   

    //make pixels in a box colored
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            cs225::HSLAPixel& pixel = map.getPixel(sourceX - 5 + x, sourceY - 5 + y);
            pixel.h = 120;
            pixel.s = 1;
            pixel.l = .5;
            pixel.a = 1;
        }
    }

    //initialize desitnation coordinates
    int destX;
    int destY;


    //add location and path for the rest of the flights
    for (int i = 0; i < (int)path.size(); i++) {
        //get destination location on map
        destX = round(longDegToPixel(path[i]->dest_long));
        destY = round(latDegToPixel(path[i]->dest_lat));
       
        //make destination colored
        for (int x = 0; x < 10; x++) {
            for (int y = 0; y < 10; y++) {
                cs225::HSLAPixel& pixel = map.getPixel(destX - 5 + x, destY - 5 + y);
                pixel.h = 0;
                pixel.s = 1;
                pixel.l = .5;
                pixel.a = 1;
            }
        }

        //get line equation between start and dest
        double X1 = sourceX;
        double X2 = destX;
        double Y1 = sourceY;
        double Y2 = destY;
        if (X2 < X1) {
            X1 = destX;
            X2 = sourceX;
            Y1 = destY;
            Y2 = sourceY;
        }

        //if slope is zero just draw a straight line and go to next flight
        if (X1 == X2) {
            if (Y2 < Y1) {
                int temp = Y1;
                Y1 = Y2;
                Y2 = temp;
            }
            for (int y = Y1; y <= Y2; y++) {
                for (int j = 0; j < 2; j++) {
                    for (int k = 0; k < 2; k++) {
                        cs225::HSLAPixel& pixel = map.getPixel(X1 -1 + j, y - 1 + k);
                        pixel.h = 0;
                        pixel.s = 1;
                        pixel.l = 0;
                        pixel.a = 1;
                    }
                }
            }
            //mark start as end
            sourceX = destX;
            sourceY = destY;
            continue;
        }

        //calculate slope and y intecept for line equation
        double slope = (Y2 - Y1) / (X2 - X1);
        double yInt = (Y2 - slope * X2);

        //draw the line
        for (int x = X1; x <= X2; x++) {
            int y = round(slope * x + yInt);
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    cs225::HSLAPixel& pixel = map.getPixel(x - 1 + j, y - 1 + k);
                    pixel.h = 0;
                    pixel.s = 1;
                    pixel.l = 0;
                    pixel.a = 1;
                }
            }
            
        }
        
        //mark start as end
        sourceX = destX;
        sourceY = destY;
    }
    //save drawn map to drawnMap.png
    map.writeToFile("drawnMap.png");
}

int AirportGraph::latDegToPixel(int degree) {
    return 518 - degree * 5.7166;
}

int AirportGraph::longDegToPixel(int degree) {
    return 1029 + degree * 5.75;
}