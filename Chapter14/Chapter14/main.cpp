using namespace std;
#include <iostream>
#include <string>

//dynamic memory allocation example. Creates array of pointers with szie 10, when the array reaches 10 elements, the size is doubled and so on.
int* extend_array(int* values, int* size)
{
	*size *= 2;//doubles the size of the array.
	int *new_values = new int[*size];//creates the new array of double size.
	for (int i = 0; i < *size; i++)
	{
		new_values[i] = values[i];//copies the old array to the new array.
	}
	delete[] values;//deletes used pointers.
	return new_values;
}
void print_array(int* values, int size, int slots_taken)
{
	cout << "Array size is: " << size << endl;
	cout << "Positions set so far: " << slots_taken <<endl;
	cout << "Values in array: " << endl;
	for (int i = 0; i < slots_taken; i++)
	{
		cout << "values[" << i << "] = " << values[i] <<endl;
	}
}
void dynamic_array()
{
	int input = 0;
	int next_element = 0;
	int size = 10;
	int* values = new int[size];//array of pointers.

	cout << "Please input a value: ";
	cin >> input;

	while (input > 0)
	{
		if (size == next_element + 1)
		{
			values = extend_array(values, &size);
		}
		values[next_element] = input;
		next_element++;

		cout << "Current array values are: " << endl;
		print_array(values, size, next_element);
		cout << "Please enter a number: ";
		cin >> input;
	}
	delete[] values;
}

//pointer arithmetic example.
void pointer_arithmetic()
{
	int x[3];
	x[0] = 1;
	x[1] = 2;
	x[2] = 3;£
	*(x + 3) = 120;//pointer arithmetic to assign 120 to x[3].

	for (int i = 0; i <= 3; i ++)
	{
		cout << x[i] << "\n";
	}
}

void pointer_array()
{
	int **my_array;//double pointer.
	my_array = new int*[3];//creates an array of pointers with 3 locations, pointer to a pointer.

	for (int i = 0; i < 3; i++)
	{
		my_array[i] = new int[3];//make each pointer location store an address of an array of 3 elements.
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			my_array[i][j] = 0;//initliases each position in thois two dimentional array with the value of 0.
		}
	}
	for (int i = 0; i < 3; i++)//delete each memory location of the array of pointers.
	{
		delete[] my_array[i];
	}
	delete[] my_array;//lastly, delete the pointer.
	//this could all be done with int my_array[3][3]; !!
}

int main()
{


	system("pause");
}