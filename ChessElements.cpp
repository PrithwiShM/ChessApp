#include "ChessElements.h"

chessBoard::chessBoard(const std::vector<std::unique_ptr<chessPiece>>& alivePieces) {
    // Initialize all board positions to nullptr
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            boardelements[i][j] = nullptr;
        }
    }

    turn = 0; // Initialize the turn (0 for white, 1 for black)
}


bool chessBoard::checkvalidMove(move m, bool t) {
    if (boardelements[m.X][m.Y] == nullptr)
        return true;
    // return false if it is a same team space 
    if (boardelements[m.X][m.Y]->team == t)
        return false;
    // check other piece move constraints later
    return true;
}

bool chessBoard::checkcaptureMove(move m, bool t) {
    if (!boardelements[m.X][m.Y])
        return false;
    // return true if the new position is a enemy space !
    if (boardelements[m.X][m.Y]->team != t)
        return true;
    return false;
}

void chessBoard::movePieces(move m) {
    // Get the piece at the source position
    chessPiece* movingPiece = boardelements[m.oX][m.oY];

    // Move the piece
    boardelements[m.X][m.Y] = movingPiece;   // Place the piece at the destination
    boardelements[m.oX][m.oY] = nullptr;     // Remove the piece from the source position

    // Update the piece's position & Sprite 
    movingPiece->update_pos_Sprite(m.X, m.Y);
}