/* CSCI261 Final Project: Shortest path
 * World class header - replaces Map.h
 *
 * Author: Joseph Brownlee (jmbrownlee@mines.edu)
 */

#ifndef MAIN_CPP_WORLD_H
#define MAIN_CPP_WORLD_H

#include <vector>
#include <string>
using namespace std;

#include "point.hpp"
#include "coord.hpp"

class World {
public:

    // constructors
    World() = default;
    explicit World(string fileName); // read surface from file into World object

    vector<coord<unsigned short>> getBestPath(coord<unsigned short> start, coord<unsigned short> end) const ;
    const vector<vector<point<unsigned short>>> & getSurface();

    point<unsigned short> * getPointPtr(coord<unsigned short> &position) const ;

private:
//    static const unsigned INF;
//    static const point<unsigned short> DEFAULT_POINT;
    bool _valid {false};
    vector<vector<point<unsigned short>>> _surface; // 2D vector of points with location, _height, score, etc. data

    void generateMap(unsigned rowSize, unsigned colSize);

    bool readSurface(char readType, ifstream &fin);
//    // these are member functions to allow getting points from _surface
//    template <typename Type>
//    double straightLineDist(coord<Type> p1, coord<Type> p2);
//
//    template <typename Type>

//    long heuristic(coord<Type> start, coord<Type> mid, coord<Type> end);
};


#endif //MAIN_CPP_WORLD_H
