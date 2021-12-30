/* CSCI261 Final Project: Shortest path
 * main file
 *
 * Author: Joseph Brownlee (jmbrownlee)
 *
 * see acknowledgements.md for resources used (Math Professors, other students, online forums, etc)
 */

#include <iostream>

using namespace std;

#include "class/World.h"
#include "class/coord.hpp"


int main() {

    // create surface based on our file
    World mountain("testSurface1.txt");

    // debug: display surface 2D vector
    for (const auto& row : mountain.getSurface()) {
        for (const auto& point: row)
            cout << point.getHeight() << ' ';
        cout << endl;
    }

    // request start and end points
    coord<unsigned short> start, end;
    cout << "start point (x y) ";
    cin >> start; // take 2 integers from stream
    cout << "end point (x y) ";
    cin >> end;

    // calculate shortest path
    vector<coord<unsigned short>> path = mountain.getBestPath(start, end);

    // debug: display shortest path
    if (path.empty()) {
        cout << "could not find a valid path." << endl;
        return 0;
    } // else:
    for(auto node : path) {
        cout << "(" << node.x << ", " << node.y << ")" << endl;
    }

    return 0;
}