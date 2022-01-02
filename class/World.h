/* CSCI261 Final Project: Shortest path
 * World class header - replaces Map.h
 *
 * Author: Joseph Brownlee
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

    /* best path calculations */
    template <typename Type>
    double straightLineDist(const coord<Type>& c1, const coord<Type>& c2) const ;
    template <typename Type>
    long heuristic(const coord<Type>& start, const coord<Type>& mid, const coord<Type>& end);
    template <typename Type>
    long heuristic(const coord<Type>& start, const coord<Type>& end);

public:

//    World() = default;
    explicit World(string fileName);
    vector<coord<unsigned short>> getBestPath(coord<unsigned short> start, coord<unsigned short> end);
    const vector<vector<point<unsigned short>>> & getSurface();
};


#endif //MAIN_CPP_WORLD_H
