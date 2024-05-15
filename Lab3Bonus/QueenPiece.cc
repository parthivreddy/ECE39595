#include "QueenPiece.hh"
#include "BishopPiece.hh"
#include "RookPiece.hh"
#include "ChessPiece.hh"
#include "ChessBoard.hh"

using Student::QueenPiece;
using Student::ChessPiece;
using Student::ChessBoard;

QueenPiece::QueenPiece(ChessBoard &board, Color color, int row, int col) : ChessPiece(board, color, row, col){
    type = Queen;
}

Type QueenPiece::getType() {
    return this->type;
}

bool QueenPiece::canMoveToLocation(int toRow, int toCol) {
    RookPiece * rookType = new RookPiece(board, this->getColor(), this->row, this->col);
    BishopPiece * bishopType = new BishopPiece(board, this->getColor(), this->row, this->col);;
    // int fromRow = row;
    // int fromCol = col;
    // rookType->setPosition(fromRow, fromCol);
    // bishopType->setPosition(fromRow, fromCol);
    bool check = (rookType->canMoveToLocation(toRow, toCol) || bishopType->canMoveToLocation(toRow, toCol));
    delete rookType;
    delete bishopType;
    return check;
}

const char* QueenPiece::toString() {
    if(getColor() == White) {
        return u8"\u2655";
    }
    else {
        return u8"\u265B";
    }
}