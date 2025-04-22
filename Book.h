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

  string bookPrint() {return "Title: " + title + ", By " + author + " (Published: " + publicationDate  + ") " + " Genre(s) [" + genre + "] " + "Price: $" + price;}

  };
// Book Class

// Random Print Function
void printTop5Books (vector<Book>& books) {
    cout << "\nTop 5 books after sorting:\n";
    for (int i = 0; i < 5; i++) {cout << books[i].bookPrint() << "\n";}
}
// Random Print Function

// Compare Functions
inline bool compareByTitle(Book& a, Book& b) {return a.title < b.title;}
inline bool compareByAuthor(Book& a, Book& b) {
    return a.author < b.author;
}
bool compareByGenre(Book& a, Book& b) {return a.genre < b.genre;}
bool compareByDate(Book& a, Book& b) {return a.publicationDate < b.publicationDate;}
bool compareByPublisher(Book& a, Book& b) {return a.publisher < b.publisher;}
bool compareByPrice(Book& a, Book& b) {
    string pa = a.price;
    string pb = b.price;

    pa.erase(remove(pa.begin(), pa.end(), ','), pa.end());
    pb.erase(remove(pb.begin(), pb.end(), ','), pb.end());

    return stof(pa) < stof(pb);
}
struct compareBookPrice { // For priority que (Max Heap)
    bool operator()(Book& a, Book& b) {
        string pa = a.price;
        string pb = b.price;

        pa.erase(remove(pa.begin(), pa.end(), ','), pa.end());
        pb.erase(remove(pb.begin(), pb.end(), ','), pb.end());
        return stof(pa) < stof(pb);
    }
};

template <typename compare>
bool flexibleComp(Book a, Book b, compare comp, bool descending) {
    if (descending) {return comp(a, b);}
    return comp(b, a);
}
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
    string author = cleanAuthor(fields[1]);
    string genre = cleanGenre(fields[3]);
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
    else if (field == "genre") {
        string loweredKeyword = keyword;
        transform(loweredKeyword.begin(), loweredKeyword.end(), loweredKeyword.begin(), ::tolower);
        if (genreMatch(books[i].genre, loweredKeyword)) {results.push_back(books[i]);}
    }

    if (target.find(keyword) != string::npos) {
      results.push_back(books[i]);
    }
  }
  return results;
}
// Search Function

// Uhhhhhh
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
// Uhhhhhh

// Bench
void benchmarkSorts(vector<Book>& books, string field) {
    bool descending = true;

    int quickComparisons = 0, mergeComparisons = 0;
    vector<Book> quickData = books;
    vector<Book> mergeData = books;

    function<bool(Book&, Book&)> compare;
    if (field == "title") compare = compareByTitle;
    else if (field == "author") compare = compareByAuthor;
    else if (field == "price") compare = compareByPrice;
    else if (field == "date") compare = compareByDate;
    else {cout << "Invalid field.\n"; return;}

    auto qStart = chrono::high_resolution_clock::now();
    quickSort(quickData, 0, quickData.size() - 1, compare, quickComparisons, descending);
    auto qEnd = chrono::high_resolution_clock::now();
    double quickTime = chrono::duration<double>(qEnd - qStart).count();

    auto mStart = chrono::high_resolution_clock::now();
    mergeSort(mergeData, 0, mergeData.size() - 1, compare, mergeComparisons, descending);
    auto mEnd = chrono::high_resolution_clock::now();
    double mergeTime = chrono::duration<double>(mEnd - mStart).count();

    double comparisonDiff = 100.0 * abs(quickComparisons - mergeComparisons) / (quickComparisons + mergeComparisons);
    double timeDiff = 100.0 * abs(quickTime - mergeTime) / (quickTime + mergeTime);

    cout << "\nBenchmark Results: Sort by " << field << " (Descending)\n";
    cout << "QuickSort:\n  Comparisons: " << quickComparisons << "\n  Time: " << quickTime << "s\n";
    cout << "MergeSort:\n  Comparisons: " << mergeComparisons << "\n  Time: " << mergeTime << "s\n";
    cout << fixed << setprecision(2);
    cout << "\nComparison Summary:\n";
    if (mergeComparisons < quickComparisons)
        cout << "  MergeSort used " << comparisonDiff << "% fewer comparisons.\n";
    else
        cout << "  QuickSort used " << comparisonDiff << "% fewer comparisons.\n";

    if (mergeTime < quickTime)
        cout << "  MergeSort was " << timeDiff << "% faster.\n";
    else
        cout << "  QuickSort was " << timeDiff << "% faster.\n";
}
// Bench

// Menu Loop
void menuLoop(vector<Book>& books) {
    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        if (choice == 0) break;
        char optionChoice;
        bool descending = false;

        if (choice >= 1 && choice <= 4) {
            displaySortOption();
            cin >> optionChoice;
            char sortOrder;
            cout << "Sort ascending (A) or descending (D)? ";
            cin >> sortOrder;
            descending = (sortOrder == 'D' || sortOrder == 'd');
        }

        int comparisons = 0;
        auto start = chrono::high_resolution_clock::now();

        switch (choice) {
            case 1:
                if (optionChoice == 'A' || optionChoice == 'a') {
                    quickSort(books, 0, books.size() - 1, compareByTitle, comparisons, descending);
                    printTop5Books(books);
                }
                else {
                    mergeSort(books, 0, books.size() - 1, compareByTitle, comparisons, descending);
                    printTop5Books(books);
                }
                break;
            case 2:
                if (optionChoice == 'A' || optionChoice == 'a') {
                    quickSort(books, 0, books.size() - 1, compareByAuthor, comparisons, descending);
                    printTop5Books(books);
                }
                else {
                    mergeSort(books, 0, books.size() - 1, compareByAuthor, comparisons, descending);
                    printTop5Books(books);
                }
                break;
            case 3:
                if (optionChoice == 'A' || optionChoice == 'a') {
                    quickSort(books, 0, books.size() - 1, compareByPrice, comparisons, descending);
                    printTop5Books(books);
                }
                else {
                    mergeSort(books, 0, books.size() - 1, compareByPrice, comparisons, descending);
                    printTop5Books(books);
                }
                break;
            case 4:
                if (optionChoice == 'A' || optionChoice == 'a') {
                    quickSort(books, 0, books.size() - 1, compareByDate, comparisons, descending);
                    printTop5Books(books);
                }
                else {
                    mergeSort(books, 0, books.size() - 1, compareByDate, comparisons, descending);
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
            case 7: {
                string field;
                cout << "Enter field to benchmark (title, author, price, date): ";
                cin >> field;
                benchmarkSorts(books, field);
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
