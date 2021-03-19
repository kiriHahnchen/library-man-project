#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#include "../../misc_tools/text_utils/text_utils.h"

typedef struct
{
    char    bookName        [MAX_SIZE_STRING];
    char    bookAuthor      [MAX_SIZE_STRING];
    char    bookLanguage    [MAX_SIZE_STRING];
    char    bookSubject     [MAX_SIZE_STRING];
    char    bookPublisher   [MAX_SIZE_STRING];
    char    bookQuantity    [MAX_SIZE_STRING];
    char    bookFilename    [FILENAME_MAX   ];
//    int     bookPubDate;
} BookInfo;

int Book_Init(BookInfo inputBook);

int Book_Edit(BookInfo inputBook);

int Book_Del(BookInfo inputBook);

#endif // BOOK_H_INCLUDED
