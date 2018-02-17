/*******************************************************************************
* MACHINE PROBLEM - Chess                                                      *
* File: ChessIO.h                                                              *
* Made by: Harold R. Mansilla, Carlo Trono & Waleed Occidental                 *
* Course: BS Computer Science - University of the Philippines - Manila         *
* For CMSC 21 - Fundamentals of Programming (Laboratory)                       *
* Submitted to: Perlita E. Gasmen                                              *
*                                                                              *
*******************************************************************************/

#include "ChessGame.cpp"

#ifndef CHESSIO_H_INCLUDED
#define CHESSIO_H_INCLUDED

void menu();
/*
void pageDisplay(int pageNo){
    for(int i=0;i!=110;i++)
        cout<<(char)17;
    gotoxy(48,9);cout<<"Page "<<pageNo<<" of 11\n";
    for(int i=0;i!=110;i++)
        cout<<(char)17;
}

void instructionsDisplay(){
    chessGame cg;
    int currPage = 0, yesNo = 0, keyInput = 0;
    system("cls");
    setFColorYellow();
    splashInstructions();
    clearColorAndBackground();
    pageDisplay(1);
    cout<<"\nWelcome to our chess game!"<<endl;
    cout<<"This application is a joint project of three students from the University of the Philippines-Manila."<<endl;;
    cout<<"We hope you'll enjoy the program as much as we did making it!"<<endl<<endl;
    cout<<"Navigate using the LEFT and RIGHT arrow keys.\nPress ENTER to go back to the Main Menu.";
    setFColorCyan();
    clearColorAndBackground();
    while(1){
        keyInput = getch();
        if((keyInput == KEY_LEFT && currPage == 0) || (keyInput == KEY_LEFT && currPage == 1)){
            currPage = 1;
            system("cls");
            setFColorYellow();
            splashInstructions();
            clearColorAndBackground();
            pageDisplay(2);
            cout<<"Welcome to our chess game!"<<endl;
            cout<<"This application is a joint project of three students from the University of the Philippines-Manila.";
            cout<<"We hope you'll enjoy the program as much as we did making it!";
            cout<<endl;
            cout<<endl;
            cout<<"Navigate using the LEFT and RIGHT arrow keys.Press ENTER to go back to the Main Menu.";
            setFColorCyan();
            gotoxy(48,28);
            cout<<"Page 1 of 11";
            clearColorAndBackground();
        }
        else if((keyInput == KEY_RIGHT && (currPage == 1 || currPage == 0) )|| (keyInput == KEY_LEFT && currPage == 3)){
            currPage = 2;
            system("cls");
            setFColorYellow();
            splashInstructions();
            clearColorAndBackground();
            pageDisplay(2);
            cout<<"In a chess match, each player has 16 pieces:"<<endl;
            Sleep(500);
            cout<<"(1) King,"<<endl;
            Sleep(700);
            cout<<"(1) Queen,"<<endl;
            Sleep(700);
            cout<<"(2) Rooks,"<<endl;
            Sleep(700);
            cout<<"(2) Bishops,"<<endl;
            Sleep(700);
            cout<<"(2) Knights, and;"<<endl;
            Sleep(700);
            cout<<"(8) Pawns."<<endl;
            Sleep(700);
            cout<<endl
                <<"The goal of the game is to checkmate the other king."<<endl
                <<"Checkmate - king is in a position to be captured (checkmate position) and cannot"
                <<"escape from captivity."<<endl;
            setFColorCyan();
            gotoxy(48,28); cout<<"Page 2 of 11";
            clearColorAndBackground();
        }
        else if((keyInput == KEY_RIGHT && currPage == 2 )|| (keyInput == KEY_LEFT && currPage == 4)){
            currPage = 3;
            system("cls");
            setFColorYellow();
            splashInstructions();
            clearColorAndBackground();
            pageDisplay(3);
            cout<<"The king is the most important piece, but is one of the weakest. "<<endl
                <<"The king can only move "
                <<"one "
                <<"square in any direction: "<<endl
                <<"up, down, to the sides, and diagonally."<<endl;
            setFColorCyan();
            gotoxy(48,28); cout<<"Page 3 of 11";
            clearColorAndBackground();
        }
        else if((keyInput == KEY_RIGHT && currPage == 3 )|| (keyInput == KEY_LEFT && currPage == 5)){
            currPage = 4;
            system("cls");
            setFColorYellow();
            splashInstructions();
            clearColorAndBackground();
            pageDisplay(4);
            cout<<"The queen is the easily most powerful piece. "<<endl;
            cout<<"She can move in any one straight direction - forward,"<<endl;
            cout<<"backward, sideways, or diagonally."<<endl;
            //cout<<"She can move as far as possible, as long as she does"<<endl;
            cout<<"not go through her own pieces."<<endl<<endl;
            //cg.boardInitInstructions(queen);
            setFColorCyan();
            gotoxy(48,28); cout<<"Page 4 of 11";
            clearColorAndBackground();
        }
        else if((keyInput == KEY_RIGHT && currPage == 4) || (keyInput == KEY_LEFT && currPage == 6)){
            currPage = 5;
            system("cls");
            setFColorYellow();
            splashInstructions();
            clearColorAndBackground();
            pageDisplay(5);
            cout<<"The rook may move as far as it wants, but only forward"<<endl;
            cout<<"backward, and to the sides. "<<endl;
            setFColorCyan();
            gotoxy(48,28); cout<<"Page 5 of 11";
            clearColorAndBackground();
        }
        else if((keyInput == KEY_RIGHT && currPage == 5) || (keyInput == KEY_LEFT && currPage == 7)){
            currPage = 6;
            system("cls");
            setFColorYellow();
            splashInstructions();
            clearColorAndBackground();
            pageDisplay(6);
            cout<<"The bishop may move as far as it wants, but only diagonally. "<<endl;
            setFColorCyan();
            gotoxy(48,28); cout<<"Page 6 of 11";
            clearColorAndBackground();
        }
        else if((keyInput == KEY_RIGHT && currPage == 6) || (keyInput == KEY_LEFT && currPage == 8)){
            currPage = 7;
            system("cls");
            setFColorYellow();
            splashInstructions();
            clearColorAndBackground();
            pageDisplay(7);
            cout<<"Knights move in a very different way from the other pieces."<<endl;
            cout<<"These pieces would go two squares, then one more move at a 90"<<endl;
            cout<<"degree angle, just like the shape of letter L.";
            Sleep(500);
            setFColorCyan();
            gotoxy(48,28); cout<<"Page 7 of 11";
            clearColorAndBackground();
        }
        else if((keyInput == KEY_RIGHT && currPage == 7) || (keyInput == KEY_LEFT && currPage == 9)){
            currPage = 8;
            system("cls");
            setFColorYellow();
            splashInstructions();
            clearColorAndBackground();
            pageDisplay(8);
            cout<<"Pawns are easily the pieces that move forward, but capture diagonally."<<endl;
            setFColorCyan();
            gotoxy(48,28); cout<<"Page 8 of 11";
            clearColorAndBackground();
        }
        else if((keyInput == KEY_RIGHT && currPage == 8) || (keyInput == KEY_LEFT && currPage == 10)){
            currPage = 9;
            system("cls");
            setFColorYellow();
            splashInstructions();
            clearColorAndBackground();
            pageDisplay(9);
            cout<<"Pawns have another special ability and that is that if a pawn"<<endl;
            cout<<"reaches the other side of the board, it may be promoted to any piece."<<endl;
            setFColorCyan();
            gotoxy(48,28); cout<<"Page 9 of 11";
            clearColorAndBackground();
        }
        else if((keyInput == KEY_RIGHT && currPage == 9) || (keyInput == KEY_LEFT && currPage == 11)){
            currPage = 10;
            system("cls");
            setFColorYellow();
            splashInstructions();
            clearColorAndBackground();
            pageDisplay(10);
            cout<<"If a pawn moves out two squares on its first move, and by doing so lands"<<endl;
            cout<<"to the side of the opposing pawn."<<endl;
            cout<<"That other pawn can also capture the first pawn as it passes by."<<endl;
            setFColorCyan();
            gotoxy(48,28); cout<<"Page 10 of 11";
            clearColorAndBackground();
        }
        else if((keyInput == KEY_RIGHT && currPage == 10) || (keyInput == KEY_LEFT && currPage == 12)){
            currPage = 11;
            system("cls");
            setFColorYellow();
            splashInstructions();
            clearColorAndBackground();
            pageDisplay(11);
            cout<<"This move allows you to do two important things all in one move:"<<endl;
            cout<<"Get your king to safety, and get your rook out of the corner and into the game."<<endl;
            cout<<"This is done by moving the king two squares over to one side and then move the"<<endl;
            cout<<"rook from that side’s corner to right next to the king on the opposite side"<<endl;
            setFColorCyan();
            gotoxy(48,28); cout<<"Page 11 of 11";
            clearColorAndBackground();
        }
        else if(keyInput == 13){
            menu();
        }
    }
}

void aboutProgram(){
    system("cls");
    splashScreen();
    splashName();
    system("pause");
    menu();
}

void menu(){
    SetConsoleTitle("CHESS");
    int choice = 0, currMenu = 0;
    system("cls");
    splashScreen();
    std::cout<<"\n\nPress the UP or DOWN key to continue";
    while(1){
        choice = getch();
            if ((choice == KEY_UP && currMenu == 0) || (choice == KEY_UP && currMenu == 2)){
                system("cls");
                currMenu = 1;
                splashScreen();
                clearColorAndBackground();
                SetColorAndBackground();
                std::cout<<"\nPlay game\n";
                clearColorAndBackground();
                std::cout<<"Instructions\n";
                clearColorAndBackground();
                std::cout<<"About\n";
                clearColorAndBackground();
                std::cout<<"Quit";
                clearColorAndBackground();
            }
            else if ((choice == KEY_DOWN && currMenu == 1) || (choice == KEY_UP && currMenu == 3)){
                system("cls");
                currMenu = 2;
                splashScreen();
                clearColorAndBackground();
                std::cout<<"\nPlay game\n";
                SetColorAndBackground();
                std::cout<<"Instructions\n";
                clearColorAndBackground();
                std::cout<<"About\n";
                clearColorAndBackground();
                std::cout<<"Quit";
                clearColorAndBackground();
            }
            else if ((choice == KEY_DOWN && currMenu == 2) || (choice == KEY_UP && currMenu == 4)){
                system("cls");
                currMenu = 3;
                splashScreen();
                clearColorAndBackground();
                std::cout<<"\nPlay game\n";
                clearColorAndBackground();
                std::cout<<"Instructions\n";
                SetColorAndBackground();
                std::cout<<"About\n";
                clearColorAndBackground();
                std::cout<<"Quit";
                clearColorAndBackground();
            }
            else if ((choice == KEY_DOWN && currMenu == 3) || (choice == KEY_DOWN && currMenu == 0)){
                system("cls");
                currMenu = 4;
                splashScreen();
                clearColorAndBackground();
                std::cout<<"\nPlay game\n";
                clearColorAndBackground();
                std::cout<<"Instructions\n";
                clearColorAndBackground();
                std::cout<<"About\n";
                SetColorAndBackground();
                std::cout<<"Quit";
                clearColorAndBackground();
            }
            else if(choice == 13 && currMenu == 1){
                playGame();
            }
            else if(choice == 13 && currMenu == 2){
                instructionsDisplay();
            }
            else if(choice == 13 && currMenu == 3){
                aboutProgram();
            }
            else if(choice == 13 && currMenu == 4){
                system("cls");
                std::cout<<"Would you like to quit?\n\nYes\nNo";
                int yesNo = 0, currMenu1 = 0;
                while(1){
                    yesNo = getch();
                    if(yesNo == KEY_UP){
                        currMenu1 = 1;
                        system("cls");
                        clearColorAndBackground();
                        std::cout<<"Would you like to quit?\n\n";
                        SetColorAndBackground();
                        std::cout<<"Yes\n";
                        clearColorAndBackground();
                        std::cout<<"No";
                        clearColorAndBackground();
                    }
                    else if(yesNo == KEY_DOWN){
                        currMenu1 = 2;
                        system("cls");
                        clearColorAndBackground();
                        std::cout<<"Would you like to quit?\n\n";
                        clearColorAndBackground();
                        std::cout<<"Yes\n";
                        SetColorAndBackground();
                        std::cout<<"No";
                        clearColorAndBackground();
                    }
                    else if(yesNo == 13 && currMenu1 == 1){
                        system("cls");
                        exit(0);
                    }
                    else if(yesNo == 13 && currMenu1 == 2){
                        system("cls");
                        menu();
                    }
                }
            }
    }
}
*/

#endif // CHESSIO_H_INCLUDED
