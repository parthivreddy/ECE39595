#include <assert.h>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"
#include <iostream>
#include <stdio.h>

void test_part1_4x4_1()
{
    // Config file content:
    // 0
    // 4 4
    // w r 3 2
    // b b 1 3
    // b r 1 1
    // w r 2 3
    // ~
    // isValidScan

    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Bishop, 2, 2);
    sBoard.createChessPiece(White, Rook, 1, 0);
    sBoard.createChessPiece(Black, Bishop, 1, 3);
    sBoard.createChessPiece(Black, Rook, 1, 1);
    sBoard.createChessPiece(White, Rook, 2, 3);
    sBoard.createChessPiece(White, Pawn, 2, 2);
    std::cout << sBoard.isValidMove(2,2,1,3) << "\n";
    std::cout << sBoard.displayBoard().str() << "\n";

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.

    return;
}

// void readIn(FILE * fp) {
//     int numRow = fgetc(fp);
//     fgetc(fp); //eat space
//     int numCol = fgetc(fp);
//     fgetc(fp); //eat new line
//     while(fgetc(fp) != '~') {
//         Color col;
//         Type ty;
//         int row;
//         int column;
//         if(fgetc(fp) == 'w') {
//             col = White;
//         }
//         else {
//             col = Black;
//         }
//         fgetc(fp);
//         char typeChar = fgetc(fp);
//         if(typeChar == 'p') {
//             ty = Pawn;
//         }
//         else if(typeChar == 'b') {
//             ty = Bishop;
//         }
//         else if(typeChar == 'r') {
//             ty = Rook;
//         }
//         fgetc(fp); //eat space
//         row = int(fgetc(fp));
//         fgetc(fp);
//         column = int(fgetc(fp));
//         fgetc(fp);
//     }
//     if(fgetc(fp) != 'm') {
//         while(fgetc(fp) != '\n'); {
//             printf("hello\n");
//         }
//     }
// }
void hi() {
    Student::ChessBoard sBoard(8,8);

    sBoard.createChessPiece(Black,Pawn,1,5);
    sBoard.createChessPiece(Black,Pawn,6,4);
    sBoard.createChessPiece(Black,Pawn,1,4);
    sBoard.createChessPiece(Black,Pawn,5,1);
    sBoard.createChessPiece(Black,Pawn,5,3);
    sBoard.createChessPiece(White,Pawn,3,6);
    sBoard.createChessPiece(Black,Bishop,4,3);
    sBoard.createChessPiece(Black,Bishop,5,3);
    sBoard.createChessPiece(White,Bishop,1,2);
    sBoard.createChessPiece(Black,Bishop,7,7);
    sBoard.createChessPiece(Black,Bishop,4,6);
    sBoard.createChessPiece(White,Pawn,7,0);
    sBoard.createChessPiece(Black,Rook,3,7);
    sBoard.createChessPiece(White,Pawn,5,7);
    sBoard.createChessPiece(White,Bishop,3,0);
    sBoard.createChessPiece(Black,Rook,3,3);
    sBoard.createChessPiece(Black,King,5,3);
    sBoard.createChessPiece(White,King,6,3);
    sBoard.isValidScan(8,8);
    sBoard.underThreatScan(8,8);
    
    std::cout << sBoard.displayBoard().str() << "\n";

    sBoard.movePiece(6,3,5,3);
    std::cout << sBoard.displayBoard().str() << "\n";

    sBoard.movePiece(4,3,6,5);
    std::cout << sBoard.displayBoard().str() << "\n";

    sBoard.movePiece(5,3,4,2);
    sBoard.movePiece(5,0,7,4);
    sBoard.movePiece(4,6,5,5);
    sBoard.movePiece(3,6,2,6);
    sBoard.movePiece(3,3,3,4);
    sBoard.movePiece(0,3,3,1);
    sBoard.isValidScan(8,8);
    sBoard.underThreatScan(8,8);

    sBoard.movePiece(1,2,2,3);
    sBoard.movePiece(6,5,7,4);
    sBoard.movePiece(2,3,0,1);
    sBoard.movePiece(1,7,2,5);
    sBoard.movePiece(5,1,6,1);
    sBoard.movePiece(2,6,1,6);
    sBoard.movePiece(5,5,4,6);
    sBoard.movePiece(6,6,1,4);
    sBoard.isValidScan(8,8);
    sBoard.underThreatScan(8,8);

    sBoard.movePiece(3,0,0,3);
    sBoard.movePiece(7,4,5,6);
    sBoard.movePiece(0,1,3,4);
    sBoard.movePiece(1,5,1,6);
    sBoard.movePiece(7,7,6,6);
    sBoard.movePiece(3,4,6,1);
    sBoard.movePiece(1,5,2,5);
    sBoard.movePiece(0,3,3,4);
    sBoard.isValidScan(8,8);
    sBoard.underThreatScan(8,8);

    sBoard.movePiece(0,3,3,0);
    sBoard.movePiece(6,6,4,4);
    sBoard.movePiece(6,1,5,0);
    sBoard.movePiece(6,4,6,3);
    sBoard.movePiece(5,6,4,7);
    sBoard.movePiece(3,0,4,1);
    sBoard.movePiece(4,6,5,5);
    sBoard.movePiece(6,7,2,4);
    sBoard.isValidScan(8,8);
    sBoard.underThreatScan(8,8);

    sBoard.movePiece(5,0,7,2);
    sBoard.movePiece(5,5,4,6);
    sBoard.movePiece(1,6,0,6);
    sBoard.movePiece(7,2,1,5);
    sBoard.movePiece(4,4,0,0);
    sBoard.movePiece(4,2,5,3);
    sBoard.movePiece(4,6,5,5);
    sBoard.movePiece(1,7,6,5);
    sBoard.isValidScan(8,8);
    sBoard.underThreatScan(8,8);

    sBoard.movePiece(4,1,3,2);
    sBoard.movePiece(1,4,3,4);
    sBoard.movePiece(3,2,6,5);
    sBoard.movePiece(1,2,2,3);
    sBoard.movePiece(2,5,3,5);
    sBoard.movePiece(7,2,5,4);
    sBoard.movePiece(3,4,4,4);
    sBoard.movePiece(5,0,2,2);
    sBoard.isValidScan(8,8);
    sBoard.underThreatScan(8,8);

    sBoard.movePiece(5,3,4,2);
    sBoard.movePiece(4,7,2,5);
    sBoard.movePiece(6,5,4,7);
    sBoard.movePiece(3,3,6,1);
    sBoard.movePiece(3,7,1,7);
    sBoard.movePiece(5,4,4,3);
    sBoard.movePiece(2,5,3,4);
    sBoard.movePiece(7,0,6,1);
    sBoard.isValidScan(8,8);
    sBoard.underThreatScan(8,8);

    sBoard.movePiece(4,3,3,4);
    sBoard.movePiece(4,4,5,4);
    sBoard.movePiece(4,2,3,1);
    sBoard.movePiece(0,1,6,0);
    sBoard.movePiece(5,5,3,3);
    sBoard.movePiece(4,7,7,4);
    sBoard.movePiece(1,7,5,7);
    sBoard.movePiece(3,1,2,2);
    sBoard.isValidScan(8,8);
    sBoard.underThreatScan(8,8);
}

int main(int argc, char ** argv)
{
    // FILE * fp = fopen(argv[1], "r");
    // fgetc(fp); //eat 0
    // fgetc(fp); //eat new line
    hi();


    return EXIT_SUCCESS;
}
