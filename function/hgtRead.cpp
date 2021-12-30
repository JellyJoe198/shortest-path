/* CSCI261 Final Project: Shortest path
 * file parsing functions
 *
 * Author: Joseph Brownlee (jmbrownlee)
 *
 */

#include "hgtRead.h"

// required libraries from header
//#include <vector>
//#include <fstream>

// required libraries for implementation
#include <sstream>  // string stream extraction
#include <string>
#include <iostream> // debug
using namespace std;

//template dev_fillGridFromSpaced<int>;
/// @desc fills given 2D vector with floats from filestream. \n bool dev_fillGridFromSpaced(vector<vector<Type>> grid, ifstream& fin);
/// @param grid  a 2D array (initialized to size 0 for now todo-later vector size check)
/// @param fin  must be numbers separated by spaces, the rows separated by newline '\\n'
/// @return 0 if successful, true if failed
/// @status working.
/// @debug_info template <typename Type>
/// bool dev_fillGridFromSpaced(vector<vector<Type>> grid, ifstream& fin) {
/// //debug: using hyper-specific template (taken from error callback) to work around a linking error:
template<> bool dev_fillGridFromSpaced<unsigned int>(std::vector<std::vector<unsigned int, std::allocator<unsigned int> >, std::allocator<std::vector<unsigned int, std::allocator<unsigned int> > > > grid
        , std::basic_ifstream<char, std::char_traits<char>>&fin) {
    // store each line of fin as a row in this grid vector
    int i(0), counter(0); // rows, counter
    while (!fin.eof()) {
        // get next line from file
        string line;
        if (getline(fin, line)) {

            // verify that line has contents
            if (line.empty())
                continue;
            grid.resize(i + 1); // make space in vector for another row

        } else {
            if(++counter > 50) break; // avoid infinite loops by capping count of empty lines
            continue; // jump to next line if current line is empty
        }

        // add contents to vector
        int elevation;
        stringstream lin(line); // allow extraction from the line
        while (!lin.eof()) { // extract all contents of lin
            lin >> elevation;
//            cout << elevation << ' '; //debug
            grid.at(i).push_back(elevation); // add to current row of vector
        }

//        cout << endl; //debug

        ++i; // go to next row in vector
    }
    return false;
}

/// @desc fills given 2D vector with Uint16 _height values from filestream
/// @param fin  must be in HGT format: a continuous stream of 16 bit integers.
///  Rows are 1201 or 3601 values wide, depending on resolution.
/// @param grid  a 2D array (initialized to size 0 for now todo-later vector size check)
/// @return 0 if successful, true if failed
/// @status not-working, please use dev_fillGridFromSpaced()
bool fillGridHGT(vector<vector<uint16_t>> & grid, const string& filename) {//ifstream& fin) {

    ifstream fin(filename, std::ios::binary);
    if (!fin.is_open()) {
        cerr << "unable to open surface file" << endl;
        return true;
    }

    int row_Size = 1201; // default size of row is 1201. Can be 3601 depending on file
    // read all rows
//    uint16_t elevation = 0;
    for (int i = 0; i < 1+1*row_Size; ++i) {
        // read row
        grid.resize(grid.size()+1); // make another row
        for (int j = 0; j < row_Size; ++j) {

            // todo fix binary reading
            // read a 16bit integer https://en.cppreference.com/w/cpp/io/basic_istream/read
            uint16_t n = 2;
            if(fin.read(reinterpret_cast<char*>(&n), sizeof n)) {
                if(n) grid.at(i).push_back(n); // add to current row of vector
                else grid.at(i).push_back(n+1); // zero is reserved for empty, set it to 1
//                cout << n << ' '; //debug
            }
//            cout << n << ' ';
        }
    }
    if (fin.eof()) return false;
    else {
        cout << "Warning: hgt file may be improperly formatted." << endl;
        return true;
    }
}
