#include "Book.h"

BookNode *Book::insert(BookNode *&currentNode, int &id, const string &title, const string &author, const string &isbn, const string &date) {
    if (currentNode == nullptr) {
        int newId;
        if (id == 0) {
            newId = getMaxId(root) + 1;
        } else {
            newId = id;
        }

        return new BookNode(newId, title, author, date, isbn);
    } else if (title < currentNode->title) {
        currentNode->left = insert(currentNode->left, id, title, author, isbn, date);
    } else {
        currentNode->right = insert(currentNode->right, id, title, author, isbn, date);
    }
    return currentNode;
}


BookNode *Book::buildBalancedBST(vector<BookNode *> &nodes, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = start + (end - start) / 2;
    BookNode *currentNode = nodes[mid];

    currentNode->left = buildBalancedBST(nodes, start, mid - 1);
    currentNode->right = buildBalancedBST(nodes, mid + 1, end);

    return currentNode;
}

void Book::makeBalancedTree(vector<BookNode *> &nodes) {
    root = buildBalancedBST(nodes, 0, nodes.size() - 1);
}

void Book::searchBookByISBN(BookNode *&currentNode, const string &isbn, BookNode *&temp) {

    if (currentNode == nullptr) {
        return;
    }

    searchBookByISBN(currentNode->left, isbn, temp);
    if (currentNode->isbn == isbn) {
        temp = currentNode;
    }

    searchBookByISBN(currentNode->right, isbn, temp);
}

void Book::searchBookById(BookNode *&currentNode, const int &id, BookNode *&temp) {
    if (currentNode == nullptr||temp != nullptr) {
        return;
    }

    searchBookById(currentNode->left, id, temp);
    if (currentNode->id == id) {
        temp = currentNode;
        return;
    }

    searchBookById(currentNode->right, id, temp);
}

void Book::displayInOrder(BookNode *currentNode) {
    if (currentNode) {
        displayInOrder(currentNode->left);

        cout << "ID: " << currentNode->id << " | Title: " << currentNode->title
             << " | Author: " << currentNode->author << " | ISBN: " << currentNode->isbn
             << " | Due date: " << currentNode->date << endl;

        displayInOrder(currentNode->right);
    }
}

void Book::saveFileRecursive(BookNode *currentNode, ofstream &file) {
    if (currentNode) {
        saveFileRecursive(currentNode->left, file);
        file << currentNode->id << "|" << currentNode->title << "|" << currentNode->author << "|"
             << currentNode->isbn << "|" << currentNode->date << "\n";
        saveFileRecursive(currentNode->right, file);
    }
}

void Book::insert(int book_id, const string &title, const string &author, const string &date, const string &isbn) {
    // cout<<"Here in insert\n";
    root = insert(root, book_id, title, author, date, isbn);
    // cout<<root->id<<root->title<<root->author<<root->isbn<<root->date<<endl;
}

void Book::buildLibraryFromSingleLineFile(const string &filename) {
    ifstream file(filename);
    if (file.is_open()) {
        int id;
        string title, author, isbn, date, strid;

        while (getline(file, strid, '|') && getline(file, title, '|') && getline(file, author, '|') &&
               getline(file, isbn, '|') && getline(file, date)) {
            id = stoi(strid); //changes string to int
            // cout<<"Here\n";
            // cout<<"ID:"<<id<<"\n"<<"TITLE:"<<title<<"\n"<<"AUTHOR:"<<author<<"\n"<<"ISBN:"<<isbn<<"\n"<<"DATE:"<<date<<endl;

            // cout<<id<<title<<author<<isbn<<date<<endl;
            insert(id, title, author, isbn, date);  // Use the root directly
        }

        file.close();
    } else {
        cout << "Could not open file.\n";
    }
}

void Book::display() {
    cout << "Books in Library:\n";
    displayInOrder(root);
}

void Book::saveDataToFile(const string &filename) {
    ofstream outfile(filename, ios::out);
    if (outfile.is_open()) {
        saveFileRecursive(root, outfile);
        outfile.close();
    } else {
        cout << "Could not open file for writing.\n";
    }
}

BookNode *Book::searchByISBN(const string &isbn) {
    BookNode *temp;
    searchBookByISBN(root, isbn, temp);
    return temp;
}

BookNode *Book::searchById(const int &id) {
    BookNode *temp= nullptr;
    searchBookById(root, id, temp);
    return temp;
}

BookNode *Book::searchByTitle(const string &title) {
    BookNode *temp = nullptr;
    searchBookByTitle(root, title, temp);
    return temp;
}

void Book::searchBookByTitle(BookNode *&currentNode, const string &title, BookNode *&temp) {
    if (currentNode == nullptr) {
        return;
    }

    searchBookByTitle(currentNode->left, title, temp);
    if (currentNode->title == title) {
        temp = currentNode;
        return; // If the book is found, no need to search further
    }
    searchBookByTitle(currentNode->right, title, temp);
}

void Book::borrowBook(int &id, string &date) {
    BookNode *temp = searchById(id);
    if (temp) {
        temp->date = date;
        cout << "Book is borrowed successfully. \n";
    } else {
        cout << "Book not found. \n";
    }
}

void Book::returnBook(int &id) {
    BookNode *temp = searchById(id);
    if (temp) {
        temp->date = "";
        cout << "Book is returned. \n";
    } else {
        cout << "Book not found. \n";
    }
}


void Book::updateBook(int id) {
    BookNode *temp = searchById(id);
    if (temp) {
        int choice;
        cout << "Select information to update:\n";
        cout << "1. Update ID\n";
        cout << "2. Update Title\n";
        cout << "3. Update Author's Name\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                int newId;
                cout << "Enter the new ID: ";
                cin >> newId;
                temp->id = newId;
                cout << "ID updated successfully.\n";
                break;
            case 2: {
                string newTitle;
                cout << "Enter the new title: ";
                cin.ignore();
                getline(cin, newTitle);
                temp->title = newTitle;
                cout << "Title updated successfully.\n";
                break;
            }
            case 3: {
                string newAuthor;
                cout << "Enter the new author's name: ";
                cin.ignore();
                getline(cin, newAuthor);
                temp->author = newAuthor;
                cout << "Author's name updated successfully.\n";
                break;
            }
            default:
                cout << "Invalid choice.\n";
                break;
        }
    } else {
        cout << "Book not found. \n";
    }
}
int Book::getMaxId(BookNode *currentNode) {
    if (currentNode == nullptr) {
        return INT_MIN;
    }

    int maxLeft = getMaxId(currentNode->left);
    int maxRight = getMaxId(currentNode->right);

    return max(currentNode->id, max(maxLeft, maxRight));
}
void Book::addBook() {
    int nBooks;
    cout << "Enter the number of books to add. \n";
    cin >> nBooks;

    for (int i = 0; i < nBooks; i++) {
        int id;
        string title, author, isbn, date;

        cout << "Enter book details:\n";
        cin.ignore();
        cout << "Title: ";
        getline(cin, title);
        cout << "Author: ";
        getline(cin, author);
        cout << "ISBN: ";
        getline(cin, isbn);
        cout << "Due Date: ";
        getline(cin, date);

        insert(root, id, title, author, isbn, date);
        cout << "Book added successfully with ID: " << id << "\n";

        ofstream outfile("books.txt", ios::app);
        if (outfile.is_open()) {
            outfile << id << "|" << title << "|" << author << "|" << isbn << "|" << date << "\n";
            outfile.close();
            cout << "Book details added to books.txt.\n";
        } else {
            cout << "Could not open books.txt for writing.\n";
        }
    }
}

void Book::collectNodesInOrder(BookNode *currentNode, vector<BookNode *> &nodes) {
    if (currentNode) {
        collectNodesInOrder(currentNode->left, nodes);
        nodes.push_back(currentNode);
        collectNodesInOrder(currentNode->right, nodes);
    }
}

void Book::displaySortedById() {
    // Collect all nodes in a vector
    vector<BookNode *> nodes;
    collectNodesInOrder(root, nodes);

    // Use bucket sort for sorting based on ID
    const int maxId = 100; // assuming IDs are in a reasonable range
    vector<vector<BookNode *>> buckets(maxId + 1);

    for (auto node: nodes) {
        buckets[node->id].push_back(node);
    }

    cout << "Books in Library (Sorted by ID):\n";
    for (const auto &bucket: buckets) {
        for (const auto &node: bucket) {
            cout << "ID: " << node->id << " | Title: " << node->title
                 << " | Author: " << node->author << " | ISBN: " << node->isbn
                 << " | Due date: " << node->date << endl;
        }
    }
}

void Book::displayFineForBook(int id) {
    BookNode *temp = searchById(id);

    if (temp && !temp->date.empty()) {
        string currentDate;
        cout << "Enter the current date (YYYY-MM-DD): ";
        cin >> currentDate;

        if (currentDate > temp->date) {
            int overdays;
            cout << "Enter the days of the overdue book: ";
            cin >> overdays;
            int charge = overdays * 100;

            cout << "Fine for overdue book:\n";
            cout << "ID: " << temp->id << " | Title: " << temp->title
                 << " | Author: " << temp->author << " | ISBN: " << temp->isbn
                 << " | Due date: " << temp->date << " | Fine: " << charge << " RS\n";

            // Save fine information to a file
            saveFineToFile(temp, currentDate, charge);
        } else {
            cout << "Book date is not overdue. No fine.\n";
        }
    } else {
        cout << "Book not found or does not borrowed yet. \n";
    }
}

void Book::saveFineToFile(BookNode *bookNode, const string &currentDate, int fine) {
    ofstream fineFile("fine_records.txt", ios::app); // Open file in append mode

    if (fineFile.is_open()) {
        fineFile << "ID: " << bookNode->id << " | Title: " << bookNode->title
                 << " | Author: " << bookNode->author << " | ISBN: " << bookNode->isbn
                 << " | Due date: " << bookNode->date << " | Fine: " << fine << " RS | Paid on: " << currentDate
                 << "\n";

        fineFile.close();
        cout << "Fine information saved to file.\n";
    } else {
        cout << "Could not open fine_records.txt for writing.\n";
    }
}

void Book::displayFines() {
    int numBooks;
    cout << "Enter the number of books to calculate fines: ";
    cin >> numBooks;
    for (int i = 0; i < numBooks; ++i) {
        int id;
        cout << "Enter the ID of book " << i + 1 << ": ";
        cin >> id;

        displayFineForBook(id);
    }
}

BookNode* removeBook(BookNode* currentNode, int id) {
    if (currentNode == nullptr) {
        return nullptr;
    }

    if (id < currentNode->id) {
        currentNode->left = removeBook(currentNode->left, id);
    } else if (id > currentNode->id) {
        currentNode->right = removeBook(currentNode->right, id);
    } else {
        if (currentNode->left == nullptr) {
            BookNode* temp = currentNode->right;
            delete currentNode;
            return temp;
        } else if (currentNode->right == nullptr) {
            BookNode* temp = currentNode->left;
            delete currentNode;
            return temp;
        }

        BookNode* temp = currentNode->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        currentNode->id = temp->id;
        currentNode->title = temp->title;
        currentNode->author = temp->author;
        currentNode->isbn = temp->isbn;
        currentNode->date = temp->date;

        currentNode->right = removeBook(currentNode->right, temp->id);
    }

    return currentNode;
}


void Book::removeBookById(int id) {
    if (searchById(id) == nullptr) {
        cout << "Book with ID " << id << " not found.\n";
        return;
    }

    root = removeBook(root, id);
    saveDataToFile("books.txt");
    cout << "Book with ID " << id << " removed successfully.\n";
}


void Book::removeBookByTitle(const string& title) {
    BookNode* temp = searchByTitle(title);
    if (temp == nullptr) {
        cout << "Book with title '" << title << "' not found.\n";
        return;
    }

    root = removeBook(root, temp->id);
    saveDataToFile("books.txt");
    cout << "Book with title '" << title << "' removed successfully.\n";
}


void Book::removeBookByISBN(const string& isbn) {
    BookNode* temp = searchByISBN(isbn);
    if (temp == nullptr) {
        cout << "Book with ISBN '" << isbn << "' not found.\n";
        return;
    }

    root = removeBook(root, temp->id);
    saveDataToFile("books.txt");
    cout << "Book with ISBN '" << isbn << "' removed successfully.\n";
}

void Book::removeSpecificBook() {
    int choice;
    cout << "Select how you want to remove the book:\n";
    cout << "1. Remove by ID\n";
    cout << "2. Remove by Title\n";
    cout << "3. Remove by ISBN\n";
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int idToRemove;
            cout << "Enter the ID of the book to remove: ";
            cin >> idToRemove;
            removeBookById(idToRemove);
            break;
        }
        case 2: {
            string titleToRemove;
            cout << "Enter the title of the book to remove: ";
            cin.ignore();
            getline(cin, titleToRemove);
            removeBookByTitle(titleToRemove);
            break;
        }
        case 3: {
            string isbnToRemove;
            cout << "Enter the ISBN of the book to remove: ";
            cin >> isbnToRemove;
            removeBookByISBN(isbnToRemove);
            break;
        }
        default:
            cout << "Invalid choice.\n";
            break;
    }
}
void Book::extendDueDate(int & id, int daysToExtend) {
    BookNode* temp = searchById( id);

    if (temp && !temp->date.empty()) {
        // Assuming date is stored in the format "YYYY-MM-DD"

        // Extract year, month, and day from the current date
        int year, month, day;
        sscanf(temp->date.c_str(), "%d-%d-%d", &year, &month, &day);

        // Extend the date by adding daysToExtend to the current day
        day += daysToExtend;

        // Handle month and year overflow
        while (day > 30) { // Assuming each month has 30 days for simplicity
            day -= 30;
            month++;

            if (month > 12) {
                month = 1;
                year++;
            }
        }
        // Update the due date of the book
        // Format the new date and update temp->date
        char buffer[20];
        sprintf(buffer, "%04d-%02d-%02d", year, month, day);
        temp->date = buffer;

        cout << "Due date extended successfully. New due date: " << temp->date << endl;
    } else {
        cout << "Book not found or not borrowed yet." << endl;
    }
}
void Book::saveFileSorted(BookNode *currentNode, ofstream &file) {
    if (currentNode) {
        saveFileSorted(currentNode->left, file);
        file << currentNode->id << "|" << currentNode->title << "|" << currentNode->author << "|"
             << currentNode->isbn << "|" << currentNode->date << "\n";
        saveFileSorted(currentNode->right, file);
    }
}

void Book::saveSortedDataToFile(const string &filename) {
    // Collect all nodes in a vector
    vector<BookNode *> nodes;
    collectNodesInOrder(root, nodes);

    // Use bucket sort for sorting based on ID
    const int maxId = 100; // assuming IDs are in a reasonable range
    vector<vector<BookNode *>> buckets(maxId + 1);

    for (auto node : nodes) {
        buckets[node->id].push_back(node);
    }

    // Open the file for writing
    ofstream outfile(filename, ios::out);
    if (outfile.is_open()) {
        // Save the sorted data to the file using bucket sort order
        for (const auto &bucket : buckets) {
            for (const auto &node : bucket) {
                outfile << node->id << "|" << node->title << "|" << node->author << "|"
                        << node->isbn << "|" << node->date << "\n";
            }
        }
        outfile.close();
        cout << "Sorted data saved to " << filename << ".\n";
    } else {
        cout << "Could not open file for writing.\n";
    }
}

// Call this function after sorting to save the sorted data to "books.txt"
void Book::saveSortedDataToFile() {
    saveSortedDataToFile("books.txt");
}
