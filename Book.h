//
// Created by Dylan Haas on 4/20/25.
//

#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Utilities.h"

using namespace std;
using namespace Utilities;

// Book Class
class Book {
  public:
    string title;
    string author;
    string genre;
    string publisher;
    string publicationDate;
    string price;

    Book() = default;
    Book(string& title, string& author, string& genre, string& publisher, string& date, string& price)
     : title(title), author(author), genre(genre), publisher(publisher), publicationDate(date), price(price) {}

  string bookPrint() {return "Title: " + title + ", " + author + " (Published: " + publicationDate  + ") " + " Genre(s) [" + genre + "] " + "Price: $" + price;}

  };
// Book Class

// Random Print Function
void printTop5Books (vector<Book>& books) {
    cout << "\nTop 5 books after sorting:\n";
    for (int i = 0; i < 5; i++) {cout << books[i].bookPrint() << "\n";}
}
// Random Print Function

// Compare Functions
bool compareByTitle(Book a, Book b) {return a.title < b.title;}
bool compareByAuthor(Book& a, Book& b) {return a.author < b.author;}
bool compareByGenre(Book& a, Book& b) {return a.genre < b.genre;}
bool compareByDate(Book& a, Book& b) {return a.publicationDate < b.publicationDate;}
bool compareByPublisher(Book& a, Book& b) {return a.publisher < b.publisher;}
bool compareByPrice(Book& a, Book& b) {return a.price < b.price;}
struct compareBookPrice {
    bool operator()(Book a, Book b) {
        return stof(a.price) < stof(b.price);
    }
};
// Compare Functions

// CSV Load
vector<Book> loadBooksFromCSV(string& filename) {
  vector<Book> books;
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Unable to open file.\n";
    return books;
  }

  string line;
  getline(file, line); // Skip header

  while (getline(file, line)) {
    vector<string> fields = splitCSVLine(line);
    if (fields.size() < 6) {continue;}

    string title = trim(fields[0]);
    string author = trim(fields[1]);
    string genre = trim(fields[3]);
    string publisher = trim(fields[4]);
    string date = trim(fields[5]);
    string price = getPrice(fields[6]);
    if (genre == "") {genre = "Unknown";}
    books.emplace_back(title, author, genre,publisher, date, price);
  }

  return books;
}
// CSV Load

// Search Function
vector<Book> searchBooks(vector<Book>& books, string& keyword, string& field) {
  vector<Book> results;
  for (int i = 0; i < books.size(); ++i) {
    string target;
    if (field == "title") target = books[i].title;
    else if (field == "author") target = books[i].author;
    else if (field == "genre") target = books[i].genre;

    if (target.find(keyword) != string::npos) {
      results.push_back(books[i]);
    }
  }
  return results;
}
// Search Function


vector<Book> getTopNExpensiveBooks(vector<Book>& books, int N) {
    priority_queue<Book, vector<Book>, compareBookPrice> pq;
    for (int i = 0; i < books.size(); ++i) {pq.push(books[i]);}
    vector<Book> result;
    for (int i = 0; i < N && !pq.empty(); ++i) {
        result.push_back(pq.top());
        pq.pop();
    }
    return result;
}


// Menu Loop
void menuLoop(vector<Book>& books) {
    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        if (choice == 0) break;

        char optionChoice;
        if (choice >= 1 && choice <= 4) {
            displaySortOption();
            cin >> optionChoice;
        }

        int comparisons = 0;
        auto start = chrono::high_resolution_clock::now();

        switch (choice) {
            case 1:
                if (optionChoice == 'A' || optionChoice == 'a') {
                    quickSort(books, 0, books.size() - 1, compareByTitle, comparisons);
                    printTop5Books(books);
                }
                else {
                    mergeSort(books, 0, books.size() - 1, compareByTitle, comparisons);
                    printTop5Books(books);
                }
                break;
            case 2:
                if (optionChoice == 'A' || optionChoice == 'a') {
                    quickSort(books, 0, books.size() - 1, compareByAuthor, comparisons);
                    printTop5Books(books);
                }
                else {
                    mergeSort(books, 0, books.size() - 1, compareByAuthor, comparisons);
                    printTop5Books(books);
                }
                break;
            case 3:
                if (optionChoice == 'A' || optionChoice == 'a') {
                    quickSort(books, 0, books.size() - 1, compareByPrice, comparisons);
                    printTop5Books(books);
                }
                else {
                    mergeSort(books, 0, books.size() - 1, compareByPrice, comparisons);
                    printTop5Books(books);
                }
                break;
            case 4:
                if (optionChoice == 'A' || optionChoice == 'a') {
                    quickSort(books, 0, books.size() - 1, compareByDate, comparisons);
                    printTop5Books(books);
                }
                else {
                    mergeSort(books, 0, books.size() - 1, compareByDate, comparisons);
                    printTop5Books(books);
                }
                break;
            case 5: {
                string keyword, field;
                cout << "Enter field to search (title, author, genre): ";
                cin >> field;
                cout << "Enter keyword: ";
                cin >> keyword;
                vector<Book> results = searchBooks(books, keyword, field);
                for (int i = 0; i < min(5, (int)results.size()); ++i) {
                    cout << results[i].bookPrint() << "\n";
                }
                continue;
            }
            case 6: {
                int N;
                cout << "Enter N: ";
                cin >> N;
                vector<Book> topBooks = getTopNExpensiveBooks(books, N);
                for (int i = 0; i < topBooks.size(); ++i) {
                    cout << topBooks[i].bookPrint() << "\n";
                }
                continue;
            }
            default:
                cout << "Invalid option.\n";
                continue;
        }

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Comparisons made: " << comparisons << "\n";
        cout << "Elapsed time: " << duration.count() << " seconds\n";
    }
}
// Menu Loop




#endif //BOOK_H
