using namespace std;
#include <iostream>
#include <string>
#include <array>

/*1 - Write a fucntion that builds a two dimensional multiplication table with arbitrary sizes of the two dimensions.*/
/*2 - Write a function that takes three arguments, length width and height, dynamically allocated a three dimensional array with those values and fills the 
three dimensional array with multiplication tables.*/
/*3 - Write out a program that points out the memory addresses of each element in a two dimensiona array.*/






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
	x[2] = 3;
	*(x + 3) = 120;//pointer arithmetic to assign 120 to x[3].

	for (int i = 0; i <= 3; i ++)
	{
		cout << x[i] << "\n";
	}
}

void pointer_array()//complicated way to make a 2D array.
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
	//Unless you did need to make a resizable 2 demensional array!
}

void multiplication_table(int size_x, int size_y)
{
	int **table;

	table = new int*[size_x];
	for (int i = 0; i < size_x; i ++)
	{
		table[i] = new int[size_y];
	}
	for (int x = 0; x < size_x; x++)
	{
		for (int y = 0; y < size_y; y++)
		{						
			table[x][y] = x * y;
			cout << x << " * " << y << " = " << table[x][y] << "\n";
		}
	}
	delete[] table;
}
void three_multiplication_table(int size_x, int size_y, int size_z)
{
	int ***table;

	table = new int**[size_x];
	for (int i = 0; i < size_x; i++)
	{
		table[i] = new int*[size_y];
		for (int j = 0; j < size_y; j++)
		{
			table[i][j] = new int[size_z];
		}
	}
	for (int x = 0; x < size_x; x++)
	{
		for (int y = 0; y < size_y; y++)
		{
			for (int z = 0; z < size_z; z++)
			{
				table[x][y][z] = x * y * z;
				cout << x << " * " << y << " * " << z << " = " << table[x][y][z] << "\n";
			}
		}
	}
	delete[] table;
}

int main()
{
	multiplication_table(25, 22);
	three_multiplication_table(2, 4, 5);
	system("pause");
}