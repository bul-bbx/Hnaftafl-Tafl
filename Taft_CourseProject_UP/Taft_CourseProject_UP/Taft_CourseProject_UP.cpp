#include <iostream>
#include <iomanip>

using namespace std;

int const maxInputLength = 15;
int const maxWordLength = 6;
int const maxWords = 5;


int const maxSize = 13; //The maximal size that the board can be
int const minSize = 7; //The minimal size that the board can be

int preset = 0; //The size that the board is
bool turn = 1; //1 - Defenders, 0 - Attackers
int moves = 0; //Moves taken so far
int defCount = 0; //The count of the Defenders' figures
int defDeadCount = 0; //The count of the dead Defenders' figures
int attCount = 0; //The count of the Attackers' figures
int attDeadCount = 0; //The count of the dead Attackers' figures
bool gameEnd = false;

char PreviousAttMove[] = { '0', '0', '0', '0' };//x1, y1, x2, y2 (x1, y1 - last position, x2, y2 - current position)
char PreviousDefMove[] = { '0', '0', '0', '0' };//x1, y1, x2, y2 (x1, y1 - last position, x2, y2 - current position)

char** board = new char* [preset];

void Clear() //Clears the console and sets the cursor on the top left space
{
	cout << "\x1B[2J\x1B[H";
}

void Win() //Prints the Win Screen
{
	Clear();
	cout << "========================\n";
	if (!turn)
	{
		cout << setw(19) << "Attackers won!";
	}
	else
	{
		cout << setw(19) << "Defenders won!";
	}
	cout << "\n========================\n";
	if (!turn)
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
	cout << endl;
	cout << endl;
	if (turn)
		cout << "Defenders to move!";
	else
		cout << "Attackers to move!";

	cout << endl;
	cout << endl;
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
		case 11: setup11x11(); break;
		case 13: setup13x13(); break;
		default: setup11x11(); break; //if a preset is not chosen the game sets up the traditional board size which is 11x11
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

void SaveMove(char x1, char y1, char x2, char y2) //Saves the coordinated of the change of the last movement
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

bool IsMoveLegal(char x1, char y1, char x2, char y2) //Checks if the move is along the rules or not
{

	int trueX1 = (int)(x1 - 'A');
	int trueY1 = (int)(y1 - '1');
	int trueX2 = (int)(x2 - 'A');
	int trueY2 = (int)(y2 - '1');

	bool x1Correct = trueX1 >= 0 && trueX1 <= preset - 1;
	bool y1Correct = trueY1 >= 0 && trueY1 <= preset - 1;
	bool x2Correct = trueX2 >= 0 && trueX2 <= preset - 1;
	bool y2Correct = trueY2 >= 0 && trueY2 <= preset - 1;

	if (!(x1Correct || x2Correct || y1Correct || y2Correct))
		return false;

	bool xAxis = trueX1 == trueX2;
	bool yAxis = trueY1 == trueY2;
	if (turn)
	{
		cout << (board[trueX1][trueY1] == 'D');
		cout << (board[trueX2][trueY2] == 'E');
		cout << (xAxis ^ yAxis);

		if (board[trueX1][trueY1] == 'D' && board[trueX2][trueY2] == 'E' && xAxis ^ yAxis)
		{
			return true;
		}
		else
			return false;
		if (board[trueX1][trueY1] == 'K' && xAxis ^ yAxis)
		{
			if (board[trueX2][trueY2] == 'X' || board[trueX2][trueY2] == 'E')
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
	{
		if (board[trueX1][trueY1] == 'A' && xAxis ^ yAxis && board[trueX2][trueY2])
			return true;
		else
			return false;
	}

	return 1;
}

void IsKingOnX() // Checks if the king is on one of the corners and if he is it displays win for defenders
{
	bool isOnTopLeft = board[0][0] == 'K';
	bool isOnTopRight = board[preset - 1][0] == 'K';
	bool isOnBottomLeft = board[0][preset - 1] == 'K';
	bool isOnBottomRight = board[preset - 1][preset - 1] == 'K';
	if (isOnTopLeft && isOnTopRight && isOnBottomLeft && isOnBottomRight)
	{
		Win();
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
			if (i == 0 || i == preset - 1) //Checks if the current figurine is on the left-most or right-most column
			{
				bool surround = board[i][k - 1] == board[i][k + 1] || board[i][k - 1] == 'X' || board[i][k + 1] == 'X'; //Checks if a figurine is surrounded
				bool emptySurroundings = board[i][k - 1] != 'E'; //Checks if the surroundings are empty
				bool figurineIsNotSame = board[i][k] != board[i][k - 1]; //Checks if figurine is not the same as the surrounding ones
				if (surround && emptySurroundings && figurineIsKing && figurineIsNotSame)
				{
					Win();
				}
			}
			else
			{
				if (k == 0 || k == preset - 1)//Checks if a figurine is on the top or bottom row
				{
					bool surround = board[i - 1][k] == board[i + 1][k] || board[i - 1][k] == 'X' || board[i + 1][k] == 'X'; //Checks if a figurine is surrounded
					bool emptySurroundings = board[i + 1][k] != 'E'; //Checks if the surroundings are empty
					bool figurineIsNotSame = board[i][k] != board[i + 1][k]; //Checks if figurine is not the same as the surrounding ones
					if (surround && emptySurroundings && figurineIsKing && figurineIsNotSame)
					{
						Win();
					}
				}
				else
				{
					bool surroundI = board[i - 1][k] == board[i + 1][k] || board[i - 1][k] == 'X' || board[i + 1][k] == 'X'; //Checks if a figurine is surrounded on the i axis
					bool surroundK = board[i][k - 1] == board[i][k + 1] || board[i][k - 1] == 'X' || board[i][k + 1] == 'X'; //Checks if a figurine is surrounded on the k axis
					bool figurineIsNotSame = board[i][k] != board[i + 1][k] || board[i][k] != board[i][k - 1]; //Checks if figurine is not the same as the surrounding ones
					bool emptySurroundingsK = board[i][k - 1] != 'E'; //Checks if surroundings on the k axis are empty
					bool emptySurroundingsI = board[i - 1][k] != 'E'; //Checks if surroundings on the i axis are empty

					bool combinedChecksI = surroundI && figurineIsKing && figurineIsNotSame;
					bool combinedChecksK = surroundK && figurineIsKing && figurineIsNotSame;
					if (combinedChecksI && emptySurroundingsI)
						Win();

					if (combinedChecksI && emptySurroundingsK)
						Win();

					if (combinedChecksK && emptySurroundingsI)
						Win();

					if (combinedChecksK && emptySurroundingsK)
						Win();
				}
			}
		}
	}
}

void RemoveFigurine(char x, char y) //Removes a figurine at the given coordinates
{
	cout << "\nFigurine on coordinates " << x << ", " << y << " with symbol " << board[x][y] << " has been taken!";
	board[x][y] = 'E';
	if (board[x][y] == 'A')
	{
		attCount--;
		attDeadCount++;
	}
	if (board[x][y] == 'D')
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
			bool figurineIsNotEmptyOrSafe = board[i][k] != 'E' || board[i][k] == 'X'; //Checks if the figurine being taken is empty or safe space
			bool figurineIsNotKing = board[i][k] != 'K';
			if (figurineIsNotEmptyOrSafe && figurineIsNotKing)
			{
				if (i == 0 || i == preset - 1) //Checks if the current figurine is on the left-most or right-most column
				{
					bool surroundI = board[i][k - 1] == board[i][k + 1] || board[i][k - 1] == 'X' || board[i][k + 1] == 'X'; //Checks if a figurine is surrounded
					bool emptySurroundings = board[i][k - 1] != 'E'; //Checks if the surroundings are empty
					bool figurineIsNotSame = board[i][k] != board[i][k - 1]; //Checks if figurine is not the same as the surrounding ones
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
						bool figurineIsNotSame = board[i][k] != board[i + 1][k]; //Checks if figurine is not the same as the surrounding ones
						if (surroundK && emptySurroundings && figurineIsNotSame)
						{
							RemoveFigurine(i, k);
						}
					}
					else
					{
						bool surroundI = board[i - 1][k] == board[i + 1][k] || board[i - 1][k] == 'X' || board[i + 1][k] == 'X'; //Checks if a figurine is surrounded on the i axis
						bool surroundK = board[i][k - 1] == board[i][k + 1] || board[i][k - 1] == 'X' || board[i][k + 1] == 'X'; //Checks if a figurine is surrounded on the k axis
						bool figurineIsNotSame = board[i][k] != board[i + 1][k] || board[i][k] != board[i][k - 1]; //Checks if figurine is not the same as the surrounding ones
						bool emptySurroundingsK = board[i][k - 1] != 'E'; //Checks if surroundings on the k axis are empty
						bool emptySurroundingsI = board[i - 1][k] != 'E'; //Checks if surroundings on the i axis are empty

						bool combinedChecksI = surroundI && figurineIsNotSame;
						bool combinedChecksK = surroundK && figurineIsNotSame;
						if (combinedChecksI && emptySurroundingsI)
							RemoveFigurine(i, k);

						if (combinedChecksI && emptySurroundingsK)
							RemoveFigurine(i, k);

						if (combinedChecksK && emptySurroundingsI)
							RemoveFigurine(i, k);

						if (combinedChecksK && emptySurroundingsK)
							RemoveFigurine(i, k);
					}
				}
			}
		}
	}
}

void Move(char x1, char y1, char x2, char y2) // Makes the move chosen by the player if it is legal
{
	int trueX1 = (int)(x1 - 'A');
	int trueY1 = (int)(y1 - '1');
	int trueX2 = (int)(x2 - 'A');
	int trueY2 = (int)(y2 - '1');

	if (IsMoveLegal(x1, y1, x2, y2))
	{
		board[trueX2][trueY2] = board[trueX1][trueY1];
		board[trueX1][trueY1] = 'E';
		SaveMove(x1, y1, x2, y2);
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
	if (turn)
	{
		Move(PreviousDefMove[2], PreviousDefMove[3], PreviousDefMove[0], PreviousDefMove[1]);
	}
	else
	{
		Move(PreviousAttMove[2], PreviousAttMove[3], PreviousAttMove[0], PreviousAttMove[1]);
	}
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
		"\nEnter(use the number in the brackets):";
	cin >> preset;
	bool check = false;
	while (!check)
	{
		check = InitializeBoard(check);
	}
	PrintBoard();

	char input[maxInputLength];

	while (!gameEnd)
	{

		PrintBoard();
		cout << "\nEnter a command (Write 'Help' for commands):\n";
		cin.getline(input, maxInputLength);
		char words[maxWords][maxWordLength];
		char currentWord[maxWordLength];
		int wordIndex = 0;
		int wordCount = 0;

		for (int i = 0; ; ++i) {
			if (input[i] == ' ' || input[i] == '\0') {
				if (wordIndex > 0) {
					currentWord[wordIndex] = '\0';

					int j = 0;
					while (currentWord[j] != '\0') {
						words[wordCount][j] = currentWord[j];
						j++;
					}
					words[wordCount][j] = '\0';
					wordCount++;

					wordIndex = 0;
				}
				if (input[i] == '\0') {
					break;
				}
			}
			else {
				currentWord[wordIndex++] = input[i];
			}
		}

		if (strcmp(words[0], "Move") == 0) {
			Move(words[1][0], words[2][0], words[3][0], words[4][0]);
		}
		else
		{
			if (strcmp(words[0], "Back") == 0) {
				Back();
			}
			else {
				if (strcmp(words[0], "Quit") == 0) {
					Quit();
				}
				else {
					if (strcmp(words[0], "Info") == 0) {
						Info();
					}
					else {
						if (strcmp(words[0], "Help") == 0) {
							Help();
						}
						else {
							if (strcmp(words[0], "Rules") == 0) {
								Rules();
							}
							else {
								cout << "\nInvalid command!\n";
							}
						}
					}
				}
			}
		}


	}
	for (int i = 0; i < preset; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}
