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