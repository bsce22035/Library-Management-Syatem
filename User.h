
#include <iostream>
#include <fstream>
//#include <filesystem>
using namespace std;
#include <vector>
class User{
public:
    string user_name;
    string user_id;
    string batch;
    User * next;
    User(string x="", string y ="", string z=" ");
    User& operator>>(User &a) {
        cout << "Enter User Name Kindly" << endl;
        cin >> a.user_name;
        cout << "Enter User ID kindly" << endl;
        cin >> a.user_id;
        cout << "Enter User Batch Kindly" << endl;
        cin >> a.batch;
        return a;
    }

    const User& operator<<(const User &a) {
        cout << "user_name: " << a.user_name << " user_id: " << a.user_id << " batch: " << a.batch << endl;
        return a;
    }

};



