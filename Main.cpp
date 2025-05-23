#include <SFML/Graphics.hpp>
#include "ChessWindow.h"

float holderWidth = 0.0;  // Global variable for width
float holderHeight = 0.0; // Global variable for height


int main()
{
    holderWidth = 720.0;  // Assign global width
    holderHeight = 720.0; // Assign global height
    ChessWindow Window(holderWidth, holderHeight, "Main Program");
    while(Window.update()) {
        
    }

    return 0;
}