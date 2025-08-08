#include "Admin_list.h"

void Admin_list::input(std::string name, std::string Id, std::string pass){
    Admin *ptr=new Admin;
    ptr->get_Name(name);
    ptr->get_Id(Id);
    ptr->get_Pass(pass);
    ptr->link=current_ptr;
    current_ptr=ptr;
}

bool Admin_list::login(std::string user, std::string id, std::string pass1) {
    //   static int counter =3;
    Admin *new_ptr=new Admin;
    //  new_ptr =current_ptr;
    while(new_ptr){
        if(new_ptr->set_Name()==user && new_ptr->set_Id()==id && new_ptr->set_password()==pass1){
            cout<<"found"<<endl;
            return true;
        }
        else
            new_ptr=new_ptr->link;
    }
    cout<<"not valid"<<endl;
    return false;
}

bool Admin_list::performLogin(Admin_list &userList) {
    for (int attempt = 0; attempt < 3; ++attempt) {
        // Prompt for login credentials
        string username, password, id;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter id: ";
        cin >> id;
        cout << "Enter password: ";
        cin >> password;

        if (userList.login(username, id, password)) {
            return true;
        } else {
            cout << "Invalid entry. Please try again." << endl;
        }
    }

    cout << "Too many login attempts. Could not access it." << endl;
    return false;
}