#pragma once

#include "Position.h"

class Board
{
public:
    Board() = default;
    ~Board() = default;

    bool Place(Position position, Stone stone);
    void Print() const;
    Stone GetStoneAt(Position position) const;

private:
    std::map<Position, Stone> m_stones;
    Position m_lastPlace;
};