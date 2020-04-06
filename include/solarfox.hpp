//
// Created by blanko on 01/04/2020.
//

#ifndef OOP_ARCADE_2019_SNAKE_HPP
#define OOP_ARCADE_2019_SNAKE_HPP

#include "interface/IGame.hpp"
#include <vector>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

class Solarfox : public IGame {
public:
    Solarfox();
    ~Solarfox() override = default;

    void handleEvent(const std::string &name) override;
    void handleUpdate(int elapsedTime) override;
    void handleRender(IGraphicRenderer &renderer) const override;
    const std::map<std::string, std::string> getGameData() override;

private:
    Color colorBlack = Color(0, 0, 0, 255);
    Color colorMap = Color(255, 0, 255, 255);
    Color colorBorder = Color(255, 0, 125, 255);
    Color colorSnake = Color(61, 154, 59, 255);
    Color colorApple = Color(255, 125, 0, 255);

    bool _gameOver = false;
    int size_snake = 4;
    int eat = 0;
    int time = 0;
    int dir = 0;
    bool move = false;
    Vector2f apple = Vector2f(15, 70);

    std::vector<std::vector<Rect>> rect;
    std::vector<Vector2f> snake = {
        Vector2f(50, 50),
        Vector2f(50, 55),
        Vector2f(50, 60),
        Vector2f(50, 65),
    };
};


#endif //OOP_ARCADE_2019_SNAKE_HPP
