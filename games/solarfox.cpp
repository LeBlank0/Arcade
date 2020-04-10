//
// Created by elec on 01/04/2020.
//

#include <iostream>
#include <fstream>
#include "../include/solarfox.hpp"

Solarfox::Solarfox()
{
    int fd = open("/dev/urandom", O_RDONLY);
    unsigned seed;

    openmap();
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

void Solarfox::openmap() {
    std::ifstream file1{"assets/SolarFoxMap1"};
    std::ifstream file2{"assets/SolarFoxMap2"};
    std::ifstream file3{"assets/SolarFoxMap3"};
    std::string line;

    if (file1) {
        while (getline(file1, line)) {
            line += '\n';
            map1.emplace_back(line);
            line = "";
        }
    } else {
        std::cout << "Solarfox map does not exist\n";
        exit(84);
    }
    line = "";
    if (file2) {
        while (getline(file2, line)) {
            line += '\n';
            map2.emplace_back(line);
            line = "";
        }
    } else {
        std::cout << "Solarfox map does not exist\n";
        exit(84);
    }
    line = "";
    if (file3) {
        while (getline(file3, line)) {
            line += '\n';
            map3.emplace_back(line);
            line = "";
        }
    } else {
        std::cout << "Solarfox Score does not exist\n";
        exit(84);
    }
    file1.close();
    file2.close();
    file3.close();
    themap = 1;
    mapcurrent = map1;
}

void Solarfox::handleEvent(const std::string &event)
{
    if (event == "right" && !move) {
        dir += 1;
        move = true;
    }
    if (event == "left" && !move) {
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

int Solarfox::countmap() {
    size_t count = 0;

    for (auto &i : mapcurrent) {
        if(i.find('1') != std::string::npos) {
            count++;
        }
    }
    std::cout << count << std::endl;
    return count;
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
    if (mapcurrent[i][y] == '1' && ship.x == rect[y][i].getPositionX() && ship.y == rect[y][i].getPositionY()) {
        score+=10;
        mapcurrent[i][y] = '0';
        scoreNb.setText(std::to_string(score));
        if (countmap() == 0) {
            if (themap == 1) {
                mapcurrent = map2;
                themap = 2;
            } else if (themap == 2) {
                mapcurrent = map3;
                themap = 3;
            } else if (themap == 3) {
                mapcurrent = map1;
                themap = 1;
            }
        }
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
    if (mapcurrent[i][y] == '*')
        rect[y][i].setColor(colorBorder);
    if (mapcurrent[i][y] == '1')
        rect[y][i].setColor(colorCoins);
    if (ship.x == rect[y][i].getPositionX() && ship.y ==        rect[y][i].getPositionY())
        rect[y][i].setColor(colorShip);
}

extern "C"
IGame *entry() {
    return new Solarfox();
}
