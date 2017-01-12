struct Records
{   double seconds;
    char player[50];
    char result[10];
    unsigned int lines,columns;
    unsigned int nrOfMines;
};

void setRecord(Records &r,char name[50],char res[10],double s,unsigned int l,unsigned int c,unsigned int m);
void showRecords(Records r[],int n);

