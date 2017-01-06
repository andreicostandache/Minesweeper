struct MinesweeperMapCell
{
    bool containsMine,containsFlag,canBeRevealed;
    int nrOfAdjacentMines;
};
struct MinesweeperMap
{
    MinesweeperMapCell grid [100][100];
    int xDimension,yDimension,nrOfMines;
};
void initializeMinesweeperMapCell(MinesweeperMapCell &a);
void initializeMinesweeperMap(MinesweeperMap &m1,int y,int x,int b);
int countAdjacentMines(MinesweeperMap m,int i,int j);
int countAdjacentFlags(MinesweeperMap m,int i,int j);
void placingMines(MinesweeperMap &m1);
void countAdjacentMines1(MinesweeperMap &m1);


