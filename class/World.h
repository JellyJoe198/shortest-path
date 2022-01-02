/* CSCI261 Final Project: Shortest path
 * World class header - replaces Map.h
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

    explicit World(string fileName); // constructor

    bool valid() const;

    vector<coord<unsigned short>> getBestPath(coord<unsigned short> start, coord<unsigned short> end);

    /* surface accessors */
    const vector<vector<point<unsigned short>>> & getSurface() const; // raw vector
    void exportSurface(ostream& output) const; // export surface as text to given stream
    void displaySurface(char dispType) const; // display to window

private:
    bool _valid {false};
    vector<vector<point<unsigned short>>> _surface; // 2D vector of points with location, _height, score, etc. data
    void generateMap(unsigned rowSize, unsigned colSize);

    int readSurface(char readType, ifstream &fin);

    /* best path calculations */
    template <typename Type>
    double straightLineDist(const coord<Type>& c1, const coord<Type>& c2) const ;
    template <typename Type>
    long heuristic(const coord<Type>& start, const coord<Type>& mid, const coord<Type>& end);
    template <typename Type>
    long heuristic(const coord<Type>& start, const coord<Type>& end);
};


#endif //MAIN_CPP_WORLD_H
