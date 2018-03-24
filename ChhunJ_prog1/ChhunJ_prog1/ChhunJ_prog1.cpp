// ChhunJ_prog1.cpp : Defines the entry point for the console application.
//
/*
Program introduction up here

*/
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>

//enum State dfastate = start_start;
using namespace std;
enum State  { state_start, state_f, state_fr, state_fre, state_free};
//EnumState function prototypes
enum State start(int c);
//Enum state prototypes handling the string 'free'
enum State f(int c);
enum State fr(int c);
enum State fre(int c);
enum State free(int c);
//Main function prototypes

enum State dfaState = state_start; //Global State variable, will represent and hold the current/final state the input reaches


//Function declarations
int _tmain(int argc, _TCHAR* argv[])
{
	ifstream file;
	string fileName = "test1.txt";
	int character; //to hold characters
	string lineFromFile;
	file.open(fileName);

	if(!file){cout<<"File with name " + fileName + " does not exist!" <<endl<<endl;}
	else
	{
		//Perform file handling
		//while not end of file
		while(!file.eof())
		{
			getline(file,lineFromFile);
			cout <<"lineFromFile = " + lineFromFile << endl<<endl;
		}
	}

	//END
	cout<<"Hello world testing" << endl <<endl;
	system("pause"); //pause screen to show output
	return 0;
}

//enum Based Functions for state
enum State start(int c)
{
	if(c == 'f'){dfaState = state_f;}
	return dfaState;
}
enum State f(int c)
{
	if(c =='r'){dfaState = state_fr;}
	else dfaState = state_start;
	return dfaState;
}
enum State fr(int c)
{
	if(c =='e'){dfaState = state_fre;}

	else dfaState = state_start;
	return dfaState;
}
enum State fre(int c)
{
	if(c =='e'){dfaState = state_free;}

	else dfaState = state_start;
	return dfaState;
}
enum State free(int c)
{
	//For now test, see if can reach state free
	cout <<"I AM IN STATE FREE, current input character = " + c << endl;
	return dfaState;
}