#pragma once


class Player
{
private:
	int playerNumber;
	bool isHuman;
	State state;
	ValueTable valueStr;

public:
	
	// Create a computer player having the inputr player number and the given value table
	Player(int playerNumbe, ValueTable valueStr);

	// Create a human player with the given player number
	Player(int playerNumber);

	~Player();

	ValueTable& GetValueStructure() {  return valueStr;	}

	// Select the next greedy move for the current state of the player
	State SelectNextMove_Greedy();
	// Select the next greedy move for the input state 
	State SelectNextMove_Greedy(const State& current);

	// Select the next random move for the player's current state
	State SelectNextMove_Random();
	// Select the next random move for the input state
	State SelectNextMove_Random(const State& current);

	// Get the next input from the user
	State SelectNextMove_Human();

	// Update the current state of the player
	void UpdateState(State s);
	State GetState() { return state; }

	// Get possible next moves for the input state
	vector<State> GetPossibleMoves(const State& current);

	// Check if the current state of the player is a winning state
	bool CheckIfWon();	
	// Check if the input state is a winning state for the player
	bool CheckIfWon(const State& current);
	
	// Check if a move is possible based on the current player's state
	bool CheckIfAnyMoveLeft();

	bool IsHuman() { return isHuman; }
};

