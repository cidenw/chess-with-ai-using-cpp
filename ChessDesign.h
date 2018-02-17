/*******************************************************************************
* MACHINE PROBLEM - Chess                                                      *
* File: ChessDesign.h                                                          *
* Made by: Harold R. Mansilla, Carlo Trono &                                   *
* Course: BS Computer Science - University of the Philippines - Manila         *
* For CMSC 21 - Fundamentals of Programming (Laboratory)                       *
* Submitted to: Perlita E. Gasmen                                              *
*                                                                              *
* PROGRAMMERS' NOTE: ASCII Design source:                                      *
* http://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20 *
*******************************************************************************/

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctype.h>
#include <iomanip>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <vector>

#ifndef CHESSDESIGN_H_INCLUDED
#define CHESSDESIGN_H_INCLUDED

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void gotoxy(int x,int y){
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void splashInstructions(){
    cout<<" ___   __    _  _______  _______  ______    __   __  _______  _______  ___   _______  __    _  _______ \n";
    cout<<"|   | |  |  | ||       ||       ||    _ |  |  | |  ||       ||       ||   | |       ||  |  | ||       |\n";
    cout<<"|   | |   |_| ||  _____||_     _||   | ||  |  | |  ||       ||_     _||   | |   _   ||   |_| ||  _____|\n";
    cout<<"|   | |       || |_____   |   |  |   |_||_ |  |_|  ||       |  |   |  |   | |  | |  ||       || |_____ \n";
    cout<<"|   | |  _    ||_____  |  |   |  |    __  ||       ||      _|  |   |  |   | |  |_|  ||  _    ||_____  |\n";
    cout<<"|   | | | |   | _____| |  |   |  |   |  | ||       ||     |_   |   |  |   | |       || | |   | _____| |\n";
    cout<<"|___| |_|  |__||_______|  |___|  |___|  |_||_______||_______|  |___|  |___| |_______||_|  |__||_______|\n\n";
}

void splashName(){
    for(int i=0;i!=47;i++)
        cout<<(char)219;
    gotoxy(32, 9);  cout<<" _  _ _ _/_ _   _/  /_    . _/_ /_ _   _/_ _  _  _ _  \n";
    gotoxy(32, 10); cout<<"/_ / /_|/  /_'/_/  /_//_/.  /  / //_'  /  /_'/_|/ / / \n";
    gotoxy(32, 11); cout<<"                      _/                                 \n";
    for(int i=0;i!=50;i++)
        cout<<(char)219;
}

void setFColorRed(){ //This function sets the foreground color to red
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
}

void setFColorGreen(){ //This function sets the foreground color to green
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
}

void setFColorBlue(){ //This function sets the foreground color to blue
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
}

void setFColorYellow(){ //This function sets the foreground color to yellow
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_INTENSITY | BACKGROUND_BLUE);
}

void setFColorDefault(){ //This function sets the foreground color to the default color (white)
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED| FOREGROUND_INTENSITY | BACKGROUND_BLUE);
}

void setFColorPink(){ //This function sets the foreground color to pink/magenta
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
}

void setFColorCyan(){ //This function sets the foreground color to cyan
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
}

void setFColorBlackOnBlue(){ //This function sets the foreground color to black and the background to light blue
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_INTENSITY);
}

void setFColorWhiteOnBlue(){ //This function sets the foreground color to black and the background to light blue
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED| FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
}

void setFColorBlackOnMagenta(){ //This function sets the foreground color to black and the background to magenta
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);// | BACKGROUND_BLUE | BACKGROUND_GREEN);
}

void setFColorWhiteOnMagenta(){ //This function sets the foreground color to white and the background color to magenta
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED| FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);// | BACKGROUND_BLUE| BACKGROUND_GREEN);
}

void SetColorAndBackground(){ //This function sets the foreground color to white and the background red(highlighting)
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_INTENSITY);
}

void setColorAndBackgroundWhite(){
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
}

void setColorAndBackgroundBlack(){
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED| FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

void clearColorAndBackground(){ //This function sets the foreground color to cyan
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY|BACKGROUND_BLUE);
}

void splashScreen(){ //displays "CHESS" on the console
    setFColorCyan();
    gotoxy(30,1);cout<<" "<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)187<<(char)219<<(char)219<<(char)187<<"  "<<(char)219<<(char)219<<(char)187<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)187<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)187<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)187<<endl;
    gotoxy(30,2);cout<<(char)219<<(char)219<<(char)201<<(char)205<<(char)205<<(char)205<<(char)205<<(char)188<<(char)219<<(char)219<<(char)186<<"  "<<(char)219<<(char)219<<(char)186<<(char)219<<(char)219<<(char)201<<(char)205<<(char)205<<(char)205<<(char)205<<(char)188<<(char)219<<(char)219<<(char)201<<(char)205<<(char)205<<(char)205<<(char)205<<(char)188<<(char)219<<(char)219<<(char)201<<(char)205<<(char)205<<(char)205<<(char)205<<(char)188<<endl;
    gotoxy(30,3);cout<<(char)219<<(char)219<<(char)186<<"     "<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)186<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)187<<"  "<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)187<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)187<<endl;
    gotoxy(30,4);cout<<(char)219<<(char)219<<(char)186<<"     "<<(char)219<<(char)219<<(char)201<<(char)205<<(char)205<<(char)219<<(char)219<<(char)186<<(char)219<<(char)219<<(char)201<<(char)205<<(char)205<<(char)188<<"  "<<(char)65<<(char)205<<(char)205<<(char)205<<(char)205<<(char)219<<(char)219<<(char)186<<(char)65<<(char)205<<(char)205<<(char)205<<(char)205<<(char)219<<(char)219<<(char)186<<endl;
    gotoxy(30,5);cout<<(char)65<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)187<<(char)219<<(char)219<<(char)186<<"  "<<(char)219<<(char)219<<(char)186<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)187<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)186<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)219<<(char)186<<endl;
    gotoxy(30,6);cout<<" "<<(char)65<<(char)205<<(char)205<<(char)205<<(char)205<<(char)205<<(char)188<<(char)65<<(char)205<<(char)188<<"  "<<(char)65<<(char)205<<(char)188<<(char)65<<(char)205<<(char)205<<(char)205<<(char)205<<(char)205<<(char)205<<(char)188<<(char)65<<(char)205<<(char)205<<(char)205<<(char)205<<(char)205<<(char)205<<(char)188<<(char)65<<(char)205<<(char)205<<(char)205<<(char)205<<(char)205<<(char)205<<(char)188;
    clearColorAndBackground();
    cout<<"\n";
}
void splashPieces(){
cout<<"                                                     _:_"<<endl;\
Sleep(65);
cout<<"                                                    '-.-'"<<endl;
Sleep(65);
cout<<"                                           ()      __.'.__"<<endl;
Sleep(65);
cout<<"                                        .-:--:-.  |_______|"<<endl;
Sleep(65);
cout<<"                                 ()      "<<(char)92<<"____/    "<<(char)92<<"=====/"<<endl;
Sleep(65);
cout<<"                                 /"<<(char)92<<"      {====}     )___("<<endl;
Sleep(65);
cout<<"                      ("<<(char)92<<"=,      //"<<(char)92<<(char)92<<"      )__(     /_____"<<(char)92<<" "<<endl;
Sleep(65);
cout<<"      __    |'-'-'|  //  ."<<(char)92<<"    (    )    /____"<<(char)92<<"     |   |"<<endl;
Sleep(65);
cout<<"     /  "<<(char)92<<"   |_____| (( "<<(char)92<<"_  "<<(char)92<<"    )__(      |  |      |   |"<<endl;
Sleep(65);
cout<<"     "<<(char)92<<"__/    |===|   ))  `"<<(char)92<<"_)  /____"<<(char)92<<"     |  |      |   |"<<endl;
Sleep(65);
cout<<"    /____"<<(char)92<<"   |   |  (/     "<<(char)92<<"    |  |      |  |      |   |"<<endl;
Sleep(65);
cout<<"     |  |    |   |   | _.-'|    |  |      |  |      |   |"<<endl;
Sleep(65);
cout<<"     |__|    )___(    )___(    /____"<<(char)92<<"    /____"<<(char)92<<"    /_____"<<(char)92<<" "<<endl;
Sleep(65);
cout<<"    (====)  (=====)  (=====)  (======)  (======)  (=======)"<<endl;
Sleep(65);
cout<<"    }===={  }====={  }====={  }======{  }======{  }======={"<<endl;
Sleep(65);
cout<<"   (______)(_______)(_______)(________)(________)(_________)"<<endl;
cout<<endl;
cout<<endl;
Sleep(400);
cout<<"                                :)";
}
#endif // CHESSDESIGN_H_INCLUDED
