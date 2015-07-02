using namespace std;
#include <iostream>
#include <string>
#include <vector>

//1 - rewrite the meny program using switch case.
//2 - write a program the write the lyrics of "12 days of christmas" using switch case
//3 - write a two player tic-tak-toe game allowing two hums to play, using enums to reprsent values on the board.

void twelvedays()
{
	for (int i = 1; i < 13; i++)
	{
		cout << "on the ";
		switch (i)
		{
		case 1:
			cout << "first day";
			break;
		case 2:
			cout << "second day";
			break;
		case 3:
			cout << "third day";
			break;
		case 4:
			cout << "fourth day";
			break;
		case 5:
			cout << "fifth day";
			break;
		case 6:
			cout << "sixth day";
			break;
		case 7:
			cout << "seventh day";
			break;
		case 8:
			cout << "eighth day";
			break;
		case 9:
			cout << "ninth day";
			break;
		case 10:
			cout << "tenth day";
			break;
		case 11:
			cout << "eleventh day";
			break;
		case 12:
			cout << "twelfth day";
			break;
		default:
			break;
		}
		cout << " of christmas, my true love gave to me...\n";

		switch (i)
		{
		case 12:
			cout << "twelve drummers drumming\n";
		case 11:
			cout << "eleven pipers piping\n";
		case 10:
			cout << "ten lords leaping\n";
		case 9:
			cout << "nine lords dancing\n";
		case 8:
			cout << "eight maids milking\n";
		case 7:
			cout << "seven swans swimming\n";
		case 6:
			cout << "six geese laying\n";
		case 5:
			cout << "five gold rings\n";
		case 4:
			cout << "four calling birds\n";
		case 3:
			cout << "three french hens\n";
		case 2:
			cout << "two turtle doves\n";
		case 1:
			cout << "a partridge in a pair tree\n\n";
		}
	}
}

int P1_choice;
int P2_choice;
bool run = true;
bool P1_win = false;
bool P2_win = false;
enum value { CROSS = 'X', CIRCLE = 'O', BLANK = '-' };
vector <char> board = { BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK};

void printboard()
{
	for (int i = 0; i < board.size(); i++)
	{
		cout << board[i];
		if (i == 2)
		{
			cout << "\n";
		}
		if (i == 5)
		{
			cout << "\n";
		}
		if (i == 8)
		{
			cout << "\n";
		}
	}
}
void checkwin()
{
	for (int i = 0; i < 3; i++)
	{
		if (board[i] == CROSS && board[i + 3] == CROSS && board[i + 6] == CROSS)//down
		{
			P1_win = true;
		}
		if (board[i] == CIRCLE && board[i + 3] == CIRCLE && board[i + 6] == CIRCLE)//down
		{
			P2_win = true;
		}
	}
	for (int j = 0; j < 7; j++)
	{
		if (board[j] == CROSS && board[j + 1] == CROSS && board[j + 2] == CROSS)//across
		{
			P1_win = true;
		}
		if (board[j] == CIRCLE && board[j + 1] == CIRCLE && board[j + 2] == CIRCLE)//across
		{
			P2_win = true;
		}
	}
	for (int k = 0; k < 1; k++)
	{
		if (board[k] == CROSS && board[k + 4] == CROSS && board[k + 8] == CROSS)//diagonal
		{
			P1_win = true;
		}
		if (board[k + 2] == CROSS && board[k + 4] == CROSS && board[k + 6] == CROSS)//diagonal
		{
			P1_win = true;
		}

		if (board[k] == CIRCLE && board[k + 4] == CIRCLE && board[k + 8] == CIRCLE)//diagonal
		{
			P2_win = true;
		}
		if (board[k + 2] == CIRCLE && board[k + 4] == CIRCLE && board[k + 6] == CIRCLE)//diagonal
		{
			P2_win = true;
		}
	}

	if (P1_win == true)
	{
		cout << "\nplayer 1 has won\n";
	}
	if (P2_win == true)
	{
		cout << "\nplayer 2 has won\n";
	}	
}
void tictaktoe()
{
	bool P1_turn = true;
	bool P2_turn = false;

	cout << "welcome to tick tac toe, each space on the grid is represented by numbers 1 to 9";
	cout << "top left is 1, 2 is top middle and so on.\n";

	while (run)
	{
		if (P1_turn == true)
		{
			cout << "player one enter co-ordinate (1 to 9)\n";
			cin >> P1_choice;
			while (cin.fail())//error handle.
			{
				cin.clear();
				cin.ignore();
				cout << "player one enter co-ordinate (1 to 9)\n";
				cin >> P1_choice;
			}
			while (board[P1_choice - 1] == CIRCLE)
			{
				cin.clear();
				cin.ignore();
				cout << "slot taken, choose again\n";
				cin >> P1_choice;
			}
			if (board[P1_choice - 1] == BLANK)
			{
				board[P1_choice - 1] = CROSS;
			}
			printboard();//displays game board.
			checkwin();//checks to see if play has won with that move.
			if (P1_win == true)
			{
				break;
			}
			P1_turn = false;
			P2_turn = true;
		}
		if (P2_turn == true)
		{
			cout << "player two enter co-ordinate (1 to 9)\n";
			cin >> P2_choice;
			while (cin.fail())//error handle.
			{
				cin.clear();
				cin.ignore();
				cout << "player two enter co-ordinate (1 to 9)\n";
				cin >> P2_choice;
			}
			while (board[P2_choice - 1] == CROSS)
			{
				cin.clear();
				cin.ignore();
				cout << "slot taken, choose again\n";
				cin >> P2_choice;
			}
			if (board[P2_choice - 1] == BLANK)
			{
				board[P2_choice - 1] = CIRCLE;
			}
			printboard();//displays game board.
			checkwin();//checks to see if play has won with that move.
			if (P2_win == true)
			{
				break;
			}
			P2_turn = false;
			P1_turn = true;
		}
	}

}

void menu()
{
	int user_input;

	cout << "choose an option\n";
	cout << "- 1: twelve days of christmas\n";
	cout << "- 2: tick tack toe\n";
	cin >> user_input;
	
	switch (user_input)
	{
	case 1:
		twelvedays();
		break;
	case 2: 
		tictaktoe();
		break;
	default:
		cout << "wrong input selected, try again\n";
		menu();
		break;
	}
}

int main()
{	
	menu();
	system("pause");
}