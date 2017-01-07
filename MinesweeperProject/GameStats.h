struct Records
{
    char player[50];
    char result[10];
    double seconds;
    int lines,columns;
    int nrOfMines;
};

void setRecord(Records &r,char name[50],char res[10],double s,int l,int c,int m);
void showRecords(Records r[],int n);

