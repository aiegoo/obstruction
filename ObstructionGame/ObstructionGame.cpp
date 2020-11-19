// ObstructionGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

//Row and column for the game board
int row, column;

//Name of 2 users who are playing the game
string Player1_Name, Player2_Name;

//Grid ID : 
int gridID;
int** ptr_matrix;

void gotoXY(int, int);
void gotoXY(int, int, string);
string getXYStr(int, int);


COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

void InitGame()
{
#pragma region Starting for the game
    cout << "Obstruction Game" << endl;

    cout << "Press Escape to exit the game" << endl;

    cout << "First Player Name : ";
    cin >> Player1_Name;

    cout << "Second Player Name : ";
    cin >> Player2_Name;

    cout << "1:6*5 , 2:6*6 , 3:7*6 , 4:8*7 , 5:8*8\n please input grid id to start to play : ";
    cin >> gridID;

    switch (gridID)
    {
    case 1:
        row = 6;    column = 5;
        break;
    case 2:
        row = 6;    column = 6;
        break;
    case 3:
        row = 7;    column = 6;
        break;
    case 4:
        row = 8;    column = 7;
        break;
    case 5:
        row = 8;    column = 8;
        break;
    default:
        row = 6;    column = 5;
        break;
    }

    cout << "--------Game Rule----------" << endl;
    cout << "1. When start the game, 'o' should be inputed for player 1." << endl;
    cout << "2. After that, players can move the cursor with arrow key and input 'x' and 'o' on his turn." << endl;
    cout << "3. When all the Empty fields are filled, then the game is over with one player's win." << endl;
    cout << "4. 'E' is empty filed, 'O' is player 1 field, 'X' is player 2 field." << endl;
    cout << "---------------------------" << endl;
#pragma endregion

#pragma region Preparing the Game
    ptr_matrix = new int* [row];
    for (int i = 0; i < row; i++)
        ptr_matrix[i] = new int[column];

    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < row; j++)
        {
            ptr_matrix[i][j] = 0; // 0 : not filled, 1 : filled with O, 2 filled with X
        }
    }
#pragma endregion
}

int main()
{
    InitGame();

    CursorPosition = GetConsoleCursorPosition(console);

    int minX, maxX, minY, maxY;
    minX = CursorPosition.X;    maxX = CursorPosition.X + 3 * row - 1;
    minY = CursorPosition.Y;    maxY = CursorPosition.Y + column - 1;

    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < row; j++)
        {
            cout << "  E";
        }
        cout << endl;
    }

    gotoXY(CursorPosition.X, CursorPosition.Y);

    int c = 0;
    int turningFlag = 0; //0 : first player, 1 : second player
    while (1)
    {
        c = _getch();
        
        if (c == KEY_UP)
        {
            if (CursorPosition.Y > minY)
            {
                gotoXY(CursorPosition.X, CursorPosition.Y - 1);
            }
        }
        else if (c == KEY_DOWN)
        {
            if (CursorPosition.Y < maxY)
            {
                gotoXY(CursorPosition.X, CursorPosition.Y + 1);
            }
        }
        else if (c == KEY_LEFT)
        {
            if (CursorPosition.X > minX)
            {
                gotoXY(CursorPosition.X - 1, CursorPosition.Y);
            }
        }
        else if (c == KEY_RIGHT)
        {
            if (CursorPosition.X < maxX)
            {
                gotoXY(CursorPosition.X + 1, CursorPosition.Y);
            }
        }
        else
        {
            //Check if User click O or X for the players turn.
            if ((c == 120 && turningFlag == 1) || (c == 111 && turningFlag == 0))
            {
                int x, y;
                x = (CursorPosition.X - minX + 1) / 3;
                y = CursorPosition.Y - minY + 1;
                if (ptr_matrix[x - 1][y - 1] == 0)
                {
                    for (int i = (x > 1 ? x - 1 : x); i <= (x <= column - 1 ? x + 1 : x); i++)
                    {
                        for (int j = (y > 1 ? y - 1 : y); j <= (y <= row - 1 ? y + 1 : y); j++)
                        {
                            if (ptr_matrix[i - 1][j - 1] == 0)
                            {
                                if (turningFlag == 0)
                                {
                                    ptr_matrix[i - 1][j - 1] = 1;
                                    gotoXY(minX + i * 3 - 1, minY + (j - 1), "O");
                                }
                                else
                                {
                                    ptr_matrix[i - 1][j - 1] = 2;
                                    gotoXY(minX + i * 3 - 1, minY + (j - 1), "X");
                                }
                            }
                        }
                    }

                    bool endFlag = true;
                    for (int i = 0; i < column; i++)
                    {
                        for (int j = 0; j < row; j++)
                        {
                            if (ptr_matrix[i][j] == 0)
                            {
                                endFlag = false;
                                break;
                            }
                        }

                        if (endFlag == false)
                            break;
                    }

                    if (endFlag)
                    {
                        if (turningFlag == 0)
                        {
                            gotoXY(0, maxY + 1, Player1_Name + " Win!");
                        }
                        else
                            gotoXY(0, maxY + 1, Player2_Name + " Win!");

                        cout << endl << "Game Finished!" << endl;
                        
                        break;
                    }

                    turningFlag++;
                    turningFlag %= 2;
                }
            }
        }
    }
    
    delete[]  ptr_matrix;
    return 0;
}

void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void gotoXY(int x, int y, string text)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
    cout << text;
}

string getXYStr(int x, int y)
{
    string returnStr;
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
    cin >> returnStr;
    return returnStr;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
