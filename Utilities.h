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

    string trim(string& s) {
        size_t start = s.find_first_not_of(" \t\r\n");
        size_t end = s.find_last_not_of(" \t\r\n");
        if (start == string::npos) {
            return "";
        } else {
            return s.substr(start, end - start + 1);
        }
    }

    string getPrice(string& s) {
        size_t pos = s.find('$');
        if (pos != string::npos && pos + 1 < s.length()) {return s.substr(pos + 1);}
        return "Price Unknown";
    }

    vector<string> splitCSVLine(string& line) {
        vector<string> result;
        string field;
        bool inQuotes = false;

        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                result.push_back(trim(field));
                field.clear();
            } else {
                field += c;
            }
        }

        result.push_back(trim(field));
        return result;
    }

    // Quick Sort
    template <typename T, typename compare>
    void quickSort(vector<T>& arr, int left, int right, compare comp, int& comparisonCount) { // Comparison Count for analysis
        if (left >= right) return;
        int pivotIndex = left + (right - left) / 2;
        T pivotvalue = arr[pivotIndex];

        int i = left, j = right;
        while (i <= j) {
            while (comp(arr[i], pivotvalue)) {i++; comparisonCount++;}
            while (comp(pivotvalue, arr[j])) {j--; comparisonCount++;}
            comparisonCount++;
            if (i <= j) {swap(arr[i], arr[j]); i++; j--;}
        }
        if (left < j) quickSort(arr, left, j, comp, comparisonCount);
        if (right > i) quickSort(arr, i, right, comp, comparisonCount);
    }
    // Quick Sort

    // Merge Sort
    template <typename T, typename compare>
    void merge(vector<T>& arr, int left, int mid, int right, compare comp, int& comparisonCount) {
        vector<T> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            comparisonCount++;
            if (comp(arr[i], arr[j])) {
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
    void mergeSort(vector<T>& arr, int left, int right, compare comp, int& comparisonCount) {
        if (left >= right) return;
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comp, comparisonCount);
        mergeSort(arr, mid + 1, right, comp, comparisonCount);
        merge(arr, left, mid, right, comp, comparisonCount);
    }
    // Merge Sort

    // Display Functions
    void displayMenu() {
        cout << "\nHello :)\n";
        cout << "1. Sort books by title\n";
        cout << "2. Sort books by author\n";
        cout << "3. Sort books by price\n";
        cout << "4. Sort books by publication date\n";
        cout << "5. Search books\n";
        cout << "6. Show top-N expensive books\n";
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
