/* CSCI261 Final Project: Shortest path
 * main file
 *
 * Author: Joseph Brownlee (jmbrownlee)
 *
 * see acknowledgements.md for resources used (Math Professors, other students, online forums, etc)
 */

#include <iostream>
#include <sstream>

using namespace std;

#include "class/World.h"
#include "class/coord.hpp"

int main() {

    //
//    istream& input = cin;
//    std::string stringvalues = "1 3 1 1";
// possible error: _cameFrom is the same as this in coord 0x66f810 (1, 1) (2, 1) (2, 1)
    std::string stringvalues = "4 2 0 1";
    std::istringstream iss (stringvalues);
    istream& input = iss;

    // create surface based on our file
    World mountain("testSurface1a.txt");

    // validate surface
    if (!mountain.valid()) {
        cout << "Surface is invalid and may cause unexpected behavior. Continue anyway?";
        string answer;
        input >> answer;
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
    input >> start; // take 2 integers from stream
    cout << "end point (x y) ";
    input >> end;

    cout << endl << endl;

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