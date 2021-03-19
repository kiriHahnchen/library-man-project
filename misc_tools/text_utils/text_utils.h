#ifndef TEXT_UTILS_H_INCLUDED
#define TEXT_UTILS_H_INCLUDED

//#include "../con_utils/con_utils.h"

//int TypingMask(const char outputChar, const int MASKING_STATUS);

//int isCharValid(const int inputChar); //return different values depending on the type

//void Space_to_Underscore_CONV(char *inputString, size_t searchrange);

void inputString_field_1d_print_simple(char inputString[MAX_SIZE_STRING], int len_bound, int mask_on, int base_x, int base_y) ;

void inputString_field_1d(char inputString[MAX_SIZE_STRING], char outputString[MAX_SIZE_STRING], char validChar_set[128], int len_bound,
                          int max_input_len, int mask_on, int base_x, int base_y) ;

void all_trim(char *inputString) ;

int isValidNumString(char *inputString) ;

int sfunc_normalSearch_for_Assignment(BookData inputBook, char *inputString, int search_opt_arr[3]) ;

#endif // TEXT_UTILS_H_INCLUDED
