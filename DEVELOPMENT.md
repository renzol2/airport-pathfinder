Development of the CS 225 Final Project

Week of 11/23/20

This week, we set up the initial files for the project. We copied the files from lab_ml representing a basic graph structure for use in our own project. We also used the Makefile framework from the Final Project Demo on Github. In the interests of dividing the work equally amongst our group's members, we created individual files for the three major algorithms that we will be creating, namely the Breadth First Search (BFS) algorithm, Dijkstra's Shortest Path algorithm, and the Landmark Path algorithm. We have also written some initial code for reading in CSVs into a graph structure of airports (vertices) and routes (edges). 

Week of 11/30/20

In the second week of the project, we succeeded in reading basic data from a CSV format into a graph structure. We completed the code for a Breadth First Search traversal of the graph which, for the time being, prints the airports with at least 100 connections to other unique airports. We also began the implementation of A* search, which will replace the Landmark Path algorithm as our Complex/Uncovered option.

Week of 12/7/20

In the third week of the project, we finished our implementation of Dijkstra's algorithm and A* search by refactoring the original Graph implementation and using latitude/longitude coordinates as a heuristic. We also implemented better command line functionality to our application, allowing the user to choose parameters for our BFS, Dijkstra's, and A* functions. We also added a method in our application to generate random paths for Dijkstra's and A* to calculate, letting the user compare their runtimes. Finally, as a group, we imported CATCH testing library into our project and wrote test cases for each of our three algorithms.
