//
// Created by fajar.pk on 11/15/2023.
//

#ifndef MAH_ADMIN_H
#define MAH_ADMIN_H
#include <iostream>
using namespace std;
#include "Book.h"
#include "HashTables.h"

class Admin{
 string Admin_name;
 string Admin_Id;
 string password;
public:
 //   static  Admin* ptr;
 Admin *link;
    Admin(){
        Admin_Id="1";
        Admin_name="1";
        password="1";
        link= nullptr;
    }

 void get_Name(string x);
 void get_Id(string identityNo);
 void get_Pass(string Pass);
 string set_Name();
 string set_Id();
 string set_password();

};


#endif //MAH_ADMIN_H
