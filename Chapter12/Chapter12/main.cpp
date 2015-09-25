using namespace std;
#include<iostream>
#include<string>

/*1 - Write a function that promts the user to enter thier first and last name as two seperate values. The function should return both values to the caller via additional pointer (or reference)
parameters that are passed to the function. Do this with pointers and refereenes.*/
/*2 - Write a finction that takes two arguments and provide two seperate answers to the caller, one that is the results of multiplying the two arguments and one the addition.
As you can only return one value directly, you'll new the second value to be returned thrugh a pointer.*/
/*3 - Write a program that compared the memory address of two different viarable and prints out the order of the variables by numerical order of thier addresses.*/

void pointer_name(string* firstname, string* secondname)
{
	cout << "\npointer name: " << *firstname << " " << *secondname;
}
void reference_name(string& firstname, string& secondname)
{
	cout << "\nreference name: " << firstname << " " << secondname << "\n";
}
int double_return(int x, int y, int *z)
{
	*z = x * y;
	return x + y;
}
void swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

int main()
{
	int x = 0;//sets int to 0;
	int* pointer = &x;//make a pointer at the memory position of x
	*pointer = 25;//sets the memory location of x to 25.
	cout << pointer<< "\n";//outputs the memory position of x;
	cout << *pointer << "\n";//output the dereferenced value in the memory position of x.

	string first_name, second_name;

	cout << "enter first name: ";
	cin >> first_name;

	cout << "\nenter second name: ";
	cin >> second_name;

	if (&second_name == NULL)
	{
		cout << "please input a last name";
	}

	pointer_name(&first_name, &second_name);
	reference_name(first_name, second_name);

	int x = 5;
	int y = 10;
	int z = 0;

	cout << "pass by value return is: " << double_return(x, y, &z) << "\n";
	cout << "pass by pointer, allowing a second return value is: " << z << "\n";

	int one = 1;
	int two = 2;

	int* ptr_one = &one;
	int* ptr_two = &two;
	
	if (ptr_two > ptr_one)
	{
		cout << "vale of one: " << ptr_one << "\n";
		cout << "vale of two: " << ptr_two << "\n";

		cout << "two is largest\n";
	}
	if (ptr_one > ptr_two)
	{
		cout << "vale of one: " << ptr_one << "\n";
		cout << "vale of two: " << ptr_two << "\n";

		cout << "one is largest\n";
	}

	int value_1 = 0;
	int value_2 = 77;

	cout << "input first value: ";
	cin >> value_1;

	cout << "input second value: ";
	cin >> value_2;

	cout << "before swap value 1 is " << value_1 << "and vlaue two is " << value_2;
	swap(value_1, value_2);
	cout << "\nafter swap value 1 is " << value_1 << "and vlaue two is " << value_2;

	system("pause");
}

