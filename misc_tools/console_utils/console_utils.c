#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <conio.h>
#include "console_utils.h"

void gotoxy(int x, int y)
{
    printf("\x1B[%d;%df", x, y);
}

void any_key_exit(void)
{
    unsigned char ch1 = getch();
    if ((ch1 == 224) || (ch1 == 0)) ch1 = getch();
}

char input_characterkey_handling(void)
{
    unsigned char ch1 = getch();
    if ((ch1 == 224) || (ch1 == 0)) {
        ch1 = getch();
        return 0;
    };
    if (((ch1 >= 32) && (ch1 <= 126))  || ((ch1 == '\n') || (ch1 == '\r') || (ch1 == '\t')))
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
        };
    };
    if (ch1 == '\r')
        return 2;
    if (ch1 == '\x1B')
        return 5;
    return 0;
}

void input_arrow_key_quad(int *dirc_x, int *dirc_y)
{
    unsigned char ch1 = getch();
    if ((ch1 == 224) || (ch1 == 0)) {
        ch1 = getch();
        switch (ch1) {
        case 72:
            *dirc_x = -1;
            *dirc_y =  0;
            break;
        case 75:
            *dirc_x =  0;
            *dirc_y = -1;
            break;
        case 77:
            *dirc_x =  0;
            *dirc_y =  1;
            break;
        case 80:
            *dirc_x =  1;
            *dirc_y =  0;
            break;
        };
    };
    if (ch1 == '\r') {
        *dirc_x = 2;
        *dirc_y = 2;
    };
    if (ch1 == '\x1B') {
        *dirc_x = 5;
        *dirc_y = 5; //escape key
    };
    return ;
}

/////////////////////////////////////////////////////////

static void Draw_UpDo_Border(int n_row, int m_col, int row_info_arr[max_row], int col_info_arr[max_col], int base_x, int base_y) //updown , takes arr length of col
{
    int sum_col = 0, sum_row = 0;
    int mark_sum;
    for (int i = 1; i <= n_row; i++) sum_row += row_info_arr[i];
    for (int i = 1; i <= m_col; i++) sum_col += col_info_arr[i];
    sum_row += n_row + 0;
    sum_col += m_col + 1;

    //print up part

    gotoxy(base_x,1 + base_y);
    printf("%lc",218);
    for (int i = 2; i <= sum_col - 1; i++) printf("%lc",196);
    printf("%lc",191);

    mark_sum = 1;
    for (int i = 1; i <= m_col - 1; i++) {
        mark_sum += col_info_arr[i] + 1;
        gotoxy(base_x, mark_sum + base_y);
        printf("%lc",194);
    };

    //print down part
    gotoxy(sum_row + base_x,1 + base_y);
    printf("%lc",192);
    for (int i = 2; i <= sum_col - 1; i++) printf("%lc",196);
    printf("%lc",217);

    mark_sum = 1;
    for (int i = 1; i <= m_col - 1; i++) {
        mark_sum += col_info_arr[i] + 1;
        gotoxy(sum_row + base_x, mark_sum + base_y);
        printf("%lc",193);
    };
    printf("\n");
}

static void Draw_Hori_Border(int n_row, int m_col, int row_info_arr[max_row], int col_info_arr[max_col], int base_x, int base_y)
//horizontal ; takes arr length of col
{
    int sum = 0;
    int mark_sum;
    for (int i = 1; i <= m_col; i++) sum += col_info_arr[i];
    sum += m_col + 1;

    int base = 1 + row_info_arr[1];
    for (int i = 1; i <= n_row - 1; i++) {
        gotoxy(base + base_x, 1 + base_y);
        printf("%lc",195);
        for (int j = 2; j <= sum - 1; j++) printf("%lc",196);
        printf("%lc",180);

        mark_sum = 1;
        for (int j = 1; j <= m_col - 1; j++) {
            mark_sum += col_info_arr[j] + 1;
            gotoxy(base + base_x, mark_sum + base_y);
            printf("%lc",197);
        };

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
            mark_sum = 0;
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
    Draw_Hori_Border(n_row,m_col,row_info_arr,col_info_arr,base_x,base_y - 1);
    Draw_Vert_Border(n_row,m_col,row_info_arr,col_info_arr,base_x,base_y - 1);
    Draw_UpDo_Border(n_row,m_col,row_info_arr,col_info_arr,base_x,base_y - 1);
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

//////////////////////////////////////////////////////////////////
