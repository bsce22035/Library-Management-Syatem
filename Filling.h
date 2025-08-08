

#ifndef MAH_FILLING_H
#define MAH_FILLING_H
#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
class Filling {
public:
    string file_name = " ";
    Filling(string x = " ") {
        file_name = x;
        fstream variable(file_name + ".txt", ios::app);

    }
    bool openingfile(string x);
    bool file_Exists(const string &filename) ;
    void create_and_check(string batch, string username, string id);
};


#endif //MAH_FILLING_H
