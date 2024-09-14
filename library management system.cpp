#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

// Structure for a Book
struct Book {
    string title;
    string author;
    string ISBN;
    bool is_available;
    time_t checkout_time;
};

// Structure for Borrower
struct Borrower {
    string name;
    vector<Book*> borrowed_books;
};

// Class for Library
class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    const int checkout_duration = 14; // Duration for which books can be borrowed (in days)
    const double fine_per_day = 1.0;  // Fine per overdue day

public:
    // Add book to library
    void addBook(string title, string author, string ISBN) {
        books.push_back({title, author, ISBN, true, 0});
        cout << "Book '" << title << "' added successfully!" << endl;
    }

    // Search for a book by title, author, or ISBN
    void searchBook(string keyword) {
        bool found = false;
        for (const auto& book : books) {
            if (book.title.find(keyword) != string::npos || 
                book.author.find(keyword) != string::npos || 
                book.ISBN.find(keyword) != string::npos) {
                found = true;
                cout << "Title: " << book.title << ", Author: " << book.author 
                     << ", ISBN: " << book.ISBN 
                     << ", Available: " << (book.is_available ? "Yes" : "No") << endl;
            }
        }
        if (!found) {
            cout << "No book found with the keyword '" << keyword << "'." << endl;
        }
    }

    // Check out a book to a borrower
    void checkoutBook(string borrower_name, string ISBN) {
        Borrower* borrower = findBorrower(borrower_name);
        if (!borrower) {
            borrowers.push_back({borrower_name, {}});
            borrower = &borrowers.back();
        }

        for (auto& book : books) {
            if (book.ISBN == ISBN && book.is_available) {
                book.is_available = false;
                book.checkout_time = time(0); // Record checkout time
                borrower->borrowed_books.push_back(&book);
                cout << "Book '" << book.title << "' checked out to " << borrower_name << "." << endl;
                return;
            }
        }
        cout << "Book with ISBN " << ISBN << " is not available for checkout." << endl;
    }

    // Return a book to the library
    void returnBook(string borrower_name, string ISBN) {
        Borrower* borrower = findBorrower(borrower_name);
        if (!borrower) {
            cout << "Borrower '" << borrower_name << "' not found!" << endl;
            return;
        }

        for (auto it = borrower->borrowed_books.begin(); it != borrower->borrowed_books.end(); ++it) {
            if ((*it)->ISBN == ISBN) {
                double fine = calculateFine((*it)->checkout_time);
                (*it)->is_available = true;
                cout << "Book '" << (*it)->title << "' returned by " << borrower_name << "." << endl;
                if (fine > 0) {
                    cout << "Fine due for overdue: $" << fixed << setprecision(2) << fine << endl;
                }
                borrower->borrowed_books.erase(it);
                return;
            }
        }
        cout << "Borrower '" << borrower_name << "' does not have a book with ISBN " << ISBN << "." << endl;
    }

    // View borrowed books for a borrower
    void viewBorrowedBooks(string borrower_name) {
        Borrower* borrower = findBorrower(borrower_name);
        if (!borrower) {
            cout << "Borrower '" << borrower_name << "' not found!" << endl;
            return;
        }

        if (borrower->borrowed_books.empty()) {
            cout << borrower_name << " has no borrowed books." << endl;
            return;
        }

        cout << "Books borrowed by " << borrower_name << ":" << endl;
        for (const auto* book : borrower->borrowed_books) {
            cout << "Title: " << book->title << ", ISBN: " << book->ISBN << endl;
        }
    }

private:
    // Find borrower by name
    Borrower* findBorrower(const string& borrower_name) {
        for (auto& borrower : borrowers) {
            if (borrower.name == borrower_name) {
                return &borrower;
            }
        }
        return nullptr;
    }

    // Calculate fine for an overdue book
    double calculateFine(time_t checkout_time) {
        time_t now = time(0);
        double seconds_overdue = difftime(now, checkout_time);
        double days_overdue = seconds_overdue / (60 * 60 * 24);
        if (days_overdue > checkout_duration) {
            return (days_overdue - checkout_duration) * fine_per_day;
        }
        return 0;
    }
};

// Main function for user interface
int main() {
    Library library;
    int choice;

    do {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add a Book" << endl;
        cout << "2. Search for a Book" << endl;
        cout << "3. Checkout a Book" << endl;
        cout << "4. Return a Book" << endl;
        cout << "5. View Borrowed Books" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character

        switch (choice) {
            case 1: {
                string title, author, ISBN;
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                cout << "Enter ISBN: ";
                getline(cin, ISBN);
                library.addBook(title, author, ISBN);
                break;
            }
            case 2: {
                string keyword;
                cout << "Enter keyword to search by title, author, or ISBN: ";
                getline(cin, keyword);
                library.searchBook(keyword);
                break;
            }
            case 3: {
                string borrower_name, ISBN;
                cout << "Enter borrower name: ";
                getline(cin, borrower_name);
                cout << "Enter book ISBN: ";
                getline(cin, ISBN);
                library.checkoutBook(borrower_name, ISBN);
                break;
            }
            case 4: {
                string borrower_name, ISBN;
                cout << "Enter borrower name: ";
                getline(cin, borrower_name);
                cout << "Enter book ISBN: ";
                getline(cin, ISBN);
                library.returnBook(borrower_name, ISBN);
                break;
            }
            case 5: {
                string borrower_name;
                cout << "Enter borrower name: ";
                getline(cin, borrower_name);
                library.viewBorrowedBooks(borrower_name);
                break;
            }
            case 6:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}