/* CSCI261 Final Project: Shortest path
 * World class header
 *
 * Author: Joseph Brownlee
 */

#ifndef MAIN_CPP_WORLD_H
#define MAIN_CPP_WORLD_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include "point.hpp"
#include "coord.hpp"

class World {
public:

    explicit World(const string& fileName); // constructor

    bool valid() const;

    vector<coord<unsigned short>> getBestPath(coord<unsigned short> start, coord<unsigned short> end);

    /* surface accessors */
    const vector<vector<point<unsigned short>>> & getSurface() const; // raw vector
    void exportSurface(ostream& output) const; // export surface as text to given stream
    void displaySurface(char dispType) const; // display to window

private:
    vector<vector<point<unsigned short>>> _surface; // 2D map of points with height and score data
    bool _valid {false};

    int readSurface(char readType, ifstream &fin);
    void generateMap(unsigned rowSize, unsigned colSize);

    /* best path calculations */
    template <typename T>
    double straightLineDist(coord<T> &c1, coord<T> &c2);
    template <typename T>
    long heuristic(coord<T>& start, coord<T>& mid, coord<T>& end);
    template <typename T>
    long heuristic(coord<T>& start, coord<T>& end);
};


#endif //MAIN_CPP_WORLD_H
