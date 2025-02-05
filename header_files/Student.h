#ifndef STUDENT_H
#define STUDENT_H
#include <vector>
#include <string>
#include <Class.h>

// Member functions and variable definitions in this file
class Student{
    public:

    private:
    std::string name;
    std::vector<Class*> classes; //list of classes the student is enrolled in
    std:: vector <std::string> grades;
};
#endif