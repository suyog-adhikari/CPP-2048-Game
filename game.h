#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <iostream>
#include <conio.h>

class board{
    protected:
        int box [4][4];
        int input;
        int score;
    public:
        void init();
        void display();
        bool check();
        void add();
        int findMax();
        virtual void run() = 0;
};

class game : public board{
    private:
        bool gameRunning;
    protected:
        int mainMenuChoise;
    public:
        void mainMenu();
        void runGame();
        void aboutGame();
        void quitGame();
        void run();
};

#endif // GAME_H_INCLUDED
