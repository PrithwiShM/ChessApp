#include "ChessWindow.h"
#include "Assets.h"

ChessWindow::ChessWindow(float width, float height, const std::string& title)
    : board(alivePieces) {                   // : window(sf::VideoMode(width, height), title) 
    int a = 1;
    window.create(sf::VideoMode((int)width, (int)(height + 30)), title);
    window.setFramerateLimit(60);

    Holder_width = width;
    Holder_height = height;
    bool sColor = 1;
    sColors[0].r = 118;
    sColors[0].g = 150;
    sColors[0].b = 86;
    sColors[1].r = 238;
    sColors[1].g = 238;
    sColors[1].b = 210;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Squares[i][j].setFillColor(sColors[sColor]);
            sColor = !sColor;
        }
        sColor = !sColor;
    }
    FitToHolder();
    FitText();
    turn = 0;
    // creating all the pieces
    //First all the pawns
    for (int i = 0; i < 8; i++) {
        alivePieces.push_back(std::make_unique<chessPiece>(1, 0, imgPath[0], i, 1));
        alivePieces.push_back(std::make_unique<chessPiece>(0, 0, imgPath[6], i, 6));
    }
    //the rooks+
    alivePieces.push_back(std::make_unique<chessPiece>(1, 1, imgPath[1], 0, 0));
    alivePieces.push_back(std::make_unique<chessPiece>(1, 1, imgPath[1], 7, 0));
    alivePieces.push_back(std::make_unique<chessPiece>(0, 1, imgPath[7], 0, 7));
    alivePieces.push_back(std::make_unique<chessPiece>(0, 1, imgPath[7], 7, 7));
    //the Knights
    alivePieces.push_back(std::make_unique<chessPiece>(1, 2, imgPath[2], 1, 0));
    alivePieces.push_back(std::make_unique<chessPiece>(1, 2, imgPath[2], 6, 0));
    alivePieces.push_back(std::make_unique<chessPiece>(0, 2, imgPath[8], 1, 7));
    alivePieces.push_back(std::make_unique<chessPiece>(0, 2, imgPath[8], 6, 7));
    //the Bishops
    alivePieces.push_back(std::make_unique<chessPiece>(1, 3, imgPath[3], 2, 0));
    alivePieces.push_back(std::make_unique<chessPiece>(1, 3, imgPath[3], 5, 0));
    alivePieces.push_back(std::make_unique<chessPiece>(0, 3, imgPath[9], 2, 7));
    alivePieces.push_back(std::make_unique<chessPiece>(0, 3, imgPath[9], 5, 7));
    //the Kings
    alivePieces.push_back(std::make_unique<chessPiece>(1, 4, imgPath[4], 3, 0));
    alivePieces.push_back(std::make_unique<chessPiece>(0, 4, imgPath[10], 4, 7));
    //the Queens
    alivePieces.push_back(std::make_unique<chessPiece>(1, 5, imgPath[5], 4, 0));
    alivePieces.push_back(std::make_unique<chessPiece>(0, 5, imgPath[11], 3, 7));

    // initialization the chess board in the constructor
    for (const auto& piece : alivePieces) {
        board.boardelements[piece->x][piece->y] = piece.get();
    }

}

void ChessWindow::FitToHolder() { // will be run once at the start of the program
    int Holder_left = 0;
    int Holder_top = 0;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Squares[i][j].setPosition(sf::Vector2f(i * Holder_width / 8, j * Holder_height / 8));
            Squares[i][j].setSize(sf::Vector2f(Holder_width / 8, Holder_height / 8));
        }
    }
}

void ChessWindow::FitText() {
    if (!font.loadFromFile("./calibri.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return; // Exit or handle the error
    }
    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(Holder_width / 2 - 12, Holder_height + 3));
}

void ChessWindow::DrawSquares() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            window.draw(Squares[i][j]);
        }
    }
}
void ChessWindow::DrawPieces() {
    for (const auto& piece : alivePieces) {
        //if (piece->draw) {
        window.draw(piece->Sprite);
        //}
    }
}
void ChessWindow::WriteText() {
    if (turn)
        text.setString("Turn: White");
    else
        text.setString("Turn: Black");

    // inside the main loop, between window.clear() and window.display()
    window.draw(text);
}

/*
0- Nothing has happened
1- A valid piece is selected
2- (Intermidiary) A valid target is choosen
*/

bool ChessWindow::update() {

    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            return false; // Indicate the window has closed, exit the event Loop

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                int pX, pY;
                pX = event.mouseButton.x;
                pY = event.mouseButton.y;
                int projX, projY;
                projX = (pX - (pX % (int)(holderWidth / 8))) / (holderWidth / 8);
                projY = (pY - (pY % (int)(holderHeight / 8))) / (holderHeight / 8);

                if (cSelect == 0 && board.assertTurn(projX, projY, turn)) {
                    // State - 1 : Correct piece selected to move
                    selected[0] = projX;
                    selected[1] = projY;
                    Squares[projX][projY].setFillColor(sf::Color(186, 202, 68));
                    cSelect = 1;
                }
                else if (cSelect == 1)
                {   // State - 2 : Trying to make a move
                    if (selected[0] == projX && selected[1] == projY)
                    {
                        // selected the currently selected box again : 2 -> 1
                        Squares[selected[0]][selected[1]].setFillColor(sColors[1 - ((selected[0] + selected[1]) % 2)]);
                        cSelect = 0;
                    }
                    else
                    { // everything is correct in junction to sequence of steps in move
                        move m(selected[0], selected[1], projX, projY);
                        // Finally making the move
                        if (board.checkvalidMove(m, turn)) {
                            if (board.checkcaptureMove(m, turn)) {
                                // need to delete a piece!
                                chessPiece* del = board.boardelements[projX][projY];
                                std::cout << "Captured " << del->pieceID << " at ";
                                std::cout << del->x << " " << del->y << std::endl;
                                // 1) Remove the owning unique_ptr from alivePieces
                                auto it = std::find_if(
                                    alivePieces.begin(),
                                    alivePieces.end(),
                                    [&](const std::unique_ptr<chessPiece>& up) {
                                        return up.get() == del;
                                    }
                                );

                                if (it != alivePieces.end()) {
                                    // 2) Erase it—this calls unique_ptr::~unique_ptr(),
                                    //    which deletes the chessPiece and frees its memory.
                                    alivePieces.erase(it);
                                }
                                std::cout << "AllivePieces Size " << alivePieces.size() << std::endl;
                            }
                            
                            board.movePieces(m);
                            Squares[selected[0]][selected[1]].setFillColor(sColors[1 - ((selected[0] + selected[1]) % 2)]);
                            cSelect = 0;
                            turn = ~turn;
                        }
                        else {
                            // print trying to make an invalid move
                            std::cout << "Trying to make an Invalid Move:in State 1" << std::endl;
                        }

                    }
                }
                else {
                    // print trying to make an invalid move
                    std::cout << "Unselected piece:in State 0" << std::endl;
                }
                

            }
        default:
            //std::cout << "Dragging is not a Valid move, Use only left click" << std::endl;
            break;
        }

    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
        return false; // Indicate the window has closed
    }
    // Render the scene
    window.clear();
    DrawSquares();
    DrawPieces();
    WriteText();
    window.display();

    return true; // Indicate the window is still open
}