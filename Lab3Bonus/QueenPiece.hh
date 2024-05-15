#ifndef __QUEENPIECE_H__
#define __QUEENPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Pawn chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class QueenPiece : public ChessPiece
    {
        public:
            QueenPiece(ChessBoard &board, Color color, int row, int col);
            Type getType();
            bool canMoveToLocation(int toRow, int toCol);
            const char *toString();
    };
}

#endif
