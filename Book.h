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
    string publicationDate;

    Book() = default;
    Book(string& title, string& author, string& genre, string& date)
     : title(title), author(author), genre(genre), publicationDate(date) {}
    // Can expand constructor later on

    bool operator < (Book& other) {return title < other.title;} // Simple title sort
    bool operator == (Book& other) {return title == other.title;} // May need more comparisons depending on use case
    bool operator != (Book& other) {return title != other.title;} // ^^

  string bookPrint() {return "Title: " + title + " by " + author + " (Published: " + publicationDate  + ") " + "-- Genre: " + genre;}


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
    if (fields.size() < 38) continue;

    string title = trim(fields[3]);
    string author = trim(fields[11]);
    string subjects = trim(fields[2]);
    string date = trim(fields[13]);

    unordered_set<string> genreSet = {
      "Fiction", "Romance", "Fantasy", "Science Fiction",
      "Adventure", "Mystery", "Gothic", "Historical", "Satire", "Psychological"
    }; // Will add more genres or find a more efficient way


    string genre = "Unknown";
    vector<string> matchedGenres = extractGenres(subjects, genreSet);
    if (!matchedGenres.empty()) {
      genre = matchedGenres[0];
    }

    books.emplace_back(title, author, genre, date);
  }

  return books;
}






#endif //BOOK_H
