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
    World mountain("testSurface1w.txt");

    // validate surface
    if (!mountain.valid()) {
        cout << "Surface is invalid and may cause unexpected behavior. Continue anyway?";
        string answer;
        cin >> answer;
        // check if answer is a yes
        bool yes = false;
        if (!answer.empty()) {
            const char a = answer[0];
            if (a == 'y' || a == 'Y' || (a >= '1' && a <= '9') ) // y, Y, [any digit not zero]
                yes = true;
        }

        if (!yes) return 0; // exit program unless user approved
    }

    // send surface to standard output
    cout << endl;
    mountain.exportSurface(cout);

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