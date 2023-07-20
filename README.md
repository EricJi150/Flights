FALL21 CS225 Final Project
Written By: ericji3, monaj22, arehma21, lhdou2

Presentation Link (log into google @illinois account to view): https://drive.google.com/file/d/1eGdJk45mczPofHRn7VN908U5jofHv0lC/view?usp=sharing

Downloading and Viewing Code On Your Own Machine:
1) From the terminal, run "git clone https://github-dev.cs.illinois.edu/cs225-fa21/ericji3-monaj22-arehma21-lhdou2"
2) Navigate to directory title "ericji3-monaj22-arema21-lhdou2" and then to "final_proj" to view all the code
3) Airport class can be found in "Airport.cpp" and "Airport.h"
4) Flight class can be found in "Flight.cpp" and "Flight.h"
5) Graph implementation, BFS, djikstra's, and visualation algorithm can all be found in "AirportGraph.cpp" and "AirportGraph.h"


Viewing Dataset:
1) Original dataset can be viewed on "https://openflights.org/data.html"
2) Processed airport data can be found in "final_proj/airports_only_necessary_data.csv"
3) Processed flight data can be found in "final_proj/routes_data_latest.csv"

Building and Running The Program:
1) From the terminal run "cd ericji3-monaj22-arehma21-lhdou2"
2) From the terminal run "cd final_proj"
3) From the terminal, run "$ make" to build project
4) From the terminal, run "$ ./final_project" to run project
5) Type a valid IATA in all caps for departure airport and press ENTER
6) Type a valid IATA in all caps for desitination airport and press ENTER
7) Type "0" to find path of least distance or "1" for path of least transfers and press ENTER
8) Information regarding flight will be printed out in terminal
9) Open "final_proj/drawnMap.png" to see visualization on world map

Building and Running All Tests:
1) From the terminal, run "$ make test" to build test cases
2) From the terminal, run "$ ./test" to run all test cases

Test Airport and Flight Parsing:
1) After building test cases, Airport and Flight parsing tests can be run with the test name (i.e "./test "Check Airport Constructor Parsing Data Correctly" ")
2) There are test cases that check if sample Airport and Flight data can be parsed correctly with the appropriate constructors and all variables of the objects created are tested

Test Dijkstra and BFS:
1) After building test cases, each BFS test case can be run with the test name (i.e. "./test "2 Airports, 1 flight" ")
2) There are test cases that test whether BFS runs for a small sample size as well as a slightly larger sample size and test if the vector BFS returns contains the correct flights in the correct order
3) There are test cases that test whether Dijkstra selects the correct algorithm between picking LEAST NODES and LEAST DISTANCE (./test "Dijkstra Picks Correct Path")
4) There are also edge test cases that test inputting invalid source and destination airports as well as situations where there are no flights from 2 nodes.

Test Visualization:
1) After building test cases, run each visualition test case one by one with test name (i.e. "./test "Visualization Simple NE from origin"")
2) There are test cases to test paths to all four quadrants of the map, straight up and down paths, and paths including transfers
3) All solutions to each visualization test case can be found in the tests directory
4) Compare output with solution (i.e. "diff drawnMap.png tests/solnSimpleNE.png")
