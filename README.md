# ComproDatastruct

Map Navigation System

Overview: 

This program is a map navigation system that stores map data as a weighted undirected graph.

A weighted graph means that every path has a distance or cost assigned to it. For example, the path from n1 to n2 may have a distance of 135. An undirected graph means that every path can be used in both directions. If there is a path from n1 to n2, then there is also a path from n2 back to n1.

All route data is stored in a text file. The program loads this data, builds the graph, and then allows the user to interact with the map through a menu. The user can display the graph, find the shortest path, block a location, unblock a location, and display all available locations.


Project Structure: 

The program is divided into multiple files so that each part of the system has a clear responsibility.


main.c: 

This is the starting point of the program. It prepares the main system by creating the graph, initializing the blocked node system, loading map data from a file, and adding alternative names for locations. After setup, it enters the menu loop and waits for user input.

menu.c: 

This file handles user interaction. It displays the menu, reads the user's choice, and calls the correct function based on that choice. For example, if the user wants to find a route, the program asks for the start and destination locations, then sends them to Dijkstra's algorithm. If the user wants to block or unblock a location, this file calls the blocked node system.

graph.c: 

This file stores the map as a graph using an adjacency list. Each node has a list of connected nodes and the distance to each connected node. When the program adds an edge, it adds the connection in both directions because the graph is undirected.

utils.c:

This file helps with loading data from the text file and managing node names. The data file uses names such as n1, n2, and n10, but the program works more easily with numeric indexes. This file converts node names to indexes and converts indexes back to node names when displaying results.

mapping.c: 

This file is used to search for and display location information. For example, if the user enters n10, the program checks whether that node exists. It can also display all locations loaded from the map file.

block.c: 

This file manages the blocked node system. It uses an array to store whether each node is blocked. A value of 1 means the node is blocked, while a value of 0 means the node is available. This system is used together with Dijkstra's algorithm so that the shortest path does not pass through blocked locations.

alternative.c: 

This file handles alternative names for nodes. For example, the user may not remember n10, but may remember the name Library. The program allows an easy-to-read name to be linked to a real node ID. When finding a path, the user can type the alternative name instead of the node ID.

pq.c: 

This file implements a priority queue using a min-heap. It is used by Dijkstra's algorithm to quickly select the node with the smallest current distance. The priority queue stores nodes together with their distances, and the node with the lowest distance is removed first.

Dijkstra's Algorithm: 

Dijkstra's algorithm is used to find the shortest path from a starting node to another node in a graph with positive edge weights.

The basic idea is to first set the distance from the start node to every other node as infinity. The distance from the start node to itself is set to 0. The algorithm then repeatedly selects the unvisited node with the smallest distance and updates the distances of its neighboring nodes. This continues until the shortest path is found.

In this program, Dijkstra's algorithm is improved in two important ways.

First, the program uses a priority queue instead of manually searching for the node with the smallest distance every time. Without a priority queue, the program would need to scan all nodes repeatedly. With a priority queue, nodes are ordered by distance, so the node with the smallest distance can be selected more efficiently.

Second, the program supports blocked nodes. Before finding a path, the program checks whether the start or destination node is blocked. If either one is blocked, the path search does not continue. While Dijkstra's algorithm is running, any neighboring node that is blocked is skipped. This means the final route will avoid blocked locations, even if the blocked route would normally be the shortest path.

Because of this, the program does not only find the shortest path. It finds the shortest usable path based on the current blocked locations.