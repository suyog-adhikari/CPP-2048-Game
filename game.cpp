#include "game.h"
#include "functions.h"
#include <fstream>

#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77

const int gameOver = 16;   // Value at which the game ends

void board :: init()    // initializes the board
{
    for (int i = 0 ; i<4; i++)  // to clear the array. Useful when user attempts to play game for 2nd time.
    {
        for (int j = 0; j<4; j++)
            box[i][j] = 0;
    }

    for (int i=0;i<2;i++)       // sets random 2 positions as '2'
    {
        int j = std :: rand()%4;
        int k = std :: rand()%4;
        box[j][k] = 2 ;
    }
}

bool board :: check()   // checks if the game is over or if the user has won the game
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j<4; j++)
        {
            if (box[i][j] == gameOver)      // if the number is equal to the selected number, the user has WON the game
            {
                display();                  // Since the LOOP returns false, the box must be displayed. Else, the game ends with penultimate situation of the board gets displayed.
                gotoxy(3,20);
                std :: cout << "\t YOU WIN !! :D" << std :: endl;
                Sleep(1500);
                gotoxy(6,25);
                std :: cout << "\t\t Enter Any key To continue";
                getch();
                return false;
            }
        }
    }

    for (int i = 0; i < 4; i++)     // if user has not won and there is a 0 left in the box, game keeps running
    {
        for (int j = 0; j<4; j++)
        {
            if (box[i][j] == 0)
                return true;
        }
    }

    for (int i = 0; i < 4; i++)     // checking for same numbers in con-current positions
    {
        for (int j = 0; j<4; j++)
        {
            if (box[i][j] == box[i+1][j] || box[i][j] == box [i][j+1])
                return true;        // if there are same numbers in concurrent position, the game hasn't ended even if the box is full.
        }
    }

    display();      // Displaying box is essential before ending the game. Else, penultimate state gets displayed
    gotoxy(3,18);
    std :: cout << "GAME OVER !! :(" << std :: endl;     // if any of the above FOR loop doesn't return the value TURE, game has obviously ended.
    std :: cout << "\tYou Made it to : " <<  findMax() << std :: endl;

    Sleep(1500);
    std :: cout << "\n\n\t\t Enter Any key To continue";
    getch();
    return false;
}

void board :: add()     // add '2' to a random empty place in the board
{
    int possibility = 0;    // Since adding is implemented using implemented using infinite loop, checking possibility is essential.
                            // There might be no possibility of adding a new number in a case, where the board is full, but the game hasn't ended.

    for (int i = 0; i < 4; i++)     // checks for the possibility to add
    {
        for (int j = 0; j<4; j++)
        {
            if (box[i][j] == 0)     // if an empty space is remaining, new number can be added.
            {
                possibility = 1;
                break;
            }
        }

        if (possibility == 1)       // to eliminate unnecessary loops.
            break;
    }

    if (possibility == 0)           // if there is no-possibility to add, the function ends.
        return;

    while (1)       // Loop breaks after adding '2' to a random empty position
    {
        int j = std :: rand()%4;
        int k = std :: rand()%4;

        if (box[j][k] == 0)
            box [j][k] = 2;
        else
            continue;

        break;
    }

    clearErrorMessage();        // clears the error message that was created in case of wrong key press. (Declared under "functions.h")
}

void board :: display()     // displays the board in 4*4 form
{
    int x = 30, y = 10;

    for (int i=0; i<4;i++)
    {
        for (int j=0; j<4; j++)
        {
            gotoxy(x,y);

            if (box [i][j] != 0)
                std :: cout << " " << box [i][j] << "   ";
            else
                std :: cout << "  .  ";

            x+=5;
        }

        x=30;
        y+=1;
    }

    gotoxy(65,12);
    std :: cout << "Score : " << score;
    createBox(28,8,25,8);   // creates box around the numbers.

    std :: cout << std :: endl; // takes pointer below the box. (Removing it makes no difference)
}

int board :: findMax()
{
    int max = box[0][0];

    for (int i = 0 ; i<4; i++)  // to clear the array. Useful when user attempts to play game for 2nd time.
    {
        for (int j = 0; j<4; j++)
        {
            if (box[i][j] > max)
                max = box [i][j];
        }
    }

    return max;
}

void game :: run()      // major part of the game : Performs shifting/combining/checking of the numbers
{
    display();

    int inp;
    inp = getch();

    switch (inp)
    {
    case LEFT_KEY:
        {
            int add = 0;
            for (int i = 0 ; i<4; i++)
            {
                for (int k = 0 ; k <3 ; k++)    // Must be executed three time to completely move the numbers to the left
                {
                    for (int j = 1; j<4 ;j++)   // Checks if the numbers are addable or movable
                    {
                        if (box[i][j-1] == 0)
                        {
                            box [i][j-1] = box [i][j];  // moves the number to adjacent left position
                            box [i][j] = 0;
                        }
                        else if (box[i][j-1] == box [i][j] && add != 1)
                        {
                            add = 1;           // Performs addition only once. (E.g. Moving '2 2 2 2' gives '4 2 2 0'. If removed '8 0 0 0' will be obtained)
                            score+= box[i][j];
                            box [i][j-1]*=2;
                            box [i][j] = 0;
                        }
                        else
                            continue;
                    }
                }
                add = 0;
            }

            break;
        }

        case RIGHT_KEY:
            {
                int add = 0;
                for (int i = 0 ; i<4; i++)      // similar algorithm to that of LEFT_KEY
                {
                    for (int k = 0 ; k <3 ; k++)
                    {
                        for (int j = 3; j>0 ;j--)
                        {
                            if (box[i][j] == 0)
                            {
                                box [i][j] = box [i][j-1];
                                box [i][j-1] = 0;
                            }
                            else if (box[i][j] == box [i][j-1] && add != 1)
                            {
                                add = 1;
                                score+= box[i][j];
                                box [i][j]*=2;
                                box [i][j-1] = 0;
                            }
                            else
                                continue;
                        }
                    }
                    add = 0;
                }

            break;
        }

        case UP_KEY:
            {
                int add = 0;
            for (int j = 0 ; j<4; j++)      // similar algorithm to that of LEFT_KEY
            {
                for (int k = 0 ; k <3 ; k++)
                {
                    for (int i = 1; i<4 ;i++)
                    {
                        if (box[i-1][j] == 0)
                        {
                            box [i-1][j] = box [i][j];
                            box [i][j] = 0;
                        }
                        else if (box[i][j] == box [i-1][j] && add != 1)
                        {
                            add = 1;
                            score+= box[i][j];
                            box [i-1][j]*=2;
                            box [i][j] = 0;
                        }
                        else
                            continue;
                    }
                }
                add = 0;
            }

            break;
        }

        case DOWN_KEY:
            {
                int add = 0;
                for (int j = 0 ; j<4; j++)      // similar algorithm to that of LEFT_KEY
                {
                    for (int k = 0 ; k <3 ; k++)
                    {
                        for (int i = 3; i>0 ;i--)
                        {
                            if (box[i][j] == 0)
                            {
                                box [i][j] = box [i-1][j];
                                box [i-1][j] = 0;
                            }
                            else if (box[i][j] == box [i-1][j] && add != 1)
                            {
                                add = 1;
                                score+= box[i][j];
                                box [i][j]*=2;
                                box [i-1][j] = 0;
                            }
                            else
                                continue;
                        }
                    }
                    add = 0;
                }
            break;
        }

        case 27:
            clearErrorMessage();
            gotoxy(3,20);
            std :: cout << "Exiting Game...." << std :: endl;
            Sleep(1500);
            gameRunning = false;
            return;

        case 224:   // 224 is an exception, since getch() takes 224 before the ASCII of Arrow Keys
            return;

        default:        // in case of any other numbers except for the desired keys, exception is thrown
            throw (inp);
            break;
        }

    add();
}

void game :: mainMenu()     // starting menu of the game. Guides user to three different options
{
    system("CLS");
    createBox(20,1,20,5);
    gotoxy(25,3);
    std :: cout << "Main Menu";

    gotoxy(10,8);
    std :: cout << "Play Game";
    gotoxy(10,10);
    std :: cout << "How to Play?";
    gotoxy(10,12);
    std :: cout << "Quit Game";

    mainMenuChoise = arrow(3,3,8,2);        // arrow function (defined under "functions.h") return the value of the available main menu options
}

void game :: runGame()
{
    system("CLS");

    createBox(20,1,20,5);                    // This Section of code was originally written under 'game :: display()'
    gotoxy(25,3);                            // It is transfered into this section to reduce frequent blinking of the screen.
    std :: cout << gameOver << " Game";      // Blinking occurred during each update of the game box.

    init();
    gameRunning = true;    // Since running game has started.
    score = 0;

    while (gameRunning)
    {
        try
        {
            run();
        }
        catch (int e)      // exception message
        {
            gotoxy(3,20);
            std :: cout << "Error : Unrecognized command !! \n\t Use arrow Keys to play the Game" << std :: endl;
        }

        if (gameRunning == false)       // checks if user has pressed 'ESC' and ends game.
            break;

        gameRunning = check();
    }
}

void game :: aboutGame()        // about section of the game. Displays general information about the game
{
    system("CLS");
    createBox(20,1,20,5);
    gotoxy(25,3);
    std :: cout << "About Game";

    gotoxy(3,9);
    std :: cout << gameOver << " is a single-player console game. \n   The objective of the game is to slide numbers and combine them to get number " << gameOver << std :: endl;
    gotoxy(3,13);
    std :: cout << "How to play?" << std :: endl;
    std :: cout << "  --------------" << std :: endl;
    std :: cout << "\n   Use your arrow keys to combine the numbers. \n   Use 'ESC' key at anytime to stop playing and return back to the main menu" << std :: endl;

    gotoxy(8,22);
    std :: cout << "-----------------------------";
    gotoxy(10,23);
    std :: cout << "Enter Any Key to Continue";
    getch();
}

void game :: quitGame()     // algorithm to quit the game. Takes 5 seconds to quit the game
{
    system("CLS");
    createBox(20,1,22,5);
    gotoxy(24,3);
    std :: cout << "Programmed By:";

    gotoxy(8,8);
    std :: cout << "------------------------------------------";
    gotoxy(10,10);
    std :: cout << "Suyog Adhikari";
    gotoxy(10,11);
    std :: cout << "Instagram: suyog.adhikari";
    gotoxy(10,12);
    std :: cout << "Mail: suyog.adhikari058@gmail.com";
    gotoxy(10,13);
    std :: cout << "Github: suyog-adhikari";
    gotoxy(8,15);
    std :: cout << "------------------------------------------";

    for (int i=5;i>0;i--)       // Displays the timer
    {
        gotoxy(5,20);
        std :: cout << "\t Exiting Automatically in : " << i << " Seconds";
        Sleep(1000);
    }
}
