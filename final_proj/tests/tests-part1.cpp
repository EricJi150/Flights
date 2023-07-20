#include "../cs225/catch/catch.hpp"

// #include "../lab_intro.h"
// #include "../cs225/PNG.h"
// #include "../cs225/HSLAPixel.h"

// using cs225::HSLAPixel;
// using cs225::PNG;
#include <string>

#include "../Airport.h"
#include "../AirportGraph.h"
#include "../Flight.h"

using std::string;


//Insert test cases that check if data is in the right place
TEST_CASE("Check Airport Constructor Parsing Data Correctly", "[weight=1]") {
  vector<Airport> airports;
  string line = "AAA,12,456";
  Airport example =  Airport(line);
  airports.push_back(example);

  REQUIRE(airports[0].iata == "AAA");
  REQUIRE(airports[0].latitude == 12);
  REQUIRE(airports[0].longitude == 456);
}

TEST_CASE("Check Flight Constructor PArsing Data Correctly", "[weight=1]") {
  vector<Flight> flights;
  string line = "AAA,5,12,34,BBB,6,56,78,999";
  Flight example = Flight(line);
  flights.push_back(example);

  REQUIRE(flights[0].source_iata == "AAA");
  REQUIRE(flights[0].source_lat == 12);
  REQUIRE(flights[0].source_long == 34);
  REQUIRE(flights[0].dest_iata == "BBB");
  REQUIRE(flights[0].dest_lat == 56);
  REQUIRE(flights[0].dest_long == 78);
  REQUIRE(flights[0].distance == 999);
}


//BFS Test Cases

//Only 2 Airports and 2 Possible flight
TEST_CASE("2 Airports 1 flight", "[weight=1]") {
  Airport* a = new Airport();
  a->iata = "AAA";

  Airport* b = new Airport();
  b->iata = "BBB";

  Flight* aToB = new Flight("AAA", "BBB");

  AirportGraph fakeGraph;

  fakeGraph.addNode(a);
  fakeGraph.addNode(b);

  fakeGraph.addEdge(aToB);

  vector<Flight*> testVector = fakeGraph.bfs("AAA","BBB");

  REQUIRE(testVector.size() == 1);
  REQUIRE(testVector[0]->source_iata == "AAA");
  REQUIRE(testVector[0]->dest_iata == "BBB");

}

//4 Airports 5 Flight paths test case
//Makes sure that BFS returns a vector with the Flights in the right order
TEST_CASE("Larger Number of Airports and Flights", "[weight=1]") {
  Airport* a = new Airport();  
  a->iata = "AAA";
  Airport* b = new Airport(); 
  b->iata = "BBB";
  Airport* c = new Airport();  
  c->iata = "CCC"; 
  Airport* d = new Airport(); 
  d->iata = "DDD";

  Flight* aToB = new Flight("AAA","BBB");

  Flight* bToC = new Flight("BBB","CCC");

  Flight* cToD = new Flight("CCC","DDD");

  Flight* bToD = new Flight("BBB", "DDD"); 

  Flight* dToA = new Flight("DDD", "AAA");

  AirportGraph fakeGraph;
  fakeGraph.addNode(a);
  fakeGraph.addNode(b);
  fakeGraph.addNode(c);
  fakeGraph.addNode(d); 
  fakeGraph.addEdge(aToB);
  fakeGraph.addEdge(bToC);
  fakeGraph.addEdge(cToD);
  fakeGraph.addEdge(bToD);
  fakeGraph.addEdge(dToA);

  vector<Flight*> bfsAtoB = fakeGraph.bfs("AAA","BBB");
  vector<Flight*> bfsAtoD = fakeGraph.bfs("AAA","DDD");
  vector<Flight*> bfsCtoA = fakeGraph.bfs("CCC","AAA");
  vector<Flight*> bfsDtoC = fakeGraph.bfs("DDD","CCC");

  REQUIRE(bfsAtoB.size() == 1);
  REQUIRE(bfsAtoD.size() == 2);
  REQUIRE(bfsCtoA.size() == 2);
  REQUIRE(bfsDtoC.size() == 3);

  REQUIRE(bfsAtoB[0]->source_iata == "AAA"); 
  REQUIRE(bfsAtoB[0]->dest_iata == "BBB");

  REQUIRE(bfsAtoD[0]->source_iata == "AAA");
  REQUIRE(bfsAtoD[0]->dest_iata == "BBB");
  REQUIRE(bfsAtoD[1]->source_iata == "BBB");
  REQUIRE(bfsAtoD[1]->dest_iata == "DDD");

  REQUIRE(bfsCtoA[0]->source_iata == "CCC");
  REQUIRE(bfsCtoA[0]->dest_iata == "DDD");
  REQUIRE(bfsCtoA[1]->source_iata == "DDD");
  REQUIRE(bfsCtoA[1]->dest_iata == "AAA");

  REQUIRE(bfsDtoC[0]->source_iata == "DDD");
  REQUIRE(bfsDtoC[0]->dest_iata == "AAA");
  REQUIRE(bfsDtoC[1]->source_iata == "AAA");
  REQUIRE(bfsDtoC[1]->dest_iata == "BBB");
  REQUIRE(bfsDtoC[2]->source_iata == "BBB");
  REQUIRE(bfsDtoC[2]->dest_iata == "CCC");
}

//Invalid IATA edge case
TEST_CASE("Invalid Start IATA", "[weight=1]") {
  Airport* a = new Airport();
  a->iata = "AAA";

  Airport* b = new Airport();
  b->iata = "BBB";

  Flight* aToB = new Flight("AAA", "BBB");

  AirportGraph fakeGraph;

  fakeGraph.addNode(a);
  fakeGraph.addNode(b);

  fakeGraph.addEdge(aToB);

  vector<Flight*> testVector = fakeGraph.bfs("CCC","BBB");
  vector<Flight*> testDijkstra = fakeGraph.Dijkstra("CCC","BBB");
  REQUIRE(testVector.size() == 0);
  REQUIRE(testDijkstra.size() == 0); 
}


//Invalid IATA edge case
TEST_CASE("Invalid End IATA", "[weight=1]") {
  Airport* a = new Airport();
  a->iata = "AAA";

  Airport* b = new Airport();
  b->iata = "BBB";

  Flight* aToB = new Flight("AAA", "BBB");

  AirportGraph fakeGraph;

  fakeGraph.addNode(a);
  fakeGraph.addNode(b);

  fakeGraph.addEdge(aToB);

  vector<Flight*> testVector = fakeGraph.bfs("AAA","CCC");
  vector<Flight*> testDijkstra = fakeGraph.Dijkstra("AAA","CCC");

  REQUIRE(testVector.size() == 0);
  REQUIRE(testDijkstra.size() == 0); 
}

//No path edge case
TEST_CASE("No path", "[weight=1]") {
  Airport* a = new Airport();
  a->iata = "AAA";

  Airport* b = new Airport();
  b->iata = "BBB";

  Airport* c = new Airport();
  c->iata = "CCC";

  Flight* aToB = new Flight("AAA", "BBB");

  AirportGraph fakeGraph;

  fakeGraph.addNode(a);
  fakeGraph.addNode(b);

  fakeGraph.addEdge(aToB);

  vector<Flight*> testVector = fakeGraph.bfs("AAA","CCC");
  vector<Flight*> testDijkstra = fakeGraph.Dijkstra("AAA","CCC");
  REQUIRE(testVector.size() == 0); 
  REQUIRE(testDijkstra.size() == 0);  
  
}

TEST_CASE("Dijkstra Picks Correct Path", "[weight=1]") {
  Airport* a = new Airport();
  a->iata = "AAA";

  Airport* b = new Airport();
  b->iata = "BBB";

  Airport* c = new Airport();
  c->iata = "CCC";

  Airport* d = new Airport(); 
  d->iata = "DDD"; 

//The flight from A->B->C has a lower total edge weight (distance) than D->C
//Despite having more stops, this algorithm should prefer A->B->C over D->C
// because it is edge weight based.
 Flight* aToB = new Flight("AAA","BBB"); 
 aToB->distance = 10; 
 Flight* dToC = new Flight("DDD","CCC");
 dToC->distance = 100;
 Flight* bToC = new Flight("BBB","CCC"); 
 bToC->distance = 10; 

  AirportGraph fakeGraph;

  fakeGraph.addNode(a);
  fakeGraph.addNode(b);
  fakeGraph.addNode(c);

  fakeGraph.addEdge(aToB);
  fakeGraph.addEdge(dToC);
  fakeGraph.addEdge(bToC);
 

  vector <Flight*> fakePath = fakeGraph.Dijkstra("AAA","CCC");

  REQUIRE(fakePath[0]->source_iata == "AAA" );  
}

TEST_CASE("Visualization Simple NE from origin", "[weight=1]") {
  Flight* aToB = new Flight("AAA", "BBB");
  aToB->source_lat = 0;
  aToB->source_long = 0;
  aToB->dest_lat = 45;
  aToB->dest_long = 45;

  AirportGraph fakeGraph;

  vector<Flight*> testVector;
  testVector.push_back(aToB);

  fakeGraph.visualization(testVector);

  //solution image found in tests folder, compare it with drawnMap.png in tests
}

TEST_CASE("Visualization Simple NW from origin", "[weight=1]") {
  Flight* aToB = new Flight("AAA", "BBB");
  aToB->source_lat = 0;
  aToB->source_long = 0;
  aToB->dest_lat = 45;
  aToB->dest_long = -45;

  AirportGraph fakeGraph;

  vector<Flight*> testVector;
  testVector.push_back(aToB);

  fakeGraph.visualization(testVector);

  //solution image found in tests folder, compare it with drawnMap.png in tests
}

TEST_CASE("Visualization Simple SE from origin", "[weight=1]") {
  Flight* aToB = new Flight("AAA", "BBB");
  aToB->source_lat = 0;
  aToB->source_long = 0;
  aToB->dest_lat = -45;
  aToB->dest_long = 45;

  AirportGraph fakeGraph;

  vector<Flight*> testVector;
  testVector.push_back(aToB);

  fakeGraph.visualization(testVector);

  //solution image found in tests folder, compare it with drawnMap.png in tests
}

TEST_CASE("Visualization Simple SW from origin", "[weight=1]") {
  Flight* aToB = new Flight("AAA", "BBB");
  aToB->source_lat = 0;
  aToB->source_long = 0;
  aToB->dest_lat = -45;
  aToB->dest_long = -45;

  AirportGraph fakeGraph;

  vector<Flight*> testVector;
  testVector.push_back(aToB);

  fakeGraph.visualization(testVector);

  //solution image found in tests folder, compare it with drawnMap.png in tests
}

TEST_CASE("Visualization Complex", "[weight=1]") {
  Flight* aToB = new Flight("AAA", "BBB");
  aToB->source_lat = 20;
  aToB->source_long = 30;
  aToB->dest_lat = -45;
  aToB->dest_long = 50;

  Flight* bToC = new Flight("BBB", "CCC");
  bToC->source_lat = -45;
  bToC->source_long = 50;
  bToC->dest_lat = 75;
  bToC->dest_long = -80;

  AirportGraph fakeGraph;

  vector<Flight*> testVector;
  testVector.push_back(aToB);
  testVector.push_back(bToC);

  fakeGraph.visualization(testVector);

  //solution image found in tests folder, compare it with drawnMap.png in tests
}

TEST_CASE("Visualization Simple straight up from origin", "[weight=1]") {
  Flight* aToB = new Flight("AAA", "BBB");
  aToB->source_lat = 0;
  aToB->source_long = 30;
  aToB->dest_lat = 30;
  aToB->dest_long = 30;

  AirportGraph fakeGraph;

  vector<Flight*> testVector;
  testVector.push_back(aToB);

  fakeGraph.visualization(testVector);

  //solution image found in tests folder, compare it with drawnMap.png in tests
}


