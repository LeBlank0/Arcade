//
// Created by chaoticks on 21/03/2020.
//

#include "../include/libs/Sfml.hpp"

Sfml::Sfml() {
    window.create(sf::VideoMode(800, 600, 60), "Arcade");
}

bool Sfml::isOperational() {
    return isOpen;
}

std::string Sfml::handleEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isOpen = false;
            return "quit";
        }
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Delete) {
                isOpen = false;
                return "quit";
            }
            if (event.key.code == sf::Keyboard::Escape)
                return "menu";
            if (event.key.code == sf::Keyboard::E)
                return "next_game";
            if (event.key.code == sf::Keyboard::C)
                return "prev_game";
            if (event.key.code == sf::Keyboard::A)
                return "next_graphic";
            if (event.key.code == sf::Keyboard::W)
                return "prev_graphic";
            if (event.key.code == sf::Keyboard::Enter)
                return "enter";
            if (event.key.code == sf::Keyboard::Space)
                return "space";
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Z)
                return "up";
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q)
                return "left";
            if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                return "down";
            if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
                return "right";
            if (event.key.code == sf::Keyboard::R)
                return "restart";
            return "";
        }
    }
    return "";
}

void Sfml::drawScreen() {
    window.display();
}

void Sfml::clearScreen() {
    window.clear();
}

void Sfml::drawRect(const Rect &rect) {
    sf::RectangleShape rectangle(sf::Vector2f(rect.getSizeX(), rect.getSizeY()));

    rectangle.setFillColor(sf::Color(rect.getColorRed(), rect.getColorGreen(), rect.getColorBlue(), rect.getColorAlpha()));
    rectangle.setPosition(sf::Vector2f(POS(window.getSize().x, rect.getPositionX()), POS(window.getSize().y, rect.getPositionY())));
    window.draw(rectangle);
}

void Sfml::drawCircle(const Circle &circle) {
    sf::CircleShape cir(circle.getSizeX());

    cir.setFillColor(sf::Color(circle.getColorRed(), circle.getColorGreen(), circle.getColorBlue(), circle.getColorAlpha()));
    cir.setPosition(sf::Vector2f(POS(window.getSize().x, circle.getPositionX()), POS(window.getSize().y, circle.getPositionY())));
    window.draw(cir);
}

void Sfml::drawSprite(const Sprite &sprite) {
    sf::Texture te;
    sf::Sprite sp;

    te.loadFromFile(sprite.getTextureName());
    sp.setTexture(te);
    sp.setPosition(sf::Vector2f(POS(window.getSize().x, sprite.getPositionX()), POS(window.getSize().y, sprite.getPositionY())));
    window.draw(sp);
}

void Sfml::drawText(const Text &text) {
    sf::Font font;
    font.loadFromFile("assets/arial.ttf");
    sf::Text txt(text.getText(), font);

    txt.setStyle(sf::Text::Regular);
    txt.setFillColor(sf::Color(text.getColorRed(), text.getColorGreen(), text.getColorBlue(), text.getColorAlpha()));
    txt.setPosition(sf::Vector2f(POS(window.getSize().x, text.getPositionX()), POS(window.getSize().y, text.getPositionY())));
    window.draw(txt);
}

extern "C"
IGraphic *entry() {
    return new Sfml();
}
