//
// Created by elec on 01/04/2020.
//

#include <iostream>
#include "../include/solarfox.hpp"

Solarfox::Solarfox()
{
}

void Solarfox::handleEvent(const std::string &event)
{
}

void Solarfox::handleUpdate(int t)
{
}

void Solarfox::handleRender(IGraphicRenderer &renderer) const
{
    renderer.clearScreen();
    renderer.drawRect(Rect(Vector2f(10,10), Vector2f(250,250), Color(0,255,0,255)));
    //    for (int i = 0; i < 20; i++)
//        for (int y = 0; y < 20; y++) {
//            renderer.drawRect(rect[i][y]);
//        }
    //    renderer.drawText(Text("NIK STOP", Vector2f(10,10), Vector2f(10, 10), Color(255, 255, 255, 0)));
    renderer.drawScreen();
}

const std::map<std::string, std::string> Solarfox::getGameData()
{
    std::map<std::string, std::string> map;

    if (_gameOver)
        map["go"] = "yes";
    return (map);
}

extern "C"
IGame *entry() {
    return new Solarfox();
}
