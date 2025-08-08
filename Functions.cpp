//
// Created by fajar.pk on 12/5/2023.
//

#include "Functions.h"
void User_book_borrow(Book & library,Hash& hash_tables) {
    library.buildLibraryFromSingleLineFile("books.txt");
    string user_name, user_id, batch, borrow_date;
    cout << "Enter your User Name: ";
    cin >> user_name;
    cout << "Enter your User ID: ";
    cin >> user_id;
    cout << "Enter your Batch: ";
    cin >> batch;
    hash_tables.processFile(batch,hash_tables);
    User *user = hash_tables.search(user_id);
    if (user != nullptr && user->user_id == user_id && user->user_name==user_name) {
        int bookIdToBorrow;
        string borrow_date;
        cout << "Enter Book ID to borrow: ";
        cin >> bookIdToBorrow;
        cout<<"Enter the due date of the book. \n";
        cin>>borrow_date;

        // Borrow the book
        library.borrowBook(bookIdToBorrow, borrow_date);

        ofstream userFile("user_info.txt", std::ios::app);
        if (userFile.is_open()) {
            userFile << user_name << " " << user_id << " " << batch << " " << bookIdToBorrow << " " << borrow_date
                     << std::endl;
            userFile.close();
        } else {
            cerr << "Error opening the user_info file." << std::endl;
        }
    } else {
        cout << "Authentication failed. User not found or invalid credentials." << std::endl;
    }
}
void user_return_book(Book& library, Hash& hash_table){

    string user_name, user_id, batch, return_date;
    cout << "Enter your User Name: ";
    cin >> user_name;
    cout << "Enter your User ID: ";
    cin >> user_id;
    cout << "Enter your Batch: ";
    cin >> batch;

    hash_table.processFile(batch,hash_table);
    User* user = hash_table.search(user_id);
    if (user != nullptr && user->user_id == user_id && user->user_name == user_name) {
        int bookIdToReturn;
        cout << "Enter Book ID to return: ";
        cin >> bookIdToReturn;

        library.returnBook(bookIdToReturn);


        ifstream inputFile("user_info.txt");
        ofstream outputFile("temp.txt");
        if (inputFile.is_open() && outputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                istringstream iss(line);
                string u_name, u_id, u_batch, b_id, b_date;
                if (iss >> u_name >> u_id >> u_batch >> b_id >> b_date) {
                    if (u_name == user_name && u_id == user_id && u_batch == batch && b_id == to_string(bookIdToReturn)) {

                    } else {
                        outputFile << line << endl;
                    }
                }
            }
            inputFile.close();
            outputFile.close();
            remove("user_info.txt");
            rename("temp.txt", "user_info.txt");
        } else {
            cerr << "Error opening the user_info file." << endl;
        }
    } else {
        cout << "Authentication failed. User not found or invalid credentials." << endl;
    }

}
void book_menu(Book & library){
    while (true) {
        cout << "==== Book Operations ====" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Search Book" << endl;
        cout << "3. Remove Book" << endl;
        cout << "4. Borrow Book" << endl;
        cout << "5. Return Book" << endl;
        cout << "6. Display Books Data" << endl;
        cout<<"7. Root node"<<endl;
        cout << "8. Back to Main Menu" << endl;
        cout << "Enter your choice: ";

        int bookChoice;
        cin >> bookChoice;

        switch (bookChoice) {
            case 1: {
                library.addBook();
                break;
            }
            case 2: {
                int searchType;
                cout << "Enter 1 to Search by ID\n ";
                cout << "Enter 2 to Search by ISBN\n";
                cout << "Enter 3 to Search by title\n";
                cout << "Enter your choice. \n";
                cin >> searchType;
                if (searchType == 1) {
                    int idToSearch;
                    cout << "Enter the id to search. \n";
                    cin >> idToSearch;
                    BookNode *foundBook = library.searchById(idToSearch);
                    if (foundBook) {
                        cout << "Book found by ISBN:\n";
                        cout << "ID: " << foundBook->id << " | Title: " << foundBook->title
                             << " | Author: " << foundBook->author << endl;
                    } else {
                        cout << "Book not found by Id.\n";
                    }
                    break;
                } else if (searchType == 2) {
                    string isbnToSearch;
                    cout << "Enter ISBN to search: ";
                    cin >> isbnToSearch;
                    BookNode *foundBook = library.searchByISBN(isbnToSearch);
                    if (foundBook) {
                        cout << "Book found by ISBN:\n";
                        cout << "ID: " << foundBook->id << " | Title: " << foundBook->title
                             << " | Author: " << foundBook->author << endl;
                    } else {
                        cout << "Book not found by ISBN.\n";
                    }
                    break;
                } else if (searchType == 3) {
                    string titleToSearch;
                    cout << "Enter the Title to search book\n";
                    cin.ignore();
                    getline(cin, titleToSearch);
                    BookNode *foundBook = library.searchByTitle(titleToSearch);
                    if (foundBook) {
                        cout << "Book found by ISBN:\n";
                        cout << "ID: " << foundBook->id << " | Title: " << foundBook->title
                             << " | Author: " << foundBook->author << endl;
                    } else {
                        cout << "Book not found by ISBN.\n";
                    }
                }
                break;
            }
            case 3:
                library.removeSpecificBook();
                break;
            case 4: {
                int bookIdToBorrow;
                string borrowDate;
                cout << "Enter Book ID to borrow: ";
                cin >> bookIdToBorrow;
                cout<<"Enter the due date of book. \n";
                cin>>borrowDate;

                library.borrowBook(bookIdToBorrow, borrowDate);
                break;
            }
            case 5: {
                int bookIdToReturn;
                cout << "Enter Book ID to return: ";
                cin >> bookIdToReturn;

                library.returnBook(bookIdToReturn);
                break;
            }
            case 6: {
                library.displaySortedById();
                library.saveSortedDataToFile();
                break;
            }
            case 7:
                library.display();
                break;
            case 8:
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
void  user_functionalities(Book &library,Hash& hashTable){
    Filling file_data; // FILLING CLASS OBJECT
    while (true) {
        cout << "==== Admin Operations ====" << endl;
        cout << "1. Add User" << endl;
        cout << "2. Remove User" << endl;
        cout << "3. User Book Borrow" << endl;
        cout << "4. User Return Book" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        int adminChoice;
        cin >> adminChoice;

        switch (adminChoice) {
            case 1: {
                string user_name, user_id, batch;
                cout << "Enter User Name: ";
                cin >> user_name;
                cout << "Enter User ID: ";
                cin >> user_id;
                cout << "Enter Batch: ";
                cin >> batch;
                file_data.create_and_check(batch, user_name, user_id);
                hashTable.processFile("2022", hashTable);
                break;
            }
            case 2: {
                string user_id, batch;
                cout << "Enter User Batch: ";
                cin >> batch;
                cout << "Enter User ID to remove: ";
                cin >> user_id;
                hashTable.processFile(batch, hashTable);
                hashTable.Remove(user_id);
                hashTable.rewriteToFile(batch);
                break;
            }
            case 3: {
                User_book_borrow(library, hashTable);
                break;
            }
            case 4: {
                user_return_book(library, hashTable);
                break;
            }
            case 5:
                return; // Exit the function
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
void libraryManagementSystem() {
    Filling file_data;
    Book library;
    Hash hashTable;
    Admin_list adminList;

    library.buildLibraryFromSingleLineFile("books.txt");

    if (adminList.performLogin(adminList)) {
        // Main menu loop
        while (true) {
            mainMenu:
            cout << "==== Library Management System ====" << endl;
            cout << "WELCOME _ ADMIN" << endl;
            cout << "1.Admin Operations" << endl;
            cout << "2. Exit" << endl;
            cout << "Enter your choice: ";

            int choice;
            cin >> choice;

            switch (choice) {

                case 1: {
                    // Admin Operations Menu
                    adminMenu:

                    cout << "==== Admin Operations ====" << endl;
                    cout << "1. USER DATABASE" << endl;
                    cout << "2. BOOKDATA BASE" << endl;
                    cout << "3. Calculate Fine" << endl;
                    cout << "4. Extend due date" <<endl;
                    cout << "5. Back to Main Menu" << endl;
                    cout << "Enter your choice: ";

                    int adminChoice;
                    cin >> adminChoice;

                    switch (adminChoice) {
                        case 1: {
                            user_functionalities(library, hashTable);
                            break;
                        }
                        case 2:
                            book_menu(library);
                            break;
                        case 3:
                            library.displayFines();
                            break;
                        case 4:
                            int days,id;
                            cout<<"Enter the book id to extend date. \n";
                            cin>>id;
                            cout<<"Enter the date to extend date.\n";
                            cin>>days;
                            library.extendDueDate(id,days);
                            break;
                        case 5:
                            goto mainMenu;
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }
                }

                    goto adminMenu;

                case 2:
                    cout << "Exiting the program. Goodbye!\n";
                    return;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }

            library.saveDataToFile("updated_books.txt");
        }
    }
}