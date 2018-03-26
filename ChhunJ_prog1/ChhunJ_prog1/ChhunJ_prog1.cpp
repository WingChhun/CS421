
/*
- ChhunJ_prog1.cpp
-Programmed by James D. Chhun
-Spring 2018, 3/22/2018 -> 3/25/2018 (completion date)
-Class CS421 - Theory of Computing by Rocio 

- This program parses through a file of email messages, these email  messages are wrapped and formatted in XML tags.
Within the program, the email messages are parsed for their message ID as well as body message, individual characters of the body message
are then passed into the FiniteAutomaton function, where a Deterministic Finite Automaton is simulated. This DFA has 45 states, 
state 44 and state 45 are the Final states, where state 45 is to accept string "win" and perform a check to see if to move onto state "winn", if not true, 
will always end back in state 44, as the final state. 
- Once this state is reached the email message has been identified as a SPAM message. Because this is a spam message
for every character that follows after reaching the final state, the state transition stays trapped within the final state because it is has been accepted.
- If the final state has been reached, a vector containing the message IDs parsed from the messages earlier will either keep the ID or pop the ID
from it's contents, at the end of the program the contents of the vector are displayed, where each element in the vector
is a ID identifying a SPAM email

- If want to change the file to be parsed, within the main, change filename to "<anyFileName within same directory"
- NOTES, there is a 'h' header file, this class is not required however it increases the modularity of the program as
- this main .cpp file is long and requires the enum States and State functions to be within it.
-README.md will be included
*
/*
Program charroduction up here

*/
//Header config
//#include "stdafx.h"
#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>

using namespace std; // allow ignore std:: prefix for output stream

// include helper class with functions that dont involve handling state


/*
Enum state config
- enum(States) will represent that current state the FA is in and wwill be used for transition fuinction outputs
*/
enum State {
	state_start,
	state_f, state_fr, state_fre, state_free, state_free_, 

	state_free_a, state_free_ac, state_free_acc,state_free_acce,state_free_access,
	state_free_s, state_free_so, state_free_sof, state_free_soft, state_free_softw, state_free_softwa, state_free_softwar, state_free_software,
	state_free_v, state_free_va, state_free_vac, state_free_vaca, state_free_vacat, state_free_vacati, state_free_vacatio, state_free_vacation,
	state_free_t, state_free_tr, state_free_tri, state_free_tria, state_free_trial, state_free_trials,

	state_w, state_wi, state_win, 
	state_winn, 
	state_winni, state_winnin, state_winning, state_winnings,
	state_winne, state_winner,
	state_winners, 

	//FINAL GOAL
	state_final, state_final_win
};


enum State start(char c); //same as state_start
//Enum state prototypes handling the string 'free'
enum State f(char c);
enum State fr(char c);
enum State fre(char c);
enum State free(char c);
enum State free_(char c);
//state prototypes handling free_access
enum State free_a(char c);
enum State free_ac(char c);
enum State free_acc(char c);
enum State free_acce(char c);
//enum State free_access(char c);
//state prototypes handling ree_software
enum State free_s(char c); 
enum State free_so(char c); 
enum State free_sof(char c); 
enum State free_soft(char c); 
enum State free_softw(char c);
enum State free_softwa(char c); 
enum State free_softwar(char c);
//enum State free_software(char c);
//state prototypes handling free_vacation
enum State free_v(char c); 
enum State free_va(char c);
enum State free_vac(char c); 
enum State free_vaca(char c); 
enum State free_vacat(char c); 
enum State free_vacati(char c); 
enum State free_vacatio(char c);
//enum State free_vacation(char c);
//state prortypes free_trials
enum State free_t(char c); 
enum State free_tr(char c); 
enum State free_tri(char c); 
enum State free_tria(char c); 
enum State free_trial(char c); 
//enum State free_trials(char c);
//FINAL
enum State final(char c);
enum State final_win(char c);

/*
- STATES free-win
*/
enum State w(char c);
enum State wi(char c);
enum State win(char c); 


/*
- STATES free-winnings
*/
enum State winn(char c); 
enum State winni(char c); 
enum State winnin(char c); 
enum State winning(char c); 
//enum State winnings(char c);

/*
- STATES free-winner(s)
*/
enum State winne(char c);
enum State winner(char c);
enum State winners(char c); 
//Main function prototypes
void printStateTransition(enum State currentState, char c);
void printLeftGrammar(vector<string> LeftGrammar);
void printState(enum State currentState); //function for testing/debug, will print currentState
	void printVectIDs(vector<string> vectSpamIDs); // function will print the IDs of the emails identified as being SPAM
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
//vector<string> LeftGrammar;
//Finite Automata prototype
void FiniteAutomata(char c); //accept a intacter
//Global State variable, will represent and hold the current/final state the input reaches

enum State dfaState = state_start; 


/* MAIN - Logic, Search for XML tags, perform appropriate action depending on which is read
- If <DOC> is read do nothing
- <DOCID> is read, expect MSGID
- 'Subject' read, do nothing, ignore line
- Else, then we should be reading body tag, perform LOGIC then
- </DOC> closing tag, then justify if the email is spam, perform LOGIC to show states reached
*/

/*2. Perform Logic to check if line contains msgID
- If so, then build a substring that contains the ID,
-Convert that substring into an integer and push into vector of SpamIDs
*/
int main() {

	//Object of Helpers Class, this will contain multiple functions not required to be in this main
	//Helpers helpers; 
	vector<string> vectSpamIDs; //vector will contain the the IDs of the emails that are identified as SPAM
	vector<State> vector_statesReached; //vector to contain all transition functions / states reached, print at end of each body parse

	string fileName = "messagefile.txt";
	string lineFromFile ="", temp = "", tempString = ""; //tempString will build a string of body lines

	int character; //to hold characters
	ifstream file;

	//START
	file.open("messagefile.txt");

	if (!file) {
		cout << "File with name " + fileName + " does not exist!" << endl << endl;
	} else {

		while (!file.eof()) {
			//1. Read Line from file
			getline(file, lineFromFile);

			if(contains_isStartOfEmail(lineFromFile))
			{			} // DO NOTHING
			else{
				//Then the line is not wrapped in <DOCID> xml tags, proceed with logic.
				if(contains_MSG_ID(lineFromFile))
				{
					//There is a msgID, now retrieve the ID and push into vector
					temp = get_MSG_ID(lineFromFile);
					vectSpamIDs.push_back(temp);
				}//END IF
				else if(contains_isNotSubject(lineFromFile))
				{}//DO NOTHING, IGNORE SUBJECT LINE
				//Final Check - is line </DOC> closing XML tag
				else if(contains_isEndOfEmail(lineFromFile))
				{

					int a = 0;
					//1. tempString is accumulated Body message, now remove quotes from it then pass into Finite Automaton
					//Search the string and remove all double quotes if any
					while(contains_quotes(tempString))
					{
						tempString = get_cleanString(tempString);
					}
					//2. If string passes FA, keep spamID inside vector, else pop it
					cout<<endl<<endl<<"Performing Finite Automata..."<<endl;
					cout <<tempString<<endl<<endl;
				

					//Pass character into Finite Automaton
					for( a = 0; a < tempString.length(); a++)
					{
						FiniteAutomata(tempString[a]);
					}
					//3. Determine if the Email is SPAM, and keep it in vector or pop it 
					if(dfaState != state_final && dfaState != state_final_win) 
					{//Once FA reaches state_final, FA stays there, so this will hold and we can determine to pop or push the ID
						//NOT SPAM POP FROM VECTOR
						vectSpamIDs.pop_back();
					}
					//4. reset tempString to be an emptyString for next emailParse
					tempString =""; 
					a = 0;
					dfaState = state_start;
				}
				else
				{
					//Build a single string, this will handle cases where multiple/incompleted lines in the email
					tempString += lineFromFile; 

				}

			}//END ELSE
		}
		file.close(); //close file
	}
	//DEBUG  - PRINT VECTORS
	printVectIDs(vectSpamIDs);
	//printLeftGrammar();
	//END
	//system("pause"); //pause screen to show output
	return 0;
}
void printStateTransition(enum State currentState, char c)
{
	cout <<"T( q"<<currentState<<", "<<c<<" ) =  "; //to be finished within state Function

}
//FINITE AUTOMATA
void FiniteAutomata(char  c)
{

	if(dfaState == state_start){dfaState == start(c);}
	else if((c == '\0' || c == ' ') && (dfaState == state_winner || dfaState == state_winnings || 
		dfaState == state_win || dfaState == state_free_trials || dfaState == state_free_software || 
		dfaState == state_free_access || dfaState == state_free_vacation))
	{dfaState = final(c);} 
	//start
	else if(dfaState == state_f){dfaState == f(c);}
	else if(dfaState == state_fr){dfaState == fr(c);}
	else if(dfaState == state_fre) {dfaState = fre(c);}
	else if(dfaState == state_free) {dfaState = free(c);}
	else if(dfaState == state_free_) {dfaState = free_(c);}
	//state prototypes handling free_access
	else if (dfaState == state_free_a){dfaState = free_a(c);}
	else if (dfaState == state_free_ac){dfaState = free_ac(c);}
	else if (dfaState == state_free_acc){dfaState = free_acc(c);}
	else if (dfaState == state_free_acce){dfaState = free_acce(c);}
	else if (dfaState == state_free_access){dfaState = final(c);}
	//state prototypes handling ree_software
	else if (dfaState == state_free_s){dfaState = free_s(c);} 
	else if (dfaState == state_free_so){dfaState = free_so(c);} 
	else if (dfaState == state_free_sof){dfaState = free_sof(c);} 
	else if (dfaState == state_free_soft){dfaState = free_soft(c);} 
	else if (dfaState == state_free_softw){dfaState = free_softw(c);}
	else if (dfaState == state_free_softwa){dfaState = free_softwa(c);} 
	else if (dfaState == state_free_softwar){dfaState = free_softwar(c);}
	else if (dfaState == state_free_software){dfaState = final(c);}
	//state prototypes handling free_vacation
	else if (dfaState == state_free_v){dfaState = free_v(c);} 
	else if (dfaState == state_free_va){dfaState = free_va(c);}
	else if (dfaState == state_free_vac){dfaState = free_vac(c);} 
	else if (dfaState == state_free_vaca){dfaState = free_vaca(c);} 
	else if (dfaState == state_free_vacat){dfaState = free_vacat(c);} 
	else if (dfaState == state_free_vacati){dfaState = free_vacati(c);} 
	else if (dfaState == state_free_vacatio){dfaState = free_vacatio(c);}
	else if (dfaState == state_free_vacation){dfaState = final(c);}
	//state prortypes free_trials
	else if (dfaState == state_free_t){dfaState = free_t(c);} 
	else if (dfaState == state_free_tr){dfaState = free_tr(c);} 
	else if (dfaState == state_free_tri){dfaState = free_tri(c);} 
	else if (dfaState == state_free_tria){dfaState = free_tria(c);} 
	else if (dfaState == state_free_trial){dfaState = free_trial(c);} 
	else if (dfaState == state_free_trials){dfaState = final(c);}
	//WIN STATES
	else if (dfaState == state_w){dfaState = w(c);}
	else if (dfaState == state_wi){dfaState = wi(c);}
	else if (dfaState == state_win){dfaState = final_win(c);} 
	else if(dfaState == state_final_win){dfaState = final_win(c);}
	//WINNINGS STATES
	else if (dfaState == state_winn){dfaState = winn(c);} 
	else if (dfaState == state_winni){dfaState = winni(c);} 
	else if (dfaState == state_winnin){dfaState = winnin(c);} 
	else if (dfaState == state_winning){dfaState = winning(c);} 
	else if (dfaState == state_winnings){dfaState = final(c);}
	//WINNER(S) STATES
	else if (dfaState == state_winne){dfaState = winne(c);}
	else if (dfaState == state_winner){
	
	 if (c){dfaState = winner(c);}
	 else{final(c);}
	}
	else if (dfaState == state_winners){dfaState = final(c);} 
	//FINAL CATCH ANY MISSED ERRORS

	else if (dfaState == state_final || dfaState == state_final_win)
	{
		//This was the goal, stop everything, the message has been identified as SPAM
		dfaState = final(c);
	}

}
void printLeftGrammar()
{
	

}
//PRINT FUNCTIONS
void printState(enum State currentState)
{
	cout <<"Showing State : " << currentState << endl;
}
void printVectIDs(vector<string> vect_spamIDs)
{
	cout<<endl<<endl<<"Printing IDs of Emails identified as SPAM"<<endl;
	for(int i = 0; i < vect_spamIDs.size(); i++)
	{
		cout<<"spamID = " <<vect_spamIDs[i] <<endl;
	}
}
void printFinalStates()
{
	cout<<"Called printFinalStates from Helper Class" <<endl;
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

bool contains_isNotSubject(string lineFromFile)
{
	//Function will check if this line is the Subject:
	int temp = -1; 
	temp = lineFromFile.find("Subject:"); //search for 'Subject'
	if(temp != -1){return true;} //false, there is no subject stirng
	return false; 
}
bool contains_isEndOfEmail(string lineFromFile)
{
	//Function will check if this line is the end of the Email
	int temp = -1; 
	temp = lineFromFile.find("</DOC>"); 
	if(temp != -1){return true;} 
	return false; 
}
bool contains_isStartOfEmail(string lineFromFile)
{
	//Function checks if starting line
	int temp = -1;
	temp = lineFromFile.find("<DOC>");
	if(temp!= -1 ){return true;}
	return false;
}
bool contains_quotes(string lineFromFile)
{
	int temp = -1; 
	temp = lineFromFile.find('"');
	if(temp == -1 ) {return false;}
	return true;
}
//GET FUNCTIONS
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
string get_cleanString(string strCleanse)
{
int position = -1;
do
{
	position = strCleanse.find('"');
	strCleanse.erase(position,1); //erase single character
}while(strCleanse.find('"') != -1);
	return strCleanse ;
}

//STATE BASED FUNCTIONS
enum State start(char c) {

	printStateTransition(dfaState,c);

	if (c == 'f') {

		dfaState = state_f;cout <<"q"<<state_f << ", ";

	}
	else if(c == 'w'){dfaState = state_w;cout <<"q"<<state_w << ", ";}
	else{dfaState = state_start;cout <<"q"<<state_start << ", "; //no change
	}
	return dfaState;
}
enum State f(char c) {

	printStateTransition(dfaState,c);

	if (c == 'r') {

		dfaState = state_fr;cout <<"q"<<state_fr << ", ";

	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State fr(char c) {

	printStateTransition(dfaState,c);

	if (c == 'e') {

		dfaState = state_fre;cout <<"q"<<state_fre << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State fre(char c) {

	printStateTransition(dfaState,c);

	if (c == 'e') {

		dfaState = state_free;cout <<"q"<<state_free << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State free(char c) {

	printStateTransition(dfaState,c);

	if (c == ' ') {
		dfaState = state_free_;cout <<"q"<<state_free_ << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State free_(char c) {
	printStateTransition(dfaState,c);

	if (c =='a') {dfaState = state_free_a;cout <<"q"<<state_free_a << ", ";} 
	else if(c =='s'){dfaState =state_free_s;cout <<"q"<<state_free_s << ", ";} //move onto software test 
	else if(c =='v'){dfaState =state_free_v;cout <<"q"<<state_free_v << ", ";} // move onto vacation test
	else if(c =='t'){dfaState =state_free_t;cout <<"q"<<state_free_t << ", ";} //move onto trials test
	else {dfaState = state_start;cout <<"q"<<state_start << ", ";} //fail
	return dfaState;
}
//state prototypes handling free_access
enum State free_a(char c)
{
	printStateTransition(dfaState,c);

	if (c =='c') {
		dfaState = state_free_ac;cout <<"q"<<state_free_ac << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State free_ac(char c)
{
	printStateTransition(dfaState,c);

	if (c =='c') {
		dfaState = state_free_acc;cout <<"q"<<state_free_acc << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State free_acc(char c)
{
	printStateTransition(dfaState,c);

	if (c =='e') {
		dfaState = state_free_acce;cout <<"q"<<state_free_acce << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State free_acce(char c)
{
	printStateTransition(dfaState,c);

	if (c =='s') {
		//FINAL STATE //DONE
		//cout<<endl<<"String 'free access' accepted"  << ", ";
		dfaState = state_final;cout <<"q"<<state_final << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}

//state prototypes handling ree_software
enum State free_s(char c)
{
	printStateTransition(dfaState,c);

	if (c =='o') {
		dfaState = state_free_so;cout <<"q"<<state_free_so << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_so(char c)
{
	printStateTransition(dfaState,c);

	if (c =='f') {
		dfaState = state_free_sof;cout <<"q"<<state_free_sof << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_sof(char c)
{
	printStateTransition(dfaState,c);

	if (c =='t') {
		dfaState = state_free_soft;cout <<"q"<<state_free_soft << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_soft(char c)
{
	printStateTransition(dfaState,c);

	if (c =='w') {
		dfaState = state_free_softw;cout <<"q"<<state_free_softw << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_softw(char c)
{
	printStateTransition(dfaState,c);

	if (c =='a') {
		dfaState = state_free_softwa;cout <<"q"<<state_free_softwa << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State free_softwa(char c)
{
	printStateTransition(dfaState,c);

	if (c =='r') {
		dfaState = state_free_softwar;cout <<"q"<<state_free_softwar << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_softwar(char c)
{
	printStateTransition(dfaState,c);

	if (c =='e') {
		//	cout<<endl<<"String 'free software' accepted"  << ", ";
		dfaState = state_final; cout <<"q"<<state_final << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}

//state prototypes handling free_vacation
enum State free_v(char c)
{
	printStateTransition(dfaState,c);

	if (c =='a') {
		dfaState = state_free_va;cout <<"q"<<state_free_va << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_va(char c)
{
	printStateTransition(dfaState,c);

	if (c =='c') {
		dfaState = state_free_vac;cout <<"q"<<state_free_vac << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State free_vac(char c)
{
	printStateTransition(dfaState,c);

	if (c =='a') {
		dfaState = state_free_vaca;cout <<"q"<<state_free_vaca << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_vaca(char c)
{
	printStateTransition(dfaState,c);

	if (c =='t') {
		dfaState = state_free_vacat;cout <<"q"<<state_free_vacat << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_vacat(char c)
{
	printStateTransition(dfaState,c);

	if (c =='i') {
		dfaState = state_free_vacati;cout <<"q"<<state_free_vacati << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_vacati(char c)
{
	printStateTransition(dfaState,c);

	if (c =='o') {
		dfaState = state_free_vacatio;cout <<"q"<<state_free_vacatio << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_vacatio(char c)
{
	printStateTransition(dfaState,c);

	if (c =='n') {
		//cout<<endl<<"String 'free vacation' accepted"  << ", ";
		dfaState = state_final; cout <<"q"<<state_final << ", ";
		//	dfaState = state_free_vacation;cout <<"q"<<state_free_vacation << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}

//state prortypes free_trials
enum State free_t(char c)
{
	printStateTransition(dfaState,c);

	if (c =='r') {
		dfaState = state_free_tr;cout <<"q"<<state_free_tr << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_tr(char c)
{
	printStateTransition(dfaState,c);

	if (c =='i') {
		dfaState = state_free_tri;cout <<"q"<<state_free_tri << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_tri(char c)
{
	printStateTransition(dfaState,c);

	if (c =='a') {
		dfaState = state_free_tria;cout <<"q"<<state_free_tria << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_tria(char c)
{
	printStateTransition(dfaState,c);

	if (c =='l') {
		dfaState = state_free_trial;cout <<"q"<<state_free_trial << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State free_trial(char c)
{
	printStateTransition(dfaState,c);

	if (c =='s') {
		//cout<<endl<<"String 'free trals' accepted"  << ", ";
		dfaState = state_final; cout <<"q"<<state_final << ", ";
		//dfaState = state_free_trials;cout <<"q"<<state_free_trials << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 

/*
- STATES free-win
*/
enum State w(char c)
{
	printStateTransition(dfaState,c);

	if (c =='i') {
		dfaState = state_wi;cout <<"q"<<state_wi << ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State wi(char c)
{
	printStateTransition(dfaState,c);

	if (c =='n') {
		dfaState = state_final_win;cout <<"q"<< state_final_win<< ", ";
	} else {dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State win(char c)
{

	printStateTransition(dfaState,c);

	if (c =='n'){
		//cout<<endl<<"String 'free win' accepted"  << ", ";
		dfaState = state_winn;cout <<"q"<<state_winn << ", ";	
	}
	else{dfaState = state_start;cout <<"q"<<state_start << ", ";}
	return dfaState;
} 


/*
- STATES free-winnings
*/
enum State winn(char c)
{
	printStateTransition(dfaState,c);

	if (c =='i') {
		dfaState = state_winni;cout <<"q"<<state_winni << ", ";
	}
	else if(c =='e'){dfaState = state_winne;cout <<"q"<<state_winne << ", ";}
	else {dfaState = state_start;}
	return dfaState;
} 
enum State winni(char c)
{
	printStateTransition(dfaState,c);

	if (c =='n') {
		dfaState = state_winnin;
		cout <<"q"<<state_winnin << ", ";
	} else {dfaState = state_start;
	cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State winnin(char c)
{
	printStateTransition(dfaState,c);

	if (c =='g') {
		dfaState = state_winning;
		cout <<"q"<<state_winning << ", ";
	} else {dfaState = state_start;
	cout <<"q"<<state_start << ", ";}
	return dfaState;
} 
enum State winning(char c)
{
	printStateTransition(dfaState,c);

	if (c =='s') {
		//cout<<endl<<"String 'winnings' accepted"  << ", ";
		dfaState = state_final; cout <<"q"<<state_final << ", ";

	} 
	else {dfaState = state_start;
	cout <<"q"<<state_start << ", ";}
	return dfaState;

}
/*
- STATES free-winner(s)
*/
enum State winne(char c)
{
	printStateTransition(dfaState,c);

	if (c =='r') {
		dfaState = state_winner;
		cout <<"q"<<state_winner << ", ";
	} else {dfaState = state_start;
	cout <<"q"<<state_start << ", ";}
	return dfaState;
}
enum State winner(char c)
{
	printStateTransition(dfaState,c);
	//100% this is accepted

	if (c =='s' || c == '\n' || c == '\0' || c == ' ' ) {
		//cout <<endl<<"q"<<"String 'winners' accepted"  << ", ";
		dfaState = state_final;}
	else if (!(c =='s')){dfaState = state_start;}
	else{dfaState = state_final;}
	cout <<"q"<<state_final << ", ";


	return dfaState;
}


//FINAL
enum State final(char c)
{
	printStateTransition(dfaState, c);
	cout <<"qF" <<",  " ;
	dfaState = state_final;
	return dfaState;
}
enum State final_win(char c)
{
	printStateTransition(dfaState,c);

	if(c == 'n'){dfaState = state_winn;
	cout <<"q"<<state_winn << ", ";
	}
	else if(c ='\0' || c == ' ')
	{
		dfaState = state_final;// immutable now
		cout <<"qF_W"<<",  ";
	}
	else
	{
		dfaState = state_start;
	}

	return dfaState;

}