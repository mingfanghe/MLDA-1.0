#ifndef BASEGADGET_H
#define BASEGADGET_H

#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Gadget
{
public:
    Gadget();
    void  matrix_to_csv(const vector<vector<double>> &matrix, string file);

};

#endif // BASEGADGET_H
