//
// Created by chaoticks on 01/04/2020.
//

#include <iostream>
#include "../include/Menu.hpp"

void Menu::handleEvent(const std::string &event) {
    if (state == PSEUDO) {
        eventPseudoLetter(event);
        eventPseudoCursor(event);
        if (event == "enter") {
            state = MENU;
            setName();
        }
    } else if (state == MENU) {
        if (cursorLine == 0)
            eventLineOne(event);
        else if (cursorLine == 1)
            eventLineTwo(event);
        else if (event == "enter" && cursorLine == 2) {
            cursorLine++;
            goToGame = true;
        }
    }
}

void Menu::eventLineOne(const std::string &event)
{
    if (event == "right" && cursorPosition == 0) {
        cursorPosition++;
        GameOne.setColor(colorUnselected);
        GameTwo.setColor(colorCursorSelected);
        ScoreOne.setText(_scoresSolarfox.at(0).first + " : " + std::to_string(_scoresSolarfox.at(0).second));
        ScoreTwo.setText(_scoresSolarfox.at(1).first + " : " + std::to_string(_scoresSolarfox.at(1).second));
        ScoreThree.setText(_scoresSolarfox.at(2).first + " : " + std::to_string(_scoresSolarfox.at(2).second));
    }
    if (event == "left" && cursorPosition == 1) {
        cursorPosition--;
        GameOne.setColor(colorCursorSelected);
        GameTwo.setColor(colorUnselected);
        ScoreOne.setText(_scoresSnake.at(0).first + " : " + std::to_string(_scoresSnake.at(0).second));
        ScoreTwo.setText(_scoresSnake.at(1).first + " : " + std::to_string(_scoresSnake.at(1).second));
        ScoreThree.setText(_scoresSnake.at(2).first + " : " + std::to_string(_scoresSnake.at(2).second));
    }
    if (event == "enter" && cursorPosition == 0) {
        cursorLine++;
        cursorPosition = 0;
        indexGame = 0;
        GameOne.setColor(colorSelected);
        GameTwo.setColor(colorBlack);
        LibOne.setColor(colorCursorSelected);
    }
    if (event == "enter" && cursorPosition == 1) {
        cursorLine++;
        cursorPosition = 0;
        GameTwo.setColor(colorSelected);
        GameOne.setColor(colorBlack);
        LibOne.setColor(colorCursorSelected);
        indexGame = 1;
    }
}

void Menu::eventLineTwo(const std::string &event)
{
    if (event == "enter")
        Play.setColor(colorCursorSelected);
    if (event == "right" && cursorPosition == 1) {
        cursorPosition++;
        LibTwo.setColor(colorUnselected);
        LibThree.setColor(colorCursorSelected);
    }
    if (event == "right" && cursorPosition == 0) {
        cursorPosition++;
        LibOne.setColor(colorUnselected);
        LibTwo.setColor(colorCursorSelected);
    }
    if (event == "left" && cursorPosition == 1) {
        cursorPosition--;
        LibOne.setColor(colorCursorSelected);
        LibTwo.setColor(colorUnselected);
    }
    if (event == "left" && cursorPosition == 2) {
        cursorPosition--;
        LibTwo.setColor(colorCursorSelected);
        LibThree.setColor(colorUnselected);
    }
    if (event == "enter" && cursorPosition == 0) {
        cursorLine++;
        indexLib = 0;
        LibOne.setColor(colorSelected);
        LibThree.setColor(colorBlack);
        LibTwo.setColor(colorBlack);
    }
    if (event == "enter" && cursorPosition == 1) {
        cursorLine++;
        indexLib = 1;
        LibTwo.setColor(colorSelected);
        LibOne.setColor(colorBlack);
        LibThree.setColor(colorBlack);
    }
    if (event == "enter" && cursorPosition == 2) {
        cursorLine++;
        indexLib = 2;
        LibThree.setColor(colorSelected);
        LibOne.setColor(colorBlack);
        LibTwo.setColor(colorBlack);
    }
}

void Menu::eventPseudoCursor(const std::string &event) {
    if (event == "right" && cursorPosition == 3) {
        ArrowUp.setPositionX(53);
        ArrowDown.setPositionX(53);
        cursorPosition++;
    }
    if (event == "right" && cursorPosition == 2) {
        ArrowUp.setPositionX(50);
        ArrowDown.setPositionX(50);
        cursorPosition++;
    }
    if (event == "right" && cursorPosition == 1) {
        ArrowUp.setPositionX(47);
        ArrowDown.setPositionX(47);
        cursorPosition++;
    }
    if (event == "right" && cursorPosition == 0) {
        ArrowUp.setPositionX(44);
        ArrowDown.setPositionX(44);
        cursorPosition++;
    }
    if (event == "left" && cursorPosition == 1) {
        ArrowUp.setPositionX(41);
        ArrowDown.setPositionX(41);
        cursorPosition--;
    }
    if (event == "left" && cursorPosition == 2) {
        ArrowUp.setPositionX(44);
        ArrowDown.setPositionX(44);
        cursorPosition--;
    }
    if (event == "left" && cursorPosition == 3) {
        ArrowUp.setPositionX(47);
        ArrowDown.setPositionX(47);
        cursorPosition--;
    }
    if (event == "left" && cursorPosition == 4) {
        ArrowUp.setPositionX(50);
        ArrowDown.setPositionX(50);
        cursorPosition--;
    }
}

void Menu::eventPseudoLetter(const std::string &event) {
    std::string temp = "";

    if (event == "up" && cursorPosition == 0) {
        if (letters[0] < 90) {
            letters[0]++;
            Letter1.setText(temp += letters[0]);
        }
    }
    if (event == "down" && cursorPosition == 0) {
        if (letters[0] > 65) {
            letters[0]--;
            Letter1.setText(temp += letters[0]);
        }
    }

    if (event == "up" && cursorPosition == 1) {
        if (letters[1] < 90) {
            letters[1]++;
            Letter2.setText(temp += letters[1]);
        }
    }
    if (event == "down" && cursorPosition == 1) {
        if (letters[1] > 65) {
            letters[1]--;
            Letter2.setText(temp += letters[1]);
        }
    }

    if (event == "up" && cursorPosition == 2) {
        if (letters[2] < 90) {
            letters[2]++;
            Letter3.setText(temp += letters[2]);
        }
    }
    if (event == "down" && cursorPosition == 2) {
        if (letters[2] > 65) {
            letters[2]--;
            Letter3.setText(temp += letters[2]);
        }
    }

    if (event == "up" && cursorPosition == 3) {
        if (letters[3] < 90) {
            letters[3]++;
            Letter4.setText(temp += letters[3]);
        }
    }
    if (event == "down" && cursorPosition == 3) {
        if (letters[3] > 65) {
            letters[3]--;
            Letter4.setText(temp += letters[3]);
        }
    }

    if (event == "up" && cursorPosition == 4) {
        if (letters[4] < 90) {
            letters[4]++;
            Letter5.setText(temp += letters[4]);
        }
    }
    if (event == "down" && cursorPosition == 4) {
        if (letters[4] > 65) {
            letters[4]--;
            Letter5.setText(temp += letters[4]);
        }
    }
}

void Menu::handleUpdate(int elepsedTime) {
    (void)elepsedTime;
}

void Menu::handleRender(IGraphicRenderer &renderer) const {
    renderer.clearScreen();
    if (state == PSEUDO) {
        renderer.drawText(EnterName);
        renderer.drawText(Letter1);
        renderer.drawText(Letter2);
        renderer.drawText(Letter3);
        renderer.drawText(Letter4);
        renderer.drawText(Letter5);
        renderer.drawText(ArrowUp);
        renderer.drawText(ArrowDown);
    } else if (state == MENU) {
        if (cursorLine < 3) {
            renderer.drawText(HighScore);
            renderer.drawText(Title);
            renderer.drawText(TitleGames);
            renderer.drawText(GameTwo);
            renderer.drawText(GameOne);
            renderer.drawText(TitleLib);
            renderer.drawText(LibOne);
            renderer.drawText(LibThree);
            renderer.drawText(LibTwo);
            renderer.drawText(Play);
            renderer.drawText(Helper);
            renderer.drawText(ScoreOne);
            renderer.drawText(ScoreTwo);
            renderer.drawText(ScoreThree);
            renderer.drawText(Name);
        }
    }
    renderer.drawScreen();
}

int Menu::getIndexLib() const {
    return indexLib;
}

int Menu::getIndexGame() const {
    return indexGame;
}

bool Menu::getInfoPlay() const {
    return goToGame;
}

void Menu::loadscoresSnake() {
    std::ifstream file{"save/LeaderboardSnake.txt"};
    std::vector<std::string> score;
    file >> std::noskipws;
    std::istream_iterator<char> b{file}, e{};
    std::string st;
    std::string stsave;

    if (!file.is_open()) {
        std::cerr << "No such file" << std::endl;
        exit(84);
    }
    for (; e != b; ++b)
        st += *b;
    for(size_t i = 0; st[i]; i++) {
        if (st[i] == '\n') {
            stsave += '\n';
            _scoresSnake.emplace_back(stsave);
            stsave = "";
        } else {
            stsave += st[i];
        }
    }
    file.close();
}

void Menu::loadscoresSolarfox() {
    std::ifstream file{"save/LeaderboardSolarfox.txt"};
    std::vector<std::string> score;
    file >> std::noskipws;
    std::istream_iterator<char> b{file}, e{};
    std::string st;
    std::string stsave;

    if (!file.is_open()) {
        std::cerr << "No such file" << std::endl;
        exit(84);
    }
    for (; e != b; ++b)
        st += *b;
    for(size_t i = 0; st[i]; i++) {
        if (st[i] == '\n') {
            stsave += '\n';
            _scoresSolarfox.emplace_back(stsave);
            stsave = "";
        } else {
            stsave += st[i];
        }
    }
    file.close();
}

void Menu::loadScores() {
    loadscoresSnake();
    loadscoresSolarfox();
    ScoreOne.setText(_scoresSnake.at(0).first + " : " + std::to_string(_scoresSnake.at(0).second));
    ScoreTwo.setText(_scoresSnake.at(1).first + " : " + std::to_string(_scoresSnake.at(1).second));
    ScoreThree.setText(_scoresSnake.at(2).first + " : " + std::to_string(_scoresSnake.at(2).second));
}

void Menu::saveScores() {
    std::string save;
    std::ofstream out("sts.txt");
    std::ofstream out2("sts.txt");

    for (auto& i : _scoresSnake) {
        (void)i;
        save += _scoresSnake.back();
        _scoresSnake.pop_back();
    }
    out << save;
    out.close();
    save = "";
    for (auto& i : _scoresSolarfox) {
        (void)i;
        save += _scoresSolarfox.back();
        _scoresSolarfox.pop_back();
    }
    out2 << save;
    out2.close();
}

std::vector<std::pair<std::string, int>> Menu::getScoresSolarfox() const {
    return _scoresSolarfox;
}

void Menu::setScoresSolarfox(std::vector<std::pair<std::string, int>> newScores) {
    _scoresSolarfox = newScores;
}

std::vector<std::pair<std::string, int>> Menu::getScoresSnake() const {
    return _scoresSnake;
}

void Menu::setScoresSnake(std::vector<std::pair<std::string, int>> newScores) {
    _scoresSnake = newScores;
}

void Menu::setLettersSize() {
    letters.reserve(5);
    letters[0] = 64;
    letters[1] = 64;
    letters[2] = 64;
    letters[3] = 64;
    letters[4] = 64;
    GameOne.setText(gamesNames.at(0));
    GameTwo.setText(gamesNames.at(1));
    LibOne.setText(libsNames.at(0));
    LibTwo.setText(libsNames.at(1));
    LibThree.setText(libsNames.at(2));
}

void Menu::setName() {
    for (int i = 0; i < 5; i++) {
        if (letters[i] == 64)
            letters[i] = ' ';
    }
    name += letters[0];
    name += letters[1];
    name += letters[2];
    name += letters[3];
    name += letters[4];
    cursorPosition = 0;
    cursorLine = 0;
    Name.setText(name);
}

const std::map<std::string, std::string> Menu::getGameData() {
    return std::map<std::string, std::string>();
}

void Menu::setInfoPlay(const bool info) {
    goToGame = info;
}

void Menu::resetMenu() {
    cursorPosition = 0;
    cursorLine = 0;
    indexLib = -1;
    indexGame = -1;
    state = PSEUDO;
    letters.clear();
    name.clear();
    Letter1.setText("_");
    Letter2.setText("_");
    Letter3.setText("_");
    Letter4.setText("_");
    Letter5.setText("_");
    GameOne.setColor(colorCursorSelected);
    GameTwo.setColor(colorUnselected);
    LibOne.setColor(colorUnselected);
    LibTwo.setColor(colorUnselected);
    LibThree.setColor(colorUnselected);
    Play.setColor(colorUnselected);
}
