#include <iostream>
#include <random>
#include <ctime>
#define DEBUG 0
using namespace std;

class door
{
public:
	bool isCar;
};

class doors
{
public:
	int door_count;
	door *door_array;
	doors(int door_count);
	void reinitialization();
	bool test_door(int i);
	int car_index();
	void display_doors();
	int other_door(int attempts);
	int this_door(int attempts);
};
doors::doors(int door_count)
{
	door_array = new door[door_count];

	for (int i = 0; i < door_count; i++)
	{
		door_array[i].isCar = false;
	}

	int index = rand() % door_count;
	door_array[index].isCar = true;

	this->door_count = door_count;
}

void doors::reinitialization()
{
	delete[] door_array;
	door_array = new door[door_count];

	for (int i = 0; i < door_count; i++)
	{
		door_array[i].isCar = false;
	}

	int index = rand() % door_count;
	door_array[index].isCar = true;

}

bool doors::test_door(int i)
{
	if (door_array[i].isCar) return true;
	return false;
}

int doors::car_index()
{
	for (int i = 0; i < door_count; i++)
		if (test_door(i)) return i;
	return -1;
}

void doors::display_doors()
{
	for (int i = 0; i < door_count; i++)
	{
		cout << (door_array[i].isCar == true ? " + " : " - ");
	}
	cout << endl;
}

// You choose a door, you pick the other ... the most succesful way !
int doors::other_door(int attempts)
{
	int picked;
	int other;
	int wins = 0;

	for (int i = 0; i < attempts; i++)
	{
		picked = rand() % door_count;
#if DEBUG == 1
		cout << "You picked : " << picked << endl;
		display_doors();
#endif
		int car = car_index();
		if (picked == car)
		{
#if DEBUG == 1
			cout << "You Lost ..." << endl << endl << endl;
#endif
			reinitialization();
			continue;
		}
#if DEBUG == 1
		cout << "You won !" << endl << endl << endl;
#endif
		wins++;
		reinitialization();
	}
	return wins;
}

// You choose what you picked in the first place !
int doors::this_door(int attempts)
{
	int picked;
	int other;
	int wins = 0;

	for (int i = 0; i < attempts; i++)
	{
		picked = rand() % door_count;
#if DEBUG == 1
		cout << "You picked : " << picked << endl;
		display_doors();
#endif
		int car = car_index();
		if (picked != car)
		{
#if DEBUG == 1
			cout << "You Lost ..." << endl << endl << endl;
#endif
			reinitialization();
			continue;
		}
#if DEBUG == 1
		cout << "You won !" << endl << endl << endl;
#endif
		wins++;
		reinitialization();
	}
	return wins;
}

int main()
{
	int door_count = 1000; // How many doors you wish ?
	srand(unsigned(time(NULL)));
	doors comp(door_count); // Creating the competition, well good luck ! (You're gonna have it with the 'other_door' function, shhhh)

	// Vars
	int attempts;
	int wins;
	float percentage;

	attempts = 1000000;
	wins = comp.other_door(attempts);
	percentage = wins * 100.0 / attempts;
	cout << "Other Door :" << endl;
	cout << "Wins are " << wins << " Out of " << attempts << " Attempts" << endl;
	cout << "Percentage is " << percentage << "%" << endl << endl;

	cout << "This Door :" << endl;
	wins = comp.this_door(attempts);
	percentage = wins * 100.0 / attempts;
	cout << "Wins are " << wins << " Out of " << attempts << " Attempts" << endl;
	cout << "Percentage is " << percentage << "%" << endl << endl;

	system("pause");
	return 0;
}