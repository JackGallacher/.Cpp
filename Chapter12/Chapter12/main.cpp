using namespace std;
#include<iostream>
#include<string>

int main()
{
	int x = 25;//sets int to 25;
	int* pointer = &x;//make a pointer at the memory position of x
	cout << pointer<< "\n";//outputs the memory position of x;
	cout << *pointer << "\n";//output the dereferenced value in the memory position of x.

	system("pause");
}
