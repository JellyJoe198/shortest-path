/* CSCI261 Final Project: Shortest path
 * World class header - replaces Map.h
 *
 * Author: Joseph Brownlee
 *
 * note: combining header and class here is a design decision
 * because there are relatively few functions.
 */

#ifndef MAIN_CPP_WORLD_H
#define MAIN_CPP_WORLD_H

#include <vector>
#include <string>
using namespace std;

#include "point.hpp"
#include "coord.hpp"

class World {
private:
//    static const unsigned INF;
//    static const point<unsigned short> DEFAULT_POINT;
    bool _valid {false};
    vector<vector<point<unsigned short>>> _surface; // 2D vector of points with location, _height, score, etc. data
    void generateMap(unsigned rowSize, unsigned colSize);

    bool readSurface(char readType, ifstream &fin);
public:

    World() = default;
    explicit World(string fileName);
    vector<coord<unsigned short>> getBestPath(coord<unsigned short> start, coord<unsigned short> end);
    const vector<vector<point<unsigned short>>> & getSurface();
};


#endif //MAIN_CPP_WORLD_H
