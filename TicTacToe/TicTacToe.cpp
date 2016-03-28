
#include "stdafx.h"
#include "ValueStructure.h"
#include "Player.h"
#include "Global.h"

/* Sets up matches betweeb human and computer 
 vs1 is the structure holding the values for the first player
 vs2 is the structure holding the values for the second player */
void Play(const ValueTable& vs1, const ValueTable& vs2)
{
	// Play the game until the user inputs zero to end the game
	while (1)
	{
		// Select the first player or exit the game 
		cout << "Who Plays first (H/C/0 to exit)? ";
		char c;
		cin >> c;

		// Exit if the user enters zero
		if (c == '0')
			return;

		Player* playerArray[2];
		if (c == 'H' || c == 'h') // If the first player is human
		{
			Player p1(2, vs2);
			Player p2(1);
			playerArray[0] = &p2;
			playerArray[1] = &p1;
		}
		else  // If the first player is computer
		{
			Player p1(1, vs1);
			Player p2(2);
			playerArray[0] = &p1;
			playerArray[1] = &p2;			
		}

		bool gameEnded = false;

		while (1)
		{
			// Alternate between users
			for (int playerIndex = 0; playerIndex < 2; ++playerIndex)
			{
				// Check if it is possible to make a move
				if (!playerArray[playerIndex]->CheckIfAnyMoveLeft())
				{
					// If there is no move left and no player has won, it is a draw!
					cout << "It is a draw!" << endl;
					gameEnded = true;
					break;
				}

				/* If the current player is human, get the next move from the user. Otherwise, 
				computer selects the next greedy move */
				State newS;
				if (playerArray[playerIndex]->IsHuman()) // If current player is human
					newS = playerArray[playerIndex]->SelectNextMove_Human();
				else  // If current player is computer				
					newS = playerArray[playerIndex]->SelectNextMove_Greedy();

				// Print the new state
				Global::PrintState(newS);

				// Update the state for both players
				playerArray[0]->UpdateState(newS);
				playerArray[1]->UpdateState(newS);

				// Check to see if the current player has won
				if (playerArray[playerIndex]->CheckIfWon())
				{
					if (playerArray[playerIndex]->IsHuman())
						cout << "You Won!" << endl;
					else
						cout << "Computer Won!" << endl;
					
					gameEnded = true;
					break;
				}
			}

			if (gameEnded)
				break;
		}
	}
}

/* Trains the players by reinforcement learning 
 vs1 is the structure holding the values for the first player
 vs2 is the structure holding the values for the second player */
void Train(ValueTable& vs1, ValueTable& vs2)
{
	// Play thousands of games to train the players
	for (int iter = 0; iter < 30000; ++iter)
	{
		// Instantiate the first and the second players
		Player p1(1, vs1); 
		Player p2(2, vs2);
		array<Player, 2> playerArray{ p1, p2 };

		float eps = 0.2;   // The probability of selecting a random move
		float alpha = 0.1; // Learing rate
		bool gameEnded = false;

		while (1) // loops until a single game ends
		{
			// Alternate between users
			for (int playerIndex = 0; playerIndex < 2; ++playerIndex)  
			{
				// Check if it is possible to make a move
				if (!playerArray[playerIndex].CheckIfAnyMoveLeft())
				{
					gameEnded = true;
					break;
				}

				// Get the current state of the game 
				State oldS = playerArray[playerIndex].GetState();
				State newS;

				float rand = Global::realDist(Global::generator);
				bool greedy = true;
				if (rand < eps)
				{
					// Select the next move randomly 
					newS = playerArray[playerIndex].SelectNextMove_Random();
					greedy = false;
				}
				else
					// Select the next move greedily
					newS = playerArray[playerIndex].SelectNextMove_Greedy();

				// Update the state for both players
				playerArray[0].UpdateState(newS);
				playerArray[1].UpdateState(newS);

				// Check if the current player has won
				if (playerArray[playerIndex].CheckIfWon())
				{
					/* If the current player wins, the other player looses.
					   Update the value table for each player according to result of the game */
					playerArray[0].GetValueStructure().UpdateValue(newS, 1 - playerIndex);
					playerArray[1].GetValueStructure().UpdateValue(newS, playerIndex);
					gameEnded = true;
				}

				// If the move was greedy, update the value table for players.
				if (greedy)
				{
					// Value[oldS] = Value[oldS] + alpha * (Value[newS] - Value[oldS])
					playerArray[0].GetValueStructure().Update(oldS, newS, alpha);
					playerArray[1].GetValueStructure().Update(oldS, newS, alpha);

					if (gameEnded)
						break;
				}
			}

			if (gameEnded)
				break;
		}

		vs1 = playerArray[0].GetValueStructure();
		vs2 = playerArray[1].GetValueStructure();
	}
}

int main()
{
	// Create two value tables. One for the first player and the other or the second player.
	ValueTable vs1{};
	ValueTable vs2{};

	// Train the players and update the value tables.	
	Train(vs1, vs2);

	// Play against human
	Play(vs1, vs2);

	getchar();
	return 0;
}

