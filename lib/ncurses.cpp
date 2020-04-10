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
        if (key == 127 || key == KEY_DC) {
            isOpen = false;
            return "quit";
        }
    }
    return "";
}

void ncurses::drawScreen() {
    refresh();
}

void ncurses::clearScreen() {
    clear();
}

int ncurses::getncursecolor(const AColor &color) {
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

int ncurses::makeasquarepair(const Rect &rect)
{
    int i = 0;

    if (maxsquare == 0) {
        init_pair(i+100, getncursecolor(rect.getColor()), getncursecolor(rect.getColor()));
        contentj.push_back(getncursecolor(rect.getColor()));
        maxsquare++;
        return (0);
    }
    i = 1;
    for (; i < contentj.size(); i++)
        if (getncursecolor(rect.getColor()) == contentj[i])
            return (i+100);
    maxpairs++;
    init_pair(i+100, COLOR_BLACK, getncursecolor(rect.getColor()));
    contentj.push_back(getncursecolor(rect.getColor()));
    return (i);
}

int ncurses::makeatextpair(const Text &text)
{
    int i = 0;

    if (maxpairs == 0) {
        init_pair(i, getncursecolor(text.getColor()), COLOR_BLACK);
        contenti.push_back(getncursecolor(text.getColor()));
        maxpairs++;
        return (0);
    }
    i = 1;
    for (; i < contenti.size(); i++)
        if (getncursecolor(text.getColor()) == contenti[i])
            return (i);
    maxpairs++;
    init_pair(i, getncursecolor(text.getColor()), COLOR_BLACK);
    contenti.push_back(getncursecolor(text.getColor()));
    return (i);
}

void ncurses::drawSprite(const Sprite &sprite) {
}

void ncurses::color_pair()
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_RED);
    init_pair(4, COLOR_GREEN, COLOR_GREEN);
    init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(6, COLOR_BLUE, COLOR_BLUE);
    init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(8, COLOR_CYAN, COLOR_CYAN);

    init_pair(9, COLOR_RED, COLOR_BLACK);
    init_pair(10, COLOR_GREEN, COLOR_BLACK);
    init_pair(11, COLOR_BLUE, COLOR_BLACK);
    init_pair(12, COLOR_YELLOW, COLOR_BLACK);
    init_pair(13, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(14, COLOR_CYAN, COLOR_BLACK);
    init_pair(15, COLOR_WHITE, COLOR_BLACK);
}

void ncurses::colors(char red, char blue, char green)
{
    if (red < 80 && green < 80 && blue < 80)
        attron(COLOR_PAIR(1));
    if (red > 80 && green > 80 && blue > 80)
        attron(COLOR_PAIR(2));
    if (red > 80 && green < 80 && blue < 80)
        attron(COLOR_PAIR(3));
    if (red < 80 && green > 80 && blue < 80)
        attron(COLOR_PAIR(4));
    if (red > 80 && green > 80)
        attron(COLOR_PAIR(5));
    if (red < 80 && green < 80 && blue > 80)
        attron(COLOR_PAIR(6));
    if (red > 80 && blue > 80)
        attron(COLOR_PAIR(7));
    if (green > 80 && blue > 80)
        attron(COLOR_PAIR(8));
}

void ncurses::colors_text(char red, char blue, char green)
{
    if (red < 80 && green < 80 && blue < 80)
        attron(COLOR_PAIR(1));
    if (red > 80 && green < 80 && blue < 80)
        attron(COLOR_PAIR(9));
    if (red < 80 && green > 80 && blue < 80)
        attron(COLOR_PAIR(10));
    if (red < 80 && green < 80 && blue > 80)
        attron(COLOR_PAIR(11));
    if (red > 80 && green > 80)
        attron(COLOR_PAIR(12));
    if (red > 80 && blue > 80)
        attron(COLOR_PAIR(13));
    if (green > 80 && blue > 80)
        attron(COLOR_PAIR(14));
    if (red > 80 && green > 80 && blue > 80)
        attron(COLOR_PAIR(15));
}

void ncurses::drawRect(const Rect &rect) {
    attron(COLOR_PAIR(makeasquarepair(rect)));
//    colors(rect.getColorRed(), rect.getColorBlue(), rect.getColorGreen());
    for (size_t i = 0; i < rect.getSizeY(); i++) {
        for (size_t j = 0; j < rect.getSizeX(); j++) {
            mvprintw(static_cast<int>((rect.getPositionY() / 100 * 600) / (600 / 33)),
                     static_cast<int>((rect.getPositionX() / 100 * 800) / (800 / 88)),
                     "   ");
        }


    }
    attroff(COLOR_PAIR(makeasquarepair(rect)));
}

void ncurses::drawCircle(const Circle &circle) {
}

void ncurses::drawText(const Text &text) {
    attron(COLOR_PAIR(makeatextpair(text)));
//    colors(text.getColorRed(), text.getColorBlue(), text.getColorGreen());
    mvprintw(static_cast<int>((text.getPositionY() / 100 * 600) / (600 / 33)),
             static_cast<int>((text.getPositionX() / 100 * 800) / (800 / 88)),
             text.getText().c_str());
    attroff(COLOR_PAIR(makeatextpair(text)));
}

extern "C"
IGraphic *entry() {
    return new ncurses();
}
