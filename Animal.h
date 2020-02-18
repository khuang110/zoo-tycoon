#pragma once
#include <iostream>
#include <string>

using namespace std;

class Animal
{
public:
	Animal();
	~Animal();
	void set_baby();		// make animal a baby
	void set_to_child();	// just change is_baby
	bool get_baby();
	void set_sick(bool);
	bool get_sick();
	void increment_age();
	int get_age();
	void set_reproduce();

protected:
	int age;
	int count;			// number of animals
	int cost;
	bool is_sick;
	bool is_baby;
	int num_babies;		//num of babies it makes
	int food_cost_mult;		// food cost multiplier
	bool can_reproduce;
};


