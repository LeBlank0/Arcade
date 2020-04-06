//
// Created by chaoticks on 21/03/2020.
//

#include <iostream>
#include "../include/libs/ncurses.hpp"

ncurses::ncurses() {
    initscr();
    start_color();
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    getmaxyx(stdscr, this->row, this->col);
    cbreak();
    timeout(1);
}

bool ncurses::isOperational() {
    return isOpen;
}

int ncurses::getncursecolor(const AColor &color) {
    //    std::cout << "red : " << percent(color.getColorRed()) << std::endl;
    //    std::cout << "green : " << percent(color.getColorGreen()) << std::endl;
    //    std::cout << "blue : " << percent(color.getColorBlue()) << std::endl;
    if (percent(color.getColorRed()) > 80 &&
    percent(color.getColorGreen()) > 80 &&
    percent(color.getColorBlue()) > 80) {

        return COLOR_WHITE;
    } else if (percent(color.getColorGreen()) < 80 &&
    percent(color.getColorRed()) < 80 &&
    percent(color.getColorBlue()) < 80) {
        return COLOR_BLACK;
    } else if (percent(color.getColorGreen()) < 80 &&
    percent(color.getColorRed()) > 80 &&
    percent(color.getColorBlue()) < 80) {
        return COLOR_RED;
    } else if (percent(color.getColorGreen()) > 80 &&
    percent(color.getColorRed()) < 80 &&
    percent(color.getColorBlue()) < 80) {
        return COLOR_GREEN;
    } else if (percent(color.getColorGreen()) < 80 &&
    percent(color.getColorRed()) < 80 &&
    percent(color.getColorBlue()) > 80) {
        return COLOR_BLUE;
    } else if (percent(color.getColorRed()) > 80 &&
    percent(color.getColorGreen()) > 80) {
        return COLOR_YELLOW;
    } else if (percent(color.getColorRed()) > 80 &&
    percent(color.getColorBlue()) > 80) {
        return COLOR_MAGENTA;
    } else if (percent(color.getColorGreen()) > 80 &&
    percent(color.getColorBlue()) > 80) {
        return COLOR_CYAN;
    } else {
        return COLOR_WHITE;
    }
}

std::string ncurses::handleEvent() {
    int key = getch();
    if (key == ERR) {
        return "";
    } else {
        if (key == 27)
            return "menu";
        if (key == 'e')
            return "next_game";
        if (key == 'a')
            return "prev_game";
        if (key == 'x')
            return "next_graphic";
        if (key == 'w')
            return "prev_graphic";
        if (key == 10)
            return "enter";
        if (key == ' ')
            return "space";
        if (key == 'r')
            return "restart";
        if (key == 'z' || key == KEY_UP)
            return "up";
        if (key == 'q' || key == KEY_LEFT)
            return "left";
        if (key == 's' || key == KEY_DOWN)
            return "down";
        if (key == 'd' || key == KEY_RIGHT)
            return "right";
        if (key == KEY_BACKSPACE || key == KEY_DL) {
            isOpen = false;
            return "quit";
        }
    }
    return "";
}

void ncurses::drawScreen() {
    refresh();
    //    nodelay(stdscr,1);
    //    std::cout << "row : " <<  this->row << std::endl;
    //    std::cout << "col : " <<  this->col << std::endl;
}

void ncurses::clearScreen() {
    clear();
    //    clear();
}

void ncurses::drawRect(const Rect &rect) {
    init_pair(2, getncursecolor(rect.getColor()), COLOR_BLACK);
    attron(COLOR_PAIR(2));
    for (size_t i = 0; i < rect.getSizeY(); i++) {
        for (size_t j = 0; j < rect.getSizeX(); j++)
            mvprintw(static_cast<int>((rect.getPositionY() / 100 * 600) / (600 / 33)),
                     static_cast<int>((rect.getPositionX() / 100 * 800) / (800 / 88)), " ");
    }
    attroff(getncursecolor(rect.getColor()));
}

void ncurses::drawCircle(const Circle &circle) {
    init_pair(3, getncursecolor(circle.getColor()), COLOR_BLACK);
    attron(COLOR_PAIR(3));
    for (int i = 0; i < circle.getSizeX(); i++)
        for (int j = 0; j < circle.getSizeY(); j++) {
            if ((i - (circle.getSizeX() / 2)) * (i - (circle.getSizeX() / 2)) +
                (j - (circle.getSizeX() / 2) * (j - (circle.getSizeX() / 2))) ==
                (circle.getSizeX() / 2) * (circle.getSizeX() / 2)) {
                mvprintw(static_cast<int>((circle.getPositionY() / 100 * 600) /
                                          (600 / 33)),
                         static_cast<int>((circle.getPositionX() / 100 * 800) /
                                          (800 / 88)), " ");
            }
        }
    attroff(3);
}

void ncurses::drawSprite(const Sprite &sprite) {
}

//short int getPairFromColor(Color fg, Color bg) {
//    short id_fg = getColorId(fg);
//    short id_bg = getColorId(bg);
//    return getPairFromId(id_fg, id_bg);
//}
//
//short int getPairFromid(short int id_fg, short int id_bg) {
//    short int pair_fg;
//    short int pair_bg;
//
//    for (short int i = 1; i < Biggestpair; ++i) {
//        pair_content(i, &pair_fg, &pair_bg);
//        if(id_fg == pair_fg && id_fg, id_bg)
//            return i;
//    }
//    init_pair(Biggestpair);
//}
//
//short int getColorId(Color color) {
//    short int r;
//    short int g;
//    short int b;
//
//    for (short int i = 0; i < Biggestpair; ++i) {
//        color_content(i, &r, &g, &b);
//        if ( r == color.red && g == color.green && b == color.blue)
//            return i;
//    }
//    init_color(Biggestpair, color.red, color.green, color.blue);
//    return Biggestpair++;
//}

int ncurses::makeapair(const Text &text)
{
    int i = 0;

    if (maxpairs == 0) {
        contenti.push_back(getncursecolor(text.getColor()));
        maxpairs++;
        return (0);
    }
    for (; i < contenti.size(); i++)
        if (getncursecolor(text.getColor()) == contenti[i])
            return (i);
    maxpairs++;
    contenti.push_back(getncursecolor(text.getColor()));
    return (i);
}

void ncurses::drawText(const Text &text) {
    attron(COLOR_PAIR(makeapair(text)));
    mvprintw(static_cast<int>((text.getPositionY() / 100 * 600) / (600 / 33)),
             static_cast<int>((text.getPositionX() / 100 * 800) / (800 / 88)),
             text.getText().c_str());
    attroff(COLOR_PAIR(1));
}

extern "C"
IGraphic *entry() {
    return new ncurses();
}
