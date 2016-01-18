using namespace std;
#include <cstddef>//used to allow the use of NULL.
#include <iostream>

struct spaceship//creates a spaceship object with the following parameters.
{
	int x_position;
	int y_position;
	int power;
	spaceship* next_spaceship;//a pointer to the next spaceship in the list. Think of it as a hook on a train. you might not need it, but it is there if you need to hook(create) another carrage.
};
spaceship* first = NULL;// this is the list where we will store out list of ships. a "one stop point" for doing things with our list.

spaceship* new_spaceship()
{
	spaceship* ship = new spaceship;//creates an instane of the spaceship struct that we will be the return value.
	ship->x_position = 0;//the "->" allows you to acces the feilds of a structure through a pointer.
	ship->y_position = 0;
	ship->power = 20;
	ship->next_spaceship = first;//makes this ship points to previous ship/first element in the list.
	first = ship;//makes the current ship the first object in the list.
	return ship;//returns a newly created spaceship structure.
}

void upgrade_power(spaceship* ship)//takes in the pointer of a spaceship object location and adds to its power variable.
{
	ship->power += 10;
}

void display_ship(spaceship &ship)
{
	cout << "\npower: " << ship.power;
	cout << "\nx_position: " << ship.x_position;
	cout << "\ny_position" << ship.y_position;
}

int main()
{
	spaceship* my_ship = new_spaceship();//creates a pointer of a new spaceship object.
	upgrade_power(my_ship);//upgrades the power of this ship.

	display_ship(*my_ship);

	system("pause");
}