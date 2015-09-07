#include "Game.h"

#include <iostream>
#include <string>
#include <Windows.h>

Game::Game()
    : m_board(std::make_unique<RealisticColorScheme>())
{
}

Game::Game(Handicap handicap)
    : Game()
{
    if (handicap == Handicap::Two)
    {
        m_board.Add(Position("d4"),  Stone::Black, false);
        m_board.Add(Position("q16"), Stone::Black, false);
    }
    else if (handicap == Handicap::Three)
    {
        m_board.Add(Position("d4"),  Stone::Black, false);
        m_board.Add(Position("q16"), Stone::Black, false);
        m_board.Add(Position("q4"),  Stone::Black, false);
    }
    else if (handicap == Handicap::Four)
    {
        m_board.Add(Position("d4"),  Stone::Black, false);
        m_board.Add(Position("q16"), Stone::Black, false);
        m_board.Add(Position("q4"),  Stone::Black, false);
        m_board.Add(Position("d16"), Stone::Black, false);
    }
    else if (handicap == Handicap::Five)
    {
        m_board.Add(Position("d4"),  Stone::Black, false);
        m_board.Add(Position("q16"), Stone::Black, false);
        m_board.Add(Position("q4"),  Stone::Black, false);
        m_board.Add(Position("d16"), Stone::Black, false);
        m_board.Add(Position("k10"), Stone::Black, false);
    }
    else if (handicap == Handicap::Six)
    {
        m_board.Add(Position("d4"),  Stone::Black, false);
        m_board.Add(Position("q16"), Stone::Black, false);
        m_board.Add(Position("q4"),  Stone::Black, false);
        m_board.Add(Position("d16"), Stone::Black, false);
        m_board.Add(Position("d10"), Stone::Black, false);
        m_board.Add(Position("q10"), Stone::Black, false);
    }
    else if (handicap == Handicap::Seven)
    {
        m_board.Add(Position("d4"),  Stone::Black, false);
        m_board.Add(Position("q16"), Stone::Black, false);
        m_board.Add(Position("q4"),  Stone::Black, false);
        m_board.Add(Position("d16"), Stone::Black, false);
        m_board.Add(Position("d10"), Stone::Black, false);
        m_board.Add(Position("q10"), Stone::Black, false);
        m_board.Add(Position("k10"), Stone::Black, false);
    }
    else if (handicap == Handicap::Eight)
    {
        m_board.Add(Position("d4"),  Stone::Black, false);
        m_board.Add(Position("q16"), Stone::Black, false);
        m_board.Add(Position("q4"),  Stone::Black, false);
        m_board.Add(Position("d16"), Stone::Black, false);
        m_board.Add(Position("d10"), Stone::Black, false);
        m_board.Add(Position("q10"), Stone::Black, false);
        m_board.Add(Position("k4"),  Stone::Black, false);
        m_board.Add(Position("k16"), Stone::Black, false);
    }
    else if (handicap == Handicap::Nine)
    {
        m_board.Add(Position("d4"),  Stone::Black, false);
        m_board.Add(Position("q16"), Stone::Black, false);
        m_board.Add(Position("q4"),  Stone::Black, false);
        m_board.Add(Position("d16"), Stone::Black, false);
        m_board.Add(Position("d10"), Stone::Black, false);
        m_board.Add(Position("q10"), Stone::Black, false);
        m_board.Add(Position("k4"),  Stone::Black, false);
        m_board.Add(Position("k16"), Stone::Black, false);
        m_board.Add(Position("k10"), Stone::Black, false);
    }

    m_turn = Stone::White;
}

void Game::Start()
{
    while (true)
    {
        bool valid = false;
        while (!valid)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            WORD savedAttributes;

            GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
            savedAttributes = consoleInfo.wAttributes;

            system("cls");
            m_board.Print();

            std::string turnString = (m_turn == Stone::Black) ? "black" : "white";

            SetConsoleTextAttribute(hConsole, savedAttributes);
            std::cout << "\n" << turnString << "> ";
        
            std::string input;
            std::cin >> input;

            if (input == "undo")
            {
                if (m_historyIndex > 0)
                {
                    m_history[--m_historyIndex]->Revert(m_board);
                    m_turn = (m_turn == Stone::Black) ? Stone::White : Stone::Black;
                }
            }
            else if (input == "redo")
            {
                if (m_historyIndex != m_history.size())
                {
                    m_history[m_historyIndex++]->Apply(m_board);
                    m_turn = (m_turn == Stone::Black) ? Stone::White : Stone::Black;
                }
            }
            else if (input == "quit")
            {
                system("cls");
                exit(0);
            }
            else
            {
                Position position(input);
                if (position.Valid())
                {
                    Stone stone = (m_turn == Stone::Black) ? Stone::Black : Stone::White;
                    Position previousLastPosition = m_board.GetLastPosition();
                
                    Board boardCopy = m_board;
                
                    // TODO: Add additional failure conditions (ko, suicide)
                    if (boardCopy.Add(Position(position), stone, true))
                    {
                        valid = true;
                        m_turn = (m_turn == Stone::Black) ? Stone::White : Stone::Black;

                        m_board = boardCopy;
                    
                        auto iter = begin(m_history);
                        std::advance(iter, m_historyIndex);
                        m_history.erase(iter, end(m_history));

                        m_history.push_back(std::make_unique<AddAction>(position, stone, previousLastPosition));
                        ++m_historyIndex;
                    }
                }
            }
        }
    }
}