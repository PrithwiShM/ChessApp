#include <vector>
#include <memory> // For std::unique_ptr
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "ChessElements.h"

class ChessWindow {
private:
    float Holder_width;
    float Holder_height;
    sf::RenderWindow window;
    sf::RectangleShape Squares[8][8];
    sf::Font font;
    sf::Text text;
    sf::Color sColors[2];
    bool cSelect = 0;
    int selected[2];
    int turn;

    // Single Ownership
    std::vector<std::unique_ptr<chessPiece>> alivePieces;

    // Lookup and other utility functions
    chessBoard board;

    void FitToHolder();
    
    void FitText();

    void DrawSquares();

    void DrawPieces();

    void WriteText();
public:
    // Constructor to initialize the window, squares and the chessPieces
    ChessWindow(float width, float height, const std::string& title);
    
    // Update method to process events and render the window
    bool update();
};

