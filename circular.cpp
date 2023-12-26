#include <iostream>
#include <vector>
#include <cmath>

// Standalone Example 
// Is already in the A*.hpp 

struct Point {
    int x;
    int y;
};

// Function to update the grid with "1"s in a circular fashion around the center point
void updateGridCircular(std::vector<std::vector<int>>& grid, const Point& center, int radius) {
    int rows = grid.size();
    int cols = grid[0].size();
    int radiusSquared = radius * radius;

    // Update only the points within the circular range using a single loop
    for (int index = 0; index < rows * cols; ++index) {
        int i = index / cols;
        int j = index % cols;
        int dx = center.x - i;
        int dy = center.y - j;
        if ((dx * dx + dy * dy) <= radiusSquared) {
            grid[i][j] = 1;
        }
    }
}

// Function to print the grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // Define a grid size
    const int rows = 5;
    const int cols = 5;

    // Define a 2D vector to represent the grid
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));

    // Center point and radius of the circular pattern
    Point center = {1, 2};
    int radius = 2;

    // Update the grid in a circular fashion
    updateGridCircular(grid, center, radius);

    // Print the updated grid
    printGrid(grid);

    return 0;
}
