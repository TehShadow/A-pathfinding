// Example for jsonHandling

#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

using namespace std;

int main() {
    // Specify the path to the JSON file
    string filePath = "dummyObjects.json";

    // Open the JSON file
    ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return 1;
    }

    // Parse the JSON file
    Json::Value root;
    Json::CharReaderBuilder readerBuilder;
    Json::parseFromStream(readerBuilder, fileStream, &root, nullptr);

    // Iterate through the array of objects
    for (const auto& object : root) {
        string name = object["name"].asString();
        int size = object["size"].asInt();
        int x = object["coordinates"]["x"].asInt();
        int y = object["coordinates"]["y"].asInt();

        // Print object details
        cout << "Name: " << name << ", Size: " << size
                  << ", Coordinates: (" << x << ", " << y << ")" << endl;
    }

    return 0;
}
