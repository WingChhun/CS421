// ChhunJ_prog1.cpp : Defines the entry point for the console application.
//
/*
Program introduction up here

*/
//Header config
#include "stdafx.h"
#include < iostream > 
#include < fstream > 
#include < string > 
#include < stack >
#include < vector >

using namespace std; // allow ignore std:: prefix for output stream


/*
Enum state config
- enum(States) will represent that current state the FA is in and wwill be used for transition fuinction outputs
*/
enum State {
	state_start,
	state_f,
	state_fr,
	state_fre,
	state_free
};

void printState(enum State currentState); //function for testing
void printVectIDs(vector<int> vectSpamIDs);
enum State start(int c); //same as state_start
//Enum state prototypes handling the string 'free'
enum State f(int c);
enum State fr(int c);
enum State fre(int c);
enum State free(int c);
//Main function prototypes

enum State dfaState = state_start; //Global State variable, will represent and hold the current/final state the input reaches

//Function declarations
int _tmain(int argc, _TCHAR * argv[]) {

	vector<int> vectSpamIDs; //vector will contain the the IDs of the emails that are identified as SPAM
	string fileName = "testIDs.txt";
	string lineFromFile ="";
	string srch_MSGID = "msg",srch_DOCID = "</DOCID>"; //will be used to search for msgIDs within XML tags of email
	int character,messageID = -1, docID =-1; //to hold characters

	ifstream file;
	file.open(fileName);

	if (!file) {
		cout << "File with name " + fileName + " does not exist!" << endl << endl;
	} else {
		//Perform file handling
		//while not end of file
		while (!file.eof()) {
			//1. Read Line from file
			getline(file, lineFromFile);

			//debug - test - show output
			cout << "lineFromFile = " + lineFromFile << endl << endl;

			//2. Perform Logic to store the msgID into vectorArray if !(-1)
			cout <<"starter messageID " << messageID <<endl;
			messageID = lineFromFile.find(srch_MSGID); //search for starting index of 'msg'
			docID = lineFromFile.find(srch_DOCID); //search for DOCID string
			cout<<"The starting index of 'msg' is " << messageID <<endl;
			cout <<"The starting index of </DOCID> is " <<docID <<endl;
			if(messageID == -1){cout<<"Do nothing, message ID is invalid! " << messageID<<endl;}
			else{cout<<"Pushing into vectorSpamIDS!"<<endl;vectSpamIDs.push_back(messageID);} //push into vector
			//3. Perform Logic to retrieve the body of the message

			//4. Perform Finite Automata Logic

			//5. Pop or do nothing to the msgID within the vector, this signals the msgID has been identified as SPAM or not.

			//Show Final State after processing the line

			//6. Reset dfaState and reset msgID
			messageID = -1; //reset
			printState(dfaState);
			
		}
		file.close(); //close file
	}
	//DEBUG  - PRINT VECTORS
	printVectIDs(vectSpamIDs);

	//END
	cout << "Hello world testing" << endl << endl;
	system("pause"); //pause screen to show output
	return 0;
}
void printState(enum State currentState)
{
	cout <<"Showing State : " << currentState << endl;
}
void printVectIDs(vector<int> vect_spamIDs)
{
	cout<<"Printing vector IDS!";
	for(int i = 0; i < vect_spamIDs.size(); i++)
	{
		cout<<"spamID = " <<vect_spamIDs[i] <<endl;
	}
}
//enum Based Functions for state
enum State start(int c) {
	if (c == 'f') {
		dfaState = state_f;
	}
	return dfaState;
}
enum State f(int c) {
	if (c == 'r') {
		dfaState = state_fr;
	} else dfaState = state_start;
	return dfaState;
}
enum State fr(int c) {
	if (c == 'e') {
		dfaState = state_fre;
	} else dfaState = state_start;
	return dfaState;
}
enum State fre(int c) {
	if (c == 'e') {
		dfaState = state_free;
	} else dfaState = state_start;
	return dfaState;
}
enum State free(int c) {
	//For now test, see if can reach state free
	cout << "I AM IN STATE FREE, current input character = " + c << endl;
	return dfaState;
}