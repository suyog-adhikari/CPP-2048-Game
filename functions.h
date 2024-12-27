#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <ctime>

COORD coord = {0, 0};           //Sets co-ordinates to (0,0)
COORD max_res,cursor_size;

void gotoxy (int x, int y){         //Function for changing output display co-ordinates
        coord.X = x; coord.Y = y;   // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); //points cursor to the given X & Y coordinate
}

void createBox(int xpos,int ypos,int xsize,int ysize){      // creates a solid box based on parameters
    int x = xpos , y = ypos;

    gotoxy(xpos,ypos);

    for(int i=1;i<=ysize;i++){
        for (int j=1;j<=xsize;j++){
            if (i==1 || i==ysize)
                std :: cout << "\xdb";
            else{
                if(j==1 || j==2 || j==xsize-1 || j==xsize)
                    std :: cout << "\xdb";
                else
                    gotoxy(xpos+xsize-2,y);
            }
        }
        y++;
        x = xpos;
        gotoxy(x,y);
    }
}

int arrow (int max_size,int xpos, int ypos,int diffy){      //creates arrow like display that helps user choose options in main menu
    int value = 1;
    int keypress;
    int x = xpos, y = ypos;

    while (1){
        gotoxy(x,y);
        std :: cout << "\xDB\xDB\xDB\xB2\xB2";

        keypress = getch();

        switch (keypress){
        case 72:{       // Handling for UP KEY press
            if (value == 1)
                break;
            else
                value--;

            gotoxy(x,y);
            std :: cout << "     ";

            y-=diffy;

            break;
        }

        case 80:{    // Handling for DOWN KEY press
            if (value == max_size)
                break;
            else
                value++;

            gotoxy(x,y);        // Clears the arrow that was printed in previous position
            std :: cout << "     ";

            y+=diffy;

            break;
        }
        case 8:                     // clearing screen in case of BACKSPACE
            system("cls");
            return 0;
            break;

        case 13:                    // returns the current position of the cursor in case of user presses ENTER key
            return value;
            break;
        }
    }
}

void clearErrorMessage(){            //Clears the exception message that was generated in case of undesired key press.
    gotoxy(3,20);
    for (int i=0;i<240;i++)
        std :: cout << " ";
}
#endif // FUNCTIONS_H_INCLUDED
