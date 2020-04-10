//
// Created by elec on 01/04/2020.
//

#include <iostream>
#include "../include/solarfox.hpp"

Solarfox::Solarfox()
{
    // remplace la var map par la lecture de fichier dans assets (fait gaffe le chemin c'est juste ./assets/SolarFoxMap1)
    int fd = open("/dev/urandom", O_RDONLY);
    unsigned seed;

    read(fd, &seed, sizeof seed);
    srand(seed);
    for (int i = 0; i < 20; i++) {
        std::vector<Rect> tmp;
        rect.push_back(tmp);
        for (int y = 0; y < 20; y++) {
            Rect rtmp = Rect(Vector2f(i * 5, y * 5), Vector2f(40, 30), colorBlack);
            rect[i].push_back(rtmp);
        }
    }
}

void Solarfox::handleEvent(const std::string &event)
{
    if (event == "right" && move == false) {
        dir += 1;
        move = true;
    }
    if (event == "left" && move == false) {
        dir -= 1;
        move = true;
    }
    if (event == "space" && speed == 150000) {
        speed = 120000;
    } else if (event == "space" && speed == 120000)
        speed = 150000;
    if (dir < 0)
        dir = 3;
    if (dir > 3)
        dir = 0;
}

void Solarfox::handleUpdate(int t)
{
    if (t - timeShip > speed) {
        move = false;
        moveShip();
        collision();
        for (int i = 0; i < 20; i++)
            for (int y = 0; y < 20; y++) {
                handleCoins(i, y);
                setMapRectColor(i, y);
            }
        timeShip = t;
    }
    if (t - timeEnnemies > 150000) {
        timeEnnemies = t;
    }
    if (t - timeShoot > 50000) {
        timeShoot = t;
    }
}

void Solarfox::handleRender(IGraphicRenderer &renderer) const
{
    renderer.clearScreen();
    for (int i = 0; i < 20; i++)
        for (int y = 0; y < 20; y++) {
            renderer.drawRect(rect[i][y]);
        }
    renderer.drawText(name);
    renderer.drawText(scoretxt);
    renderer.drawText(scoreNb);
    renderer.drawScreen();
}

const std::map<std::string, std::string> Solarfox::getGameData()
{
    std::map<std::string, std::string> map;

    if (_gameOver)
        map["go"] = "yes";
    return (map);
}

void Solarfox::handleCoins(int i, int y) {
    if (map[i][y] == '1' && ship.x == rect[y][i].getPositionX() && ship.y == rect[y][i].getPositionY()) {
        score++;
        map[i][y] = '0';
        scoreNb.setText(std::to_string(score));
    }
}

void Solarfox::moveShip() {
    if (dir == 0)
        ship -= Vector2f(0, 5);
    if (dir == 1)
        ship += Vector2f(5, 0);
    if (dir == 2)
        ship += Vector2f(0, 5);
    if (dir == 3)
        ship -= Vector2f(5, 0);
}

void Solarfox::collision() {
    if (!(ship.x >= 0 && ship.x <= 95 && ship.y >= 10 && ship.y <= 85))
        _gameOver = true;
}

void Solarfox::setMapRectColor(int i, int y) {
    rect[y][i].setColor(colorBlack);
    if (map[i][y] == '*')
        rect[y][i].setColor(colorBorder);
    if (map[i][y] == '1')
        rect[y][i].setColor(colorCoins);
    if (ship.x == rect[y][i].getPositionX() && ship.y ==        rect[y][i].getPositionY())
        rect[y][i].setColor(colorShip);
}

extern "C"
IGame *entry() {
    return new Solarfox();
}
