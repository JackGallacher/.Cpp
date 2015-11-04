using namespace std;
#include <iostream>
#include<cstdlib>
#include<ctime>
#include<array>
#include<algorithm>
#include <string>

void insertion_sort(int array[], int size)//insertion sort function.
{
	int index = 0;
	int i = 0;
	int j = 0;

	for (i = 1; i < size; i++)// increment i if it is less than the array size.
	{
		index = array[i];//index is equal to the array location of i;
		for (j = i - 1; (j >= 0) && (array[j] < index); j--)// for j is equal to i - 1, j is greater than zero and the array position of j is less than index, decrease the value of j;
		{
			array[j + 1] = array[j];// array position j + 1 is equal to the array position of j;
		}
		array[j + 1] = index;//array position of j + 1 is equal to the index value.
	}
}
void display(int array[], int size)//function to display the chosen array.
{
	int highest = 0;
	int lowest = 0;
	int average = 0;

	for (int i = 0; i < size; i++)
	{
		if (array[i] > highest)
		{
			highest = array[i];
		}
		average += array[i];
	}
	cout << "highest is: " << highest << "\n";
	cout << "average is:" << average / size << "\n";
	for (int i = 0; i < size; i++)
	{
		cout << array[i] << "\n";
	}
}
bool issorted(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i - 1] > array[i])
		{
			return false;
		}
	}
	return true;
}
void array_program()
{
	srand(time(NULL));

	int myarray[50];
	for (int i = 0; i <= 49; i++)
	{
		myarray[i] = rand();
	}
	if (!issorted(myarray, 50))
	{
		cout << "array is not sorterd, sorting...\n";
		insertion_sort(myarray, 50);
		display(myarray, 50);
	}
	else
	{
		cout << "array is sorted, printing...\n";
		display(myarray, 50);
	}
}
int main()
{
	int input = 0;
	cout << "1: array program\n";
	cin >> input;
	switch (input)
	{
	case 1:
		array_program();
		break;
	default:
		cout << "incorrect input submitted, try again.";
		main();
		break;
	};
	system("pause");
}