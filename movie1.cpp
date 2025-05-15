#include <iostream>  
#include <string>  
#include <cctype>  
using namespace std;  

// Converts string to lowercase
string toLower(string s) {  
    for(char &c : s) {
        c = tolower(c);
    }
    return s;
}  

// --- REQUIRED METHODS --- 
// Insertion sort 
void sort(string titles[], int years[], int n) {  
    for(int i = 0; i < n; i++) {
        string keyTitle = titles[i];
        int keyYear = years[i];
        int j = i - 1;
        while (j >= 0 && toLower(titles[j]) > toLower(keyTitle)) {
            titles[j + 1] = titles[j];
            years[j + 1] = years[j];
            j--;
        }
        titles[j + 1]= keyTitle;
        years[j + 1] = keyYear;
    } 
}  
// Linear search
// Searches for a movie title and counts comparisons
bool linear_search(const string titles[], const int years[], int n,  
                   string target, int &comparisons, int &year_result) {  
    comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if(toLower(titles[i]) == toLower(target)) {
            year_result = years[i];
            return true;
        }
    } 
    return false;
}  
// Binary search
// Searches for a movie title in a sorted array and counts comparisons
bool binary_search(const string titles[], const int years[], int n,  
                   string target, int &comparisons, int &year_result) {  
    int left = 0, right = n - 1;
    comparisons = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        comparisons++;
        string midTitle = toLower(titles[mid]);
        string targetLower = toLower(target);
    
        if (midTitle == targetLower){ 
            year_result = years[mid];
            return true;
        } else if(midTitle < targetLower) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

// Resize the dynamic array
void resize(string *&titles, int *&years, int &capacity) {  
    int new_capacity = capacity * 2;
    string *newTitles = new string[new_capacity];
    int *newYears = new int[new_capacity];

    for (int i = 0; i < capacity; i++) {
        newTitles[i] = titles[i];
        newYears[i] = years[i];
    }
    delete[] titles;
    delete[] years;

    titles = newTitles;
    years = newYears;
    capacity = new_capacity;
}  

void search_and_report(const string titles[], const int years[], int n,  
                       string target, string method_name,  
                       bool (*search_func)(const string[], const int[], int,  
                                          string, int&, int&)) {  
    int comparisons = 0, year_result = 0;
    bool found = search_func(titles, years, n, target, comparisons, year_result);
    cout << method_name << ": ";
    if (found) {
        cout << "Found (" << year_result << ") [Comparisons: " << comparisons << "]\n";
    } else {
        cout << "Not Found [Comparisons: " << comparisons << "]\n";
    }
}  

// --- MAIN FUNCTION (PARTIALLY COMPLETED) ---  
int main() {  
    int capacity = 2, size = 0;  
    string *titles = new string[capacity];  
    int *years = new int[capacity];  
    string input;  
    int year;  

    // Input movies  
    cout << "Enter movie records (type 'done' to finish):\n";  
    while(true) {  
        cout << "Title: ";  
        getline(cin, input);  
        if(toLower(input) == "done") break;  

        if(size == capacity) {  
            resize(titles, years, capacity); 
        }  

        titles[size] = input;  
        cout << "Year: ";  
        cin >> year;  
        cin.ignore();  
        years[size++] = year;  
    }  

    // Sort 
    sort(titles, years, size);

    // Search interface  
    string searchTerm;  
    do {  
        cout << "\nEnter movie title to search (type 'finish' to exit): ";  
        getline(cin, searchTerm);  
        if(toLower(searchTerm) == "finish") break;  

        search_and_report(titles, years, size, searchTerm, "Linear search", linear_search);
        search_and_report(titles, years, size, searchTerm, "Binary search", binary_search);  
    } while(true);  

    delete[] titles;  
    delete[] years;  
    return 0;  
}  
