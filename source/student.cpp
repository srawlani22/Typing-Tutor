#include "student.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <time.h>
#include <winuser.h>
#include <cctype>
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
    return name;
}

bool Student::openFile(ifstream & fileStream, string& fileName){
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
    cin >> level;
    switch (level) {
        case 1:
            cout << "You chose the easy level" << endl;  
            fileName = ".//data//easy.txt"; //assign the fileName string to be the path for the easy file
            break;
        case 2:
            cout << "You chose the intermediate level" << endl;
            fileName = ".//data//intermediate.txt"; //assign the fileName string to be the path for the intermediate file
            break;
        case 3: 
            cout << "You chose the hard level" << endl;
            fileName = ".//data//hard.txt";//assign the fileName string to be the path for the hard file
            break;
        default:
            cout << "Error: invalid input. Re-run code" << endl; 
    }
}

void Student::showUserFile(ifstream & fileStream, string fileName){
    string line;
    while (!fileStream.eof()){ //shows the file to the user
        getline(fileStream, line);
        cout << line << endl;
    }

    cout << "Copy the paragraph above. You have 60 seconds to go as far as you can" << endl;
}

void Student::timeAndGrabInput (string& copiedString){
    clock_t t;
    t = clock();
    int counter = 0;

    bool status[260]; //array to keep track of the status of the key press
    for (int i = 0; i < 250; i++){
        status[i] = false;
    }
    //clear buffer
    for (int key = 0; key < 250; key++){
        if (GetAsyncKeyState(key)){
        }
    }

    while( clock() - t < (10 * CLOCKS_PER_SEC) ) { //clock running for 10 seconds
        for(int key = 0; key < 255; key++) { //These are ASCII bounds 
            if (key == 8 || (key >= 32 && key <= 126) || key == 190 || key == 188){ //only check backspace and things above the space bar
                    if(GetAsyncKeyState(key) && (status[key] == false)){ //check to see if a key is pressed and the key was not marked as pressed already
                            if(key == 190){
                                copiedString.append(1,'.');
                                cout << ".";
                            } else if (key == 188){
                                copiedString.append(1,',');
                                cout << ",";
                            } /*else if (key == 8){
                                copiedString.erase(copiedString.length() - 1, 1);
                            } */else {
                                copiedString.append(1, static_cast<char>(key));
                                cout << static_cast<char>(key);
                            } 
                        //cout << static_cast<char>(key); //show the user the character they are pressing as they input things
                        //cout << endl << "T: " << t << " Clock: " << clock() << endl;
                        //cout << endl << "clock() - T: " << clock() - t << " 10*Clock_per_sec: " << (10 * CLOCKS_PER_SEC) << endl;
                        status[key] = true; //revert the status to true so that it only registers once
                        counter++;
                } else if (!GetAsyncKeyState(key) && (status[key] == true)){ //check if the key is not being pressed but the status says that it is
                    status[key] = false; //revert the status to false
                }
            }
        }
    }

    /*for (int i = 0; i < copiedString.length(); i++){
        cout << "cs[" << i << "]" << copiedString[i] << endl;
    }*/
}

void Student::calcAccuracy(ifstream & fileStream, string fileName, string copiedString){
    int countCharacters = 0; //total number of characters in the file
    string line = ""; //empty string to hold the getline
    /*fileStream.close(); //close the fileStream becuase we already went through it to show the user the file
    openFile(fileStream, fileName); //open the file once again so that we can count the charcters within the file
    while (!fileStream.eof()){ //check to make sure we are not at the end of the file
        getline(fileStream,line); //grab a line from the file
        for (int i = 0; i < line.length(); i++){ //iterate through the string
            countCharacters++; //increment the countCharacters variable for every character in the line
        }
    }*/

    //fixing the backspace characters
    ///////////////NEED TO FIND A WAY TO DECREASE THE LENGTH OF TEH STRING BECUASE IT IS MESSING WITH THE COUNTING OF CHARACTERS
    for (int i = 0; i < copiedString.length(); i++){ //iterate through the entire string
        if (static_cast<int>(copiedString[i]) == 8){ //check to see if the character is a backspace character
            for (int j = i; j < copiedString.length(); j++){ //move every chracter down when there is a backspace character
                copiedString[j - 1] = copiedString[j + 1];
                //copiedString.resize(copiedString.length() - 1);
            }
        }
    }

///////NOT COUNTING THE CHARACTERS CORRECTLY BECAUSE WHEN WE GET RID OF TEH BACKSPACES THE LENGTH OF TEH STRING IS STILL
    for (int i = 0; i < copiedString.length(); i++){
            countCharacters++;
    }
    cout << "count characters: " << countCharacters << endl; //test print statement

    int countCommonCharacters = 0; //integer to hold the number of common characters
    fileStream.close(); //close the file because we just went through it to count the characters
    openFile(fileStream, fileName); //open the file again
    /*for (int i = 0; i < copiedString.length(); i++){ //iterating through the string
        while (!fileStream.eof()){ //check to make sure we are not at the end of the file
            getline(fileStream, line); //get a line from the file
            for (int j = 0; j < line.length(); j++){ //iterate through the line in the file
                if (islower(line[j])){
                    copiedString[i] = tolower(copiedString[i]);
                }
                //line[j] = toupper(line[j]); //make all of the file uppercase because GetAsyncKeyState only captures upper case keys
                if (copiedString[i] == line[j]){ //if both the copied string and line chracter are the same, increment the count of the common characters
                    countCommonCharacters++;
                }
            }
        }
    }*/

    int i = 0; //index for the copied string
    while (!fileStream.eof() || i < copiedString.length()){ //make sure we aren't at the end of the file or at the end of the copied string
        getline(fileStream, line); //grab a line from the file
        for (int j = 0; j < line.length(); j++){ //iterate through the line
            if (islower(line[j])){
                    copiedString[i] = tolower(copiedString[i]);
                }
            if (line[j] == copiedString[i]){ //check if the line is equal to the copied string 
                countCommonCharacters++; //increment the common characters
            }
            i++; //increment the index for the copied string
        }
    }


    cout << "copied string" << copiedString << endl;
    cout << "common chars" << countCommonCharacters << endl;

    float acc = 0;
    cout << "made it here" << endl;
    acc = (static_cast<float>(countCommonCharacters)/static_cast<float>(countCharacters)) * 100;
    cout << "i don't think we made it here" << endl;
    cout << "accuracy: " << acc << endl;
    cout << "i reallly don't think we made it here" << endl;
    accuracy.push_back(acc);
}

void Student::calcWPM(ifstream & fileStream, string fileName, string copiedString){
    fileStream.close();
    openFile(fileStream, fileName);
    int countWords = 1; //initialize a countWords function and assign it to be 1 becuase the last word does not have a space and would not be counted
    for (int i = 0; static_cast<int>(copiedString[i]) != 0; i++){ //iterate through the shown sentence to count the number of words
        if (static_cast<int>(copiedString[i]) == 32){ //if the character is a space, increment the countWords variable
            countWords++;
        }
    }
    float wordspm;
    wordspm = static_cast<float>(countWords) / 60;
    wpm.push_back(wordspm);
}
        
void Student::playGame(){
        ifstream fileStream; //initialize a file path 
        string fileName = ""; //initilaize a string to hold the name of the file
        string copiedString = ""; //initialize a string to hold the user input
        levelDecider(fileStream, fileName); //call the level decider function so the user can choose which level they want
        openFile(fileStream, fileName); //open the file based on which level they chose
        showUserFile(fileStream, fileName); //show the paragraph to the user
        timeAndGrabInput(copiedString); //call the time and grab input function to grab the user input while timing 60 seconds
        fileStream.close();
         calcWPM(fileStream, fileName, copiedString);
        calcAccuracy(fileStream, fileName, copiedString);
       
}

void Student::printAll(){
    ofstream output;
    output.open(name + "averageStats.txt");
    float averageAccuracy, averageWPM;

    output << "The name of the player is: " << name << endl;

    for(int i=0; i < accuracy.size(); i++){
        output << "Try " << i + 1 << endl;
        output << "Accuracy is: " << accuracy[i] << "%" << endl;
        output << "WPM is: " << wpm[i] << endl;
        averageAccuracy += averageAccuracy+ accuracy[i];
        averageWPM += averageWPM + wpm[i];
        cout << endl;
    }
    averageAccuracy = averageAccuracy/ accuracy.size();
    averageWPM = averageWPM/wpm.size();

    output << "The average accurcy is: " << averageAccuracy << endl;
    output << "The average typing speed is: " << averageWPM << endl;

}