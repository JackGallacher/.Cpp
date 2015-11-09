using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define ARR_SIZE 15

void quicksort(vector <int> &list, int left, int right);
void insertionsort(vector <int> &list);
void merge(vector<int> &list, int p, int r);
void merge_sort(vector<int> &list, int p, int r);
void swapdata(int &number1, int &number2);
void display(vector<int> &list);
void print(vector<int> &vt);

vector<int> list{ -22, 10, 43, 23, -78, 45, 100, 123, 56, 98, 41, 90, 24, 96, 86, -30 };
int main()
{
	//quicksort(list, 0, list.size() - 1);
	//insertionsort(list);
	//merge_sort(list, 0, list.size() - 1);
	display(list);

	system("pause");
}
void quicksort(vector <int> &list, int left, int right)
{
	int pivot;
	int leftArrow = left;
	int rightArrow = right;

	pivot = list[(left + right) / 2];
	do
	{
		while (list[rightArrow] < pivot)
		{
			--rightArrow;
		}
		while (list[leftArrow] > pivot)
		{
			++leftArrow;
		}
		if (leftArrow <= rightArrow)
		{
			swapdata(list[leftArrow], list[rightArrow]);
			++leftArrow;
			--rightArrow;
		}
	} while (rightArrow >= leftArrow);
	if (left < rightArrow)
	{
		quicksort(list, left, rightArrow);
	}
	if (leftArrow < right)
	{
		quicksort(list, leftArrow, right);
	}
}
void insertionsort(vector <int> &list)
{
	int i;
	int j;
	int key;
	int listLength = list.size();

	for (j = 1; j < listLength; j++)
	{
		key = list[j];
		for (i = j - 1; (i >= 0) && (list[i] < key); i--)
		{
			list[i + 1] = list[i];
		}
		list[i + 1] = key;
	}
}
void merge(vector<int> &list, int p, int r)
{
	int mid = floor((p + r) / 2);
	int i1 = 0;
	int i2 = p;
	int i3 = mid + 1;

	vector<int> temp_list;
	temp_list.resize(r - p + 1);

	while (i2 <= mid && i3 <= r)
	{
		if (list[i2] < list[i3])
		{
			temp_list[i1++] = list[i2++];
		}
		else
		{
			temp_list[i1++] = list[i3++];
		}
	}
	while (i2 <= mid)
	{
		temp_list[i1++] = list[i2++];
	}
	while (i3 <= r)
	{
		temp_list[i1++] = list[i3++];
	}
	for (int i = p; i <= r; i++)
	{
		list[i] = temp_list[i - p];
	}

}
void merge_sort(vector<int> &list, int p, int r)
{
	if (p<r)
	{
		int mid = floor((p + r) / 2);
		merge_sort(list, p, mid);
		merge_sort(list, mid + 1, r);
		merge(list, p, r);
	}
}
void swapdata(int &number1, int &number2)
{
	int temp;

	temp = number1;
	number1 = number2;
	number2 = temp;
}
void display(vector<int> &list)
{
	for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << " ";
	}
}
