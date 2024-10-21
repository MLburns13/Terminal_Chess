#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cmath>
#include <string>
#include "player.cpp"


class Board {
    private:
        int row, col;
        int** locations;
        Player players[2];
        std::unordered_map<int, std::wstring> values = {{0, L" "}, {1, L"♟"}, {2, L"♞"}, {3, L"♝"}, {4, L"♜"}, {5, L"♛"},{6, L"♚"},
                                                       {7, L"♙"}, {8, L"♘"}, {9, L"♗"}, {10, L"♖"}, {11, L"♕"}, {12, L"♔"}};
        
    public:
        Board(int row, int col) {
            if(row > 26) this->row = 26;
            else if(row < 4) this->row = 4;
            else this->row = row;

            if(col > 26) this->col = 26;
            else if(col < 4) this->col = 4;
            else this->col = col;

            locations = new int*[this->row];
            for(int i = 0; i < this->row; ++i) {
                locations[i] = new int[this->col];
            }
            players[0] = Player(this->row, this->col, true);
            players[1] = Player(this->row, this->col, false);

            refreshBoard();
        }
        Board() {
            this->row = 8;
            this->col = 8;
            locations = new int*[row];
            for(int i = 0; i < row; ++i) {
                locations[i] = new int[col];
            }
            players[0] = Player(this->row, this->col, true);
            players[1] = Player(this->row, this->col, false);
            refreshBoard();
        }

        ~Board() {
            for(int i = 0; i < row; i++) {
                delete[] locations[i];
            }
            delete[] locations;
        }

        void refreshBoard() {        
            // fills everything in as zeros
            for(int i = 0; i < col; i++) {
                for (int j = 0; j< row; j++) {
                    locations[i][j] = 0;
                }
            }
            /*
            // fills in pawn rows
            for(int i = 0; i < col; i++) {
                locations[1][i] = 1;
                locations[row-2][i] = 7;
            }
            // fills in rooks
            locations[0][0] = 4;
            locations[0][col-1] = 4;
            locations[row-1][0] = 10;
            locations[row-1][col-1] = 10;
            //fills in kings
            locations[0][col/2] = 6;
            locations[row-1][col/2] = 12;
            //fills in queens
            locations[0][(col/2)-1] = 5;
            locations[row-1][(col/2)-1] = 11;
            if (col % 2 == 1){
                locations[0][(col/2)+1] = 5;
                locations[row-1][(col/2)+1] = 11;
            }
            //fills in knights and bishop
            int index = 1;
            while(locations[0][index] == 0) {
                if(index % 2 == 1) {
                    locations[0][index] = 2;
                    locations[0][col-index-1] = 2;
                    locations[row-1][index] = 8;
                    locations[row-1][col-index-1] = 8;
                }
                else if (index % 2 == 0){
                    locations[0][index] = 3;
                    locations[0][col-index-1] = 3;
                    locations[row-1][index] = 9;
                    locations[row-1][col-index-1] = 9;
                }
                index++;
            }*/

            for(std::vector<int> arr:players[0].pieces) {
                locations[arr[1]][arr[2]] = arr[0];
            }

            for(std::vector<int> arr:players[1].pieces) {
                locations[arr[1]][arr[2]] = arr[0];
            }
        }

        void printBoardLiteral() {
            for(int i = row-1; i >= 0; i--) {
                for(int j = 0; j < col; j++) {
                    std::wcout << locations[i][j] << ", ";
                }
                std::wcout << std::endl;
            }
        }
    
        void printBoard() {
            // ╔ ═ ╦ ╗ ╩ ║ ╝ ╚ ╣ ╠ ╬


            // print top row
            std::wcout << L"   ╔══";
            for(int i = 0; i < col -1 ; i++) {
                std::wcout << L"╦══";
            }
            std::wcout << L"╗" << std::endl;
            // print middle rows
            for(int i = row-1; i >= 0; i--) {
                if(i < 9){
                    std::wcout << L" ";
                }
                std::wcout << i+1 << L" ";
                for(int j = 0; j < col; j++) {
                    std::wcout << L"║" << values[locations[i][j]] << L" ";
                }
                std::wcout << L"║" << std::endl;
                if(i > 0) {
                    std::wcout << L"   ╠══";
                    for(int j = 0; j < col-1; j++) {
                        std::wcout << L"╬══";
                    }
                    std::wcout << L"╣" << std::endl;
                }
            }
            //print bottom row
            std::wcout << L"   ╚══";
            for(int i = 0; i < col-1; i++) {
                std::wcout << L"╩══";
            }
            std::wcout << L"╝" << std::endl;
            //print row lettering
            std::string letters = "abcdefghijklmnopqrstuvwxyz";
            std::wcout << "  ";
            for(int i = 0; i < col; i++){
                std::wcout << "  " << letters.at(i);
            }
            std::wcout << std::endl;
        }

        bool isValidSting(std::string str) {
            for(char c:str) {
                if(!isdigit(c) && !isalpha(c)) {
                    return false;
                }
            }
            return true;
        }

        //https://cheatography.com/davechild/cheat-sheets/chess-algebraic-notation/
        //there are extra cases to consider 
        //if at the end of the string is a letter then we know there is promotion
        bool notation(std::string str, bool white) {
            if(!isValidSting(str) || str.length() < 2 ||str.length() > 11) return false;
            
            if(str == "0-0") {
                //castle
            }
            if(str == "0-0-0") {
                //long castle
            }
            if(str.length() == 2) {
                //Pawn
                int type = pieceType(str.length(),str.at(1), white);
                int endRow = xCoord(str.at(str.length()-1));
                int endCol = yCoord(str.at(str.length()-2));
                bool take = false;
                bool check = false;
                bool checkmate = false;

                //return validMove(1+6*white, );
            }
            else if (str.at(str.length()-1) == '+'){
                //check
                bool check = true;
                bool checkmate = false;
                int endRow = xCoord(str.at(str.length()-3));
                int endCol = yCoord(str.at(str.length()-2));
                if(str.at(str.length()-4) == 'x'){
                    bool take = true;
                    int type = pieceType(str.length(), str.at(str.length()-5), white);
                }
                else if(isalpha(str.at(str.length()-4))){
                    bool take = false;
                    int type = pieceType(str.length(), str.at(str.length()-4), white);
                }
                else{
                    //for pawns that checked
                    if(white == true) int type  = 1;
                    else int type = 7;
                }
            }
            else if (str.at(str.length()-1) == '#'){
                //checkmate
                bool check = false;
                bool checkmate = true;
                int endRow = xCoord(str.at(str.length()-3));
                int endCol = yCoord(str.at(str.length()-2));
                if(str.at(str.length()-4) == 'x'){
                    bool take = true;
                    int type = pieceType(str.length(), str.at(str.length()-5), white);
                }
                else if(isalpha(str.at(str.length()-4))){
                    bool take = false;
                    int type = pieceType(str.length(), str.at(str.length()-4), white);
                }
                else{
                    //for pawns that checkmated if thats even possible
                    if(white == true) int type  = 1;
                    else int type = 7;
                }
            }
            else{
                //location
                bool check = false;
                bool checkmate = false;
                int endRow = xCoord(str.at(str.length()-2));
                int endCol = yCoord(str.at(str.length()-1));
                if(str.at(str.length()-3) == 'x'){
                    bool take = true;
                    int type = pieceType(str.length(), str.at(str.length()-4), white);
                }
                else if(isalpha(str.at(str.length()-3))){
                    bool take = false;
                    int type = pieceType(str.length(), str.at(str.length()-3), white);
                }
            }
        }

        bool check(char check){
            if(check == '+') return 1;
            else return 0;
        }

        bool checkmate(char checkmate){
            if(checkmate == '#') return 1;
            else return 0;
        }

        int xCoord(char xCoord){
            if(int(xCoord) > 96) {
                return (int)xCoord-97;
            }
            if(int(xCoord) > 64 ) {
                return (int)xCoord-65;
            }
            return -1;
        }

        int yCoord(char yCoord){
            return int(yCoord) - 1;
        }

        bool take(char take){
            if(take == 'x') return 1;
            else return 0;
        }

        void InvalidInputMessage(){
            std::wcout << L"Invalid Chess Notation";
        }

        int pieceType(int length, char type, bool white){
            //pawns
            if(length == 2){
                if(white == 1) return 1;
                else if(white == 0) return 7;
            }
            else if(white){
                if(type == 'P') return 1;
                else if(type == 'N') return 2;
                else if(type == 'B') return 3;
                else if(type == 'R') return 4;
                else if(type == 'Q') return 5;
                else if(type == 'K') return 6;
            }
            else{
                if(type == 'P') return 7;
                else if(type == 'N') return 8;
                else if(type == 'B') return 9;
                else if(type == 'R') return 10;
                else if(type == 'Q') return 11;
                else if(type == 'K') return 12;
            }
        }

        bool validMove(int type, int startRow, int startCol, int endRow, int endCol) {
            if(endRow > row || endCol > col) return false;
            if(endRow == startRow && endCol == startCol) return false;
            if(type < 7) {
                if(players[0].findPiece(endRow, endCol)) return false;
            }
            else {
                if(players[1].findPiece(endRow, endCol)) return false;
            }
            int colDiff = endCol-startCol;
            int rowDiff = endRow-startRow;
            int colDiffSign = colDiff/colDiff;
            int rowDiffSign = rowDiff/rowDiff;
            switch(type) {
                case 1: case 7:
                    if(endCol != startCol) {
                        if(abs(colDiff) > 1 || rowDiff > 1 || endRow < startRow) {
                            return false;
                        }
                        return players[type%7].findPiece(endRow, endCol);
                    }
                    else if(startRow == 1 && rowDiff < 3) {
                        return true;
                    }
                    else if(rowDiff < 2) {
                        return true;
                    }
                    return false;
                    break;
                case 2: case 8:
                    if(abs(colDiff) == 2 && abs(rowDiff) == 1) {
                        return true;
                    }
                    else if(abs(colDiff) == 1 && abs(rowDiff) == 2) {
                        return true;
                    }
                    return false;
                    break;
                case 3: case 9:
                    if(abs(colDiff) != abs(rowDiff)) {
                        return false;
                    }
                    for(int i = 1; i < abs(colDiff); i++) {
                        if(players[0].findPiece(startCol+(i*colDiffSign), startRow+(i*rowDiffSign))) return false;
                        if(players[1].findPiece(startCol+(i*colDiffSign), startRow+(i*rowDiffSign))) return false;
                    }
                    break;
                case 4: case 10:
                    if(colDiff != 0 && rowDiff != 0) return false;
                    if(rowDiff != 0) {
                        for(int i = 1; i < abs(rowDiff); i++) {
                            if(players[0].findPiece(startCol, startRow+(i*rowDiffSign))) return false;
                            if(players[1].findPiece(startCol, startRow+(i*rowDiffSign))) return false;
                        }
                    }
                    else if(colDiff != 0) {
                        for(int i = 1; i < abs(colDiff); i++) {
                            if(players[0].findPiece(startCol+(i*colDiffSign), startRow)) return false;
                            if(players[1].findPiece(startCol+(i*colDiffSign), startRow)) return false;
                        }
                    }
                    break;
                case 5: case 11:
                    if(abs(colDiff) == abs(rowDiff)) {
                        for(int i = 1; i < abs(colDiff); i++) {
                            if(players[0].findPiece(startCol+(i*colDiffSign), startRow+(i*rowDiffSign))) return false;
                            if(players[1].findPiece(startCol+(i*colDiffSign), startRow+(i*rowDiffSign))) return false;
                        }
                    }
                    else if(colDiff != 0 && rowDiff == 0) {
                        for(int i = 1; i < abs(rowDiff); i++) {
                            if(players[0].findPiece(startCol, startRow+(i*rowDiffSign))) return false;
                            if(players[1].findPiece(startCol, startRow+(i*rowDiffSign))) return false;
                        }
                    }
                    else if(colDiff == 0 && rowDiff != 0) {
                        for(int i = 1; i < abs(colDiff); i++) {
                            if(players[0].findPiece(startCol+(i*colDiffSign), startRow)) return false;
                            if(players[1].findPiece(startCol+(i*colDiffSign), startRow)) return false;
                        }
                    }
                    break;
            }
            return true;
        }

        bool removePiece(int type, int row, int col) {
            if(type < 7) {
                return players[0].removePiece(type, row, col);
            }
            return players[1].removePiece(type, row, col);
        }

        void movePiece(int type, int startRow, int startCol, int finalRow, int finalCol) {
            if(type < 7) {
                players[0].movePiece(type, startRow, startCol, finalRow, finalCol);
                return; 
            }
            players[1].movePiece(type, startRow, startCol, finalRow, finalCol);
        }    

        void takePiece(int type, int startRow, int startCol, int finalRow, int finalCol) {
            if(type < 7) {
                players[0].movePiece(type, startRow, startCol, finalRow, finalCol);
                players[1].removePiece(finalRow, finalCol);
                return;
            }
            players[1].movePiece(type, startRow, startCol, finalRow, finalCol);
            players[0].removePiece(finalRow, finalCol);
        }
};
