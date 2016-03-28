#include "stdafx.h"
#include "ValueStructure.h"
#include "Global.h"


// Create a value table and set all the values to 0.5
ValueTable::ValueTable(bool inverse)
	:valueArray{}, inverse{ inverse }
{
	valueArray.fill(0.5);
}

// Copy constructor for the class
ValueTable::ValueTable(const ValueTable& vs)
	: valueArray{}
{
	this->inverse = vs.inverse;
	this->valueArray = vs.valueArray;
}

ValueTable::~ValueTable()
{
}

// Get the value of the input state
float ValueTable::GetValue(const State& s)
{
	int index = ConvertToIndex(s);
	return valueArray[index];
}

// Update the value of the given state to newVal
void ValueTable::UpdateValue(const State& s, float newVaL)
{
	int index = ConvertToIndex(s);
	valueArray[index] = newVaL;
}

// Convert the given state to an index to be used with the value table
int ValueTable::ConvertToIndex(const State& s)
{
	State rs = s;
	// If inverse is true, change the places of 1's and 2's
	if (inverse)
		rs = Global::ReverseState(s);

	// Convert the state to an integer number
	int sum = 0;
	for (int i = 0; i < rs.size(); ++i)
		sum += s[i] * pow(3, i);

	return sum;
}

// Update the value of the pre state based on the value of the post state
// Value[oldState] = Value[oldS] + alpha * (Value[newState] - Value[oldState])
void ValueTable::Update(const State& pre, const State& post, float alpha)
{
	int indexPre = ConvertToIndex(pre);
	int indexPost = ConvertToIndex(post);

	valueArray[indexPre] += alpha * (valueArray[indexPost] - valueArray[indexPre]);
}

