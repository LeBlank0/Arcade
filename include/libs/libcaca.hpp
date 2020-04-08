//
// Created by chaoticks on 21/03/2020.
//

#ifndef OOP_ARCADE_2019_LIBCACA_HPP
#define OOP_ARCADE_2019_LIBCACA_HPP

#include "../interface/IGraphic.hpp"
#include <caca.h>

class libcaca : public IGraphic {
public:
    libcaca();
    ~libcaca() override;

    bool isOperational() override;

    std::string handleEvent() override;

    void drawScreen() override;
    void clearScreen() override;

    void drawRect(const Rect &rect) override;
    void drawCircle(const Circle &circle) override;
    void drawSprite(const Sprite &sprite) override;
    void drawText(const Text &text) override;

    void setColor(const AColor &color, bool background);

    caca_canvas_t *_cv;
    caca_display_t *_dp;
    caca_event_t _ev;

    bool isOpen = true;
};


#endif //OOP_ARCADE_2019_LIBCACA_HPP
