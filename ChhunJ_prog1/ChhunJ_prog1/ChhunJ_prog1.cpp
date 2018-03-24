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
bool contains_MSG_ID(string lineFromFile);
string get_MSG_ID(string lineFromFile);
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

	string temp = "";
	int character; //to hold characters

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
			cout <<endl<< "lineFromFile = " + lineFromFile << endl << endl;

			/*2. Perform Logic to check if line contains msgID
			- If so, then build a substring that contains the ID,
			-Convert that substring into an integer and push into vector of SpamIDs
			*/
			if(contains_MSG_ID(lineFromFile))
			{
				//There is a msgID, now retrieve the ID and push into vector
				cout<<"TRUTHY retrieving msgID now"<<endl;
				temp = get_MSG_ID(lineFromFile);
				//DEBUG 
				cout <<" DISPLAYING substring that should contain messageID " << temp <<endl;
				cout<<"Pushing into vectorSpamIDS!"<<endl; 
				vectSpamIDs.push_back(stoi(temp));
			}//END IF
			//Then the line is not wrapped in <DOCID> xml tags, proceed with logic.
			else{

				/*3. Perform Logic to retrieve the body of the message
				-Ignore the Subject line
				*/
				//4. Perform Finite Automata Logic

				//5. Pop or do nothing to the msgID within the vector, this signals the msgID has been identified as SPAM or not.

				//Show Final State after processing the line
				printState(dfaState);
				//6. Reset dfaState and reset msgID

			}//END ELSE
		}
		file.close(); //close file
	}
	//DEBUG  - PRINT VECTORS
	printVectIDs(vectSpamIDs);

	//END
	system("pause"); //pause screen to show output
	return 0;
}
//PRINT FUNCTIONS
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
//FILE PARSING FUNCTIONS
bool contains_MSG_ID(string lineFromFile)
{
	string srch_MSGID = "msg",srch_DOCID = "</DOCID>"; 
	int temp = -1,temp2=-1;
	temp = lineFromFile.find("msg"); //search for starting index of 'msg'
	temp2 = lineFromFile.find("</DOCID>"); //search for DOCID string
	if((temp != -1) && (temp2 != -1)){return true;}
	return false;
}
string get_MSG_ID(string lineFromFile)
{
	//return a string containing the msgID 
	string temp = ""; 
	int messageID = -1, docID = -1;
	messageID = lineFromFile.find("msg"); //search for starting index of 'msg'
	docID = lineFromFile.find("</DOCID>"); //search for DOCID string
	temp = lineFromFile.substr(messageID+3, docID-1);
	return temp; //temp is the messageID as a string
}


//STATE BASED FUNCTIONS
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