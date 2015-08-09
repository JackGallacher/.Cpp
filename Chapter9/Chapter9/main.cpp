using namespace std;
#include<iostream>
#include <string>

void convert(int input);
void number_conveter();
void prime_finder();
void checkprime(int number);

int main()
{
	int choice = 0;
	cout << "1: int to string number converter.\n2: primes from 1 to 1000\n";
	cin >> choice;

	switch (choice)
	{
	case 1:
		number_conveter();
		break;
	case 2:
		prime_finder();
		break;
	default:
		cout << "invalid input, try again.\n";
		main();
		break;
	}
	system("pause");
}
void prime_finder()
{
	int n;//current number to check for prime factors.
	int factortotal = 0;


	for (int x = 0; x <= 1000; x++)//loops for 1 to 1000;
	{
		int factortotal = 0;
		//cout << "the prime factor of " << x << " is: ";
		n = x;

		int i = 2;//starts from 2.
		while (i < n / 2)//while i is les than n divided by 2.
		{
			if (n%i == 0)//if n modulus i is zero.
			{
				n /= i;//n equals n divided by i.
				//cout << i << " ";//output value of i;
				factortotal = factortotal + i;
			}
			else //if n modulus i is not 2, increment i by 1 to check n against the next number.
			{
				i++;
			}
		}
		factortotal = factortotal + n;
		checkprime(factortotal);
		//cout << n << ". "<< "factor total = "<< factortotal;// output the value of n.			
	}
}
void checkprime(int number)
{
	int count = 0;
	for (int i = 1; i <= number; i++)
	{
		if (number % i == 0)
		{
			count++;
		}
	}
	if (count == 2)//if this number is 2, it means that the count value has only been added to when the number has been divisible by 1 and again when i has reached out number.
	{
		cout << number << "\n";
	}
}










void number_conveter()
{
	int input = 0;

	cout << "enter a number between -999,999 and 999,999\n";
	cin >> input;
	convert(input);
	cout << "\n";
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


