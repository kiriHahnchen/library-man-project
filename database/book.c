#include "libman_database.h"

//int istaken(char *inputStr)  ;

BookData base_Book[MAX_READED_BOOK];
int bookNumber;

void Book_Write_single(BookData inputBook)
{

    FILE *fpBook = fopen(inputBook.bookFilename,"wb+");
    fwrite(inputBook.bookTitle      ,sizeof(char),MAX_SIZE_STRING   , fpBook); fprintf(fpBook,"\n");
    fwrite(inputBook.bookAuthor     ,sizeof(char),MAX_SIZE_STRING   , fpBook); fprintf(fpBook,"\n");
    fwrite(inputBook.bookLanguage   ,sizeof(char),MAX_SIZE_STRING   , fpBook); fprintf(fpBook,"\n");
    fwrite(inputBook.bookSubject    ,sizeof(char),MAX_SIZE_STRING   , fpBook); fprintf(fpBook,"\n");
    fwrite(inputBook.bookPublisher  ,sizeof(char),MAX_SIZE_STRING   , fpBook); fprintf(fpBook,"\n");
    fwrite(inputBook.bookQuantity   ,sizeof(char),MAX_SIZE_STRING   , fpBook); fprintf(fpBook,"\n");
    fwrite(inputBook.bookFilename   ,sizeof(char),MAX_SIZE_FILENAME , fpBook); fprintf(fpBook,"\n");
    fwrite(inputBook.bookContents   ,sizeof(char),MAX_SIZE_CONTENT  , fpBook);

    fclose(fpBook);

}

void Book_Write_all(void)
{
    base_Book_clean_init() ;
    _chdir("book");
    //booknumber counts from 0
    //eg: 0 1 2 3 4 = 5 times
    for (int i = 0; i <= bookNumber; i++) {
        Book_Write_single(*(base_Book + i));
    };
    _chdir("..\\");
}

void Book_Load(BookData *inputBook, char* filepath)
{

    _chdir("book");
    FILE *fpBook = fopen(filepath,"rb");
    fread(inputBook->bookTitle      ,sizeof(char),MAX_SIZE_STRING   , fpBook); fgetc(fpBook);
    fread(inputBook->bookAuthor     ,sizeof(char),MAX_SIZE_STRING   , fpBook); fgetc(fpBook);
    fread(inputBook->bookLanguage   ,sizeof(char),MAX_SIZE_STRING   , fpBook); fgetc(fpBook);
    fread(inputBook->bookSubject    ,sizeof(char),MAX_SIZE_STRING   , fpBook); fgetc(fpBook);
    fread(inputBook->bookPublisher  ,sizeof(char),MAX_SIZE_STRING   , fpBook); fgetc(fpBook);
    fread(inputBook->bookQuantity   ,sizeof(char),MAX_SIZE_STRING   , fpBook); fgetc(fpBook);
    fread(inputBook->bookFilename   ,sizeof(char),MAX_SIZE_FILENAME , fpBook); fgetc(fpBook);
    fread(inputBook->bookContents   ,sizeof(char),MAX_SIZE_CONTENT  , fpBook);

    fclose(fpBook);
    _chdir("..\\");
}

//base_book

int base_Book_init(void)
{
    DIR *dir;
    if ((dir = opendir ("book")) == NULL) {
        return -2;
    };

    struct dirent *ent;
    int i = -1;
    readdir(dir); //get rid of "."
    readdir(dir); //get rid of ".."
    while ((ent = readdir (dir)) != NULL) {
        Book_Load(base_Book + ++i,ent->d_name);
    };
    closedir(dir);

    return i;
}

int base_Book_clean_init(void)
{
    DIR *dir;
    if ((dir = opendir ("book")) == NULL) {
        return -2;
    };

    struct dirent *ent;
    int i = -1;
    readdir(dir); //get rid of "."
    readdir(dir); //get rid of ".."
    while ((ent = readdir (dir)) != NULL) {
        _chdir("book");
        remove(ent->d_name);
        _chdir("..\\");
    };
    closedir(dir);

    return i;
}

int base_Book_add(BookData inputBook)
{
    if (bookNumber == MAX_READED_BOOK - 1)
        return 0; //out of range

    char *tmpStr = inputBook.bookFilename; //shorten

    _chdir("book");
    while (tmpnam(tmpStr) == NULL) ;
    _chdir("..\\"); //temporary moves back to main folder

    //This section is for recording what new file has been added
    //almost similar to a full log-file
    //automatically deleted when the program terminated
    FILE *fp = fopen("tmpnam_generated.txt","a+");
    fwrite(tmpStr,1,32,fp) ; fputc('\n',fp) ;

    *(strchr(tmpStr,'.')) = '0';
    memcpy(tmpStr,tmpStr+1,strlen(tmpStr) - 1);
    tmpStr[strlen(tmpStr) - 1] = '\0';

    fwrite(tmpStr,1,32,fp) ; fputc('\n',fp) ;
    fclose(fp) ;
    //finished logging

    _chdir("book");
    base_Book[++bookNumber] = inputBook;
    Book_Write_single(base_Book[bookNumber]) ;
    _chdir("..\\");

    return 1;
}

void base_Book_del(int index)
//del a book from its index
{
    BookData *dest = base_Book + index,
             *src  = dest + 1;
    size_t num =  MAX_READED_BOOK - (index + 1);
           num *= sizeof(BookData); //get number of bytes
    memcpy(dest,src,num);

    bookNumber--;
}

