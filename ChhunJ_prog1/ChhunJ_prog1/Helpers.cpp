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
	cout<<endl<<endl<<"Printing IDs of Emails identified as SPAM"<<endl;
	for(int i = 0; i < vect_spamIDs.size(); i++)
	{
		cout<<"spamID = " <<vect_spamIDs[i] <<endl;
	}
}
void Helpers::printFinalStates()
{
	cout<<"Called printFinalStates from Helper Class" <<endl;
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

bool Helpers::contains_isNotSubject(string lineFromFile)
{
	//Function will check if this line is the Subject:
	int temp = -1; 
	temp = lineFromFile.find("Subject:"); //search for 'Subject'
	if(temp != -1){return true;} //false, there is no subject stirng
	return false; 
}
bool Helpers::contains_isEndOfEmail(string lineFromFile)
{
	//Function will check if this line is the end of the Email
	int temp = -1; 
	temp = lineFromFile.find("</DOC>"); 
	if(temp != -1){return true;} 
	return false; 
}
bool Helpers::contains_isStartOfEmail(string lineFromFile)
{
	//Function checks if starting line
	int temp = -1;
	temp = lineFromFile.find("<DOC>");
	if(temp!= -1 ){return true;}
	return false;
}
bool Helpers::contains_quotes(string lineFromFile)
{
	int temp = -1; 
	temp = lineFromFile.find('"');
	if(temp == -1 ) {return false;}
	return true;
}
//GET FUNCTIONS
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
string Helpers::get_cleanString(string strCleanse)
{
int position = -1;
do
{
	position = strCleanse.find('"');
	strCleanse.erase(position,1); //erase single character
}while(strCleanse.find('"') != -1);
	return strCleanse ;
}
