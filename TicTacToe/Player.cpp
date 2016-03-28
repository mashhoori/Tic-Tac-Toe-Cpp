#include "stdafx.h"
#include "ValueStructure.h"
#include "Player.h"
#include "Global.h"


// Create a computer player having the inputr player number and the given value table
Player::Player(int playerNumber, ValueTable valueStr)
	:playerNumber{ playerNumber }, state{}, valueStr{ valueStr }, isHuman{ false }
{
}

// Create a human player with the given player number
Player::Player(int playerNumber)
	: playerNumber{ playerNumber }, state{}, isHuman{ true }
{
}

Player::~Player()
{
}

// Update the current state of the player
void Player::UpdateState(State s)
{
	this->state = s;
}

// Get possible next moves for the input state
vector<State> Player::GetPossibleMoves(const State& current)
{
	vector<State> list; // list of possible next moves

	for (int i = 0; i < current.size(); ++i)
	{
		if (current[i] == 0) // if the position is empty
		{
			State s = current;
			s[i] = playerNumber;

			list.push_back(s);
		}
	}
	return list;
}

// Select the next greedy move for the current state of the player
State Player::SelectNextMove_Greedy()
{
	return SelectNextMove_Greedy(state);
}

// Select the next greedy move for the input state 
State Player::SelectNextMove_Greedy(const State& current)
{
	vector<State> list = GetPossibleMoves(current);
	vector<State> maxStates;

	float maxVal = -1;
	for (State s : list)
	{
		float val = valueStr.GetValue(s);
		if (val > maxVal)
		{
			maxVal = val;
			maxStates.clear();
			maxStates.push_back(s);
		}
		else if (val == maxVal)
			maxStates.push_back(s);
	}


	// Select randomly among greedy moves
	uniform_int_distribution<int> distribution(0, maxStates.size() - 1);
	int index = distribution(Global::generator);

	return maxStates[index];
}

// Select the next random move for the player's current state
State Player::SelectNextMove_Random()
{
	return SelectNextMove_Random(state);
}

// Select the next random move for the input state
State Player::SelectNextMove_Random(const State& current)
{
	vector<State> list = GetPossibleMoves(current);
	State best;

	// Select randomly among all possible moves
	uniform_int_distribution<int> distribution(0, list.size() - 1);
	int index = distribution(Global::generator);

	return list[index];
}

// Get the next input from the user
State Player::SelectNextMove_Human()
{
	State s = state;
	int pos;
	cout << "Enter the position (1-9): ";
	cin >> pos;

	while (pos < 1 || pos > 9 || state[pos - 1] != 0)
	{
		cout << "Invalid move! Enter the position again: ";
		cin >> pos;
	}

	s[pos - 1] = playerNumber;
	return s;
}

// Check if the input state is a winning state for the player
bool Player::CheckIfWon(const State& s)
{
	int playerNum = playerNumber;

	if ((s[0] == playerNum && s[1] == playerNum && s[2] == playerNum) ||
		(s[3] == playerNum && s[4] == playerNum && s[5] == playerNum) ||
		(s[6] == playerNum && s[7] == playerNum && s[8] == playerNum) ||
		(s[0] == playerNum && s[4] == playerNum && s[8] == playerNum) ||
		(s[2] == playerNum && s[4] == playerNum && s[6] == playerNum) ||
		(s[0] == playerNum && s[3] == playerNum && s[6] == playerNum) ||
		(s[1] == playerNum && s[4] == playerNum && s[7] == playerNum) ||
		(s[2] == playerNum && s[5] == playerNum && s[8] == playerNum))
		return true;

	return false;
}

// Check if the current state of the player is a winning state
bool Player::CheckIfWon()
{
	return CheckIfWon(state);
}

// Check if a move is possible based on the current player's state
bool Player::CheckIfAnyMoveLeft()
{
	for (int i = 0; i < state.size(); ++i)
		if (state[i] == 0)
			return true;

	return false;
}