#include "student.h"// included the student.h file for the class
#include <iostream>
#include <string>// included the string library for the string functions
#include <vector>// included vector for definig vectors
#include <time.h>// included time.h for clock_t and clock() function
#include <winuser.h>// included this for GetSyncKeyState
#include <cctype>// included cctype for islower and tolower
#include <fstream>// fstream for input and output stream
using namespace std;

//Empty Constructor to set name to nothing and level to 1
Student::Student(){
    name = ""; //assign the name to be empty
    level = 1; //start the level at 1
}

Student::Student(string inputName){
    name = inputName; //assign the name to be the name that was input
    level = 1; //start the level at 1
}
        
float Student::getLastWPM(){
    return wpm[wpm.size() - 1]; //return the last value in the wpm vector
}

float Student::getLastAccuracy(){
    return accuracy[accuracy.size() - 1]; //return the last value in the accuracy vector
}

string Student::getName(){
    return name;// retunrs the name of the player, just an interface function
}

bool Student::openFile(ifstream & fileStream, string & fileName){
    fileStream.open(fileName); //attempt to open the file

    if (fileStream.fail()){ //return false if it failed to open the file
        cout << "There was an error"; 
        return false;
    } else { //return true if the file was opened succesfully
        return true;
    }
}

void Student::levelDecider(ifstream & fileStream, string& fileName){
    cout << "What level would you like to play? (Enter 1 for beginner, 2 for intermediate, 3 for hard)" << endl;
    cin.ignore();
    cin >> level;// the user enters the level that they want to play
    // a switch case switches between the levels based on the user input and opens the file accordingly
    switch (level) {
        case 1:// easy level
            cout << "You chose the easy level" << endl;  
            fileName = ".//data//easy.txt"; //assign the fileName string to be the path for the easy file
            break;
        case 2:// intermediate level
            cout << "You chose the intermediate level" << endl;
            fileName = ".//data//intermediate.txt"; //assign the fileName string to be the path for the intermediate file
            break;
        case 3: // hard level
            cout << "You chose the hard level" << endl;
            fileName = ".//data//hard.txt";//assign the fileName string to be the path for the hard file
            break;
        default:// a default case in case the user inputs any number that is beyond the scope of the switch case
            cout << "Error: invalid input. Re-run code" << endl; 
    }
    cout << endl;
}

void Student::showUserFile(ifstream & fileStream, string fileName){// shows the file to the user based on the selection from the switch case
    string line;// a string varaible 
    while (!fileStream.eof()){ //prints the stuff that is inside the file to the terminal so that the user can play the game
        getline(fileStream, line);// gets every specific line
        cout << line << endl;// all the lines are printed
    }
    cout << endl;

    cout << "Copy the paragraph above. You have 60 seconds to go as far as you can" << endl << endl << endl;
}

void Student::timeAndGrabInput (string& copiedString){// the timer function
    clock_t t;// a clock variable to hold the original time 
    t = clock();// this the variable to hold the remaining time

    bool status[260]; //array to keep track of the status of the key press
    for (int i = 0; i < 250; i++){
        status[i] = false;// a for loop that assigns the status of all the keys to false initially
    }
    //clear buffer
    // the terminal was catching random characters before even running the code, so we had to use a for loop that would clear the terminal everytime we typed something
    for (int key = 0; key < 250; key++){
        if (GetAsyncKeyState(key)){// checks the status of the key, pressed or not
        }
    }

    while( clock() - t < (60 * CLOCKS_PER_SEC) ) { //clock running for 60 seconds
        for(int key = 0; key < 255; key++) { //These are ASCII bounds, the bounds within which we want to capture the user input 
            if (key == 8 || (key >= 32 && key <= 126) || key == 190 || key == 188){ //only check backspace and things above the space bar
                    if(GetAsyncKeyState(key) && (status[key] == false)){ //check to see if a key is pressed and the key was not marked as pressed already
                            if(key == 190){// capturing a period becuase a weird character is printed to the terminal everytime a period key is pressed.
                                copiedString.append(1,'.');// this appends the period to the string and prints it
                                cout << ".";
                            } else if (key == 188){// capturing a comma becuase a weird character is printed to the terminal everytime a comma key is pressed.
                                copiedString.append(1,',');// this appends the comma to the string and prints it
                                cout << ",";
                            } else {
                                copiedString.append(1, static_cast<char>(key));// all the characters are appended to the string if there are no special characters
                                cout << static_cast<char>(key);
                            } 
                        status[key] = true; //revert the status to true so that it only registers once
                } else if (!GetAsyncKeyState(key) && (status[key] == true)){ //check if the key is not being pressed but the status says that it is
                    status[key] = false; //revert the status to false
                }
            }
        }
    }
}

void Student::removeBackspace (string& copiedString){
    while( copiedString.find(8, 0) != string::npos ) { //Run until no backspaces, findsif the backspace key is pressed, since the value of backspace as an ASCII bound is 8.
        copiedString.erase(  copiedString.find(8, 0) - 1  , 2);// it erases and overwrites the string in the array by two positions, the one we erased and the other when we pressed backspace
    }
}

void Student::calcAccuracy(ifstream & fileStream, string fileName, string& copiedString){
    int countCharacters = 0; //total number of characters in the file
    string line = ""; //empty string to hold the getline
    int countCommonCharacters = 0; //integer to hold the number of common characters
    fileStream.close(); //close the file because we just went through it to count the characters
    openFile(fileStream, fileName); //open the file again

    removeBackspace(copiedString);// calling this function to remove the backspace

    //counting the characters within the string
    for (int i = 0; i < copiedString.length(); i++){
            countCharacters++;// counts all the characters that are inside the string, total number of characters in the entire file basically
    }

    int i = 0; //index for the copied string
    while (!fileStream.eof() && (i < copiedString.length())){ //make sure we aren't at the end of the file or at the end of the copied string
        getline(fileStream, line); //grab a line from the file
        for (int j = 0; j < line.length(); j++){ //iterate through the line
            if (islower(line[j])){// if the characters in the file are lower case then we turn the characters of the copied string into lower case to calculate accuracy
                    copiedString[i] = tolower(copiedString[i]);
            }
            if (line[j] == copiedString[i]){ //check if the line is equal to the copied string 
                countCommonCharacters++; //increment the common characters
            }
            i++; //increment the index for the copied string
        }
    }

    float acc = 0.0;// a float variable that holds the accuracy of the player
    acc = (static_cast<float>(countCommonCharacters)/static_cast<float>(countCharacters)) * 100;// calculating accuracy
    accuracy.push_back(acc); // the accuracy is pushed back into the vector
}

void Student::calcWPM(ifstream & fileStream, string fileName, string copiedString){
    fileStream.close();// we need to close and open the file again because it was open in the calcAccuracy function
    openFile(fileStream, fileName);
    int countWords = 1; //initialize a countWords function and assign it to be 1 becuase the last word does not have a space and would not be counted
    //for (int i = 0; static_cast<int>(copiedString[i]) != 0; i++){ //iterate through the shown sentence to count the number of words
    for(int i=0; i<copiedString.length(); i++){
        if (static_cast<int>(copiedString[i]) == 32){ //if the character is a space, increment the countWords variable
            countWords++;// words are incremented everytime user presses the space bar
        }
    }

    wpm.push_back(countWords);// the final speed is pushed into the vector
}
        
void Student::playGame(){// the function that calls all the functions basically
        ifstream fileStream; //initialize a file path 
        string fileName = ""; //initilaize a string to hold the name of the file
        string copiedString = ""; //initialize a string to hold the user input
        levelDecider(fileStream, fileName); //call the level decider function so the user can choose which level they want
        openFile(fileStream, fileName); //open the file based on which level they chose
        showUserFile(fileStream, fileName); //show the paragraph to the user
        timeAndGrabInput(copiedString); //call the time and grab input function to grab the user input while timing 60 seconds
        removeBackspace(copiedString);
        fileStream.close();
     
        calcWPM(fileStream, fileName, copiedString);
        calcAccuracy(fileStream, fileName, copiedString);
        copiedString = "";
        fileStream.close();
}

void Student::printAll(){// function that prints all the stats to the user file 
    ofstream output;// an output file where eveything would be pushed
    output.open(".\\userStats\\"+ name + "averageStats.txt");// the stats and results of the player will be pushed to a text file that would be stored in the userStats folder
    float averageAccuracy, averageWPM;// two variables that will hold the avg accuracy and avg typing speed in wpm

    output << "The name of the player is: " << name << endl;// the name of the player is printed in the file

    for(int i=0; i < accuracy.size(); i++){// a for loop iterates through all the vectors and prints all the values to the output file
        output << "Try " << i + 1 << endl;// tells how may times has a user played the game
        output << "Accuracy is: " << accuracy[i] << "%" << endl;// tells the accuracy everytime user plays the game
        output << "WPM is: " << wpm[i] << endl;// tells the typing speed everythims user plays in wpm
        averageAccuracy += averageAccuracy+ accuracy[i];// adds all the accuracies based on the number of times a user has played the game
        averageWPM += averageWPM + wpm[i];// adds all the typing speeds based on the number of times a user has played the game
        cout << endl;
    }
    averageAccuracy = averageAccuracy/ accuracy.size();// calculates the avg accuracy
    averageWPM = averageWPM/wpm.size();// calculates the avg typing speed

    output << "The average accurcy is: " << averageAccuracy << "%" << endl;// the average accuracy 
    output << "The average typing speed is: " << averageWPM << " wpm" << endl;// and typing speed are printed to the output file

}