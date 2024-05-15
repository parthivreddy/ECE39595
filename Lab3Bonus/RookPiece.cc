#include "RookPiece.hh"
#include "ChessPiece.hh"
#include "ChessBoard.hh"

using Student::RookPiece;
using Student::ChessPiece;
using Student::ChessBoard;

RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column) {
    type = Rook;
}

Type RookPiece::getType() {
    return type;
}

bool RookPiece::canMoveToLocation(int toRow, int toCol) {
    if(getRow() != toRow && getColumn() != toCol) {
        return false; //can't move diagonally
    }
    int rowDir;
    int colDir;
    if(getRow() - toRow < 0) {
        rowDir = 1; //up
    }
    else {
        rowDir = -1; //down
    }

    if(getColumn() - toCol < 0) {
        colDir = 1; //right
    }
    else {
        colDir = -1; //left
    }

    for(int i = 0; i < std::abs(getRow() - toRow) - 1; i++) {
        //loop to check to see no pieces in between curr and dest-1
        //if not moving from row will not run loop
        if(board.getPiece(getRow() + (i+1)*rowDir, getColumn()) != nullptr) {
            return false;
        }
    }

    for(int i = 0; i < std::abs(getColumn() - toCol) - 1; i++) {
        if(board.getPiece(getRow(), getColumn() + (i+1)* colDir) != nullptr) {
            return false;
        }
    }

    //should be safe since nullptr condition evaluated first
    if(board.getPiece(toRow, toCol) == nullptr || board.getPiece(toRow, toCol)->getColor() != color) {
        return true;
    }
    
    return false;
}

const char * RookPiece::toString() {
    if(color == White) {
        return u8"\u2656";
    }
    else {
        return u8"\u265C";
    }
}


