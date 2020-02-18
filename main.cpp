#include "Zoo.h"

int main()
{
	bool flag = false;
	while (!flag)
	{
		Zoo z;
		z.main_menu();
		z.menu();
		cout << "Do you want to play again?\n";
		cout << "0- - yes\n1 - no\n";
		cin >> flag;

	}

	return 0;
}