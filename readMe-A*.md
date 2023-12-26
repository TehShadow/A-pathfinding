# A* Pathfinding Algorithm with JSON Data Parsing

## Overview

This C++ code implements the A* algorithm for pathfinding on a 2D grid. Additionally, it includes functionality to parse object data from a JSON file and use that data to place obstacles on the grid.

## Features

1. **A* Pathfinding Algorithm**: The code provides a class, `AStarAlgorithm`, that encapsulates the A* algorithm for finding the shortest path between two points on a grid.

2. **Grid Manipulation**: The class allows the user to create a grid, place obstacles randomly, visualize the grid, and find paths from a specified start point to a goal point.

3. **JSON Data Parsing**: The class includes functions to parse object data from a JSON file. The data includes object names, sizes, and coordinates.

4. **Object Data Utilization**: The parsed object data is used to place obstacles on the grid.

## Usage

1. **Instantiating the A* Algorithm Object**:

    ```cpp
    // Example instantiation with a grid size of 10x10 and 15 random obstacles
    AStarAlgorithm astar(10, 10, 15);
    // Example instantiation with a grid size of 10x10
    AStarAlgorithm astar(10, 10);
    ```

2. **Pathfinding**:

    ```cpp
    // Find a path from (0, 0) to (9, 9)
    auto path = astar.findPath({0, 0}, {9, 9});
    astar.printPath(path);
    ```

3. **Grid Manipulation**:

    ```cpp
    // Place obstacles in a circular region around (5, 5) with a radius of 2
    astar.placePoints(5, 5, 2);

    // Display the updated grid
    astar.displayGrid();
    ```

4. **JSON Data Parsing and Utilization**:

    ```cpp
    // Parse object data from a JSON file
    astar.parseJsonFile("object_data.json");

    // Print parsed object data
    astar.printData();

    // Use parsed data to place obstacles on the grid
    astar.useData();
    ```

## Dependencies

- [jsoncpp](https://github.com/open-source-parsers/jsoncpp): A C++ library for interacting with JSON data.
    ```bash
    sudo apt-get install libjsoncpp-dev
    ```

## Building and Running

1. **Build the Code**:

    ```bash
    g++ -o main main.cpp -ljsoncpp
    ```

2. **Run the Executable**:

    ```bash
    ./main
    ```

## Additional Notes

- The code uses the `jsoncpp` library for JSON parsing. Ensure that the library is properly installed on your system.

- Feel free to customize the grid size, obstacle count, and other parameters according to your requirements.

