#include "BishopPiece.hh"
#include "ChessPiece.hh"
#include "ChessBoard.hh"

using Student::BishopPiece;
using Student::ChessPiece;
using Student::ChessBoard;

BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int col) : ChessPiece(board, color, row, col){
    type = Bishop;
}

Type BishopPiece::getType() {
    return this->type;
}

bool BishopPiece::canMoveToLocation(int toRow, int toCol) {
    if(std::abs(getRow() - toRow) != std::abs(getColumn() - toCol)) {
        return false; //not diagonal
    }

    int rowDir;
    int colDir;

    if(getRow() - toRow < 0) {
        rowDir = 1;
    }
    else {
        rowDir = -1;
    }
    if(getColumn() - toCol < 0) {
        colDir = 1;
    }
    else {
        colDir = -1;
    }

    for(int i = 0; i < std::abs(getRow() - toRow) - 1; i++) {
        if(board.getPiece(getRow() + (i+1)*rowDir, getColumn() + (i+1)*colDir) != nullptr) {
            return false;
        }
    }

    if(board.getPiece(toRow, toCol) == nullptr || board.getPiece(toRow, toCol)->getColor() != color) {
        return true;
    }
    return false;
}

const char * BishopPiece::toString() {
    if(color == White) {
        return u8"\u2657";
    }
    else {
        return u8"\u265D";
    }
}