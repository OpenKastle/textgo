#include "Game.h"

#include <iostream>
#include <bitset>
#include <windows.h>

int main()
{
    Game game;
    game.Start();

    /*
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (unsigned int i = 0; i < 256; ++i)
    {
        SetConsoleTextAttribute(hConsole, i);
        std::cout << std::bitset<8>(i).to_string() << ": texttexttext\n";
    }
    */

    std::cin.get();
}