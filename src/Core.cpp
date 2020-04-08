/*
** EPITECH PROJECT, 2020
** cpp_pool
** File description:
** .cpp
*/

#include "../include/Core.hpp"
#include <dirent.h>
#include <iostream>

Core::Core() :
    _game(""),
    _graphic("")
{
    struct dirent *entry;
    DIR *dir_libs = opendir("./lib");
    DIR *dir_games = opendir("./games");

    std::string pathLibs = "./lib/";
    std::string pathGames = "./games/";

    std::string nameMenu = "";
    std::string finalName = "";

    if (dir_libs == NULL || dir_games == NULL)
        return;
    while ((entry = readdir(dir_libs)) != NULL) {
        std::string name = entry->d_name;
        if (name.length() > 3 && name.substr( name.length() - 3 ) == ".so") {
            _libs.push_back(pathLibs + name);
            nameMenu = name.substr(11);
            finalName = nameMenu.substr (0, nameMenu.length() - 3);
            _menu.libsNames.push_back(finalName);
        }
    }
    std::cout << std::endl;
    while ((entry = readdir(dir_games)) != NULL) {
        std::string name = entry->d_name;
        if (name.length() > 3 && name.substr( name.length() - 3 ) == ".so") {
            _games.push_back(pathGames + name);
            nameMenu = name.substr(12);
            finalName = nameMenu.substr (0, nameMenu.length() - 3);
            _menu.gamesNames.push_back(finalName);
        }
    }
    closedir(dir_libs);
    closedir(dir_games);
}

Core::~Core() {

}

int Core::run(std::string lib) {
    (void)lib;

    _menu.loadScores();
    _menu.setLettersSize();
    while (_loop) {
        if (_menu.getInfoPlay()) {
            _state = GAME;
        }
        if (!_stateLoad && _state == GAME) {
            loadGraphic(_menu.getIndexLib());
            loadGame(_menu.getIndexGame());
            _stateLoad = true;
        }
        if (_state == MENU)
            _loop = loop(_menu);
        else if (_state == GAME)
            _loop = loop(*this->_game);
        if (_state == GAME && _game->getGameData().find("go")->second == "yes")
            _state = MENU;
    }
    return (0);
}

void Core::loadGraphic(int index) {
    if (index == -1 || (size_t)index > _libs.size())
        return;
    _graphic.load(_libs.at(index));
    _indexGraphic = index;
}

void Core::loadGame(int index) {
    if (index == -1 || (size_t)index > _games.size())
        return;
    _game.load(_games.at(index));
    _indexGame = index;
}

bool Core::loop(IGame &render) {
    std::string event;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    event = _graphic->handleEvent();
    if (event == "quit")
        return (false);
    if (event == "menu" && _state == GAME) {
        _state = MENU;
        return (true);
    }
    render.handleEvent(event);
    render.handleUpdate(time + std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count());
    render.handleRender(*this->_graphic);
    time += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count();
    if (event == "next_graphic" && _state == GAME)
        swapGraphic(1);
    if (event == "prev_graphic" && _state == GAME)
        swapGraphic(-1);
    if (event == "next_game" && _state == GAME)
        swapGame(1);
    if (event == "next_game" && _state == GAME)
        swapGame(-1);
    return (true);
}

void Core::load(std::string lib) {
    int index = 0;

    for ( auto &i : _libs ) {
        if (i == lib) {
            _indexGraphic = index;
            _graphic.load(i);
            return;
        }
        index++;
    }
    printf("lib: %s is not in directory ./lib\n", lib.c_str());
    exit(84);
}

bool Core::menuLoop(Menu &menu) {
    (void)menu;
    return false;
}

bool Core::gameLoop() {
    return false;
}

void Core::swapGraphic(int index) {
    if ((long unsigned int)_indexGraphic + index >= _libs.size() || _indexGraphic + index < 0)
        return;
    _indexGraphic += index;
    loadGraphic(_indexGraphic);
}

void Core::swapGame(int index) {
    if ((long unsigned int)_indexGame + index >= _games.size() || _indexGame + index < 0)
        return;
    _indexGame += index;
    loadGame(_indexGame);
}
