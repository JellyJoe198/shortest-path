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

    coord<pos_t> * cameFrom = nullptr; // pointer to previous node in shortest path (used in A* alg)

// //    bool _validPoint;

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


    /* validity checks */
    bool valid() const {
//        if(_point != nullptr)
            return _point && _point->valid();
    }
    bool bothValid(const coord<pos_t>& rhs) const {
        return this->valid() && rhs.valid(); // true if both valid
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

//    /* type conversions */
//    explicit operator unsigned short() const {
//        return x, y;
//    }
};


#endif //MAIN_CPP_COORD_HPP
