# CS421 - WingChhun
CSUSM CS421  - Spring 2018 


## Repository and Course Information

 - This repository is created for CS421 - Theory of Computation course at CSUSM.


## Assgignment / Program Info
- Programs involve designing and implementing Finite State Machines or (Finite Automata/tons) in C++
- HW 1(3/24/2018) - Implement a Finite State Automata 
    - Design a pattern matching Finite Automaton that accepts the language of patterns as follows:
        - L = {'Free access' , 'free software', 'free vacation' , 'free trials', 'win', 'winner', 'winners', 'winnings'}
        - Must find these regular expressions/patterns within 'messagefile.txt' which is formatted similar to a HMTL email written using XML tags, 
            - Only read RegExpressions within body of the message, ignore subject
            - Display all states/ set of states the FA reaches using transition functions
                - Ultimately goal:
                    - Display message ID numbers for the emails identified as SPAM.
    - PDF will be attached

## Approach
 - HW 1 
    - Approach involves using enum class in C++, to create functions with no real purpose other than to have named-value
        - have vector hold message IDs, push everytime a messageID is read
            -vector.pop_back() if the body of the message fails the regEx test.
            - otherwise, vector contains an ID where the messageID is SPAM
        - Have enum state functions that are named to represent the current state
        - Have one global state that is returned after each pattern test  for every line in the body of file
    - Main problems to solve
        - How to parse through the file and it's XML tags, only retrieve msgID as well as body of message

# Compiler Info

- Programs are written in C++ using Visual Studio Ultimate 2012 / Visual Studio Code
    - However programs are meant to be run on emacs using the g++ compiler and will have to be formatted afterwards

    ## PROGRAM 1 README
    
## Class Info
 -Programmed by James D. Chhun
 -Spring 2018, 3/22/2018 -> 3/25/2018 (completion date)
 -Class CS421 - Theory of Computing by Rocio 

## Program Description
 
 - This program parses through a file of email messages, these email  messages are wrapped and formatted in XML tags.
  
  -Within the program, the email messages are parsed for their message ID as well as body message, individual characters of the body message
  are then passed into the FiniteAutomaton function, where a Deterministic Finite Automaton is simulated. 
  
  -This DFA has 44 states, state 44 is the Final state, once this state is reached the email message has been identified as a SPAM message. Because this is a spam message
  for every character that follows after reaching the final state, the state transition stays trapped within the final state because it is has been accepted.
  
  - If the final state has been reached, a vector containing the message IDs parsed from the messages earlier will either keep the ID or pop the ID
  from it's contents, at the end of the program the contents of the vector are displayed, where each element in the vector
  is a ID identifying a SPAM email

## NOTES
  - If want to change the file to be parsed, within the main, change filename to "anyFileName within same directory"

  ## DEPENDENCIES
  - NOTES, there is a 'Helpers.h' header file, this class is not required however it increases the modularity of the program as
		- this main .cpp file is long and requires the enum States and State functions to be within it.
  - Other preprocessors
    - iostream, stack, vector, string, fstream

 ## Information on how to compile and run program on campus computer 
  
  - To run this program, 4 files are required to be in the same directory, these files include,
    - ChhunJ_prog1.cpp  ( this is the head of the source code for the program)
    - Header.h
    - Header.cpp
    - messagefile.txt  ( This can be any messageFile but the name within ChhunJ_prog1.cpp must be changed accordingly for other files)
        - Will include patterns of email messages denoted from prompt
## How to run
    - Using Putty, compile all files by navigating to the directory containing all of the required files
        - Run the command
            - 'g++ Header.h Header.cpp ChhunJ_prog1.cpp'
        - After program has compiled
            -  Run the command
            - './a.out'
    - Output will be displayed on the screen / PUTTY window.
    
## Expected papers to be included on submission date (3/26/2018)
- Hard copies of
    -Reg expression,
    -Reg grammar
    # Code
    -Hard copies of source code
    # Sample Run Output
    - Output from main messagefile.txt
    - Output from two other sample runs

  -README.md will be included
