//
// Created by fajar.pk on 11/15/2023.
//

#include "HashTables.h"

int Hash::function( string key){ // giving the key id
        int a_value=0; // assigning in a particular value that is zero
        int index; //indexing value check
        for(int i=0;i<key.length();i++){
            a_value=a_value+(int)key[i];
        }
        index=a_value%table_size;
        return index; // returns a index
    }

void Hash::processFile(const std::string &filename, Hash &hashTable){
  //  Filling check_file;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string user_Name, Id;
            if (iss >> user_Name >> Id) {
                // Assuming your insert function is similar to the one you provided
                hashTable.insert(user_Name, Id, filename);  // Replace "BatchValue" with the actual batch value
            } else {
                cerr << "Error in seprating  line: " << line << endl;
            }
        }
        file.close();
    }
    else if(!file.is_open()){
        cerr << "Error opening the file: " << filename << endl;
    }
    else{
        cout<<"file not open"<<endl;
    }
}

void Hash::insert(std::string user_name, std::string id, std::string batch) {
    int value_in_table = function(id);

    // Check if the user information already exists in the table
    User *existing_User = hash_table[value_in_table];
    while (existing_User != nullptr) {
        if (existing_User->user_name == user_name && existing_User->user_id == id) {
            // User already exists, do not insert again
            cout << "User already exists." << endl;
            return;
        }
        existing_User = existing_User->next;

    }

    // User does not exist, proceed with insertion
    User *new_User = new User();
    new_User->user_name = user_name;
    new_User->user_id = id;
    new_User->batch = batch;

    if (hash_table[value_in_table] == nullptr) {
        // If the index is empty, create a new User and set it as the head
        hash_table[value_in_table] = new_User;
    } else {
        User *temporary = hash_table[value_in_table];
        while (temporary->next != nullptr) {
            temporary = temporary->next;
        }
        temporary->next = new_User;
    }
}

void Hash::Remove(std::string user_id){
    int value_2= function(user_id);
    User* current = hash_table[value_2];
    User* prev = nullptr;

    while (current != nullptr) {
        if (current->user_id == user_id) {
            // User found, remove from the hashtable
            if (prev == nullptr) {
                // User is the head of the linked list
                hash_table[value_2] = current->next;
            } else {
                prev->next = current->next;
            }

            delete current;
            cout << "User with ID " << user_id << " removed successfully." << endl;
            return;
        }

        prev = current;
        current = current->next;
    }

    cout << "User with ID " << user_id << " not found." << endl;
}


Hash::~Hash() {
    for (int i = 0; i < table_size; ++i) {
        User *current = hash_table[i];
        while (current) {
            User *temp = current;
            current = current->next;
            delete temp;
        }
    }
}

User *Hash::search(std::string user_id){
    int index = function(user_id);

    User* current = hash_table[index];
    while (current != nullptr) {
        if (current->user_id == user_id) {
            // User found
            return current;
        }
        current = current->next;
    }

    // User not found
    return nullptr;
}