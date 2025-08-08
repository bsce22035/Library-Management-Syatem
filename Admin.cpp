#include "Admin.h"
void Admin::get_Pass(std::string Pass){ password=Pass;}
void Admin::get_Id(std::string identityNo) {Admin_Id=identityNo;}
void Admin::get_Name(std::string x) { Admin_name=x;}
string Admin::set_Id(){return Admin_Id;}
string Admin::set_Name(){return Admin_name;}
string Admin::set_password(){return password;}