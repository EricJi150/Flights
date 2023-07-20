/**
 * @file AirportGraph.h
 * Declarations of airport graph creation functions
 */

#pragma once
#include <vector>
#include <map>
#include <stack>
#include "Airport.h"
#include "Flight.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
using namespace std;

class AirportGraph {

    public:
        /**
         * Creates empty airport adjacency matrix
         */
        AirportGraph(); 

        /**
         * Adds a node to the airport adjacency matrix
         * @param node Airport pointer node to be added
         */
        void addNode(Airport* node);

        /**
         * Adds an edge to the airport adjacency matrix
         * @param edge flight path to be added
         */
        void addEdge(Flight* edge);

        /**
         * Returns all potential paths the inputted airport can travel to
         * @param IATA_ The IATA of the airport we want paths from
         */
        vector<int> adjacentNodes(string IATA_); 

        /**
         * BFS traversal from source airport to destination airport
         * @param start IATA of source airport
         * @param end IATA of destination airport
         * @return Vector of Flight pointers from start to end using BFS
         */
        vector<Flight*> bfs(string start, string end);

        /**
         * Dijkstra algorithm from source airport to destination airport
         * @param src IATA of source airport
         * @param dest IATA of destination airport
         * @return Vector of Flight pointers from start to end using Dijkstra
         */
        vector<Flight*>  Dijkstra(string src, string dest);

    
       
        /**
        * Used to create stack of flights visited

        */

       stack<Flight*> printPath(vector<Flight*> pathResult, int j, string dest, stack<Flight*> s);


        /**
         * Helper function: finds vert with min distance that are not included in SPT
         * @param dist[]
         * @param sptSet[] 
         * @return 
         */
        int minDistance(int dist[], bool sptSet[]);

        /**
         * Visualization function that maps out the path between start and destination
         * @param path
         */
        void visualization(vector<Flight*> path);

        /**
         * Converts latitude degree to pixel number
         * @param degree
         * @return y index on PNG
         */
       int latDegToPixel(int degree);

        /**
         * Converts longitude degree to pixel number
         * @param degree
         * @return x index on PNG
         */
        int longDegToPixel(int degree);

        //Member variables
        vector <vector<Flight*>> matrix; //2D vector matrx of adjacency list
        map <string, int> IndexMap; //Maps IATA to index on matrix | (Key, Value) = (IATA, Index)
        map <int, string> IATAMap; //Maps index to IATA | (Key, Value) = (Index, IATA)
        int size = 0; // number of airports
};
