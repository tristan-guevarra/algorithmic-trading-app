#ifndef DICT_H
#define DICT_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>

// Struct to hold definition data with its associated module
struct Definition {
    std::string meaning;
    std::string module; // Module this definition belongs to
};

// Struct to hold student data
struct Student {
    int studentID;
    std::unordered_set<std::string> completedModules; // Track the modules the student has completed
};

// Dict Class
class Dict {

public:
    std::unordered_map<std::string, std::vector<Definition>> dict; // Dictionary storing words and definitions
    std::unordered_map<int, Student> students; // Mapping studentID to student data
    Dict();

    // Add a word with its meaning and associated module
    void addWord(const std::string &word, const std::string &meaning, const std::string &module);

    // Remove a word from the dictionary
    void removeWord(const std::string &word);

    // Register a new student by studentID
    void registerStudent(int studentID);

    // Mark a module as completed for a student
    void completeModule(int studentID, const std::string &module);

    // Get the first meaning of a word visible to the student based on completed modules
    std::string getMeaning(const std::string &word, int studentID) const;

    // Display all words and meanings visible to the student based on completed modules
    void displayAllDefinitions(int studentID) const;

    // Save dictionary and student data to a file
    void saveToFile(const std::string &filename) const;

    // Load dictionary and student data from a file
    void loadFromFile(const std::string &filename);
};

#endif // DICT_H
