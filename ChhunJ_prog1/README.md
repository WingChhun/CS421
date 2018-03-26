
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
  - If want to change the file to be parsed, within the main, change file.open("messagefile.txt") ' 
        - Either change the contents of messagefile.txt 
        - OR change the filename to be opened to something else 


 ## Information on how to compile and run program on campus computer 
  
  - To run this program, 2 files are required
    - ChhunJ_prog1.cpp  ( this is the head of the source code for the program)
    - messagefile.txt ("File containing email patterns");

## How to run
    - Using Putty, compile all files by navigating to the directory containing all of the required files
        - Run the command
            - 'g++ ChhunJ_prog1.cpp' or 'g++ *'
        - After program has compiled
            -  Run the command
            - './a.out'

    - Output will be displayed on the screen / PUTTY window.
         - Using the provided messagefile.txt, the output within PUTTY will product segmentation fault
                - To get a stable output on PUTTY, I have added a folder full of patterns that I used for unit testing
         - If using an IDE, segmentation fault will not appear

## Expected papers to be included on submission date (3/26/2018)
- Hard copies of
    -Reg expression,
    -Reg grammar
    # Code
    -Hard copies of source code
    # Sample Run Output
    - Output from main messagefile.txt
    - Output from three other sample runs

  -README.md will be included
