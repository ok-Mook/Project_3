//
// Created by Dylan Haas on 4/20/25.
//

#include "Book.h"
#include "Utilities.h"
using namespace Utilities;
using namespace std;


int main() {
    string path = "BooksDataset.csv";
    vector<Book> books = loadBooksFromCSV(path);
    menuLoop(books);
    return 0;
}
