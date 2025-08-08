#ifndef MAH_HASHTABLES_H
#define MAH_HASHTABLES_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
using namespace std;
#include <vector>
#include"User.h"
#include "Admin.h"
#include "Filling.h"
class Hash{
public:
    static const int table_size=10;
    vector<User*>hash_table;//do it in a constructor
    Hash():hash_table(table_size, nullptr){};
    int function(string key);
    User* search(string user_id);
    void insert(string user_name, string id, string batch);
    void Remove(string k);
    void processFile(const string& filename, Hash & hashTable);
    friend Filling;
    ~Hash();
    void rewriteToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < table_size; ++i) {
                User* current = hash_table[i];
                while (current != nullptr) {
                    file << current->user_name << " " << current->user_id << endl;
                    current = current->next;
                }
            }
            file.close();
            cout << "Hashtable contents rewritten to file successfully." << endl;
        } else {
            cerr << "Error opening the file: " << filename << endl;
        }
    }
};


#endif //MAH_HASHTABLES_H

/*

  ///DATA INPUT IN SEARCH KA FUNCTION KI IMPLEMENTATION IN USER CODE
string search_user;
cout << "Enter the user name to search: ";
cin >> search_user;

USER* found_user = hashTable.search(search_user);
if (found_user != nullptr) {
cout << "User found: " << found_user->user_name << " " << found_user->user_id << " " << found_user->batch << endl;
} else {
cout << "User not found." << endl;
cout<<"if u want to enter the user "<<endl;
filing obj;
cout<<" enter user name & id";
string y;
string x;
cin>>x>>y;
obj.CREATE("filename.txt",x,y);*/
