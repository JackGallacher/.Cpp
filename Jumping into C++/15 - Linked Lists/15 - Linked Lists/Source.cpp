using namespace std;
#include <cstddef>//used to allow the use of NULL.
#include <iostream>
#include <string>

struct spaceship//creates a spaceship object with the following parameters.
{
	string name;
	int x_position;
	int y_position;
	int power;
	spaceship* next_spaceship;//a pointer to the next spaceship in the list. Think of it as a hook on a train. you might not need it, but it is there if you need to hook(create) another carrage.
};
spaceship* add_spaceship(spaceship* ship_list, string ship_name)
{
	spaceship* ship = new spaceship();//creates a new instance of a spaceship that we are going to add to our linked list.
	ship->name = ship_name;
	ship->x_position = 0;
	ship->y_position = 0;
	ship->power = 20;
	ship->next_spaceship = ship_list;//assigns the next_sapceship variable to the previous element in the list, "linking" them.
	return ship;
}
void upgrade_power(spaceship* ship_list)//takes in the pointer of a spaceship object location and adds to its power variable.
{
	spaceship* current_ship = ship_list;
	while (current_ship != NULL)
	{
		current_ship->power + 10;
		current_ship = current_ship->next_spaceship;
	}

}

void display_linkedlist(spaceship* ship_list)
{
	spaceship* current_ship = ship_list;
	while (current_ship != NULL)
	{
		cout << "ship name: "<< current_ship->name << "\n";
		cout << "ship power: " << current_ship->power << "\n";
		current_ship = current_ship->next_spaceship;
	}
}
void display_ship(spaceship &ship)
{
	cout << "\npower: " << ship.power;
	cout << "\nx_position: " << ship.x_position;
	cout << "\ny_position " << ship.y_position << "\n";
}
int main()
{	
	spaceship* ship_list = NULL;//creates out list that we will add stuff to.
	ship_list = add_spaceship(ship_list, "ship 1");//here we specify the linked list we are adding to, plus passing in the name of the node we are adding.
	ship_list = add_spaceship(ship_list, "ship 2");
	ship_list = add_spaceship(ship_list, "ship 3");

	upgrade_power(ship_list);
	display_linkedlist(ship_list);

	system("pause");
}