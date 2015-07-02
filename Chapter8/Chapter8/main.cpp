using namespace std;
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

//1 - write a program that simulates a coinflip.
//2 - write a program that picks a number between 0 and 100 and lets the user guess the number, the programs says "too high" "too low" or "just right" based on the closeness of the guess.
//3 - write a program that solves the guessing game.
//4 - make a "slot machine" that randomly displays the results of the machine to the player, have three or more values for each wheel and print out winnings if the values match.
//5 - write a program to play poker, give 5 cards to the player, let the player choose new cards and determine how good the hand is.


void menu();//prototype of menu.

//generates random number based on time.
int getrandom()
{
	return rand();
}
//simulates a coin flip, if number is above 50 but below 100 it is tails, below 50 and above zero it is heads.
void coin_flip()
{
	int rand_value = getrandom() % (100 - 0) + 0;

	if (rand_value < 50)
	{
		cout << "coin is heads\n";
		//cout << rand_value << "\n";//outputs the random value
		menu();
	}
	if (rand_value > 50)
	{
		cout << "coin is tails\n";
		//cout << rand_value << "\n";//outputs the random value
		menu();
	}
}
//guessing game.
void guess_number()
{
	int rand_value = getrandom() % (100 - 1) + 0;
	int guess = 0;

	while (guess != rand_value)
	{
		cout << "pick a number between 1 and 100\n";
		cin >> guess;

		if (guess < rand_value)
		{
			cout << "too low\n";
		}
		if (guess > rand_value)
		{
			cout << "too high\n";
		}
		if (guess == rand_value)
		{
			cout << "just right\n";
		}
	}
}
//automates and solves the guessing game
void solve_game()
{
	int computer_guess = 0;
	guess_number();
}
//switch selection of tasks.
void menu()
{
	int user_input;

	cout << "press 1 to coin flip\n";
	cout << "press 2 to play the guessing game\n";
	cin >> user_input;

	switch (user_input)
	{
	case 1:
		coin_flip();
		break;
	case 2:
		guess_number();
		break;
	case 3:
		solve_game();
		break;
	default:
		cout << "you did not select a valid option, please try again \n";
		menu();
		break;
	}
}
//init.
int main()
{
	srand(time(NULL));//seeds the random value with time.
	menu();
	system("pause");
}