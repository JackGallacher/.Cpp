using namespace std;
#include <iostream>
#include <string>

//1 - Write a program that lets the user fill in a single structure with the name, address and phone number of a single person.

//struct spaceship//defines a spaceship struct. 
//{
//	int x_position;
//	int y_position;
//	int power;
//};
//spaceship create()//applies default variables to a spaceship object.
//{
//	spaceship ship;
//	ship.power = 5;
//	ship.x_position = 12;
//	ship.y_position = 17;
//	return ship;
//}
//spaceship upgrade(spaceship ship)//alters and existing spaceship variable.
//{
//	ship.power += 10;
//	return ship;
//}

struct notebook
{
	string name;
	string address;
	string phone_number;
};

int main()
{
	//spaceship myship;
	//myship = create();
	//myship = upgrade(myship);
	//cout << myship.power;

	notebook mynotebook;

	cout << "enter name: ";
	getline(cin, mynotebook.name);
	
	cout << "enter address: ";
	getline(cin, mynotebook.address);

	cout << "enter phone number: ";
	cin >> mynotebook.phone_number;

	cout << "\nname: " << mynotebook.name;
	cout << "\naddress: " << mynotebook.address;
	cout << "\nphone number: " << mynotebook.phone_number << "\n";

	system("pause");

}
