#include "GUI.hpp"
#include <iostream>

int main()
{
    std::cout << "========================================" << std::endl;
    std::cout << "       Tic-Tac-Toe with SFML" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  - Click to select X or O at menu" << std::endl;
    std::cout << "  - Click on cells to make your move" << std::endl;
    std::cout << "  - ESC to return to menu" << std::endl;
    std::cout << "  - Click anywhere after game over to play again" << std::endl;
    std::cout << std::endl;
    std::cout << "Features:" << std::endl;
    std::cout << "  - Unbeatable AI using Minimax algorithm" << std::endl;
    std::cout << "  - Score tracking across games" << std::endl;
    std::cout << "  - Colored graphics and hover effects" << std::endl;
    std::cout << "  - Winning line highlighting" << std::endl;
    std::cout << std::endl;

    try {
        GUI gui;
        if (!gui.initialize()) {
            std::cerr << "Failed to initialize GUI!" << std::endl;
            return 1;
        }

        std::cout << "Game started! Good luck!" << std::endl;
        gui.run();
        std::cout << "Thanks for playing!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
