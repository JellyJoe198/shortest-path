/* CSCI261 Final Project: Shortest path
 * Math implementation file
 *
 * Author: Joseph Brownlee
 */

#include "extraMath.h"

#include <cmath>
using namespace std;

/// @returns equation evaluated at a point
/// @status bad, debug: 2x^3.5 +1
template <typename TYPE>
float eval(const TYPE& equation, float point) {
    return 2*pow(point,3.5f) +1;//debug use predefined function
}

/// @return Reimman sum approximation of integral between boundA and boundB
/// @param equation string of equation to approximate
/// @param deltaX size of rectangles for approximation
/// @status integration works, waiting on eval() function.
template <typename TYPE>
double integrate(const TYPE& equation, float boundA, float boundB, float deltaX /*=.1*/) {
    double sum = 0;
//    float halfX = deltaX / 2;

    int maxi = ceil(fabs(boundB - boundA) / deltaX); // normalized maximum iteration

    // use reimman sum to approximate integral
    // (float i = boundA; i < boundB; i += deltaX) // this is bad bc float rounding.
    for (int i = 0; i < maxi; i += 1) { // instead, normalize to int then scale.
        float k = i * deltaX + boundA; // scale int to correct float
        float height = eval(equation, k + deltaX / 2); // _height of middle of slice
        sum += deltaX * height; // add area of rectangle to our sum
    }

    return sum;
}

//float sqrt(const float& input) {
//    return std::sqrt(input);
//}

/// @return shortest path as list of nodes
/// @params start and end points (should be first and last items of path)
/// @params grid must be of non-zero size
/// @source pseudocode from wikipedia A*, specified to this problem by jmbrownlee
/// @status not working
vector<point<unsigned>> A_Star(point<unsigned> start, point<unsigned> end, const vector<vector<unsigned>> & grid) {
    // vector to store shortest path so far
    vector<point<unsigned>> shortPath {start};

    // The set of discovered nodes that may need to be (re-)expanded.
    vector<point<unsigned>> openSet {start}; // Initially, only the start node is known.

    // For node n, cameFrom[n] is the node immediately preceding it on the cheapest path from start
    vector<point<unsigned>> cameFrom;// = start; // redundant, just use shortPath[n-1]?

    /*/ gScore[n] is the cost of the cheapest path from start to n currently known.
    unsigned max_unsigned = -1; //pow(2, sizeof( unsigned));
    vector<point<unsigned>> gScore(0, {max_unsigned,max_unsigned}); // map with default value of Infinity https://stackoverflow.com/a/47434423/12541334
    gScore.push_back(start);// */
    Map<unsigned> gScore;
    cout << grid.size();// debug: grid is of size zero
    gScore.expand(grid.size(), grid.at(0).size());
    gScore.set(start, 0);

    Map<unsigned> fscore;
    fscore.set(start, heuristic(start, end));

    while (!openSet.empty()) { // while openSet is not empty
        // find node in openSet having the lowest _fScore[] value
        point<unsigned int> current = openSet.at(0); // the node in openSet having the lowest _fScore[] value
        for (auto node: openSet) {
            if (fscore.get(node) < fscore.get(current))
                current = node;
        }

        // stopping condition
        if (current == end) { // if this node is the end node, return the path to this node
            shortPath.push_back(end);
            return shortPath;
//            return reconstruct_path(cameFrom, current);
        }

        vector<point<unsigned>> neighbors; // neighboring nodes of current
        // add right, top, left, and bottom neighbors. //neighbors.emplace_back(current.x+1,current.y); //neighbors.emplace_back(current.x,current.y+1); //neighbors.emplace_back(current.x-1,current.y); //neighbors.emplace_back(current.x,current.y-1);

        for (point<unsigned int> (neighbor): neighbors) { // for each neighbor of current
            // d(current,neighbor) is the weight of the edge from nodePos to neighbor
            // tentative_gScore is the distance from start to the neighbor through nodePos
            unsigned tentative_gScore = gScore.get(current) + straightLineDist(current, neighbor);
            if (tentative_gScore < gScore[neighbor]) {
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighbor] := current
                gScore[neighbor] := tentative_gScore
                _fScore[neighbor] := tentative_gScore + h(neighbor)
                if neighbor not in openSet
                openSet.add(neighbor)// */
            }
        }
//        openSet.erase(nodePos); // remove from list (already checked this node)
    }
    return vector<point<unsigned>>{0}; // failure (empty vector)
}

// the shortest possible path between 2 points is a straight line.
double straightLineDist(coord p1, coord p2) {
    if (p1 == p2) return 0;
    // use Pythagoras to get distance between 2 points
    return sqrt(pow(abs((long)p1.x - (long)p2.x), 2) + pow(abs((long)p1.y - (long)p2.y), 2) );
}

// how short a path from start to finish can be if it goes through n.
long heuristic(coord start, coord mid, coord end) {
    return 10*(straightLineDist(start, mid) + straightLineDist(mid, end));
}
long heuristic(coord start, coord end) { // shortcut: start to end = start to start to end
    return heuristic(start, start, end);
}

/* template<typename pos_t>
long heuristic(vector<point<pos_t>> pathSoFar, point<pos_t> mid, point<pos_t> end) {
    return (fscore(pathSoFar) + straightLineDist(mid, end));
}//*/
