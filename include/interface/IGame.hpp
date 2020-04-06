//
// Created by chaoticks on 19/03/2020.
//

#ifndef OOP_ARCADE_2019_IGAME_HPP
#define OOP_ARCADE_2019_IGAME_HPP

#include <map>
#include <string>
#include "IGraphic.hpp"

class IGame
{
public:
    virtual ~IGame() = default;

    virtual void handleEvent(const std::string &name) = 0;
    virtual void handleUpdate(int elepsedTime) = 0;
    virtual void handleRender(IGraphicRenderer &renderer) const = 0;

    virtual const std::map<std::string, std::string> getGameData() = 0;
};


#endif //OOP_ARCADE_2019_IGAME_HPP
