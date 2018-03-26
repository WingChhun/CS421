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
	void printState(enum State currentState); //function for testing/debug, will print currentState
	void printVectIDs(vector<int> vectSpamIDs); // function will print the IDs of the emails identified as being SPAM
	void printFinalStates(); //function to print the Final states as numbers to the user

	//Truthy/Falsy functions, to determine what line is being read in the email

	bool contains_MSG_ID(string lineFromFile); // check if <DOCID> and 'msg' is present in the string, 
	bool contains_isStartOfEmail(string lineFromFile); //search for <DOC>
	bool contains_isNotSubject(string lineFromFile); //Check if 'Subject' is present, if so, return false to skip
	bool contains_isEndOfEmail(string lineFromFile); //check if </DOC>, end of the email
	bool contains_quotes(string lineFromFile); //check if string contains quotes, return false if doesnt, return true if does
	//get MSGID Functions
	string get_MSG_ID(string lineFromFile);
	string get_cleanString(string lineFromFile); //returns a string without double quotes
	//parse BODY functions

	//OTHER ADD LATER
};

