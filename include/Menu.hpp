//
// Created by chaoticks on 01/04/2020.
//

#ifndef OOP_ARCADE_2019_MENU_HPP
#define OOP_ARCADE_2019_MENU_HPP

#include <vector>
#include <iostream>
#include <iterator>
#include <fstream>
#include <iostream>
#include <cstring>
#include "interface/IGame.hpp"

#define PSEUDO -1
#define MENU 0

class Menu : public IGame {
public:
    ~Menu() override = default;

    void handleEvent(const std::string &name) override;
    void handleUpdate(int elepsedTime) override;
    void handleRender(IGraphicRenderer &renderer) const override;

    int getIndexLib() const;
    int getIndexGame() const;
    bool getInfoPlay() const;

    std::vector<std::string> getScoresSolarfox() const;
    void setScoresSolarfox(std::vector<std::string> newScores);
    std::vector<std::string> getScoresSnake() const;
    void setScoresSnake(std::vector<std::string> newScores);

    void setLettersSize();

    const std::map<std::string, std::string> getGameData() override;

    void loadscoresSolarfox();
    void loadscoresSnake();
    void loadScores();
    void saveScores();

    std::vector<std::string> libsNames;
    std::vector<std::string> gamesNames;

private:
    Color colorBlack = Color(0, 0, 0, 255);
    Color colorCursorSelected = Color(255, 125, 0, 255);
    Color colorSelected = Color(0, 255, 0, 255);
    Color colorUnselected = Color(255, 255, 255, 255);
    Color colorHelper = Color(255, 0, 255, 255);

    Text Name = Text("", Vector2f(2, 2), Vector2f(5, 5), colorUnselected);

    Text Title = Text("   Arcade   ", Vector2f(40, 10), Vector2f(5, 5), colorUnselected);

    Text TitleGames = Text(" Games: ", Vector2f(2, 30), Vector2f(5, 5), colorUnselected);
    Text GameOne = Text(" Snake ", Vector2f(25, 30), Vector2f(5, 5), colorCursorSelected);
    Text GameTwo = Text(" SolarFox ", Vector2f(45, 30), Vector2f(5, 5), colorUnselected);

    Text HighScore = Text(" Highscore ", Vector2f(75, 18), Vector2f(5, 5), colorUnselected);
    Text ScoreOne = Text("", Vector2f(70, 26), Vector2f(5, 5), colorUnselected);
    Text ScoreTwo = Text("", Vector2f(70, 30), Vector2f(5, 5), colorUnselected);
    Text ScoreThree = Text("", Vector2f(70, 34), Vector2f(5, 5), colorUnselected);

    Text TitleLib = Text(" Libs: ", Vector2f(2, 55), Vector2f(5, 5), colorUnselected);
    Text LibOne = Text(" LibCaca ", Vector2f(25, 55), Vector2f(5, 5), colorUnselected);
    Text LibTwo = Text(" NCurses ", Vector2f(45, 55), Vector2f(5, 5), colorUnselected);
    Text LibThree = Text(" Sfml ", Vector2f(65, 55), Vector2f(5, 5), colorUnselected);

    Text Play = Text(" Play ", Vector2f(44, 80), Vector2f(5, 5), colorUnselected);

    Text Helper = Text("'Left arrow' / 'Q' = Left    'Right arrow' / 'D' = Right    'Enter' = Select", Vector2f(0, 93), Vector2f(5, 5), colorHelper);

    void eventLineOne(const std::string &event);
    void eventLineTwo(const std::string &event);

    Text EnterName = Text(" Select your name ", Vector2f(32, 28), Vector2f(5, 5), colorUnselected);
    Text Letter1 = Text("_", Vector2f(40, 50), Vector2f(5, 5), colorUnselected);
    Text Letter2 = Text("_", Vector2f(43, 50), Vector2f(5, 5), colorUnselected);
    Text Letter3 = Text("_", Vector2f(46, 50), Vector2f(5, 5), colorUnselected);
    Text Letter4 = Text("_", Vector2f(49, 50), Vector2f(5, 5), colorUnselected);
    Text Letter5 = Text("_", Vector2f(52, 50), Vector2f(5, 5), colorUnselected);

    Text ArrowUp = Text("I", Vector2f(41, 42), Vector2f(5, 5), colorUnselected);
    Text ArrowDown = Text("I", Vector2f(41, 58), Vector2f(5, 5), colorUnselected);


    int cursorPosition = 0;
    int cursorLine = 0;

    int indexLib = -1;
    int indexGame = -1;

    bool goToGame = false;

    std::vector<std::string> _scoresSolarfox;
    std::vector<std::string> _scoresSnake;

    int state = PSEUDO;

    void eventPseudoCursor(const std::string &event);
    void eventPseudoLetter(const std::string &event);

    void setName();

    std::vector<int> letters;
    std::string name;
};


#endif //OOP_ARCADE_2019_MENU_HPP
