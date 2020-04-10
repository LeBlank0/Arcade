//
// Created by chaoticks on 21/03/2020.
//

#include "../include/libs/libcaca.hpp"

#include <caca.h>

bool libcaca::isOperational() {
    return isOpen;
}

std::string libcaca::handleEvent() {
    caca_get_event(_dp, CACA_EVENT_KEY_PRESS, &_ev, 100000);
    if (caca_get_event_type(&_ev) == CACA_EVENT_KEY_PRESS) {
        int key = caca_get_event_key_ch(&_ev);
        if (key == 27)
            return "menu";
        if (key == 101)
            return "next_game";
        if (key == 99)
            return "prev_game";
        if (key == 97)
            return "next_graphic";
        if (key == 119)
            return "prev_graphic";
        if (key == 8 || key == 127) {
            isOpen = false;
            return "quit";
        }
        if (key == 114)
            return "restart";
        if (key == 13)
            return "enter";
        if (key == 32)
            return "space";
        if (key == 122 || key == 273)
            return "up";
        if (key == 113 || key == 275)
            return "left";
        if (key == 115 || key == 274)
            return "down";
        if (key == 100 || key == 276)
            return "right";
    }
    return "";
}

void libcaca::drawScreen() {
    caca_refresh_display(_dp);
}

void libcaca::clearScreen() {
    caca_set_color_ansi(_cv, CACA_BLACK, CACA_BLACK);
    caca_clear_canvas(_cv);
    caca_refresh_display(_dp);
}

void libcaca::drawRect(const Rect &rect) {
    int x = POS(int(caca_get_display_width(_dp)) / 10, rect.getPositionX());
    int y = POS(int(caca_get_display_height(_dp)) / 19, rect.getPositionY());
    int width = POS(caca_get_display_width(_dp) / 10, int(rect.getSizeX()));
    int height = POS(caca_get_display_height(_dp) / 19, int(rect.getSizeY()));

    setColor(rect.getColor(), true);
    caca_draw_box(_cv, x, y, width, height, 0);
    caca_refresh_display(_dp);
}

void libcaca::drawCircle(const Circle &circle) {
    int x = POS(int(caca_get_display_width(_dp)) / 5, circle.getPositionX() / 2);
    int y = POS(int(caca_get_display_height(_dp)) / 10, circle.getPositionY() / 2);
    int width = POS(caca_get_display_width(_dp) / 10, int(circle.getSizeX()) / 2);
    int height = POS(caca_get_display_height(_dp) / 19, int(circle.getSizeY()) / 2);

    setColor(circle.getColor(), false);
    caca_draw_ellipse(_cv, x, y, width, height, 0);
    caca_refresh_display(_dp);
}

void libcaca::drawSprite(const Sprite &sprite) {
    caca_import_area_from_file(_cv, 0, 0, sprite.getTextureName().c_str(), "ansi");
}

void libcaca::drawText(const Text &text) {
    int x = POS(int(caca_get_display_width(_dp)) / 5, text.getPositionX() / 2);
    int y = POS(int(caca_get_display_height(_dp)) / 9.5, text.getPositionY() / 2);

    setColor(text.getColor(), false);
    //caca_set_color_ansi(_cv, CACA_BLACK, CACA_WHITE);
    caca_put_str(_cv, x, y, text.getText().c_str());
}

void libcaca::setColor(const AColor &color, bool background) {
    uint16_t cacaColor = (color.getColorAlpha() / 255 * 15) << 12 |
            (color.getColorRed() / 255 * 15) << 8 |
            (color.getColorGreen() / 255 * 15) << 4 |
            (color.getColorBlue() / 255 * 15) << 0;

    caca_set_color_argb(_cv, cacaColor, background ? cacaColor : 0x0000);
}

libcaca::libcaca() {
    _dp = caca_create_display(nullptr);
    if(!_dp)
        return;
    _cv = caca_get_canvas(_dp);
    caca_set_display_title(_dp, "Arcade");
    caca_refresh_display(_dp);
}

libcaca::~libcaca() {
    caca_free_display(_dp);
}

extern "C"
IGraphic *entry() {
    return new libcaca();
}
