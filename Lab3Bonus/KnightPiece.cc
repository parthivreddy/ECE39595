#include "KnightPiece.hh"
#include "ChessPiece.hh"
#include "ChessBoard.hh"

using Student::KnightPiece;
using Student::ChessPiece;
using Student::ChessBoard;

KnightPiece::KnightPiece(ChessBoard &board, Color color, int row, int col) : ChessPiece(board, color, row, col){
    type = Knight;
}

Type KnightPiece::getType() {
    return this->type;
}

bool KnightPiece::canMoveToLocation(int toRow, int toCol) {
    ChessPiece * destPiece = board.getPiece(toRow, toCol);
    if(destPiece != nullptr) {
        if(destPiece->getColor() == color) {
            return false;
        }
    }

    int diffRow = std::abs(getRow() - toRow);
    int diffCol = std::abs(getColumn() - toCol);

    if(diffRow == 1) {
        if(diffCol != 2) {
            return false;
        }
    }
    else if(diffRow == 2) {
        if(diffCol != 1) {
            return false;
        }
    }
    else {
        return false;
    }
    return true;
}

const char* KnightPiece::toString() {
    if(getColor() == White) {
        return u8"\u2658";
    }
    else {
        return u8"\u265E";
    }
}