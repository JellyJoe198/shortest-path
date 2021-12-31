/* CSCI261 Final Project: Shortest path
 * point class header and implementation file
 *
 * Author: Joseph Brownlee
 *
 * notes:
 * - point does not contain location data, this is handled by the coord class to reduce memory usage.
 * - defining functions in place here is required to allow templates to work properly.
 */

#ifndef MAIN_CPP_POINT_HPP
#define MAIN_CPP_POINT_HPP

/// coordinates structure
template <typename height_t, typename score_t = unsigned short>
class point {
private:
    height_t _height;
    score_t _fScore, _gScore; // scores used in A* algorithm
//    bool _valid{0}; // height 0 reserved for invalid. (to save space)
public:
    height_t getHeight() const { return _height; }
    void setHeight(height_t height) { _height = height; }

    score_t getfScore() const { return _fScore; }
    void setfScore(score_t fScore) { _fScore = fScore; }

    score_t getgScore() const { return _gScore; }
    void setgScore(score_t gScore) { _gScore = gScore; }

    // construction
    point() {
        _fScore = 0;
        _gScore = 0;
        _height = 0;
    }
    explicit point(height_t height, score_t score) {
        _fScore = score;
        _gScore = score;
        _height = height;
//        _valid = (bool)height; // height 0 is reserved as invalid height
    }

    bool valid() const {
        return _height;
    }
};

#endif //MAIN_CPP_POINT_HPP
