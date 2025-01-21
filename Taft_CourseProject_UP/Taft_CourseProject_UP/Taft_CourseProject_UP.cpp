// Veliko Velikov 8MI0600548

#include <iostream>
#include <iomanip>
//#include <cstring>

using namespace std;

int const maxInputLength = 15;
int const maxWordLength = 6;
int const maxWords = 5;

int const maxSize = 13; // The maximal size that the board can be
int const minSize = 7; // The minimal size that the board can be

int preset = 0; // The size that the board is
char turn = 'N'; // 1 - Defenders, 0 - Attackers
int moves = 0; // Moves taken so far
int defCount = 0; // The count of the Defenders' figures
int defDeadCount = 0; // The count of the dead Defenders' figures
int attCount = 0; // The count of the Attackers' figures
int attDeadCount = 0; // The count of the dead Attackers' figures
bool gameEnd = false;

char** board = nullptr;
char** boardDef = nullptr;
char** boardAtt = nullptr;

void Clear() // Clears the console and sets the cursor on the top left space
{
	cout << "\x1B[2J\x1B[H";
}

void Win(char character) // Prints the Win Screen
{
	Clear();
	cout << "========================\n";
	if (character == 'A')
	{
		cout << setw(19) << "Attackers won!";
	}
	else
	{
		cout << setw(19) << "Defenders won!";
	}
	cout << "\n========================\n";
	if (character == 'A')
	{
		cout << "The king has been caught! The kingdom falls!";
	}
	else
	{
		cout << "The king escaped! The kingdom will prevail!";
	}
	gameEnd = true;
}

void CountFigurines() // Counts the amount of every figurine there is
{
	attCount = 0;
	defCount = 0;
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
	Clear();
	cout << "  | ";
	for (int i = 0; i < preset; i++)
	{
		cout << (char)('A' + i) << " "; // Sets the top orienting row (the letters for the spaces)
	}
	cout << "| " << endl;
	for (int i = 0; i < 2 * (preset + 4) - 1; i++)
		cout << "-"; // Sets the divisor between the orienting row and the board
	cout << endl;

	for (int i = 0; i < preset; i++)
	{
		cout << setw(2) << i + 1 << "| "; // Sets the left most orienting column (the numbers for the spaces)
		for (int k = 0; k < preset; k++)
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
		cout << "|" << i + 1; // Sets the right most orienting column (the numbers for the spaces)
		cout << endl;
	}

	for (int i = 0; i < 2 * (preset + 4) - 1; i++)
		cout << "-"; // Sets the divisor between the orienting row and the board

	cout << endl << "  | ";
	for (int i = 0; i < preset; i++)
	{
		cout << (char)('A' + i) << " "; // Sets the top orienting row (the letters for the spaces)
	}
	cout << "| " << endl;

	cout << endl;
	if (turn == 'D')
		cout << "Defenders to move!";
	if (turn == 'A')
		cout << "Attackers to move!";
	cout << endl << endl;
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


	//Defenders
	board[preset / 2][preset / 2 + 1] = 'D';
	board[preset / 2 + 1][preset / 2] = 'D';
	board[preset / 2][preset / 2 - 1] = 'D';
	board[preset / 2 - 1][preset / 2] = 'D';
	board[preset / 2 + 1][preset / 2 + 1] = 'D';
	board[preset / 2 - 1][preset / 2 + 1] = 'D';
	board[preset / 2 + 1][preset / 2 - 1] = 'D';
	board[preset / 2 - 1][preset / 2 - 1] = 'D';
	board[preset / 2 - 2][preset / 2] = 'D';
	board[preset / 2 + 2][preset / 2] = 'D';
	board[preset / 2][preset / 2 - 2] = 'D';
	board[preset / 2][preset / 2 + 2] = 'D';
	CountFigurines();

	//King
	board[preset / 2][preset / 2] = 'K';

	//Safe Spaces;
	board[0][0] = 'X';
	board[preset - 1][0] = 'X';
	board[preset - 1][preset - 1] = 'X';
	board[0][preset - 1] = 'X';

}

void setup13x13() // Sets up the board on a 13x13 preset
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

	//Defenders
	board[preset / 2][preset / 2 + 1] = 'D';
	board[preset / 2 + 1][preset / 2] = 'D';
	board[preset / 2][preset / 2 - 1] = 'D';
	board[preset / 2 - 1][preset / 2] = 'D';
	board[preset / 2 + 1][preset / 2 + 1] = 'D';
	board[preset / 2 - 1][preset / 2 + 1] = 'D';
	board[preset / 2 + 1][preset / 2 - 1] = 'D';
	board[preset / 2 - 1][preset / 2 - 1] = 'D';
	board[preset / 2 - 2][preset / 2] = 'D';
	board[preset / 2 + 2][preset / 2] = 'D';
	board[preset / 2][preset / 2 - 2] = 'D';
	board[preset / 2][preset / 2 + 2] = 'D';
	board[preset / 2 - 3][preset / 2] = 'D';
	board[preset / 2 + 3][preset / 2] = 'D';
	board[preset / 2][preset / 2 - 3] = 'D';
	board[preset / 2][preset / 2 + 3] = 'D';
	CountFigurines();

	//King
	board[preset / 2][preset / 2] = 'K';

	//Safe Spaces;
	board[0][0] = 'X';
	board[preset - 1][0] = 'X';
	board[preset - 1][preset - 1] = 'X';
	board[0][preset - 1] = 'X';
}

bool InitializeBoard() // Sets up the board and makes sure that the parameters given are correct
{
	Clear();
	bool numericCheck = preset % 2 == 1 && preset >= minSize && preset <= maxSize;
	if (numericCheck)
	{
		board = new char* [preset];
		boardDef = new char* [preset];
		boardAtt = new char* [preset];
		for (int i = 0; i < preset; i++)
		{
			board[i] = new char[preset];
			boardDef[i] = new char[preset];
			boardAtt[i] = new char[preset];
		}
		switch (preset)
		{
		case 7: setup7x7(); break;
		case 9: setup9x9(); break;
		case 11: setup11x11(); break;
		case 13: setup13x13(); break;
		default: setup11x11(); break;
		}
		return true;
	}
	else
	{
		cout << "Invalid input! \n";
		cout << "Choose a setup (use the number in the brackets):" <<
			"\n7x7(7)" <<
			"\n9x9(9)" <<
			"\n11x11(11)" <<
			"\n13x13(13)" << endl;
		cin >> preset;
		return false;
	}
}

void SaveMove() //Saves the coordinated of the change of the last movement
{
	if (!turn)
	{
		for (int i = 0; i < preset; i++)
		{
			for (int k = 0; k < preset; k++)
			{
				boardDef[i][k] = board[i][k];
			}
		}
	}
	else
	{
		for (int i = 0; i < preset; i++)
		{
			for (int k = 0; k < preset; k++)
			{
				boardAtt[i][k] = board[i][k];
			}
		}
	}
}

bool IsMoveLegal(char x1, char* y1, char x2, char* y2) //Checks if the move is along the rules or not
{

	int trueY1, trueY2;
	int trueX1 = (int)(x1 - 'A');
	if (strlen(y1) > 1)
		trueY1 = (int)(y1[0] - '0') * 10 + (int)(y1[1] - '1');
	else
		trueY1 = (int)(y1[0] - '1');
	int trueX2 = (int)(x2 - 'A');
	if (strlen(y2) > 1)
		trueY2 = (int)(y2[0] - '0') * 10 + (int)(y2[1] - '1');
	else
		trueY2 = (int)(y2[0] - '1');

	bool x1Correct = trueX1 >= 0 && trueX1 <= preset - 1;
	bool y1Correct = trueY1 >= 0 && trueY1 <= preset - 1;
	bool x2Correct = trueX2 >= 0 && trueX2 <= preset - 1;
	bool y2Correct = trueY2 >= 0 && trueY2 <= preset - 1;

	if (!(x1Correct || x2Correct || y1Correct || y2Correct))
		return false;



	bool xAxis = trueX1 == trueX2;
	bool yAxis = trueY1 == trueY2;
	if (xAxis ^ yAxis)
	{
		if (yAxis)
		{
			if (trueX1 < trueX2)
				for (int i = trueX1; i < trueX2; i++)
				{
					if (board[trueY1 + 1][i] != 'E')
					{
						return false;
					}
				}
			else
				for (int i = trueX2 + 1; i < trueX1; i++)
				{
					if (board[trueY1][i] != 'E')
					{
						return false;
					}
				}
		}
		else
		{
			if (trueY1 < trueY2)
				for (int i = trueY1 + 1; i < trueY2; i++)
				{
					if (board[i][trueX1] != 'E')
					{
						return false;
					}
				}
			else
				for (int i = trueY2 + 1; i < trueY1; i++)
				{
					if (board[i][trueX1] != 'E')
					{
						return false;
					}
				}
		}
		if (turn)
		{
			if (board[trueY1][trueX1] == 'D' && board[trueY2][trueX2] == 'E' && xAxis ^ yAxis)
			{
				return true;
			}
			else
			{
				if (board[trueY1][trueX1] == 'K' && xAxis ^ yAxis)
				{
					if (board[trueY2][trueX2] == 'X' || board[trueY2][trueX2] == 'E')
						return true;
					else
						return false;
				}
				else
					return false;
			}
		}
		else
		{
			if (board[trueY1][trueX1] == 'A' && xAxis ^ yAxis && board[trueY2][trueX2] == 'E')
				return true;
			else
				return false;
		}
	}

}

void IsKingOnX() // Checks if the king is on one of the corners and if he is it displays win for defenders
{
	bool isOnTopLeft = board[0][0] == 'K';
	bool isOnTopRight = board[preset - 1][0] == 'K';
	bool isOnBottomLeft = board[0][preset - 1] == 'K';
	bool isOnBottomRight = board[preset - 1][preset - 1] == 'K';
	if (isOnTopLeft && isOnTopRight && isOnBottomLeft && isOnBottomRight)
	{
		Win('D');
	}
}

void IsKingCaptured()//Checks if the king has two other figurines (or an X and a figurine) on opposite sides
{
	char captured[2] = { preset, preset };
	for (int i = 0; i < preset; i++)
	{
		for (int k = 0; k < preset; k++)
		{
			bool figurineIsKing = board[i][k] == 'K'; //Checks if the figurine being taken is empty or safe space
			if (figurineIsKing)
			{
				if (i == 0 || i == preset - 1) //Checks if the current figurine is on the left-most or right-most column
				{
					bool surroundI = board[i][k - 1] == board[i][k + 1] || board[i][k - 1] == 'X' || board[i][k + 1] == 'X'; //Checks if a figurine is surrounded
					bool emptySurroundings = board[i][k - 1] != 'E'; //Checks if the surroundings are empty
					bool figurineIsNotDef = board[i][k - 1] != 'D'; //Checks if figurine is not the same as the surrounding ones
					if (surroundI && emptySurroundings && figurineIsNotDef)
					{
						Win('A');
					}
				}
				else
				{
					if (k == 0 || k == preset - 1)//Checks if a figurine is on the top or bottom row
					{
						bool surroundK = board[i - 1][k] == board[i + 1][k] || board[i - 1][k] == 'X' || board[i + 1][k] == 'X'; //Checks if a figurine is surrounded
						bool emptySurroundings = board[i + 1][k] != 'E'; //Checks if the surroundings are empty
						bool figurineIsNotDef = board[i + 1][k] != 'D'; //Checks if figurine is not the same as the surrounding ones
						if (surroundK && emptySurroundings && figurineIsNotDef)
						{
							Win('A');
						}
					}
					else
					{
						bool surroundI = board[i - 1][k] == board[i + 1][k] || board[i - 1][k] == 'X' || board[i + 1][k] == 'X'; //Checks if a figurine is surrounded on the i axis
						bool surroundK = board[i][k - 1] == board[i][k + 1] || board[i][k - 1] == 'X' || board[i][k + 1] == 'X'; //Checks if a figurine is surrounded on the k axis
						bool figurineIsNotDef = (board[i + 1][k] != 'D' && board[i - 1][k] != 'D') || (board[i][k - 1] != 'D' && board[i][k + 1] != 'D'); //Checks if the surrounding figurines are attackers
						bool emptySurroundingsK = board[i][k - 1] != 'E'; //Checks if surroundings on the k axis are empty
						bool emptySurroundingsI = board[i - 1][k] != 'E'; //Checks if surroundings on the i axis are empty

						bool combinedChecksI = surroundI && figurineIsNotDef;
						bool combinedChecksK = surroundK && figurineIsNotDef;
						if (combinedChecksI && emptySurroundingsI)
							Win('A');

						if (combinedChecksK && emptySurroundingsK)
							Win('A');
					}
				}
			}
		}
	}
}

void RemoveFigurine(int x, int y) //Removes a figurine at the given coordinates
{
	char trueYarr[2];
	char trueY;
	char trueX = (char)(x + 'A');
	if (y > 9)
	{
		trueYarr[0] = (char)(y / 10 + '1');
		trueYarr[1] = (char)(y % 10 + '1');
	}
	else
		trueY = y + '1';
	char character = board[x][y];
	board[x][y] = 'E';

	if (y > 9)
	{
		cout << "\nFigurine on coordinates " << trueX << ", " << trueYarr[0] << trueYarr[1] << " with symbol " << character << " has been taken!";
	}
	else
		cout << "\nFigurine on coordinates " << trueX << ", " << trueY << " with symbol " << character << " has been taken!";

	if (character == 'A')
	{
		attCount--;
		attDeadCount++;
	}
	if (character == 'D')
	{
		defCount--;
		defDeadCount++;
	}
}

void IsFigurineCaptured() //Checks if any figurine has two other figurines (or an X and a figurine) on opposite sides
{
	for (int i = 0; i < preset; i++)
	{
		for (int k = 0; k < preset; k++)
		{
			bool figurineIsNotEmptyOrSafe = !(board[i][k] == 'E' || board[i][k] == 'X'); //Checks if the figurine being taken is empty or safe space
			bool figurineIsNotKing = board[i][k] != 'K';
			if (figurineIsNotEmptyOrSafe && figurineIsNotKing)
			{
				if (i == 0 || i == preset - 1) //Checks if the current figurine is on the left-most or right-most column
				{
					bool surroundI = board[i][k - 1] == board[i][k + 1] || board[i][k - 1] == 'X' || board[i][k + 1] == 'X'; //Checks if a figurine is surrounded
					bool emptySurroundings = board[i][k - 1] != 'E'; //Checks if the surroundings are empty
					bool figurineIsNotSame = board[i][k] != board[i][k - 1] || board[i][k] != board[i][k + 1]; //Checks if figurine is not the same as the surrounding ones


					if (board[i][k] == 'D')
					{
						surroundI = surroundI && !(board[i][k - 1] == 'K' || board[i][k + 1] == 'K');
					}

					if (surroundI && emptySurroundings && figurineIsNotSame)
					{
						RemoveFigurine(i, k);
					}
				}
				else
				{
					if (k == 0 || k == preset - 1)//Checks if a figurine is on the top or bottom row
					{
						bool surroundK = board[i - 1][k] == board[i + 1][k] || board[i - 1][k] == 'X' || board[i + 1][k] == 'X'; //Checks if a figurine is surrounded
						bool emptySurroundings = board[i + 1][k] != 'E'; //Checks if the surroundings are empty
						bool figurineIsNotSame = board[i][k] != board[i + 1][k] || board[i][k] != board[i - 1][k]; //Checks if figurine is not the same as the surrounding ones


						if (board[i][k] == 'D')
						{
							surroundK = surroundK && !(board[i - 1][k] == 'K' || board[i + 1][k] == 'K');
						}
						if (surroundK && emptySurroundings && figurineIsNotSame)
						{
							RemoveFigurine(i, k);
						}
					}
					else
					{
						bool surroundI = board[i - 1][k] == board[i + 1][k] || board[i - 1][k] == 'X' || board[i + 1][k] == 'X'; //Checks if a figurine is surrounded on the i axis
						bool surroundK = board[i][k - 1] == board[i][k + 1] || board[i][k - 1] == 'X' || board[i][k + 1] == 'X'; //Checks if a figurine is surrounded on the k axis
						bool figurineIsNotSame = (board[i][k] != board[i + 1][k] || board[i][k] != board[i - 1][k]) && (board[i][k] != board[i][k - 1] || board[i][k] != board[i][k + 1]); //Checks if figurine is not the same as the surrounding ones
						bool emptySurroundingsK = board[i][k - 1] != 'E' || board[i][k + 1] != 'E'; //Checks if surroundings on the k axis are empty
						bool emptySurroundingsI = board[i - 1][k] != 'E' || board[i + 1][k] != 'E'; //Checks if surroundings on the i axis are empty


						if (board[i][k] == 'D')
						{
							surroundI = surroundI && !(board[i][k - 1] == 'K' || board[i][k + 1] == 'K');
							surroundK = surroundK && !(board[i - 1][k] == 'K' || board[i + 1][k] == 'K');
						}
						bool combinedChecksI = surroundI && figurineIsNotSame;
						bool combinedChecksK = surroundK && figurineIsNotSame;
						if (combinedChecksI && emptySurroundingsI)
							RemoveFigurine(i, k);

						if (combinedChecksK && emptySurroundingsK)
							RemoveFigurine(i, k);
					}
				}
			}
		}
	}
}

void Move(char x1, char* y1, char x2, char* y2) // Makes the move chosen by the player if it is legal
{
	int trueY1, trueY2;
	int trueX1 = (int)(x1 - 'A');
	if (strlen(y1) > 1)
		trueY1 = (int)(y1[0] - '0') * 10 + (int)(y1[1] - '1');
	else
		trueY1 = (int)(y1[0] - '1');
	int trueX2 = (int)(x2 - 'A');
	if (strlen(y2) > 1)
		trueY2 = (int)(y2[0] - '0') * 10 + (int)(y2[1] - '1');
	else
		trueY2 = (int)(y2[0] - '1');

	if (IsMoveLegal(x1, y1, x2, y2))
	{
		SaveMove();
		if (trueY1 == preset / 2 && trueX1 == preset / 2)
		{
			board[trueY2][trueX2] = board[trueY1][trueX1];
			board[trueY1][trueX1] = 'X';
		}
		else
		{
			board[trueY2][trueX2] = board[trueY1][trueX1];
			board[trueY1][trueX1] = 'E';
		}
		moves++;
		IsFigurineCaptured();
		IsKingCaptured();
		IsKingOnX();
		turn = !turn;
	}
	else
	{
		cout << "Choose a valid move!";
	}
}

void Back() //Turns back one move
{
	turn = !turn;
	moves--;
	if (!turn)
	{
		for (int i = 0; i < preset; i++)
		{
			for (int k = 0; k < preset; k++)
			{
				board[i][k] = boardDef[i][k];
			}
		}
	}
	else
	{
		for (int i = 0; i < preset; i++)
		{
			for (int k = 0; k < preset; k++)
			{
				board[i][k] = boardAtt[i][k];
			}
		}
	}
	PrintBoard();
}

void Rules() //Prints the rules of the game
{
	cout << "\nRules of the game:\n" <<
		"1. Setup and Pieces\n" <<
		" - The king starts on the throne at the center.\n" <<
		" - Defenders surround the king, while attackers begin at the edges.\n" <<
		"The king must escape to a corner to win for the defenders.\n\n" <<
		"2. Movement and Capture\n" <<
		" - Pieces move like chess rooks(vertically or horizontally).\n" <<
		" - Pieces are captured when surrounded on both sides.\n" <<
		" - The king must avoid being surrounded and escape to a corner.\n\n" <<
		"3. Winning\n" <<
		" - Attackers win by capturing the king.\n" <<
		" - Defenders win if the king escapes to a corner.";
}

void Info() // Writes the info about the game situation(Player on turn, Number of figurines, Takes figurines, Number of moves taken so far)
{
	cout << "\nDefenders: " <<
		"\nAlive - " << defCount <<
		"\nDead - " << defDeadCount <<
		"\nAttackers: " <<
		"\nAlive - " << attCount <<
		"\nDead - " << attDeadCount;
	if (!gameEnd)
	{
		if (turn)
			cout << "\n\nDefenders turn";
		else
			cout << "\n\nAttackers turn";
	}
	cout << "\n\nMoves conducted - " << moves;
}

void Help() // Gives a list with the possible commands
{
	cout << "\nHere's a list with all the commands:\n" <<
		"1. Move (x1) (y1) (x2) (y2) - Moves a figurine of the player who is on turn currently\n" <<
		"2. Back - Takes back one move\n" <<
		"3. Quit - Leaves the game\n" <<
		"4. Info - Gives you the info about the current situation of the game\n" <<
		"5. Help - Brings out this list\n" <<
		"6. Rules - Gives you the rules of the game\n";
}

void Quit() //Leaves the game
{
	gameEnd = true;
	Info();
}

int main()
{
	cout << "Choose a setup (use the number in the brackets):" <<
		"\n7x7(7)" <<
		"\n9x9(9)" <<
		"\n11x11(11)" <<
		"\n13x13(13)" <<
		"\nEnter a preset:" << endl;
	cin >> preset;

	while (!InitializeBoard()); // Loop until the board is initialized correctly

	PrintBoard();

	cout << "Choose who will start first (A/D): ";
	char toStart;
	cin >> toStart;
	while (toStart != 'A' && toStart != 'D') {
		cout << "Choose who will start first (A/D): ";
		cin >> toStart;
	}
	turn = toStart;

	char input[maxInputLength];
	while (!gameEnd) {
		PrintBoard();
		cout << "\nEnter a command (Write 'Help' for commands):\n";

		cin.getline(input, maxInputLength);
		char words[maxWords][maxWordLength];
		int wordCount = 0;

		char* context;
		char* token = strtok_s(input, " ", &context);
		while (token != nullptr && wordCount < maxWords) {
			strncpy_s(words[wordCount], maxWordLength, token, _TRUNCATE);
			words[wordCount][maxWordLength - 1] = '\0'; // Null-terminate
			wordCount++;
			token = strtok_s(nullptr, " ", &context);
		}

		if (strcmp(words[0], "Move") == 0 && wordCount == 5) {
			Move(words[1][0], words[2], words[3][0], words[4]);
		}
		else if (strcmp(words[0], "Back") == 0) {
			Back();
		}
		else if (strcmp(words[0], "Quit") == 0) {
			Quit();
		}
		else if (strcmp(words[0], "Info") == 0) {
			Info();
		}
		else if (strcmp(words[0], "Help") == 0) {
			Help();
		}
		else if (strcmp(words[0], "Rules") == 0) {
			Rules();
		}
		else {
			if (strlen(words[0]) <= 0)
				cout << "\nInvalid command!\n";
		}
		cout << "\nPress any key to continue...";
		getchar(); // Wait for user input
	}

	for (int i = 0; i < preset; i++)
	{
		delete[] board[i];
		delete[] boardDef[i];
		delete[] boardAtt[i];
	}
	delete[] board;
	delete[] boardDef;
	delete[] boardAtt;

	return 0;
}