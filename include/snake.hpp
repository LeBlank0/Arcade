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

class Snake : public IGame {
public:
    Snake();
    ~Snake() override = default;

    void handleEvent(const std::string &name) override;
    void handleUpdate(int elapsedTime) override;
    void handleRender(IGraphicRenderer &renderer) const override;
    const std::map<std::string, std::string> getGameData() override;

    void newApple();
    void moveSnake();
    void collision();
    void setMapRectColor(int i, int y);

private:
    Color colorBlack = Color(0, 0, 0, 255);
    Color colorWhite = Color(255, 255, 255, 255);
    Color colorMap = Color(250, 255, 0, 255);
    Color colorBorder = Color(0, 255, 255, 255);
    Color colorSnake1 = Color(255, 0, 255, 255);
    Color colorSnake2 = Color(0, 255, 0, 255);
    Color colorHead = Color(0, 0, 255, 255);
    Color colorApple = Color(255, 0, 0, 255);

    bool _gameOver = false;
    int size_snake = 4;
    int loop = 200000;
    int eat = 0;
    int time = 0;
    int dir = 0;
    bool move = false;
    Vector2f apple = Vector2f(15, 70);

    Text name = Text(" Snake ", Vector2f(2, -1), Vector2f(5, 5), colorWhite);
    Text score = Text(" Score : ", Vector2f(40, -1), Vector2f(5, 5), colorWhite);
    Text scoreNb = Text("0", Vector2f(55, -1), Vector2f(5, 5), colorWhite);
    std::vector<std::vector<Rect>> rect;
    std::vector<Vector2f> snake = {
        Vector2f(50, 50),
        Vector2f(50, 55),
        Vector2f(50, 60),
        Vector2f(50, 65),
    };
};


#endif //OOP_ARCADE_2019_SNAKE_HPP
