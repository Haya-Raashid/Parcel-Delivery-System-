# Parcel Delivery System

## Overview
The Parcel Delivery project reads a real-world-style dataset of 1,180 package records from a CSV
file, storing and indexing them in multiple data structures simultaneously to serve different 
operational needs: fast lookup, ordered traversal, dispatch queuing, workload analysis, 
and shortest-path route optimisation. 

## Features
1. Load and persist parcel data from a structured CSV file. 
2. Maintain a doubly linked list for full traversal and deletion.
3. Implements a queue for package processing.
4. Use an AVL tree to rank delivery areas by parcel volume.
5. Uses a hash table for efficient package/area lookup.
6. Implement a FIFO dispatch queue for orderly parcel processing. 
7. Apply Dijkstra’s algorithm to find optimised multi-city delivery routes.
8. 
## Data Structures and Algorithms
The project implements the following data structures and algorithms:

| Data Structure          | Purpose                                       |
---------------------------------------------------------------------------
| Doubly Linked List      | Stores and manages package records            |
| Queue                   | Processes packages in order                   |
| Binary Search Tree (BST)| Organizes delivery areas                      |
| AVL Tree                | Maintains balanced area data                  |
| Hash Table              | Provides efficient lookup                     |
| Graph                   | Represents connections between delivery areas |
| Dijkstra's Algorithm    | Finds shortest paths between locations        |

## Technologies Used
1- C++
2- File Handling
3- CSV Data
4- Data Structures
5- Graph(Dijkstra) Algorithms

## Dataset
1- package_csv: The project uses a CSV dataset containing package delivery records. 
Each package contains information such as its ID, destination, weight, and priority.
The dataset is read from a CSV file when the program runs.
2- Distances-csv: This csv is used to map distances between cities, that are used by 
the Graph as well as the Dijsktra Algorithm.

## Learning Outcomes
Through this project, I practiced:
1- Implementing data structures from scratch in C++
2- Working with linked lists, queues, trees, hash tables, and graphs
3- Implementing AVL tree rotations and balancing
4- Working with multiple CSV file input
5- Applying graph algorithms to a practical problem
