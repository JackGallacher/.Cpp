using namespace std;
#include <iostream>
#include <string>
#include <array>

class Animal 
{
public:
	virtual void Diet() = 0;//Pure Virtual function that has to be overriden in child classes.
};

class Dog : public Animal
{
public:
	void Diet()
	{
		cout << "This is the Dogs diet, overridden from the Virtual Void in the parent class Animal.\n";
	}
};

void GetDiet(Animal* AnimalToGetDiet)//We can pass any child class from Animal into this function as it inherits from Animal.
{
	AnimalToGetDiet->Diet();
}

string ReverseString(string myString)
{
	string ReversedString = "";
	for (char &c : myString)
	{
		ReversedString = c + ReversedString;
	}
	return ReversedString;
}

void FindMatchingInArray(int ArrayOne[], int ArrayTwo[], int Size1, int Size2)
{
	string MatchingNumbers = "";

	for (int i = 0; i < Size1; i++)
	{
		for (int j = 0; j < Size2; j++)
		{
			if (ArrayOne[i] == ArrayTwo[j])
			{
				if (MatchingNumbers.find(to_string(ArrayOne[i])))
				{
					MatchingNumbers = to_string(ArrayOne[i]) + " " + MatchingNumbers;
				}
			}
		}
	}
	cout << "Common numbers in the two arrays are: " << MatchingNumbers + "\n";
}

int main()
{
	int Array1[6] = { 1, 2, 3, 4, 5, 7 };
	int Array2[5] = { 3, 2, 9, 3, 7 };
	FindMatchingInArray(Array1, Array2, sizeof(Array1)/sizeof(Array1[0]), sizeof(Array2)/sizeof(Array2[0]));

	//Dog* myDog = new Dog;
	//GetDiet(myDog);

	//string StringToReverse = "";

	//cout << "Please input a string that you would like to reverse:";
	//getline(cin, StringToReverse);

	//cout << ReverseString(StringToReverse) << "\n";

	system("pause");
}