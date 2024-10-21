#include <iostream>
#include <vector>
#include <algorithm>


struct Player {
    bool white;
    std::vector<std::vector<int>> pieces; // index 0 = piece, index 1 = x-coord, index 2 = y-coord
    Player() {}
    Player(int row, int col, bool white) {
        if(white) {
            for(int i = 0; i < col; i++) { // pawns
                pieces.push_back({1, 1, i});
            }
            pieces.push_back({4, 0, 0}); // rooks
            pieces.push_back({4, 0, col-1});
            pieces.push_back({6, 0, col/2}); // king
            pieces.push_back({5, 0, (col/2)-1}); // queen
            if(col % 2 == 1) pieces.push_back({5, 0, (col/2)+1}); // possible queen 2
            for(int i = 0; i < (col-4)/2; i++) { // bishops and knights
                if(i % 2 == 0) {
                    pieces.push_back({2, 0, i+1});
                    pieces.push_back({2, 0, col-i-2});
                }
                else if(i % 2 == 1) {
                    pieces.push_back({3, 0, i+1});
                    pieces.push_back({3, 0, col-i-2});
                }
                
            }
        }
        else {
            for(int i = 0; i < col; i++) { // pawns
                pieces.push_back({7, row-2, i});
            }
            pieces.push_back({10, row-1, 0}); // rooks
            pieces.push_back({10, row-1, col-1});
            pieces.push_back({12, row-1, col/2}); // king
            pieces.push_back({11, row-1, (col/2)-1}); // queen
            if(col % 2 == 1) pieces.push_back({11, row-1, (col/2)+1}); // possible queen 2
            for(int i = 0; i < (col-4)/2; i++) { // bishops and knights
                if(i % 2 == 0) {
                    pieces.push_back({8, row-1, i+1});
                    pieces.push_back({8, row-1, col-i-2});
                }
                else if(i % 2 == 1) {
                    pieces.push_back({9, row-1, i+1});
                    pieces.push_back({9, row-1, col-i-2});
                }
            }
        }
    }
    
    bool findPiece(int row, int col) {
        for(std::vector<int> piece:pieces) {
            if(piece[1] == row && piece[2] == col) return true;
        }
        return false;
    }

    bool removePiece(int type, int row, int col) {
        std::vector<int> arr = {type, row, col};
        for(auto it = pieces.begin(); it != pieces.end(); ++it) {
            if(*it == arr){
                pieces.erase(it);
                return true;
            }
        }
        return false;
    }

    bool removePiece(int row, int col) {
        for(auto it = pieces.begin(); it != pieces.end(); ++it) {
            std::vector<int> arr = *it;
            if(arr[1] == row && arr[2] == col){
                pieces.erase(it);
                return true;
            }
        }
        return false;
    }

    void movePiece(int type, int startRow, int startCol, int finalRow, int finalCol) {
        removePiece(type, startRow, startCol);
        pieces.push_back({type, finalRow, finalCol});
    }
};