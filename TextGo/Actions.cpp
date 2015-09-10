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
}

void AddAction::Revert(Board& board)
{
    board.Remove(m_position);
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

LastStoneChange::LastStoneChange(Position oldPosition, Position newPosition)
    : m_oldPosition(oldPosition),
      m_newPosition(newPosition)
{
}

void LastStoneChange::Apply(Board& board)
{
    board.SetLastPosition(m_newPosition);
}

void LastStoneChange::Revert(Board& board)
{
    board.SetLastPosition(m_oldPosition);
}