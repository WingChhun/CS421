#include "stdafx.h"
#include "Helpers.h"




Helpers::Helpers(void)
{
}


Helpers::~Helpers(void)
{
}

//PRINT FUNCTIONS
void Helpers::printState(enum State currentState)
{
	cout <<"Showing State : " << currentState << endl;
}
void Helpers::printVectIDs(vector<int> vect_spamIDs)
{
	cout<<"Printing vector IDS!";
	for(int i = 0; i < vect_spamIDs.size(); i++)
	{
		cout<<"spamID = " <<vect_spamIDs[i] <<endl;
	}
}
//FILE PARSING FUNCTIONS
bool Helpers::contains_MSG_ID(string lineFromFile)
{
	string srch_MSGID = "msg",srch_DOCID = "</DOCID>"; 
	int temp = -1,temp2=-1;
	temp = lineFromFile.find("msg"); //search for starting index of 'msg'
	temp2 = lineFromFile.find("</DOCID>"); //search for DOCID string
	if((temp != -1) && (temp2 != -1)){return true;}
	return false;
}
string Helpers::get_MSG_ID(string lineFromFile)
{
	//return a string containing the msgID 
	string temp = ""; 
	int messageID = -1, docID = -1;
	messageID = lineFromFile.find("msg"); //search for starting index of 'msg'
	docID = lineFromFile.find("</DOCID>"); //search for DOCID string
	temp = lineFromFile.substr(messageID+3, docID-1);
	return temp; //temp is the messageID as a string
}
