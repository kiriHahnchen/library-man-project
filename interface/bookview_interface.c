#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../database/libman_database.h"
#include "../misc_tools/libman_tools.h"

void bview_for_assignment_view(BookData inputBook)
{
    system("cls") ;
    gotoxy(1,1);
    printf("Title: %s"     , inputBook.bookTitle)       ; printf("\n");
    printf("Author(s): %s" , inputBook.bookAuthor)      ; printf("\n");
    printf("Language: %s"  , inputBook.bookLanguage)    ; printf("\n");
    printf("Subject: %s"   , inputBook.bookSubject)     ; printf("\n");
    printf("Publisher: %s" , inputBook.bookPublisher)   ; printf("\n");
    printf("Quantity: %s"  , inputBook.bookQuantity)    ; printf("\n");

    printf("\nPress anykey to go back to the booklist menu\n") ;
    any_key_exit() ;
}

int bview_for_assignment_add(BookData *inputBook)
{
    system("cls") ;
    gotoxy(1,1);
    char o_status = 0 ;

    printf("Title: ");
    scanf("%100[^\n]s",inputBook->bookTitle    ) ;
    while (fgetc(stdin) != '\n') ;

    printf("Author(s): ");
    scanf("%100[^\n]s",inputBook->bookAuthor   ) ;
    while (fgetc(stdin) != '\n') ;

    printf("Language: ");
    scanf("%100[^\n]s",inputBook->bookLanguage ) ;
    while (fgetc(stdin) != '\n') ;

    printf("Subject: ");
    scanf("%100[^\n]s",inputBook->bookSubject  ) ;
    while (fgetc(stdin) != '\n') ;

    printf("Publisher: ");
    scanf("%100[^\n]s",inputBook->bookPublisher) ;
    while (fgetc(stdin) != '\n') ;

    printf("Quantity: ");
    scanf("%100[0-9]s",inputBook->bookQuantity) ;
    while (fgetc(stdin) != '\n') ;

    printf("\n");
    printf("\nSave changes ? ( [Y] YES \\ [N] NO ) : ") ;
    o_status = fgetc(stdin) ;
    while (fgetc(stdin) != '\n') ;

    printf("\nPress anykey to go back to the booklist menu\n") ;

    any_key_exit() ;

    if ((o_status == 'Y') || (o_status == 'y')) {
        return 1;
    } ;
    return 0;
}


int bview_for_assignment_edit(BookData *inputBook)
{
    system("cls") ;
    gotoxy(1,1);
    char o_status ;
    BookData origBook = *inputBook ;

    printf("Title: ");
    scanf("%100[^\n]s",inputBook->bookTitle   ) ;
    while (fgetc(stdin) != '\n') ;

    printf("Author(s): ");
    scanf("%100[^\n]s",inputBook->bookAuthor   ) ;
    while (fgetc(stdin) != '\n') ;

    printf("Language: ");
    scanf("%100[^\n]s",inputBook->bookLanguage ) ;
    while (fgetc(stdin) != '\n') ;

    printf("Subject: ");
    scanf("%100[^\n]s",inputBook->bookSubject  ) ;
    while (fgetc(stdin) != '\n') ;

    printf("Publisher: ");
    scanf("%100[^\n]s",inputBook->bookPublisher) ;
    while (fgetc(stdin) != '\n') ;

    printf("Quantity: ");
    scanf("%100[0-9]s",inputBook->bookQuantity) ;
    while (fgetc(stdin) != '\n') ;

    printf("\n");
    printf("\nSave changes ? ( [Y] YES \\ [N] NO ) : ") ;
    o_status = fgetc(stdin) ;
    while (fgetc(stdin) != '\n') ;

    printf("\nPress anykey to go back to the booklist menu\n") ;
    any_key_exit() ;

    if ((o_status == 'Y') || (o_status == 'y')) {
        return 1;
    } ;
    *inputBook = origBook ;
    return 0;
}
