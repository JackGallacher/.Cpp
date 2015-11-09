#include <iostream>
#include <string>

using namespace std;

class MyAnimal
{
public:
	virtual int GetNumberOfLegs() const = 0;
	virtual void Speak() = 0;

};
class Cat : public MyAnimal
{
public:
	void Speak()
	{
		cout << "meow";
	}
	int GetNumberOfLegs() const { return 4; }
};
class Dog : public MyAnimal
{
public:
	void Speak()
	{
		cout << "woof";
	}
	int GetNumberOfLegs() const { return 4; }

};
class Spider : public MyAnimal
{
public:
	void Speak()
	{
		cout << "skitter";
	}
	int GetNumberOfLegs() const { return 8; }

};
class AnimalFactory
{
private:
	AnimalFactory(){};//default constuctor
	AnimalFactory(const AnimalFactory&){};
	AnimalFactory &operator=(const AnimalFactory&) { return *this; }
	static AnimalFactory *pAnimalFactory;

public:
	MyAnimal* CreateAnimal(const string &animalName);
	static AnimalFactory *getSingletonAnimalFactory();
};
MyAnimal *AnimalFactory::CreateAnimal(const string &animalName)
{
	if (animalName == "cat")
	{
		return new Cat();
	}
	if (animalName == "dog")
	{
		return new Dog();
	}
	if (animalName == "spider")
	{
		return new Spider();
	}
	return 0;
}
AnimalFactory* AnimalFactory::getSingletonAnimalFactory()
{
	if (!pAnimalFactory)
	{
		pAnimalFactory = new AnimalFactory();
		return pAnimalFactory;
	}
}
AnimalFactory* AnimalFactory::pAnimalFactory = NULL;