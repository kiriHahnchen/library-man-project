#include "libman_database.h"

void Option_Write(AccountData rememberAcc, int rememberStatus)
{
    FILE *fp = fopen(OPTION_FILEPATH,"wb+");
    char blankStr[MAX_SIZE_FILENAME] = "";
    fprintf(fp,"%d\n",rememberStatus);
    if (rememberStatus)
        fwrite(rememberAcc.accFilename,sizeof(char),sizeof(rememberAcc.accFilename),fp);
    else
        fwrite(blankStr               ,sizeof(char),sizeof(rememberAcc.accFilename),fp);
    //fprintf(fp,"\n%d\n",echoStatus);
    fclose(fp);
}

int Option_Read(int *rememberStatus)
{
    int index ;
    char readedFilename[MAX_SIZE_FILENAME];

    FILE *fp = fopen(OPTION_FILEPATH,"rb");
    fscanf(fp,"%d",rememberStatus);
    fgetc(fp);
    fread(readedFilename,sizeof(char),sizeof(readedFilename),fp); fgetc(fp);
    //fscanf(fp,"%d",echoStatus);
    fclose(fp);
    if (*rememberStatus) {
        index = Account_Find_by_Filename(readedFilename);
        if (index == -1)
            *rememberStatus = 0;
    }
    else
        index = -1;
    return index;
}
