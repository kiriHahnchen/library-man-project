#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "con_utils.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void gotoxy(int row, int col)
{
    printf("\x1B[%d;%df", row, col);
}

void any_key_exit(void)
{
    unsigned char ch1 = getch();
    if ((ch1 == 224) || (ch1 == 0)) ch1 = getch();
}

char input_displayable_ascii_character_handling(void)
{
    unsigned char ch1 = getch();
    if ((ch1 == 224) || (ch1 == 0)) {
        ch1 = getch();
        switch (ch1) {
        case 75:
            return -1;
        case 77:
            return 1;
        };
    };
    if (((ch1 >= 32) && (ch1 <= 126))  || ((ch1 == '\n') || (ch1 == '\r') || (ch1 == '\t') || (ch1 == '\x1B') || (ch1 == '\b')))
        return ch1;
    else
        return 0;
}

int input_arrow_key_vert(void)
{
    unsigned char ch1 = getch();
    if ((ch1 == 224) || (ch1 == 0)) {
        ch1 = getch();
        switch (ch1) {
        case 72:
            return -1;
        case 80:
            return 1;
        case 75: return 3;
        case 77: return 3;
        };
    };
    if (ch1 == '\r')
        return 2;
    if (ch1 == '\x1B')
        return 5;
    return 0;
}

int input_arrow_key_hori(void)
{
    unsigned char ch1 = getch();
    if ((ch1 == 224) || (ch1 == 0)) {
        ch1 = getch();
        switch (ch1) {
        case 75:
            return -1;
        case 77:
            return 1;
        case 72: return 3;
        case 80: return 3;
        };
    };
    if (ch1 == '\r')
        return 2;
    if (ch1 == '\x1B')
        return 5;
    return 0;
}

int input_arrow_key_quad(int *dirc_x, int *dirc_y)
{
    unsigned char ch1 = getch();
    int hori_or_vert = 0;
    if ((ch1 == 224) || (ch1 == 0)) {
        ch1 = getch();
        switch (ch1) {
        case 72:
            *dirc_x = -1;
            //*dirc_y =  0; dirc_y no change
            hori_or_vert = 2;
            break;
        case 75:
            //*dirc_x =  0;
            *dirc_y = -1;
            hori_or_vert = 1;
            break;
        case 77:
            //*dirc_x =  0;
            *dirc_y =  1;
            hori_or_vert = 1;
            break;
        case 80:
            *dirc_x =  1;
            //*dirc_y =  0;
            hori_or_vert = 2;
            break;
        };
    };
    if (ch1 == '\r') {
        hori_or_vert = 3;
    };
    if (ch1 == '\x1B') {
        hori_or_vert = 5;
    };
    return hori_or_vert;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void Draw_UpDo_Border(int n_row, int m_col, int row_info_arr[max_row], int col_info_arr[max_col], int base_x, int base_y)
//updown , takes arr length of col
{
    int sum_col = 0, sum_row = 0;
    for (int i = 1; i <= n_row; i++) {sum_row += row_info_arr[i];}; sum_row += n_row + 1;
    for (int i = 1; i <= m_col; i++) {sum_col += col_info_arr[i];}; sum_col += m_col + 1;

    //print up part

    gotoxy(base_x,base_y);
    printf("%lc",218);
    for (int i = 1; i <= m_col; i++) {
        for (int j = 1; j <= col_info_arr[i]; j++) {
            printf("%lc",196);
        };
        printf("%lc",194);
    };
    printf("\b%lc",191);

    //print down part
    gotoxy(sum_row + base_x - 1,base_y);
    printf("%lc",192);
    for (int i = 1; i <= m_col; i++) {
        for (int j = 1; j <= col_info_arr[i]; j++) {
            printf("%lc",196);
        };
        printf("%lc",193);
    };
    printf("\b%lc",217);
}

static void Draw_Hori_Border(int n_row, int m_col, int row_info_arr[max_row], int col_info_arr[max_col], int base_x, int base_y)
//horizontal ; takes arr length of col
{
    int sum = 0;
    for (int i = 1; i <= m_col; i++) {sum += col_info_arr[i];};
    sum += m_col + 1;

    int base = row_info_arr[1] + 1;
    for (int i = 1; i <= n_row - 1; i++) {
        gotoxy(base + base_x, base_y);
        printf("%lc",195);
        for (int j = 1; j <= m_col; j++) {
            for (int k = 1; k <= col_info_arr[j]; k++) {
                printf("%lc",196);
            };
            printf("%lc",197);
        };
        printf("\b%lc",180);

        base += row_info_arr[i + 1] + 1;
    };
}

static void Draw_Vert_Border(int n_row, int m_col, int row_info_arr[max_row], int col_info_arr[max_col], int base_x, int base_y)
//vertical ; takes arr length of col
{
    int sum = 0;
    int mark_sum;
    for (int i = 1; i <= m_col; i++) sum += col_info_arr[i];
    sum += m_col + 1;

    int base = 1;
    for (int i = 1; i <= n_row; i++) {

        for (int j = 1; j <= row_info_arr[i]; j++) {
            mark_sum = -1;
            for (int k = 0; k <= m_col; k++) {
                mark_sum += col_info_arr[k] + 1;
                gotoxy(base + base_x, mark_sum + base_y); //because next line will continue printing 179 character, so base++
                printf("%lc",179);
            };
            base++;
        };

        base ++;
    };
}

void Draw_Table(int n_row, int m_col, int row_info_arr[max_row], int col_info_arr[max_col], int base_x, int base_y) // takes n of row, m of col, arr length of col
{
    Draw_Hori_Border(n_row,m_col,row_info_arr,col_info_arr,base_x,base_y);
    Draw_Vert_Border(n_row,m_col,row_info_arr,col_info_arr,base_x,base_y);
    Draw_UpDo_Border(n_row,m_col,row_info_arr,col_info_arr,base_x,base_y);
}

static int Text_Indent_Pos(int col_len, size_t str_len, int indent_pref, int tab_len)
//takes length of column, length of input string=> returns where to print
{
    //-1 left, 0 middle, 1 right
    int pos = 0;
    switch (indent_pref) {
    case 0:
        pos = (col_len / 2) - (int) (str_len / 2);
        break;
    case 1:
        if (str_len > (size_t) col_len - 2)
            pos = 0;
        else
            pos = col_len - str_len;
        break;
    case -1:
        pos = tab_len;
        break;
    };
    return pos;
}

void Text_to_table_cell(int n_row, int m_col, int row_info_arr[max_row], int col_info_arr[max_col], char inputString[MAX_SIZE_STRING],
                        int indent_pref, int tab_len, int row_line, int base_x, int base_y)
//info in r,c format, length of column, input string, indent preference
{
    char outputString[MAX_SIZE_STRING] = "";

    int mark_sum_col = 0;
    for (int i = 0; i <= m_col - 1; i++) {
        mark_sum_col += col_info_arr[i] + 1;
    };
    mark_sum_col++;

    int mark_sum_row = 0;
    for (int i = 0; i <= n_row - 1; i++) {
        mark_sum_row += row_info_arr[i] + 1;
    };
    mark_sum_row += row_line;

    if (strlen(inputString) > (size_t) col_info_arr[m_col] - tab_len) {
        strncpy(outputString,inputString,col_info_arr[m_col] - tab_len);
        memset(outputString + (col_info_arr[m_col] - 4),'.',3);
        outputString[col_info_arr[m_col]] = '\0';
    }
    else {
        strcpy(outputString,inputString);
    }
    int outputStr_len = Text_Indent_Pos(col_info_arr[m_col],strlen(inputString),indent_pref,tab_len);

    gotoxy(mark_sum_row + base_x - 1, mark_sum_col + outputStr_len + base_y - 1);
    printf("%s",outputString);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void OPT_print_mask(corxy prev_coord, corxy curr_coord, int mask_on, int mask_off)
{
    gotoxy(prev_coord.x,prev_coord.y); printf("%lc",mask_off);
    gotoxy(curr_coord.x,curr_coord.y); printf("%lc",mask_on );
}

static void OPT_print_mask_envelope(corxy prev_coord, corxy curr_coord)
{
    gotoxy(prev_coord.x,prev_coord.y + 1); printf(" \b\b\b ");
    gotoxy(curr_coord.x,curr_coord.y + 1); printf("]\b\b\b[");
}

int OPT_mono_create_1d(int n_OPT, int input_OPT, corxy inputCoord_arr[n_OPT], int trailMode, int mask_on, int mask_off, int dirc)
{
    int (*dirc_handl)(void);
    if ((dirc == 1) || (dirc == 2)) {
        if (dirc == 2) {dirc_handl = input_arrow_key_hori;}
        else           {dirc_handl = input_arrow_key_vert;}
        ;
    }
    else {
        return -1; //error occured, no changes;
    };

    int inp_dirc;
    int curr_OPT = input_OPT, prev_OPT = curr_OPT;
    do {
        OPT_print_mask(inputCoord_arr[prev_OPT],inputCoord_arr[curr_OPT],mask_on,mask_off);
        inp_dirc = dirc_handl();
        prev_OPT = curr_OPT;
        switch (inp_dirc) {
        case 1:
            do { curr_OPT = (curr_OPT + 1) % n_OPT; }
            while (inputCoord_arr[curr_OPT].x == 0);
            break;
        case -1:
            do { curr_OPT = (curr_OPT + n_OPT - 1) % n_OPT; }
            while (inputCoord_arr[curr_OPT].x == 0);
            break;
        };
    } while ((inp_dirc != 2) && (inp_dirc != 5));

    //below is when inp_dirc == 5;

    if (trailMode == 0) {
        OPT_print_mask(inputCoord_arr[curr_OPT],inputCoord_arr[curr_OPT],mask_off,mask_on);
    };
    //OPT_print_mask(inputCoord_arr[curr_OPT],inputCoord_arr[curr_OPT],mask_on,mask_on);
    //this is dont need, since you still left a cursor when loop break

    return (inp_dirc == 5) ? -1 : curr_OPT;
}

void OPT_multi_create_1d_withHierarchie(int n_OPT, corxy inputCoord_arr[n_OPT],int inputHierarchie[n_OPT][n_OPT] ,
                                        int mask_on, int mask_off, int dirc, int output_OPTs[n_OPT]              )
{
    int (*dirc_handl)(void);
    if ((dirc == 1) || (dirc == 2)) {
        if (dirc == 2) {dirc_handl = input_arrow_key_hori;}
        else           {dirc_handl = input_arrow_key_vert;}
        ;
    }
    else {
        return ; //error occured, no changes; no value
    };

    int inp_dirc = 0;
    int curr_OPT = 0, prev_OPT = curr_OPT;
    while (inp_dirc != 5) {
        for (int i = 0; i < n_OPT; i++) {
            if (output_OPTs[i]) {
                gotoxy(inputCoord_arr[i].x,inputCoord_arr[i].y);
                printf("%lc",mask_off);
            }
            else {
                gotoxy(inputCoord_arr[i].x,inputCoord_arr[i].y);
                printf("%lc",mask_on);
            }
        }; //current state of all

        OPT_print_mask_envelope(inputCoord_arr[prev_OPT],inputCoord_arr[curr_OPT]);
        inp_dirc = dirc_handl();
        prev_OPT = curr_OPT;
        switch (inp_dirc) {
        case  1: curr_OPT = (curr_OPT + 1) % n_OPT;         break;
        case -1: curr_OPT = (curr_OPT + n_OPT - 1) % n_OPT; break;
        case  2:
            output_OPTs[curr_OPT] = (output_OPTs[curr_OPT] + 1) % 2;
            if (output_OPTs[curr_OPT]) {
                //check hierarchie when output_opt == 1
                for (int i = 0; i < n_OPT; i++)
                    output_OPTs[i] = (inputHierarchie[curr_OPT][i]) ? 1 : output_OPTs[i];
            };
            break;
        };
    };

    //this is last check before exit the prog
    gotoxy(inputCoord_arr[curr_OPT].x,inputCoord_arr[curr_OPT].y + 1); printf(" \b\b\b ");
    for (int i = 0; i < n_OPT; i++) {
        if (output_OPTs[i]) {
            //check hierarchie when output_opt == 1
            for (int j = 0; j < n_OPT; j++) {
                if (inputHierarchie[i][j]) {
                    output_OPTs[j] = 1;
                };
            };
        };
    };
    for (int i = 0; i < n_OPT; i++) {
        if (output_OPTs[i]) {
            gotoxy(inputCoord_arr[i].x,inputCoord_arr[i].y);
            printf("%lc",mask_off);
        }
        else {
            gotoxy(inputCoord_arr[i].x,inputCoord_arr[i].y);
            printf("%lc",mask_on);
        }
    }; //current state of all
    return ; //end prog, no return value
}

                                                                          //row    //col
int OPT_mono_create_2d(int n_OPT_row, int m_OPT_col, corxy inputCoord_arr[m_OPT_col][n_OPT_row], int trailMode ,
                       int mask_on  , int mask_off , corxy inp_pos                                             )
{
    int (*dirc_handl)(int *dirc_x, int *dirc_y) = input_arrow_key_quad; //shorten

    corxy inp_dirc = {.x = 0, .y = 0};

    corxy curr_OPT = {.x = inp_pos.y, .y = inp_pos.x} ,
          prev_OPT = {.x = inp_pos.y, .y = inp_pos.x} ;

    int hori_or_vert;
    do {
        OPT_print_mask(inputCoord_arr[prev_OPT.y][prev_OPT.x],
                       inputCoord_arr[curr_OPT.y][curr_OPT.x], mask_on,mask_off);
        hori_or_vert = dirc_handl(&(inp_dirc.x),&(inp_dirc.y));
        prev_OPT = curr_OPT;
        //handle verti, meaning row
        if (hori_or_vert == 2) {
            if (inp_dirc.x == 1)
                do { curr_OPT.x = (curr_OPT.x + 1) % n_OPT_row; }
                while (inputCoord_arr[curr_OPT.y][curr_OPT.x].x == 0);
            else
                do { curr_OPT.x = (curr_OPT.x + n_OPT_row - 1) % n_OPT_row; }
                while (inputCoord_arr[curr_OPT.y][curr_OPT.x].x == 0);
        };

        //handle hori, meaning col
        if (hori_or_vert == 1) {
            if (inp_dirc.y == 1)
                do { curr_OPT.y = (curr_OPT.y + 1) % m_OPT_col; }
                while (inputCoord_arr[curr_OPT.y][curr_OPT.x].x == 0);
            else
                do { curr_OPT.y = (curr_OPT.y + m_OPT_col - 1) % m_OPT_col;}
                while (inputCoord_arr[curr_OPT.y][curr_OPT.x].x == 0);
        };

    } while ((hori_or_vert != 3) && (hori_or_vert != 5));

    if (hori_or_vert == 5) return -1; //no changes

    if (trailMode == 0) {
        OPT_print_mask(inputCoord_arr[curr_OPT.y][curr_OPT.x],
                       inputCoord_arr[curr_OPT.y][curr_OPT.x],mask_off,mask_off);
    };

    //collapse curr_x, curr_y into single OPT value

    return curr_OPT.x + ((curr_OPT.y) * n_OPT_row);
}


//future 2d implement
