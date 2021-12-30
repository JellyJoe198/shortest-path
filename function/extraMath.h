/* CSCI261 Final Project: Shortest path
 * Math function headers
 *
 * Author: Joseph Brownlee (jmbrownlee)
 */

#ifndef FINAL_PROJECT_MATH_H
#define FINAL_PROJECT_MATH_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "../class/coord.hpp"
#include "../class/Map.h"


// function declarations

// generate the line distance between 2 points
double straightLineDist(coord<unsigned short>p1, coord<unsigned short> p2);

// A* finds shortest path from start to goal. based on https://en.wikipedia.org/wiki/A*_search_algorithm#Pseudocode
vector<point<unsigned>> A_Star(point<unsigned> start, point<unsigned> end, const vector<vector<unsigned>> & grid);

// how short a path from start to finish can be if it goes through n.
template <typename Type>
long heuristic(point<Type> start, point<Type> mid, point<Type> end);
template<typename Type>
long heuristic(point<Type> start, point<Type> end);

/** unused math **/
// approximate the area under a curve within bounds
double integrate(const string& equation, float boundA, float boundB, float deltaX = .1);

// function prototypes from other math file:
int alternating(int n);
int power(int n, int p);
int factorial(int n);
int fibb(int n);

#endif //FINAL_PROJECT_MATH_H
