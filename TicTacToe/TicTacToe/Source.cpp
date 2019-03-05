#include <iostream>
#include <string>
#include <vector>
#include "Ai.h" //Header file with the class Ai that plays the Ai's turn.

using namespace std;

void WelcomeMsg(bool &, bool &); //Welcomes the player and asks him if he wants to play singleplayer or multyplayer.
void PrintField(char[3][3], bool); //Prints the playing field.
int CheckInput(int &); //Checks the user input, it must be a single number 1-3.
void PlayerTurn(char[][3], bool, bool &); //Asks the user the coordinates and checks if they are available.
bool CheckWon(char[][3], bool); //Prints a message who has won depending on the returned integer of CheckState().
int CheckState(char[][3]); //Checks the playing field and returns an integer depending on who has won/if its a draw/or if the game hasn't ended.
bool Exit(); //Asks the user if they want a rematch.

int main()
{
	do
	{
		string temp;
		bool player = true; //Dictates who's turn it is.
		bool mp = true; //Dictates if the player will be up against another player or an Ai.
		char field[3][3] = { '*','*','*','*','*','*','*','*','*' }; //Empty playing field that changes with player's input.
		Ai AiTurn; //Object that will play Ai's turn.
		WelcomeMsg(mp, player);
		while (!(CheckWon(field, mp)))
		{
			PrintField(field, mp);
			if (mp == true)
			{
				PlayerTurn(field, mp, player);
			}
			else
			{
				if (player)
					PlayerTurn(field, mp, player);
				else
				{
					AiTurn.AiMove(field, player);
					player = true;
				}
			}
			PrintField(field, mp);
		}
	} while (Exit());
}

void WelcomeMsg(bool & mp, bool & player)
{
	string temp;
	system("cls");
	cout << "Welcome to the game of Tic Tac Toe. To win the game a player must connect 3 of his/hers symbols in a horizontal,vertical or diagonal line. Good luck!" << endl;
	cout << "Would you like to play multyplayer? Y/y for yes or any other key for singleplayer." << endl;
	cout << "Your input: ";
	getline(cin, temp);
	if (temp[0] != 'y' && temp[0] != 'Y')
	{
		mp = false;
		cout << "Would you like to play first? Y/y for yes or any other key to play second." << endl;
		cout << "Your input: ";
		getline(cin, temp);
		if (temp[0] != 'y' && temp[0] != 'Y')
			player = false;
	}
}

void PrintField(char field[3][3], bool mp)
{
	system("cls");
	if (mp)
		cout << "Player 1: X" << "  " << "Player 2: O" << endl << endl;
	else
		cout << "Player: X" << "  " << "Computer: O" << endl << endl;
	cout << "    " << "1" << "   " << "2" << "   " << "3" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << i + 1 << "   ";
		for (int j = 0; j < 3; j++)
			cout << field[i][j] << "   ";
		cout << endl;
	}
	cout << endl << endl;
}

int CheckInput(string & temp)
{
	int temp_i;
	if (temp.size() > 1 || !(temp[0] >= '1' && temp[0] <= '3'))
	{
		cout << "Wrong input, please input a single number from 1 to 3: ";
		getline(cin, temp);
		CheckInput(temp);
	}
	else
		return temp_i = stoi(temp);
}

void PlayerTurn(char field[3][3], bool mp, bool & player)
{
	string temp;
	int r, c, turn;
	char symbol;
	if (mp)
	{
		if (player)
		{
			symbol = 'X';
			turn = 1;
		}
		else
		{
			symbol = 'O';
			turn = 2;
		}
		cout << "Player " << turn << "'s turn: " << symbol << endl;
	}
	else
	{
		symbol = 'X';
		cout << "Player's turn: " << symbol << endl;
	}
	do
	{
		cout << "Please input coordinates of row: ";
		getline(cin, temp);
		r = CheckInput(temp);
		cout << "Please input coordinates of column: ";
		getline(cin, temp);
		c = CheckInput(temp);
		if (field[r - 1][c - 1] != '*')
			cout << "Those coordinates are taken, please input new ones." << endl;
	} while (field[r - 1][c - 1] != '*');
	field[r - 1][c - 1] = symbol;
	player = !player;
}

bool CheckWon(char field[3][3], bool mp)
{
	int outcome = 0;
	outcome = CheckState(field);
	if (outcome == 0)
		return false;
	else if (outcome == 3)
	{
		cout << "The game is a draw." << endl;
		return true;

	}
	else if (outcome == 1)
	{
		if (mp)
			cout << "Player 1 has won the game!" << endl;
		else
			cout << "Player has won the game!" << endl;
		return true;
	}
	else if (outcome == 2)
	{
		if (mp)
			cout << "Player 2 has won the game!" << endl;
		else
			cout << "Computer has won the game!" << endl;
		return true;
	}
}

int CheckState(char field[3][3])
{
	if (field[0][0] == 'X' && field[0][1] == 'X' && field[0][2] == 'X')
		return 1;
	else if (field[1][0] == 'X' && field[1][1] == 'X' && field[1][2] == 'X')
		return 1;
	else if (field[2][0] == 'X' && field[2][1] == 'X' && field[2][2] == 'X')
		return 1;
	else if (field[0][0] == 'X' && field[1][0] == 'X' && field[2][0] == 'X')
		return 1;
	else if (field[0][1] == 'X' && field[1][1] == 'X' && field[2][1] == 'X')
		return 1;
	else if (field[0][2] == 'X' && field[1][2] == 'X' && field[2][2] == 'X')
		return 1;
	else if (field[0][0] == 'X' && field[1][1] == 'X' && field[2][2] == 'X')
		return 1;
	else if (field[0][2] == 'X' && field[1][1] == 'X' && field[2][0] == 'X')
		return 1;

	else if (field[0][0] == 'O' && field[0][1] == 'O' && field[0][2] == 'O')
		return 2;
	else if (field[1][0] == 'O' && field[1][1] == 'O' && field[1][2] == 'O')
		return 2;
	else if (field[2][0] == 'O' && field[2][1] == 'O' && field[2][2] == 'O')
		return 2;
	else if (field[0][0] == 'O' && field[1][0] == 'O' && field[2][0] == 'O')
		return 2;
	else if (field[0][1] == 'O' && field[1][1] == 'O' && field[2][1] == 'O')
		return 2;
	else if (field[0][2] == 'O' && field[1][2] == 'O' && field[2][2] == 'O')
		return 2;
	else if (field[0][0] == 'O' && field[1][1] == 'O' && field[2][2] == 'O')
		return 2;
	else if (field[0][2] == 'O' && field[1][1] == 'O' && field[2][0] == 'O')
		return 2;
	else
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (field[i][j] == '*')
					return 0;
			}
		}
		return 3;
	}
}

bool Exit()
{
	string temp;
	cout << "Would you like to play again? y/Y for yes or any other key for no." << endl;
	getline(cin, temp);
	if (temp[0] == 'y' || temp[0] == 'Y')
		return true;
	else
		return false;
}