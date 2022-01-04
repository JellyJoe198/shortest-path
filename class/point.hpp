/* CSCI261 Final Project: Shortest path
 * point class header and implementation file
 *
 * Author: Joseph Brownlee
 *
 * notes:
 * - each point does not contain its own location data, this is handled by the coord class to reduce memory usage.
 * - all functions check `if(this)` before accessing memory to avoid SIGSEGV because:
 *    coord.hpp can call functions on null points in memory, so all functions must work with nonexistent parents:
 * - defining functions in place here is required to allow typename templates to work properly.
 */

#ifndef MAIN_CPP_POINT_HPP
#define MAIN_CPP_POINT_HPP

template <typename Type>
struct location {
    Type x, y;
};

//typedef location<unsigned short> loc;
//const auto INF = (unsigned short)(~0);
//const loc nulloc = {INF,INF};

template <typename height_t, typename score_t = unsigned short>
class point {
private:
    height_t _height; // payload surface data, zero is invalid.
    mutable score_t _fScore, _gScore; // scores used in A* alg
//    point<height_t> * _previous = nullptr; // previous item in path found by A* alg
//     loc _pLoc = nulloc;

public:

    /*point<height_t> & getPrevious() {
        if (this) return _previous;
        else return nullptr;
    }
    bool setPrevious(const point<height_t>& point) {
        if (this) {_previous = &point; return true;}
        else return false;
    }//*/
//    loc getPrevious() {
//        if (this) return _pLoc;
//        else return nulloc;
//    }
//    bool setPrevious(const loc& pt) {
//
//    }

    // basic getters and setters. must check if self exists before reading from self.
    height_t getHeight() const { if(this) return _height; }
    void setHeight(height_t height) {if(this) _height = height; }

    score_t getfScore() const { if(this) return _fScore; }
    void setfScore(score_t fScore) {if(this) _fScore = fScore; }

    score_t getgScore() const { if(this) return _gScore; }
    void setgScore(score_t gScore) {if(this) this->_gScore = gScore;}

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

    // zero height is invalid.
    bool valid() const {
        if(this) return _height;
        else return false;
    }
};

#endif //MAIN_CPP_POINT_HPP
