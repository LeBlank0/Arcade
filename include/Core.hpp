//
// Created by chaoticks on 19/03/2020.
//

#ifndef OOP_ARCADE_2019_CORE_HPP
#define OOP_ARCADE_2019_CORE_HPP

#include <map>
#include <string>
#include <vector>
#include <experimental/filesystem>
#include "interface/IGraphic.hpp"
#include "interface/IGame.hpp"
#include "SoLoader.hpp"
#include "Menu.hpp"

#define MENU 0
#define GAME 1

class Core
{
public:
    explicit Core();
    ~Core();

    int run(std::string lib);
    void load(std::string lib);

private:
    void loadGraphic(int index);
    void loadGame(int index);

    bool menuLoop(Menu &menu);
    bool gameLoop();

    void swapGraphic(int index);
    void swapGame(int index);

    bool loop(IGame &render);

    std::vector<std::string> _libs;
    std::vector<std::string> _games;

    int _indexGame = -1;
    int _indexGraphic = -1;

    SoLoader<IGame> _game;
    SoLoader<IGraphic> _graphic;

    Menu _menu;

    int _state = MENU;
    bool _loop = true;
    bool _stateLoad = false;
    int time = 0;
};

#endif //OOP_ARCADE_2019_CORE_HPP
