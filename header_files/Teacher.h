#ifndef TEACHER_H
#define TEACHER_H
#include <string>
#include <vector>
#include <Class.h>

// Member functions and variable definitions in this file
class Teacher{
    public:
    Teacher(){} //constructor


    private:
       std:: vector <Class*> classes; //list of classes the teacher has
       std:: string name; 

};
#endif