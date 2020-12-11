# jkang74-youtsey2-renzol2-kgs5
Final Project

## Current usage

There are two ways to utilize the algorithms created in this final project. The first uses the main.cpp file. After compiling, the functions that run in main use a graph based on the OpenFlights dataset. The test.cpp file uses simpler graph structures to make it easier to check if the algorithms are achieving their purposes. 

## Breadth First Search traversal

Our implementation of the BFS traversal takes in an integer argument that determines the minimum number of outgoing direct routes that an airport should have. In order to return a traversal of the entire graph in a vector, enter 0 as the argument. To return the top 28 airports, enter 100.

## Dijkstra's Algorithm and A* Search

For Dijkstra's Algorithm and A* Search, enter a valid source ID and destination ID. These IDs are based on OpenFlight airport IDs listed in the airports.dat.txt file. These IDs are the first value in each line of the text file. 

## Dijkstra's Algorithm and A* Search Paths Function

Another function in main runs a number of shortest paths based on the inputted range argument. These shortest paths start from Hartsfield-Jackson Atlanta International Airport (the airport with the highest passenger traffic in the world and one of the 28 with over 100 outgoing flight routes) and have random destinations.  Writing "time" before calls to these paths functions will display the runtime. Although running a Dijkstra's paths function followed by an A* paths function will not have the same paths, the A* paths function will run faster on average when each function is given the same range of paths.

### Compiling
```
make
make test
```

### Running
```java
./main bfs DIRECT_ROUTES
./main dj SOURCE_ID DESTINATION_ID
./main astar SOURCE_ID DESTINATION_ID
./main paths dj RANGE
./main paths astar RANGE

./test
```
