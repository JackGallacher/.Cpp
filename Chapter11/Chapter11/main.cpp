using namespace std;
#include <iostream>
#include <string>
#include <time.h>//allows random.
#include <vector>
//#include <cstdlib>




//1 - Write a program that lets the user fill in a single structure with the name, address and phone number of a single person.
//2 - Create and array of spaceship objects and wrtie a program that continually updates thier positions until they all go off screen. Assume that the size of the screen is 1024 x 760 pixels.
// 3 - Create and address bok program that builds on task 1. This time, the user should not just be able to fill a single stucture, but should be able to add new entries. Add the abilty to browse
//the list of entries.


struct spaceship//defines a spaceship struct. 
{
	int x_position;
	int y_position;
	string name;
};
spaceship create()//applies default variables to a spaceship object.
{
	spaceship ship;
	ship.x_position = 0;
	ship.y_position = 0;
return ship;
}
spaceship update(spaceship ship)
{
	if (ship.x_position <= 1024)
	{
		ship.x_position += rand() % 5;//random number between 0 and 5.
	}
	if (ship.x_position <= 768)
	{
		ship.y_position += rand() % 5;//random number between 0 and 5.
	}
	else
	{
		//cout << "position is out of screen!";
	}
	return ship;
}
struct notebook//notebook strcut for storing data of an individual, adapted to accomodate task 3.
{
	string name;
	string address;
	string phone_number;
};
void notebook_program()//adepred to accomidate task 3.
{
	vector <notebook> mynotebook;//creates an ajustable vector of type "notebook"
	notebook person;//creates a new instance of a notebook struct
	int input = 0;//used to record the users input
	int vector_position = 0;//used to record the current vecotor position.

	do
	{
		cout << "press 1 to add a name to the notebook\npress 2 to view all enteries in the notebook\npress 3 to select whitch entry to view.";
		cin >> input;

		switch (input)
		{
		case 1:
			mynotebook.push_back(notebook());
			cin.ignore();
			cout << "enter name: ";
			getline(cin, mynotebook[vector_position].name);
			cout << "enter address: ";
			getline(cin, mynotebook[vector_position].address);
			cout << "enter phone number: ";
			cin >> mynotebook[vector_position].phone_number;
			vector_position++;
			break;
		case 2:
			for (int i = 0; i < mynotebook.size(); i++)
			{
				cout << mynotebook[i].name << "\n";
				cout << mynotebook[i].address << "\n";
				cout << mynotebook[i].phone_number << "\n";
			}
			break;
		case 3:
			cout << "input number between 0 and " << mynotebook.size() << "\n";
			cin >> input;

			cout << mynotebook[input].name << "\n";
			cout << mynotebook[input].address << "\n";
			cout << mynotebook[input].phone_number << "\n";
			break;
		}
	} while (1);
}
void spaceship_program()
{
	spaceship myship[5];
	for (int i = 0; i < 5; i++)//init each spaceship in the array.
	{
		myship[i] = create();
		myship[i].name = "spaceship " + to_string(i);
		//cout << myship[i].name + " position is: " + to_string(myship[i].x_position) + ", " + to_string(myship[i].y_position) + "\n";
	}
	int i = 0;
	while (i < 100)
	{

		for (int i = 0; i < 5; i++)//imit each spaceship in the array.
		{
			myship[0] = update(myship[0]);
			myship[1] = update(myship[1]);
			myship[2] = update(myship[2]);
			myship[3] = update(myship[3]);
			myship[4] = update(myship[4]);
			cout << myship[i].name + " position is: " + to_string(myship[i].x_position) + ", " + to_string(myship[i].y_position) + "\n";
		}
		i++;
	}
	cout << "all ships have gone off screen!\n";
}
struct highscore
{
	string player;
	vector <string> score;
	//string score;
};
void highscore_program()
{
	int input = 0;
	int vector_position = 0;

	vector <vector <highscore>> database;
	vector <highscore> players;

	string new_score;

	int score_position = 0;

	do 
	{
		cout << "Press 1 to add new user and score\n";
		cout << "Press 2 to add new score to a user\n";
		cout << "Press 3 to display high scores\n";
		cout << "Press 4 to display the list of players\n";
		cout << "Press 5 to search for a player and view thier scores\n";
		cin >> input;

		switch (input)
		{
		case 1:
			players.push_back(highscore());
			database.push_back(players);

			cin.ignore();
			cout << "enter name: ";
			getline(cin, players[vector_position].player);
			cout << "enter score: ";
			getline(cin, players[vector_position].score[0]);

			vector_position++;
			score_position++;
			break;
		case 2:
			cout << "input number between 0 and " << database.size() << " to add a new score to\n";
			cin >> input;

			cout << "enter new score for player" << input << "\n";
			cin >> new_score;

			players[input].score[players[input].score.size() + 1] = new_score;

			//players.scorepush_back(score);
			break;
		case 5:
			cout << "input number between 0 and " << database.size() << "\n";
			cin >> input;
			cout << players[input].player << "\n";

			for (int i = 0; i <= players.size(); i++)
			{
				cout << players[input].score[i] << "\n";
			}
			break;
		}
	} while (1);
}
int main()
{
	srand(time(NULL));//seeds random number.

	int option = 0;
	cout << "enter option\n1: notebook\n2: spaceship\n3: highscores";
	cin >> option;

	switch (option)
	{
	case 1:
		notebook_program();
		break;
	case 2:
		spaceship_program();
		break;
	case 3:
		highscore_program();
		break;
	default:
		cout << "wrong input, try again";
		main();
		break;
	}







	system("pause");
}
