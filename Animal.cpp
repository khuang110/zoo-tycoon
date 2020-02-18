#include "Animal.h"



Animal::Animal()
{
	is_baby = false;
	is_sick = false;
	cost = 0;
	age = 48;		// default age in months
	can_reproduce = true;
}


Animal::~Animal()
{
}

void Animal::increment_age()
{
	age++;
}

void Animal::set_baby()		// no parameter since true or false
{
	this->is_baby = true;
	this->can_reproduce = false;
	this->age = 0;
}

void Animal::set_to_child()
{
	this->is_baby = false;
}

bool Animal::get_baby()
{
	return is_baby;
}

bool Animal::get_sick()
{
	return is_sick;
}

void Animal::set_sick(bool condition)
{
	this->is_sick = condition;
}

int Animal::get_age()
{
	return age;
}

void Animal::set_reproduce() 
{
	this->can_reproduce = true;
}