#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstring>
#include "MinesweeperMap.h"
#include "GameStats.h"
#include "WindowsAndSurfaces.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>
using namespace std;

bool ok=true;
unsigned int numberOfRevealedCells=0,necessaryRevealedCells,numberOfFlags;
char option,playAgain;
bool keepPlaying=true,firstMove=true;
SDL_Surface *zero = NULL,*one = NULL,*two = NULL,*three = NULL,*four = NULL,*five = NULL,*six = NULL,*seven = NULL,*eight = NULL,*mine = NULL,*flag = NULL,*box = NULL;

void reveal(MinesweeperMap m1)
{
    unsigned int i,j;
    cout<<"Number of flags available:"<<numberOfFlags<<endl;
    cout<<"   ";
    for(j=0; j<=m1.xDimension-1; j++)
    {
        cout<<"  "<<j<<"";
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
            cout<<"|";
            if(m1.grid[i][j].canBeRevealed==true)
            {
                if(m1.grid[i][j].containsMine==true)
                    cout<<" M ";
                else
                {
                    if(m1.grid[i][j].nrOfAdjacentMines==0)
                        cout<<"   ";
                    else
                        cout<<" "<<m1.grid[i][j].nrOfAdjacentMines<<" ";
                }
            }
            else if(m1.grid[i][j].containsFlag==true)
                cout<<" F ";
            else
                cout<<" * ";
        }
        cout<<"|";
    }


}

void open(MinesweeperMap &m,unsigned int i,unsigned int j)
{
    if(i>=0&&i<=m.yDimension-1&&j>=0&&j<=m.xDimension-1&&m.grid[i][j].canBeRevealed==false&&m.grid[i][j].containsFlag==false)
    {
        m.grid[i][j].canBeRevealed=true;
        if(m.grid[i][j].containsMine==true)
        {
            if(firstMove==true)
            {
                unsigned int a,b;
                bool changedMinePlace=false;
                srand(time(NULL));
                while(changedMinePlace==false)
                {
                    a=rand()%m.yDimension;
                    b=rand()%m.xDimension;
                    if(m.grid[a][b].containsMine==false&&(a!=i||b!=j))
                    {
                        m.grid[a][b].containsMine=true;
                        changedMinePlace=true;
                        m.grid[i][j].containsMine=false;
                        countAdjacentMines1(m);
                    }
                }
                numberOfRevealedCells++;
            }
            else
                ok=false;

        }
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
        firstMove=false;
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
    unsigned int i,j,lines,columns;
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
void initializeGame(MinesweeperMap &m,char wayOfPlaying)
{
    int lines,mines,columns;
    if(wayOfPlaying=='m')
    {
        cout<<"Type the number of lines you want(minimum 3,maximum 15): ";
        do
        {
            cin>>lines;
        }
        while(lines<=2||lines>=16);
        cout<<endl;
        cout<<"Type the number of columns you want(minimum 3,maximum 30):  ";
        do
        {
            cin>>columns;
        }
        while(columns<=2||columns>=31);
        cout<<endl;
        cout<<"Type the number of mines you want;it must be   >2  and  <(lines*columns-1):";
        do
        {
            cin>>mines;
        }
        while(mines>=lines*columns-1||mines<=2);
        cout<<endl;
    }
    else
    {
        cout<<"Type the number of lines you want(minimum 3,maximum 100): ";
        do
        {
            cin>>lines;
        }
        while(lines<=2||lines>=101);
        cout<<endl;
        cout<<"Type the number of columns you want(minimum 3,maximum 25):  ";
        do
        {
            cin>>columns;
        }
        while(columns<=2||columns>=26);
        cout<<endl;
        cout<<"Type the number of mines you want;it must be   >2  and  <(lines*columns-1):";
        do
        {
            cin>>mines;
        }
        while(mines>=lines*columns-1||mines<=2);
        cout<<endl;
    }
    initializeMinesweeperMap(m,lines,columns,mines);
    numberOfFlags=m.nrOfMines;
    placeMines(m);
    countAdjacentMines1(m);
    if(wayOfPlaying=='k')reveal(m);
    necessaryRevealedCells=lines*columns-mines;
    ok=true;
    numberOfRevealedCells=0;
    firstMove=true;

}

void playingUsingKeyboard(MinesweeperMap &m)
{

    char action;
    unsigned int line,column,nr;
    cout<<" * on map means that the cell isn't opened and isn't marked with a flag"<<endl;
    cout<<"F-the cell isn't opened ,but it is marked with a flag"<<endl;
    cout<<"M-the cell is opened,and contains a mine ->Game Over"<<endl;
    cout<<"Type the line,the column and the action you want"<<endl;
    cout<<"o-open the cell at (line,column)"<<endl;
    cout<<"f-mark the cell at (line,column)with a flag"<<endl;
    cout<<"d-if the cell at (line,column) is already opened ,and the number of flags adjacent to it = number of the adjacent mines,all the cells around it,which are not marked with a flag, will be opened"<<endl;
    do
    {
        cin>>line>>column>>action;
    }
    while(line<0||line>m.yDimension-1||column<0||column>m.xDimension||(action!='o'&&action!='f'&&action!='d'));
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

    system("CLS");
    reveal(m);


}



void playingUsingMouse(MinesweeperMap &m,SDL_Window* &w,SDL_Surface* &s)
{

    unsigned int line,column,nr;
    SDL_Event e;
    SDL_Point mousePosition;
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
            cout<<"Flags available:"<<numberOfFlags<<endl;
            cout<<" * on map means that the cell isn't opened and isn't marked with a flag"<<endl;
            cout<<"F-the cell isn't opened ,but it is marked with a flag"<<endl;
            cout<<"M-the cell is opened,and contains a mine ->Game Over"<<endl;
            cout<<"Left click to open a cell;if the cell is already opened ,and the number of flags adjacent to it = number of the adjacent mines,all the cells around it,which are not marked with a flag, will be opened"<<endl;
            cout<<"Right click to mark a cell with a flag(or to unmark it)"<<endl;
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
    unsigned int line,column,i,j;
    char player[50];
    MinesweeperMap gameMap;
    double seconds;
    Records r[100];
    unsigned int numberOfRecords=0;
    clock_t t1,t2;
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
            initializeGame(gameMap,'k');
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
            SDL_SetMainReady();
            initializeGame(gameMap,'m');
            gameWindow=initWindow(gameMap.yDimension,gameMap.xDimension);
            screen=SDL_GetWindowSurface(gameWindow);
            SDL_SetWindowInputFocus(gameWindow);
            system("CLS");
            cout<<"Flags available: "<<numberOfFlags<<endl<<endl;
            cout<<" * on map means that the cell isn't opened and isn't marked with a flag"<<endl;
            cout<<"F-the cell isn't opened ,but it is marked with a flag"<<endl;
            cout<<"M-the cell is opened,and contains a mine ->Game Over"<<endl;
            cout<<"Left click to open a cell;if the cell is already opened ,and the number of flags adjacent to it = number of the adjacent mines,all the cells around it,which are not marked with a flag, will be opened"<<endl;
            cout<<"Right click to mark a cell with a flag(or to unmark it)"<<endl;
            SDL_Init(SDL_INIT_EVENTS);
            draw(gameMap,gameWindow,screen);
            t1=clock();
            do
            {
                playingUsingMouse(gameMap,gameWindow,screen);
                if(ok==false||(numberOfRevealedCells==necessaryRevealedCells&&numberOfFlags==0))
                {
                    t2=clock();
                    seconds=(t2-t1)/(double)CLOCKS_PER_SEC;
                    clean(gameWindow,screen);
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
            SDL_Quit();
            break;
        }
    }
    while(keepPlaying==true);
    showRecords(r,numberOfRecords);
    SDL_Quit();
    return 0;
}






