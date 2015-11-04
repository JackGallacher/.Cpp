using namespace std;
#include <iostream>
#include <string>

//1 - output the song "99 bottles of beer".
//2 - write a menu that allows users to select from a list of options.
//3 - write a program that computes a running sum of inputs, terminating when 0 is pressed.
//4 - write a password promt that allows only a certain amount of attempts.
//5 - write a program that displays the first 20 prime numbers.
/*6 - write a program that provides the option of tallying up the results of a poll with 3 possible values. the first input is the question followed by the possible answers. when zero is pressed
the results are tallied and shown in a bar graph*/


int main()
{
	//1
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

	//2
	string input;
	do
	{
		cout << "choose an option\n";
		cout << "- 1\n";
		cout << "- 2\n";
		cout << "- 3\n";

		cin >> input;

	} while (input != "1" && input != "2" && input != "3");

	if (input == "1")
	{
		cout << "you chose option 1\n";
	}
	else if (input == "2")
	{
		cout << "you chose option 2\n";
	}
	else if (input == "3")
	{
		cout << "you chose option 3\n";
	}

	//3
	int current_number = 0;
	int previous_number = 0;

	while (1)
	{
		cout << "enter number: ";
		cin >> current_number;
		if (current_number == 0)
		{
			break;
		}
		cout << "total so far = " << current_number + previous_number << "\n";
		previous_number = current_number + previous_number;
	}

	//4
	int attempts = 5;
	string password = "password";
	string user_attempt;

	while (user_attempt != "password" && attempts > 0)
	{
		cout << "please enter password: ";
		cin >> user_attempt;

		if (user_attempt != password)
		{
			attempts--;
			cout << "\nincorrect password, please try again\n";
			cout << "attempts remaining: " << attempts << "\n\n";

			if (attempts == 0)
			{
				cout << "you have run of attempts";
			}
		}

		if (user_attempt == password)
		{
			cout << "password is correct\n";
		}
	}

	//5
	for (int i = 1; i < 21; i++)
	{
		cout << i * i << "\n";
	}

	//6
	string question;
	string answer_one;
	string answer_two;
	string answer_three;

	int select_one = 0;
	int select_two = 0;
	int select_three = 0;

	int user_answer = 0;

	cout << "enter question: ";
	getline(cin, question);

	cout << "enter answer 1: ";
	getline(cin, answer_one);

	cout << "enter answer 2: ";
	getline(cin, answer_two);

	cout << "enter answer 3: ";
	getline(cin, answer_three);

	while (true)
	{
		cout << "\n" << question << "\n";
		cout << "1- " << answer_one << "\n";
		cout << "2- " << answer_two << "\n";
		cout << "3- " << answer_three << "\n";
		cout << "please input your answer: 1, 2, or 3\n";
		cout << "press 0 to display results\n";

		cin >> user_answer;

		if (user_answer == 1)
		{
			cout << "you chose answer 1\n";
			select_one++;
		}
		if (user_answer == 2)
		{
			cout << "you chose answer 2\n";
			select_two++;
		}
		if (user_answer == 3)
		{
			cout << "you chose answer 3\n";
			select_three++;
		}
		if (user_answer == 0)
		{
			cout << "\n";
			cout << "results\n";
			cout << "answer 1: ";
			for (int i = 0; i < select_one; i++)
			{
				cout << "#";
			}
			cout << "\n";
			cout << "answer 2: ";
			for (int i = 0; i < select_two; i++)
			{
				cout << "#";
			}
			cout << "\n";
			cout << "answer 3: ";
			for (int i = 0; i < select_three; i++)
			{
				cout << "#";
			}
			cout << "\n";
			break;
		}
	}

	system("pause");
}