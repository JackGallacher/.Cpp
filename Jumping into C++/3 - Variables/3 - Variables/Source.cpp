using namespace std;
#include <iostream>;

//1 - Write a program that outputs your name.
//2 - Write a program that reads in then adds two numbers.
//3 - Write a program that reads in then divides two numbers.

int main()
{
	//1
	cout << "Jack";

	//2
	double x = 0;
	double y = 0;

	cout << "input number 1: ";
	cin >> x;
	cout << "input number 2: ";
	cin >> y;
	cout << "input 1 + input 2 = " << x + y << "\n";//adds x and y.

													//3
	double i = 0;
	double j = 0;

	cout << "input number 1: ";
	cin >> i;
	cout << "input number 2: ";
	cin >> j;
	cout << "input 1 / input 2 = " << i / j << "\n";//divides i and j.

	system("pause");
}