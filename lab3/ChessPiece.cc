#include "ChessPiece.hh"

using Student::ChessPiece;

ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column)
    :board(board) {
    this->color = color;
    this->row = row;
    this->col = column;
}

Color ChessPiece::getColor(){
    return this->color;
}

Type ChessPiece::getType(){
    return this->type;
}

int ChessPiece::getRow() {
    return this->row;
}

int ChessPiece::getColumn() {
    return this->col;
}

void ChessPiece::setPosition(int row, int column) {
    this->row = row;
    this->col = column;
}


