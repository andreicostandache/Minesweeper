struct Records
{
    char player[50];
    char result[10];
    double seconds;
    int lines,columns;
};

void setRecord(Records &r,char name[50],char res[10],double s,int l,int c);
void showRecords(Records r[],int n);

