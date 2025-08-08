//
// Created by ITU_CE22 on 04-Nov-23.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "BookNode.h"
#include <climits>

using namespace std;

class Book {
public:

public:
    BookNode *root;
    string bookFile;

    Book() : root(nullptr) {
        bookFile = "books.txt";
    }

    BookNode *insert(BookNode *&currentNode, int &id, const string &title, const string &author,const string &isbn, const string &date);
    BookNode *buildBalancedBST(vector<BookNode *> &nodes, int start, int end) ;
    void searchBookByISBN(BookNode *&currentNode, const string &isbn, BookNode *&temp);
    void searchBookById(BookNode *&currentNode, const int &id, BookNode *&temp);
    void searchBookByTitle(BookNode *&currentNode, const string &title, BookNode *&temp);
    void displayInOrder(BookNode *currentNode);
    void saveFileRecursive(BookNode *currentNode, ofstream &file);
    void makeBalancedTree(vector<BookNode *> &nodes);
    void insert(int id, const string &title, const string &author, const string &date, const string &isbn) ;
    void buildLibraryFromSingleLineFile(const string &filename) ;
    void display() ;
    void removeBookById(int id);
    void removeBookByTitle(const string& title);
    void removeBookByISBN(const string& isbn);
    void removeSpecificBook();
    void updateBook(int id);
    void displayFineForBook(int id);
    int getMaxId(BookNode *currentNode);
    void addBook();
    void saveDataToFile(const string &filename);
    BookNode *searchByISBN(const string &isbn);
    BookNode *searchById(const int& id);
    BookNode *searchByTitle(const string& title);
    void borrowBook(int &id, string &date);
    void returnBook(int &id) ;
    void extendDueDate(int & id, int daysToExtend);
    void displaySortedById();
    void saveFineToFile(BookNode *bookNode, const string &currentDate, int fine);
    void displayFines();
    void collectNodesInOrder(BookNode* currentNode, vector<BookNode*>& nodes);
    void saveSortedDataToFile();
    void saveSortedDataToFile(const string &filename);
    void saveFileSorted(BookNode *currentNode, ofstream &file);

};

