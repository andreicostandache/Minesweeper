#include "GameStats.h"
#include <cstring>
#include <iostream>
using namespace std;

void setRecord(Records &r,char name[50],char res[10],double s,int l,int c,int m)
 {
     strcpy(r.player,name);
     strcpy(r.result,res);
     r.seconds=s;
     r.lines=l;
     r.columns=c;
     r.nrOfMines=m;
 }

void showRecords(Records r[],int n)
{
    int i;
    if(n>=1)
        for(i=0; i<=n-1; i++,cout<<endl)
            cout<<i+1<<" "<<'('<<r[i].result<<" game"<<')'<<"player: "<<r[i].player<<" "<<"The map had "<<r[i].lines<<" lines, "<<r[i].columns<<" columns, "<<r[i].nrOfMines<<" mines, and the game lasted "<<r[i].seconds<<" seconds"<<endl;
    else
        cout<<"No games played yet :(";
}

