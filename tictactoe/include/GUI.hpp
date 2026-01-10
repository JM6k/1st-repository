#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <array>

class GUI {
public:
    // Constructor
    GUI();

    // Initialize the window and resources
    bool initialize();

    // Main game loop
    void run();

private:
    // Window and game
    sf::RenderWindow window;
    Game game;

    // Visual settings
    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 900;
    static constexpr int BOARD_SIZE = 600;
    static constexpr int BOARD_OFFSET_X = 100;
    static constexpr int BOARD_OFFSET_Y = 150;
    static constexpr int CELL_SIZE = BOARD_SIZE / 3;

    // Colors
    sf::Color backgroundColor;
    sf::Color gridColor;
    sf::Color xColor;
    sf::Color oColor;
    sf::Color hoverColor;
    sf::Color winLineColor;

    // Font
    sf::Font font;

    // Hover state
    int hoveredCell;

    // Winning line
    std::array<int, 3> winningLine;
    bool hasWinningLine;

    // Handle events
    void handleEvents();

    // Handle mouse click
    void handleMouseClick(int x, int y);

    // Handle menu click
    void handleMenuClick(int x, int y);

    // Update game state
    void update();

    // Render everything
    void render();

    // Render menu
    void renderMenu();

    // Render game board
    void renderBoard();

    // Render grid lines
    void renderGrid();

    // Render X and O marks
    void renderMarks();

    // Render single X mark
    void renderX(int row, int col);

    // Render single O mark
    void renderO(int row, int col);

    // Render hover effect
    void renderHover();

    // Render winning line
    void renderWinningLine();

    // Render scores and status
    void renderUI();

    // Render game over screen
    void renderGameOver();

    // Get cell from mouse position
    int getCellFromPosition(int x, int y) const;

    // Get cell center position
    sf::Vector2f getCellCenter(int row, int col) const;

    // Find winning line positions
    void findWinningLine();

    // Create text with common settings
    sf::Text createText(const std::string& str, int size, sf::Color color, float x, float y);
};

#endif // GUI_HPP
