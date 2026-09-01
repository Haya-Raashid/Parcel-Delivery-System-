# Parcel Delivery System

## Overview

The Parcel Delivery System is a C++ project that reads a dataset of 1,180 package records from CSV files and manages the data using multiple data structures. Each data structure is used to address a different operational requirement, including package management, efficient lookup, dispatch processing, workload analysis, and shortest-path route optimization.

## Features

- Load and process parcel data from structured CSV files
- Maintain a doubly linked list for package storage, traversal, and deletion
- Implement a queue for orderly package processing
- Use a Binary Search Tree (BST) to organize delivery areas
- Use an AVL tree to maintain balanced delivery-area data and analyze parcel volume
- Implement a hash table for efficient package and area lookup
- Represent connections between cities using a graph
- Apply Dijkstra's algorithm to find optimized delivery routes between cities

## Data Structures and Algorithms

The project implements the following data structures and algorithms:

| Data Structure / Algorithm | Purpose |
|---|---|
| Doubly Linked List | Stores and manages package records |
| Queue | Processes packages in FIFO order |
| Binary Search Tree (BST) | Organizes delivery areas |
| AVL Tree | Maintains balanced delivery-area data |
| Hash Table | Provides efficient package and area lookup |
| Graph | Represents connections and distances between cities |
| Dijkstra's Algorithm | Finds shortest delivery routes between cities |

## Technologies Used

- C++
- File Handling
- CSV Data Processing
- Data Structures
- Graph Algorithms
- Dijkstra's Algorithm

## Dataset

The project uses two CSV files:

- **package_dataset_1180_entries.csv:** Contains 1,180 package delivery records. Each package includes information such as its ID, destination, weight, and priority.

- **Distances.csv:** Contains distance information between cities. This data is used to construct the graph and calculate shortest delivery routes using Dijkstra's algorithm.

## Learning Outcomes

Through this project, I practiced:

- Implementing data structures from scratch in C++
- Working with doubly linked lists, queues, trees, hash tables, and graphs
- Implementing AVL tree rotations and balancing
- Working with multiple CSV file inputs
- Applying graph algorithms to a practical delivery problem
- Combining multiple data structures to solve different aspects of a larger system
