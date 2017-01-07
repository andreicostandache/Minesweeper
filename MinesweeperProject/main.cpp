#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstring>
#include "MinesweeperMap.h"
#include "GameStats.h"
#include "WindowsAndSurfaces.h"
#include <SDL.h>
using namespace std;

bool ok=true;
int numberOfRevealedCells=0,necessaryRevealedCells,numberOfFlags;
char option,playAgain;
bool keepPlaying=true;
clock_t t1,t2;
SDL_Surface *zero = NULL,*one = NULL,*two = NULL,*three = NULL,*four = NULL,*five = NULL,*six = NULL,*seven = NULL,*eight = NULL,*mine = NULL,*flag = NULL,*box = NULL;
SDL_Point mousePosition;
int countNeighbouringMines(MinesweeperMap &m,int i,int j)
{
    int x,y,nr=0;
    x=m.xDimension-1;
    y=m.yDimension-1;

    if(i>=1)
    {
        if(j>=1) nr+=m.grid[i-1][j-1].containsMine;
        if(j<=y-1) nr+=m.grid[i-1][j+1].containsMine;
        nr+=m.grid[i-1][j].containsMine;
    }
    if(j>=1)nr+=m.grid[i][j-1].containsMine;
    if(j<=y-1) nr+=m.grid[i][j+1].containsMine;
    if(i<=y-1)
    {
        if(j>=1)nr+=m.grid[i+1][j-1].containsMine;
        if(j<=y-1) nr+=m.grid[i+1][j+1].containsMine;
        nr+=m.grid[i+1][j].containsMine;

    }
    return nr;
}


int countNeighbouringFlags(MinesweeperMap &m,int i,int j)
{
    int x,y,nr=0;
    x=m.xDimension-1;
    y=m.yDimension-1;

    if(i>=1)
    {
        if(j>=1) nr+=m.grid[i-1][j-1].containsFlag;
        if(j<=y-1) nr+=m.grid[i-1][j+1].containsFlag;
        nr+=m.grid[i-1][j].containsFlag;
    }
    if(j>=1)nr+=m.grid[i][j-1].containsFlag;
    if(j<=y-1) nr+=m.grid[i][j+1].containsFlag;
    if(i<=y-1)
    {
        if(j>=1)nr+=m.grid[i+1][j-1].containsFlag;
        if(j<=y-1) nr+=m.grid[i+1][j+1].containsFlag;
        nr+=m.grid[i+1][j].containsFlag;

    }
    return nr;
}

void reveal(MinesweeperMap m1)
{
    int i,j;
    cout<<"Number of flags available:"<<numberOfFlags<<endl;
    cout<<"   ";
    for(j=0; j<=m1.xDimension-1; j++)
    {
        cout<<j;
        if(j<10)
            cout<<" ";
    }
    cout<<endl;
    for(i=0; i<=m1.yDimension-1; i++,cout<<endl)
    {
        cout<<i<<" ";
        if(i<10)
            cout<<" ";
        for(j=0; j<=m1.xDimension-1; j++)
        {
            cout<<'|';
            if(m1.grid[i][j].canBeRevealed==true)
            {
                if(m1.grid[i][j].containsMine==true)
                    cout<<'M';
                else
                {
                    if(m1.grid[i][j].nrOfAdjacentMines==0)
                        cout<<" ";
                    else
                        cout<<m1.grid[i][j].nrOfAdjacentMines;
                }
            }
            else if(m1.grid[i][j].containsFlag==true)
                cout<<'F';
            else
                cout<<"*";
        }
        cout<<'|';
    }


}

void open(MinesweeperMap &m,int i,int j)
{
    if(i>=0&&i<=m.yDimension-1&&j>=0&&j<=m.xDimension-1&&m.grid[i][j].canBeRevealed==false&&m.grid[i][j].containsFlag==false)
    {
        m.grid[i][j].canBeRevealed=true;
        if(m.grid[i][j].containsMine==true)
            ok=false;
        else
        {
            numberOfRevealedCells++;
            if(m.grid[i][j].nrOfAdjacentMines==0)
            {
                open(m,i+1,j+1);
                open(m,i+1,j);
                open(m,i+1,j-1);
                open(m,i,j+1);
                open(m,i,j-1);
                open(m,i-1,j+1);
                open(m,i-1,j);
                open(m,i-1,j-1);
            }
        }

    }


}
void initSurfaces()
{
    zero = SDL_LoadBMP( "images/digit0.bmp" );
    one = SDL_LoadBMP( "images/digit1.bmp" );
    two = SDL_LoadBMP( "images/digit2.bmp" );
    three = SDL_LoadBMP( "images/digit3.bmp" );
    four = SDL_LoadBMP( "images/digit4.bmp" );
    five = SDL_LoadBMP( "images/digit5.bmp" );
    six = SDL_LoadBMP( "images/digit6.bmp" );
    seven = SDL_LoadBMP( "images/digit7.bmp" );
    eight = SDL_LoadBMP( "images/digit8.bmp" );
    box=SDL_LoadBMP("images/box.bmp");
    flag = SDL_LoadBMP( "images/flag.bmp" );
    mine=SDL_LoadBMP("images/mine.bmp");
}

void draw(MinesweeperMap m,SDL_Window* &w,SDL_Surface* &s)
{
    int i,j,lines,columns;
    lines=m.yDimension;
    columns=m.xDimension;
    for(i=0; i<=lines-1; i++,cout<<endl)
    {

        for(j=0; j<=columns-1; j++)
        {

            if(m.grid[i][j].canBeRevealed==true)
            {
                if(m.grid[i][j].containsMine==true)
                    applySurface(j,i,mine,s);
                else
                {
                    if(m.grid[i][j].nrOfAdjacentMines==0)
                        applySurface(j,i,zero,s);
                    else
                    {
                        switch(m.grid[i][j].nrOfAdjacentMines)
                        {
                        case 1:
                            applySurface(j,i,one,s);
                            break;
                        case 2:
                            applySurface(j,i,two,s);
                            break;
                        case 3:
                            applySurface(j,i,three,s);
                            break;
                        case 4:
                            applySurface(j,i,four,s);
                            break;
                        case 5:
                            applySurface(j,i,five,s);
                            break;
                        case 6:
                            applySurface(j,i,six,s);
                            break;
                        case 7:
                            applySurface(j,i,seven,s);
                            break;
                        case 8:
                            applySurface(j,i,eight,s);
                            break;
                        }

                    }
                }
            }
            else if(m.grid[i][j].containsFlag==true)
                applySurface(j,i,flag,s);
            else
                applySurface(j,i,box,s);
        }
    }


    SDL_UpdateWindowSurface(w);

}
void initializeGame(MinesweeperMap &m)
{
    int lines,mines,columns;
    cout<<"Type the number of lines you want: ";
    do
    {
        cin>>lines;
    }
    while(lines<=0);
    cout<<endl;
    cout<<"Type the number of columns you want:  ";
    do
    {
        cin>>columns;
    }
    while(columns<=0);
    cout<<endl;
    cout<<"Type the number of mines you want:";
    do
    {
        cin>>mines;
    }
    while(mines>=lines*columns||mines<=0);
    cout<<endl;
    initializeMinesweeperMap(m,lines,columns,mines);
    numberOfFlags=m.nrOfMines;
    placeMines(m);
    countAdjacentMines1(m);
    reveal(m);
    necessaryRevealedCells=lines*columns-mines;
    ok=true;
    numberOfRevealedCells=0;


}

void playingUsingKeyboard(MinesweeperMap &m)
{

    char action;
    int line,column,nr;
    cout<<"Type the line,the column and the action you want; o-open the cell at (line,column);f-mark the cell at (line,column)with a flag;a-special opening"<<endl;
    do
    {
        cin>>line>>column>>action;
    }
    while(line<0||line>m.yDimension-1||column<0||column>m.xDimension||(action!='o'&&action!='f'&&action!='a'));
    if(action=='o')
    {
        open(m,line,column);


    }
    else if(action=='f')
    {
        if(m.grid[line][column].canBeRevealed==false)
        {
            if(m.grid[line][column].containsFlag==true)
            {
                numberOfFlags++;
                m.grid[line][column].containsFlag=false;
            }
            else if(numberOfFlags>0)
            {
                numberOfFlags--;
                m.grid[line][column].containsFlag=true;
            }

        }

    }
    else
    {
        if(m.grid[line][column].canBeRevealed==true)
        {
            nr=countNeighbouringFlags(m,line,column);
            if(nr==m.grid[line][column].nrOfAdjacentMines)
            {

                open(m,line+1,column+1);
                open(m,line+1,column);
                open(m,line+1,column-1);
                open(m,line,column+1);
                open(m,line,column-1);
                open(m,line-1,column+1);
                open(m,line-1,column);
                open(m,line-1,column-1);




            }

        }

    }

    system("CLS");
    reveal(m);


}



void playingUsingMouse(MinesweeperMap &m,SDL_Window* &w,SDL_Surface* &s)
{

    int line,column,nr;
    SDL_Event e;
    while(SDL_PollEvent(&e)!=0)
    {
        if(e.type==SDL_QUIT)
            ok=false;
        else if(e.type==SDL_MOUSEBUTTONDOWN)
        {
            SDL_GetMouseState(&mousePosition.x,&mousePosition.y);
            line=mousePosition.y/50;
            column=mousePosition.x/50;
            if(e.button.button==SDL_BUTTON_LEFT)
            {
                if(m.grid[line][column].canBeRevealed==false)
                    open(m,line,column);
                else
                {
                    nr=countAdjacentFlags(m,line,column);
                    if(nr==m.grid[line][column].nrOfAdjacentMines)
                    {

                        open(m,line+1,column+1);
                        open(m,line+1,column);
                        open(m,line+1,column-1);
                        open(m,line,column+1);
                        open(m,line,column-1);
                        open(m,line-1,column+1);
                        open(m,line-1,column);
                        open(m,line-1,column-1);




                    }
                }
            }
            else
            {

                if(m.grid[line][column].canBeRevealed==false)
                {
                    if(m.grid[line][column].containsFlag==true)
                    {
                        numberOfFlags++;
                        m.grid[line][column].containsFlag=false;
                    }
                    else if(numberOfFlags>0)
                    {
                        numberOfFlags--;
                        m.grid[line][column].containsFlag=true;
                    }

                }

            }
            system("CLS");
            cout<<"Left click to open a cell;if the cell is already opened ,and the number of flags adjacent to it = number of the adjacent mines,all the cells around it,which are not marked with a flag, will be opened"<<endl;
            cout<<"Right click to mark a cell with a flag(or to unmark it)"<<endl;
            reveal(m);
            draw(m,w,s);
        }

    }


}

void menu()
{
    option='b';
    cout<<"If you want to play using your keyboard,press k;if you want to play using your mouse,press m "<<endl<<"If you want to see your stats press s"<<endl;
    do
    {
        cin>>option;
    }
    while(option!='k'&&option!='s'&&option!='m');


}

void playAgainQuestion()
{
    cout<<endl;
    cout<<"Play again? y-yes ;n-no"<<endl;
    do
    {
        cin>>playAgain;
        if(playAgain=='y')
        {
            system("CLS");
            keepPlaying=true;
        }

    }
    while(playAgain!='y'&&playAgain!='n');



}

int main(int argc, char* args[])
{
    int line,column;
    char player[50];
    MinesweeperMap gameMap;
    double seconds;
    Records r[100];
    int numberOfRecords=0;
    SDL_Window *gameWindow;
    SDL_Surface *screen;
    initSurfaces();
    do
    {
mainMenu:
        menu();
        switch(option)
        {
        case 's':
            showRecords(r,numberOfRecords);
            cout<<endl;
            cout<<"Press s to return to main menu"<<endl;
            do
            {
                cin>>option;
            }
            while(option!='s');
            system("CLS");
            goto mainMenu;
            break;


        case 'k':
            initializeGame(gameMap);
            system("CLS");
            reveal(gameMap);
            t1=clock();
            do
            {
                playingUsingKeyboard(gameMap);

                if(ok==false||(numberOfRevealedCells==necessaryRevealedCells&&numberOfFlags==0))
                {
                    t2=clock();
                    seconds=(t2-t1)/(double)CLOCKS_PER_SEC;
                    cout<<endl;
                    cout<<"Type your name"<<endl;
                    cin>>player;
                    cout<<endl;
                    if(numberOfRevealedCells==necessaryRevealedCells&&numberOfFlags==0)

                    {
                        cout<<endl<<"you won";
                        setRecord(r[numberOfRecords],player,"won",seconds,gameMap.yDimension,gameMap.xDimension,gameMap.nrOfMines);
                    }
                    else
                    {
                        cout<<endl<<"you lost";
                        setRecord(r[numberOfRecords],player,"lost",seconds,gameMap.yDimension,gameMap.xDimension,gameMap.nrOfMines);
                    }
                    numberOfRecords++;
                    keepPlaying=false;
                    playAgainQuestion();
                }

            }
            while(ok==true&&(numberOfRevealedCells<necessaryRevealedCells||numberOfFlags!=0));
            break;
        case 'm':
            initializeGame(gameMap);
            clean(gameWindow,screen);
            gameWindow=initWindow(gameMap.yDimension,gameMap.xDimension);
            screen=SDL_GetWindowSurface(gameWindow);
            SDL_SetWindowInputFocus(gameWindow);
            cout<<"Left click to open a cell;if the cell is already opened ,and the number of flags adjacent to it = number of the adjacent mines,all the cells around it,which are not marked with a flag, will be opened"<<endl;
            cout<<"Right click to mark a cell with a flag(or to unmark it)"<<endl;
            draw(gameMap,gameWindow,screen);
            t1=clock();
            do
            {
                playingUsingMouse(gameMap,gameWindow,screen);
                if(ok==false||(numberOfRevealedCells==necessaryRevealedCells&&numberOfFlags==0))
                {   t2=clock();
                    seconds=(t2-t1)/(double)CLOCKS_PER_SEC;
                    SDL_HideWindow(gameWindow);
                    cout<<endl;
                    cout<<"Type your name"<<endl;
                    cin>>player;
                    cout<<endl;
                    if(numberOfRevealedCells==necessaryRevealedCells&&numberOfFlags==0)

                    {
                        cout<<endl<<"you won";
                        setRecord(r[numberOfRecords],player,"won",seconds,gameMap.yDimension,gameMap.xDimension,gameMap.nrOfMines);
                    }
                    else
                    {
                        cout<<endl<<"you lost";
                        setRecord(r[numberOfRecords],player,"lost",seconds,gameMap.yDimension,gameMap.xDimension,gameMap.nrOfMines);
                    }
                    numberOfRecords++;
                    keepPlaying=false;
                    playAgainQuestion();

                }

            }
            while(ok==true&&(numberOfRevealedCells<necessaryRevealedCells||numberOfFlags!=0));
            clean(gameWindow,screen);
            break;
        }
    }
    while(keepPlaying==true);
    showRecords(r,numberOfRecords);
    return 0;
}






