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

int main()
{
	int input = 0;
	int next_element = 0;
	int size = 10;
	int* values = new int[size];//array of pointers.

	cout << "Please input a value: ";
	cin >> input;

	while(input > 0)
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
	system("pause");
}