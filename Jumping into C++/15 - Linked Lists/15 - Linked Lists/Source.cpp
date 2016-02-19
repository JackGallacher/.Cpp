using namespace std;
#include <cstddef>//used to allow the use of NULL.
#include <iostream>
#include <string>

class spaceship//creates a spaceship object with the following parameters.
{
public: 

	//class functions.
	spaceship* add_spaceship(spaceship* ship_list, string ship_name);
	spaceship* remove_spaceship(spaceship* ship_list, string ship_name);
	void upgrade_power(spaceship* ship_list);
	void upgrade_single_ship(spaceship* ship_list, string ship_name);
	void display_linkedlist(spaceship* ship_list);
	void display_ship(spaceship* ship_list, string ship_name);

private:

	//node data sets, private as they only need to be used in each instance of this class.
	string name;
	int x_position;
	int y_position;
	int power;
	spaceship* next_spaceship;//a pointer to the next spaceship in the list. Think of it as a hook on a train. you might not need it, but it is there if you need to hook(create) another carrage.
};
//declarations of class functions
spaceship* spaceship::add_spaceship(spaceship* ship_list, string ship_name)
{
	spaceship* ship = new spaceship();//creates a new instance of a spaceship that we are going to add to our linked list.
	ship->name = ship_name;
	ship->x_position = 0;
	ship->y_position = 0;
	ship->power = 20;
	ship->next_spaceship = ship_list;//assigns the next_sapceship variable to the previous element in the list, "linking" them.
	return ship;
}
void spaceship::upgrade_power(spaceship* ship_list)//takes in the pointer of a spaceship object location and adds to its power variable.
{
	spaceship* current_ship = ship_list;
	while (current_ship != NULL)
	{
		current_ship->power += 10;
		current_ship = current_ship->next_spaceship;
	}
}
void spaceship::upgrade_single_ship(spaceship* ship_list, string ship_name)
{
	spaceship* current_ship = ship_list;
	while (current_ship != NULL)
	{
		if (current_ship ->name == ship_name)//searches for the element in the linked list that contains the name passed to this function.
		{
			current_ship->power += 10;
		}
	}
}
void spaceship::display_linkedlist(spaceship* ship_list)
{
	spaceship* current_ship = ship_list;
	while (current_ship != NULL)
	{
		cout << "ship name: "<< current_ship->name << "\n";
		cout << "ship power: " << current_ship->power << "\n";
		if(current_ship->next_spaceship != NULL)
		{
			cout << "next node: " << current_ship->next_spaceship->name << "\n\n";
		}
		else
		{
			cout << "next node: NULL\n";
		}		
		current_ship = current_ship->next_spaceship;
	}
}
void spaceship::display_ship(spaceship* ship_list, string ship_name)
{
	spaceship* current_ship = ship_list;
	while (current_ship != NULL)
	{
		if (current_ship -> name == ship_name)
		{
			cout << "\npower: " << current_ship->power;
			cout << "\nx_position: " << current_ship->x_position;
			cout << "\ny_position " << current_ship->y_position << "\n";
		}
		current_ship = current_ship->next_spaceship;
	}
} 
//spaceship* spaceship::remove_spaceship(spaceship* ship_list, string ship_name)
//{

//}
int main()
{	
	spaceship* ship_list = NULL;//declaration of a linked list.

	spaceship spaceship;//instance of our spaceship class, only need one no matter how many linkedc lists we make of the spaceship type.

	ship_list = spaceship.add_spaceship(ship_list, "ship 1");
	ship_list = spaceship.add_spaceship(ship_list, "ship 2");
	ship_list = spaceship.add_spaceship(ship_list, "ship 3");

	spaceship.display_linkedlist(ship_list);

	system("pause");
}