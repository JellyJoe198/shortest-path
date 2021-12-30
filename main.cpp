/* CSCI261 Final Project continuation: Best Path
 * main file
 *
 * Author: Joseph Brownlee (jmbrownlee@mines.edu)
 *
 * see final.md/acknowledgements for resources used (Math Professors, other students, online forums, etc)
 */

#include <iostream>

using namespace std;

#include "class/World.h"
#include "class/coord.hpp"


int main() {

    // create surface based on our file
    World mountain("testSurface1.txt");  // testSurface1.txt is simpler than hgt files fir testing

    // display surface 2D vector to console
    bool doCoutSurface{true};
    if (mountain.getSurface().size() > 5) {
        cout << "Surface is larger than 5 rows. "
                "Would you like to display it to this console? (1/0) ";
        cin >> doCoutSurface;
    }
    if (doCoutSurface) {
        for (const auto &row: mountain.getSurface()) {
            for (const auto &point: row)
                cout << point.getHeight() << ' ';
            cout << endl;
        }
    }

    // request start and end points
    coord<unsigned short> start, end;
    cout << "start point (x y) ";
    cin >> start; // take 2 integers from stream
    cout << "end point (x y) ";
    cin >> end;

    // calculate shortest path
    vector<coord<unsigned short>> path = mountain.getBestPath(start, end);

    // display shortest path to console
    if (path.empty()) {
        cout << "could not find a valid path." << endl;
        return 0;
    } // else:
    for(auto node : path) {
        cout << "(" << node.x << ", " << node.y << ")" << endl;
    }

    return 0;
}