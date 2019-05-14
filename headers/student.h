#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include <time.h>
#include <winuser.h>
using namespace std;

class Student {
    private: 
        string name; //variable to hold the name of the student
        vector<float> accuracy; //vector holding the accuracy of typing each time a test is completed
        vector<float> wpm; //vector holding the words per minute each time a students completes a typing tutor test
        int level; //1 - beginner, 2 - intermediate, 3 - hardcore
        time_t start; //start time
        time_t stop; //end time
        vector<time_t> timeTaken; //time taken to copy the sentence or file or whatever we choose, will be 60 deconds as default
    public:

        //Empty Constructor to set name to nothing and level to 1
        Student();

        //Constructor that sets name to be equal to in rode down
        Student(string inputName);
        
        //interface method for recieving the last in the words per minute vector
        float getLastWPM();

        //interface method for recieving the last thing in the accuracy vector
        float getLastAccuracy();

        //interface method to recieve the name of the user
        string getName();

        //Method that opens a file and checks if it is open or not
        //Intput: ifstream fileStream, string fileName - name of the file the code will open
        //Output: file open or not
        bool openFile(ifstream & fileStream, string& fileName);

        //Method that shows the decided file and asks them to copy it and captures the input
        //Input: ifstream& fileStream, string fileName
        //Output: the file is shown to user and we capture the copied string
        void showUserFile(ifstream & fileStream, string fileName);

        //Method to allow the user to input characters as long as the timer has not run out
        //Input: copied string - a place to store the user input
        //Output: the copied string will now hold the user input
        void timeAndGrabInput (string& copiedString);

        //Method to calculate the accuracy of the last test the user completed and push it into the vector
        //Input: ifstream & fileStream, string fileName - name of the file to open, string copiedString - the input from the user
        //Output: float accuracy pushed in the accuracy vector for the student
        void calcAccuracy(ifstream & fileStream, string fileName, string copiedString);

        //Method to calculate the words per minute of the last attempt
        //Input: ifstream& fileSTrea, string fileName - file opened & comparing to, string copiedString - user input
        //Output float wpm pushed in the wpm vector
        void calcWPM(ifstream & fileStream, string fileName, string copiedString);
        
        //Method to ask the user what level they would like to play
        //Input: ifstream& fileStream, string& fileName
        //Output: the level of the user will be changed to whatever they input
        void levelDecider(ifstream & fileStream, string& fileName); 

        //Method that calls the leveldecider, show user file and calcuation functions
        //Input: N/A
        //Output: accuracy and words per minute are pushed into their respective vectors
        void playGame();

        //print each trial and the average calculations
        void printAll();
};


#endif