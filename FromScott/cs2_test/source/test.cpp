#include <iostream>
#include <winuser.h>
#include <time.h>
#include <string>

//Modified from: https://stackoverflow.com/questions/32031368/c-how-do-i-read-in-input-for-a-certain-amount-of-time-only-can-i-do-so-withou

using namespace std;

int main (){

    string test = "";

    clock_t t;
    t = clock();
    int counter = 0;

    bool status[0x7d];
    for (int i = 0; i < 0x7d; i++){
        status[i] = false;
    }


    while( clock() - t < (10 * CLOCKS_PER_SEC) ) {
        for(int key = 0; key < 255; key++) { //These are ASCII bounds
            //if(GetAsyncKeyState(key) && (status[key] == false)){
                if(GetAsyncKeyState(key)){ 
                //test.append(1, static_cast<char>(key));
                //cout << "Key Pressed: " << static_cast<char>(key) << endl;
                cout << "Key Pressed: " << key << endl;
                //status[key] = true;
                //counter++;
            }// else if (!GetAsyncKeyState(key) && (status[key] == true)){
             //   status[key] = false;
            //}
        }
    }

    cout << "End of Loop! String: |" << test << "|" << endl;

}

