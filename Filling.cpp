#include "Filling.h"

void Filling::create_and_check(std::string batch, std::string username, std::string id) {
    if(file_Exists(batch)== true){
        ofstream variable(batch, std::ios::app);
        if (variable.is_open()) {
            cout << "file open" << endl;
            variable <<username << " " << id<<endl;
            variable.close();
        }
    }else{
        ofstream file(batch, std::ios::app);
        file.is_open();
        file<< username << " " << id<<endl;
        file.close();
    }
}

bool Filling::file_Exists(const std::string &filename)  {
    ifstream file(filename);
    return file.good();// Returns true if the file exists, false otherwise
}

bool Filling::openingfile(std::string x) {
    if (file_Exists(x) == true) {
        ifstream obj(x + ".txt", ios::in);
        cout << "file is open " << endl;
        return true;
    } else
        cout << " no file like this exists " << endl;
    return false;
}