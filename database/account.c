#include "libman_database.h"

AccountData base_Acc[MAX_READED_ACC];
int accNumber;

void Acc_Write_single(AccountData inputAcc)
{
    FILE *fpAcc = fopen(inputAcc.accFilename,"wb+");
    fwrite( inputAcc.accUsername         ,sizeof(char) ,MAX_SIZE_STRING                         ,fpAcc); fprintf(fpAcc,"\n");
    fwrite( inputAcc.accPassword         ,sizeof(char) ,MAX_SIZE_STRING                         ,fpAcc); fprintf(fpAcc,"\n");
    fwrite(&inputAcc.accPriority         ,sizeof(int ) ,1                                       ,fpAcc); fprintf(fpAcc,"\n");
    fwrite( inputAcc.accFilename         ,sizeof(char) ,MAX_SIZE_FILENAME                       ,fpAcc); fprintf(fpAcc,"\n");
    for (int i = 0; i <= inputAcc.accBMcount; i++)
        fwrite( inputAcc.accBookmark[i],sizeof(char),MAX_SIZE_FILENAME,fpAcc);
    fclose(fpAcc);
}


void Acc_Write_all(void)
{
    _chdir("account");
    //accnumber counts from 0
    //eg: 0 1 2 3 4 = 5 times
    for (int i = 0; i <= accNumber; i++) {
        Acc_Write_single(*(base_Acc + i));
    };
    _chdir("..\\");
}

void Acc_Load(AccountData *inputAcc, char* filepath)
{
    _chdir("account");
    FILE *fpAcc = fopen(filepath,"rb");
    fread(  inputAcc->accUsername         ,sizeof(char) ,MAX_SIZE_STRING                     ,fpAcc); fgetc(fpAcc);
    fread(  inputAcc->accPassword         ,sizeof(char) ,MAX_SIZE_STRING                     ,fpAcc); fgetc(fpAcc);
    fread(&(inputAcc->accPriority)        ,sizeof(int ) ,1                                   ,fpAcc); fgetc(fpAcc);
    fread(  inputAcc->accFilename         ,sizeof(char) ,MAX_SIZE_FILENAME                   ,fpAcc); fgetc(fpAcc);

    //get bmcount and bm list
    int *i = &(inputAcc->accBMcount); //to shorten
    (*i) = -1;
    char inpstr[MAX_SIZE_FILENAME];
    while (fgetc(fpAcc) != EOF) {
        fseek(fpAcc,-1,SEEK_CUR);
        fread(inpstr,sizeof(char),MAX_SIZE_FILENAME,fpAcc);
        strcpy((inputAcc->accBookmark[++(*i)]),inpstr);
    };

    fclose(fpAcc);
    _chdir("..\\");

}

//////////////////////////////////////////////////////////////////
//base_acc

int base_Acc_init(void)
{
    DIR *dir;
    if ((dir = opendir ("account")) == NULL) {
        return -2;
    };

    struct dirent *ent;
    int i = -1;
    readdir(dir); //get rid of "."
    readdir(dir); //get rid of ".."
    while ((ent = readdir (dir)) != NULL) {
            Acc_Load(base_Acc + ++i,ent->d_name);
    };
    closedir(dir);

    return i;
}


int base_Acc_add(AccountData inputAcc)
{
    if (accNumber == MAX_READED_ACC - 1)
        return 0; //out of range

    strcpy(inputAcc.accFilename,inputAcc.accUsername);
    strcat(inputAcc.accFilename,".bin");

    base_Acc[++accNumber] = inputAcc;
    return 1;
}


void base_Acc_del(int index)
//del a acc from its index
{
    AccountData *dest = base_Acc + index,
                *src  = dest + 1;
    size_t num =  MAX_READED_ACC - (index + 1);
           num *= sizeof(AccountData); //get number of bytes
    memcpy(dest,src,num);

    accNumber--;
}

int Account_Find_by_Filename(char inputFilename[MAX_SIZE_FILENAME])//use by option_read
{
    for (int i = 0; i <= accNumber; i++) {
        if (strcmp(base_Acc[i].accFilename,inputFilename) == 0)
            return i;
    };
    return -1;
}
