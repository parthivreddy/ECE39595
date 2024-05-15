#include "PawnPiece.hh"
#include "ChessPiece.hh"
#include "ChessBoard.hh"

using Student::PawnPiece;
using Student::ChessPiece;
using Student::ChessBoard;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int col) : ChessPiece(board, color, row, col){
    type = Pawn;
}

Type PawnPiece::getType() {
    return this->type;
}

bool PawnPiece::canMoveToLocation(int toRow, int toCol) {
    //if black then starting at 1
    //if white then starting at n-2
    int moveDirection;
    int startRow;
    if(getColor() == White) {
        moveDirection = -1;
        startRow = board.getNumRows() - 2;
    }
    else {
        moveDirection = 1;
        startRow = 1;
    }
    
    if(toRow == getRow()) {
        return false; //must move in some direction
    }
    if((toRow - getRow()) / moveDirection < 0) {
        return false; //making sure moving in correct direction
    }

    if(getColumn() != toCol) {//attempting capture 
        if((getRow() + moveDirection != toRow) || (std::abs(getColumn() - toCol) != 1)) {
            //if trying to capture more than 1 row or 1 col away
            return false;
        }
        else if(board.getPiece(toRow, toCol) != nullptr && board.getPiece(toRow, toCol)->getColor() != color) {
            return true; //piece can be captured
        }
        //now en passant capability
        else if(board.getPiece(getRow(), toCol) != nullptr && board.getPiece(getRow(), toCol)->getType() == Pawn && board.getPiece(getRow(), toCol)->getColor() != color) {
            //capturing behind the pawn
            //check if prevBoard state had the pawn at getRow(), toCol in the starting row
            if(color == White) {
                //check if row of prevBoard is start row
                if(board.getPrevPiece(1, toCol) == board.getPiece(getRow(), toCol)) {
                    board.updateEnPassant(true);
                    return true;
                }
            }
            else {
                if(board.getPrevPiece(board.getNumRows() - 2, toCol) == board.getPiece(getRow(), toCol)) {
                    board.updateEnPassant(true);
                    return true;
                }
            }
            return false;
        }
        else { 
            return false; //no piece at location can't have diff col
        }
    }

    if(getRow() == startRow) {
        //can move 2 squares in move direction
        if(std::abs(toRow - getRow()) > 2) {
            return false;
        }
        for(int i = 0; i < std::abs(toRow - getRow()); i++) {
            if(board.getPiece(getRow() + (i+1)*moveDirection, toCol) != nullptr) {
                return false;
            }
        }
        return true;
    }
    //now getRow is not startRow
    if(std::abs(toRow - getRow()) != 1) {
        return false;
    }
    if(board.getPiece(toRow, toCol) != nullptr) {
        return false;
    }
    return true;
}

const char * PawnPiece::toString() {
    if(getColor() == White) {
        return u8"\u2659";
    }
    else {
        return u8"\u265F";
    }
}
