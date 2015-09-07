#pragma once

#include "Position.h"

class Board
{
public:
    Board() = default;
    ~Board() = default;

    bool Add(Position position, Stone stone, bool recordLast);
    void Remove(Position position);
    void Print() const;

    Stone GetStoneAt(Position position) const;

    Position GetLastPosition() const { return m_lastPosition; }
    void SetLastPosition(Position position);

private:
    std::map<Position, Stone> m_stones;
    Position m_lastPosition;
};