#pragma once
#include "Tiger.h"



class Zoo
{
public:
	Zoo();
	~Zoo();

	Sealion *sealion_head;
	Tiger *tiger_head;
	Blackbear *blackbear_head;
	void main_menu();
	void menu();
	
private:
	float balance;
	unsigned int month;
	int calculate_revenue(bool);
	void insert_sealion(bool is_baby = false);
	void insert_bear(bool is_baby = false);
	void insert_tiger(bool is_baby = false);
	void remove_sealion(int);
	void remove_tiger(int);
	void remove_bear(int);
	int sealion_rand_revenue(bool);
	bool animal_selection();
	void clear_screen();
	void print_zoo(int);
	bool check_balance(int);
	bool special_event(int);
	void select_sick();
	void cure_sick(int);
	void make_baby();
	void convert_to_adult();
	void sealion_food();
	void tiger_food();
	void bear_food();
	int select_food();

	void increment_month();
	int n_sealion;
	int n_bear;
	int n_tiger;
	float tiger_food_cost;
	float bear_food_cost;
	float sealion_food_cost;
};

