#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

const int GRID_SIZE = 10;

// Function to generate a random grid with values between 1 and 100
void generateRandomGrid(vector<vector<int>>& grid) {
    for (int i = 0; i < GRID_SIZE; i++) {
        vector<int> row;
        for (int j = 0; j < GRID_SIZE; j++) {
            row.push_back(rand() % 100 + 1);
        }
        grid.push_back(row);
    }
}

// Function to find the highest peak in the grid using hill climbing
pair<int, int> findHighestPeak(const vector<vector<int>>& grid) {
    int currentRow = 0;
    int currentCol = 0;

    // Start at a random position in the grid
    currentRow = rand() % GRID_SIZE;
    currentCol = rand() % GRID_SIZE;

    while (true) {
        int currentHeight = grid[currentRow][currentCol];

        // Check neighbors for higher values
        int maxNeighborHeight = currentHeight;
        int newRow = currentRow;
        int newCol = currentCol;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int neighborRow = currentRow + dr[i];
            int neighborCol = currentCol + dc[i];

            // Check if the neighbor is within the grid bounds
            if (neighborRow >= 0 && neighborRow < GRID_SIZE && neighborCol >= 0 && neighborCol < GRID_SIZE) {
                int neighborHeight = grid[neighborRow][neighborCol];
                if (neighborHeight > maxNeighborHeight) {
                    maxNeighborHeight = neighborHeight;
                    newRow = neighborRow;
                    newCol = neighborCol;
                }
            }
        }

        // If no higher neighbor is found, the current position is the peak
        if (maxNeighborHeight <= currentHeight) {
            return make_pair(currentRow, currentCol);
        }

        // Move to the neighbor with the highest value
        currentRow = newRow;
        currentCol = newCol;
    }
}

int main() {
    srand(time(nullptr));
    vector<vector<int>> grid;

    generateRandomGrid(grid);

    pair<int, int> highestPeak = findHighestPeak(grid);

    cout << "Highest Peak Coordinates: (" << highestPeak.first << ", " << highestPeak.second << ")" << endl;

    return 0;
}
