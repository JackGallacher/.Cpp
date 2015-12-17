using namespace std;
#include <cstddef>
#include <iostream>

struct spaceship//creates a spaceship object with the following parameters.
{
	int x_position;
	int y_position;
	int power;
	spaceship* next_spaceship;//a pointer to the next spaceship in the list. Think of it as a hook on a train. you might not need it, but it is there if you need to hook(create) another carrage.
};

spaceship* new_spaceship()
{
	spaceship* ship = new spaceship;//creates an instane of the spaceship struct that we will be the return value.
	ship->x_position = 0;//the "->" allows you to acces the feilds of a structure through a pointer.
	ship->y_position = 0;
	ship->power = 20;
	ship->next_spaceship = NULL;//as we are creating a new spaceship based on this function being called, this is set to NULL.
	return ship;//returns a newly created spaceship structure.
}

void upgrade_power(spaceship* ship)//takes in the pointer of a spaceship object location and adds to its power variable.
{
	ship->power += 10;
}

int main()
{
	spaceship* my_ship = new_spaceship();//creates a pointer of a new spaceship object.
	upgrade_power(my_ship);//upgrades the power of this ship.

	system("pause");
}