#include "KingPiece.hh"
#include "ChessPiece.hh"
#include "ChessBoard.hh"

using Student::KingPiece;
using Student::ChessPiece;
using Student::ChessBoard;

KingPiece::KingPiece(ChessBoard &board, Color color, int row, int col) : ChessPiece(board, color, row, col){
    type = King;
}

Type KingPiece::getType() {
    return this->type;
}

bool KingPiece::canMoveToLocation(int toRow, int toCol) {
    //checks location move without checks
    int diffRow = std::abs(getRow() - toRow);
    int diffCol = std::abs(getColumn() - toCol);
    if(diffRow > 1 || diffCol > 1) {
        return false;
    }
    
    ChessPiece * destPiece = board.getPiece(toRow, toCol);
    if(destPiece != nullptr) {
        if(destPiece->getColor() == color) {
            return false;
        }
        return true;
    }
    return true;
}

const char* KingPiece::toString() {
    if(getColor() == White) {
        return u8"\u2654";
    }
    else {
        return u8"\u265A";
    }
}