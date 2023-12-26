#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>  // For rand and srand
#include <ctime>    // For time

using namespace std;

//Useful way to pack and unpack data of a 2d grid and free space 
//Not in the A*.hpp


// Define cell states
enum CellState {
    EMPTY = 0b00,
    OBSTACLE = 0b01,
    START = 0b10,
    GOAL = 0b11
};

// Print the grid of cell states
void printGrid(const vector<vector<CellState>>& states) {
    for (const auto& row : states) {
        for (const auto& cell : row) {
            cout << static_cast<int>(cell) << " ";
        }
        cout << "\n";
    }
}

// Calculate memory usage for a vector of vectors
size_t calculateMemoryUsage(const vector<vector<CellState>>& states) {
    size_t totalBytes = 0;
    for (const auto& row : states) {
        totalBytes += row.size() * sizeof(CellState);
    }
    totalBytes += states.size() * sizeof(vector<CellState>);
    return totalBytes;
}

// Pack cell states of each row into a vector of int64_t
vector<int64_t> packRows(const vector<vector<CellState>>& states) {
    vector<int64_t> packedRows;
    for (const auto& row : states) {
        int64_t packedRow = 0;
        for (const auto& cell : row) {
            packedRow <<= 2;
            packedRow |= static_cast<int64_t>(cell);
        }
        packedRows.push_back(packedRow);
    }
    return packedRows;
}

// Unpack cell states for each row from a vector of int64_t
void unpackRows(const vector<int64_t>& packedRows, vector<vector<CellState>>& states) {
    for (int i = 0; i < packedRows.size(); ++i) {
        int64_t packedRow = packedRows[i];
        for (int col = states[i].size() - 1; col >= 0; --col) {
            states[i][col] = static_cast<CellState>(packedRow & 0b11);
            packedRow >>= 2;
        }
    }
}

// Randomly place a specified number of objects in the grid
void placeObjects(vector<vector<CellState>>& states, int numObjects) {
    srand(static_cast<unsigned>(time(nullptr))); // Seed the random number generator with the current time

    int numRows = states.size();
    int numCols = states[0].size();

    for (int i = 0; i < numObjects; ++i) {
        int randRow = rand() % numRows;
        int randCol = rand() % numCols;

        // Check if the cell is empty before placing an object
        if (states[randRow][randCol] == EMPTY) {
            states[randRow][randCol] = OBSTACLE; // You can change OBSTACLE to another value if needed
        } else {
            // If the cell is not empty, try again
            --i;
        }
    }
}


// Create a grid with specified dimensions, start position, and goal position
vector<vector<CellState>> createGrid(int xsize, int ysize, pair<int, int> start, pair<int, int> goal) {
    // Initialize the grid with EMPTY cells
    vector<vector<CellState>> grid(xsize, vector<CellState>(ysize, EMPTY));

    // Place the start and goal positions
    grid[start.first][start.second] = START;
    grid[goal.first][goal.second] = GOAL;

    // You can add more logic to randomly place obstacles or customize the grid as needed.

    return grid;
}

void printPacked(vector<int64_t>& packed){

    cout << "\nPacked Cell States for Each Row:\n";

    for (const auto& packedRow : packed) {
        cout << static_cast<int>(packedRow) << " ";
    }
    cout<<"\n"<<endl;
}

int main() {
    // Example usage with a 3000x2000 grid
    int xsize = 3000;
    int ysize = 2000;
    pair<int, int> start = {300, 300};
    pair<int, int> goal = {1300, 700};
    int numObjects = 500; // Adjust the number of objects as needed

    vector<vector<CellState>> cellStates = createGrid(xsize, ysize, start, goal);
    placeObjects(cellStates, numObjects);

    // Print the generated grid
    cout << "Generated Grid:\n";
    printGrid(cellStates);

    // Calculate memory usage for the original grid
    size_t originalMemoryUsage = calculateMemoryUsage(cellStates);

    // Pack cell states for each row
    vector<int64_t> packedRows = packRows(cellStates);

    printPacked(packedRows);

    // Calculate memory usage for the packed representation
    size_t packedMemoryUsage = packedRows.size() * sizeof(int64_t);

    // Unpack cell states for each row
    vector<vector<CellState>> unpackedCellStates(cellStates.size(), vector<CellState>(cellStates[0].size()));


    unpackRows(packedRows, unpackedCellStates);

    printGrid(unpackedCellStates);

    // Calculate memory usage for the unpacked representation
    size_t unpackedMemoryUsage = calculateMemoryUsage(unpackedCellStates);

    // Display results
    cout << "\nMemory Usage:\n";
    cout << "Original Memory Usage: " << originalMemoryUsage << " bytes\n";
    cout << "Packed Memory Usage: " << packedMemoryUsage << " bytes\n";
    cout << "Unpacked Memory Usage: " << unpackedMemoryUsage << " bytes\n";

    return 0;
}
