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











    /*
    for (int i = 0; i < 5; ++i) {
        std::cout << "[" << books[i].title << "]" << std::endl;
    } cout << endl;
    // Book Title Debug

    /* General Book Print Debug
    for (int i = 0; i < 5; ++i) {
        cout << books[i].bookPrint() << "\n";
    } cout << endl;
     //General Book Print Debug

    int titleComparisons = 0;
    quickSort<Book>(books, 0,books.size() - 1, compareByTitle, titleComparisons);
    cout << "Total comparisons among titles: " << titleComparisons << "\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "[" << books[i].title << "]" << std::endl;
    }

    //quickSort<Book>(books, 0, books.size() - 1, compareByTitle, comparisonCount);
    */


    return 0;
}
