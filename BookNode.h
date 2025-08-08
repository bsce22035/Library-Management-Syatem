//
// Created by ITU_CE22 on 09-Nov-23.
//

#ifndef BOOK_CPP_BOOKNODE_H
#define BOOK_CPP_BOOKNODE_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class BookNode {
public:
int id;
string title;
string author;
string date;
string isbn;
BookNode* left;
BookNode* right;
//BookNode(){
//    id=0;
//    title=" ";
//    author=" ";
//    date=0;
//    left= nullptr;
//    right= nullptr;
//}
BookNode(int i=0, string t="",string aut="",string d="",string is="",BookNode*l= nullptr,BookNode*r= nullptr){
    id=i;
    title=t;
    author=aut;
    date=d;
    isbn=is;
    left=l;
    right=r;

}
//    BookNode(int id, const string& title, const string& author)
//            : id(id), title(title), author(author), dateToExtend(dateToExtend), left(nullptr), right(nullptr) {}
};


#endif //BOOK_CPP_BOOKNODE_H
