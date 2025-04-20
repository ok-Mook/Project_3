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

    vector<string> splitGenres(string& s) {
        vector<string> result;
        stringstream ss(s);
        string item;
        while (getline(ss, item, ',')) {
            result.push_back(trim(item));
        }
        return result;
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

    vector<string> extractGenres(string& subjectField, unordered_set<string>& genreSet) {
        vector<string> matchedGenres;

        // Delimiters
        string cleaned = subjectField;
        replace(cleaned.begin(), cleaned.end(), ',', ';');
        replace(cleaned.begin(), cleaned.end(), '-', ' ');
        stringstream ss(cleaned);
        string token;

        while (getline(ss, token, ';')) {
            string phrase = trim(token);
            for (auto& genre : genreSet) {
                if (phrase.find(genre) != string::npos) {
                    matchedGenres.push_back(genre);
                    break;
                }
            }
        }
        return matchedGenres;
    }


}

#endif //UTILITIES_H
