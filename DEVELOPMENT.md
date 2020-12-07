Development of the CS 225 Final Project

Week of 11/23/20

This week, we set up the initial files for the project. We copied the files from lab_ml representing a basic graph structure for use in our own project. We also used the Makefile framework from the Final Project Demo on Github. In the interests of dividing the work equally amongst our group's members, we have created individual files for the three major algorithms that we will be creating, namely the Breadth First Search (BFS) algorithm, Dijkstra's Shortest Path algorithm, and the Landmark Path algorithm. We have also written some initial code for reading in CSVs into a graph structure of airports (vertices) and routes (edges). 

Week of 11/30/20

In the second week of the project, we succeeded in reading basic data from a CSV format into a graph structure. We also completed the code for a Breadth First Search traversal of the graph which, for the time being, prints the airports with at least 100 connections to other unique airports. 

We also began the implementation of A* search, which will replace the Landmark Path algorithm as our Complex/Uncovered option.

Week of 12/7/20

Int he third week of the project, we finished our implementation of A* search by refactoring the original Graph implementation and using latitude/longitude coordinates as a heuristic. We also implemented better command line functionality to our application, allowing the user to choose parameters for BFS and A*. 
