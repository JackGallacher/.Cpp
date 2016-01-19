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
//spaceship* fleet = NULL;// this is the list where we will store out list of ships. a "one stop point" for doing things with our list. the ROOT node.

spaceship* new_spaceship(spaceship* fleet)//instead of declaring the head of the list as global, we can just pass it into the function.
{
	spaceship* ship = new spaceship;//creates an instane of the spaceship struct that we will be the return value.
	ship->x_position = 0;//the "->" allows you to acces the feilds of a structure through a pointer.
	ship->y_position = 0;
	ship->power = 20;
	ship->next_spaceship = fleet;//makes this ship points to previous ship/first element in the list.
	//fleet = ship;//makes the current ship the first object in the list, we dont need this when passing the head of the list directly into the function.
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
	cout << "\ny_position" << ship.y_position + "\n";
}

int main()
{	
	//spaceship* my_ship = new_spaceship();//creates a pointer of a new spaceship object.
	spaceship* my_ship = NULL;//to do it without a global, a new enemy is created as null.
	spaceship* my_ship2 = NULL;

	my_ship = new_spaceship(my_ship);//it is then passed into the list and made the end point of the list until a new object is added.
	my_ship2 = new_spaceship(my_ship2);

	upgrade_power(my_ship);//upgrades the power of ship 1.

	display_ship(*my_ship);
	display_ship(*my_ship2);

	system("pause");
}