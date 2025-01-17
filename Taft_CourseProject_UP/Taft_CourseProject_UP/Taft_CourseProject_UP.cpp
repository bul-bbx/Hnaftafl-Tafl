#include <iostream>
#include <iomanip>

using namespace std;

int const maxSize = 13; //The maximal size that the board can be
int const minSize = 7; //The minimal size that the board can be

int preset = 0; //The size that the board is
bool turn = 1; //1 - Defenders, 0 - Attackers
int moves = 0; //Moves taken so far
int defCount = 0; //The count of the Defenders' figures
int defMaxCount = preset + 1;
int attCount = 0; //The count of the Attackers' figures
int attMaxCount = defMaxCount * 2;

char PreviousAttMove[] = { '0', '0', '0', '0' };//x1, y1, x2, y2 (x1, y1 - last position, x2, y2 - current position)
char PreviousDefMove[] = { '0', '0', '0', '0' };//x1, y1, x2, y2 (x1, y1 - last position, x2, y2 - current position)

char** board = new char* [preset];

void Clear() //Clears the console and sets the cursor on the top left space
{
	cout << "\x1B[2J\x1B[H";
}

void CountFigurines() // Counts the amount of every figurine there is
{
	for (int i = 0; i < preset; i++)
	{
		for (int k = 0; k < preset; k++)
		{
			if (board[i][k] == 'A')
				attCount++;
			if (board[i][k] == 'D')
				defCount++;
		}
	}
}



void PrintBoard() // Prints the board
{
	cout << "  | ";
	for (int i = 0; i < preset; i++)
	{
		cout << (char)('A' + i) << " "; //Sets the top orienting row (the letters for the spaces)
	}
	cout << endl;
	for (int i = 0; i < preset + 3; i++)
		cout << "- "; //Sets the divisor between the orienting row and the board
	cout << endl;
	for (int i = 0; i < preset; i++)
	{
		cout << setw(2) << i + 1 << "| "; //Sets the left most orienting column (the numbers for the spaces)
		for (int k = 0; k < preset; k++)
		{
			if (i == preset / 2 && k == preset / 2)
			{
				if (board[i][k] != 'K') //Checks if the king is in the middle and if he isn't sets it to an X
					cout << "X ";
				else
					cout << "K ";
			}
			else
			{
				switch (board[i][k])
				{
				case 'E': cout << "· "; break;
				case 'A': cout << "A "; break;
				case 'D': cout << "D "; break;
				case 'K': cout << "K "; break;
				case 'X': cout << "X "; break;
				}
			}
		}
		cout << endl;
	}
}

void setup7x7() // Sets up the board on a 7x7 preset
{
	//Empty spaces
	for (int i = 0; i < preset; i++)
	{
		for (int k = 0; k < preset; k++)
		{
			board[i][k] = 'E';
		}
	}

	//Attackers
	for (int i = 0; i < preset; i++)
	{
		if (i >= 2 && i <= preset - 3)
		{
			board[i][0] = 'A';
			board[i][preset - 1] = 'A';
			board[0][i] = 'A';
			board[preset - 1][i] = 'A';
		}
	}
	board[1][preset / 2] = 'A';
	board[preset - 2][preset / 2] = 'A';
	board[preset / 2][1] = 'A';
	board[preset / 2][preset - 2] = 'A';
	CountFigurines();

	//Defenders
	board[preset / 2][preset / 2 + 1] = 'D';
	board[preset / 2 + 1][preset / 2] = 'D';
	board[preset / 2][preset / 2 - 1] = 'D';
	board[preset / 2 - 1][preset / 2] = 'D';
	board[preset / 2 + 1][preset / 2 + 1] = 'D';
	board[preset / 2 - 1][preset / 2 + 1] = 'D';
	board[preset / 2 + 1][preset / 2 - 1] = 'D';
	board[preset / 2 - 1][preset / 2 - 1] = 'D';
	CountFigurines();

	//King
	board[preset / 2][preset / 2] = 'K';

	//Safe Spaces;
	board[0][0] = 'X';
	board[preset - 1][0] = 'X';
	board[preset - 1][preset - 1] = 'X';
	board[0][preset - 1] = 'X';
	PrintBoard();
}


void setup9x9() // Sets up the board on a 9x9 preset
{
	//Empty spaces
	for (int i = 0; i < preset; i++)
	{
		for (int k = 0; k < preset; k++)
		{
			board[i][k] = 'E';
		}
	}

	//Attackers
	for (int i = 0; i < preset; i++)
	{
		if (i >= 3 && i <= preset - 4)
		{
			board[i][0] = 'A';
			board[i][preset - 1] = 'A';
			board[0][i] = 'A';
			board[preset - 1][i] = 'A';
		}
	}
	board[1][preset / 2] = 'A';
	board[preset - 2][preset / 2] = 'A';
	board[preset / 2][1] = 'A';
	board[preset / 2][preset - 2] = 'A';
	CountFigurines();

	//Defenders
	board[preset / 2][preset / 2 + 1] = 'D';
	board[preset / 2 + 1][preset / 2] = 'D';
	board[preset / 2][preset / 2 - 1] = 'D';
	board[preset / 2 - 1][preset / 2] = 'D';
	board[preset / 2][preset / 2 + 2] = 'D';
	board[preset / 2 + 2][preset / 2] = 'D';
	board[preset / 2][preset / 2 - 2] = 'D';
	board[preset / 2 - 2][preset / 2] = 'D';
	CountFigurines();

	//King
	board[preset / 2][preset / 2] = 'K';

	//Safe Spaces;
	board[0][0] = 'X';
	board[preset - 1][0] = 'X';
	board[preset - 1][preset - 1] = 'X';
	board[0][preset - 1] = 'X';
	PrintBoard();
}

void setup11x11() // Sets up the board on a 11x11 preset
{
	//Empty spaces
	for (int i = 0; i < preset; i++)
	{
		for (int k = 0; k < preset; k++)
		{
			board[i][k] = 'E';
		}
	}

	//Attackers
	for (int i = 0; i < preset; i++)
	{
		if (i >= 2 && i <= preset - 3)
		{
			board[i][0] = 'A';
			board[i][preset - 1] = 'A';
			board[0][i] = 'A';
			board[preset - 1][i] = 'A';
		}
	}
	board[1][preset / 2] = 'A';
	board[preset - 2][preset / 2] = 'A';
	board[preset / 2][1] = 'A';
	board[preset / 2][preset - 2] = 'A';
	CountFigurines();

	//Defenders
	board[preset / 2][preset / 2 + 1] = 'D';
	board[preset / 2 + 1][preset / 2] = 'D';
	board[preset / 2][preset / 2 - 1] = 'D';
	board[preset / 2 - 1][preset / 2] = 'D';
	board[preset / 2 + 1][preset / 2 + 1] = 'D';
	board[preset / 2 - 1][preset / 2 + 1] = 'D';
	board[preset / 2 + 1][preset / 2 - 1] = 'D';
	board[preset / 2 - 1][preset / 2 - 1] = 'D';
	CountFigurines();

	//King
	board[preset / 2][preset / 2] = 'K';

	//Safe Spaces;
	board[0][0] = 'X';
	board[preset - 1][0] = 'X';
	board[preset - 1][preset - 1] = 'X';
	board[0][preset - 1] = 'X';
	PrintBoard();
}

void setup13x13() // Sets up the board on a 13x13 preset
{

}

bool InitializeBoard(bool check) //Sets up the board and makes sure that the parameters given are correct
{
	Clear();
	bool numericCheck = preset % 2 == 1 && preset >= minSize && preset <= maxSize;
	if (numericCheck || preset == 0 || preset == ' ')
	{
		board = new char* [preset];
		for (int i = 0; i < preset; i++)
		{
			board[i] = new char[preset];
			for (int k = 0; k < preset; k++)
				board[i][k] = '0';
		}
		switch (preset)
		{
		case 7: setup7x7(); break;
			case 9: setup9x9(); break;
			//case 11: setup11x11(); break;
			//case 13: setup13x13(); break;
			//default: setup11x11(); break; //if a preset is not chosen the game sets up the traditional board size which is 11x11
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

void SaveMove(bool turn, char x1, char y1, char x2, char y2) //Saves the coordinated of the change of the last movement
{
	if (turn)
	{
		PreviousDefMove[0] = x1;
		PreviousDefMove[1] = y1;
		PreviousDefMove[2] = x2;
		PreviousDefMove[3] = y2;
	}
	else
	{
		PreviousAttMove[0] = x1;
		PreviousAttMove[1] = y1;
		PreviousAttMove[2] = x2;
		PreviousAttMove[3] = y2;
	}
}




bool IsMoveLegal()
{
	return 1;
}

bool IsKingCaptured()
{
	return 1;
}

bool IsFigurineCaptured()
{
	return 1;
}

void Move(bool turn, char x1, char y1, char x2, char y2) // Makes the move chosen by the player
{

}

void Info() // Writes the info about the game situation(Player on turn, Number of figurines, Takes figurines, Number of moves taken so far)
{

}

void Quit() //Leaves the game
{

}

void Win(char character) //Prints the Win Screen
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
