#include "stdafx.h"
#include "Global.h"


// Change the places of 1's and 2's in the given state
State Global::ReverseState(const State& s)
{
	State sr = s;
	for (int i = 0; i < sr.size(); ++i)
	{
		if (sr[i] == 1)
			sr[i] = 2;
		else if (sr[i] == 2)
			sr[i] = 1;
	}

	return sr;
}

// Print the given state
void Global::PrintState(const State& state)
{
	for (int i = 0; i < state.size(); ++i)
	{
		if (i == 3 || i == 6)
			cout << "\n----------\n";


		if (state[i] == 1)
			cout << "X";
		else if (state[i] == 2)
			cout << "O";
		else
			cout << " ";


		if (i % 3 != 2)
			cout << " | ";
	}

	cout << "\n\n\n" << endl;
}


default_random_engine Global::generator{};
uniform_real_distribution<float> Global::realDist(0.0, 1.0);