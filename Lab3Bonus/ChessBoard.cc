#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
#include "ChessPiece.hh"
#include "QueenPiece.hh"
#include "KnightPiece.hh"
// #include <stdio.h>
#include <iostream>

using Student::ChessBoard;
using Student::ChessPiece;

ChessBoard::ChessBoard(int numRow, int numCol) {
    this->board = std::vector<std::vector<ChessPiece *>> (numRow, std::vector<ChessPiece*> (numCol, nullptr));
    this->numRows = numRow;
    this->numCols = numCol;
    this->turn = White;
}

ChessBoard::~ChessBoard() {
    int row = getNumRows();
    int col = getNumCols();
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            ChessPiece * piece = getPiece(i,j);
            if(piece != nullptr) {
                delete piece;
            }
        }
    }
}


void ChessBoard::createChessPiece(Color col, Type ty, int startRow, int startColumn) {
    ChessPiece * oldPiece = getPiece(startRow, startColumn);
    if(oldPiece != nullptr) {
        this->board[startRow][startColumn] = nullptr;
        delete oldPiece;
    }
    
    if(ty == Pawn) {
        PawnPiece * pawn = new PawnPiece(*this, col, startRow, startColumn);
        this->board[startRow][startColumn] = pawn;
    }
    else if(ty == Bishop) {
        BishopPiece * bishop = new BishopPiece(*this, col, startRow, startColumn);
        this->board[startRow][startColumn] = bishop;
    }
    else if(ty == Rook) {
        RookPiece * rook = new RookPiece(*this, col, startRow, startColumn);
        this->board[startRow][startColumn] = rook;
    }
    else if(ty == King) {
        KingPiece * king = new KingPiece(*this, col, startRow, startColumn);
        this->board[startRow][startColumn] = king;
        if(col == White) {
            whiteValid = 1;
            whiteRow = startRow;
            whiteCol = startColumn;
        }
        else {
            blackValid = 1;
            blackRow = startRow;
            blackCol = startColumn;
        }
    }
    else if(ty == Queen) {
        QueenPiece * queen = new QueenPiece(*this, col, startRow, startColumn);
        this->board[startRow][startColumn] = queen;
    }
    else if(ty == Knight) {
        KnightPiece * knight = new KnightPiece(*this, col, startRow, startColumn);
        this->board[startRow][startColumn] = knight;
    }
    //std::cout << displayBoard().str() << "\n";
}

void ChessBoard::convertPiece(int row, int col) {
    ChessPiece * piece = board[row][col];
    board[row][col] = nullptr;
    createChessPiece(piece->color, Queen, row, col);
    delete piece;
}

bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
    //std::cout << "(" << fromRow << "," << fromColumn << ") :: " << "(" << toRow << ", " << toColumn << ")\n";
    if(getPiece(fromRow, fromColumn) == nullptr) {
        return false;
    }
    prevBoard = board;
    if(turn == getPiece(fromRow, fromColumn)->getColor()) {
        if(isValidMove(fromRow, fromColumn, toRow, toColumn)) {
            //Now toRow toCol might not be piece to be deleted
            //because of en passant
            //have en passant bool variable in board
            ChessPiece * piece;
            if(enPassant) {
                piece = board[fromRow][toColumn];
            }
            else { 
                piece = board[toRow][toColumn];
            }
            if(piece != nullptr) {
                if(piece->getType() == King) {
                    if(piece->getColor() == White) {
                        whiteValid = 0;
                        whiteRow = 0;
                        whiteCol = 0;
                    }
                    else {
                        blackValid = 0;
                        blackRow = 0;
                        blackCol = 0;
                    }
                }
                delete piece;
            }
            board[toRow][toColumn] = getPiece(fromRow, fromColumn);
            board[fromRow][fromColumn] = nullptr;
            board[toRow][toColumn]->row = toRow;
            board[toRow][toColumn]->col = toColumn;
            if(getPiece(toRow, toColumn)->getType() == King) {
                if(getPiece(toRow, toColumn)->getColor() == White) {
                    whiteRow = toRow;
                    whiteCol = toColumn;
                }
                else {
                    blackRow = toRow;
                    blackCol = toColumn;
                }
            }
            ChessPiece * dest = board[toRow][toColumn];
            if(dest->getType() == Pawn) {
                if(dest->getColor() == White && toRow == 0) {
                    convertPiece(toRow, toColumn);
                }
                else if(dest->getColor() == Black && toRow == numRows - 1) {
                    convertPiece(toRow, toColumn);
                }
            }
            turn = (turn == White) ? Black : White;
            enPassant = false;
            //displayBoard();
            //std::cout << displayBoard().str() << "\n";
            return true;
        }
    }
    enPassant = false;
    return false;
}

// ChessPiece * ChessBoard::tempMove(ChessPiece * piece, int toRow, int toColumn) {
//     ChessPiece * destPiece = getPiece(toRow, toColumn);
    
//     if(piece->canMoveToLocation(toRow, toColumn)) {
//         //this means that no piece where we want to move or we can capture
//         if(destPiece == nullptr) {

//         }
//     }
// }

ChessPiece * ChessBoard::tempMovePiece(int fromRow, int fromColumn, int toRow, int toColumn) {
    if(getPiece(fromRow, fromColumn) == nullptr) {
        return nullptr;
    }
    if(getPiece(fromRow, fromColumn)->canMoveToLocation(toRow, toColumn)) {
        //must store and restore the piece that might get deleted
        ChessPiece * piece = board[toRow][toColumn];

        board[toRow][toColumn] = getPiece(fromRow, fromColumn);
        board[fromRow][fromColumn] = nullptr;
        board[toRow][toColumn]->row = toRow;
        board[toRow][toColumn]->col = toColumn;
        //turn = (turn == White) ? Black : White;
        if(piece != nullptr && piece->getType() == King) {
            if(piece->getColor() == White) {
                whiteValid = 0;
            }
            else {
                blackValid = 0;
            }
        }
        return piece;
    }
    return nullptr;
}

void ChessBoard::revertTempMove(ChessPiece * piece, int oldRow, int oldColumn, int toRow, int toCol) {
    ChessPiece * oldPiece = getPiece(toRow, toCol);
    board[oldRow][oldColumn] = oldPiece;
    board[toRow][toCol] = piece;
    if(piece != nullptr && piece->getType() == King) {
        if(piece->getColor() == White) {
            whiteValid = 1;
        }
        else {
            blackValid = 1;
        }
    }
    oldPiece->row = oldRow;
    oldPiece->col = oldColumn;

}

bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn) {
    ChessPiece * piece = getPiece(fromRow, fromColumn);
    ChessPiece * blackKing = getKing(Black);
    ChessPiece * whiteKing = getKing(White);
    
    if(piece == nullptr) {
        return false; //if no piece at location
    }
    if(fromRow == toRow && fromColumn == toColumn) {
        return false; //must move somewhere
    }
    if(toRow < 0 || toRow > numRows - 1 || toColumn < 0 || toColumn > numCols - 1) {
        return false;
    }
    if(piece->canMoveToLocation(toRow, toColumn) == false) {
        return false;
    }
    // if(whiteValid && whiteKing == nullptr) {
    //     return false; //if whiteking captured
    // }
    // if(blackValid && blackKing == nullptr) {
    //     return false; //if blackking captured
    // }

    // if(piece == whiteKing || piece == blackKing) {
    //     //need to check if whiteKing will be in check if moving
    //     if(isSquareUnderThreat(piece->getColor(), toRow, toColumn)) {
    //         return false;
    //     }
    //     else {
    //         return true;
    //     }
    // }


    if(piece->getColor() == White) {
        if(whiteKing == nullptr) {
            return true;
            //no need to consider king of own color
        }
        //temp move piece and see if in check
        ChessPiece * movedPiece = tempMovePiece(fromRow, fromColumn, toRow, toColumn);
        //if mo
        // if(movedPiece == nullptr && piece->row == fromRow && piece->col == fromColumn) {
        //     //then was not our turn
        //     return false;
        // }
        if(isPieceUnderThreat(whiteKing->getRow(), whiteKing->getColumn())) {
            revertTempMove(movedPiece, fromRow, fromColumn, toRow, toColumn);
            return false; //if king is under threat after temp move can't move
        }
        revertTempMove(movedPiece, fromRow, fromColumn, toRow, toColumn);
    }
    else {
        if(blackKing == nullptr) {
            return true;
        }
        ChessPiece * movedPiece = tempMovePiece(fromRow, fromColumn, toRow, toColumn);
        //if mo
        // if(movedPiece == nullptr && piece->row == fromRow && piece->col == fromColumn) {
        //     //then was not our turn
        //     return false;
        // }
        if(isPieceUnderThreat(blackKing->getRow(), blackKing->getColumn())) {
            revertTempMove(movedPiece, fromRow, fromColumn, toRow, toColumn);
            return false; //if king is under threat after temp move can't move
        }
        revertTempMove(movedPiece, fromRow, fromColumn, toRow, toColumn);
    }
    
    return true;
}

bool ChessBoard::isPieceUnderThreat(int row, int column) {
    if(getPiece(row, column) == nullptr) {
        //no piece at under threat location
        return false;
    }
    
    for(int i = 0; i < getNumRows(); i++) {
        for(int j = 0; j < getNumCols(); j++) {
            if(getPiece(i, j) != nullptr) {
                if(getPiece(i, j)->getColor() != getPiece(row, column)->getColor()) {
                    if(getPiece(i, j)->canMoveToLocation(row,column)) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool ChessBoard::isSquareUnderThreat(Color color, int row, int col) {
    for(int i = 0; i < getNumRows(); i++) {
        for(int j = 0; j < getNumCols(); j++) {
            if(getPiece(i, j) != nullptr) {
                if(getPiece(i, j)->getColor() != color) {
                    if(getPiece(i, j)->canMoveToLocation(row,col)) {
                        return true;
                    }
                }
                
            }
        }
    }
    return false;
}

ChessPiece * ChessBoard::getKing(Color col) {
    if(col == White) {
        if(whiteValid) {
            return getPiece(whiteRow, whiteCol);
        }
    }
    else {
        if(blackValid) {
            return getPiece(blackRow, blackCol);
        }
    }
    return nullptr;
}


std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i;
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString());
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}

void ChessBoard::isValidScan(int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(getPiece(i, j) != nullptr) {
                std::cout << getPiece(i,j)->toString() << "\n--------\n";
                std::cout << "from:(" << i << ", " << j << ")\n";
            }
            for(int k = 0; k < n; k++){
                for(int x = 0; x < m; x++){
                    //isValidMove(i,j,k,x);
                    if(isValidMove(i,j,k,x)) {
                        std::cout << "to:(" << k << ", " << x << ")\n";
                    }
                }
            }
        }
    }
}

void ChessBoard::underThreatScan(int n, int m){
    for(int k = 0; k < n; k++){
        for(int x = 0; x < m; x++){
            isPieceUnderThreat(k,x);
        }
    }
}

float ChessBoard::scoreBoard2() {
    float myScore = 0;
    float move = 0;
    float theirScore = 0;
    float move2 = 0;
    int count = 0;
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            ChessPiece * piece = board[i][j];
            if(piece == nullptr) {
                continue;
            }
            Type ty = piece->getType();
            if(piece->getColor() == turn) {
                if(ty == King) {
                    myScore += 200;
                }
                else if(ty == Queen) {
                    myScore += 9;
                }
                else if(ty == Rook) {
                    myScore += 5;
                }
                else if(ty == Knight || ty == Bishop) {
                    myScore += 3;
                }
                else if(ty == Pawn) {
                    myScore += 1;
                }
                for(int k = 0; k < numRows; k++) {
                    for(int x = 0; x < numCols; x++) {
                        if(isValidMove(i, j, k, x)) {
                            if(board[k][x] == nullptr || (board[k][x] != nullptr && board[k][x]->getType() != King)) {
                                move += 0.1;
                            }
                        }
                    }
                }
            }
            else {
                if(ty == King) {
                    theirScore += 200;
                }
                else if(ty == Queen) {
                    theirScore += 9;
                }
                else if(ty == Rook) {
                    theirScore += 5;
                }
                else if(ty == Knight || ty == Bishop) {
                    theirScore += 3;
                }
                else if(ty == Pawn) {
                    theirScore += 1;
                }
                for(int k = 0; k < numRows; k++) {
                    for(int x = 0; x < numCols; x++) {
                        if(isValidMove(i, j, k, x)) {
                            count += 1;
                            if(board[k][x] == nullptr || (board[k][x] != nullptr && board[k][x]->getType() != King)) {
                                move2 += 0.1;
                            }
                        }
                    }
                }
            }
        }
    }
    return myScore + move - theirScore - move2;
}

float ChessBoard::scoreBoard() {
    float myScore = 0;
    float move = 0;
    float theirScore = 0;
    float move2 = 0;
    int count = 0;
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            ChessPiece * piece = board[i][j];
            if(piece == nullptr) {
                continue;
            }
            Type ty = piece->getType();
            if(piece->getColor() == turn) {
                if(ty == King) {
                    myScore += 200;
                }
                else if(ty == Queen) {
                    myScore += 9;
                }
                else if(ty == Rook) {
                    myScore += 5;
                }
                else if(ty == Knight || ty == Bishop) {
                    myScore += 3;
                }
                else if(ty == Pawn) {
                    myScore += 1;
                }
                for(int k = 0; k < numRows; k++) {
                    for(int x = 0; x < numCols; x++) {
                        if(isValidMove(i, j, k, x)) {
                            move += 0.1;
                            // if(board[k][x] == nullptr || (board[k][x] != nullptr && board[k][x]->getType() != King)) {
                            //     move += 0.1;
                            // }
                        }
                    }
                }
            }
            else {
                if(ty == King) {
                    theirScore += 200;
                }
                else if(ty == Queen) {
                    theirScore += 9;
                }
                else if(ty == Rook) {
                    theirScore += 5;
                }
                else if(ty == Knight || ty == Bishop) {
                    theirScore += 3;
                }
                else if(ty == Pawn) {
                    theirScore += 1;
                }
                for(int k = 0; k < numRows; k++) {
                    for(int x = 0; x < numCols; x++) {
                        if(isValidMove(i, j, k, x)) {
                            count += 1;
                            move2 += 0.1;
                            // if(board[k][x] == nullptr || (board[k][x] != nullptr && board[k][x]->getType() != King)) {
                            //     move2 += 0.1;
                            // }
                        }
                    }
                }
            }
        }
    }
    return myScore + move - theirScore - move2;
}

float ChessBoard::getHighestNextScore() {
    float tempScore = scoreBoard();
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            ChessPiece * piece = board[i][j];
            if(piece == nullptr || piece->getColor() != turn) {
                continue;
            }
            for(int k = 0; k < numRows; k++) {
                for(int x = 0; x < numCols; x++) {
                    ChessPiece * dest = board[k][x];
                    if(dest != nullptr && dest->getColor() != piece->getColor()) {
                        if(isValidMove(i, j, k, x)) {
                            ChessPiece * revert = tempMovePiece(i, j, k, x);
                            float newScore = scoreBoard();
                            if(tempScore < newScore) {
                                tempScore = newScore;
                            }
                            revertTempMove(revert, i, j, k, x);
                        }
                    }
                }
            }
        }
    }
    return tempScore;
}
