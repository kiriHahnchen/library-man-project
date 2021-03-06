#ifndef CON_UTILS_H_INCLUDED
#define CON_UTILS_H_INCLUDED

#include "../../database/libman_database.h"

#ifndef MAX_SIZE_STRING
#define MAX_SIZE_STRING 100
#endif // MAX_SIZE_STRING

#define max_col 15
#define max_row 20

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
    int x,y;
} corxy;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gotoxy(int row, int col);

void any_key_exit(void);

char input_displayable_ascii_character_handling(void) ;
//usage is wider
//can only reposition the input cursor, delete under cursor, add under cursor
//now accepts displayable ascii characters on the keyboard

int  input_arrow_key_vert(void);

int  input_arrow_key_hori(void);

int  input_arrow_key_quad(int *dirc_x, int *dirc_y);

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

int OPT_mono_create_1d(int n_OPT, int input_OPT, corxy inputCoord_arr[n_OPT], int trailMode, int mask_on, int mask_off, int dirc);
//1 means vertical
//2 means horizontal
//returns the value user choosen

//trail mode is status , if you choose 1, it will leave a cursor on where you left
//useful for index choosing

void OPT_multi_create_1d_withHierarchie(int n_OPT, corxy inputCoord_arr[n_OPT],int inputHierarchie[n_OPT][n_OPT] ,
                                        int mask_on, int mask_off, int dirc, int output_OPTs[n_OPT]              );

//multiple choice with hierarchie
//output to an array of value

                                                                    //col first  //row second
int OPT_mono_create_2d(int n_OPT_row, int m_OPT_col, corxy inputCoord_arr[m_OPT_col][n_OPT_row], int trailMode ,
                       int mask_on  , int mask_off , corxy inp_pos                                            );

//i.e: n_row = 5, m_col = 2, inputCoord_arr do as int A[2][5] ;
/**
 *
 *  corxy inputCoord_arr[2][5] = {{{11,114},{15,114},{19,114},{23,114},{27,114}},
 *                                {{11,133},{15,133},{19,133},{23,133},{27,133}}
 *                               };
 *  corxy inp_pos = {0,1};
 *  int output_OPT = OPT_mono_create_2d(5,2,inputCoord_arr,0,254,32,inp_pos);
 *  gotoxy(25 + 8,1); //whatever number you like
 *  printf("The number u choose is %d",output_OPT);
 *
 *
 */



#endif // CON_UTILS_H_INCLUDED
