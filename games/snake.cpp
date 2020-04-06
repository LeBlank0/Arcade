//
// Created by blanko on 01/04/2020.
//

#include <iostream>
#include "../include/snake.hpp"

Snake::Snake() {
    int fd = open("/dev/urandom", O_RDONLY);
    unsigned seed;

    read(fd, &seed, sizeof seed);
    srand(seed);
    for (int i = 0; i < 20; i++) {
        std::vector<Rect> tmp;
        rect.push_back(tmp);
        for (int y = 0; y < 20; y++) {
            Rect rtmp = Rect(Vector2f(i * 5, y * 5), Vector2f(40, 30), colorMap);
            if (i == 0 || i == 19 || y == 0 || y == 19)
                rtmp.setColor(colorBorder);
            rect[i].push_back(rtmp);
        }
    }
}

void Snake::handleEvent(const std::string &event) {
    if (event == "right" && move == false) {
        dir += 1;
        move = true;
    }
    if (event == "left" && move == false) {
        dir -= 1;
        move = true;
    }
    if (dir < 0)
        dir = 3;
    if (dir > 3)
        dir = 0;
}

void Snake::handleUpdate(int t) {
    if (t - time > 200000 && loop > 150000)
        loop -= 100;
    if (t - time > loop) {
        move = false;
        moveSnake();
        eat = 0;
        if (snake[0].x == apple.x && snake[0].y == apple.y)
            newApple();
        collision();
        for (int i = 1; i < 19; i++)
            for (int y = 1; y < 19; y++)
                setMapRectColor(i, y);
        time = t;
    }
}

void Snake::handleRender(IGraphicRenderer &renderer) const {
    renderer.clearScreen();
    for (int i = 0; i < 20; i++)
        for (int y = 0; y < 20; y++) {
            renderer.drawRect(rect[i][y]);
        }
    renderer.drawText(name);
    renderer.drawText(score);
    renderer.drawText(scoreNb);
    renderer.drawScreen();
}

const std::map<std::string, std::string> Snake::getGameData()
{
    std::map<std::string, std::string> map;

    if (_gameOver)
        map["go"] = "yes";
    return (map);
}

void Snake::newApple() {
    Vector2f new_snake = Vector2f(snake[size_snake - 1].y, snake[size_snake - 1].x);
    snake.push_back(new_snake);
    size_snake++;
    eat = 1;
    int randx = (rand() % 18) + 1;
    int randy = (rand() % 18) + 1;
    for (int s = 0; s != size_snake; s++)
        if (snake[s].x == randx * 5 && snake[s].y == randy * 5) {
            randx = (rand() % 18) + 1;
            randy = (rand() % 18) + 1;
            s = -1;
        }
    Vector2f new_apple = Vector2f(randx * 5, randy * 5);
    apple = new_apple;
    scoreNb.setText(std::to_string(size_snake - 4));
}

void Snake::moveSnake() {
    for (int i = size_snake - eat; i > 0; i--) {
        Vector2f part = Vector2f(snake[i - 1].x, snake[i - 1].y);
        snake[i] = part;
    }
    if (dir == 0)
        snake[0] -= Vector2f(0, 5);
    if (dir == 1)
        snake[0] += Vector2f(5, 0);
    if (dir == 2)
        snake[0] += Vector2f(0, 5);
    if (dir == 3)
        snake[0] -= Vector2f(5, 0);
}

void Snake::collision() {
    if (snake[0].x < 5 || snake[0].x > 90 || snake[0].y < 5 || snake[0].y > 90)
        _gameOver = true;
    for (int s = 1; s != size_snake + eat; s++)
        if (snake[0].x == snake[s].x && snake[0].y == snake[s].y)
            _gameOver = true;
}

void Snake::setMapRectColor(int i, int y) {
    for (int s = 1; s != size_snake - eat; s++) {
        if (rect[i][y].getPositionX() == snake[s].x && rect[i][y].getPositionY() == snake[s].y) {
            if (s % 2 == 0)
                rect[i][y].setColor(colorSnake1);
            else if (s % 2 == 1)
                rect[i][y].setColor(colorSnake2);
            break;
        }
        else
            rect[i][y].setColor(colorMap);
    }
    if (rect[i][y].getPositionX() == apple.x && rect[i][y].getPositionY() == apple.y)
        rect[i][y].setColor(colorApple);
    if (rect[i][y].getPositionX() == snake[0].x && rect[i][y].getPositionY() == snake[0].y)
        rect[i][y].setColor(colorHead);
}

extern "C"
IGame *entry() {
    return new Snake();
}
