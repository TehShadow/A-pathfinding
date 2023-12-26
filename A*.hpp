#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <random>
#include <climits>
#include <fstream>
#include <jsoncpp/json/json.h>

using namespace std;

class AStarAlgorithm {
public:
    // Constructors
    AStarAlgorithm(int xSize, int ySize, int obstacleCount);
    AStarAlgorithm(int xSize, int ySize);

    // Public Methods
    vector<pair<int, int>> findPath(pair<int, int> start, pair<int, int> goal);
    void placePoints(int x, int y, int radius);
    void printPath(const vector<pair<int, int>>& path) const;
    void displayGrid() const;
    void parseJsonFile(const std::string& filePath);
    void printData();
    void useData();

private:
    // Nested Struct
    struct Node {
        int x, y;         // Coordinates of the node
        int cost;         // Cost to reach this node
        int heuristic;    // Heuristic value (estimated cost to goal)

        // Constructor
        Node(int x, int y, int cost, int heuristic);
        
        // Calculate the total cost (cost + heuristic)
        int getTotalCost() const {
            return cost + heuristic;
        }

        // Overload the less than operator for priority queue
        bool operator<(const Node& other) const {
            return getTotalCost() > other.getTotalCost();
        }
    };

        struct Object {
        std::string name;
        int size;
        int x;
        int y;
    };

    // Private Methods
    int calculateHeuristic(int currentX, int currentY, int goalX, int goalY);
    vector<pair<int, int>> aStar(pair<int, int> start, pair<int, int> goal);
    vector<vector<int>> createGrid(int xSize, int ySize);
    void addRandomObstacles(int obstacleCount);

    // Private Members
    int xSize;
    int ySize;
    vector<vector<int>> grid_;
    vector<Object> jsonData;

};

AStarAlgorithm::Node::Node(int x, int y, int cost, int heuristic)
    : x(x), y(y), cost(cost), heuristic(heuristic) {}

AStarAlgorithm::AStarAlgorithm(int xSize, int ySize, int obstacleCount)
    : grid_(createGrid(xSize, ySize)), xSize(xSize), ySize(ySize) {
    addRandomObstacles(obstacleCount);
}

AStarAlgorithm::AStarAlgorithm(int xSize, int ySize)
    : grid_(createGrid(xSize, ySize)), xSize(xSize), ySize(ySize) {}

vector<pair<int, int>> AStarAlgorithm::findPath(pair<int, int> start, pair<int, int> goal) {
    return aStar(start,goal);
}

void AStarAlgorithm::placePoints(int x, int y, int radius) {
    int xMin = max(0, x - radius);
    int xMax = min(xSize - 1, x + radius);
    int yMin = max(0, y - radius);
    int yMax = min(ySize - 1, y + radius);

    // Calculate squared radius
    int radiusSquared = radius * radius;
    for (int i = xMin; i <= xMax; ++i) {
        for (int j = yMin; j <= yMax; ++j) {
            // Calculate squared distance
            int dx = i - x;
            int dy = j - y;
            int distanceSquared = dx * dx + dy * dy;

            // Check if the squared distance is less than or equal to the squared radius
            if (distanceSquared <= radiusSquared) {
                grid_[i][j] = 1;
            }
        }
    }
}

void AStarAlgorithm::printPath(const vector<pair<int, int>>& path) const {
    cout << "Path: ";
    for (const auto& point : path) {
        cout << "(" << point.first << ", " << point.second << ") ";
    }
    cout << "\n----------" << endl;
}

void AStarAlgorithm::displayGrid() const {
    for (const auto& row : this->grid_) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

void AStarAlgorithm::parseJsonFile(const std::string& filePath) {
    // Open the JSON file
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Error opening file: " << filePath << std::endl;
        return;  // Return an empty vector on error
    }

    // Parse the JSON file
    Json::Value root;
    Json::CharReaderBuilder readerBuilder;
    Json::parseFromStream(readerBuilder, fileStream, &root, nullptr);

    // Iterate through the array of objects
    for (const auto& object : root) {
        Object obj;
        obj.name = object["name"].asString();
        obj.size = object["size"].asInt();
        obj.x = object["coordinates"]["x"].asInt();
        obj.y = object["coordinates"]["y"].asInt();

        // Store the object in the vector
        this->jsonData.push_back(obj);
    }
}

void AStarAlgorithm::printData() {
        for (const auto& obj : this->jsonData) {
            std::cout << "Name: " << obj.name << ", Size: " << obj.size
                    << ", Coordinates: (" << obj.x << ", " << obj.y << ")" << std::endl;
        }
}

void AStarAlgorithm::useData() {
        for(const auto& obj : this->jsonData){
            this->placePoints(obj.x,obj.y,obj.size);
        }
}

int AStarAlgorithm::calculateHeuristic(int currentX, int currentY, int goalX, int goalY) {
    return abs(currentX - goalX) + abs(currentY - goalY);
}

vector<pair<int, int>> AStarAlgorithm::aStar(pair<int, int> start, pair<int, int> goal) {
// Directions: Up, Down, Left, Right, Up-Left, Up-Right, Down-Left, Down-Right
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

        priority_queue<Node> openSet;
        vector<vector<int>> costSoFar(grid_.size(), vector<int>(grid_[0].size(), INT_MAX));
        vector<vector<Node>> cameFrom(grid_.size(), vector<Node>(grid_[0].size(), Node(-1, -1, 0, 0)));
        int maxCost = INT_MIN;
        int minHeu = INT_MAX;
        Node newGoal(0,0,0,0);

        openSet.push(Node(start.first, start.second, 0, calculateHeuristic(start.first, start.second, goal.first, goal.second)));
        costSoFar[start.first][start.second] = 0;

        while (!openSet.empty()) {
            Node current = openSet.top();
            openSet.pop();

            if (current.x == goal.first && current.y == goal.second) {
                vector<pair<int, int>> path;
                while (current.x != -1 && current.y != -1) {
                    path.push_back({current.x, current.y});
                    current = cameFrom[current.x][current.y];
                }
                reverse(path.begin(), path.end());
                return path;
            }

            for (auto direction : directions) {
                int nextX = current.x + direction.first;
                int nextY = current.y + direction.second;

                if (nextX >= 0 && nextX < grid_.size() && nextY >= 0 && nextY < grid_[0].size()) {
                    if (grid_[nextX][nextY] != 1) {
                        int newCost = current.cost + 1;
                        if (newCost < costSoFar[nextX][nextY]) {
                            costSoFar[nextX][nextY] = newCost;
                            int heuristic = calculateHeuristic(nextX, nextY, goal.first, goal.second);
                            int totalCost = newCost + heuristic;
                            openSet.push(Node(nextX, nextY, newCost, heuristic));
                            cameFrom[nextX][nextY] = current;
                            if(current.heuristic < minHeu && current.cost > maxCost){
                                minHeu = current.heuristic;
                                maxCost = current.cost;
                                newGoal = current;
                            }
                        }
                    }
                }
            }
        }

        cout<<"Position is taken ...\nGoing as close as posible..."<<endl;
        cout<<"New Goal {"<<newGoal.x<<","<<newGoal.y<<"}"<<endl;
        pair newGoalPair = {newGoal.x,newGoal.y};
        return this->aStar(start,newGoalPair);
}

vector<vector<int>> AStarAlgorithm::createGrid(int xSize, int ySize) {
     // Initialize the grid with zeros
    vector<vector<int>> grid(xSize, vector<int>(ySize, 0));
    return grid;
}

void AStarAlgorithm::addRandomObstacles(int obstacleCount) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> randX(0, grid_.size() - 1);
    uniform_int_distribution<int> randY(0, grid_[0].size() - 1);

    for (int i = 0; i < obstacleCount; ++i) {
        int x = randX(gen);
        int y = randY(gen);
        grid_[x][y] = 1;
    }
}
