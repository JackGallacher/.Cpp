#ifndef STUDENT_H
#define STUDENT_H
using namespace std;
#include <iostream>
#include <string>

class StudentKey//contains sutdent data.
{
public:
	StudentKey(int h, int w) 	{ height = h; weight = w; }

	int height;
	int weight;
};
class Student//contains student name.
{
public:
	Student(string n) { name = n; }
	string name;
};

#endif STUDENT_H