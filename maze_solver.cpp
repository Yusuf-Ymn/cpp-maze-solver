#include <iostream>

using namespace std;

#define ROWS 10
#define COLS 10

// Define the maze matrix (0 = open, 1 = wall)
int maze[ROWS][COLS] = {
    {0, 0, 1, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 0, 0, 1, 1, 0, 0, 0, 1, 1},
    {1, 1, 0, 1, 1, 0, 0, 1, 1, 1},
    {1, 1, 0, 0, 1, 1, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 0}
};

#define MAX_PATH_LENGTH (ROWS * COLS)

// Array to store the solution path as (x,y) coordinates
int path[MAX_PATH_LENGTH][2];
int pathLength = 0;

/**
 * findPath:
 *  Uses backtracking to search for a path from (x, y)
 *  to the goal at (ROWS-1, COLS-1).
 *  - Returns false if the current cell is not open.
 *  - Returns true and fills `path[]` when the goal is reached.
 */
bool findPath(int x, int y) {
    // Check bounds and whether cell is open
    if (x < 0 || x >= ROWS || y < 0 || y >= COLS || maze[x][y] != 0) {
        return false;
    }

    // Mark this cell as part of the path
    path[pathLength][0] = x;
    path[pathLength][1] = y;
    pathLength++;

    // Check if we've reached the exit
    if (x == ROWS - 1 && y == COLS - 1) {
        return true;
    }

    // Mark visited to avoid revisiting during backtracking
    maze[x][y] = 2;

    // Try moving: right, down, left, up
    if (findPath(x, y + 1) ||
        findPath(x + 1, y) ||
        findPath(x, y - 1) ||
        findPath(x - 1, y)) {
        return true;
    }

    // Backtrack: remove this cell from path
    pathLength--;
    maze[x][y] = 0; // unmark

    return false;
}

/**
 * printMazeWithPath:
 *  Marks the found path in the maze and prints it.
 *  - Wall: '#'
 *  - Path: '*'
 *  - Open space: '  '
 */
void printMazeWithPath() {
    // Mark path cells with '3'
    for (int i = 0; i < pathLength; ++i) {
        int r = path[i][0];
        int c = path[i][1];
        maze[r][c] = 3;
    }

    // Print the maze row by row
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (maze[i][j] == 1) {
                cout << "# ";   // Wall
            } else if (maze[i][j] == 3) {
                cout << "* ";   // Solution path
            } else {
                cout << "  ";   // Open space
            }
        }
        cout << endl;
    }
}

int main() {
    // Start searching from (0,0)
    if (findPath(0, 0)) {
        cout << "Path found!" << endl << endl;

        cout << "Maze (solution path marked with *):" << endl;
        printMazeWithPath();

        cout << "\nStep-by-step coordinates of the solution:" << endl;
        for (int i = 0; i < pathLength; ++i) {
            cout << "(" << path[i][0] << "," << path[i][1] << ")" << endl;
        }
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}
