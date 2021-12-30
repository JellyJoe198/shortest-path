/* CSCI261 Final Project: Shortest path
 * World class implementation - replaces Map.h
 *
 * Author: Joseph Brownlee
 *
 * note: combining header and class here is a design decision
 * because there are relatively few functions.
 */

#include "World.h"

#include <fstream>
#include <iostream>
#include <sstream>  // used in extraction of spaced file streams
//#include <string>
//#include <vector>
using namespace std;


const unsigned short INF = (unsigned short)(~0); // infinity https://stackoverflow.com/a/47434423
const point<unsigned short> DEFAULT_POINT(0, INF);

/// @desc constructor of World data from file
/// @param fileName the name of the file to open (including extension)
World::World(string fileName) {

    /* open file */
    ifstream fin(fileName); // dev_outputSurface.txt is a test surface simpler than hgt files
    if (!fin.is_open()) {
        cerr << "unable to open surface file" << endl;
        _valid = false;
        return;
    }

    /* read file as our surface */
    readSurface('s', fin);

//    generateMap(2);
}

bool World::readSurface(char readType, ifstream &fin) {
//    vector<vector< point<unsigned short> >> _surface; // temporary grid to store surface

    /* read data */
    bool linesInconsistentLength{0}, emptyLines{0}; // data verification/warning trackers
    while (!fin.eof()) {
        // get each line from file
        string line;
        if (getline(fin, line) ) {
            // verify that line has contents
            if (line.empty())
                continue;
            _surface.resize(_surface.size() + 1); // make space in grid for another row
        }
        else {
            emptyLines = true;
            continue; // if line is empty, skip over it
        }

        // add line to vector
        unsigned height;
        stringstream lin(line); // allow extraction from the line
        while (!lin.eof()) { // extract all contents of lin
            lin >> height;
//            cout << height << ' '; //debug
            height += (!height); // set zeros to ones (zero is reserved)
            _surface.back().push_back(point<unsigned short>(height, INF) ); // add point to current place in current row of vector
        }

        // verify line size consistency with previous line, once it has at least 2 lines
        if (!linesInconsistentLength && _surface.size() > 1 && _surface.back().size() != _surface.at(_surface.size() - 2 ).size()) {
            linesInconsistentLength = true;
        }

    } // end while

    // handling of warning cases
    if (linesInconsistentLength)
        cout << "Warning (important): lines in surface file are of inconsistent length." << endl;
    if (emptyLines)
        cout << "Warning (weak): surface file contains empty lines that were ignored." << endl;

    return true;
}

// generate empty map
/// @param rowSize size of row. @param colSize defaults to rowSize if not specified.
void World::generateMap(unsigned int rowSize, unsigned int colSize = 0) {
    if(!colSize)
        colSize = rowSize; // default to square if columns not given

    // generate the empty surface
    _surface.resize(rowSize, vector<point<unsigned short>>(colSize, DEFAULT_POINT )); // create grid of proper size, defaulted to 0 height and infinite cost
}

// get raw surface
/// @returns constant reference to surface (to avoid copying large data)
const vector<vector<point<unsigned short>>> & World::getSurface() {
    return _surface;
}


/** functions required for best path calculation **/

#include <cmath>

double heightCoeff = 3; // exaggerate height change to encourage flatter paths

// the shortest possible path between 2 points is a straight line.
template <typename Type>
double straightLineDist(coord<Type> p1, coord<Type> p2) {
    if (p1 == p2) return 0;

    // verify points
    if (!p1.bothValid(p2)) {
        cout << "Warning (code bug): a node has invalid height" << endl;
        return INF; // invalid height means node distance cannot be properly calculated.
    }

    // use Pythagoras to get distance between 2 points
    return sqrt(
            // use absolute value and long cast to make sure values don't wraparound when subtracting
            pow(abs((long)p1.x - (long)p2.x), 2)
            + pow(abs((long)p1.y - (long)p2.y), 2)
            + pow(abs((long)heightCoeff * p1.getHeight() - (long)heightCoeff * p2.getHeight()), 2)
            );
}

// how short a path from start to finish can be if it goes through n.
template <typename Type>
long heuristic(coord<Type> start, coord<Type> mid, coord<Type> end) {
    return 10*( straightLineDist(start, mid) + straightLineDist(mid, end));
}
template <typename Type>
long heuristic(coord<Type> start, coord<Type> end) { // shortcut: start to end = start to start to end
    return heuristic(start, start, end);
}

//double sumScore(vector<coord<unsigned short>>);

// get best path
/// @desc use the A* algorithm to find the best path along member surface
/// @return a vector of coordinates corresponding to nodes of the shortest path
vector<coord<unsigned short>> World::getBestPath(coord<unsigned short> start, coord<unsigned short> end) {
    // variables used: start, end, grid-surface

    vector<coord<unsigned short>> shortPath{start};

    // The set of discovered nodes that may need to be (re-)expanded.
    vector<coord<unsigned short>> openSet = {start}; // initially only start is known.

    start.setgScore(0); // gScore is the cost of the shortest known path from start to this node.
    start.setfScore(heuristic(start,end)); // fScore is the cost of the shortest possible path through this node, using straight line calculations.

    while (!openSet.empty()) { // while openSet is not empty

        // find node in openSet having the lowest fScore
        int cPos = 0; // position of lowest node
        coord<unsigned short> current = openSet.at(0); // will contain the node in openSet of the lowest fScore
        for (int i = 0; i < openSet.size(); ++i) {
            auto node = openSet[i];
            if (node.getfScore() < current.getfScore()) {
                current = node;
                cPos = i;
            }
        }

        // stopping condition: path reaches end
        if (current == end) { // if this node is the end node, return the path to this node
            shortPath.push_back(end);
            return shortPath;
//            return reconstruct_path(cameFrom, current);
        }

        // neighboring nodes of current
        vector<coord<unsigned short>> neighbors;
        vector<coord<int8_t>> neighborOffsets = {{1, 0}, {0, 1}, {-1, 0}, {0, -1} };
        for (auto offset : neighborOffsets) {
            coord<long> position(current.x + offset.x, current.y + offset.y);
            if( position.x < 0 || position.y < 0 || position.x >= _surface.size() || position.y >= _surface.front().size()) // make sure we don't count nodes outside our grid
                neighbors.emplace_back(position.x, position.y); // add into neighbors vector
        }

        openSet.erase(openSet.begin() + cPos); //openSet.Remove(current);

        // populate height values from _surface for relevant points
        if(!current.valid())
            current.setHeight(_surface.at(current.x).at(current.y).getHeight()); // retrieve height from surface
        for (auto &neighbor: neighbors) { // populate all neighbors
            if (!neighbor.valid())
                neighbor.setHeight(_surface.at(neighbor.x).at(neighbor.y).getHeight());
        }

        // find the neighbor of current with the lowest score
        for (auto &neighbor: neighbors) { // for each neighbor of current
            unsigned short tentative_gScore = current.getgScore() + (unsigned short)round(straightLineDist(current, neighbor) );
            if (tentative_gScore < neighbor.getgScore()) {
                // This path to neighbor is better than any previous one. Record it!
                // this first encounter of neighbor.gScore is always true bc gScore defaults to INF.
                shortPath.push_back(neighbor);
                neighbor.setgScore(tentative_gScore);
                neighbor.setfScore(tentative_gScore + heuristic(start, neighbor, end)); // make a guess of the short length through this node

                // add good neighbor to openSet if not already added
                bool inSet = false;
                for (const auto &item : openSet) { // go through openSet and check if neighbor is there
                    if (neighbor == item) {
                        inSet = true;
                        break;
                    }
                }
                if (!inSet)
                    openSet.push_back(neighbor);
                openSet.push_back(neighbor);
            } // end found smaller

        } // end for neighbors

    } // end while openSet not empty

    return {};//vector<coord<unsigned short>>(0); // failure return is empty vector
}