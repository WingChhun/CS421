#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Helpers
{
public:
	Helpers(void);
	~Helpers(void);

	//PRINT FUNCTIONS
	void printState(enum State currentState); //function for testing
	void printVectIDs(vector<int> vectSpamIDs);
	//get MSGID Functions
	bool contains_MSG_ID(string lineFromFile);
	string get_MSG_ID(string lineFromFile);
	//parse BODY functions

	//OTHER ADD LATER
};

