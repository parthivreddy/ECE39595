#ifndef __PAWNPIECE_H__
#define __PAWNPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Pawn chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class PawnPiece : public ChessPiece
    {
        public:
            PawnPiece(ChessBoard &board, Color color, int row, int col);
            Type getType();
            bool canMoveToLocation(int toRow, int toCol);
            const char *toString();
        //     bool getMovedTwo() {return movedTwo;};
        // private:
        //     bool movedTwo = false;
    };
}

#endif
