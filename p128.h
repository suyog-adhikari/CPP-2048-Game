#ifndef P128_H_INCLUDED
#define P128_H_INCLUDED

#include "game.h"

class p128 : public game
{
public:
    void runProgram()
    {
        mn:
        mainMenu();

        switch (mainMenuChoise)
        {
        case 1:
            system("CLS");
            runGame();
            goto mn;
            break;
        case 2:
            aboutGame();
            goto mn;
            break;
        case 3:
            quitGame();
            break;
        }
    }
};
#endif // P128_H_INCLUDED
