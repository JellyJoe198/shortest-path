/* CSCI261 Final Project: Shortest path
 * World class implementation - replaces Map.h
 *
 * Author: Joseph Brownlee
 */

#include "World.h"

#include <fstream>  // fin
#include <iomanip>
#include <sstream>   // used in extraction of spaced file streams, hopefully not needed for hgt files
#include <cmath>
//#include <iostream> // cout
//#include <string>
//#include <vector>
using namespace std;

// mapping constants
const unsigned short INF = (unsigned short)(~0); // infinity https://stackoverflow.com/a/47434423
const point<unsigned short> DEFAULT_POINT(0, INF);

/// @desc constructor of World data from file
/// @param fileName the name of the file to open (including extension)
World::World(const string& fileName) {

    /* open file */
    ifstream fin(fileName); // dev_outputSurface.txt is a test surface simpler than hgt files
    if (!fin.is_open()) {
        cerr << "unable to open surface file" << endl;
        _valid = false;
        return;
    }

    int err = readSurface(fin, 's');;
/*
    // read first few bytes to determine file type
    char filType = 's'; // default to string read
    int i = 0; char testByte;
    while (i<15) {
        fin >> testByte;
        if (testByte == 0 || testByte == '0') {
            filType = 'b';
        }
        cout << testByte;
        ++i;
    }
    cout << endl << endl;

    int err {0x0000};

    if (filType == 's') { // string type (default)
        cout << "readType string\n";
        // read file as surface
        fin.seekg (0, std::ifstream::beg); // go back to beginning of file
        err = readSurface(fin, 's');
    }
    else  cout << "readType byte\n";
//*/
    fin.close();

//    auto err = readSurface(fin, 'b');
//    auto err = readHGT(fileName);

    // handle errors: use bitwise logic to check if each possible error occurred
        // this is inefficient I just wanted to see if I could
    if (err & 0x1000)
        cout << "WARNING (important): lines in surface file are of inconsistent length!" << endl;
    if (err & 0x0100)
        cout << "Warning (weak): surface file contains empty lines that were ignored." << endl;

    _valid = !(err&0x1000); // surface is only valid if there are no important errors
}

/// @brief reads surface from given file stream
/// @param readType s: spaced strings \n b: binary (hgt type)
/// @param fin valid file stream from which to read surface
/// @returns error codes:
///     \n 0x1000: unstable linesInconsistentLength
///     \n 0x0100: warn emptyLines
int World::readSurface(ifstream &fin, char readType = 0) {

    /* read data */
    // data verification/warning trackers
    bool linesInconsistentLength    {false},
         emptyLines                 {false};


    // binary integer read
    if (readType == 'b') {

        // get length of file to know how large the array should be
        fin.seekg (0, fin.end);
        int length = fin.tellg();
        fin.seekg (0, fin.beg);

//        // smaller file
//        if (length == 2* 1201*1201) {}

        char tr[2];
        uint16_t tempInt;
        vector<vector<uint16_t>> tempMap;
        tempMap.resize(1201, vector<uint16_t>(1201)); // make space for all height values
        while (!fin.eof()) { // keep reading until entire file is read
            for (int i = 0; i < 1201; ++i) {
                for (int j = 0; j < 1201; ++j) {
                    // read each integer (2 bytes)
//                    fin >> tr[0] >> tr[1];
//                    tempInt = tr[0]*( (char)(~0)+1 ) + tr[1];
                    fin >> tempInt;
                    tempMap[i][j] = tempInt;
                }
            }

        } // end while

        for (int i = 0; i < 1201; ++i) {
            _surface.resize(_surface.size() + 1); // make space in grid for another row
            for (int j = 0; j < 1201; ++j) {
                _surface.back().push_back(
                        point<unsigned short>(tempMap[i][j], INF)); // add corresponding height to this point
            }
        }

    // string number read
    } else { // if (readType == 's')
        while (!fin.eof()) {
            // get each line from file
            string line;
            if (getline(fin, line)) {
                // verify that line has contents
                if (line.empty())
                    continue;

                _surface.resize(_surface.size() + 1); // make space in grid for another row
            } else { // line is empty (only occurs at last line)
//                emptyLines = true;
                continue; // skip last line
            }

            if (isspace(line[0])) { // line only contains whitespace
                emptyLines = true;
                continue; // skip over this line
            }

            // add line to vector
            unsigned height;
            stringstream lin(line); // allow extraction from the line
            while (!lin.eof()) { // extract all contents of lin
                lin >> height;
//            cout << height << ' '; //debug
                height += (!height); // set zeros to ones (zero is reserved)
                _surface.back().push_back(
                        point<unsigned short>(height, INF)); // add point to end of current row of vector
            }

            // verify line size consistency with previous line, once it has at least 2 lines
            if (!linesInconsistentLength && _surface.size() > 1
                && _surface.back().size() != _surface.at(_surface.size() - 2).size()) {
                linesInconsistentLength = true;

                // attempt to pad shorter vectors to avoid out of range error
//                if
            }

        } // end while
    } // end extraction

//    // handling of warning cases
//    if (linesInconsistentLength)    // 0x1000
//        cout << "Warning (important!): lines in surface file are of inconsistent length!" << endl;
//    if (emptyLines)                 // 0x0100
//        cout << "Warning (weak): surface file contains empty lines that were ignored." << endl;

    return (0x0000 // each bit corresponds to a different error.
       +0x1000 * linesInconsistentLength
       +0x0100 * emptyLines
    );
}

///// @brief generate empty map
///// @param rowSize size of row. @param colSize defaults to rowSize if not specified.
//void World::generateMap(unsigned int rowSize, unsigned int colSize = 0) {
//    if(!colSize)
//        colSize = rowSize; // default to square if columns not given
//
//    // generate the empty surface
//    _surface.resize(rowSize, vector<point<unsigned short>>(colSize, DEFAULT_POINT )); // create grid of proper size, defaulted to 0 height and infinite cost
//}

// get raw surface
/// @returns constant reference to surface (to avoid copying large data)
const surface_t & World::getSurface() const {
    return _surface;
}


/** functions required for best path calculation **/

//double heightCoeff = 3; // exaggerate height changes to encourage flatter paths

// the shortest possible path between 2 points is a straight line.
template <typename T>
double World::straightLineDist(coord<T> &c1, coord<T> &c2) {
    if (c1 == c2) return 0;
    // verify and autofill relevant heights
    for (auto& crd : {c1, c2}) {
        crd.populatePoint(_surface);
//        if (!crd.valid()) {
//            crd.setHeight(
//                    _surface.at(crd.x).at(crd.y).getHeight() ); // retrieve this point's height from _surface
//        }

        if (!crd.valid()) {
            cout << "Warning: could not find height of coordinate " << crd.x << ' ' << crd.y << endl;

            // invalid height means distance to this node cannot be properly calculated.
            // Infinity means this node will be avoided as long as there are other valid nodes around.
            return INF;
        }
    }

    // use Pythagoras to get distance between 2 points
    return sqrt(
            // possible bug: wraparound with negatives. use long or double cast to fix.
            pow(abs(c1.x - c2.x), 2)
            + pow(abs(c1.y - c2.y), 2)
            + pow(_heightCoeff * abs(c1.getHeight() - c2.getHeight()), 2)
        );
}

const short SCORE_SCALE = 1;

// how short a path from start to finish can be if it goes through n.
template <typename T>
long World::heuristic(coord<T>& start, coord<T>& mid, coord<T>& end) {
    return SCORE_SCALE*( straightLineDist(start, mid) + straightLineDist(mid, end));
}
template <typename T>
long World::heuristic(coord<T>& start, coord<T>& end) { // shortcut: start to end = start to start to end
    return heuristic(start, start, end);
}

typedef vector<coord<unsigned short>> vcoords;

// best path calculation
/// @desc find the best path along _surface using A* algorithm
/// @return a vector of coordinates corresponding to nodes of the shortest path
/// @params start and end are zero-indexed coordinates (x y) corresponding to position on _surface.
vcoords World::getBestPath(coord<unsigned short> start, coord<unsigned short> end) {
    // variables used: start, end, grid-surface

//    vcoords nodeHistory{start};
    vcoords currentHistory{1, {(unsigned short)(~0),(unsigned short)(~0)} };

    // The set of discovered nodes that may need to be (re-)expanded.
    vcoords openSet = {start}; // initially only start is known.

    start.setgScore(0); // gScore is the cost of the shortest known path from start to this node.
    start.setfScore(heuristic(start,end)); // fScore is the cost of the shortest possible path through this node, using straight line calculations.

    while (!openSet.empty()) { // while openSet is not empty

        // find node in openSet having the lowest fScore
        int cPos = 0; // position of lowest node in openSet
        coord<unsigned short> currentNode = openSet.at(0); // will contain the node in openSet of the lowest fScore
        for (int i = 0; i < openSet.size(); ++i) {
            auto node = openSet[i];
            if (node.getfScore() < currentNode.getfScore()) {
                currentNode = node;
                cPos = i;
            }
        }
        currentHistory.push_back(currentNode);
        index_t currentPermIndex = currentHistory.size() -1;

        // stopping condition: path reaches end
        if (currentNode == end) { // if this node is the end node, return the path to this node
            // reconstruct path from end to start.
            vcoords shortestPath {currentNode};
            currentNode.reconstructPath(shortestPath, currentHistory);

            /* currently, the path is very blocky. plan: rerun algorithm using diagonals. */

            return shortestPath;
        }

        // get neighboring nodes of current node
        vcoords neighbors;
        const coord<short> offsets[] = {
                {1,0}, {0,1}, {-1,0}, {0,-1},
                {1,1}, {1,-1}, {-1,1}, {-1,-1}
        };
        for (const auto& offset : offsets) {
            const coord<unsigned short> pos (currentNode.x + offset.x, currentNode.y + offset.y, INF);
            if(pos.x < 0 || pos.y < 0 || pos.x >= _surface.size() || pos.y >= _surface.at(pos.x).size()) // make sure we don't count nodes outside our grid
            {} else {
                neighbors.push_back(pos);
            }
        }

        openSet.erase(openSet.begin() + cPos); //openSet.Remove(current);

        // populate height values from _surface for relevant points
        currentNode.populatePoint(_surface);
        for (auto &neighbor: neighbors) { // populate all neighbors
            neighbor.populatePoint(_surface);
        }

        // find the neighbor of current with the lowest score, and add it to openSet
        for (auto &neighbor: neighbors) { // for each neighbor of current node
            unsigned short tentative_gScore = currentNode.getgScore() + (unsigned short)round(straightLineDist(currentNode, neighbor) );
            if (tentative_gScore < neighbor.getgScore()) {
                // This path to neighbor is better than any previous one. Record it!
                // this first encounter of neighbor.gScore is always true bc gScore defaults to INF.
                neighbor.setCameFrom(currentPermIndex);
                neighbor.setgScore(tentative_gScore);
                // make a guess of the short length through this node
                neighbor.setfScore(1*SCORE_SCALE*tentative_gScore + heuristic(start, neighbor, end) );

                // add good neighbor to openSet if not already added
                bool inSet = false;
                for (const auto& item : openSet) { // go through openSet and check if neighbor is there
                    if (neighbor == item) {
                        inSet = true;
                        break;
                    }
                }
                if (!inSet)
                    openSet.push_back(neighbor);
            } // end found smaller

        } // end for neighbors

    } // end while openSet not empty

    return {};//vcoords(0); // failure return is empty vector
}

bool World::valid() const {
    return _valid;
}

/// send all points of surface to ostream.\n
/// default display: each item evenly spaced and each row on new line
void World::exportSurface(ostream& output) const {
    for (const auto& row : this->getSurface()) {
        for (const auto& point: row)
            output << setw(5) << point.getHeight() << ' ';
        output << endl;
    }
}

void World::displaySurface(char dispType = 'd') const {
    cout << "not implemented. displaying surface to default text output." << endl;
    this->exportSurface(cout);
}

/// set height coefficient.
/// @return true if unsuccessful
bool World::setHeightCoeff(double coeff) {
    if (coeff >= 0) {
        _heightCoeff = coeff;
        return false;
    }
    return true;
}

sf::Vector2<size_t> World::getSize() const {
    return {
        _surface.size(), // row count
        _surface.at(0).size() // column count
    };
}

point<unsigned short> World::getPoint(int x, int y) const {
    // preliminary range check
    if (x >=0 && y >=0  &&  x < getSize().x && y < getSize().y)
        return getSurface().at(x).at(y);
    else
        return {}; // default point (height zero) if invalid
}

/// get height range
/// @returns x: min (smallest) \n y: max (highest)
sf::Vector2<unsigned> World::getHeightRange() const {
    unsigned min = getPoint(0,0).getHeight();
    unsigned max = getPoint(0,0).getHeight(); // initialize both to first point

    for (int i = 1; i < getSize().x; ++i) {
        for (int j = 1; j < getSize().y; ++j) {
            // compare each height to max and min.
            auto height = getPoint(i,j).getHeight();
            if (max < height)
                max = height;
            if (min > height)
                min = height;
        }
    }

    return {min, max};
}

double World::getHeightCoeff() const {
    return _heightCoeff;
}
