#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

extern float holderWidth;
extern float holderHeight;

struct chessPiece
{
private:
    sf::Texture pieceTex; // Texture as a member variable (not local)

public:
    sf::Sprite Sprite;
    int x, y, pieceID; // 0 - pawn, 1- rook, 2-knight, 3-Bishop, 4-King, 5-Queen
    bool team; // 1 is white and 0 is black
    chessPiece(bool Team, int type, const std::string& texturePath, int a, int b) {
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

    void update_pos_Sprite(int a, int b) {
        x = a;
        y = b;
        Sprite.setPosition(sf::Vector2f(x * holderWidth / 8, y * holderHeight / 8));
    }
};

struct move {
    int oX, oY, X, Y;
  
    move(int oldX, int oldY, int newX, int newY) {
        oX = oldX;
        oY = oldY;
        X = newX;
        Y = newY;
    }
};

class chessBoard {
private:
    int turn;
public:
    chessPiece* boardelements[8][8]; // 2D array of raw pointers to chessPiece

    chessBoard(const std::vector<std::unique_ptr<chessPiece>>& alivePieces);
    /**
    * Function to check if the correct player is playing 
    */
    bool assertTurn(int x, int y, bool turn) {
        if (!boardelements[x][y]) return false;
        return (boardelements[x][y]->team == turn);
    }
    /*
    * 
    */
    bool checkvalidMove(move m, bool t);

    bool checkcaptureMove(move m, bool t);

    void movePieces(move m);
};