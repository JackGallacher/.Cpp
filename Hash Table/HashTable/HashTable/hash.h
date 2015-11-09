#ifndef HASH_H
#define HASH_H
using namespace std;
#include <iostream>
#include <string>
#include "node.h"

#define DEFAULT_TABLESIZE 11
class Hashtable
{
private:
	int table_size;
	Node** table;
public:
	Hashtable(int T = DEFAULT_TABLESIZE);
	long hashFunction(StudentKey *MyStudentKey);
	void put(Node*);
	void Hashtable::Display(Node* N);
};
long Hashtable::hashFunction(StudentKey *MyStudentKey)
{
	long temp = MyStudentKey->height % MyStudentKey->weight;
	return temp;
};
void Hashtable::put(Node *N)
{
	int index = hashFunction(N->MyStudentKey);
	//if bucket pointer is null, set bucket to point at our node
	//else
	//make our node point where the bucket presently points
	//and then the bucket point at our node.
	if (table[index] = NULL)
	{
		table[index] = N;
	}
	else
	{
		N->next = table[index];
		table[index] = N;
	}
};
Hashtable::Hashtable(int T)
{
	//set table size
	table_size = T;
	//construct node* array of length T -using new
	table = new Node*[table_size];
};
void Hashtable::Display(Node* N)
{
	cout << N->MyStudent->name << ": ";
	cout << "Height: " << N->MyStudentKey->height << ",";
	cout << " Weight: " << N->MyStudentKey->weight << endl;
}
#endif