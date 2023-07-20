
#### Leading Question

Airline data can be used to optimize many different aspects of a flight. For our project, we are focusing on the cheapest **flight in terms of fuel costs** between 2+ airports and the **shortest flight** given 2+ airports. The **order** of the airports visited will be acquired and projected onto a visualization of a map. 

#### Dataset Acquisition and Processing 
We will be using the OpenFlights data from here: <https://openflights.org/data.html>. We will be using the 2 MB routes.dat file. It is a .txt comma separated file. Each node represents an airport and edges connect airports that have flights between them. The node also contains the longitude and latitude data of that airport, the city of the airport, and the country. The weight of the edges is the distance calculated by inserting the longitude latitude data between two airports into the Haversine Equation, specified here:



Fuel costs are calculated as follows: 

`	`1 gallon of airline fuel in 2017 cost $1.69

`	`Airplanes burn approximately 5 gallons of fuel per mile. 

`	`COST = 1.69 \* 5 \* distance 

The cost will be added into the data sheet using a simple algebraic Excel function for each node. Ex: 



|Airport Name|Longitude|Latitude|Distance|Cost|
| :- | :- | :- | :- | :- |
|London |43|81|*Calculated by Haversine and inserted to data via Excel*|<p>*Calculated by* </p><p>*DISTANCE \* 1.69 \* 5  via Excel*</p>|


Some errors within our data that we may encounter is missing data and out of range data. In the case of missing data, if the name is missing, we will just rename the data to “unlisted.” This will be done using Python. In the case that our latitude data is outside of the range of -90 to 90 and/or our longitude data is outside of -180 to 80 or is missing, then we will replace that information with a random number generated in the appropriate range.



#### Graph Algorithms

*Graphical Representation*

Using C++, we will create an adjacency list to store the edges and corresponding nodes of our graph. The following algorithms will be used to acquire the desired outputs from our data:


- Dijkstra’s algorithm 
  - Significance of the algorithm: Input the starting airport and the desired destinations. Returns the path with the smallest weight. In our case, the weight of the edges corresponds to the distance and therefore the estimated cost of the flight (for the airline, as a function of gas consumption and prices) 
  - Expected runtime: O(ElogV) where E = edges and V = vertices

- BFS 
  - Expected runtime: O(number of total airports) = O(n) 
  - Significance of the algorithm: Input starting airport and the desired destinations. Returns the path that requires the least switching between airports. That is, the shortest path (in terms of number of edges) between two nodes.

- Project on to map based on data
  - Significance of the algorithm: Input the longitude and latitude of the start and end airports. Using longitude and latitude, convert location to a pixel on a png of a scaled map. We will calculate the pixels along a straight line from the two airports and color them red to represent a line. This will be done using the Euclidean distance formula. 
  - Estimated runtime: O(n) 


#### Timeline
Starting with the week of November 8th, we have 5 weeks until the due date which is on December 13th. Data Acquisition and Processing to create the map should both be done within weeks 1 and 2 maximum. The bulk of this algorithm work will likely be completed after MP 6’s due date starting week 2. During week 2, work on the BFS Traversal and Dijkstra’s Algorithm should be started if not already ongoing. These algorithms should likely be completed within weeks 3 and 4. By the mid-project check-in, two graph algorithms should be either complete or near full completion. The third graph algorithm should be worked on after the mid-project check-in and ultimately completed by the end of semester deadline. Students not working on this second graph algorithm implementation will be assigned to work on the final presentation and are responsible for making sure the presentation adheres to the guidelines.
