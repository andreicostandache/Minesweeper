struct MinesweeperMapCell
{
    unsigned int nrOfAdjacentMines;
    bool containsMine,containsFlag,canBeRevealed;

};
struct MinesweeperMap
{
    MinesweeperMapCell grid [110][60];
    unsigned int xDimension,yDimension,nrOfMines;
};
void initializeMinesweeperMapCell(MinesweeperMapCell &a);
void initializeMinesweeperMap(MinesweeperMap &m1,unsigned int y,unsigned int x,unsigned int b);
unsigned int countAdjacentMines(MinesweeperMap m,unsigned int i,unsigned int j);
unsigned int countAdjacentFlags(MinesweeperMap m,unsigned int i,unsigned int j);
void placeMines(MinesweeperMap &m1);
void countAdjacentMines1(MinesweeperMap &m1);



