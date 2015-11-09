#include <iostream>
#include "myanimal.h"
using namespace std;


int main(int argc, char **argv)
{
	MyAnimal *pAnimal = NULL;
	string animalName;

	AnimalFactory *sc1;
	sc1 = AnimalFactory::getSingletonAnimalFactory();
	cout << "type the name of an animal (e.g. cat, dog, spider):" << endl;
	cin >> animalName;

	pAnimal = sc1->CreateAnimal(animalName);
	pAnimal->Speak();
	cout << "\n" << pAnimal->GetNumberOfLegs() << "\n";

	system("pause");

	if (pAnimal)
	{
		delete pAnimal;
		return 1;
	}

}