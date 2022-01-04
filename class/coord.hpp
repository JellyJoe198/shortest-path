/* CSCI261 Final Project: Shortest path
 * coord header and implementation (in place) file
 *
 * Author: Joseph Brownlee
 *
 * Coordinate is a wrapper around a point to add location data.
 *  It is important to optimize for memory because there are at least 1442401 points in a full 3º input file.
 *  Not all points need to be aware of their location in the grid.
 *
 * note: defining functions in place here is required to allow templates to work properly.
 */

#ifndef MAIN_CPP_COORD_HPP
#define MAIN_CPP_COORD_HPP

#include "point.hpp"

#ifndef surface_t
#define surface_t vector<vector<point<unsigned short>>>
#endif//surface_t

//template <typename Type>
//struct location {
//    Type x, y;
//};

// template: specify type of position and, optionally, point height and score data types
template <typename pos_t = unsigned, typename p_height_t = unsigned short, typename p_score_t = unsigned short>
class coord {
private:
    // todo make point a pointer to increase speed & streamline value population from grids.
    mutable point<p_height_t, p_score_t> * _point = nullptr;

    coord<pos_t> * _cameFrom = nullptr; // pointer to previous node in shortest path (used in A* alg)

public:

    pos_t x, y; // location of point, such as in a grid

    // constructors
    coord() {
        this->x = 0; this->y = 0;
    }
    coord(pos_t x, pos_t y) {
        this->x = x; this->y = y;
    }
    coord(pos_t x, pos_t y, p_score_t score) {
        this->x = x; this->y = y; setgScore(score); setfScore(score);
    }

    // populate: find the point corresponding to this->location.
    void populatePoint(surface_t& source, bool override = false) const {
        if(override|| !this->valid()) { // if point is invalid or overridden
            // retrieve data from surface
            this->_point = & source.at(this->x).at(this->y);
//            this->setHeight(source.at(this->x).at(this->y).getHeight() );
        }
    }

//    bool validPoint();

    /* point shortcut getters */
    p_score_t getHeight() const { return _point->getHeight(); }
    void setHeight(p_height_t height) const {_point->setHeight(height); }

    p_score_t getgScore() const { return _point->getgScore(); }
    void setgScore(p_score_t score) {_point->setgScore(score); }

    p_score_t getfScore() const { return _point->getfScore(); }
    void setfScore(p_score_t score) {_point->setfScore(score); }

    // set cameFrom for use in reconstructPath
    void cameFrom(coord<pos_t> crd) {
        if (&crd != this)
            _cameFrom = & crd; // store pointer to cameFrom node
//        if (_cameFrom) {
//            cout << "warning: cameFrom called on node already filled." << endl;
//        }
    }

    /// reconstruct path: use _cameFrom recursively to find all consecutive nodes in path
    void reconstructPath(vector<coord<pos_t>>& path) const {
        // stopping condition: start node, cameFrom doesn't exist
        if (!_cameFrom) {
            return;
        }

        // recursion: add to vector and repeat.
        path.push_back(*_cameFrom); // add coord object to the vector
//        if (this == _cameFrom) {
//            cout << "possible error: `_cameFrom` is the same as `this` in coord " << this
//                 << " in path position " << path.size() << endl;
//        }
//        else
        _cameFrom->reconstructPath(path); // repeat
    }

    /* validity checks */
    bool valid() const {
        return _point && _point->valid(); // true if point exists and is valid
    }
    bool bothValid(const coord<pos_t>& rhs) const {
        return this->valid() && rhs.valid(); // true if both coords are valid
    }

    /** overloaded operators **/

    // extract 2 items from stream
    // https://www.geeksforgeeks.org/overloading-stream-insertion-operators-c/
    friend istream & operator >> (istream &in,  coord &c) {
        in >> c.x >> c.y;
        return in;
    }

    // equality
    bool operator ==(const coord<pos_t>& rhs) const {
        return this->x == rhs.x
            && this->y == rhs.y; // true if they're both the same point
    }
//    bool operator !=(const coord<pos_t>& rhs) const {
//        return !(this == rhs);
//    }

    /// @brief memberwise multiply by a constant
    /// @returns 0,0 if invalid, otherwise returns coords, each multiplied.
    coord<pos_t> operator *(const unsigned mult) const {
        return { valid() * this->x * mult,
                 valid() * this->y * mult};
    }

    /// @brief memberwise addition of two coordinates
    /// @returns 0,0 if invalid, otherwise returns coords added
    template <typename Type>
    coord<pos_t> operator +(const coord<Type>& rhs) const {
        return { valid() * (pos_t)(this->x + rhs.x) ,
                 valid() * (pos_t)(this->y + rhs.y) };
    }

};


#endif //MAIN_CPP_COORD_HPP
