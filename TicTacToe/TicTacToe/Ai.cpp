#include "Ai.h"
#include <iostream>
#include <vector>

using namespace std;

int CheckState(char[][3]); //Checks the playing field and returns an integer depending on who has won/if its a draw/or if the game hasn't ended.

void Ai::AiMove(char field[][3], bool player)
{
	Ai Temp;
	Temp = AiBestMove(field, player);
	field[Temp.x][Temp.y] = 'O';
}

Ai Ai::AiBestMove(char field[][3], bool player) //Gets the best possible move with MinMax algorithm.
{
	int victory = CheckState(field);
	if (victory == 1)
	{
		return Ai(-10); // 'X' has won return -10.
	}
	else if (victory == 2)
	{
		return Ai(10); // 'O' has won return 10.
	}
	else if (victory == 3)
	{
		return Ai(0); // It's a draw return 0.
	}
	char symbol;
	if (player == true)
		symbol = 'X';
	else
		symbol = 'O';
	/*
	Vector that holds moves for every node(first node is the computers turn, 2nd is the player's turn, etc.)
	*/
	vector <Ai> moves;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (field[i][j] == '*')
			{
				Ai move;
				move.x = i;
				move.y = j;
				field[i][j] = symbol;
				if (player)
					move.score = AiBestMove(field, false).score;
				else
					move.score = AiBestMove(field, true).score;
				/*
				When the game has gotten to an end state (won or draw) the move will get a score of 10/-10/0
				and will be put into a vector of moves for that node.
				*/
				moves.push_back(move);
				field[i][j] = '*';
			}
		}
	}
	/*
	Once all the moves are done for that node, one score will be picked from all of the moves in the node's moves vector
	depending on the player's turn in that node. If it was the computer's turn in that node the score will be highest possible,
	if it was the player's turn the score will be lowest possible.
	*/
	int bestMove = 0;
	if (player == false)
	{
		int bestScore = -100000;
		for (int i = 0; i < moves.size(); i++)
		{
			if (bestScore < moves[i].score)
			{
				bestScore = moves[i].score;
				bestMove = i;
			}
		}
	}
	else
	{
		int bestScore = 100000;
		for (int i = 0; i < moves.size(); i++)
		{
			if (bestScore > moves[i].score)
			{
				bestScore = moves[i].score;
				bestMove = i;
			}
		}
	}
	//Return the best move depending on the player's turn to the previous node.
	return moves[bestMove];
}