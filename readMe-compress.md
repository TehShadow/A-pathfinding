# Grid Operations with Packed Representation

## Overview

This C++ code demonstrates operations on a 2D grid of cell states, including printing the grid, packing and unpacking cell states for efficient memory usage, and random object placement.

## Features

1. **Grid Manipulation**: The code allows you to create a grid, print its contents, and place random objects on it.

2. **Memory Optimization**: Cell states are packed into a more memory-efficient representation for storage and can be unpacked when needed.

## Usage

1. **Setting Up the Grid**:

    ```cpp
    // Example grid setup with a 3000x2000 grid, start and goal positions, and 500 random objects
    int xsize = 3000;
    int ysize = 2000;
    pair<int, int> start = {300, 300};
    pair<int, int> goal = {1300, 700};
    int numObjects = 500;

    vector<vector<CellState>> cellStates = createGrid(xsize, ysize, start, goal);
    placeObjects(cellStates, numObjects);
    ```

2. **Printing the Grid**:

    ```cpp
    // Print the generated grid
    cout << "Generated Grid:\n";
    printGrid(cellStates);
    ```

3. **Packing and Unpacking**:

    ```cpp
    // Pack cell states for each row
    vector<int64_t> packedRows = packRows(cellStates);

    // Unpack cell states for each row
    vector<vector<CellState>> unpackedCellStates(cellStates.size(), vector<CellState>(cellStates[0].size()));
    unpackRows(packedRows, unpackedCellStates);
    ```

4. **Calculating Memory Usage**:

    ```cpp
    // Calculate memory usage for the original, packed, and unpacked representations
    size_t originalMemoryUsage = calculateMemoryUsage(cellStates);
    size_t packedMemoryUsage = packedRows.size() * sizeof(int64_t);
    size_t unpackedMemoryUsage = calculateMemoryUsage(unpackedCellStates);
    ```

5. **Displaying Results**:

    ```cpp
    // Display results
    cout << "\nMemory Usage:\n";
    cout << "Original Memory Usage: " << originalMemoryUsage << " bytes\n";
    cout << "Packed Memory Usage: " << packedMemoryUsage << " bytes\n";
    cout << "Unpacked Memory Usage: " << unpackedMemoryUsage << " bytes\n";
    ```

## Dependencies

- None

## Building and Running

1. **Build the Code**:

    ```bash
    g++ -o main main.cpp
    ```

2. **Run the Executable**:

    ```bash
    ./main
    ```

## Additional Notes

- Adjust grid dimensions, start/goal positions, and the number of objects as needed.

- The code uses the `rand` function for random object placement. Ensure randomness as per your requirements.

