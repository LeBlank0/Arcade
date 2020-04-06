//
// Created by chaoticks on 21/03/2020.
//

#ifndef OOP_ARCADE_2019_SFML_HPP
#define OOP_ARCADE_2019_SFML_HPP


#include "../interface/IGraphic.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Sfml : public IGraphic {
public:
    Sfml();
    ~Sfml() override = default;

    bool isOperational() override;
    std::string handleEvent() override;

    void drawScreen() override;
    void clearScreen() override;

    void drawRect(const Rect &rect) override;
    void drawCircle(const Circle &circle) override;
    void drawSprite(const Sprite &sprite) override;
    void drawText(const Text &text) override;

    sf::RenderWindow window;
    bool isOpen = true;
};

#endif //OOP_ARCADE_2019_SFML_HPP
