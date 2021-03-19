#include <ctype.h>
#include "../../database/libman_database.h"
#include "../con_utils/con_utils.h"

static int isCharValid_base_on_set(const int inputChar, char validChar_set[128])
{
    for (int i = 0; i <= 128; i++)
        if (inputChar == validChar_set[i])
            return 1;
    return 0;
}

int istaken(char *inputStr)
{
    //int status = 0;

    for (int i = 0; i <= bookNumber; i++) {
        if (strcmp(inputStr,base_Book[i].bookFilename) == 0)
            return 1;
    }
    return 0;
}

static void inputString_field_1d_print(char inputString[MAX_SIZE_STRING], int offset_pos, int len_bound, int curr_pos, int mask_on, int base_x, int base_y)
{
    printf("\x1B[?25l"); //hide cursor
    gotoxy(base_x,base_y);
    for (int i = 0; i <= len_bound - 1; i++) printf(" ");
    gotoxy(base_x,base_y);
    int len = (int) strlen(inputString) ;
    if (mask_on == -1) {
        int output_len = (len_bound > len) ? len : len_bound ;
        printf("%.*s", output_len, inputString + offset_pos);
    }
    else {
        int output_len = (len_bound > len) ? len : len_bound;
        output_len--; //to 0-indexed number
        for(int i = 0; i <= output_len; i++) printf("*");
    };
    gotoxy(base_x,curr_pos + base_y); //go to cursor position, based on
                             //the length of the current string
    printf("\x1B[?25h")  ;   //show cursor
}

/**<  For use in other -base function */

void inputString_field_1d_print_simple(char inputString[MAX_SIZE_STRING], int len_bound, int mask_on, int base_x, int base_y)
{
    printf("\x1B[?25l"); //hide cursor
    gotoxy(base_x,base_y);
    for (int i = 0; i <= len_bound - 1; i++) printf(" ");
    gotoxy(base_x,base_y);
    int len = (int) strlen(inputString) ;
    if (mask_on == -1) {
        int output_len = (len_bound > len) ? len : len_bound ;
        printf("%.*s", output_len, inputString);
    }
    else {
        int output_len = (len_bound > len) ? len : len_bound;
        output_len--; //to 0-indexed number
        for(int i = 0; i <= output_len; i++) printf("*");
    };
}

/**< Text input function */
//len_bound is 1-indexed
/** TODO (Anh Hai#1#): Should passing the col_info_arr into this, and add indent_pref to this */
//dunno why but this function should be inside con_utils instead

void inputString_field_1d(char inputString[MAX_SIZE_STRING], char outputString[MAX_SIZE_STRING], char validChar_set[128], int len_bound,
                          int max_input_len, int mask_on, int base_x, int base_y)
{
    char inputCh ;
    char tmpString[MAX_SIZE_STRING] = "";
    strcpy(tmpString,inputString);

    int offset_pos = (int) strlen(inputString) - len_bound; //furthest offset
    int cursor = (int) strlen(inputString) ;                //real position of cursor in string
    int curr_pos ;                                          //position display on screen
    if (offset_pos < 0)
        curr_pos = cursor    ;
    else
        curr_pos = len_bound ;
    //if negative, it equals cursor, else go to len_bound   (largest pos)
    if (offset_pos < 0) offset_pos = 0;                     //0 if negative
    //input field appearance init
    inputString_field_1d_print(tmpString,offset_pos,len_bound,curr_pos,mask_on,base_x,base_y) ;
    do {
        inputCh = input_displayable_ascii_character_handling(); //input
        if (inputCh == 0) continue ;
        if ((inputCh == -1) || (inputCh == 1)) {
            //go to the left
            if (inputCh == -1) {
                if ((strlen(tmpString) == 0) || (cursor == 0))
                    continue ;
                //if curr_pos = 0 and offset > 0
                if ((offset_pos > 0) && (curr_pos == 0)) {
                    cursor-- ;
                    offset_pos--;
                    inputString_field_1d_print(tmpString,offset_pos,len_bound,curr_pos,mask_on,base_x,base_y) ;
                    continue ;
                } ;
                if (curr_pos > 0) {
                    cursor--;
                    curr_pos--;
                    printf("\b") ;
                    continue ;
                } ;
            };
            //go to the right
            if (inputCh == 1) {
                int len = (int) strlen(tmpString) ;
                if (len == 0)
                    continue ;
                if ((offset_pos == 0) && (cursor == len))
                    continue ;

                if (curr_pos == len_bound) {
                    if (offset_pos < len - len_bound) {
                        cursor++;
                        offset_pos++;
                    } ;
                    if (offset_pos > len - len_bound)
                        continue ;
                    if (offset_pos == len - len_bound) {
                        if (cursor == len)
                            continue ;
                    };
                }
                else {
                    cursor++;
                    curr_pos++;
                };
                inputString_field_1d_print(tmpString,offset_pos,len_bound,curr_pos,mask_on,base_x,base_y) ; //redraw
                continue ;
            };
        };

        if (inputCh == '\b') {
            if ((strlen(tmpString) == 0) || (cursor == 0))
                continue ;

            //process string
            int len  = (int) strlen(tmpString) - 1;
            for (int i = cursor - 1; i <= len - 1; i++)
                tmpString[i] = tmpString[i + 1];
            tmpString[len] = 0 ;
            cursor--;

            //process the cursor and printing
            if (offset_pos > 0) {
                if (offset_pos > len - len_bound)
                    offset_pos -- ;
                else {
                    if (curr_pos == 0) offset_pos -- ;
                    else               curr_pos   -- ;
                } ;
            }
            else {
                if (curr_pos > 0)
                    curr_pos --;
            }
            inputString_field_1d_print(tmpString,offset_pos,len_bound,curr_pos,mask_on,base_x,base_y) ;
            continue ;
        };

        if ((inputCh != '\x1B') && (inputCh != '\r') && (inputCh != '\n')) {
            if (isCharValid_base_on_set(inputCh,validChar_set) == 0)
                continue ;
        }
        else {
            continue ;
        }
        //adding character
        //string process
        if ((int) strlen(tmpString) != max_input_len) {
            int len = (int) strlen(tmpString) ;
            for (int i = len + 1; i >= cursor + 1; i--) {
                tmpString[i] = tmpString[i - 1] ;
            } ;
            tmpString[cursor++] = inputCh ;

            if (curr_pos != len_bound) curr_pos   ++ ;
            else                       offset_pos ++ ;
            inputString_field_1d_print(tmpString,offset_pos,len_bound,curr_pos,mask_on,base_x,base_y) ;
        } ;

    } while ((inputCh != '\x1B') && (inputCh != '\r') && (inputCh != '\n')) ;

    if ((inputCh == '\r') || (inputCh == '\n'))
        strcpy(outputString,tmpString);   //save
    else
        strcpy(outputString,inputString); //discard changes
    //post printing
    offset_pos = 0;
    curr_pos = 0;
    inputString_field_1d_print(outputString,offset_pos,len_bound,curr_pos,mask_on,base_x,base_y) ;
    printf("\x1B[?25l"); //hide cursor
}

void right_trim(char *inputString)
{
	size_t len = strlen(inputString);
	if (len == 0) return ;
	len--;
	while (inputString[len] == ' ') {
		inputString[len--] = 0 ;
	}
}

void left_trim(char *inputString)
{
	size_t len = strlen(inputString);
	if (len == 0) return ;
	while (inputString[0] == ' ') {
		memcpy(inputString, inputString + 1, --len) ;
		inputString[len] = 0 ;
	}
}

void mid_trim(char *inputString)
{
	char *pos;
	if (strlen(inputString) == 0) return ;
	while ((pos = strstr(inputString,"  ")) != NULL) {
		memcpy(pos, pos + 1, strlen(pos + 1)) ;
		inputString[strlen(inputString) - 1] = 0 ;
	};
}

void all_trim(char *inputString)
{
	right_trim(inputString) ;
	left_trim(inputString) ;
	mid_trim(inputString) ;
}

int isNum(char inputChar)
{
	if (inputChar >= '0' && inputChar <= '9')
		return 1;
	else
		if (inputChar == ' ')
			return 1;
		else
			return 0;
}

int isValidNumString(char *inputString)
{
    int len = (int) strlen(inputString) ;
	for (int i = 0; i < len; i++)
		if (!isNum(inputString[i]))
			return 0;
	return 1;
}


int sfunc_normalSearch_for_Assignment(BookData inputBook, char *inputString, int search_opt_arr[3])
{
    if (search_opt_arr[0]) {
        if (strstr(inputBook.bookTitle,inputString) != NULL)
            return 1;
        else
            return 0;
    } ;

    if (search_opt_arr[1]) {
        if (strstr(inputBook.bookQuantity,inputString) != NULL)
            return 1;
        else
            return 0;
    } ;

    if (search_opt_arr[2]) {
        if ((strstr(inputBook.bookLanguage  ,inputString) != NULL) ||
            (strstr(inputBook.bookPublisher ,inputString) != NULL) ||
            (strstr(inputBook.bookAuthor    ,inputString) != NULL) ||
            (strstr(inputBook.bookSubject   ,inputString) != NULL) ||
            (strstr(inputBook.bookContents  ,inputString) != NULL)
            )
            return 1;
        else
            return 0;
    } ;

    return 0 ;
}
