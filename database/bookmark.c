#include "libman_database.h"

int Bookmark_Add(BookData inputBook, AccountData *inputAcc) //add a book to single user
{
    for (int i = 0; i <= inputAcc->accBMcount; i++) {
        if (strcmp(inputAcc->accBookmark[i],inputBook.bookFilename) == 0) return 0; //if already add
    };

    int *i = &(inputAcc->accBMcount); //shorten
    strcpy(inputAcc->accBookmark[++(*i)],inputBook.bookFilename);
    return 1;
}

int Bookmark_Find (BookData inputBook, AccountData inputAcc)
{
    for (int i = 0; i <= inputAcc.accBMcount; i++) {
        if (strcmp(inputAcc.accBookmark[i],inputBook.bookFilename) == 0) return 1; //if already add
    };

    return 0;
}

void Bookmark_Del_single(BookData inputBook, AccountData *inputAcc) //single user
{
    int i;
    for (i = 0; i <= inputAcc->accBMcount; i++) {
        if (strcmp(inputAcc->accBookmark[i],inputBook.bookFilename) == 0) {
            char *dest = inputAcc->accBookmark[i    ]  ,
                 *src  = inputAcc->accBookmark[i + 1]  ;
            size_t num =  MAX_READED_BOOK - (i + 1);
                   num *= sizeof(inputAcc->accBookmark[i]);
            memcpy(dest,src,num);
            (inputAcc->accBMcount)--;
            return ;
        }
    };
}

void Bookmark_Del_all(BookData inputBook) //all user, invoked when a book is deleted
{
    for (int i = 0; i <= accNumber - 1; i++)
        Bookmark_Del_single(inputBook,base_Acc + i);
}
