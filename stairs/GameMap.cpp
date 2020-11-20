#include <curses.h>
#include <string>
#include <cstdlib>

#define PLAYER '@'
#define WALL 'W'
#define OPPONENT 'O'
#define E_TRACE ' '

using namespace std;

// struct Player;
int is_move_okay(int,int);
void setOutLine();
void setBlock(int,int);
// 
struct Block
{
    static const int mb_row,mb_col;
    void appear(const int & move_row,const int & move_col)
    {
        mvaddstr(move_row,move_col,"|####|");
    }
};
// 
void settingGameMap()
{
    WINDOW * w;
    w = initscr();//term 변수 통해 단말기 종류 결정
    curs_set(0);
    // start main
    keypad(stdscr,TRUE);
    timeout(30);
    // int row = LINES-1,col = COLS-COLS,move_row = 0,move_col=0;
    int bt_row = LINES-1 , left_col = COLS/3 , right_col = COLS-COLS/3 , center_col = COLS/2; 
    int row = bt_row-1,col = center_col+5;
    // 
    setOutLine();//테두리
    // setBlock(bt_row-1,center_col);//블럭 쌓기
    // 
    int inc_row = bt_row-1,inc_col = center_col,switch_col=-5,random;
    // 처음 시작 계단
    mvaddstr(inc_row,inc_col,"|####|");
    // 
    int ch = 'y';
    while ((ch!='q')&&(ch='Q'))
    {
        random = rand()%8;
        for (int j = 0; j < random; j++)
        {
            if(inc_col>COLS/3-10&&inc_col<COLS-COLS/3+10)
            {
                inc_row = inc_row-1;
                inc_col = inc_col+switch_col;
                mvaddstr(inc_row,inc_col,"|####|");
            }
        }
        if(switch_col==-5){switch_col = 5;}
        else{switch_col=-5;}
        random = rand()%8;
        mvaddstr(row,col,"@(YH)");
        ch = getch();
        switch (ch)
        {
            case KEY_UP:    
                if(is_move_okay(row-1,col)) row -= 1; break;
            case KEY_DOWN:  
                if(is_move_okay(row+1,col)) row += 1; break;
            case KEY_LEFT:  
                if(is_move_okay(row,col-1)) row -= 1 , col += 5; break;
            case KEY_RIGHT: 
                if(is_move_okay(row,col+1))
                {
                    row -= 1 , col -= 5; 
                    // mvaddch(row,col-1,E_TRACE);
                    break;
                } 
                
        }
    }
    endwin();//모든 자원 반납
}
// 
int is_move_okay(int row,int col)
{
    int campare_ch = mvinch(row,col);
    return !(campare_ch==OPPONENT||campare_ch==WALL);
}
// 
void setOutLine()
{
    for (int i = 0; i < LINES; i++)
    {
        for (int j = COLS/3; j < COLS-COLS/3; j++)
        {
            if (i==0||i==LINES-1)
            {
                mvaddch(i,j,'*');   
            }
            else  if (i%2==0&&(j==COLS/3||j==(COLS-COLS/3)-1))
            {
                mvaddch(i,j,'*');   
            }
        }
    }
}
// void setBlock(int move_row,int move_col)
// {
//     // 
//     int inc_row = move_row,inc_col = move_col,switch_col=-5,random = rand()%8;
//     // 처음 시작 계단
//     mvaddstr(move_row,move_col,"|####|");
//     for (int i = 0; i < 10; i++)
//     {        
//         for (int j = 0; j < random; j++)
//         {
//             if(inc_col>COLS/3-5&&inc_col<COLS-COLS/3+5)
//             {
//                 inc_row = inc_row-1;
//                 inc_col = inc_col+switch_col;
//                 mvaddstr(inc_row,inc_col,"|####|");
//             }
//         }
//         if(switch_col==-5){switch_col = 5;}
//         else{switch_col=-5;}
//         random = rand()%6;
//     }
// }
