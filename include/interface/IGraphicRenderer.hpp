//
// Created by chaoticks on 19/03/2020.
//

#ifndef OOP_ARCADE_2019_IGRAPHICRENDERER_HPP
#define OOP_ARCADE_2019_IGRAPHICRENDERER_HPP

#include "../Drawables.hpp"

class IGraphicRenderer
{
public:
    virtual ~IGraphicRenderer() = default;
    virtual void drawScreen() = 0;
    virtual void clearScreen() = 0;
    virtual void drawRect(const Rect &rect) = 0;
    virtual void drawCircle(const Circle &circle) = 0;
    virtual void drawSprite(const Sprite &sprite) = 0;
    virtual void drawText(const Text &text) = 0;
    IGraphicRenderer &operator =(const IGraphicRenderer &) = delete;
};


#endif //OOP_ARCADE_2019_IGRAPHICRENDERER_HPP
