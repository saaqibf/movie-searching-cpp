#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

// Converts a string to lowercase for case-insensitive comparisons
string toLower(string s) {
    for (char &c : s) {
        c = tolower(c);
    }
    return s;
}

// Comparator for sorting movie titles (case-insensitive)
bool compareTitles(const pair<string, int> &a, const pair<string, int> &b) {
    return toLower(a.first) < toLower(b.first);
}

// Linear search: Searches for a movie title and counts comparisons
bool linear_search(const vector<pair<string, int>> &movies,
                   string target, int &comparisons, int &year_result) {
    comparisons = 0;
    string targetLower = toLower(target);
    for (const auto &movie : movies) {
        comparisons++;
        if (toLower(movie.first) == targetLower) {
            year_result = movie.second;
            return true;
        }
    }
    return false;
}

// Binary search: Assumes the vector is sorted and performs case-insensitive search
bool binary_search(const vector<pair<string, int>> &movies,
                   string target, int &comparisons, int &year_result) {
    int left = 0, right = movies.size() - 1;
    comparisons = 0;
    string targetLower = toLower(target);
    while (left <= right) {
        int mid = (left + right) / 2;
        comparisons++;
        string midTitle = toLower(movies[mid].first);

        if (midTitle == targetLower) {
            year_result = movies[mid].second;
            return true;
        } else if (midTitle < targetLower) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

// Executes a search function and prints the results
void search_and_report(const vector<pair<string, int>> &movies,
                       string target, string method_name,
                       bool (*search_func)(const vector<pair<string, int>> &,
                                            string, int &, int &)) {
    int comparisons = 0, year_result = 0;
    bool found = search_func(movies, target, comparisons, year_result);
    cout << method_name << ": ";
    if (found) {
        cout << "Found (" << year_result << ") [Comparisons: " << comparisons << "]\n";
    } else {
        cout << "Not Found [Comparisons: " << comparisons << "]\n";
    }
}

int main() {
    vector<pair<string, int>> movies; // Stores movie titles and years
    string title;
    int year;

    // Input movie records
    cout << "Enter movie records (type 'done' to finish):\n";
    while (true) {
        cout << "Title: ";
        getline(cin, title);
        if (toLower(title) == "done") break;
        cout << "Year: ";
        cin >> year;
        cin.ignore();
        movies.push_back({title, year});
    }

    // Sort movies by title (case-insensitive)
    sort(movies.begin(), movies.end(), compareTitles);

    // Search for movies
    string searchTerm;
    do {
        cout << "\nEnter movie title to search (type 'finish' to exit): ";
        getline(cin, searchTerm);
        if (toLower(searchTerm) == "finish") break;

        // Perform and report both linear and binary searches
        search_and_report(movies, searchTerm, "Linear search", linear_search);
        search_and_report(movies, searchTerm, "Binary search", binary_search);
    } while (true);

    return 0;
}