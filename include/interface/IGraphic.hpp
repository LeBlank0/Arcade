//
// Created by chaoticks on 19/03/2020.
//

#ifndef OOP_ARCADE_2019_IGRAPHIC_HPP
#define OOP_ARCADE_2019_IGRAPHIC_HPP

#include "../Drawables.hpp"
#include "IGraphicRenderer.hpp"

class IGraphic: public IGraphicRenderer
{
public:
    IGraphic() = default;
    IGraphic(const IGraphic &) = delete;

    virtual ~IGraphic() = default;
    virtual bool isOperational() = 0;
    virtual std::string handleEvent() = 0;
};

#endif //OOP_ARCADE_2019_IGRAPHIC_HPP
