#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "board.cpp"

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    Board test(10, 10);
    test.printBoard();
    test.movePiece(5, 0, 4, 3, 3);
    test.refreshBoard();
    test.printBoard();
    std::wcout << test.validMove(5, 3, 3, 1, 3) << std::endl;
    
    return 0;
}