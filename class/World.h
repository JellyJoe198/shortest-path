/* CSCI261 Final Project: Shortest path
 * World class header
 *
 * Author: Joseph Brownlee (jmbrownlee@mines.edu)
 */

#ifndef MAIN_CPP_WORLD_H
#define MAIN_CPP_WORLD_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#include <SFML/System/Vector2.hpp>

#include "point.hpp"
#include "coord.hpp"

//template <typename Type>
//struct Vector2 {
//    Type x, y;
//};

class World {
public:

    explicit World(const string& fileName); // constructor

    bool valid() const;

    vector<coord<unsigned short>> getBestPath(coord<unsigned short> start, coord<unsigned short> end);

    bool setHeightCoeff(double coeff);
    double getHeightCoeff();

    /* surface accessors */
    const vector<vector<point<unsigned short>>> & getSurface() const; // raw vector
    void exportSurface(ostream& output) const; // export surface as text to given stream
    void displaySurface(char dispType) const; // display to window

    sf::Vector2<size_t> getSize() const;
    point<unsigned short> getPoint(int x, int y) const;
    sf::Vector2<unsigned> getHeightRange() const;

private:
    vector<vector<point<unsigned short>>> _surface; // 2D map of points with height and score data
    bool _valid {false};
    double _heightCoeff {3}; // bug: this doen't make a path if less than 1

    int readSurface(ifstream &fin, char readType);
//    void generateMap(unsigned rowSize, unsigned colSize);

    /* best path calculations */
    template <typename T>
    double straightLineDist(coord<T> &c1, coord<T> &c2);
    template <typename T>
    long heuristic(coord<T>& start, coord<T>& mid, coord<T>& end);
    template <typename T>
    long heuristic(coord<T>& start, coord<T>& end);
};


#endif //MAIN_CPP_WORLD_H
