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
    enemypos.emplace_back(2);
    enemypos.emplace_back(18);
    shoot1.emplace_back(99);
    shoot1.emplace_back(99);
    shoot2.emplace_back(99);
    shoot2.emplace_back(99);
    for (int i = 0; i < 20; i++) {
        std::vector<Rect> tmp;
        rect.push_back(tmp);
        for (int y = 0; y < 20; y++) {
            Rect rtmp = Rect(Vector2f(i * 5, y * 5), Vector2f(40, 30), colorBlack);
            rect[i].push_back(rtmp);
        }
    }
}

void Solarfox::resetGame(int i) {
    shoot1.at(0) = 0;
    shoot1.at(1) = 0;
    shoot2.at(0) = 0;
    shoot2.at(1) = 0;
    already1 = 0;
    already2 = 0;
    csave1 = ' ';
    csave2 = ' ';
    if (i == 0) {
        enemypos.at(0) = 2;
        enemypos.at(1) = 18;
//        emplaceback(score);
//        saveSolarfox();
        score = 0;
        timeShip = 0;
        timeEnnemies = 0;
        timeShootEnnemies = 0;
        timeShoot = 0;
        dir = 0;
        themap = 1;
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
    if (event == "enter")
        playerShoot();
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
        if(i.find('1') != std::string::npos)
            count++;
    }
    return count;
}

void Solarfox::modify1() {
    shoot1.at(0) = 0;
    shoot1.at(1) = 0;
    csave1 = ' ';
    already1 = 0;
}

void Solarfox::modify2() {
    shoot2.at(0) = 0;
    shoot2.at(1) = 0;
    csave2 = ' ';
    already2 = 0;
}

void Solarfox::playerShoot() {
    if (dir == 0) {
        if (mapcurrent[ship.y/5 - 1][ship.x / 5] == mapcurrent[shoot1.at(0)][shoot1.at(1)]) {
            mapcurrent[ship.y/5 - 1][ship.x / 5] = csave1;
            modify1();
        }
        if (mapcurrent[ship.y/5 - 1][ship.x / 5] == mapcurrent[shoot2.at(0)][shoot2.at(1)]) {
            mapcurrent[ship.y/5 - 1][ship.x / 5] = csave2;
            modify2();
        }
        if (mapcurrent[ship.y/5 - 2][ship.x / 5] == mapcurrent[shoot1.at(0)][shoot1.at(1)]) {
            mapcurrent[ship.y/5 - 2][ship.x / 5] = csave1;
            modify1();
        }
        if (mapcurrent[ship.y/5 - 2][ship.x / 5] == mapcurrent[shoot2.at(0)][shoot2.at(1)]) {
            mapcurrent[ship.y/5 - 2][ship.x / 5] = csave2;
            modify2();
        }
    } else if (dir == 1) {
        if (mapcurrent[ship.y/5][ship.x / 5 + 1] == mapcurrent[shoot1.at(0)][shoot1.at(1)]) {
            mapcurrent[ship.y/5][ship.x / 5 + 1] = csave1;
            modify1();
        }
        if (mapcurrent[ship.y/5][ship.x / 5 + 1] == mapcurrent[shoot2.at(0)][shoot2.at(1)]) {
            mapcurrent[ship.y/5][ship.x / 5 + 1] = csave2;
            modify2();
        }
        if (mapcurrent[ship.y/5][ship.x / 5 + 2] == mapcurrent[shoot1.at(0)][shoot1.at(1)]) {
            mapcurrent[ship.y/5][ship.x / 5 + 2] = csave1;
            modify1();
        }
        if (mapcurrent[ship.y/5][ship.x / 5 + 2] == mapcurrent[shoot2.at(0)][shoot2.at(1)]) {
            mapcurrent[ship.y/5][ship.x / 5 + 2] = csave2;
            modify2();
        }
    } else if (dir == 2) {
        if (mapcurrent[ship.y/5 + 1][ship.x / 5] == mapcurrent[shoot1.at(0)][shoot1.at(1)]) {
            mapcurrent[ship.y/5 + 1][ship.x / 5] = csave1;
            modify1();
        }
        if (mapcurrent[ship.y/5 + 1][ship.x / 5] == mapcurrent[shoot2.at(0)][shoot2.at(1)]) {
            mapcurrent[ship.y/5 + 1][ship.x / 5] = csave2;
            modify2();
        }
        if (mapcurrent[ship.y/5 + 2][ship.x / 5] == mapcurrent[shoot1.at(0)][shoot1.at(1)]) {
            mapcurrent[ship.y/5 + 2][ship.x / 5] = csave1;
            modify1();
        }
        if (mapcurrent[ship.y/5 + 2][ship.x / 5] == mapcurrent[shoot2.at(0)][shoot2.at(1)]) {
            mapcurrent[ship.y/5 + 2][ship.x / 5] = csave2;
            modify2();
        }
    } else if (dir == 3) {
        if (mapcurrent[ship.y/5][ship.x / 5 - 1] == mapcurrent[shoot1.at(0)][shoot1.at(1)]) {
            mapcurrent[ship.y/5][ship.x / 5 - 1] = csave1;
            modify1();
        }
        if (mapcurrent[ship.y/5][ship.x / 5 - 1] == mapcurrent[shoot2.at(0)][shoot2.at(1)]) {
            mapcurrent[ship.y/5][ship.x / 5 - 1] = csave2;
            modify2();
        }
        if (mapcurrent[ship.y/5][ship.x / 5 - 2] == mapcurrent[shoot1.at(0)][shoot1.at(1)]) {
            mapcurrent[ship.y/5][ship.x / 5 - 2] = csave1;
            modify1();
        }
        if (mapcurrent[ship.y/5][ship.x / 5 - 2] == mapcurrent[shoot2.at(0)][shoot2.at(1)]) {
            mapcurrent[ship.y/5][ship.x / 5 - 2] = csave2;
            modify2();
        }
    }
}

void Solarfox::enemyShoot(int i, int y, int z) {
    if (already1 == 0 || already2 == 0) {
        if (z == 0 && already1 == 0) {
            shoot1.at(0) = i+1;
            shoot1.at(1) = y;
            csave1 = mapcurrent[shoot1.at(0)][shoot1.at(1)];
            mapcurrent[shoot1.at(0)][shoot1.at(1)] = 'x';
            already1 = 1;
        } else if (z == 1 && already2 == 0){
            shoot2.at(0) = i-1;
            shoot2.at(1) = y;
            csave2 = mapcurrent[shoot2.at(0)][shoot2.at(1)];
            mapcurrent[shoot2.at(0)][shoot2.at(1)] = 'x';
            already2 = 1;
        }
    } else {
        if (z == 0) {
            if (shoot1.at(1) == (ship.x / 5) && shoot1.at(0) == (ship.y / 5)) {
                _gameOver = true;
                resetGame(1);
            } else if ((mapcurrent[shoot1.at(0)+1][shoot1.at(1)] == '9'
            || mapcurrent[shoot1.at(0)+1][shoot1.at(1)] == '*'
            || mapcurrent[shoot1.at(0)+1][shoot1.at(1)] == 'x') && already2 == 1) {
                mapcurrent[shoot1.at(0)][shoot1.at(1)] = '0';
                shoot1.at(0) = 0;
                shoot1.at(1) = 0;
                csave1 = ' ';
                already1 = 0;
            } else {
                mapcurrent[shoot1.at(0)][shoot1.at(1)] = csave1;
                shoot1.at(0) += 1;
                csave1 = mapcurrent[shoot1.at(0)][shoot1.at(1)];
                mapcurrent[shoot1.at(0)][shoot1.at(1)] = 'x';
            }
        } else {
            if (shoot2.at(1) == (ship.x / 5) && shoot2.at(0) == (ship.y / 5)) {
                _gameOver = true;
                resetGame(1);
            } else if ((mapcurrent[shoot2.at(0) - 1][shoot2.at(1)] == '9'
                || mapcurrent[shoot2.at(0) - 1][shoot2.at(1)] == '*'
                || mapcurrent[shoot2.at(0) - 1][shoot2.at(1)] == 'x') && already2 == 1) {
                mapcurrent[shoot2.at(0)][shoot2.at(1)] = '0';
                shoot2.at(0) = 0;
                shoot2.at(1) = 0;
                csave2 = ' ';
                already2 = 0;
            } else {
                mapcurrent[shoot2.at(0)][shoot2.at(1)] = csave2;
                shoot2.at(0) -= 1;
                csave2 = mapcurrent[shoot2.at(0)][shoot2.at(1)];
                mapcurrent[shoot2.at(0)][shoot2.at(1)] = 'x';
            }
        }
    }
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
    if (t - timeShootEnnemies > 200000) {
        enemyShoot(1, enemypos.at(0), 0);
        enemyShoot(18, enemypos.at(1), 1);
        timeShootEnnemies = t;
    }
    if (t - timeEnnemies > 150000) {
        timeEnnemies = t;
        wmove[0] = moveEnemy(wmove[0], 1, enemypos.at(0), 0);
        wmove[1] =  moveEnemy(wmove[1], 18, enemypos.at(1), 1);
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
                resetGame(0);
                mapcurrent = map2;
                themap = 2;
            } else if (themap == 2) {
                resetGame(0);
                mapcurrent = map3;
                themap = 3;
            } else if (themap == 3) {
                resetGame(0);
                mapcurrent = map1;
                themap = 1;
            }
        }
    }
}

void Solarfox::moveShip() {
    if(dir == 0)
        ship -= Vector2f(0,5);
    if(dir == 1)
        ship += Vector2f(5,0);
    if(dir == 2)
        ship += Vector2f(0,5);
    if(dir == 3)
        ship -= Vector2f(5,0);
}

char Solarfox::moveEnemy(char movement, int i, int y, int z) {
    if (movement == 'd') {
        if(mapcurrent[i][y + 1] != '#') {
            mapcurrent[i][y] = '*';
            mapcurrent[i][y + 1] = '9';
            enemypos.at(z) += 1;
            return movement;
        } else {
            mapcurrent[i][y] = '*';
            mapcurrent[i][y - 1] = '9';
            enemypos.at(z) -= 1;
            return 'g';
        }
    } else {
        if (mapcurrent[i][y - 1] != '#') {
            mapcurrent[i][y] = '*';
            mapcurrent[i][y - 1] = '9';
            enemypos.at(z) -= 1;
            return movement;
        } else {
            mapcurrent[i][y] = '*';
            mapcurrent[i][y + 1] = '9';
            enemypos.at(z) += 1;
            return 'd';
        }
    }
}

void Solarfox::collision() {
    if (!(ship.x >= 0 && ship.x <= 95 && ship.y >= 10 && ship.y <= 85)) {
        _gameOver = true;
        resetGame(1);
    }
}

void Solarfox::setMapRectColor(int i, int y) {
    rect[y][i].setColor(colorBlack);
    if (mapcurrent[i][y] == '*' || mapcurrent[i][y] == '#')
        rect[y][i].setColor(colorBorder);
    if (mapcurrent[i][y] == '1')
        rect[y][i].setColor(colorCoins);
    if (mapcurrent[i][y] == '9' || mapcurrent[i][y] == 'x')
        rect[y][i].setColor(colorEnemy);
    if (ship.x == rect[y][i].getPositionX() && ship.y == rect[y][i].getPositionY())
        rect[y][i].setColor(colorShip);
}

extern "C"
IGame *entry() {
    return new Solarfox();
}
