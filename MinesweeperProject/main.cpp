#include <iostream>
#include <ctime>
#include "MinesweeperMap.h"
#include <stdlib.h>
using namespace std;

bool ok=true;
int numberOfRevealedCells=0,necessaryRevealedCells,numberOfFlags;
char option,playAgain;
bool keepPlaying=true;

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
    placingMines(m);
    countAdjacentMines1(m);
    reveal(m);
    numberOfFlags=mines;
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
    else if(action=='a')
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
    else
        cout<<"INVALID MOVE";
    system("CLS");
    reveal(m);


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
    char action,play;
    MinesweeperMap gameMap;

    double seconds;
    do
    {

            initializeGame(gameMap);
            system("CLS");
            reveal(gameMap);
            do
            {
                playingUsingKeyboard(gameMap);

                if(ok==false||(numberOfRevealedCells==necessaryRevealedCells&&numberOfFlags==0))
                {


                    if(numberOfRevealedCells==necessaryRevealedCells&&numberOfFlags==0)


                        cout<<endl<<"you won";


                    else

                        cout<<endl<<"you lost";

                    keepPlaying=false;
                    playAgainQuestion();
                }

            }
            while(ok==true&&(numberOfRevealedCells<necessaryRevealedCells||numberOfFlags!=0));
        }

    while(keepPlaying==true);

    return 0;
}







