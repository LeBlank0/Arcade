//
// Created by elec on 01/04/2020.
//

#include <iostream>
#include "../include/snake.hpp"

void Snake::handleEvent(const std::string &event) {

}

void Snake::handleUpdate(int time) {

}

void Snake::handleRender(IGraphicRenderer &renderer) const {

}

extern "C"
IGame *entry() {
    return new Snake();
}
