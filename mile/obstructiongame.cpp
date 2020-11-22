// ObstructionGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main()
{
    int row, column;
    string Player1_Name, Player2_Name;
    int gridID;

#pragma region Starting for the game
    cout << "Obstruction Game" << endl;
    cout << "Press Escape to exit the game" << endl;

    cout << "First Player Name : ";
    cin >> Player1_Name;

    cout << "Secon Player Name : ";
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
#pragma endregion

#pragma region Preparing the Game
    int** ptr_matrix = new int* [row];
    for (int i = 0; i < row; i++)
        ptr_matrix[i] = new int[column];

    for (int i = 0; i < column; i++)
    {
        for (int j = 0; j < row; j++)
        {
            cout << " E";
            ptr_matrix[i][j] = 0; // 0 : not filled, 1 : filled with O, 2 filled with X
        }
        cout << endl;
    }
#pragma endregion

#pragma region Game Main Logic
    int turningFlag = 0; //0 : first player, 1 : second player
    int x, y;
    while (true)
    {
        bool isEmptyCell = false;
        while (!isEmptyCell)
        {
            if (turningFlag == 0)
                cout << Player1_Name << "[x,y] : ";
            else
                cout << Player2_Name << "[x,y] : ";

            cin >> y;
            if (y == -1)
                return 0;
            cin >> x;
            if (x == -1)
                return 0;

            if (ptr_matrix[x - 1][y - 1] == 0)
            {
                break;
            }
        }

        for (int i = (x > 1 ? x - 1 : x); i <= (x <= column - 1 ? x + 1 : x); i++)
        {
            for (int j = (y > 1 ? y - 1 : y); j <= (y <= row - 1 ? y + 1 : y); j++)
            {
                if (ptr_matrix[i - 1][j - 1] == 0)
                {
                    if (turningFlag == 0)
                        ptr_matrix[i - 1][j - 1] = 1;
                    else
                        ptr_matrix[i - 1][j - 1] = 2;
                }
            }
        }

        for (int i = 0; i < column; i++)
        {
            for (int j = 0; j < row; j++)
            {
                if (ptr_matrix[i][j] == 0)
                    cout << " E";
                else if (ptr_matrix[i][j] == 1)
                    cout << " O";
                else if (ptr_matrix[i][j] == 2)
                    cout << " X";
            }
            cout << endl;
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
                cout << Player1_Name << " Win!" << endl;
            else
                cout << Player2_Name << " Win!" << endl;

            return 0;
        }

        turningFlag++;
        turningFlag %= 2;
    }
#pragma endregion
    
    delete[]  ptr_matrix;
    return 0;
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
