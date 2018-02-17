#include "ChessDesign.h"
void menu();
enum pieces{pEmpty, pawn, knight, bishop, rook, queen, king}; //for types of pieces in the game
enum sides{black, white, neutral}; //sides in the game
enum turns{player, player2, computer}; //although there is a player2 type, we might not use it due to the constraint of time :)
enum playMode{playerVersusAI, playerVSplayer}; //play mode for the game
bool hasMovedLRook=false; //For Castling
bool hasMovedRRook=false; //For Castling
bool hasMovedKing=false; //For Castling
bool hasMovedLRook2=false;
bool hasMovedRRook2=false;
bool hasMovedKing2=false;
bool playerVsAIBlack=false;
turns currentTurn;
turns previousTurn;
struct xy{ //Coordinates
    int col,row;
};

struct aiMove{
    int row, col, value;
};

struct cell{ //this structure entails the piece in the certain cell, its side, and its valid moves
    pieces piece;
    sides side;
    vector<struct aiMove> validMoves;
    int row, col;
};

struct aiPiece{
    pieces piece;
    int rowFrom, colFrom;
    int rowBest, colBest;
    vector<struct xy> validMoves;
    int value;
};

cell board[8][8];

class chessGame{
public:
    void boardInit(sides);
    void printBoard();
    void printPiece(pieces, sides, int, int);
    void getMove(sides);
    void makeMove(int, int, int, int, sides);
    void rotateBoard();
    void doCastling(int, int, int, int);
    void promotePawn(int, int, int, int); //Promotion
    void aiGenerateMove();
    void twoPlayerResults();
    void EndGame();
    void returnToMenu();
    aiPiece getMoveAI(sides);
    int convertRank(char);
    int convertFile(char);
    int chooseMode();
    int twoPlayerGame(string, string);
    int playerVsAI();
    int getPieceValue(pieces);
    bool isValidPick(int, int, sides);
    bool isCheck(int, int, sides);
    bool isCheckMate(int, int, sides);
    bool isValidMove(int, int, int, int);
    vector<xy> vmPawn(int, int,sides);
    vector<xy> getValidMoves(int, int, pieces, sides);
    vector<xy> vmKnight(int, int, sides);
    vector<xy> vmRook(int, int, sides);
    vector<xy> vmBishop(int, int, sides);
    vector<xy> vmQueen(int, int, sides);
    vector<xy> vmKing(int, int, sides);
    vector<xy> vmPawn2(int, int, sides);
    string getName(int);
    playMode getMode();
    aiPiece pickBestPieceAndMove(vector<aiPiece>, sides);
    aiMove getBestMoveOfPiece(aiPiece, sides);
    aiMove getBestFromValid(vector<xy>, sides, int, int);
    vector<sides> chooseSide(string, string);
    xy getPieceCheck(int, int, sides);
    xy getKing(sides);
    void Resign();

private:
    string player1Name, player2Name;
    playMode mode;
    vector<sides> sideChosen;
    sides side_player, side_ai;

};

void chessGame::boardInit(sides side){
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            board[i][j].piece=pEmpty;
            board[i][j].side=neutral; //Initialize the whole board
        }
    }
    //board[2][2].side=black;
    board[0][0].piece=board[0][7].piece=board[7][0].piece=board[7][7].piece=rook; //place rooks in board
    board[0][1].piece=board[0][6].piece=board[7][1].piece=board[7][6].piece=knight;//board[2][2].piece=knight; //
    board[0][2].piece=board[0][5].piece=board[7][2].piece=board[7][5].piece=bishop;
    if(side==white){
        board[0][3].piece=board[7][3].piece=queen;
        board[0][4].piece=board[7][4].piece=king;
    }else{
        board[0][3].piece=board[7][3].piece=king;
        board[0][4].piece=board[7][4].piece=queen;
    }

    for(int j=0,i=1; j<8; j++){
        board[i][j].piece=pawn;
    }
    for(int j=0,i=6; j<8; j++){
        board[i][j].piece=pawn;
    }

    for(int i=0; i<2; i++){ //initialize side of AI to black
        for(int j=0; j<8; j++){
            if(side==white){
                board[i][j].side=black;
            }else{
                board[i][j].side=white;
            }
        }
    }
    for(int i=6; i<8; i++){
        for(int j=0; j<8; j++){
            if(side==white){
                board[i][j].side=white;
            }else{
                board[i][j].side=black;
            }

        }
    }
}

void chessGame::printBoard(){
    system("cls");
    cout << "   " << (char)201;
    for(int j=0; j<26; j++){
        //if(j==4) cout << (char)209;
        cout << (char)205;
    }
    cout << (char)187;
    cout <<endl;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(j==0) cout << " " << 8-i <<" "<<(char)186<< " ";
            printPiece(board[i][j].piece, board[i][j].side,i,j);
            if(j==7) cout << " " <<(char)186;
        }
        cout <<endl;
    }
    cout << "   " << (char)200;
    for(int j=0; j<26; j++){
        cout <<(char)205;
    }
    cout << (char)188 << endl;
    cout << "      A  B  C  D  E  F  G  H"<<endl;
}

void chessGame::printPiece(pieces piece, sides side, int rowNo, int columnNo){
    if(((rowNo + 1) % 2 == 0) && ((columnNo + 1) % 2 != 0) && side == black) setFColorBlackOnMagenta();
    else if(((rowNo + 1) % 2 == 0) && ((columnNo + 1) % 2 != 0) && side == white) setFColorWhiteOnMagenta();
    else if(((rowNo + 1) % 2 != 0) && ((columnNo + 1) % 2 == 0) && side == black) setFColorBlackOnMagenta();
    else if(((rowNo + 1) % 2 != 0) && ((columnNo + 1) % 2 == 0) && side == white) setFColorWhiteOnMagenta();
    else if(side == black) setFColorBlackOnBlue();
    else if (side == white) setFColorWhiteOnBlue();
    else if(((rowNo + 1) % 2 == 0) && ((columnNo + 1) % 2 != 0)) setFColorBlackOnMagenta();
    else if(((rowNo + 1) % 2 == 0) && ((columnNo + 1) % 2 != 0)) setFColorWhiteOnMagenta();
    else if(((rowNo + 1) % 2 != 0) && ((columnNo + 1) % 2 == 0)) setFColorBlackOnMagenta();
    else if(((rowNo + 1) % 2 != 0) && ((columnNo + 1) % 2 == 0)) setFColorWhiteOnMagenta();
    else setFColorWhiteOnBlue();switch(piece){
        case king: cout<<" K "; break;
        case queen:cout<<" Q "; break;
        case rook: cout<<" R "; break;
        case bishop: cout<<" B "; break;
        case knight:cout<< " N "; break;
        case pawn: cout<< " P "; break;
        case pEmpty: cout << "   "; break;
    }
    clearColorAndBackground();
}

void chessGame::makeMove(int fromRow, int fromCol, int toRow, int toCol, sides side){
    if(board[fromRow][fromCol].piece==rook && fromRow==7 && fromCol==0 && side==white) hasMovedLRook=true;
    if(board[fromRow][fromCol].piece==rook && fromRow==7 && fromCol==7 && side==white) hasMovedRRook=true;
    if(board[fromRow][fromCol].piece==king && fromRow==7 && fromCol==4 && side==white) hasMovedKing=true;
    if(board[fromRow][fromCol].piece==rook && fromRow==7 && fromCol==0 && side==black) hasMovedLRook2=true;
    if(board[fromRow][fromCol].piece==rook && fromRow==7 && fromCol==7 && side==black) hasMovedRRook2=true;
    if(board[fromRow][fromCol].piece==king && fromRow==7 && fromCol==3 && side==black) hasMovedKing2=true;
    if(board[fromRow][fromCol].piece==pawn && toRow==0){
        promotePawn(fromRow, fromCol, toRow, toCol);
    }
    if(board[fromRow][fromCol].piece==king && fromRow==7 && fromCol==4 && side==white && (toRow==7 && (toCol==2 || toCol==6))){
        cout<< "<- Castling ->"<<endl;
        system("pause");
        doCastling(fromRow, fromCol, toRow, toCol);
    }else if(board[fromRow][fromCol].piece==king && fromRow==7 && fromCol==3 && side==black && (toRow==7 && (toCol==1 || toCol==5))){
        cout<< "<- Castling ->"<<endl;
        system("pause");
        doCastling(fromRow, fromCol, toRow, toCol);
    }else{
        //cout << toRow << "," << toCol;
        //system("pause");
        board[toRow][toCol].piece=board[fromRow][fromCol].piece;
        board[toRow][toCol].side=board[fromRow][fromCol].side;
        board[fromRow][fromCol].piece=pEmpty;
        board[fromRow][fromCol].side=neutral;
    }
}

void chessGame::doCastling(int fromRow, int fromCol, int toRow, int toCol){
    if(toCol==2){
        board[7][2].piece=board[fromRow][fromCol].piece; //places king two to the left
        board[7][2].side=board[fromRow][fromCol].side;
        board[fromRow][fromCol].piece=pEmpty;
        board[fromRow][fromCol].side=neutral;
        board[7][3].piece=board[7][0].piece;
        board[7][3].side=board[7][0].side;
        board[7][0].piece=pEmpty;
        board[7][0].side=neutral;
    }
    if(toCol==6){
        board[7][6].piece=board[fromRow][fromCol].piece; //places king two to the left
        board[7][6].side=board[fromRow][fromCol].side;
        board[fromRow][fromCol].piece=pEmpty;
        board[fromRow][fromCol].side=neutral;
        board[7][5].piece=board[7][7].piece;
        board[7][5].side=board[7][7].side;
        board[7][7].piece=pEmpty;
        board[7][7].side=neutral;
    }
    if(toCol==1){
        board[7][1].piece=board[fromRow][fromCol].piece;
        board[7][1].side=board[fromRow][fromCol].side;
        board[fromRow][fromCol].piece=pEmpty/*==srand(50,0))*/;
        board[fromRow][fromCol].side=neutral;
        board[7][2].piece=board[7][0].piece;
        board[7][2].side=board[7][0].side;
        board[7][0].piece=pEmpty;
        board[7][0].side=neutral;
    }
    if(toCol==5){
        board[7][5].piece=board[fromRow][fromCol].piece;
        board[7][5].side=board[fromRow][fromCol].side;
        board[fromRow][fromCol].piece=pEmpty;
        board[fromRow][fromCol].side=neutral;
        board[7][4].piece=board[7][7].piece;
        board[7][4].side=board[7][7].side;
        board[7][7].piece=pEmpty;
        board[7][7].side=neutral;
    }
}

void chessGame::promotePawn(int fromRow, int fromCol, int toRow, int toCol){
    cout << "Your pawn reached the 8th file.\nChoose your promotion:\n";
    cout << "Q - Queen\tN - Knight\nR - Rook\tB - Bishop\n";
    cout << "Promote to: ";
    char choice;
    do{
        cin>>choice;
    }while(toupper(choice)!='Q' && toupper(choice)!='N' && toupper(choice)!='R' && toupper(choice)!='B');
    switch(toupper(choice)){
        case'Q':board[fromRow][fromCol].piece=queen;
                break;
        case'N':board[fromRow][fromCol].piece=knight;
                break;
        case'R':board[fromRow][fromCol].piece=rook;
                break;
        case'B':board[fromRow][fromCol].piece=bishop;
                break;
    }
}


void chessGame::rotateBoard(){
    cell temp;
    for(int i=0; i<4; i++){
        for(int j=0; j<8; j++){
            //swap pieces
            temp.piece=board[i][j].piece;
            temp.side=board[i][j].side;
            board[i][j].piece=board[7-i][7-j].piece;
            board[i][j].side=board[7-i][7-j].side;
            board[7-i][7-j].piece=temp.piece;
            board[7-i][7-j].side=temp.side;
        }
    }
}

void chessGame::getMove(sides side){
    struct xy pos1;
    struct xy pos2;
    vector<xy> vm; //valid moves
    string str_pos1, str_pos2;
    vector <xy> kingVM;
    bool isLooped=false;
    //get king position
    xy kingPos;
    for(int i=0; i<=7; i++){
        for(int j=0; j<=7; j++){
            if(board[i][j].piece==king && board[i][j].side==side){
                kingPos.row=i;
                kingPos.col=j;
                break;
            }
        }
    }
    kingVM=getValidMoves(kingPos.row, kingPos.col, board[kingPos.row][kingPos.col].piece, board[kingPos.row][kingPos.col].side);
    // then check
    if(isCheck(kingPos.row, kingPos.col, side)){
        cout << "CHECK";
        if(isCheckMate(kingPos.row, kingPos.col, side)){
            cout << "MATE";
            EndGame();
        }
        cout<<endl;
        /*
        if(isCheckMate(kingPos.row, kingPos.col, side)){
            if(side==white) cout << "Checkmate - White wins!";
            if(side==black) cout << "Checkmate - Black wins!";
            //go to menu gawa ka function congratulations then return sa menu
        }
        // required na i move yung king
        pos1.row=kingPos.row;
        pos1.col=kingPos.col;
        cout << "Where do you want the king to move: (ex. B4)";
        do{
            getline(cin, str_pos2);
            pos2.col=convertRank(str_pos2[0]);
            pos2.row=convertFile(str_pos2[1]);
        }while(!isValidMove(pos1.row, pos1.col, pos2.row, pos2.col));
        cout << "Move: "<< str_pos2<<endl;
        */


    }
    cell pieceFrom, pieceTo;
    do{

        cout << "Piece you want to move: (Enter \"resign\" to quit)";
        do{
            getline(cin, str_pos1);
            pos1.col=convertRank(str_pos1[0]);
            pos1.row=convertFile(str_pos1[1]);
            if(str_pos1=="resign"){
                menu();
            }
        }while(!isValidPick(pos1.row, pos1.col, side) || str_pos1.length()>2);
        /*
        pieceFrom.row=pos1.row;
        pieceFrom.col=pos1.col;
        pieceFrom.piece=board[pos1.row][pos1.col].piece;
        pieceFrom.side=board[pos1.row][pos2.col].side;
        */
        cout << "Pick: "<< str_pos1 << endl;
        cout << "Where do you want this piece to move: (ex. B4)";
        do{
            getline(cin, str_pos2);
            pos2.col=convertRank(str_pos2[0]);
            pos2.row=convertFile(str_pos2[1]);
        }while(!isValidMove(pos1.row, pos1.col, pos2.row, pos2.col));

        pieceTo.row=pos2.row;
        pieceTo.col=pos2.col;
        pieceTo.piece=board[pos2.row][pos2.col].piece;
        pieceTo.side=board[pos2.row][pos2.col].side;

        cout << "Move: "<< str_pos2<<endl;
        makeMove(pos1.row, pos1.col, pos2.row, pos2.col, side);
        kingPos=getKing(side);
        if(isCheck(kingPos.row, kingPos.col, side)){
            board[pos1.row][pos1.col].piece=board[pos2.row][pos2.col].piece;
            board[pos1.row][pos1.col].side=board[pos2.row][pos2.col].side;
            board[pos2.row][pos2.col].piece=pieceTo.piece;
            board[pos2.row][pos2.col].side=pieceTo.side;
            cout << "Invalid move: Still in check\n";
        }
        isLooped=true;
    }while(isCheck(kingPos.row, kingPos.col, side));
    system("pause");
    //makeMove(pos1.row, pos1.col, pos2.row, pos2.col, side);
}

int chessGame::convertRank(char c){
    return toupper(c)-65;
}

int chessGame::convertFile(char c){
    return 8-((int)c-48);
}

int chessGame::chooseMode(){
    int choice = 0, currMenu = 0;
    system("cls");
    cout<<"Choose a mode of play:\n\nPlayer vs AI\nPlayer vs Player";
    while(1){
        choice = getch();
        if((choice == KEY_UP && currMenu == 0) || (choice == KEY_UP && currMenu == 2)){
            currMenu = 1;
            system("cls");
            clearColorAndBackground();
            cout<<"Choose a mode of play: \n\n";
            SetColorAndBackground();
            cout<<"Player vs AI\n";
            clearColorAndBackground();
            cout<<"Player vs Player";
            clearColorAndBackground();
        }
        else if ((choice == KEY_DOWN && currMenu == 0) || (choice == KEY_DOWN && currMenu == 1)){
            currMenu = 2;
            system("cls");
            clearColorAndBackground();
            cout<<"Choose a mode of play: \n\n";
            clearColorAndBackground();
            cout<<"Player vs AI\n";
            SetColorAndBackground();
            cout<<"Player vs Player";
            clearColorAndBackground();
        }
        else if (choice == 13 && currMenu == 1){
            mode = playerVersusAI;
            return 0;
        }
        else if (choice == 13 && currMenu == 2){
            mode = playerVSplayer;
            return 0;
        }
    }

}

int chessGame::twoPlayerGame(string p1name, string p2name){
    turns currentTurn;
    vector<sides> sideAssignment = chooseSide(p1name, p2name);
    sides p1side = sideAssignment[0], p2side = sideAssignment[1];
    if(p1side==white){
        currentTurn=player;
    }else{
        currentTurn=player2;
    }
    if(p1side==white){
        currentTurn=player;
    }else{
        currentTurn=player2;
    }
    while(1){
        printBoard();
        if(currentTurn==player){
            if(toupper(p1name[p1name.length() - 1]) == 'S') cout << p1name <<"' turn\n";
            else cout << p1name <<"'s turn\n";
            getMove(p1side);
        }else{
            if(toupper(p2name[p2name.length() - 1]) == 'S') cout << p2name <<"' turn\n";
            else cout << p2name <<"'s turn\n";
            getMove(p2side);
        }
        if(currentTurn==player){
            currentTurn=player2;
            previousTurn=player;
        }else{
            currentTurn=player;
            previousTurn=player2;
        }
        rotateBoard();
    }
}

bool chessGame::isValidPick(int row, int col, sides side){ //valid choice of piece for the player
    vector<xy> vm;
    vm=getValidMoves(row, col, board[row][col].piece,board[row][col].side);
    if(vm.empty()==true){
        return false;
    }
    if(side==white){
        if(board[row][col].side!=white) return false;
    }else{ // if black
        if(board[row][col].side!=black) return false;
    }

    return true;
}

bool chessGame::isValidMove(int rowFrom, int colFrom, int row, int col){
    vector <xy> vm;
    vm=getValidMoves(rowFrom, colFrom, board[rowFrom][colFrom].piece,board[rowFrom][colFrom].side);
    //cout << vm[0].row << ", " << vm[0].col << endl;
    if(isCheck(row, col, board[rowFrom][colFrom].side) && board[rowFrom][colFrom].piece==king) return false; // false if the king is check in the next move
    for(int i=0; i<vm.size(); i++){
        if(row==vm[i].row && col==vm[i].col) return true;
    }
    return false;
}

bool chessGame::isCheck(int row, int col, sides side){
    xy temp;
    int k=0;
    vector<xy> enemyMoves;
    vector<xy> eMtemp;
    //sides eSide;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j].side!=side){
                //eMtemp=getValidMoves(i, j, board[i][j].piece, board[i][j].side);
                if(board[i][j].piece==pawn){
                    //cout << i<<","<<j<<endl;
                    //cout << eMtemp[k].row <<"-"<<eMtemp[k].row<<endl;
                    eMtemp=vmPawn2(i, j, board[i][j].side);
                    enemyMoves.insert(enemyMoves.end(), eMtemp.begin(), eMtemp.end());
                    eMtemp.clear();

                }else{
                    eMtemp=getValidMoves(i, j, board[i][j].piece, board[i][j].side);
                    enemyMoves.insert(enemyMoves.end(), eMtemp.begin(), eMtemp.end());
                    eMtemp.clear();
                }

              //  enemyMoves.insert(enemyMoves.end(), eMtemp.begin(), eMtemp.end());
             //   eMtemp.clear();
            }
        }
    }

    //cout << "\n\n";
    /*
    for(int i=0; i<enemyMoves.size(); i++){
        cout<<enemyMoves[i].row<<"-"<<enemyMoves[i].col<<endl;
    }
    */
    /*
    //xy pieceCheck; //yung piece na nag check sa king
    //pieceCheck=getPieceCheck(row, col, side);
    //cout << "The piece = " << board[pieceCheck.row][pieceCheck.col].piece;
    //system("pause");
    */
    for(int i=0; i<enemyMoves.size(); i++){
        if(enemyMoves[i].row==row && enemyMoves[i].col==col){
            return true;
        }
    }
    return false;
}

bool chessGame::isCheckMate(int row, int col, sides side){
    vector<aiPiece> allValidPieces;
    aiPiece temp;
    cell pieceTo;
    xy kingPos;
    bool checkmate=true;
    /*
    for(int a=0; a<=7; a++){
        for(int b=0; b<=7; b++){
            if(board[a][b].piece==king && board[a][b].side==side){
                kingPos.row=a;
                kingPos.col=b;
                break;
            }
        }
    }
    */
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j].side==side){
                temp.rowFrom=i+1;
                temp.colFrom=j-1;
                temp.piece=board[i][j].piece;
                allValidPieces.push_back(temp);
            }
        }
    }
    for(int i=0; i<allValidPieces.size(); i++){
        allValidPieces[i].validMoves=getValidMoves(allValidPieces[i].rowFrom, allValidPieces[i].colFrom, board[allValidPieces[i].rowFrom][allValidPieces[i].colFrom].piece, side);
    }
    for(int i=0; i<allValidPieces.size(); i++){
        for(int j=0; j<allValidPieces[i].validMoves.size(); j++){
            pieceTo.row=allValidPieces[i].validMoves[j].row;
            pieceTo.col=allValidPieces[i].validMoves[j].col;
            pieceTo.piece=board[allValidPieces[i].validMoves[j].row][allValidPieces[i].validMoves[j].col].piece;
            pieceTo.side=board[allValidPieces[i].validMoves[j].row][allValidPieces[i].validMoves[j].col].side;
            //cout <<"Make move\n"<<allValidPieces[i].rowFrom<<"-"<<allValidPieces[i].colFrom<<"    ->    " <<allValidPieces[i].validMoves[j].row<< "-" <<allValidPieces[i].validMoves[j].col<<endl;
            makeMove(allValidPieces[i].rowFrom, allValidPieces[i].colFrom, allValidPieces[i].validMoves[j].row, allValidPieces[i].validMoves[j].col, side);
            //cout << side<<"<-"<<endl;
            kingPos=getKing(side);
            if(!isCheck(kingPos.row,kingPos.col, side)){
                //cout << kingPos.row << "," << kingPos.col<<endl;
                checkmate=false;

            }
                    //checkmate=false;

            board[allValidPieces[i].rowFrom][allValidPieces[i].colFrom].piece=board[allValidPieces[i].validMoves[j].row][allValidPieces[i].validMoves[j].col].piece;
            board[allValidPieces[i].rowFrom][allValidPieces[i].colFrom].side=board[allValidPieces[i].validMoves[j].row][allValidPieces[i].validMoves[j].col].side;
            board[allValidPieces[i].validMoves[j].row][allValidPieces[i].validMoves[j].col].piece=pieceTo.piece;
            board[allValidPieces[i].validMoves[j].row][allValidPieces[i].validMoves[j].col].side=pieceTo.side;
        }
    }
    return checkmate;
}



vector <xy> chessGame::getValidMoves(int row, int col, pieces piece, sides side){ //This function gets the set of valid moves for a certain piece
    //cout << "row = " << row << "col = " << col<<endl;
    //piece=board[row][col].piece;
    //sides side=board[row][col].side;
    //cout << "piece" << piece<<endl;
    vector <xy> vm;
    switch(piece){
        case pawn: vm=vmPawn(row, col, side); break;
        case knight: vm=vmKnight(row, col, side); break;
        case rook: vm=vmRook(row, col, side); break;
        case bishop: vm=vmBishop(row, col, side); break;
        case queen: vm=vmQueen(row, col, side); break;
        case king: vm=vmKing(row, col, side); break;
    }
    return vm;
}

xy chessGame::getKing(sides side){
    xy kingPos;
        for(int a=0; a<=7; a++){
            for(int b=0; b<=7; b++){
                if(board[a][b].piece==king && board[a][b].side==side){
                    kingPos.row=a;
                    kingPos.col=b;
                    break;
                }
            }
        }
        return kingPos;
}

vector<xy> chessGame::vmPawn(int row, int col, sides side){ //Valid moves for Pawn
    vector <xy> vm;
    xy temp;
    temp.col=col;
    //cout << row<<endl;
    if(mode==playerVSplayer || currentTurn==player){
        if(row==6 && board[4][col].piece==pEmpty && board[5][col].piece==pEmpty){ //If the pawn is unmoved and the cells in front of it are empty
            temp.col=col;
            temp.row=4;
            vm.push_back(temp);
        }
        if(board[row-1][col].piece==pEmpty && row-1>=0){ //directly in front of pawn
            temp.col=col;
            temp.row=row-1;
            vm.push_back(temp);
        }
        if(board[row-1][col+1].piece!=pEmpty && board[row-1][col+1].side!=side && row-1>=0 && col+1<=7){  // upper right corner eat
            temp.col=col+1;
            temp.row=row-1;
            vm.push_back(temp);
        }
        if(board[row-1][col-1].piece!=pEmpty && board[row-1][col-1].side!=side && row-1>=0 && col-1>=0){ // upper left corner eat
            temp.col=col-1;
            temp.row=row-1;
            vm.push_back(temp);
        }
        return vm;
    }
    if(mode==playerVersusAI && currentTurn==computer){
        if(row==1 && board[2][col].piece==pEmpty && board[3][col].piece==pEmpty){
            temp.col=col;
            temp.row=3;
            vm.push_back(temp);
        }
        if(board[row+1][col].piece==pEmpty && row+1<=7){
            temp.col=col;
            temp.row=row+1;
            vm.push_back(temp);
        }
        if(board[row+1][col-1].piece!=pEmpty && board[row+1][col-1].side!=side && row+1<=7 && col-1>=0){
            temp.col=col-1;
            temp.row=row+1;
            vm.push_back(temp);
        }
        if(board[row+1][col+1].piece!=pEmpty && board[row+1][col+1].side!=side && row+1<=7 && col+1<=7){
            temp.col=col+1;
            temp.row=row+1;
            vm.push_back(temp);
        }
    }

    /*
    cout << "valid,\n";
    for(int i=0; i<vm.size(); i++){
        cout << vm[i].row << ", " << vm[i].col << endl;
    }
    system("pause");
    */
    return vm;
}

vector<xy> chessGame::vmPawn2(int row, int col, sides side){
    vector<xy> vm;
    xy temp;
        if(row==1 && board[2][col].piece==pEmpty && board[3][col].piece==pEmpty){
            temp.col=col;
            temp.row=3;
            vm.push_back(temp);
        }
        if(board[row+1][col].piece==pEmpty && row+1<=7){
            temp.col=col;
            temp.row=row+1;
            vm.push_back(temp);
        }
        if(board[row+1][col-1].piece!=pEmpty && board[row+1][col-1].side!=side && row+1<=7 && col-1>=0){
            temp.col=col-1;
            temp.row=row+1;
            vm.push_back(temp);
        }
        if(board[row+1][col+1].piece!=pEmpty && board[row+1][col+1].side!=side && row+1<=7 && col+1<=7){
            temp.col=col+1;
            temp.row=row+1;
            vm.push_back(temp);
        }

    return vm;
}

vector<xy> chessGame::vmKnight(int row, int col, sides side){
    vector <xy> vm;
    xy temp;
    temp.col=col;
        if(board[row-2][col-1].side!=side && row-2>=0 && col-1>=0){ // 2 up 1left
            temp.row=row-2;
            temp.col=col-1;
            vm.push_back(temp);
        }
        if(board[row-2][col+1].side!=side && row-2>=0 && col+1<=7){ // 2up 1 right
            temp.row=row-2;
            temp.col=col+1;
            vm.push_back(temp);
        }
        if(board[row-1][col-2].side!=side && row-1>=0 && col-2>=0){ // 1 up 2 left
            temp.row=row-1;
            temp.col=col-2;
            vm.push_back(temp);
        }
        if(board[row-1][col+2].side!=side && row-1>=0 && col+2<=7){ // 1 up 2 right
            temp.row=row-1;
            temp.col=col+2;
            vm.push_back(temp);
        }
        if(board[row+2][col+1].side!=side && row+2<=7 && col+1<=7){ // 2 down 1 right
            temp.row=row+2;
            temp.col=col+1;
            vm.push_back(temp);
        }
        if(board[row+2][col-1].side!=side && row+2<=7 && col-1>=0){ // 2 down 1 left
            temp.row=row+2;
            temp.col=col-1;
            vm.push_back(temp);
        }
        if(board[row+1][col-2].side!=side && row+1<=7 && col-2>=0){ // 1 down 2 left
            temp.row=row+1;
            temp.col=col-2;
            vm.push_back(temp);
        }
        if(board[row+1][col+2].side!=side && row+1<=7 && col+2<=7){ // 1 down 2 right
            temp.row=row+1;
            temp.col=col+2;
            vm.push_back(temp);
        }
    /*
    for(int i=0; i<vm.size(); i++){
        cout << vm[i].row << ", " << vm[i].col << endl;
    }
    system("pause");
    */
    return vm;
}

vector<xy> chessGame::vmRook(int row, int col, sides side){
    vector<xy> vm;
    xy temp;
    temp.col=col;
    for(int i=row-1; i>=0; i--){  // upwards
        if(board[i][col].piece==pEmpty){
            temp.row=i;
            temp.col=col;
            vm.push_back(temp);
        }else if(board[i][col].side!=side){
            temp.row=i;
            temp.col=col;
            vm.push_back(temp);
            break;
        }else break;
    }
    for(int i=row+1; i<=7; i++){ // downwards
        if(board[i][col].piece==pEmpty){
            temp.row=i;
            temp.col=col;
            vm.push_back(temp);
        }else if(board[i][col].side!=side){
            temp.row=i;
            temp.col=col;
            vm.push_back(temp);
            break;
        }else break;
    }
    for(int j=col+1; j<=7; j++){ //right
        if(board[row][j].piece==pEmpty){
            temp.row=row;
            temp.col=j;
            vm.push_back(temp);
        }else if(board[row][j].side!=side){
            temp.row=row;
            temp.col=j;
            vm.push_back(temp);
            break;
        }else break;
    }
    for(int j=col-1; j>=0; j--){ //left
        if(board[row][j].piece==pEmpty){
            temp.row=row;
            temp.col=j;
            vm.push_back(temp);
        }else if(board[row][j].side!=side){
            temp.row=row;
            temp.col=j;
            vm.push_back(temp);
            break;
        }else break;
    }
    return vm;
}

vector<xy> chessGame::vmBishop(int row, int col, sides side){
    vector<xy> vm;
    xy temp;
    temp.col=col;
    for(int i=row-1, j=col-1; i>=0 && j>=0; i--,j--){ //upper left
        if(board[i][j].piece==pEmpty){
            temp.row=i;
            temp.col=j;
            vm.push_back(temp);
        }else if(board[i][j].side!=side){
            temp.row=i;
            temp.col=j;
            vm.push_back(temp);
            break;
        }else break;
    }
    for(int i=row-1, j=col+1; i>=0 && j<=7; i--, j++){ //upper right
        if(board[i][j].piece==pEmpty){
            temp.row=i;
            temp.col=j;
            vm.push_back(temp);
        }else if(board[i][j].side!=side){
            temp.row=i;
            temp.col=j;
            vm.push_back(temp);
            break;
        }else break;
    }
    for(int i=row+1, j=col-1; i<=7 && j>=0; i++, j--){ // lower left
        if(board[i][j].piece==pEmpty){
            temp.row=i;
            temp.col=j;
            vm.push_back(temp);
        }else if(board[i][j].side!=side){
            temp.row=i;
            temp.col=j;
            vm.push_back(temp);
            break;
        }else break;
    }
    for(int i=row+1, j=col+1; i<=7 && j<=7;  i++, j++){ //lower right
        if(board[i][j].piece==pEmpty){
            temp.row=i;
            temp.col=j;
            vm.push_back(temp);
        }else if(board[i][j].side!=side){
            temp.row=i;
            temp.col=j;
            vm.push_back(temp);
            break;
        }else break;
    }
    return vm;
}

vector<xy> chessGame::vmQueen(int row, int col, sides side){
    vector<xy> vm, vm_rook, vm_bishop;
    vm_rook=vmRook(row, col, side);
    vm_bishop=vmBishop(row, col, side);
    vm.insert(vm.end(), vm_rook.begin(), vm_rook.end());
    vm.insert(vm.end(), vm_bishop.begin(), vm_bishop.end());
    return vm;
}

vector<xy> chessGame::vmKing(int row, int col, sides side){
    vector<xy> vm;
    xy temp;
    if(side==white && row==7 && col==4 && board[7][3].piece==pEmpty && board[7][2].piece==pEmpty && board[7][1].piece==pEmpty && hasMovedLRook==false && hasMovedKing==false){ //castling
        temp.row=7;
        temp.col=2;
        vm.push_back(temp);
    }
    if(side==white && row==7 && col==4 && board[7][5].piece==pEmpty && board[7][6].piece==pEmpty && hasMovedRRook==false && hasMovedKing==false){ //castling
        temp.row=7;
        temp.col=6;
        vm.push_back(temp);
    }
    if(side==black && row==7 && col==3 && board[7][2].piece==pEmpty && board[7][1].piece==pEmpty && hasMovedKing2==false && hasMovedLRook2==false){
        temp.row=7;
        temp.col=1;
        vm.push_back(temp);
    }
    if(side==black && row==7 && col==3 && board[7][4].piece==pEmpty && board[7][5].piece==pEmpty && board[7][6].piece==pEmpty && hasMovedKing2==false && hasMovedRRook2==false){
        temp.row=7;
        temp.col=5;
        vm.push_back(temp);
    }
    if(board[row-1][col].side!=side && row-1>=0){
        temp.row=row-1;
        temp.col=col;
        vm.push_back(temp);
    }
    if(board[row+1][col].side!=side && row+1<=7){
        temp.row=row+1;
        temp.col=col;
        vm.push_back(temp);
    }
    if(board[row][col-1].side!=side && col-1>=0){
        temp.row=row;
        temp.col=col-1;
        vm.push_back(temp);
    }
    if(board[row][col+1].side!=side && col+1<=7){
        temp.row=row;
        temp.col=col+1;
        vm.push_back(temp);
    }
    if(board[row-1][col-1].side!=side && row-1>=0 && col-1>=0){
        temp.row=row-1;
        temp.col=col-1;
        vm.push_back(temp);
    }
    if(board[row-1][col+1].side!=side && row-1>=0 && col+1<=7){
        temp.row=row-1;
        temp.col=col+1;
        vm.push_back(temp);
    }
    if(board[row+1][col-1].side!=side && row+1<=7 && col-1>=0){
        temp.row=row+1;
        temp.col=col-1;
        vm.push_back(temp);
    }
    if(board[row+1][col+1].side!=side && row+1<=7 && col+1<=7){
        temp.row=row+1;
        temp.col=col+1;
        vm.push_back(temp);
    }

    return vm;
}

string chessGame::getName(int playerNumber){
    string name;
    system("cls");
    switch(playerNumber){
        case 1:{
            cout<<"Enter your name (Player 1): ";
            getline(cin, name);
            player1Name = name;
        }break;
        case 2:{
            cout<<"Enter your name (Player 2): ";
            getline(cin, name);
            player2Name = name;
        }break;
    }
    return name;
}

playMode chessGame::getMode(){
    return mode;
}

vector<sides> chessGame::chooseSide(string p1name, string p2name){
    funct:
    int currMenu = 0, choice = 0, yesNoMenu = 0, yesNoChoice = 0;
    vector<sides> side;
    clearColorAndBackground();
    system("cls");
    cout<<"Which player will pick ";
    setColorAndBackgroundWhite();
    cout<<"WHITE";
    clearColorAndBackground();
    cout<<"?\n\nNOTE: White goes first in the game.\n\n"<<player1Name<<endl
        <<player2Name;
    while(1){
        choice = getch();
        if((choice == KEY_UP && currMenu == 0) || (choice == KEY_UP && currMenu == 2)){
            currMenu = 1;
            system("cls");
            clearColorAndBackground();
            cout<<"Which player will pick ";
            setColorAndBackgroundWhite();
            cout<<"WHITE";
            clearColorAndBackground();
            cout<<"?\n\nNOTE: White goes first in the game.\n\n";
            SetColorAndBackground();
            cout<<player1Name<<endl;
            clearColorAndBackground();
            cout<<player2Name;
            clearColorAndBackground();
        }
        else if((choice == KEY_DOWN && currMenu == 1) || (choice == KEY_DOWN && currMenu == 0)){
            currMenu = 2;
            system("cls");
            clearColorAndBackground();
            cout<<"Which player will pick ";
            setColorAndBackgroundWhite();
            cout<<"WHITE";
            clearColorAndBackground();
            cout<<"?\n\nNOTE: White goes first in the game.\n\n";
            clearColorAndBackground();
            cout<<player1Name<<endl;
            SetColorAndBackground();
            cout<<player2Name;
            clearColorAndBackground();
        }
        else if (choice == 13 && currMenu == 1){ //Player 1 is White
            system("cls");
            clearColorAndBackground();
            cout<<"Assignment of Sides\n\n";
            cout<<player1Name<<": ";
            setColorAndBackgroundWhite();
            cout<<"WHITE";
            clearColorAndBackground();
            cout<<"\n"<<player2Name<<": ";
            setColorAndBackgroundBlack();
            cout<<"BLACK";
            clearColorAndBackground();
            cout<<"\n\nAre you sure?\n\nYes\nNo";
            while(1){
                yesNoChoice = getch();
                if((yesNoChoice == KEY_UP && yesNoMenu == 0) || (yesNoChoice == KEY_UP && yesNoMenu == 2)){
                    yesNoMenu = 1;
                    system("cls");
                    clearColorAndBackground();
                    cout<<"Assignment of Sides\n\n";
                    cout<<player1Name<<": ";
                    setColorAndBackgroundWhite();
                    cout<<"WHITE";
                    clearColorAndBackground();
                    cout<<"\n"<<player2Name<<": ";
                    setColorAndBackgroundBlack();
                    cout<<"BLACK";
                    clearColorAndBackground();
                    cout<<"\n\nAre you sure?\n\n";
                    SetColorAndBackground();
                    cout<<"Yes\n";
                    clearColorAndBackground();
                    cout<<"No";
                    clearColorAndBackground();
                }
                else if((yesNoChoice == KEY_DOWN && yesNoMenu == 0) || (yesNoChoice == KEY_DOWN && yesNoMenu == 1)){
                    yesNoMenu = 2;
                    system("cls");
                    clearColorAndBackground();
                    cout<<"Assignment of Sides\n\n";
                    cout<<player1Name<<": ";
                    setColorAndBackgroundWhite();
                    cout<<"WHITE";
                    clearColorAndBackground();
                    cout<<"\n"<<player2Name<<": ";
                    setColorAndBackgroundBlack();
                    cout<<"BLACK";
                    clearColorAndBackground();
                    cout<<"\n\nAre you sure?\n\n";
                    clearColorAndBackground();
                    cout<<"Yes\n";
                    SetColorAndBackground();
                    cout<<"No";
                    clearColorAndBackground();
                }
                else if(yesNoChoice == 13 && yesNoMenu == 1){
                    side.push_back(white);
                    side.push_back(black);
                    return side;
                }
                else if(yesNoChoice == 13 && yesNoMenu == 2){
                    side.clear();
                    //chooseSide(p1name, p2name);
                    goto funct;
                }
            }
        }
        else if (choice == 13 && currMenu == 2){ //Player 2 is white
            system("cls");
            clearColorAndBackground();
            cout<<"Assignment of Sides\n\n";
            cout<<player1Name<<": ";
            setColorAndBackgroundBlack();
            cout<<"BLACK";
            clearColorAndBackground();
            cout<<"\n"<<player2Name<<": ";
            setColorAndBackgroundWhite();
            cout<<"WHITE";
            clearColorAndBackground();
            cout<<"\n\nAre you sure?\n\nYes\nNo";
            while(1){
                yesNoChoice = getch();
                if((yesNoChoice == KEY_UP && yesNoMenu == 0) || (yesNoChoice == KEY_UP && yesNoMenu == 2)){
                    yesNoMenu = 1;
                    system("cls");
                    clearColorAndBackground();
                    cout<<"Assignment of Sides\n\n";
                    cout<<player1Name<<": ";
                    setColorAndBackgroundBlack();
                    cout<<"BLACK";
                    clearColorAndBackground();
                    cout<<"\n"<<player2Name<<": ";
                    setColorAndBackgroundWhite();
                    cout<<"WHITE";
                    clearColorAndBackground();
                    cout<<"\n\nAre you sure?\n\n";
                    SetColorAndBackground();
                    cout<<"Yes\n";
                    clearColorAndBackground();
                    cout<<"No";
                    clearColorAndBackground();
                }
                else if((yesNoChoice == KEY_DOWN && yesNoMenu == 0) || (yesNoChoice == KEY_DOWN && yesNoMenu == 1)){
                    yesNoMenu = 2;
                    system("cls");
                    clearColorAndBackground();
                    cout<<"Assignment of Sides\n\n";
                    cout<<player1Name<<": ";
                    setColorAndBackgroundBlack();
                    cout<<"BLACK";
                    clearColorAndBackground();
                    cout<<"\n"<<player2Name<<": ";
                    setColorAndBackgroundWhite();
                    cout<<"WHITE";
                    clearColorAndBackground();
                    cout<<"\n\nAre you sure?\n\n";
                    clearColorAndBackground();
                    cout<<"Yes\n";
                    SetColorAndBackground();
                    cout<<"No"; //"No" is highlighted
                    clearColorAndBackground();
                }
                else if(yesNoChoice == 13 && yesNoMenu == 1){
                    side.push_back(black);
                    side.push_back(white);
                    return side;
                }
                else if(yesNoChoice == 13 && yesNoMenu == 2){
                    side.clear();
                    //chooseSide(p1name, p2name);
                    goto funct;
                }
            }
        }
    }
}

int chessGame::playerVsAI(){
    aiPiece bestmove;
    string playerName = getName(1);

    cout << "Choose side:\n";
    cout << "1. White\n2. Black\n";
    int choice;
    //sides side_player, side_ai;
    cin >> choice;
    if(choice==1){
        boardInit(white);
        side_player=white;
        side_ai=black;
        currentTurn=player;
    }else{
        boardInit(black);
        side_player=black;
        playerVsAIBlack=true;
        side_ai=white;
        currentTurn=computer;
    }
    while(1){
        printBoard();
        if(currentTurn==player){
            if(previousTurn==computer){
                if(isCheckMate(0,0, side_player)){
                    EndGame();
                }

            cout << "Iris' move is " << (char)(bestmove.colFrom+'A') << 8-bestmove.rowFrom << " to "<< (char)(bestmove.colBest+'A') << 8-bestmove.rowBest <<endl;
            }

            cout << playerName<< "'s turn\n";
            getMove(side_player);
            //makeMove(bestmove.rowFrom, bestmove.colFrom, bestmove.rowBest, bestmove.colBest, side_ai);
            currentTurn=computer;
            previousTurn=player;
        }
        printBoard();
        if(currentTurn==computer){
            if(isCheckMate(0,0, side_ai)){
                EndGame();
            }
            cout << "Computer's turn\n";
            bestmove=getMoveAI(side_ai);
            makeMove(bestmove.rowFrom, bestmove.colFrom, bestmove.rowBest, bestmove.colBest, side_ai);
            currentTurn=player;
            previousTurn=computer;
        }
    }
}

aiPiece chessGame::getMoveAI(sides side){
    vector<aiPiece> AIPieces;
    aiPiece temp;
    cell pieceTo;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j].side==side){
                temp.rowFrom=i;
                temp.colFrom=j;
                temp.piece=board[i][j].piece;
                AIPieces.push_back(temp);
            }
        }
    }
    xy kingPos;
    kingPos=getKing(side_ai);
    bool check=false;
    //get valid moves of each piece
    for(int i=0; i<AIPieces.size(); i++){

        AIPieces[i].validMoves=getValidMoves(AIPieces[i].rowFrom, AIPieces[i].colFrom, board[AIPieces[i].rowFrom][AIPieces[i].colFrom].piece,board[AIPieces[i].rowFrom][AIPieces[i].colFrom].side);
    }
    // print valid moves of all pieces of AI's side
    /*
    for(int i=0; i<AIPieces.size(); i++){
        cout << endl << i+1 << "Piece: " << AIPieces[i].piece << endl;
        cout << "valid moves:\n";
        for(int j=0; j<AIPieces[i].validMoves.size(); j++){
            cout << AIPieces[i].validMoves[j].row << "-" << AIPieces[i].validMoves[j].col<< "\t";
        }
        cout << endl;
    }*/

    system("pause");
    temp=pickBestPieceAndMove(AIPieces, side);
    if(isCheck(kingPos.row, kingPos.col, side)){
        for(int i=0; i<AIPieces.size(); i++){
            for(int j=0; j<AIPieces[i].validMoves.size(); j++){
                pieceTo.row=AIPieces[i].validMoves[j].row;
                pieceTo.col=AIPieces[i].validMoves[j].col;
                pieceTo.piece=board[AIPieces[i].validMoves[j].row][AIPieces[i].validMoves[j].col].piece;
                pieceTo.side=board[AIPieces[i].validMoves[j].row][AIPieces[i].validMoves[j].col].side;
                makeMove(AIPieces[i].rowFrom, AIPieces[i].colFrom, AIPieces[i].validMoves[j].row, AIPieces[i].validMoves[j].col, side);
                kingPos=getKing(side);
                if(!isCheck(kingPos.row, kingPos.col, side)){
                    temp.rowFrom=AIPieces[i].rowFrom;
                    temp.colFrom=AIPieces[i].colFrom;
                    temp.rowBest=AIPieces[i].validMoves[j].row;
                    temp.colBest=AIPieces[i].validMoves[j].col;
                    temp.value=1000;
                    check=true;
                }
                board[AIPieces[i].rowFrom][AIPieces[i].colFrom].piece=board[AIPieces[i].validMoves[j].row][AIPieces[i].validMoves[j].col].piece;
                board[AIPieces[i].rowFrom][AIPieces[i].colFrom].side=board[AIPieces[i].validMoves[j].row][AIPieces[i].validMoves[j].col].side;
                board[AIPieces[i].validMoves[j].row][AIPieces[i].validMoves[j].col].piece=pieceTo.piece;
                board[AIPieces[i].validMoves[j].row][AIPieces[i].validMoves[j].col].side=pieceTo.side;
                if(check==true){
                    break;
                }

            }
        }
    }
    cout << "The best move is \n row from:" << temp.rowFrom << "  colFrom: " << temp.colFrom << "   Value: " << temp.value << "   rowbest : "<<temp.rowBest << "     colbest: " << temp.colBest;
    return temp;
}

aiPiece chessGame::pickBestPieceAndMove(vector<aiPiece> aiPieces, sides side){
    aiPiece temp;
    aiMove aim_temp;
    temp.piece=pEmpty;
    temp.rowFrom=0;
    temp.colFrom=0;
    temp.value=0;
    for(int i=0; i<aiPieces.size(); i++){
        if(!aiPieces[i].validMoves.empty()){
            //cout << "\n\nOrig" << aiPieces[i].rowFrom << "-" <<aiPieces[i].colFrom << "\n\n";
            aim_temp=getBestMoveOfPiece(aiPieces[i], side);
            //cout << "\n" << i+1 << " val="<<aim_temp.value << "  row=" << aim_temp.row <<"    col=" << aim_temp.col <<endl;
            aiPieces[i].value=aim_temp.value;
            aiPieces[i].rowBest=aim_temp.row;
            aiPieces[i].colBest=aim_temp.col;
        }
    }
    for(int i=0; i<aiPieces.size(); i++){
        if(aiPieces[i].value>=temp.value && !aiPieces[i].validMoves.empty()){
            temp.value=aiPieces[i].value;
            temp.rowFrom=aiPieces[i].rowFrom;
            temp.colFrom=aiPieces[i].colFrom;
            temp.rowBest=aiPieces[i].rowBest;
            temp.colBest=aiPieces[i].colBest;
        }
    }
    return temp;

}

int chessGame::getPieceValue(pieces piece){
    int vpawn=10;
    int vbishop=30;
    int vknight=30;
    int vrook=50;
    int vqueen=90;
    int vking=1000;
    int vpEmpty=0;
    switch(piece){
    case pawn:      return vpawn;
                    break;
    case bishop:
    case knight:    return vbishop;
                    break;
    case rook:      return vrook;
                    break;
    case queen:     return vqueen;
                    break;
    case king:      return vking;
                    break;
    case pEmpty:    return vpEmpty;
                    break;
    }
}

aiMove chessGame::getBestMoveOfPiece(aiPiece piece, sides side){
    int currBest=0;
    aiMove temp;
    aiMove best;
    int int_temp=0;
    temp.value=0;
    best.value=0;
    vector<xy> vm;
    vector<xy> vmOfNextMove;


    vm=getValidMoves(piece.rowFrom, piece.colFrom, board[piece.rowFrom][piece.colFrom].piece,board[piece.rowFrom][piece.colFrom].side);
    //if(vm.empty()) cout << "TAGG";
    for(int i=0; i<vm.size(); i++){
        vmOfNextMove=getValidMoves(vm[i].row, vm[i].col, board[piece.rowFrom][piece.colFrom].piece,board[piece.rowFrom][piece.colFrom].side);
        temp=getBestFromValid(vmOfNextMove, side, vm[i].row, vm[i].col);
        //temp=getBestFromValid(vmOfNextMove, side, piece.rowFrom, piece.colFrom);
        //cout << "piece=" << board[piece.rowFrom][piece.colFrom].piece<<endl;
        //cout <<"row"<<temp.row <<"col"<<temp.col<<endl;
        //cout << "temp value:" << temp.value<<endl;
        if(temp.value>=best.value){
            best.row=vm[i].row;
            best.col=vm[i].col;
            best.value=temp.value;
        }
        vmOfNextMove.clear();
    }

    for(int i=0; i<piece.validMoves.size(); i++){
            int_temp=getPieceValue(board[piece.validMoves[i].row][piece.validMoves[i].col].piece);
            //if(isCheck(piece.validMoves[i].row, piece.validMoves[i].col, side)) int_temp=0;

            //cout << "row =" << piece.validMoves[i].row << "  col = " <<piece.validMoves[i].col <<endl;
            //cout << "temp value:" << int_temp<<endl;
            if(int_temp>=best.value){
                best.row=piece.validMoves[i].row;
                best.col=piece.validMoves[i].col;
                best.value=int_temp;
        }
    }

    //cout << "BEst\n";
    //cout << "value.." <<best.value << "   row="<<best.row <<"   col=" << best.col <<endl;

    return best;
}

aiMove chessGame::getBestFromValid(vector<xy> vm, sides side, int row, int col){
    aiMove temp;
    int currBest=0;
    int int_temp=0;
    temp.value=0;

    if(vm.empty()) return temp;
    for(int i=0; i<vm.size(); i++){
      //  if(!isCheck(vm[i].row, vm[i].col, side)){
            int_temp=getPieceValue(board[vm[i].row][vm[i].col].piece);
            //cout << "row = " << row << "  col  = " << col;
            //system("pause");
            if(isCheck(row, col, side)){
                int_temp=0;
            }
            //cout << "vmRow="<<vm[i].row << "   vmCol=" << vm[i].col << "temp: "<< int_temp<<endl;
            if(int_temp>=currBest){
                temp.row=vm[i].row;
                temp.col=vm[i].col;
                temp.value=int_temp;
            }
      //  }
    }

    return temp;
}

xy chessGame::getPieceCheck(int row, int col, sides side){ // get yung piece na nag check sa king
    xy temp;
    vector<xy> enemyMoves;
    vector<xy> eMtemp;
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j].side!=side){
                eMtemp=getValidMoves(i, j, board[i][j].piece, board[i][j].side);
                for(int k=0; k<eMtemp.size(); k++){
                    if(eMtemp[k].row==row  && eMtemp[k].col==col){
                        temp.row=i;
                        temp.col=j;
                        return temp;
                    }
                }
                //enemyMoves.insert(enemyMoves.end(), eMtemp.begin(), eMtemp.end());
                eMtemp.clear();
            }
        }
    }
}


void chessGame::EndGame(){
    cout << "\n\nWinner\n";
    exit(1);
    //playGame();
}

void chessGame::Resign(){
    system("cls");
    chooseMode();
    if(getMode()==playerVSplayer){
        string p1name=getName(1);
        string p2name=getName(2);
        twoPlayerGame(p1name, p2name);
    }else{
        playerVsAI();
    }
}


void pageDisplay(int pageNo){
    for(int i=0;i!=110;i++)
        cout<<(char)17;
    gotoxy(48,9);cout<<"Page "<<pageNo<<" of 11\n";
    for(int i=0;i!=110;i++)
        cout<<(char)17;
}

void instructionsDisplay(){
    //chessGame cg;
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
    system("cls");
    Sleep(500);
    splashName();
    Sleep(500);
    splashName();
    Sleep(500);
    splashName();
    Sleep(300);
    gotoxy(32, 9);cout<<"THE TEAM is composed of three people. They are actually a trio."<<endl;
    Sleep(300);
    gotoxy(32, 10);cout<<"They are all cute. Hehe seriously here it goes."<<endl;
    Sleep(300);
    gotoxy(32, 11);cout<<"One usually goes out with a lot of enthuiasm in coding. That is Waleed by the way, the engine that runs THE TEAM."<<endl;
    Sleep(300);
    gotoxy(32, 12);cout<<"The other one is the energizer bunny of the pack. His name is Harold. He has great coding skills, too."<<endl;
    Sleep(300);
    gotoxy(32, 13);cout<<"Uhmm, I don't know what to say anymore. The last member of this group is Carlo. He is something hehe."<<endl;
    system("pause");
    menu();
}
void menu(){
    SetConsoleTitle("CHESS");
    chessGame cg;
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
                cg.Resign();
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
int playGame(){
    chessGame cg;
    cg.chooseMode();
    //cg.boardInit(white);
    if(cg.getMode()==playerVSplayer){
        string p1name = cg.getName(1);
        string p2name = cg.getName(2);
        cg.twoPlayerGame(p1name, p2name);
    }else{
        cg.playerVsAI();
    }






    /*
    cg.aiGenerateMove();
    while(true){
        cg.printBoard();
        cg.getMove();
    }
    */
}

/* TODO

make a function to give a value to each move
make a randomizer for those equal value moves
make a function to execute the chosen move

*/
