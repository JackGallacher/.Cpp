using namespace std;
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

//1 - write a program that simulates a coinflip.
//2 - write a program that picks a number between 0 and 100 and lets the user guess the number, the programs says "too high" "too low" or "just right" based on the closeness of the guess.
//3 - write a program that solves the guessing game.
//4 - make a "slot machine" that randomly displays the results of the machine to the player, have three or more values for each wheel and print out winnings if the values match.
//5 - write a program to play poker, give 5 cards to the player, let the player choose new cards and determine how good the hand is. keep track of the cards that heve been drawn, and dont allow them to be drawn again.


void menu();//prototype of menu.

//generates random number based on time.
int getrandom(int low, int high)
{
	return rand() % (high - low + 1) + low;// exmple: <high = 100, low = 0> (100 - 0 + 1) + 0 = 101: this then gives a 0 to 100 range.
}
//simulates a coin flip, if number is above 50 but below 100 it is tails, below 50 and above zero it is heads.
void coin_flip()
{
	int rand_value = getrandom(0, 100);
	if (rand_value < 50)
	{
		cout << "coin is heads\n";
		cout << rand_value << "\n";//outputs the random value
		menu();
	}
	if (rand_value > 50)
	{
		cout << "coin is tails\n";
		cout << rand_value << "\n";//outputs the random value
		menu();
	}
}
//guessing game.
void guess_number()
{
	int rand_value = getrandom(1,100);
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
	int rand_value = getrandom(1,100);
	int guess = 0;

	while (guess != rand_value)
	{
		cout << "pick a number between 1 and 100\n";
		guess = getrandom(1,100);// just picks a random number between 1 and 100 automtically, without having the user input
		cout << guess << "\n";

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
void slots()
{
	bool winner = false;//if a winner is found.
	char spin;//input to spin machine.
	int numbers[3];//array to store each generated number.

	while (winner == false)
	{
		cout << "press 1 to spin the slot machine.\n";
		cin >> spin;

		if (spin == '1')
		{
			numbers[0] = getrandom(1, 3);//random number between 1 and 3.
			numbers[1] = getrandom(1, 3);
			numbers[2] = getrandom(1, 3);

			cout << numbers[0] << numbers[1] << numbers[2] << "\n";
			if (numbers[0] == numbers[1] && numbers[0] == numbers[2])//output if all three numbers are the same
			{
				winner = true;
			}
			cout << "----------\n";
		}
		else
		{
			cout << "incorrect input, please spin again.\n";
		}
	}

	if (winner == true)//produces output based upon the numbers that are the same.
	{
		if (numbers[0] == 1 && numbers[1] == 1 && numbers[2] == 1)
		{
			cout << "all the 1`s matched\n";
			menu();
		}
		if (numbers[0] == 2 && numbers[1] == 2 && numbers[2] == 2)
		{
			cout << "all the 2's matched\n";
			menu();
		}
		if (numbers[0] == 3 && numbers[1] == 3 && numbers[2] == 3)
		{
			cout << "all the 3's matched\n";
			menu();
		}
	}
}
void gethand()
{
	string hand[6]; //array for storing hand.
	vector<string> deck;//ajustable vector for the card deck.

	string names[13] = { "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
	string house[4] = { "Clubs", "Spades", "Hearts", "Diamonds" };

	int i = 0;//array position.
	for (int j = 0; j < 13; j++)//names slot
	{
		for (int k = 0; k < 4; k++)//house slot
		{
			deck.push_back(names[j] + " of " + house[k]); //= names[j] + " of " + house[k];
			//cout << deck[i] << "\n";
			i++;
		}
	}
	cout << "your hand is: \n";
	for (int i = 0; i < 5; i ++)//outputs the players hand, each card is based upon a random number between 1 and 52.
	{
		int card_position = getrandom(1, 52);//gets the numerical value of the current card.
		string selectedcard = deck[card_position];

		hand[i] = selectedcard;
		cout << hand[i] << "\n";


		//cout << selectedcard << "\n";
		deck.erase(deck.begin() + card_position--);//removes the current card from the vector.
		cout << "\n";
	}
	for (int i = 0; i < deck.size(); i++)//prints the current deck of cards, for testing purposes.
	{
		cout <<deck[i] << "\n";
	}
}
void poker()
{
	cout << "welcome to poker\n";
	gethand();
}
//switch selection of tasks.
void menu()
{
	int user_input;

	cout << "press 1 to coin flip\n";
	cout << "press 2 to play the guessing game\n";
	cout << "press 3 to automatically solve the guessing game\n";
	cout << "press 4 to play slots\n";
	cout << "press 5 to play poker\n";
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
	case 4:
		slots();
		break;
	case 5:
		poker();
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