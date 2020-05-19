#ifndef MYCONSOLE_H
#define MYCONSOLE_H

//virtual scan codes for keys returned by checkWhichKeyPressed
//specialKey will be true in all of the cases below
const int UPKEY = 38;
const int DOWNKEY = 40;
const int RIGHTKEY = 39;
const int LEFTKEY = 37;
const int ESCKEY = 27;
const int DELKEY = 46;
const int BACKSPACE = 8;
const int F1KEY = 112;
const int F2KEY = 113;
const int ENTERKEY = 13;
const int CTRL_Z = 26;

//this function outputs a string str at position (x,y) of the screen 
void OutputString(int x, int y, char *str);

//this function will clear the screen
void ClearScreen();

//this function is an alternative to ClearScreen(), when ClearScreen() does not work on windows 7
void ClearScreen1();


//this function will place the cursor at a certain position on the screen
void PlaceCursor(int x, int y);

//this function checks if a key is pressed and if a key is pressed
//then it returns the ascii code/virtual code of the key pressed
//specialKey would be returned as true if it is a key associated with a non-printable character
//specialKey would be returned as false if ordinary printable characters are typed
//if no key is pressed then specialKey value will not be changed
//the parameter waitTime specifies how long we have to wait for an input
//the default value is 20 millisecond.  If within the wait time no key is pressed
//the function returns zero.
unsigned int CheckWhichKeyPressed(bool &specialKey, int waitTime = 20);


//this will change the window size to width and height as specified in the function
//will not work for greater than a certain width and greater than a certain height
//depeding upon the system you are using
void SetWindowSize(int width, int height);


//changes the color of a certain co-ordinate
//An example of usage:
//    PlaceCursor(0,0);
//    cout << '*';
//    SetColorAtPoint(0,0,BACKGROUND|FOREGROUND);
bool SetColorAtPoint(int x, int y, int color);


//set the title of the window
void SetWindowTitle(char Title[]);

//will get the maximum and minimum x and y coordinates of the current window
void GetMaxWindowCoordinates(int &x, int &y);

#endif
