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
    // Can expand constructor later on

    bool operator < (Book& other) {return title < other.title;} // Simple title sort
    bool operator == (Book& other) {return title == other.title;} // May need more comparisons depending on use case
    bool operator != (Book& other) {return title != other.title;} // ^^

  string bookPrint() {return "Title: " + title + ", " + author + " (Published: " + publicationDate  + ") " + " Genre(s) [" + genre + "] " + "Price: $" + price;}


  }; // End Class


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
    if (fields.size() < 6) continue;

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






#endif //BOOK_H
