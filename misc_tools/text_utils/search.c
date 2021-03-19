#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../database/libman_database.h"
#include "text_utils.h"

/*
int sfunc_normalSearch_for_Assignment(BookData inputBook, char *inputString, int search_opt_arr[4])
{
    if (search_opt_arr[0])
        for (int i = 1; i <= 3; i++) search_opt_arr[i] = 1;
    int res[3] = {0,0,0} ;

    if (search_opt_arr[1]) {
        if (strstr(inputString,inputBook.bookTitle) != NULL)
            res[0] = 1;
    } ;

    if (search_opt_arr[2]) {
        if (strstr(inputString,inputBook.bookQuantity) != NULL)
            res[1] = 1;
    } ;

    if (search_opt_arr[3]) {
        if ((strstr(inputString,inputBook.bookLanguage  ) != NULL) ||
            (strstr(inputString,inputBook.bookPublisher ) != NULL) ||
            (strstr(inputString,inputBook.bookAuthor    ) != NULL) ||
            (strstr(inputString,inputBook.bookSubject   ) != NULL) ||
            (strstr(inputString,inputBook.bookContents  ) != NULL)
            )
            res[2] = 1;
    } ;

    return (res[0] || res[1]) || res[2] ;
}


/**< Later implemented */
/*

//receiver func

int sfunc_isAdvanced(char *inputString)
{
    //find if is advanced mode
    if (strstr(inputString,"& ") == (inputString + 0))
        return 1 ;
    return 0 ;
}

void sfunc_sub_len_num_analyzer(char *inputString, int *max_sub_len, int *max_sub_num, int isAdvanced)
{
    char *tmpString = (char *) malloc((500 + 1) * sizeof(char)) ;
    memset(tmpString,0,500) ;
    strcpy(tmpString,inputString) ;

    if (isAdvanced) {
        for (int i = 0, i <= 2; i++)
            memset(strchr(tmpString,';'),' ',1);
    } ;
    tmpString[strlen(tmpString)] = ' ';

    //base, curr, len
    int len = (int) strlen(tmpString) - 1 ;
    int count_len, count_num = 0, curr_index = 0;;
    while (curr_index <= len) {
        if (tmpString[curr_index++] != ' ') {
            count_len++;
        }
        else {
            count_num++ ;
            if (count_len > *max_sub_len)
                *max_sub_len = count_len ;
            count_len = 0;
        } ;
    } ;
}

int sfunc_search(BookData inputBook, char *inputString, int search_opt_arr[4])
{
    int search_result = 0;

    //pre-process

    char *process_string = (char *) malloc((500 + 1) * sizeof(char)) ;
    memset(process_string,0,500) ;
    strcpy(process_string,inputString) ;
    all_trim(process_string) ;

    //analyzer and sub-chunks

    int analyze_res = sfunc_isAdvanced(process_string) ;
    int max_sub_len = 0 ;
    int max_sub_num = 0 ;

    int start_alyze = (analyze_res) ? 2 : 0 ;

    sfunc_sub_len_num_analyzer(process_string + start_alyze, &max_sub_len, &max_sub_num, analyze_res) ;

    //generate the sub

    char *sub_chunk_general  [max_sub_num] = (char *) malloc(sizeof(char) * (max_sub_len + 1)) ;
    char *sub_chunk_quantity [max_sub_num] = (char *) malloc(sizeof(char) * (max_sub_len + 1)) ;
    char *sub_chunk_metadata [max_sub_num] = (char *) malloc(sizeof(char) * (max_sub_len + 1)) ;

    if (analyze_res) {

    }
    else {

    }

    //searching

    if (analyze_res) {

    }
    else {

    }

    //compute weight

    if (analyze_res) {

    }
    else {

    }

    //output


    return search_result;
}

*/
