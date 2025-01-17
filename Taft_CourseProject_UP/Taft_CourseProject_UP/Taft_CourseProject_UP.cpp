#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;
int const maxSize = 13;
int const minSize = 7;

int preset = 0;

char PreviousAttMove[] = { '0', '0', '0', '0' };//x1, y1, x2, y2
char PreviousDefMove[] = { '0', '0', '0', '0' };//x1, y1, x2, y2

void Clear()
{
	cout << "\x1B[2J\x1B[H";
}

bool InitializeBoard(bool check)
{
	Clear();
	if (preset % 2 == 1 && preset >= minSize && preset <= maxSize)
	{
		switch (preset)
		{
			case 7: setup7x7(); break;
			case 9: setup9x9(); break;
			case 11: setup11x11(); break;
			case 13: setup13x13(); break;
			default: setup11x11(); break;
		}
		check = true;
	}
	else
	{
		cout << "Invalid input! \n";
		cout << "Choose a setup (use the number in the brackets):" <<
			"\n7x7(7)" <<
			"\n9x9(9)" <<
			"\n9x9(9)" <<
			"\n11x11(11)" <<
			"\n13x13(13)" <<
			"\nEnter(use the number in the brackets):";
		cin >> preset;
	}
	return check;
}

void setup7x7()
{

}

void setup9x9()
{

}

void setup11x11()
{

}

void setup13x13()
{

}

void SaveMove(bool turn, char x1, char y1, char x2, char y2)
{

}


void PrintBoard(int preset, int* current[])
{

}


void Move(bool turn, char x1, char y1, char x2, char y2)
{

}

void Info()
{

}

void Quit()
{

}

void Win(char character)
{
	cout << "========================";
	if (character == 'A')
	{
		cout << setw(19) << "Attackers won!";
	}
	else
	{
		cout << setw(19) << "Defenders won!";
	}
	cout << "========================";
	if (character == 'A')
	{
		cout << "The king has been caught! The kingdom falls!";
	}
	else
	{
		cout << "The king escaped! The kingdom will prevail!";
	}
}


int main()
{
	cout << "Choose a setup (use the number in the brackets):" <<
		"\n7x7(7)" <<
		"\n9x9(9)" <<
		"\n9x9(9)" <<
		"\n11x11(11)" <<
		"\n13x13(13)" <<
		"\nEnter(use the number in the brackets):";
	cin >> preset;
	bool check = false;
	while (!check)
	{
		check = InitializeBoard(check);
		
	}
}
