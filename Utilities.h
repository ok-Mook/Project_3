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
using namespace std;

namespace Utilities {

    string trim(string& s) {
        size_t start = s.find_first_not_of(" \t\r\n");
        size_t end = s.find_last_not_of(" \t\r\n");
        if (start == std::string::npos) {
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

    template <typename T, typename Compare>
    void quickSort(vector<T>& arr, int left, int right, Compare comp, int& comparisonCount) { // Comparison Count for analysis
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

}

#endif //UTILITIES_H
