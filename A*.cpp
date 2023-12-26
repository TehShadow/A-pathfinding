// Include the A.hpp header file, which presumably contains the AStarAlgorithm class
#include "A*.hpp"

int main() {
    // Example usage

    // Define start and goal points
    pair<int, int> start = {0, 0};
    pair<int, int> goal = {10, 10};

    // Specify the file path for JSON data
    string filePath = "dummyObjects.json";

    // Create an instance of the AStarAlgorithm class with a 15x15 grid
    AStarAlgorithm aStarInstance(15, 15);

    // Parse object data from the specified JSON file
    aStarInstance.parseJsonFile(filePath);

    // Print the parsed object data
    aStarInstance.printData();

    // Use the parsed data to place obstacles on the grid
    aStarInstance.useData();

    // Find the path from the start to the goal
    vector<pair<int, int>> path = aStarInstance.findPath(start, goal);

    // Display the current state of the grid
    aStarInstance.displayGrid();

    // Print the calculated path
    aStarInstance.printPath(path);

    // Return 0 to indicate successful program execution
    return 0;
}

