#include "MinesweeperMap.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

void initializeMinesweeperMapCell(MinesweeperMapCell &a)
{
    a.containsMine=false;
    a.canBeRevealed=false;
    a.containsFlag=false;
    a.nrOfAdjacentMines=0;
}


void initializeMinesweeperMap(MinesweeperMap &m1,int y,int x,int b)
{
    m1.xDimension=x;
    m1.yDimension=y;
    m1.nrOfMines=b;
    int i,j;
    for(i=0; i<=m1.yDimension-1; i++)
        for(j=0; j<=m1.xDimension-1; j++)
            initializeMinesweeperMapCell(m1.grid[i][j]);
}


int countAdjacentMines(MinesweeperMap m,int i,int j)
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


int countAdjacentFlags(MinesweeperMap m,int i,int j)
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
void placingMines(MinesweeperMap &m1)
{
    int i,a,b;
    i=0;
    while(i<=m1.nrOfMines-1)
    {
        a=rand()%m1.yDimension;
        b=rand()%m1.xDimension;
        if(m1.grid[a][b].containsMine==0)
        {
            m1.grid[a][b].containsMine=1;
            i++;
        }
    }


}

void countAdjacentMines1(MinesweeperMap &m1)
{
    int i,j,x,y;
    x=m1.xDimension-1;
    y=m1.yDimension-1;

    m1.grid[0][0].nrOfAdjacentMines+=(m1.grid[1][0].containsMine+m1.grid[0][1].containsMine+m1.grid[1][1].containsMine);
    m1.grid[y][0].nrOfAdjacentMines+=(m1.grid[y][1].containsMine+m1.grid[y-1][0].containsMine+m1.grid[y-1][1].containsMine);
    m1.grid[0][x].nrOfAdjacentMines+=(m1.grid[0][x-1].containsMine+m1.grid[1][x].containsMine+m1.grid[1][x-1].containsMine);
    m1.grid[y][x].nrOfAdjacentMines+=(m1.grid[y][x-1].containsMine+m1.grid[y-1][x].containsMine+m1.grid[y-1][x-1].containsMine);

    for(j=1; j<=x-1; j++)
    {
        m1.grid[0][j].nrOfAdjacentMines+=(m1.grid[0][j-1].containsMine+m1.grid[0][j+1].containsMine+m1.grid[1][j-1].containsMine+m1.grid[1][j].containsMine+m1.grid[1][j+1].containsMine);
        m1.grid[y][j].nrOfAdjacentMines+=(m1.grid[y][j-1].containsMine+m1.grid[y][j+1].containsMine+m1.grid[y-1][j-1].containsMine+m1.grid[y-1][j].containsMine+m1.grid[y-1][j+1].containsMine);
    }
    for(i=1; i<=y-1; i++)
    {
        m1.grid[i][0].nrOfAdjacentMines+=m1.grid[i-1][0].containsMine+m1.grid[i+1][0].containsMine+m1.grid[i-1][1].containsMine+m1.grid[i+1][1].containsMine+m1.grid[i][1].containsMine;
        m1.grid[i][x].nrOfAdjacentMines+=m1.grid[i-1][x].containsMine+m1.grid[i+1][x].containsMine+m1.grid[i-1][x-1].containsMine+m1.grid[i+1][x-1].containsMine+m1.grid[i][x-1].containsMine;
    }
    for(i=1; i<=y-1; i++)
        for(j=1; j<=x-1; j++)
            m1.grid[i][j].nrOfAdjacentMines+=(m1.grid[i-1][j-1].containsMine+m1.grid[i-1][j].containsMine+m1.grid[i-1][j+1].containsMine+m1.grid[i][j-1].containsMine+m1.grid[i][j+1].containsMine+m1.grid[i+1][j-1].containsMine+m1.grid[i+1][j].containsMine+m1.grid[i+1][j+1].containsMine);
}


