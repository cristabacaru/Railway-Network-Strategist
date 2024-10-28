# Graph Processing Project

## Overview
The Graph Processing Project is a C-based application designed to handle various operations on graphs, which are data structures used to represent connections between pairs of objects. This project models the degradation of railway segments, analyzing how wear affects route integrity over time. Utilizing graphs to visualize wear rates and their impacts on adjacent tracks, it identifies routes to prioritize for preservation based on degradation and transport profitability. The analysis ensures a sustainable railway system for future generations while optimizing maintenance costs and connectivity.

## Features
- **Graph Representation**: Define and manage graphs using adjacency lists.
- **Graph Construction**: Read graph data from input files and build the corresponding data structures.
- **Wear Calculation**: Analyze and update the wear level of connections over a specified time period.
- **Route Display**: Display routes and connections that meet certain criteria, such as acceptable wear levels.
- **Shortest Path Finding**: Utilize Dijkstra's algorithm to find the shortest paths from a starting node to all other nodes in the graph.

## File Descriptions

### `graf.h`
Defines the necessary data structures used in the program, including:
- **`TCel`**: Represents a cell in the adjacency list of the graph.
- **`TGL`**: Represents the graph structure, containing nodes and adjacency lists.
- **`TDrum`**: Describes paths within the graph, including source and destination information.

### `main.c`
The main entry point of the program that:
- Reads task specifications from command line arguments.
- Manages file operations, including reading from the input file (`tema3.in`) and writing to the output file (`tema3.out`).
- Implements two main tasks, each focusing on different aspects of graph analysis.

#### Task 1: Wear Analysis
- Reads the number of routes, years, and acceptable wear level from the input.
- Constructs the graph and calculates the wear based on the specified time period.
- Outputs the resulting routes that meet the wear criteria.

#### Task 2: Shortest Path Calculation
- Reads the starting city, maximum number of railways, and existing railways.
- Constructs the graph and applies Dijkstra's algorithm to find the shortest path from the specified starting city.
- Outputs the shortest paths found.

### `genericGraf.c`
Contains generic functions that facilitate graph operations, including:
- Memory allocation for graphs and adjacency cells.
- Functions to free allocated memory.
- Functions to retrieve indexes of nodes in string vectors.

### `functiiTask1.c`
Implements functions specific to Task 1, including:
- Reading graph data and constructing the graph.
- Calculating wear levels and displaying routes based on specified criteria.

### `functiiTask2.c`
Implements functions specific to Task 2, including:
- Reading data for the shortest path calculation.
- Implementing Dijkstra's algorithm and displaying the resulting paths.

## Getting Started
To run the Graph Processing Project, follow these steps:

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/cristabacaru/Railway-Network-Strategist.git