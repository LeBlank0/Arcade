//
// Created by blanko on 01/04/2020.
//

#ifndef OOP_ARCADE_2019_SOLARFOX_HPP
#define OOP_ARCADE_2019_SOLARFOX_HPP

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

    void moveShip();
    void collision();
    void handleCoins(int i, int y);
    void setMapRectColor(int i, int y);

private:
    Color colorBlack = Color(0, 0, 0, 255);
    Color colorBorder = Color(50, 50, 50, 255);
    Color colorShip = Color(61, 154, 59, 255);
    Color colorCoins = Color(255, 125, 0, 255);
    Color colorShoot = Color(255, 0, 255, 255);

    bool _gameOver = false;
    int score = 0;
    int speed = 150000;
    int timeShip = 0;
    int timeEnnemies = 0;
    int timeShoot = 0;
    int dir = 0;
    bool move = false;

    std::vector<std::string> map = {
        "********************",
        "********************",
        "00000000000000000000",
        "00000011011011000000",
        "00000100100100100000",
        "00000011011011000000",
        "00000000100100000000",
        "00000000011000000000",
        "00000000100100000000",
        "00000011011011000000",
        "00000100100100100000",
        "00000011011011000000",
        "00000000100100000000",
        "00000000011000000000",
        "00000000100100000000",
        "00000011011011000000",
        "00000100100100100000",
        "00000000000000000000",
        "********************",
        "********************",
    };
    std::vector<std::vector<Rect>> rect;
    Vector2f ship = Vector2f(50, 50);
    Text name = Text(" SolarFox ", Vector2f(2, -1), Vector2f(5, 5), colorBlack);
    Text scoretxt = Text(" Score : ", Vector2f(40, -1), Vector2f(5, 5), colorBlack);
    Text scoreNb = Text("0", Vector2f(55, -1), Vector2f(5, 5), colorBlack);
};


#endif //OOP_ARCADE_2019_SOLARFOX_HPP
