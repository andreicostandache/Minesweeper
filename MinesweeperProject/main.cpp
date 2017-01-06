#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstring>
#include "MinesweeperMap.h"
#include "GameStats.h"
using namespace std;

bool ok=true;
int numberOfRevealedCells=0,necessaryRevealedCells,numberOfFlags;
char option,playAgain;
bool keepPlaying=true;
clock_t t1,t2;

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

void menu()
{
    option='b';
    cout<<"If you want to play,press k; "<<endl<<"If you want to see your stats press s"<<endl;
    do
    {
        cin>>option;
    }
    while(option!='k'&&option!='s');


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

int main()
{
    int line,column;
    char player[50];
    MinesweeperMap gameMap;
    double seconds;
    Records r[100];
    int numberOfRecords=0;
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
                        setRecord(r[numberOfRecords],player,"won",seconds,gameMap.yDimension,gameMap.xDimension);
                    }
                    else
                    {
                        cout<<endl<<"you lost";
                        setRecord(r[numberOfRecords],player,"lost",seconds,gameMap.yDimension,gameMap.xDimension);
                    }
                    numberOfRecords++;
                    keepPlaying=false;
                    playAgainQuestion();
                }

            }
            while(ok==true&&(numberOfRevealedCells<necessaryRevealedCells||numberOfFlags!=0));
            break;

        }
    }
    while(keepPlaying==true);
    showRecords(r,numberOfRecords);
    return 0;
}






