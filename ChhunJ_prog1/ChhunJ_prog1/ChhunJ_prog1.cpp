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

// include helper class with functions that dont involve handling state
#include "Helpers.h";

/*
Enum state config
- enum(States) will represent that current state the FA is in and wwill be used for transition fuinction outputs
*/
enum State {
	state_start,
	state_f, state_fr, state_fre, state_free, state_free_, 
	//States involving free + word
	state_free_a, state_free_ac, state_free_acc,state_free_acce,state_free_access,
	state_free_s, state_free_so, state_free_sof, state_free_soft, state_free_softw, state_free_softwa, state_free_softwar, state_free_software,
	state_free_v, state_free_va, state_free_vac, state_free_vaca, state_free_vacat, state_free_vacati, state_free_vacatio, state_free_vacation,
	state_free_t, state_free_tr, state_free_tri, state_free_tria, state_free_trial, state_free_trials,
	//states involving WIN
	state_w, state_wi, state_win, 
	state_winn, 
	state_winni, state_winnin, state_winning, state_winnings,
	state_winne, state_winner,
	state_winners, 

	//FINAL GOAL
	state_final
};

enum State start(int c); //same as state_start
//Enum state prototypes handling the string 'free'
enum State f(int c);
enum State fr(int c);
enum State fre(int c);
enum State free(int c);
enum State free_(int c);
//state prototypes handling free_access
enum State free_a(int c);
enum State free_ac(int c);
enum State free_acc(int c);
enum State free_acce(int c);
enum State free_access(int c);
//state prototypes handling ree_software
enum State free_s(int c); 
enum State free_so(int c); 
enum State free_sof(int c); 
enum State free_soft(int c); 
enum State free_softw(int c);
enum State free_softwa(int c); 
enum State free_softwar(int c);
enum State free_software(int c);
//state prototypes handling free_vacation
enum State free_v(int c); 
enum State free_va(int c);
enum State free_vac(int c); 
enum State free_vaca(int c); 
enum State free_vacat(int c); 
enum State free_vacati(int c); 
enum State free_vacatio(int c);
enum State free_vacation(int c);
//state prortypes free_trials
enum State free_t(int c); 
enum State free_tr(int c); 
enum State free_tri(int c); 
enum State free_tria(int c); 
enum State free_trial(int c); 
enum State free_trials(int c);
//FINAL
enum State final(int c);

/*
- STATES free-win
*/
enum State w(int c);
enum State wi(int c);
enum State win(int c); 


/*
- STATES free-winnings
*/
enum State winn(int c); 
enum State winni(int c); 
enum State winnin(int c); 
enum State winning(int c); 
enum State winnings(int c);

/*
- STATES free-winner(s)
*/
enum State winne(int c);
enum State winner(int c);
enum State winners(int c); 
//Main function prototypes

enum State dfaState = state_start; //Global State variable, will represent and hold the current/final state the input reaches

//Function declarations
int _tmain(int argc, _TCHAR * argv[]) {

	Helpers helpers; //object of Helpers class
	vector<int> vectSpamIDs; //vector will contain the the IDs of the emails that are identified as SPAM
	string fileName = "testIDs.txt";
	string lineFromFile ="";
	string temp = "";
	int character; //to hold characters

	ifstream file;

	//Start	
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
			if(helpers.contains_MSG_ID(lineFromFile))
			{
				//There is a msgID, now retrieve the ID and push into vector
				cout<<"TRUTHY retrieving msgID now"<<endl;
				temp = helpers.get_MSG_ID(lineFromFile);
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
				helpers.printState(dfaState);
				//6. Reset dfaState and reset msgID

			}//END ELSE
		}
		file.close(); //close file
	}
	//DEBUG  - PRINT VECTORS
	helpers.printVectIDs(vectSpamIDs);

	//END
	system("pause"); //pause screen to show output
	return 0;
}

//
////PRINT FUNCTIONS
//void printState(enum State currentState)
//{
//	cout <<"Showing State : " << currentState << endl;
//}
//void printVectIDs(vector<int> vect_spamIDs)
//{
//	cout<<"Printing vector IDS!";
//	for(int i = 0; i < vect_spamIDs.size(); i++)
//	{
//		cout<<"spamID = " <<vect_spamIDs[i] <<endl;
//	}
//}
////FILE PARSING FUNCTIONS
//bool contains_MSG_ID(string lineFromFile)
//{
//	string srch_MSGID = "msg",srch_DOCID = "</DOCID>"; 
//	int temp = -1,temp2=-1;
//	temp = lineFromFile.find("msg"); //search for starting index of 'msg'
//	temp2 = lineFromFile.find("</DOCID>"); //search for DOCID string
//	if((temp != -1) && (temp2 != -1)){return true;}
//	return false;
//}
//string get_MSG_ID(string lineFromFile)
//{
//	//return a string containing the msgID 
//	string temp = ""; 
//	int messageID = -1, docID = -1;
//	messageID = lineFromFile.find("msg"); //search for starting index of 'msg'
//	docID = lineFromFile.find("</DOCID>"); //search for DOCID string
//	temp = lineFromFile.substr(messageID+3, docID-1);
//	return temp; //temp is the messageID as a string
//}

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
	if (c == ' ') {
		dfaState = state_free_;
	} else dfaState = state_start;
	return dfaState;
}
enum State free_(int c) {
	if (c == 'a') {dfaState = state_free_;} 
	else if(c == 's'){dfaState =state_free_s;} //move onto software test 
	else if(c == 'v'){dfaState =state_free_v;} // move onto vacation test
	else if(c == 't'){dfaState =state_free_t;} //move onto trials test
	else dfaState = state_start; //fail
	return dfaState;
}
//state prototypes handling free_access
enum State free_a(int c)
{
	if (c == 'c') {
		dfaState = state_free_ac;
	} else dfaState = state_start;
	return dfaState;
}
enum State free_ac(int c)
{
	if (c == 'c') {
		dfaState = state_free_acc;
	} else dfaState = state_start;
	return dfaState;
}
enum State free_acc(int c)
{
	if (c == 'e') {
		dfaState = state_free_acce;
	} else dfaState = state_start;
	return dfaState;
}
enum State free_acce(int c)
{
	if (c == 's') {
		dfaState = state_free_access;
	} else dfaState = state_start;
	return dfaState;
}
enum State free_access(int c)
{
	//FINAL STATE //DONE
	cout<<"String 'free access' accepted" <<endl;
	dfaState = state_final;
	return dfaState;
}
//state prototypes handling ree_software
enum State free_s(int c)
{
	if (c == 'o') {
		dfaState = state_free_so;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_so(int c)
{
	if (c == 'f') {
		dfaState = state_free_sof;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_sof(int c)
{
	if (c == 't') {
		dfaState = state_free_soft;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_soft(int c)
{
	if (c == 'w') {
		dfaState = state_free_softw;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_softw(int c)
{
	if (c == 'a') {
		dfaState = state_free_softwa;
	} else dfaState = state_start;
	return dfaState;
}
enum State free_softwa(int c)
{
	if (c == 'r') {
		dfaState = state_free_softwar;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_softwar(int c)
{
	if (c == 'e') {
		dfaState = state_free_software;
	} else dfaState = state_start;
	return dfaState;
}
enum State free_software(int c)
{
	//FINAL STATE DONE
	cout<<"String 'free software' accepted" <<endl;
	dfaState = state_final;
	return dfaState;
}
//state prototypes handling free_vacation
enum State free_v(int c)
{
	if (c == 'a') {
		dfaState = state_free_va;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_va(int c)
{
	if (c == 'c') {
		dfaState = state_free_vac;
	} else dfaState = state_start;
	return dfaState;
}
enum State free_vac(int c)
{
	if (c == 'a') {
		dfaState = state_free_vaca;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_vaca(int c)
{
	if (c == 't') {
		dfaState = state_free_vacat;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_vacat(int c)
{
	if (c == 'i') {
		dfaState = state_free_vacati;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_vacati(int c)
{
	if (c == 'o') {
		dfaState = state_free_vacatio;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_vacatio(int c)
{
	if (c == 'n') {
		dfaState = state_free_vacation;
	} else dfaState = state_start;
	return dfaState;
}
enum State free_vacation(int c)
{
	//FINAL STATE, prompt
	cout <<"String 'free vacation' accepted " <<endl<<endl;
	dfaState = state_final;
	return dfaState;
}
//state prortypes free_trials
enum State free_t(int c)
{
	if (c == 'r') {
		dfaState = state_free_tr;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_tr(int c)
{
	if (c == 'i') {
		dfaState = state_free_tri;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_tri(int c)
{
	if (c == 'a') {
		dfaState = state_free_tria;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_tria(int c)
{
	if (c == 'l') {
		dfaState = state_free_trial;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_trial(int c)
{
	if (c == 's') {
		dfaState = state_free_trials;
	} else dfaState = state_start;
	return dfaState;
} 
enum State free_trials(int c)
{
	//FINAL PROMPT
	cout <<"String 'free trials' accepted" <<endl<<endl;
	dfaState = state_final;
	return dfaState;
}

/*
- STATES free-win
*/
enum State w(int c)
{
	if (c == 'i') {
		dfaState = state_wi;
	} else dfaState = state_start;
	return dfaState;
}
enum State wi(int c)
{
	if (c == 'n') {
		dfaState = state_win;
	} else dfaState = state_start;
	return dfaState;
}
enum State win(int c)
{
	if (c == 'n') {
		dfaState = state_winn;
	} else dfaState = state_start;
	return dfaState;
} 


/*
- STATES free-winnings
*/
enum State winn(int c)
{
	if (c == 'i') {
		dfaState = state_winni;
	}
	else if(c == 'e'){dfaState = state_winne;}
	else dfaState = state_start;
	return dfaState;
} 
enum State winni(int c)
{
	if (c == 'n') {
		dfaState = state_winnin;
	} else dfaState = state_start;
	return dfaState;
} 
enum State winnin(int c)
{
	if (c == 'g') {
		dfaState = state_winning;
	} else dfaState = state_start;
	return dfaState;
} 
enum State winning(int c)
{
	if (c == 's') {
		dfaState = state_winnings;
	} 
	else dfaState = state_start;
	return dfaState;
} 
enum State winnings(int c)
{
	if (c == ' ') {
		cout <<"String 'winnings' accepted" <<endl<<endl;
		dfaState = state_final;
	} else dfaState = state_start;
	return dfaState;
}

/*
- STATES free-winner(s)
*/
enum State winne(int c)
{
	if (c == 'r') {
		dfaState = state_winner;
	} else dfaState = state_start;
	return dfaState;
}
enum State winner(int c)
{
	if(c == ' '){
		cout <<"String 'winner' accepted"<<endl<<endl;
		dfaState = state_final;}
	else if (c == 's') {
		dfaState = state_winners;
	} else dfaState = state_start;
	return dfaState;
}
enum State winners(int c)
{
	if (c == ' ') {
		cout <<"String 'winners' accepted"<<endl<<endl;
		dfaState = state_final;
	} else dfaState = state_start;
	return dfaState;
}

//FINAL
enum State final(int c)
{

	cout<<"Reached state_final, returning state_final as dfaState" <<endl;
	dfaState = state_final;
	return dfaState;
}