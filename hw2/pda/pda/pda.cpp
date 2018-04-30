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
bool startPDA(int currentState, string lineFromFile);
void emptyStack(stack<char> &PDA);
void notAccepted(string lineFromFile);
void Accepted(string lineFromFile);
void showStack(stack<char> PDA);

//MAIN

int _tmain(int argc, _TCHAR* argv[])
{
	//Initialize variables

	int currentState = 0;  //variable for state
	ifstream File;
	string fileName = "input.txt";
	string lineFromFile =""; 


	//open file
	File.open(fileName); 

	if(!File){cout<<"File does not exist!"<<endl;}
	else
	{
		cout <<"File with name of " << fileName << " exists!"<<endl<<"Parsing file... " << endl<<endl;
		while(!File.eof())//While not end of file
		{

			//Reset
			currentState = 0;
			lineFromFile = "";
			//get whole line from file, and pass line, stack, and currentState into startPDA function
			getline(File, lineFromFile);
			if(lineFromFile.empty())
			{
				notAccepted(lineFromFile);
			}
			else
			{
				startPDA(currentState, lineFromFile);
			}


		}//end while


	}//end else
	File.close(); //close file
	//open file



	//END MAIN
	system("pause"); //for vscode
	return 0;
}

/*******END MAIN ***********/

bool startPDA(int currentState, string lineFromFile)
{

	stack<char> PDA;
	int i = 0;
	char temp;
	PDA.push('z');
	cout <<"Current Line = " << lineFromFile << " ... "<<endl;

	if(lineFromFile.empty() && PDA.top() == 'z')
	{
		currentState = 0;
		cout<<"Line is empty"<<endl;
	}
	else
	{
		//Loop through each character of the lineFromFile, perform an action
		for(i = 0; i < lineFromFile.length(); i++)
		{
			temp = lineFromFile[i]; 
			//SWITCH: Perform action depending on what character is read
			switch(temp)
			{
			case '(':
				if(currentState == 0)
				{
					PDA.push(temp);
				}
				else if(currentState == 1)
				{
					//Push and change state back to 0
					PDA.push(temp);
					currentState = 0;
				}
				break;
			case '[':
				if(currentState == 0)
				{
					PDA.push(temp);
				}
				else if(currentState == 1)
				{ //push and change state back to 0
					PDA.push(temp);
					currentState = 0; 
				}
				break;

			case ')':

				if(currentState == 0 && (PDA.top() ='('))
				{
					PDA.pop(); //pop top of stack b/c matching parentheses
					currentState = 1; //change state
				}
				else if(currentState == 1 && (PDA.top() ='('))
				{
					PDA.pop(); //pop top of stack b/c matching parentheses
					currentState = 1; //change state
				}
				else if(PDA.top() == '[' || PDA.top() == 'z')
				{
					cout <<"Fail"<<endl;
					notAccepted(lineFromFile);
					return false;
				}
				break;

			case ']':
				if(PDA.top() == '(' || PDA.top() == 'z')
				{
					cout <<"Fail"<<endl;
					notAccepted(lineFromFile);
					return false;
				}
				else if((currentState == 0 || currentState ==1)  && (PDA.top() ='['))
				{
					PDA.pop(); //pop top of stack b/c matching parentheses
					currentState = 1; //change state
				}
				else if(currentState == 1 && (PDA.top() ='['))
				{
					PDA.pop(); //pop top of stack b/c matching parentheses
					currentState = 1; //change state
				}

				break;
			default:
				break;
			}//END SWITCH

		}// END LOOP
	}//END ELSE

	//DEBUG - PEEK TOP
	cout<<"Top of the stack after PDA is " << PDA.top() <<endl;
	showStack(PDA);
	//If top of stack is 'z', go to final state
	if(PDA.top() == 'z')
	{
		Accepted(lineFromFile);

		currentState = 2; //go to final
	}
	else
	{
		notAccepted(lineFromFile);

	}
	if(currentState = 2){return true;} //state 2 is final
	return false;
}

/*
Function to empty the stack, occurs at end of every PDA for each line of the file
*/
void emptyStack(stack<char> &PDA)
{
	while(!PDA.empty())
	{
		PDA.pop();
	}
}

void Accepted(string lineFromFile)
{
	cout <<"Parentheses are balanced for " << lineFromFile << endl<<endl;
}

void notAccepted(string lineFromFile)
{
	if(lineFromFile.empty())
	{
		lineFromFile = "Empty String";
	}

	cout <<"Parentheses are not  balanced for " << lineFromFile << endl<<endl;

}

void showStack(stack<char> PDA)
{

	int i = 0;

	cout<<"Size of PDA is " << PDA.size() << " Now showing stack contents " << endl;
	while(!PDA.empty())
	{

		cout<<PDA.top() <<endl;
		PDA.pop();
	}
}