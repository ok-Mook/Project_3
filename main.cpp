//
// Created by Dylan Haas on 4/20/25.
//

#include "Book.h"
#include "Utilities.h"
using namespace Utilities;
using namespace std;


int main() {
    string path = "classics.csv";
    vector<Book> books = loadBooksFromCSV(path);

    for (int i = 0; i < min(5, (int)books.size()); ++i) {
        cout << books[i].bookPrint() << "\n";
    }

    return 0;
}
