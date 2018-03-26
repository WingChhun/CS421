
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
