/* CSCI261 Final Project: Shortest path
 * main file
 *
 * Author: Joseph Brownlee (jmbrownlee@mines.edu)
 *
 * see acknowledgements.md for resources used (Math Professors, other students, online forums, etc)
 */

#include <iostream>
#include <sstream>

using namespace std;

#include "class/World.h"
#include "class/coord.hpp"

int main() {

    // preset inputs
//    std::string stringvalues = "6  1 3 1 1";
//    std::string stringvalues = "6  9 2 0 1";
    std::string stringvalues = "32767 0 0 7 9"; // maze

    std::istringstream iss (stringvalues);
    istream& input = iss;

//    istream& input = cin;

    // request file name
//    cout << "fileName: ";
    string fileName = "mazeTest.txt";
//    cin >> fileName;

    // create surface based on our file
    World mountain(fileName);
//    World mountain("testSurface1a.txt");

    // request height coefficient
    int coeff;
    cout << "heightCoefficient: ";
    input >> coeff;

    if ( mountain.setHeightCoeff(coeff) )
        cout << "error: height coefficient failed to set";

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

    // display surface to text out
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

    // display shortest path to text out
    if (path.empty()) {
        cout << "could not find a valid path." << endl;
        return 0;
    } // else:
    for(auto node : path) {
        cout << "(" << node.x << ", " << node.y << ")" << endl;
    }

    /**  **/



    return 0;
}