#include "Board.h"

#include <iostream>
#include <string>
#include <Windows.h>

//#define COLORS

int main()
{
#ifdef COLORS
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    for (int k = 0; k < 16; k++)
    {
        // pick the colorattribute k you want
        SetConsoleTextAttribute(hConsole, k);
        std::cout << k << ": test\n";
    }

    std::cin.get();

#else

    Board board;
    bool blackTurn = true;

    while (true)
    {
        bool valid = false;
        while (!valid)
        {
            system("cls");
            board.Print();

            std::string turnString = blackTurn ? "black" : "white";

            std::cout << "\n" << turnString << "> ";
        
            std::string positionString;
            std::cin >> positionString;

            Position position(positionString);
            if (position.Valid())
            {
                Stone stone = blackTurn ? Stone::Black : Stone::White;
                board.Place(Position(position), stone);

                valid = true;
                blackTurn = !blackTurn;
            }
        }
    }

#endif
}