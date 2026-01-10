#include "GUI.hpp"
#include <iostream>
#include <cmath>

GUI::GUI()
    : backgroundColor(30, 30, 50),
      gridColor(100, 100, 150),
      xColor(100, 150, 255),
      oColor(255, 100, 100),
      hoverColor(255, 255, 100, 50),
      winLineColor(100, 255, 100),
      hoveredCell(-1),
      hasWinningLine(false) {
    winningLine.fill(-1);
}

bool GUI::initialize() {
    // Create window
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tic-Tac-Toe");
    window.setFramerateLimit(60);

    // Note: SFML may not have a default font, so text rendering might not work
    // For a complete implementation, you would need to load a font file
    // For now, we'll work without text or use basic shapes

    return true;
}

void GUI::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void GUI::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (game.getState() == GameState::PLAYING || game.getState() == GameState::GAME_OVER) {
                    game.setState(GameState::MENU);
                    hasWinningLine = false;
                } else {
                    window.close();
                }
            }
            if (event.key.code == sf::Keyboard::R) {
                if (game.getState() == GameState::GAME_OVER) {
                    game.resetGame();
                    hasWinningLine = false;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }

        if (event.type == sf::Event::MouseMoved) {
            if (game.getState() == GameState::PLAYING && !game.isAITurn()) {
                hoveredCell = getCellFromPosition(event.mouseMove.x, event.mouseMove.y);
            } else {
                hoveredCell = -1;
            }
        }
    }
}

void GUI::handleMouseClick(int x, int y) {
    if (game.getState() == GameState::MENU) {
        handleMenuClick(x, y);
    } else if (game.getState() == GameState::PLAYING && !game.isAITurn()) {
        int cell = getCellFromPosition(x, y);
        if (cell != -1 && game.getBoard().isValidMove(cell)) {
            game.makeMove(cell);
            if (game.isGameOver()) {
                findWinningLine();
            }
        }
    } else if (game.getState() == GameState::GAME_OVER) {
        // Click anywhere to restart
        game.resetGame();
        hasWinningLine = false;
    }
}

void GUI::handleMenuClick(int /* x */, int y) {
    // Simple menu: top half = X, bottom half = O
    if (y < WINDOW_HEIGHT / 2) {
        game.startNewGame(Cell::X);
    } else {
        game.startNewGame(Cell::O);
    }
}

void GUI::update() {
    // Process AI turn if needed
    if (game.isAITurn()) {
        // Add small delay for better UX
        static sf::Clock aiClock;
        if (aiClock.getElapsedTime().asMilliseconds() > 500) {
            game.processAITurn();
            if (game.isGameOver()) {
                findWinningLine();
            }
            aiClock.restart();
        }
    }
}

void GUI::render() {
    window.clear(backgroundColor);

    if (game.getState() == GameState::MENU) {
        renderMenu();
    } else {
        renderBoard();
        renderGrid();
        renderMarks();
        if (!game.isGameOver()) {
            renderHover();
        }
        if (hasWinningLine) {
            renderWinningLine();
        }
        renderUI();
        if (game.getState() == GameState::GAME_OVER) {
            renderGameOver();
        }
    }

    window.display();
}

void GUI::renderMenu() {
    // Draw title
    sf::RectangleShape titleBox(sf::Vector2f(600, 100));
    titleBox.setPosition(100, 100);
    titleBox.setFillColor(sf::Color(50, 50, 80));
    titleBox.setOutlineColor(gridColor);
    titleBox.setOutlineThickness(3);
    window.draw(titleBox);

    // Draw X button
    sf::RectangleShape xButton(sf::Vector2f(600, 200));
    xButton.setPosition(100, 250);
    xButton.setFillColor(sf::Color(60, 80, 120));
    xButton.setOutlineColor(xColor);
    xButton.setOutlineThickness(5);
    window.draw(xButton);

    // Draw X symbol
    sf::RectangleShape xLine1(sf::Vector2f(150, 10));
    xLine1.setPosition(325, 320);
    xLine1.setRotation(45);
    xLine1.setFillColor(xColor);
    window.draw(xLine1);

    sf::RectangleShape xLine2(sf::Vector2f(150, 10));
    xLine2.setPosition(325, 426);
    xLine2.setRotation(-45);
    xLine2.setFillColor(xColor);
    window.draw(xLine2);

    // Draw O button
    sf::RectangleShape oButton(sf::Vector2f(600, 200));
    oButton.setPosition(100, 500);
    oButton.setFillColor(sf::Color(60, 80, 120));
    oButton.setOutlineColor(oColor);
    oButton.setOutlineThickness(5);
    window.draw(oButton);

    // Draw O symbol
    sf::CircleShape oCircle(60);
    oCircle.setPosition(340, 540);
    oCircle.setFillColor(sf::Color::Transparent);
    oCircle.setOutlineColor(oColor);
    oCircle.setOutlineThickness(10);
    window.draw(oCircle);
}

void GUI::renderBoard() {
    sf::RectangleShape board(sf::Vector2f(BOARD_SIZE, BOARD_SIZE));
    board.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y);
    board.setFillColor(sf::Color(40, 40, 60));
    window.draw(board);
}

void GUI::renderGrid() {
    // Vertical lines
    for (int i = 1; i < 3; ++i) {
        sf::RectangleShape line(sf::Vector2f(5, BOARD_SIZE));
        line.setPosition(BOARD_OFFSET_X + i * CELL_SIZE, BOARD_OFFSET_Y);
        line.setFillColor(gridColor);
        window.draw(line);
    }

    // Horizontal lines
    for (int i = 1; i < 3; ++i) {
        sf::RectangleShape line(sf::Vector2f(BOARD_SIZE, 5));
        line.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y + i * CELL_SIZE);
        line.setFillColor(gridColor);
        window.draw(line);
    }
}

void GUI::renderMarks() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            Cell cell = game.getBoard().getCell(row, col);
            if (cell == Cell::X) {
                renderX(row, col);
            } else if (cell == Cell::O) {
                renderO(row, col);
            }
        }
    }
}

void GUI::renderX(int row, int col) {
    sf::Vector2f center = getCellCenter(row, col);
    float size = CELL_SIZE * 0.6f;
    float halfSize = size / 2.0f;

    // Draw two lines forming an X
    sf::RectangleShape line1(sf::Vector2f(size, 10));
    line1.setOrigin(halfSize, 5);
    line1.setPosition(center);
    line1.setRotation(45);
    line1.setFillColor(xColor);
    window.draw(line1);

    sf::RectangleShape line2(sf::Vector2f(size, 10));
    line2.setOrigin(halfSize, 5);
    line2.setPosition(center);
    line2.setRotation(-45);
    line2.setFillColor(xColor);
    window.draw(line2);
}

void GUI::renderO(int row, int col) {
    sf::Vector2f center = getCellCenter(row, col);
    float radius = CELL_SIZE * 0.3f;

    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(oColor);
    circle.setOutlineThickness(10);
    window.draw(circle);
}

void GUI::renderHover() {
    if (hoveredCell >= 0 && hoveredCell < 9 && game.getBoard().isValidMove(hoveredCell)) {
        int row, col;
        Board::positionToRowCol(hoveredCell, row, col);

        sf::RectangleShape highlight(sf::Vector2f(CELL_SIZE - 10, CELL_SIZE - 10));
        highlight.setPosition(BOARD_OFFSET_X + col * CELL_SIZE + 5, BOARD_OFFSET_Y + row * CELL_SIZE + 5);
        highlight.setFillColor(hoverColor);
        window.draw(highlight);
    }
}

void GUI::renderWinningLine() {
    if (!hasWinningLine || winningLine[0] == -1) {
        return;
    }

    int row1, col1, row2, col2;
    Board::positionToRowCol(winningLine[0], row1, col1);
    Board::positionToRowCol(winningLine[2], row2, col2);

    sf::Vector2f start = getCellCenter(row1, col1);
    sf::Vector2f end = getCellCenter(row2, col2);

    // Calculate line
    sf::Vector2f direction = end - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f;

    sf::RectangleShape line(sf::Vector2f(length, 8));
    line.setPosition(start);
    line.setRotation(angle);
    line.setFillColor(winLineColor);
    window.draw(line);
}

void GUI::renderUI() {
    // Draw score boxes
    sf::RectangleShape scoreBox(sf::Vector2f(350, 80));
    scoreBox.setPosition(50, 30);
    scoreBox.setFillColor(sf::Color(50, 50, 70));
    scoreBox.setOutlineColor(gridColor);
    scoreBox.setOutlineThickness(2);
    window.draw(scoreBox);

    scoreBox.setPosition(400, 30);
    window.draw(scoreBox);

    // Note: Without a loaded font, we can't render text
    // In a complete implementation, you would load a font and render:
    // - Player scores
    // - Current turn indicator
    // - Instructions
}

void GUI::renderGameOver() {
    // Draw semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    // Draw game over box
    sf::RectangleShape gameOverBox(sf::Vector2f(500, 300));
    gameOverBox.setPosition(150, 300);
    gameOverBox.setFillColor(sf::Color(50, 50, 80));
    gameOverBox.setOutlineColor(gridColor);
    gameOverBox.setOutlineThickness(5);
    window.draw(gameOverBox);

    // Draw winner symbol
    Cell winner = game.getWinner();
    if (winner == Cell::X) {
        // Draw big X
        sf::RectangleShape line1(sf::Vector2f(150, 15));
        line1.setPosition(325, 380);
        line1.setRotation(45);
        line1.setFillColor(xColor);
        window.draw(line1);

        sf::RectangleShape line2(sf::Vector2f(150, 15));
        line2.setPosition(325, 486);
        line2.setRotation(-45);
        line2.setFillColor(xColor);
        window.draw(line2);
    } else if (winner == Cell::O) {
        // Draw big O
        sf::CircleShape bigO(60);
        bigO.setPosition(340, 380);
        bigO.setFillColor(sf::Color::Transparent);
        bigO.setOutlineColor(oColor);
        bigO.setOutlineThickness(15);
        window.draw(bigO);
    } else {
        // Draw = for draw
        sf::RectangleShape line1(sf::Vector2f(120, 15));
        line1.setPosition(340, 410);
        line1.setFillColor(sf::Color(200, 200, 200));
        window.draw(line1);

        sf::RectangleShape line2(sf::Vector2f(120, 15));
        line2.setPosition(340, 450);
        line2.setFillColor(sf::Color(200, 200, 200));
        window.draw(line2);
    }
}

int GUI::getCellFromPosition(int x, int y) const {
    if (x < BOARD_OFFSET_X || x >= BOARD_OFFSET_X + BOARD_SIZE ||
        y < BOARD_OFFSET_Y || y >= BOARD_OFFSET_Y + BOARD_SIZE) {
        return -1;
    }

    int col = (x - BOARD_OFFSET_X) / CELL_SIZE;
    int row = (y - BOARD_OFFSET_Y) / CELL_SIZE;

    return Board::rowColToPosition(row, col);
}

sf::Vector2f GUI::getCellCenter(int row, int col) const {
    float x = BOARD_OFFSET_X + col * CELL_SIZE + CELL_SIZE / 2.0f;
    float y = BOARD_OFFSET_Y + row * CELL_SIZE + CELL_SIZE / 2.0f;
    return sf::Vector2f(x, y);
}

void GUI::findWinningLine() {
    const Board& board = game.getBoard();
    Cell winner = board.getWinner();

    if (winner == Cell::EMPTY) {
        hasWinningLine = false;
        return;
    }

    // Check rows
    for (int row = 0; row < 3; ++row) {
        if (board.getCell(row, 0) == winner &&
            board.getCell(row, 1) == winner &&
            board.getCell(row, 2) == winner) {
            winningLine = {row * 3, row * 3 + 1, row * 3 + 2};
            hasWinningLine = true;
            return;
        }
    }

    // Check columns
    for (int col = 0; col < 3; ++col) {
        if (board.getCell(0, col) == winner &&
            board.getCell(1, col) == winner &&
            board.getCell(2, col) == winner) {
            winningLine = {col, col + 3, col + 6};
            hasWinningLine = true;
            return;
        }
    }

    // Check diagonals
    if (board.getCell(0, 0) == winner &&
        board.getCell(1, 1) == winner &&
        board.getCell(2, 2) == winner) {
        winningLine = {0, 4, 8};
        hasWinningLine = true;
        return;
    }

    if (board.getCell(0, 2) == winner &&
        board.getCell(1, 1) == winner &&
        board.getCell(2, 0) == winner) {
        winningLine = {2, 4, 6};
        hasWinningLine = true;
        return;
    }

    hasWinningLine = false;
}

sf::Text GUI::createText(const std::string& str, int size, sf::Color color, float x, float y) {
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    return text;
}
