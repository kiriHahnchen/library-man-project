#ifndef CONSOLE_UTILS_H_INCLUDED
#define CONSOLE_UTILS_H_INCLUDED

#include "../text_utils/text_utils.h"

#define dist_block 3
#define max_col 15
#define max_row 20

void gotoxy(int x, int y);

void any_key_exit(void);

char input_characterkey_handling(void) ;

int  input_arrow_key_vert(void);

int  input_arrow_key_hori(void);

void input_arrow_key_quad(int *dirc_x, int *dirc_y);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Draw_Table(int n_row, int m_col, int row_info_arr[max_row], int col_info_arr[max_col], int base_x, int base_y);

void Text_to_table_cell(int n_row, int m_col, int row_info_arr[max_row], int col_info_arr[max_col], char inputString[MAX_SIZE_STRING],
                        int indent_pref, int tab_len, int row_line, int base_x, int base_y) ;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#endif // CONSOLE_UTILS_H_INCLUDED
