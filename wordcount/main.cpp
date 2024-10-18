#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

string cleanWord(const string &word) {
    string cleanedWord;
    for (char c : word) {
        if (isalpha(c) || c == '\'' || c == ',') {
            cleanedWord += c;
        }
    }
    return cleanedWord;
}

int main() {
    string filename;
    cout << "Input file: ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error! The file " << filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, pair<int, set<int>>> wordMap;
    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;
        stringstream ss(line);
        string word;
        set<string> seenWords;

        while (ss >> word) {
            word = cleanWord(word);
            if (!word.empty() && seenWords.find(word) == seenWords.end()) {
                seenWords.insert(word);
                wordMap[word].first++;
                wordMap[word].second.insert(lineNumber);
            }
        }
    }

    file.close();

    for (const auto& [word, value] : wordMap) {
        const auto& [count, lines] = value;
        cout << word << " " << count << ": ";
        for (auto it = lines.begin(); it != lines.end(); ++it) {
            if (it != lines.begin()) cout << ", ";
            cout << *it;
        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}
