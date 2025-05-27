#include "ChessElements.h"

chessPiece::chessPiece(bool Team, int type, const std::string& texturePath, int a, int b) {
    sf::IntRect blank;
    x = a;
    y = b;
    team = Team;
    pieceID = type;
    // Load texture from file
    pieceTex.loadFromFile(texturePath, blank);

    // Set up the sprite
    Sprite.setTexture(pieceTex, true);
    Sprite.setPosition(sf::Vector2f(a * holderWidth / 8, b * holderHeight / 8)); // Initial position
    Sprite.setScale(holderWidth / 1600.f, holderHeight / 1600.f); // Scale based on holder dimensions
}

void chessPiece::update_pos_Sprite(int a, int b) {
    x = a;
    y = b;
    Sprite.setPosition(sf::Vector2f(x * holderWidth / 8, y * holderHeight / 8));
}

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
    if (isLegalPieceMovement(m, t)) {
        if (boardelements[m.X][m.Y] == nullptr) // empty
            return true;
        // return false if destination contains a same team piece 
        if (boardelements[m.X][m.Y]->team == t)
            return false;
        else
            return true;
    }
    else {
        std::cout << "Moving this piece at that location Prohibited\n";
    }
    return false;
}

bool chessBoard::isLegalPieceMovement(move m, bool team)
{ // check other piece move constraints 
    
    int srcX = m.oX, srcY = m.oY;
    int dstX = m.X, dstY = m.Y;
    chessPiece* sel = boardelements[srcX][srcY];
    int pieceID = sel->pieceID;

    int dx = dstX - srcX;
    int dy = dstY - srcY;

    switch (pieceID) {
    case 0: { // pawn
        int dir = team ? +1 : -1;      // white moves y+1, black y-1
        // forward one
        if (dx == 0 && dy == dir)
            return true;
        // initial two‐step? (optional)
        if (dx == 0 && dy == 2 * dir && ((team && srcY == 1) || (!team && srcY == 6)))
            return true;
        // capture diagonally
        if (std::abs(dx) == 1 && dy == dir)
            return true;
        return false;
    }
    case 1: // rook
        return (dx == 0) ^ (dy == 0);
    case 2: // knight
        return (std::abs(dx) == 2 && std::abs(dy) == 1)
            || (std::abs(dx) == 1 && std::abs(dy) == 2);
    case 3: // bishop
        return std::abs(dx) == std::abs(dy);
    case 4: // king
        return std::max(std::abs(dx), std::abs(dy)) == 1;
    case 5: // queen
        return ((dx == 0) ^ (dy == 0))        // rook‐like
            || (std::abs(dx) == std::abs(dy)); // bishop‐like
    default:
        return false;
    }
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