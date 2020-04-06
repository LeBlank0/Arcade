//
// Created by chaoticks on 21/03/2020.
//

#ifndef OOP_ARCADE_2019_OPENGL_HPP
#define OOP_ARCADE_2019_OPENGL_HPP


#include "../interface/IGraphic.hpp"
#include <ncurses.h>
#include <vector>

#define percent(x) (x * 0.39)

class ncurses : public IGraphic {
public:
    ncurses();
    ~ncurses() override = default;

    bool isOperational() override;
    std::string handleEvent() override;

    void drawScreen() override;
    void clearScreen() override;

    void drawRect(const Rect &rect) override;
    void drawCircle(const Circle &circle) override;
    void drawSprite(const Sprite &sprite) override;
    void drawText(const Text &text) override;
    int makeapair(auto &text);

    int getncursecolor(const AColor &color);

    int maxpairs = 0;
    std::vector<int>contenti;
    bool isOpen = true;
    int row = 0;
    int col = 0;

    int x = 0;
    int y = 0;
    WINDOW *my_win;

};

#endif //OOP_ARCADE_2019_OPENGL_HPP
