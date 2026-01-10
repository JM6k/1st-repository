#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Create a window with title
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test - Tic-Tac-Toe Setup");

    // Set frame rate limit
    window.setFramerateLimit(60);

    std::cout << "SFML window created successfully!" << std::endl;
    std::cout << "Close the window to exit." << std::endl;

    // Create a simple circle to test rendering
    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(300.f, 200.f);

    // Create text (note: we'll need a font for this to work fully)
    sf::Font font;
    sf::Text text;
    text.setString("SFML is working!\nClose window to continue.");
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setPosition(200.f, 450.f);

    // Main loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        // Clear window with a dark blue color
        window.clear(sf::Color(20, 20, 60));

        // Draw the circle
        window.draw(circle);

        // Draw text (if font loaded, otherwise skip)
        if (font.getInfo().family != "")
            window.draw(text);

        // Display
        window.display();
    }

    std::cout << "SFML test completed successfully!" << std::endl;
    return 0;
}
