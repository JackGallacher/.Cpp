using namespace std;
#include <iostream>
#include <string>
#include <array>

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
	cout << "Positions set so far: " << slots_taken << endl;
	cout << "Values in array: " << endl;
	for (int i = 0; i < slots_taken; i++)
	{
		cout << "values[" << i << "] = " << values[i] << endl;
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

	for (int i = 0; i <= 3; i++)
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
}

void multiplication_table(int size_x, int size_y)
{
	int **table;

	table = new int*[size_x];
	for (int i = 0; i < size_x; i++)
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
void memory_location(int size_x, int size_y)
{
	int **table;

	table = new int*[size_x];
	for (int i = 0; i < size_x; i++)
	{
		table[i] = new int[size_y];
	}
	for (int x = 0; x < size_x; x++)
	{
		for (int y = 0; y < size_y; y++)
		{
			cout << "Memory location of array[" << x << "][" << y << "] is: " << &table[x][y] << "\n";
		}
	}
	delete[] table;
}

struct Person//the array needs to have multiple data types per person, so a struct will fulfill this need.
{
	string name = "";
	int days = 0;
};
Person* resize_array(Person* array_data, int* array_size)
{
	*array_size *= 2;//doubles the array size.
	Person* resized_array = new Person[*array_size];//creates a new Person array of the new size.

	for (int i = 0; i < *array_size; i++)
	{
		resized_array[i] = array_data[i];//copies data to new array
	}
	return resized_array;
	delete[] array_data;
}
void print_array(Person* friend_array, int array_position)
{
	for (int i = 0; i < array_position; i++)//print array.
	{
		cout << "array position [" << i << "] = Name: " << friend_array[i].name << ",  Days: " << friend_array[i].days << "\n";
	}
	delete[] friend_array;//free memory.
}
void sort_array(Person* friend_array, int array_position)//shell sort to arange names and values in decending order.
{
	int temp;
	string temp_name;

	int flag = 1;
	int numLength = sizeof(friend_array);
	int d = numLength;

	while (flag || (d > 1))
	{
		flag = 0;
		d = (d + 1) / 2;
		for (int i = 0; i < numLength - d; i++)
		{
			if (friend_array[i + d].days > friend_array[i].days)
			{
				temp = friend_array[i + d].days;
				temp_name = friend_array[i + d].name;

				friend_array[i + d].days = friend_array[i].days;
				friend_array[i + d].name = friend_array[i].name;

				friend_array[i].days = temp;
				friend_array[i].name = temp_name;
				flag = 1;
			}
		}
	}
	print_array(friend_array, array_position);
	delete[] friend_array;//free memory.
}
void friends_list()
{
	int array_size = 5;//init array size.
	int array_position = 0;//defailt array position.

	Person* friend_array;//defines pointer of struct type.
	friend_array = new Person[array_size];

	string name;
	int friend_position = 0;
	int days = 0;

	while (true)
	{
		int input = 0;
		cout << "1 - Add Friend\n2 - Update Friend\n3 - Display friends.\n4 - Sort array\n\n";
		cin >> input;

		switch (input)
		{
		case 1:
			if (array_position == array_size + 1)
			{
				cout << "array limit nearly reached, resizing array.";
				friend_array = resize_array(friend_array, &array_size);
				cout << "new array size is: " << sizeof(friend_array);
			}
			cout << "input friend name: ";
			cin >> friend_array[array_position].name;

			cout << "input days since you saw them: ";
			cin >> friend_array[array_position].days;
			cout << "\n";

			array_position++;//increment array position.
			break;
		case 2: 
			cout << "input friend name: ";
			cin >> name;

			for (int i = 0; i < array_size; i++)
			{
				if (friend_array[i].name == name)//finds the correct array member based on its name.
				{
					friend_position = i;
				}
			}

			cout << "input new days ";
			cin >> friend_array[friend_position].days;
			cout << "days updated.";
			break;
		case 3:
			print_array(friend_array, array_position);
			break;
		case 4:
			sort_array(friend_array, array_position);
			break;
		}
	}
	delete[] friend_array;
}
int main()
{
	//multiplication_table(25, 22);
	//three_multiplication_table(2, 4, 5);
	//memory_location(2, 3);
	friends_list();
	system("pause");
}