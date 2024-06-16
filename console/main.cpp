#include <SFML/Graphics.hpp>
#include <vector>
#include "headers/game.hpp"
#include "headers/render.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1800, 1600), "ImGui Board Example");
    ImGui::SFML::Init(window);

    Board board;
    ImVec2 boardPosition(50.f, 50.f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                board.handleMouseClick(mousePos, boardPosition);
            }
        }

        ImGui::SFML::Update(window, sf::seconds(1.f / 60.f));

        window.clear(sf::Color::White);

        board.render(window, boardPosition);

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;

    return 0;
}