#include "Zoo.h"
#include <thread>	// thread
#include <chrono>	// seconds / sleep
#include <time.h>	// time
#include <cstdlib>	// srand

Zoo::Zoo()
{
	balance = 100000;
	month = 0;
	n_sealion = 0;
	n_bear = 0;
	n_tiger = 0;
	tiger_food_cost = 80;
	bear_food_cost = 80;
	sealion_food_cost = 80;
	sealion_head = nullptr;
	tiger_head = nullptr;
	blackbear_head = nullptr;
}


Zoo::~Zoo()
{
	Sealion *next;

	while (sealion_head != nullptr)
	{
		next = sealion_head->next;
		delete sealion_head;
		sealion_head = next;
	}
	sealion_head = nullptr;
	
	Blackbear *b_next;

	while (blackbear_head != nullptr)
	{
		b_next = blackbear_head->next;
		delete blackbear_head;
		blackbear_head = b_next;
	}

	blackbear_head = nullptr;

	Tiger *t_next;

	while (tiger_head != nullptr)
	{
		t_next = tiger_head->next;
		delete tiger_head;
		tiger_head = t_next;
	}

	tiger_head = nullptr;
}

void Zoo::increment_month()
{
	month++;
	Sealion *s = sealion_head;
	Tiger *t = tiger_head;
	Blackbear *b = blackbear_head;

	while (s != nullptr)
	{
		s->increment_age();
		s = s->next;
	}
	while (t != nullptr)
	{
		t->increment_age();
		t = t->next;
	}
	while (b != nullptr)
	{
		b->increment_age();
		b = b->next;
	}
}

void Zoo::convert_to_adult()
{
	Sealion *s = sealion_head;
	Tiger *t = tiger_head;
	Blackbear *b = blackbear_head;

	while (s != nullptr)
	{
		if (s->get_age() == 6)		// make it a kid animal
		{
			s->set_to_child();
		}
		else if (s->get_age() == 37)		// make so it is fully adult
		{
			s->set_reproduce();		
		}
		s = s->next;
	}
	while (t != nullptr)
	{
		if (t->get_age() == 6)
		{
			t->set_to_child();
		}
		else if (t->get_age() == 37)
		{
			t->set_reproduce();
		}
		t = t->next;
	}
	while (b != nullptr)
	{
		if (b->get_age() == 6)
		{
			b->set_to_child();
		}
		else if (b->get_age() == 37)
		{
			b->set_reproduce();
		}
		b = b->next;
	}
}

void Zoo::sealion_food()
{
	srand(time(NULL));
	float percent = 0.01 * (80 + (rand() % (120 - 80 + 1)));

	sealion_food_cost *= percent;
	cout << "Base sealion food cost: $" << sealion_food_cost << endl;
}

void Zoo::bear_food()
{
	float percent = 0.01 * (80 + (rand() % (120 - 80 + 1)));

	bear_food_cost *= percent;
	cout << "Base black bear food cost: $" << bear_food_cost << endl;
}

void Zoo::tiger_food()
{
	float percent = 0.01 * (80 + (rand() % (120 - 80 + 1)));

	tiger_food_cost *= percent;
	cout << "Base tiger food cost: $" << tiger_food_cost << endl;
}

int Zoo::select_food()
{
	int buffer;
	cout << "-------------------------------------------------------------------------\nSelect a food\n";
	sealion_food();
	bear_food();
	tiger_food();
	cout << "Select a food to feed the animals\n";
	cout << "1 - cheap food: twice as likely to get sick. cost half as much as regular\n";
	cout << "2 - regular food: regular probability animal will get sick\n";
	cout << "3 - premium food: half as likely to get sick. cost twice as much\n";
	cin >> buffer;
	switch (buffer)
	{
	case 1:
		balance -= (((float)n_sealion * (sealion_food_cost / 2)) + ((float)n_tiger * (tiger_food_cost / 2)) + ((float)n_bear * (bear_food_cost / 2)));
		clear_screen();
		return 1;
	case 2:
		balance -= (((float)n_sealion * (sealion_food_cost)) + ((float)n_tiger * (tiger_food_cost)) + ((float)n_bear * (bear_food_cost)));
		clear_screen();
		return 2;
	case 3:
		balance -= (((float)n_sealion * (sealion_food_cost * 2)) + ((float)n_tiger * (tiger_food_cost * 2)) + ((float)n_bear * (bear_food_cost * 2)));
		clear_screen();
		return 4;
	}
}

int Zoo::sealion_rand_revenue(bool high_attendance)
{
	srand(time(NULL));
	int extra_revenue;
	if (high_attendance)
	{
		extra_revenue = 150 + (rand() % (400 - 150 + 1));
	}
	else
	{
		extra_revenue = 0;
	}
	return extra_revenue + 140;
}


int Zoo::calculate_revenue(bool high_attendance)		// take all the animals and calculate their revenue
{
	float revenue = 0;
	Sealion *s = sealion_head;
	Tiger *t = tiger_head;
	Blackbear *b = blackbear_head;

	while (s != nullptr)
	{
		if (s->get_baby())
		{
			revenue += (2 * sealion_rand_revenue(high_attendance));
		}
		else
		{
			revenue += sealion_rand_revenue(high_attendance);
		}
		s = s->next;
	}
	while (t != nullptr)
	{
		if (t->get_baby())
		{
			revenue += 2400;
		}
		else 
		{
			revenue += 1200;
		}
		t = t->next;
	}
	while (b != nullptr)
	{
		if (b->get_baby())
		{
			revenue += 1000;
		}
		else
		{
			revenue += 500;
		}
		b = b->next;
	}
	balance += revenue;
	return revenue;
}

void Zoo::main_menu()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	cout << " _____            _____                     " << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	cout << "|__   |___ ___   |_   _|_ _ ___ ___ ___ ___ " << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	cout << "|   __| . | . |    | | | | |  _| . | . |   |" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	cout << "|_____|___|___|    |_| |_  |___|___|___|_|_|" << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	cout << "                       |___|                " << endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	clear_screen();
}

void Zoo::menu()
{
	bool flag = true;
	while (balance >= 0)
	{
		if (flag)
		{
			cout << "Welcome to Zoo Tycoon!\n";
			cout << "You have $100,000 to start.\n";
			flag = false;
		}
		if (animal_selection())
		{
			return;
		}
		clear_screen();
		bool high_attenance = special_event(select_food());
		print_zoo(calculate_revenue(high_attenance));
		increment_month();
	}
}

void Zoo::clear_screen()
{
	for (int i = 0; i < 50; i++)
		cout << endl;
}

bool Zoo::animal_selection()
{
	int buffer, count;
	while (true)
	{
		cout << "Press 0 to buy Sealions\n";
		cout << "Press 1 to buy Black bears\n";
		cout << "Press 2 to buy Tigers\n";
		cout << "Press 3 to not buy an animal\n";
		cout << "Press 4 to quit game\n";
		cin >> buffer;
		if (this->month == 0 && buffer == 3)
		{
			cout << "You must purchase an animal to start\n";
			continue;
		}
		switch (buffer)
		{
		case 0:
			cout << "How many Sealions do you want to buy? (Max 2)\n";
			cin >> count;
			switch (count)
			{
			case 1:
				insert_sealion();		// non-baby by default
				return false;
				break;
			case 2:
				insert_sealion();
				insert_sealion();
				return false;
				break;
			default:
				cout << "Select one or two.\n";
			}
			break;
		case 1:
			cout << "How many Black bears do you want to buy? (Max 2)\n";
			cin >> count;
			switch (count)
			{
			case 1:
				insert_bear();
				return false;
				break;
			case 2:
				insert_bear();
				insert_bear();
				return false;
				break;
			default:
				cout << "Select one or two.\n";
			}
			break;
		case 2:
			cout << "How many Tigers do you want to buy? (Max 2)\n";
			cin >> count;
			switch (count)
			{
			case 1:
				insert_tiger();
				return false;
				break;
			case 2:
				insert_tiger();
				insert_tiger();
				return false;
				break;
			default:
				cout << "Select one or two.\n";
			}
			break;
		case 3:
			return false;
			break;
		case 4:
			return true;
		default:
			cout << "Make a number selection 0-4...\n";
		}
	}
}

void Zoo::insert_sealion(bool is_baby)
{
	Sealion *temp = new Sealion;
	Sealion *current = sealion_head;
	temp->next = nullptr;

	if (is_baby == true)
	{
		temp->set_baby();
	}
	else
	{
		balance -= 700;
	}
	if (n_sealion == 0)
	{
		sealion_head = temp;
		temp = nullptr;	
	}
	else {
		while (current->next != nullptr)
		{
			current = current->next;
		}

		current->next = temp;
	}
	n_sealion++;
}

void Zoo::insert_bear(bool is_baby)
{
	Blackbear *temp = new Blackbear;
	Blackbear *current = blackbear_head;
	temp->next = nullptr;

	if (is_baby == true)
	{
		temp->set_baby();
	}
	else
	{
		balance -= 5000;
	}
	if (n_bear == 0)
	{
		blackbear_head = temp;
		temp = nullptr;
	}
	else {
		while (current->next != nullptr)
		{
			current = current->next;
		}

		current->next = temp;
	}
	n_bear++;
}

void Zoo::insert_tiger(bool is_baby)
{
	Tiger *temp = new Tiger;
	Tiger *current = tiger_head;
	temp->next = nullptr;

	if (is_baby == true)
	{
		temp->set_baby();
	}
	else
	{
		balance -= 12000;
	}
	if (n_tiger == 0)
	{
		tiger_head = temp;
		temp = nullptr;
	}
	else {
		while (current->next != nullptr)
		{
			current = current->next;
		}

		current->next = temp;
	}
	n_tiger++;
}

void Zoo::remove_sealion(int index)
{

	Sealion *temp = sealion_head;
	Sealion *prev = sealion_head;

	if (temp != nullptr && index == 0)
	{
		sealion_head = temp->next;
		delete temp;
		n_sealion--;
		return;
	}

	int i = 0;
	while (temp != nullptr && i++ != index)
	{
		prev = temp;
		temp = temp->next;
	}
	prev->next = temp->next;
	delete temp;
	temp = nullptr;
	n_sealion--;
}

void Zoo::remove_bear(int index)
{

	Blackbear *temp = blackbear_head;
	Blackbear *prev = blackbear_head;

	if (temp != nullptr && index == 0)
	{
		blackbear_head = temp->next;
		delete temp;
		n_bear--;
		return;
	}

	int i = 0;
	while (temp != nullptr && i++ != index)
	{
		prev = temp;
		temp = temp->next;
	}
	prev->next = temp->next;
	delete temp;
	temp = nullptr;
	n_bear--;
}

void Zoo::remove_tiger(int index)
{

	Tiger *temp = tiger_head;
	Tiger *prev = tiger_head;

	if (temp != nullptr && index == 0)
	{
		tiger_head = temp->next;
		delete temp;
		n_tiger--;
		return;
	}

	int i = 0;
	while (temp != nullptr && i++ != index)
	{
		prev = temp;
		temp = temp->next;
	}
	prev->next = temp->next;
	delete temp;
	temp = nullptr;
	n_tiger--;
}

void Zoo::print_zoo(int revenue)
{
	cout << "Your zoo currently has:\n";
	cout << "Balance: $" << this->balance << endl;
	cout << "Sealions: " << this->n_sealion << endl;
	cout << "Black Bears: " << this->n_bear << endl;
	cout << "Tiger: " << this->n_tiger << endl;
	cout << "Last month the zoo made: $" << revenue << endl;
}

bool Zoo::check_balance(int price)
{
	int temp = balance;
	if (temp - price >= 0)
	{
		return true;
	}
	return false;
}

bool Zoo::special_event(int sick_prob)
{
	srand(time(NULL));
	int s_event = rand() % 4;
	
	switch (s_event)
	{
	case 0:	// animal sick
		if (sick_prob == 1)
		{
			select_sick();
		}
		else if (sick_prob == 2)
		{
			s_event = rand() % 2;
			if (s_event == 0)
			{
				select_sick();
			}
		}
		else
		{
			s_event = rand() % 4;
			if (s_event == 0)
			{
				select_sick();
			}
		}
		break;
	case 1:		// rando animal makes baby
		make_baby();
		break;
	case 2:		// boom in zoo attendance... sealion prints
		cout << "There was a boom in attendance!\n";
		return true;
		break;
	case 3:	// no event
		break;
	}
	return false;
}

void Zoo::select_sick()
{
	srand(time(NULL)); 
	while (true)
	{
		int r_an = rand() % 3;
		switch (r_an)
		{
		case 0:	// sealion
		{
			Sealion *s = sealion_head;
			while (s != nullptr)
			{
				if (!(s->get_sick()))
				{
					cout << "A sealion got sick!" << endl;
					s->set_sick(true);
					cure_sick(0);
					return;
				}
				s = s->next;
			}
			break;
		}
		case 1:	// bear
		{
			Blackbear *b = blackbear_head;
			while (b != nullptr)
			{
				if (!(b->get_sick()))
				{
					cout << "A Black bear got sick!" << endl;
					b->set_sick(true);
					cure_sick(1);
					return;
				}
				b = b->next;
			}
			break;
		}
		case 2:	// lion
		{
			Tiger *t = tiger_head;
			while (t != nullptr)
			{
				if (!(t->get_sick()))
				{
					cout << "A Tiger got sick!" << endl;
					t->set_sick(true);
					cure_sick(2);
					return;
				}
				t = t->next;
			}
			break;
		}
		}
	}
}

void Zoo::make_baby()
{
	bool b_flag = false, t_flag = false, s_flag = false;
	srand(time(NULL));
	while (true)
	{
		int r_an = rand() % 3;
		switch (r_an)
		{
		case 0:	// sealion
			if (n_sealion >= 2)
			{
				cout << "A Sealion had a baby!" << endl;
				insert_sealion(true);
				return;
			}
			else
			{
				s_flag = true;
			}
			break;
		case 1:	// bear
			if (n_bear >= 2)
			{
				cout << "A Black bear had 2 babies!" << endl;
				insert_bear(true);
				insert_bear(true);
				return;
			}
			else
			{
				b_flag = true;
			}
			break;
		case 2:	// lion
			if (n_tiger >= 2)
			{
				cout << "A Tiger had 3 babies!" << endl;
				insert_tiger(true);
				insert_tiger(true);
				insert_tiger(true);
				return;
			}
			else
			{
				t_flag = true;
			}
			break;
		}
		if (t_flag && s_flag && b_flag) {
			return;
		}
	}
}

void Zoo::cure_sick(int animal_type)
{
	int index;
	switch (animal_type)
	{
	case 0:	// sealion
	{
		Sealion *s = sealion_head;
		index = 0;
		while (s != nullptr)
		{
			if (s->get_sick() && ((balance - 350) >= 0))
			{
				cout << "A sealion was cured!" << endl;
				balance -= 350;
				s->set_sick(false);
				return;
			}
			else if (s->get_sick() && ((balance - 350) < 0))
			{
				cout << "You couldn't afford to cure the sick sealion and it died!\n";
				cout << "F\n";
				remove_sealion(index);
				return;
			}
			s = s->next;
			index++;
		}
		break;
	}
	case 1:	// bear
	{
		index = 0;
		Blackbear *b = blackbear_head;
		while (b != nullptr)
		{
			if (b->get_sick() && ((balance - 2500) >= 0))
			{
				cout << "A sick Black bear was cured!" << endl;
				b->set_sick(false);
				balance -= 2500;
				return;
			}
			else if (b->get_sick() && ((balance - 2500) < 0))
			{
				cout << "You couldn't afford to cure the sick black bear and it died!\n";
				cout << "F\n";
				remove_bear(index);
				return;
			}
			b = b->next;
			index++;
		}
		break;
	}
	case 2:	// lion
	{
		index = 0;
		Tiger *t = tiger_head;
		while (t != nullptr)
		{
			if (t->get_sick() && ((balance - 6000) >= 0))
			{
				balance -= 6000;
				cout << "A sick tiger was cured!" << endl;
				t->set_sick(false);
				return;
			}
			else if (t->get_sick() && ((balance - 6000) < 0))
			{
				cout << "You can't afford to fix the sick tiger and it died!\n";
				cout << "F\n";
				remove_tiger(index);
				return;
			}
			index++;
			t = t->next;
		}
		break;
	}
	}
}
