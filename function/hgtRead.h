//
// Created by jelly on 12/2/21.
//

#ifndef MAIN_CPP_HGTREAD_H
#define MAIN_CPP_HGTREAD_H

// required libraries
#include <vector>
#include <fstream>
using namespace std;

// file input
template <typename Type = unsigned>
bool dev_fillGridFromSpaced(vector<vector<Type>> grid, ifstream& fin);

// file input
bool fillGridHGT(vector<vector<uint16_t>> & grid, const string& filename);//ifstream& fin);

#endif //MAIN_CPP_HGTREAD_H
