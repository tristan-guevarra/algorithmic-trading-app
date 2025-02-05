#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream> // For file I/O

using namespace std;

// Struct to hold definition data with its associated module
struct Definition {
    string meaning;
    string module; // Module this definition belongs to
};

// Struct to hold student data
struct Student {
    int studentID;
    unordered_set<string> completedModules; // Track the modules the student has completed
};

// Dict Class
class Dict {
private:
    unordered_map<string, vector<Definition>> dict; // Dictionary storing words and definitions
    unordered_map<int, Student> students; // Mapping studentID to student data

public:
    Dict();

    // Add a word with its meaning and associated module
    void addWord(string word, string meaning, string module) {
        Definition def = {meaning, module};
        dict[word].push_back(def);
    }

    // Remove a word from the dictionary
    void removeWord(string word) {
        dict.erase(word);
    }

    // Register a new student by studentID
    void registerStudent(int studentID) {
        students[studentID] = Student{studentID, {}};
    }

    // Mark a module as completed for a student
    void completeModule(int studentID, string module) {
        if (students.find(studentID) != students.end()) {
            students[studentID].completedModules.insert(module);
        }
    }

    // Get the first meaning of a word visible to the student based on completed modules
    string getMeaning(string word, int studentID) {
        if (dict.find(word) == dict.end()) {
            return "Definition not found.";
        } else {
            for (const auto& def : dict[word]) {
                // Check if the student has completed the module required to view this definition
                if (students[studentID].completedModules.find(def.module) != students[studentID].completedModules.end()) {
                    return def.meaning;
                }
            }
            return "No definition available for this student.";
        }
    }

    // Display all words and meanings visible to the student based on completed modules
    void displayAllDefinitions(int studentID) {
        if (students.find(studentID) == students.end()) {
            cout << "Student not found." << endl;
            return;
        }
        for (const auto& i : dict) {
            cout << i.first << ":\n";  // Print the word (key)
            for (const auto& def : i.second) {  // Loop through all meanings for this word
                // Check if the student has completed the module required to view this definition
                if (students[studentID].completedModules.find(def.module) != students[studentID].completedModules.end()) {
                    cout << "- " << def.meaning << " (Module: " << def.module << ")\n";  // Print each meaning
                }
            }
        }
    }

    // Save dictionary and student data to a file
    void saveToFile(string filename) {
        ofstream file(filename);
        // Save dictionary
        for (const auto& entry : dict) {
            file << entry.first << "\n";
            for (const auto& def : entry.second) {
                file << def.meaning << "\n" << def.module << "\n";
            }
        }
        // Save student data
        for (const auto& studentEntry : students) {
            file << "Student: " << studentEntry.second.studentID << "\n";
            for (const auto& module : studentEntry.second.completedModules) {
                file << module << "\n";
            }
        }
        file.close();
    }

    // Load dictionary and student data from a file
    void loadFromFile(string filename) {
        ifstream file(filename);
        string word, meaning, module, temp;
        while (getline(file, word)) {
            // Check if it's a student entry
            if (word.rfind("Student:", 0) == 0) {
                int studentID = stoi(word.substr(8));
                Student student{studentID, {}};
                while (getline(file, module) && !module.empty()) {
                    student.completedModules.insert(module);
                }
                students[studentID] = student;
            } else {
                vector<Definition> definitions;
                while (getline(file, meaning) && getline(file, module)) {
                    definitions.push_back({meaning, module});
                }
                dict[word] = definitions;
            }
        }
        file.close();
    }
};

// Constructor for Dict class
Dict::Dict() {
    dict = unordered_map<string, vector<Definition>>();
    students = unordered_map<int, Student>();
}

// Main function with stock-related terms and multiple students completing modules
int main() {
    Dict dictionary;

    // Add stock-related terms with associated modules
    dictionary.addWord("Stock", "A type of security that signifies ownership in a corporation.", "Module 1");
    dictionary.addWord("Bond", "A fixed income instrument representing a loan made by an investor to a borrower.", "Module 1");
    dictionary.addWord("Dividend", "A distribution of profits by a corporation to its shareholders.", "Module 2");
    dictionary.addWord("ETF", "An Exchange Traded Fund is a type of investment fund traded on stock exchanges.", "Module 2");
    dictionary.addWord("IPO", "An Initial Public Offering (IPO) is when a private company offers shares to the public for the first time.", "Module 3");
    dictionary.addWord("Blue Chip Stocks", "Shares of large, well-established companies with a history of reliable performance.", "Module 3");

    // Register students
    dictionary.registerStudent(1001);
    dictionary.registerStudent(1002);
    dictionary.registerStudent(1003);

    // Student 1001 completes Module 1 and Module 2
    dictionary.completeModule(1001, "Module 1");
    dictionary.completeModule(1001, "Module 2");

    // Student 1002 completes Module 1
    dictionary.completeModule(1002, "Module 1");

    // Student 1003 completes Module 3
    dictionary.completeModule(1003, "Module 3");

    // Display all visible definitions for each student
    cout << "\nDictionary entries for Student 1001 (Modules 1 and 2 completed):\n";
    dictionary.displayAllDefinitions(1001);

    cout << "\nDictionary entries for Student 1002 (Module 1 completed):\n";
    dictionary.displayAllDefinitions(1002);

    cout << "\nDictionary entries for Student 1003 (Module 3 completed):\n";
    dictionary.displayAllDefinitions(1003);

    // // Save dictionary and student data to a file
    // dictionary.saveToFile("stock_dictionary.txt");

    // // Load the data from the file (for demonstration)
    // Dict loadedDictionary;
    // loadedDictionary.loadFromFile("stock_dictionary.txt");

    // // Display loaded definitions for students
    // cout << "\nLoaded dictionary entries for Student 1001:\n";
    // loadedDictionary.displayAllDefinitions(1001);

    return 0;
}
