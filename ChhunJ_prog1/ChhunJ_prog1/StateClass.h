#pragma once

#include "stdafx.h"
	enum State  { state_start, state_f, state_fr, state_fre, state_free};
class StateClass
{
protected:
	/*
	States and Function prototypes
	*/



public:
	StateClass(void);
	~StateClass(void);
	//Get function

	//Start state
	enum  State start(int c);
	//States involving Free
	enum  State state_f(int c);
	enum State fr(int c);
	enum  State fre(int c);
	enum  State free(int c);
	void getStuff();
};

