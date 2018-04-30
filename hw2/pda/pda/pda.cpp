// pda.cpp : Defines the entry point for the console application.
/*
- pda.cpp : Programmed by James D. Chhun 
- Professor Rocio Guillen, CS421 - Theory of Computing - Spring 2018

-Purpose:
- This program simulates a pushdown automaton that determines whether a string of round ( ) and square [ ] or 'brackets', is a valid sentence
in the language of balanced parentheses. 

- This program makes use of the cpp 'stack' class and involves using functions such as push, pop, and top to implement the pushdown automaton.
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack> 

using namespace std;
//function prototypes
bool startPDA(stack<char> &PDA, int &currentState, string lineFromFile);
void emptyStackandReset(stack<char> &PDA, int &currentState, string &lineFromFile);
int _tmain(int argc, _TCHAR* argv[])
{
	//Initialize variables
	stack<char> PDA;
	int currentState = 0;  //variable for state
	ifstream File;
	string fileName = "input.txt";
	string lineFromFile =""; 


	PDA.push('z'); //push z into the stack, will be used to determine final state
	//open file
	File.open(fileName); 

	if(!File){cout<<"File does not exist!"<<endl;}
	else
	{
		cout <<"File with name of " << fileName << " exists!"<<endl<<"Parsing file... " << endl<<endl;
		while(!File.eof())//While not end of file
		{
			//get whole line from file, and pass line, stack, and currentState into startPDA function
			getline(File, lineFromFile);
			startPDA(PDA, currentState, lineFromFile);

			cout <<"Showing top of PDA " << PDA.top()<<endl;


			//END OF PDA for string 
			//emppty Stack and reset variables
			cout<<"Debug - CLEARING STACK " << endl;
			emptyStackandReset(PDA, currentState, lineFromFile); 
			cout <<"Debug - SHOWING TOP OF STACK, (SHOULD BE 'z')" << endl;
			cout<<"Top = " << PDA.top() << " Current State = " << currentState <<endl<<endl;

		}


	}
	File.close(); //close file
	//open file



	//END MAIN
	system("pause"); //for vscode
	return 0;
}

/*******END MAIN ***********/

bool startPDA(stack<char> &PDA, int &currentState, string lineFromFile)
{
	cout<<"Testing for line = " << lineFromFile<< " ... " <<endl;
	cout<<"Pushing Stuff into stack and changing state"<<endl<<endl;
	PDA.push('A');
	PDA.push('B');
	PDA.push('C');
	currentState = 1;

	//return true if string is accepted by the language
	if(currentState = 3){return true;} //state 3 is final
	//return false if string does not reach final state
	return false;
}

/*
Function to empty the stack, occurs at end of every PDA for each line of the file
*/
void emptyStackandReset(stack<char> &PDA, int &currentState, string &lineFromFile)
{
	//reset state and line from file
	currentState = 0;
	lineFromFile = "";
	//Clear stack, pop until empty
	while(!PDA.empty())
	{PDA.pop();}
	//Push 'z' into stack
	PDA.push('z');
}