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

// template: specify type of position and, optionally, point height and score data types
template <typename pos_t = unsigned, typename p_height_t = unsigned short, typename p_score_t = unsigned short>
struct coord {
public:
    pos_t x, y; // location of point, such as in a grid
    mutable point<p_height_t, p_score_t> point; // todo make point a pointer to increase speed & streamline value population from grids.

    // constructors
    coord() { this->x = 0; this->y = 0;}
    coord(pos_t x, pos_t y) { this->x = x; this->y = y;}
    coord(pos_t x, pos_t y, p_score_t score) { this->x = x; this->y = y; this->point.setgScore(score); this->point.setfScore(score);}

    /* point shortcut getters */
    p_score_t getHeight() const { return point.getHeight(); }
    void setHeight(p_height_t height) {point.setHeight(height); }

    p_score_t getgScore() const { return point.getgScore(); }
    void setgScore(p_score_t score) {point.setgScore(score); }

    p_score_t getfScore() const { return point.getfScore(); }
    void setfScore(p_score_t score) {point.setfScore(score); }


    /* validity checks */
    bool valid() const {
        point.valid();
    }
    bool bothValid(const coord<pos_t>& rhs) const {
        return valid() && rhs.valid(); // true if both valid
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
        return bothValid(rhs)
           && this->x == rhs.x
           && this->y == rhs.y; // true if they're both valid and the same point
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
