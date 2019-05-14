#include "student.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <time.h>
#include <winuser.h>
using namespace std;

int main(){


    string playerName;
    cout << "Enter the name of the Player: ";
    cin >> playerName;
    Student player(playerName);
    player.playGame();
    //player.playGame();
    player.printAll();
    

}

//add a level decision aspect where if you have a certain average accuracy - you are bumped up a level
//add a loop to the play game function or the main for if the player wants to play again
//cite sources within the document
//comment everything... booooo

/*

- class student
    - string name
    - float accuracy (vector?)
    - float WPM (vector?) 
    - int level (1, 2, 3)
    - time_t time (vector? - ask if this is possible)
    Methods
    - get name
    - get last score
    - print average score
    - print last socre
    - choose level
    - play game (add a new accruacy and WPM) --> in the int main we should have a swtich case of what level you want and ask what student is playing to pull up the correct stats
    - print --> output to a file (TRY WITH A VECTOR FIRST --> we will probably have an input file of student names and with every new student we add their name to the input file and create a new output file)
    - time 

- Input files
    - at least three for each level (maybe more if we want choices within each level)

- adjust the calculate accuracy function
    - getline (work with input files rather than an array of strings)
    - (it would be cool to calculate based on individual words versus the entire string -- will make the program more accurate)

- clock/ timing
    - close terminal after 60 seconds (or whatever we decide)*/

/*
QUESTIONS FOR SCOTT

- GetAsyncKeyState:
    - only does upper case : is our solution acceptable? (make the entire file upper case as well)
    - does not capture period or comma : is our solution accpetable? (disregard periods or commas)
    - captures keys before it actaully runs the code (all keys all time - not even in terminal)

- Documentation
    - Assumptions
    - Use Case/ Manual
    */

