using namespace std;
#include <iostream>
#include <string>

//1 - take the menu program your wrote earlier and call functions to the calculator and 99 bottles of beer.
//2 - make your calculator program perform calculations in seperate functions.
//3 - modify your password program to put all of the checking logic in a seperate function.

//prototype of password check function.
void checkpassword(string x);

//prints the 99 bottles of beer song.
void bottles()
{
	int bottles = 99;
	string word = "bottles";

	while (bottles > 0)
	{
		cout << bottles << " " << word << " of beer on the wall, " << bottles << " " << word << " of beer \n";
		cout << "take one down pass it around \n";
		bottles--;

		if (bottles == 1)
		{
			word = "bottle";
		}
		else
		{
			word = "bottles";
		}

		cout << bottles << " " << word << " of beer left on the wall \n";
		cout << "---------------------------------------------------------------------- \n";
	}
}

//maths functions for calculator.
double add(double x, double y)
{
	double answer = x + y;
	return answer;
}
double subtract(double x, double y)
{
	double answer = x - y;
	return answer;
}
double divide(double x, double y)
{
	double answer = x / y;
	return answer;
}
double multiply(double x, double y)
{
	double answer = x * y;
	return answer;
}

//basic calculator implementation.
void calculator()
{
	char function;
	double i;
	double j;

	cout << "enter equation: ";
	cin >> i >> function >> j;

	if (function == '+')
	{
		cout << i << "+" << j << "=" << add(i, j) << "\n";
	}
	else if (function == '*')
	{
		cout << i << "*" << j << "=" << multiply(i, j) << "\n";
	}
	else if (function == '/')
	{
		cout << i << "/" << j << "=" << divide(i, j) << "\n";
	}
	else if (function == '-')
	{
		cout << i << "-" << j << "=" << subtract(i, j) << "\n";
	}
	else
	{
		cout << "incorrect function used.\n";
	}
}

//applies cin to password check function.
void password()
{
	string user_attempt;

	cout << "please enter password";
	cin >> user_attempt;

	checkpassword(user_attempt);
}

//compares inputted string to cin.
void checkpassword(string x)
{
	int attempts = 5;
	string correct_password = "password";

	if (x != correct_password)
	{
		attempts--;
		cout << "\nincorrect password, please try again\n";
		cout << "attempts remaining: " << attempts << "\n\n";
		password();
		if (attempts == 0)
		{
			cout << "you have run of attempts\n";
		}
	}
	if (x == correct_password)
	{
		cout << "password is correct\n";
	}
}

//selection menu.
void menu()
{
	string input;
	do
	{
		cout << "choose an option\n";
		cout << "- 1: 99 bottles of beer \n";
		cout << "- 2: calculator\n";
		cout << "- 3: password\n";

		cin >> input;

	} while (input != "1" && input != "2" && input != "3");

	if (input == "1")
	{
		bottles();
		menu();
	}
	else if (input == "2")
	{
		calculator();
		menu();
	}
	else if (input == "3")
	{
		password();
		menu();
	}
}

//init.
int main()
{
	menu();
	system("pause");
}