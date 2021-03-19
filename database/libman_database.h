#ifndef LIBMAN_DATABASE_H_INCLUDED
#define LIBMAN_DATABASE_H_INCLUDED

//include standard C libraries

#include <stdio.h>
#include <string.h>
#include <dirent.h>

//define s

#define OPTION_FILEPATH   "option.bin"
#define MAX_SIZE_CONTENT  5000
#define MAX_SIZE_STRING   100
#define MAX_READED_ACC    128
#define MAX_READED_BOOK   100
#define MAX_SIZE_FILENAME 64

//struct

typedef struct {
    char bookTitle        [MAX_SIZE_STRING   ];
    char bookAuthor       [MAX_SIZE_STRING   ];
    char bookLanguage     [MAX_SIZE_STRING   ];
    char bookSubject      [MAX_SIZE_STRING   ];
    char bookPublisher    [MAX_SIZE_STRING   ];
    char bookQuantity     [MAX_SIZE_STRING   ];
    char bookFilename     [MAX_SIZE_FILENAME ];
    char bookContents     [MAX_SIZE_CONTENT  ];
} BookData;

typedef struct {
    char accUsername                  [MAX_SIZE_STRING   ];
    char accPassword                  [MAX_SIZE_STRING   ];
    int  accPriority                                      ;
    char accBookmark [MAX_READED_BOOK][MAX_SIZE_FILENAME ];
    char accFilename                  [MAX_SIZE_FILENAME ];
    int  accBMcount                                       ; //account bookmark count
} AccountData;

//extern
//global variables

extern BookData     base_Book       [MAX_READED_BOOK ] ;
extern AccountData  base_Acc        [MAX_READED_ACC  ] ;

extern int bookNumber ,
           accNumber  ;

extern int rememberStatus,
           echoStatus    ;

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//account functions

void    Acc_Write_single(AccountData inputAcc);
void    Acc_Write_all(void);
void    Acc_Load(AccountData *inputAcc, char* filepath);

int     base_Acc_init(void);
int     base_Acc_add(AccountData inputAcc);
void    base_Acc_del(int index);

int     Account_Find_by_Filename(char inputFilename[MAX_SIZE_FILENAME]); //use by option_read

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//book functions

void    Book_Write_single(BookData inputBook);
void    Book_Write_all(void);
void    Book_Load(BookData *inputBook, char* filepath);

int     base_Book_init(void);
int     base_Book_add(BookData inputBook);
int     base_Book_clean_init(void); //this func to clean the old files
void    base_Book_del(int index);

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//bookmark functions

int     Bookmark_Add(BookData inputBook, AccountData *inputAcc); //add a book to single user
void    Bookmark_Del_single(BookData inputBook, AccountData *inputAcc); //single user
void    Bookmark_Del_all(BookData inputBook); //all user, invoked when a book is deleted
int     Bookmark_Find (BookData inputBook, AccountData inputAcc); //find a book

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//option functions

void    Option_Write(AccountData rememberAcc, int rememberStatus);
int     Option_Read(int *rememberStatus);

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
//general database function

void FirstTime_Run_Init(void);

void FirstTime_Login_Init(void);



#endif // LIBMAN_DATABASE_H_INCLUDED
