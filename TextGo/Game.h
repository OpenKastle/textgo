#pragma once

#include "Board.h"
#include "Actions.h"

#include <vector>
#include <memory>

class AbstractAction;

enum class Handicap
{
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine
};

class Game
{
public:
    Game();
    Game(Handicap handicap);
    ~Game() = default;

    void Start();

private:
    void AddHistory(std::unique_ptr<AbstractAction> action);

    Board m_board;
    Stone m_turn = Stone::Black;
    
    std::string m_failureCondition;

    std::vector<std::unique_ptr<AbstractAction>> m_history;
    unsigned int m_historyIndex = 0;
};