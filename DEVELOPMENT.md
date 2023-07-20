DEVELOPMENT – A document with exactly one paragraph per week, describing what was accomplished or attempted in that week. 
For full credit, your team must add a paragraph to this document every week (starting the week project goals are confirmed). 
You are strongly encouraged to as a git commit.

Week 11/15:
This week, we started and began attempting to preprocess our data and began replacing all of the null airport IDs with information 
from the routes data and missing IATA’s with information from the airport data. Any other data that can not be found between both 
sheets were deleted. Additionally, we also began to calculate the distance using the haversine formula.

Week 11/22
This week we began working on importing and reading our data to store our data into classes. We are attempting to store our airport 
data as nodes and the flight routes as edges. Additionally, we started working on creating our adjacency matrix.

Week 11/29
Finished creating nodes (airports) and edges (flights) classes and importing all of our data into these classes. This week we started 
working on our BFS traversal and began making sure that everyone was able to access the files correctly.

Week 12/5
We finished BFS and our adjacency matrix. We made sure that our BFS returns an Airport* vector. This week we will work on finishing implementing
our Dijkstra algorithm and map implementation as well ascompleting our presentation, readme, and test cases. We also repreprocessed some of our data
because there were flight paths that did not have airports. We will also work on creating test cases for our BFS.

Week 12/12
We finished Dijkstra algorithm which also returns an Airport* vector and the visualization and are wrapping up the project by finishing up written 
report and the presentation. The visualization now creates a png that has the starting point as a green box and any resulting destinations as red
boxes connected by a black line. There are also test cases for Dijkstra's algorithm and solution images for the graph visualization
