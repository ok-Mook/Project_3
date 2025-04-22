//
// Created by Dylan Haas on 4/20/25.
//

#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <chrono>
#include <queue>
#include "Book.h"
using namespace std;

namespace Utilities {

    // This Guy
    string toLower(const string& s) {
        string result = s;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    // This Guy


    // Parsing Helpers
    // Trim
    string trim(const string& s) {
        size_t start = s.find_first_not_of(" \t\r\n");
        size_t end = s.find_last_not_of(" \t\r\n");
        if (start == string::npos) {return "";}
        else {return s.substr(start, end - start + 1);}
    }
    // Trim

    // CSV
    vector<string> splitCSVLine(string& line) {
        vector<string> result;
        string field;
        bool inQuotes = false;

        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c == '"') {inQuotes = !inQuotes;}
            else if (c == ',' && !inQuotes) {
                result.push_back(trim(field));
                field.clear();
            } else {field += c;}
        }
        result.push_back(trim(field));
        return result;
    }
    // CSV
    // Parsing Helpers


    // Field Cleaning
    // Author
    string cleanAuthor(const string& raw) { // Attempt to get rid of edge cases. There are too many to go through atm.
        string author = trim(raw);

        if (author.substr(0, 3) == "By ") {author = trim(author.substr(3));}
        while (!author.empty() && (author.back() == '.' || author.back() == ',')) {author.pop_back();}
        if (author == "#value!" || author == "." || author == ".." || author == "#REF!") {return "Unknown";}
        if (!author.empty() && author.front() == '\'' && author.back() == '\'') {author = author.substr(1, author.length() - 2);}

        size_t open = 0;
        while ((open = author.find('(')) != string::npos) {
            size_t close = author.find(')', open);
            if (close != string::npos) {
                author.erase(open, close - open + 1);
            } else {
                break;
            }
        }

        while (author.find("  ") != string::npos) {author = author.replace(author.find("  "), 2, " ");}

        author = trim(author);

        int digits = count_if(author.begin(), author.end(), ::isdigit);
        int letters = count_if(author.begin(), author.end(), ::isalpha);
        if ((digits > letters && digits > 3) || author.length() < 3 || letters == 0) {return "Unknown";}

        return author;
    }
    // Author

    // Genre
    string cleanGenre(const string& raw) {
        stringstream ss(raw);
        vector<string> tokens;
        string token;

        while (getline(ss, token, ',')) {
            token = trim(token);
            if (toLower(token) != "general" && !token.empty()) {tokens.push_back(token);}
        }

        if (tokens.empty()) {return "Miscellaneous";}

        string result = tokens[0];
        for (int i = 1; i < tokens.size(); ++i) {
            result += " , " + tokens[i];
        }
        return result;
    }
    // Genre
    // Field cleaning


    // Search Helper
    bool genreMatch(string& genreField, string& keyword) {
        stringstream ss(genreField);
        string token;
        string lowerKeyword = toLower(keyword);
        while (getline(ss, token, ',')) {
            token = toLower(trim(token));
            if (token == lowerKeyword) {return true;}
            if (token.find(lowerKeyword) != string::npos && !(lowerKeyword == "fiction" && token.find("nonfiction") != string::npos)) {return true;}
        }
        return false;
    }
    // Search Helper


    // This Other Guy
    string getPrice(string& s) {
        size_t pos = s.find('$');
        if (pos != string::npos && pos + 1 < s.length()) {return s.substr(pos + 1);}
        return "Price Unknown";
    }
    // This Other Guy


    // Sorts
    // Quick Sort
    template <typename T, typename compare>
    void quickSort(vector<T>& arr, int left, int right, compare comp, int& comparisonCount, bool descending) { // Comparison Count for analysis
        if (left >= right) return;
        int pivotIndex = left + (right - left) / 2;
        T pivotvalue = arr[pivotIndex];

        int i = left, j = right;
        while (i <= j) {
            while (flexibleComp(arr[i], pivotvalue, comp, descending)) {i++; comparisonCount++;}
            while (flexibleComp(pivotvalue, arr[j], comp, descending)) {j--; comparisonCount++;}
            comparisonCount++;
            if (i <= j) {swap(arr[i], arr[j]); i++; j--;}
        }
        if (left < j) quickSort(arr, left, j, comp, comparisonCount, descending);
        if (right > i) quickSort(arr, i, right, comp, comparisonCount, descending);
    }
    // Quick Sort


    // Merge Sort
    template <typename T, typename compare>
    void merge(vector<T>& arr, int left, int mid, int right, compare comp, int& comparisonCount, bool descending) {
        vector<T> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            comparisonCount++;
            if (flexibleComp(arr[i], arr[j], comp, descending)) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }
        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];

        for (int x = 0; x < temp.size(); ++x) {
            arr[left + x] = temp[x];
        }
    }

    template <typename T, typename compare>
    void mergeSort(vector<T>& arr, int left, int right, compare comp, int& comparisonCount, bool descending) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comp, comparisonCount, descending);
        mergeSort(arr, mid + 1, right, comp, comparisonCount, descending);
        merge(arr, left, mid, right, comp, comparisonCount, descending);
    }
    // Merge Sort
    // Sorts


    // Display Functions
    void displayMenu() {
        cout << "\nHello :)\n";
        cout << "1. Sort books by title\n";
        cout << "2. Sort books by author\n";
        cout << "3. Sort books by price\n";
        cout << "4. Sort books by publication date\n";
        cout << "5. Search books\n";
        cout << "6. Show top-N expensive books\n";
        cout << "7. Benchmark QuickSort vs MergeSort\n";
        cout << "0. Exit\n";
    }

    void displaySortOption() {
        cout << "\nChoose sorting algorithm:\n";
        cout << "A. QuickSort\n";
        cout << "B. MergeSort\n";
    }
    // Display Functions





}

#endif //UTILITIES_H
