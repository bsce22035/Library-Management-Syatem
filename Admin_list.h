
#ifndef MAH_ADMIN_LIST_H
#define MAH_ADMIN_LIST_H
#include "Admin.h"
class  Admin_list{
public:
    Admin *current_ptr;
    Admin_list():   current_ptr(nullptr){}
    void input(string name,string Id,string pass);
    bool login(string user , string id , string pass1);
    bool performLogin(Admin_list & userList) ;

};


#endif //MAH_ADMIN_LIST_H
