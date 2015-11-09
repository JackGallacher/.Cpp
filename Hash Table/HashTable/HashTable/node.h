#ifndef NODE_H
#define NODE_H
using namespace std;
#include <iostream>
#include <string>
#include "student.h"

class Node
{
public:
	StudentKey *MyStudentKey;
	Student *MyStudent;
	Node *next; //used for linkedlist.

	Node(string name, int height, int weight)
	{
		//add code here.
		MyStudentKey = new StudentKey(height, weight);
		MyStudent = new Student(name);
		next = NULL;
	}
};
#endif