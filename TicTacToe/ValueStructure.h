#pragma once
class ValueTable
{
private:
	bool inverse;
	Value valueArray;

public:	
	// Create a value table and set all the values to 0.5
	ValueTable(bool inverse = false);

	// Copy constructor for the class
	ValueTable(const ValueTable& vs);

	bool GetInverse() { return inverse; }
	void SetInverse(bool val) { inverse = val; }

	~ValueTable();

	// Get the value of the input state
	float GetValue(const State& s);

	// Update the value of the given state to newVal
	void UpdateValue(const State& s, float newVaL);

	// Convert the given state to an index to be used with the value table
	int ConvertToIndex(const State& s);

	// Update the value of the pre state based on the value of the post state
	void Update(const State& pre, const State& post, float alpha);

};

