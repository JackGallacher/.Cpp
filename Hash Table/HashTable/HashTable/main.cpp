using namespace std;
#include <iostream>
#include <string>
#include "hash.h" 
#include"node.h" 
#include"student.h"

int main()
{
	Hashtable list;//creates table called list.

	Node* Joe;
	Node* Kim;

	Joe = new Node("Joe", 200, 100);//data for hash.
	Kim = new Node("Kim", 150, 60);//data for hash.

	list.put(Joe);//adds to table
	list.put(Kim);//adds to table

	list.Display(Kim);//display.
	list.Display(Joe);//display.
	system("pause");
}
