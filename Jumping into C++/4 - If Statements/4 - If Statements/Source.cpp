using namespace std;
#include <iostream>
#include <string>

int main()
{
	int x = 0, y = 0;

	cout << "enter age 1: ";
	cin >> x;
	cout << "enter age 2: ";
	cin >> y;

	if (x > y)
	{
		cout << "age 1 is greater than age 2 \n\n";
	}
	else if (x < y)
	{
		cout << "age 2 is greater than age 1 \n\n";
	}
	else if (x == y)
	{
		cout << "ages are the same \n\n";
	}

	string user1 = "jack",
			user2 = "ben",
			user3 = "ryan";

	string user1_pw = "gallacher",
			user2_pw = "moulton",
			user3_pw = "pearson";

	string username, password;

	cout << "enter username: ";
	cin >> username;
	cout << "enter password: ";
	cin >> password;

	if (username == user1 && password == user1_pw)
	{
		cout << "welcome jack\n";
	}
	else if (username == user2 && password == user2_pw)
	{
		cout << "welcome ben\n";
	}
	else if (username == user3 && password == user3_pw)
	{
		cout << "welcome ryan\n";
	}
	else
	{
		cout << "user name or password incorrect, try again.";
		main();//comment out other tasks to restart login.
	}

	char function;
	double i = 0, j = 0;

	cout << "enter equation: ";
	cin >> i >> function >> j;

	if (function == '+')
	{
		cout << i << "+" << j << "=" << i + j << "\n";
	}
	else if (function == '*')
	{
		cout << i << "*" << j << "=" << i * j << "\n";
	}
	else if (function == '/')
	{
		cout << i << "/" << j << "=" << i / j << "\n";
	}
	else if (function == '-')
	{
		cout << i << "-" << j << "=" << i - j << "\n";
	}
	else
	{
		cout << "incorrect function used.\n";
	}
	system("pause");
}