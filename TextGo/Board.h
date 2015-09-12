#pragma once

#include "Position.h"

#include "ColorSchemes.h"

#include <memory>
#include <map>

class Board
{
public:
    Board();
    Board(std::unique_ptr<ColorScheme> colorScheme);
    Board(const Board& other);
    Board& operator=(const Board& other);
    ~Board() = default;

    bool Add(Position position, Stone stone);
    void Remove(Position position);
    void Print() const;

    Stone GetStoneAt(Position position) const;

    Position GetLastPosition() const { return m_lastPosition; }
    void SetLastPosition(Position position);

    void AddCapturedStones(Stone color, unsigned int captures);
    void SubtractCapturedStones(Stone color, unsigned int captures);

    bool operator==(const Board& other) const;

private:
    unsigned int GetStoneStringPosition(Position position) const;
    std::map<unsigned int, WORD> GetBoardTextSections() const;

    std::map<Position, Stone> m_stones;
    Position m_lastPosition;

    unsigned int m_capturedBlackStones = 0;
    unsigned int m_capturedWhiteStones = 0;

    std::unique_ptr<ColorScheme> m_colorScheme;
};