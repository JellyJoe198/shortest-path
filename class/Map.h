/* CSCI261 Final Project: Shortest path
 * map class header and implementation file
 *
 * Author: Joseph Brownlee
 *
 * note: combining header and class here is a design decision
 * because there are relatively few functions.
 */

#ifndef MAIN_CPP_MAP_H
#define MAIN_CPP_MAP_H

#include <vector>
using namespace std;

#include "point.hpp"

template <typename Type, typename size_Type = unsigned long>
class Map {
private:
    const Type DEFAULT = (unsigned)(~0); // default to infinity
    // default map is 1x1 of DEFAULT
    vector<vector<Type>> _scoreMap = {vector<Type> (1,DEFAULT)}; // possible bug: this doesn't actually fill it with the default?
    bool _valid;
public:
    Map() = default;//{
//        _valid = false;
//    }
//    Map(Type rowSize, Type colSize) {
//        _scoreMap.resize(rowSize).resize(colSize)(DEFAULT); // make vector of given size filled with default
//    }// not working, compiler error: invalid use of 'void'
//     //error In template: member reference base type 'void' is not a structure or union error occurred here in instantiation of member function 'Map<unsigned int>::Map' requested here

    /// increase size of score map
    void expand(size_Type rows, size_Type cols) {
        // expand rows
        if (_scoreMap.size() < rows) {
            _scoreMap.resize(rows, vector<Type>(_scoreMap.at(0).size(), DEFAULT)); // make more rows
        }
        // expand column for each row
        for(int i = 0; i < rows; ++i) {
            if (_scoreMap.at(i).size() < cols) { // if row is too small
                _scoreMap.at(i).resize(cols, DEFAULT); // resize row
            }
        } // end for
    } // end function expand

    Type get(point<Type> node) {
        try {
            Type value = _scoreMap.at(node.x).at(node.y);
            if (!value) {
                cout << "value was zero, return default. ";
                return DEFAULT; // if it's 0 (empty vector location) return default. this should be redundant.
            }
            else return value;
        }
        catch( const std::out_of_range& e ) {/*return default*/}
        catch( const std::exception& e ) {
            cout << "Warning: score map may be malformed: " << e.what() << endl;
        }
        return DEFAULT; // if not in map, return default
    } // end function get
    void set(point<Type> node, Type value) {
        try {
            _scoreMap.at(node.x).at(node.y) = value;
        }
        catch( const std::out_of_range& e ) {
            /* expand vector to position of node and fill new slots with default value */
            expand(node.x, node.y);
            /*if (_scoreMap.size() < node.x) {
                _scoreMap.resize(node.x, vector<Type>(_scoreMap.at(0).size(),DEFAULT));
            }
            if (_scoreMap.at(node.x).size() < node.y) {
                // resize the current row and the default row
                _scoreMap.at(node.x).resize(node.x, DEFAULT);
                if (_scoreMap.at(0).size() < node.x ) {
                    _scoreMap.at(0).resize(node.x, DEFAULT);
                    // todo_later also expand other rows?
                }
            }// */
        }
        catch( const std::exception& e ) {
            cout << "Warning: score map may be malformed: " << e.what() << endl;
        }
//        return DEFAULT; // if not in map, return default
    } // end function set
};

#endif //MAIN_CPP_MAP_H
