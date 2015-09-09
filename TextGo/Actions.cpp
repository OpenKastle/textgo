#include "Actions.h"

#include "Board.h"

void CompositeAction::AddAction(std::unique_ptr<AbstractAction> action)
{
    m_actions.push_back(std::move(action));
}

void CompositeAction::Apply(Board& board)
{
    for (std::unique_ptr<AbstractAction>& action : m_actions)
    {
        action->Apply(board);
    }
}

void CompositeAction::Revert(Board& board)
{
    for (std::unique_ptr<AbstractAction>& action : m_actions)
    {
        action->Revert(board);
    }
}

AddAction::AddAction(Position position, Stone stone, Position previousLastPosition)
    : m_position(position),
      m_stone(stone),
      m_previousLastPosition(previousLastPosition)
{
}

void AddAction::Apply(Board& board)
{
    board.Add(m_position, m_stone, true);
    board.SetLastPosition(m_position);
}

void AddAction::Revert(Board& board)
{
    board.Remove(m_position);
    board.SetLastPosition(m_previousLastPosition);
}

RemoveAction::RemoveAction(Position position, Stone stone)
    : m_position(position),
      m_stone(stone)
{
}

void RemoveAction::Apply(Board& board)
{
    board.Remove(m_position);
}

void RemoveAction::Revert(Board& board)
{
    board.Add(m_position, m_stone, false);
}