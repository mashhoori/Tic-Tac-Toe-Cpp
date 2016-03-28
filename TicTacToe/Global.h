#pragma once
class Global
{

public:

	static default_random_engine generator;
	static uniform_real_distribution<float> realDist;

	// Change the places of 1's and 2's in the given state
	static State ReverseState(const State& s);

	// Print the given state
	static void PrintState(const State& s);

};

