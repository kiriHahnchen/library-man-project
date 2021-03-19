#ifndef ACCOUNT_UTILS_H_INCLUDED
#define ACCOUNT_UTILS_H_INCLUDED

#include "../../misc_tools/text_utils/text_utils.h"

typedef struct
{
    char    username    [MAX_SIZE_STRING];
    char    password    [MAX_SIZE_STRING];
    int     priority;
} AccountInfo;

int Acc_Create(AccountInfo inputAcc);

int Acc_Delete(AccountInfo inputAcc);

int Acc_Edit(AccountInfo oldAcc, AccountInfo newAcc);

int Acc_Read(char inputUsername[MAX_SIZE_STRING], AccountInfo *outputAcc);

int Acc_Cmp(AccountInfo acc1, AccountInfo acc2);

void Acc_Encrypt(AccountInfo *inputAcc);

#endif // ACCOUNT_UTILS_H_INCLUDED
