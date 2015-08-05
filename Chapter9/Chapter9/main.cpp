using namespace std;
#include<iostream>
#include <string>

void convert(int input);
int main()
{
	int input = 0;
	int first = 0;
	int second = 0;

	cout << "enter a number between -999,999 and 999,999\n";
	cin >> input;
	convert(input);
	cout << "\n";
	system("pause");
}
void convert(int input)
{
	string digits[20] = { "zero","one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
	string tens[10] = { " ","ten", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety" };

	if (input < 0)
	{
		cout << " minus ";
		convert(-input);//if number is negative, convert the negative value of it. turning it into a positive.
	}
	else if (input >= 1000)//1000 to 999999
	{
		convert(input / 1000);//run function on number /1000
		cout << " thousand ";
		if (input % 1000)
		{
			convert(input % 1000);
		}

	}
	else if (input >= 100)//100 to 999
	{
		cout << digits[input/100];
		cout << " hundred ";
		if (input % 100)
		{
			convert(input % 100);
		}
	}
	else if (input >= 20)// 20 to 99
	{
		cout << tens[input/10];
		convert(input % 10);
	}
	else if (input <= 19)//digits and teens.
	{
		cout << digits[input];
	}
}


