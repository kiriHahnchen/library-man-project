#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../database/libman_database.h"
#include "../misc_tools/libman_tools.h"
#include "bookview_interface.h"

///////////////////////////////////

typedef struct {
    int index;
    int indexBook;
} display_BookData;

///////////////////////////////////

static display_BookData curr_displ_rB_arr[MAX_READED_BOOK];
static display_BookData temp_displ_rB_arr[MAX_READED_BOOK];

static int curr_displ_rB_num , //0-indexed
           curr_bprint_range , //0-indexed
           curr_blist_index  , //0-indexed
           currAcc_index     ; //0-indexed

/**< for menu */
char blistmenu_visibility[5] ;
char blistmenu_visibility_orig[5] ;

/**< for search */
//current status
int  search_status           ;
    //to see if currently in searching status
    //if 1
    /*
        censor     book edit, add, del functions
    */
    //if 0
    /*
        uncensored book edit, add, del functions
    */

//goal of searching
int search_opt_arr[3] ;

//searching keyword
char search_str[MAX_SIZE_STRING] ;

/////////////////////////////////////////////////////////////////////////////////////////////////

static void displ_rb_arr_init(void)
{
    for (int i = 0; i <= bookNumber; i++) {
        curr_displ_rB_arr[i].index     = i;
        curr_displ_rB_arr[i].indexBook = i;
    }
    curr_displ_rB_num = bookNumber;
}

//primitive functions, use to initialize the interface


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static void blist_intf_list_base(void)
{
    gotoxy(8,5);
    int col_info_arr[4]  = {0,11,76,16};
    int row_info_arr[12] = {0,1,1,1,1,1,1,1,1,1,1,1};
    Draw_Table        (11, 3,row_info_arr,col_info_arr,                8,5);

    Text_to_table_cell(1 , 1,row_info_arr,col_info_arr,"No."   ,-1,4,1,8,5);
    Text_to_table_cell(1 , 2,row_info_arr,col_info_arr,"Titles",-1,3,1,8,5);
    Text_to_table_cell(1 , 3,row_info_arr,col_info_arr,"Qty."  , 0,0,1,8,5);
    //drawtable and text_to_table counts from 1

    char tmpStr[5];
    char bprint_bound = ((curr_bprint_range * 10 + 10) > curr_displ_rB_num)     ?
                             (curr_bprint_range * 10 + curr_displ_rB_num % 10)  :
                             (curr_bprint_range * 10 + 10)                      ,
         bprint_base  =   curr_bprint_range * 10 ;

    for (register int i = 2; i <= 11; i++) {
        Text_to_table_cell(i,1,row_info_arr,col_info_arr,"     "                                                                    ,-1,5,1,8,5);
        Text_to_table_cell(i,2,row_info_arr,col_info_arr,"                                                                         ",-1,0,1,8,5);
        Text_to_table_cell(i,3,row_info_arr,col_info_arr,"            "                                                             ,-1,0,1,8,5);
    };

    int *tmpval = (int *) malloc(sizeof(int)) ;
    *tmpval = 11 ;
    for (register int i = 0; i <= 9; i++) {
        gotoxy(*tmpval,3) ;
        if (i != curr_blist_index)
            printf(" ");
        else
            printf("%lc",254);
        (*tmpval) += 2 ;
    } ;

    free(tmpval) ;
    //cleaning up

    int curr_row = 2;
    for (int i = bprint_base; i <= bprint_bound; i++) {
        memset(tmpStr,'\0',sizeof(tmpStr));
        sprintf(tmpStr,"%d",(char)curr_displ_rB_arr[i].index + 1);
        Text_to_table_cell(curr_row,1,row_info_arr,col_info_arr,tmpStr                                                ,-1,5,1,8,5);
        Text_to_table_cell(curr_row,2,row_info_arr,col_info_arr,base_Book[curr_displ_rB_arr[i].indexBook].bookTitle   ,-1,2,1,8,5);
        Text_to_table_cell(curr_row,3,row_info_arr,col_info_arr,base_Book[curr_displ_rB_arr[i].indexBook].bookQuantity, 0,0,1,8,5);
        if (++curr_row == 12) break;
    };
    //printing books
    if (blistmenu_visibility[4] == 1) {
    int bm_col[2] = {0,13} ,
        bm_row[2] = {0,1 } ;
    Draw_Table(1,1,bm_row,bm_col,26,116);
    Text_to_table_cell(1,1,bm_row,bm_col,"             ",0,0,1,26,116) ;
    int real_index = curr_bprint_range * 10 + curr_blist_index;
        real_index = curr_displ_rB_arr[real_index].indexBook  ;
    if (Bookmark_Find(base_Book[real_index],base_Acc[currAcc_index]) == 0)
        Text_to_table_cell(1,1,bm_row,bm_col,"Bookmark",0,0,1,26,116) ;
    else
        Text_to_table_cell(1,1,bm_row,bm_col,"Unbookmark",0,0,1,26,116) ;
    } ;
}

static void blist_intf_pagination_base(void)
{
    int output_pages = (curr_displ_rB_num + 1) / 10;
    if ((curr_displ_rB_num + 1) % 10 != 0) output_pages++ ;
    gotoxy(32,73); printf("[%lc][<]                      [>][%lc]",174,175);
    gotoxy(32,79);
    for (int i = 1; i <= 10; i++) {
        if (i <= output_pages) printf(" %d"    ,i);
        else
            if (i != 10)       printf(" %lc"   ,254);
            else               printf(" %lc%lc",254,254);
    };
    corxy inputCoord_arr[14] = {{33,74},{33,77},
                                {33,80},{33,82},{33,84},{33,86},{33,88},{33,90},{33,92},{33,94},{33,96},{33,98},
                                {33,102},{33,105}};
    for (register int i = 0; i <= 13; i++) {
        gotoxy(inputCoord_arr[i].x,inputCoord_arr[i].y) ;
        printf(" ") ;
    }
    gotoxy(inputCoord_arr[curr_bprint_range + 2].x,inputCoord_arr[curr_bprint_range + 2].y) ;
    printf("%lc",254) ;
}

static void blist_intf_searchbar_base(void)
{
    //searchbar
    gotoxy(2,5);
    int row_info_arr[2] = {0,1};
    int col_info_arr[4] = {0,18,69,16};
    Draw_Table        (1,3,row_info_arr,col_info_arr,                     2,5);
    Text_to_table_cell(1,1,row_info_arr,col_info_arr,"Searchbar :", 0,0,1,2,5);
    //text inside
    inputString_field_1d_print_simple(search_str,63,-1,3,28) ;

    //cancel or search - bar
    if (search_status == 1) {
        char search_or_cancel[] = "Cancel" ;
        Text_to_table_cell(1,3,row_info_arr,col_info_arr,search_or_cancel, 0,0,1,2,5);
    }
    else {
        char search_or_cancel[] = "Search" ;
        Text_to_table_cell(1,3,row_info_arr,col_info_arr,search_or_cancel, 0,0,1,2,5);
    }

    //options
    gotoxy(6,1);
    printf("                        By Title        By Quantity        By Metadata");
    corxy inputCoord_opt_arr[3] = {//{6,11}
                                   {6,22},
                                   {6,38},
                                   {6,57}
                                   };
    for (int i = 0; i <= 2; i++) {
        if (search_opt_arr[i]) {
            gotoxy(inputCoord_opt_arr[i].x,inputCoord_opt_arr[i].y);
            printf("%lc",219); //on
        }
        else {
            gotoxy(inputCoord_opt_arr[i].x,inputCoord_opt_arr[i].y);
            printf("%lc",176); //off
        }
    }; //current state of all
}

static void blist_intf_menu_base(void)
{
    int row_info_arr[2] = {0,1 };
    int col_info_arr[2] = {0,13};

    gotoxy(10,116); Draw_Table(1,1,row_info_arr,col_info_arr,10,116);
    Text_to_table_cell(1,1,row_info_arr,col_info_arr,"View Book",0,0,1,10,116);

    //
    gotoxy(14,116); Draw_Table(1,1,row_info_arr,col_info_arr,14,116);
    if (blistmenu_visibility[1])
        Text_to_table_cell(1,1,row_info_arr,col_info_arr,"+ Add Book",0,0,1,14,116);
    else {
        gotoxy(15,117);
        printf("%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc",219,219,219,219,219,219,219,219,219,219,219,219,219);
    };

     //
    gotoxy(18,116); Draw_Table(1,1,row_info_arr,col_info_arr,18,116);
    if (blistmenu_visibility[2])
        Text_to_table_cell(1,1,row_info_arr,col_info_arr,"- Del Book",0,0,1,18,116);
    else {
        gotoxy(19,117);
        printf("%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc",219,219,219,219,219,219,219,219,219,219,219,219,219);
    };

     //
    gotoxy(22,116); Draw_Table(1,1,row_info_arr,col_info_arr,22,116);
    if (blistmenu_visibility[3])
        Text_to_table_cell(1,1,row_info_arr,col_info_arr,"Edit Book",0,0,1,22,116);
    else {
        gotoxy(23,117);
        printf("%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc",219,219,219,219,219,219,219,219,219,219,219,219,219);
    };

     //
    gotoxy(26,116); Draw_Table(1,1,row_info_arr,col_info_arr,26,116);
    if (blistmenu_visibility[4])
        Text_to_table_cell(1,1,row_info_arr,col_info_arr,"Bookmark",0,0,1,26,116);
    else {
        gotoxy(27,117);
        printf("%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc%lc",219,219,219,219,219,219,219,219,219,219,219,219,219);
    };

    gotoxy(10,135); Draw_Table(1,1,row_info_arr,col_info_arr,10,135);
    Text_to_table_cell(1,1,row_info_arr,col_info_arr,"Sort A->Z",0,0,1,10,135);

    gotoxy(14,135); Draw_Table(1,1,row_info_arr,col_info_arr,14,135);
    Text_to_table_cell(1,1,row_info_arr,col_info_arr,"Sort Z->A",0,0,1,14,135);

    gotoxy(18,135); Draw_Table(1,1,row_info_arr,col_info_arr,18,135);
    Text_to_table_cell(1,1,row_info_arr,col_info_arr,"Sort Qty Up",0,0,1,18,135);

    gotoxy(22,135); Draw_Table(1,1,row_info_arr,col_info_arr,22,135);
    Text_to_table_cell(1,1,row_info_arr,col_info_arr,"Sort Qty Do",0,0,1,22,135);

    gotoxy(26,135); Draw_Table(1,1,row_info_arr,col_info_arr,26,135);
    Text_to_table_cell(1,1,row_info_arr,col_info_arr,"Main Menu",0,0,1,26,135);
}

static void blist_intf_noti_base(void)
{
    int row_info_arr[2] = {0,5} ,
        col_info_arr[2] = {0,32} ;

    Draw_Table(1,1,row_info_arr,col_info_arr,2,116) ;
}

static void blist_intf_base(void)
{
    system("cls");
    blist_intf_menu_base();
    blist_intf_list_base();
    blist_intf_pagination_base();
    blist_intf_searchbar_base();
    blist_intf_noti_base();
    gotoxy(3  ,  3); printf("%lc",176);
    gotoxy(9  ,  3); printf("%lc",176);
    gotoxy(32 , 71); printf("%lc",176);
    gotoxy(9  ,116); printf("%lc",176);
    //gotoxy();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//sub_main intf driver

static void blist_intf_noti(char inputString[5][32])
{
    int row_info_arr[2] = {0,5} ,
        col_info_arr[2] = {0,32} ;
    char cleanStr[32] = "" ;
    memset(cleanStr,32,sizeof(char) * 32) ;
    for (int i = 0; i <= 4; i++) {
        Text_to_table_cell(1,1,row_info_arr,col_info_arr,cleanStr      ,0,0,i + 1,2,116);
        Text_to_table_cell(1,1,row_info_arr,col_info_arr,inputString[i],0,0,i + 1,2,116);
    };
}

/**<  Bookmark tools */
static void blist_intf_menu_bookmark_add(int b_index)
{
    char *ta = base_Book[b_index].bookQuantity;
    int tmp_val = atoi(ta);

    if (tmp_val == 0)  {
        char inputStr[5][32] = {"","Add to Bookmark Failed!","","Quantity unchanged",""} ;
        blist_intf_noti(inputStr) ;
        any_key_exit();

        memset(inputStr[1],0,32 * sizeof(char));
        memset(inputStr[3],0,32 * sizeof(char));
        blist_intf_noti(inputStr);
    }
    else {
        Bookmark_Add(base_Book[b_index],&base_Acc[currAcc_index]);
        char inputStr[5][32] = {"","Add to Bookmark Success!","","Quantity decrease",""} ;
        blist_intf_noti(inputStr) ;
        any_key_exit();
        memset(ta,0,sizeof(ta) - 1);
        sprintf(ta,"%d",--tmp_val);
        blist_intf_list_base();
        memset(inputStr[1],0,32 * sizeof(char));
        memset(inputStr[3],0,32 * sizeof(char));
        blist_intf_noti(inputStr);
        //redraw button
        int bm_col[2] = {0,13} ,
        bm_row[2] = {0,1 } ;
        Draw_Table(1,1,bm_row,bm_col,26,116);
        Text_to_table_cell(1,1,bm_row,bm_col,"             ",0,0,1,26,116) ;
        Text_to_table_cell(1,1,bm_row,bm_col,"Unbookmark",0,0,1,26,116) ;
    }
}
static void blist_intf_menu_bookmark_del(int b_index)
{
    char *ta = base_Book[b_index].bookQuantity;
    int tmp_val = atoi(ta);

    Bookmark_Del_single(base_Book[b_index],&base_Acc[currAcc_index]);
    char inputStr[5][32] = {"","Delete from Bookmark Success!","","Quantity increase",""} ;
    blist_intf_noti(inputStr) ;
    any_key_exit();

    memset(ta,0,sizeof(ta) - 1);
    sprintf(ta,"%d",++tmp_val);
    blist_intf_list_base();
    memset(inputStr[1],0,32 * sizeof(char));
    memset(inputStr[3],0,32 * sizeof(char));
    blist_intf_noti(inputStr);
    //redraw button
    int bm_col[2] = {0,13} ,
    bm_row[2] = {0,1 } ;
    Draw_Table(1,1,bm_row,bm_col,26,116);
    Text_to_table_cell(1,1,bm_row,bm_col,"             ",0,0,1,26,116) ;
    Text_to_table_cell(1,1,bm_row,bm_col,"Bookmark",0,0,1,26,116) ;
}
static void blist_intf_menu_book_del(int b_index)
{
    Bookmark_Del_all(base_Book[b_index]);  //del all BM
    base_Book_del(b_index);               //del book
    displ_rb_arr_init();                 //update curr

    char inputStr[5][32] = {"","Delete Book Success!","","Press any key to continue",""} ;
    blist_intf_noti(inputStr) ;
    any_key_exit();
    memset(inputStr[1],0,32 * sizeof(char));
    memset(inputStr[3],0,32 * sizeof(char));
    blist_intf_noti(inputStr);
    //display changes

    curr_blist_index--;
    if (curr_blist_index == -1) {
        curr_bprint_range--;
        if (curr_bprint_range == -1) {
            curr_bprint_range = 0;
            curr_blist_index  = 0;
        }
        else
            curr_blist_index  = 9;
    };
    blist_intf_pagination_base();
    blist_intf_list_base();
}

static void blist_intf_menu_book_add(void){
    system("cls");
    printf("\x1B[?25h"); //show cursor
    BookData tmpBook ;
    if (bview_for_assignment_add(&tmpBook) == 1) {
        base_Book_add(tmpBook) ;
        curr_displ_rB_num++;
    } ;
    //display changes
    displ_rb_arr_init() ; //update changes in number
    blist_intf_base();
    printf("\x1B[?25l"); //hide cursor
}

static void blist_intf_menu_book_edit(int b_index){

    system("cls");
    printf("\x1B[?25h"); //show cursor
    bview_for_assignment_edit(&base_Book[b_index]) ;
    //display changes
    //displ_rb_arr_init() ; no need to since still same
    blist_intf_base();
    printf("\x1B[?25l"); //hide cursor
}

/**< Sorter collection*/
int sort_az_up(const void *a, const void *b)
{
    display_BookData book_a = *(display_BookData *)a ;
    display_BookData book_b = *(display_BookData *)b ;
    int val = strcmp(base_Book[book_a.indexBook].bookTitle,base_Book[book_b.indexBook].bookTitle);
    return (val == 0) ? 0 : (val < 0) ? -1 : 1;
}
int sort_az_do(const void *a, const void *b)
{
    display_BookData book_a = *(display_BookData *)a ;
    display_BookData book_b = *(display_BookData *)b ;
    int val = strcmp(base_Book[book_a.indexBook].bookTitle,base_Book[book_b.indexBook].bookTitle);
    return (val == 0) ? 0 : (val > 0) ? -1 : 1;
}
int sort_qty_up(const void *a, const void *b)
{
    display_BookData book_a = *(display_BookData *)a ;
    display_BookData book_b = *(display_BookData *)b ;
    int val_a = atoi(base_Book[book_a.indexBook].bookQuantity);
    int val_b = atoi(base_Book[book_b.indexBook].bookQuantity);
    return (val_a == val_b) ? 0 : (val_a < val_b) ? -1 : 1;
}
int sort_qty_do(const void *a, const void *b)
{
    display_BookData book_a = *(display_BookData *)a ;
    display_BookData book_b = *(display_BookData *)b ;
    int val_a = atoi(base_Book[book_a.indexBook].bookQuantity);
    int val_b = atoi(base_Book[book_b.indexBook].bookQuantity);
    return (val_a == val_b) ? 0 : (val_a > val_b) ? -1 : 1;
}
/**< Sorting intf */
static void blist_intf_sort(int n_OPT)
{
    switch (n_OPT) {
    case 5:
        qsort(curr_displ_rB_arr,curr_displ_rB_num + 1,sizeof(display_BookData),sort_az_up) ;
        break;
    case 6:
        qsort(curr_displ_rB_arr,curr_displ_rB_num + 1,sizeof(display_BookData),sort_az_do) ;
        break;
    case 7:
        qsort(curr_displ_rB_arr,curr_displ_rB_num + 1,sizeof(display_BookData),sort_qty_up) ;
        break;
    case 8:
        qsort(curr_displ_rB_arr,curr_displ_rB_num + 1,sizeof(display_BookData),sort_qty_do) ;
        break;
    } ;
    //refresh display
    for (int i = 0; i <= curr_displ_rB_num; i++) {
        curr_displ_rB_arr[i].index = i;
    }
    blist_intf_list_base();
    return ;
}

// TODO (Anh Hai#1#): not done, add view book, edit book
//

static int blist_intf_menu(void)
{
    int n_OPT = 0;
    corxy inputCoord_arr[2][5] = {{{11,114},{15,114},{19,114},{23,114},{27,114}},
                                  {{11,133},{15,133},{19,133},{23,133},{27,133}}
                                 };
    corxy inp_pos ;
    for (register int i = 1; i <= 4; i++)
        if (!blistmenu_visibility[i]) inputCoord_arr[0][i].x = 0;

    curr_bprint_range += 0;
    curr_blist_index  += 0;
    int tmp_index;
    do {
        inp_pos.x = n_OPT / 5;
        inp_pos.y = n_OPT % 5;
        n_OPT = OPT_mono_create_2d(5,2,inputCoord_arr,0,254,32,inp_pos);
        switch (n_OPT) {
        case 0:
            //view_book
            tmp_index = curr_bprint_range * 10 + curr_blist_index ;
            tmp_index = curr_displ_rB_arr[tmp_index].indexBook;
            bview_for_assignment_view(base_Book[tmp_index]) ;
            blist_intf_base();
            break;
        case 1:
            //add
             blist_intf_menu_book_add() ;
            break;
        case 2:
            //del
            //able to del = > is in admin
            tmp_index = curr_bprint_range * 10 + curr_blist_index ;
            tmp_index = curr_displ_rB_arr[tmp_index].indexBook;
            blist_intf_menu_book_del(tmp_index) ;
            break;
        case 3:
            //edit
            tmp_index = curr_bprint_range * 10 + curr_blist_index ;
            tmp_index = curr_displ_rB_arr[tmp_index].indexBook;
            blist_intf_menu_book_edit(tmp_index) ;
            break;
        case 4:
            tmp_index = curr_bprint_range * 10 + curr_blist_index ;
            tmp_index = curr_displ_rB_arr[tmp_index].indexBook;
            if (Bookmark_Find(base_Book[tmp_index],base_Acc[currAcc_index]) == 1)
                blist_intf_menu_bookmark_del(tmp_index) ;
            else
                blist_intf_menu_bookmark_add(tmp_index);
            break;
        default:
            if ((n_OPT >= 5) && (n_OPT <= 8))
                blist_intf_sort(n_OPT) ;
            break;
        }
    } while ((n_OPT >= 0) && (n_OPT < 9));

    int *tmpval = (int *) malloc(sizeof(int)) ;
    *tmpval = 11 ;
    for (register int i = 0; i <= 4; i++) {
        gotoxy(*tmpval,114) ; printf(" ");
        gotoxy(*tmpval,133) ; printf(" ");
        (*tmpval) += 4 ;
    } ;
    free(tmpval) ;

    return (n_OPT == 9) ? 0 : 1;
}

static void blist_intf_pagination(void)
{
    int n_OPT = curr_bprint_range , tmp_OPT = (curr_bprint_range + 2);
    int tmp_index_full = curr_blist_index ,
        tmp_index_miss = ((curr_displ_rB_num % 10) < curr_blist_index ) ? curr_displ_rB_num % 10 : curr_blist_index ;

    corxy inputCoord_arr[14] = {{33,74},{33,77},
                                {33,80},{33,82},{33,84},{33,86},{33,88},{33,90},{33,92},{33,94},{33,96},{33,98},
                                {33,102},{33,105}};

    int max_pg = (curr_displ_rB_num + 1) / 10;
    if ((curr_displ_rB_num + 1) % 10 != 0) max_pg++;
    //counts froms 1
    for (register int i = 0; i < 10 - max_pg; i++) {
        inputCoord_arr[i + 2 + max_pg].x = 0;
    };
    do {
        tmp_OPT = OPT_mono_create_1d(14,tmp_OPT,inputCoord_arr,1,254,32,2);
        if (tmp_OPT != -1) {
            switch (tmp_OPT) {
            case 0 : n_OPT =  0                               ; break;
            case 1 : n_OPT -= (n_OPT == 0) ? 0 : 1            ; break;
            case 12: n_OPT += (n_OPT == max_pg - 1) ? 0 : 1   ; break;
            case 13: n_OPT = max_pg  - 1                      ; break;
            default: n_OPT = tmp_OPT - 2                      ; break;
            };
            if (n_OPT == max_pg - 1)
                curr_blist_index = tmp_index_miss ;
            else
                curr_blist_index = tmp_index_full ;
            curr_bprint_range = n_OPT ;
            blist_intf_list_base();
        }
    } while (tmp_OPT != -1) ;

    blist_intf_list_base() ;
    blist_intf_pagination_base();
}

static void blist_intf_list(void)
{
    corxy inputCoord_arr[10] = {{11,3},{13,3},{15,3},{17,3},{19,3},{21,3},{23,3},{25,3},{27,3},{29,3}};
    int n_OPT = curr_blist_index ,
        tmp_OPT = n_OPT ;
    if (curr_bprint_range == curr_displ_rB_num / 10)
        for (register int i = 0 ; i <= 9 ; i++) {
            if (i > curr_displ_rB_num % 10)
                inputCoord_arr[i].x = 0 ;
        };
    //init the accessible range

    n_OPT = OPT_mono_create_1d(10,n_OPT,inputCoord_arr,1,254,32,1) ;
    if (n_OPT == -1)
        curr_blist_index = tmp_OPT ;
    else
        curr_blist_index = n_OPT ;
    blist_intf_list_base() ;
}

/**< Searching intf */

static void blist_intf_search_search_or_cancel(int *search_status, int search_opt_arr[3])
{
    if (!((search_opt_arr[0] || search_opt_arr[1]) || search_opt_arr[2]))
        return ;

    (*search_status) = ((*search_status) + 1) % 2 ;
    int row_info_arr[2] = {0,1};
    int col_info_arr[4] = {0,18,69,16};
    if (*search_status == 1) {
        char search_or_cancel[] = "Cancel" ;
        Text_to_table_cell(1,3,row_info_arr,col_info_arr,search_or_cancel, 0,0,1,2,5);
        //censor
        strcpy(blistmenu_visibility_orig,blistmenu_visibility) ;
        memset(blistmenu_visibility + 1,0,3) ;
        curr_bprint_range = 0;
        curr_blist_index  = 0;
        //invoke searching func
        //searching ....
        //copy content of curr
        for (int i = 0; i <= bookNumber; i++) {
            temp_displ_rB_arr[i].index     = curr_displ_rB_arr[i].index;
            temp_displ_rB_arr[i].indexBook = curr_displ_rB_arr[i].indexBook;
        }
        int count_index = -1;
        for (int i = 0; i <= curr_displ_rB_num; i++) {
            int real_index = temp_displ_rB_arr[i].indexBook ;
            if (sfunc_normalSearch_for_Assignment(base_Book[real_index],search_str,search_opt_arr)) {
                count_index++;
                curr_displ_rB_arr[count_index].index = count_index;
                curr_displ_rB_arr[count_index].indexBook = real_index;
            } ;
        } ;
        curr_displ_rB_num = count_index;
        //refresh the page
        blist_intf_base();

    }
    else {
        char search_or_cancel[] = "Search" ;
        Text_to_table_cell(1,3,row_info_arr,col_info_arr,search_or_cancel, 0,0,1,2,5);
        //uncensor
        strcpy(blistmenu_visibility,blistmenu_visibility_orig) ;
        curr_bprint_range = 0;
        curr_blist_index  = 0;
        //restore orig state
        displ_rb_arr_init();
        //reset the page
        blist_intf_base();

    } ;
}

static void blist_intf_search_search_options(int search_opt_arr[3])
{
    corxy inputCoord_arr[3] = {//{6,11},
                               {6,22},
                               {6,38},
                               {6,57}
                               };
    int n_OPT = 0;
    for (int i = 0; i <= 2; i++) {
        if (search_opt_arr[i]) {
            n_OPT = i;
            break;
        } ;
    } ;
    int tmp_OPT = n_OPT ;
    n_OPT = OPT_mono_create_1d(3,n_OPT,inputCoord_arr,1,219,176,2);
    if (n_OPT == -1) {
        n_OPT = tmp_OPT ;
    } ;
    for (int i = 0; i <= 2; i++) {
        if (i == n_OPT) {
            search_opt_arr[i] = 1;
        }
        else
            search_opt_arr[i] = 0;
    } ;
}

static void blist_intf_search_searchbar(void)
{
    char validChar_set[128] = "";
    for (int i = 0; i <= 94; i++) validChar_set[i] = i + 32 ;
    inputString_field_1d(search_str,search_str,validChar_set,63,MAX_SIZE_STRING,-1,3,28) ;
}

static void blist_intf_search(void)
{
    corxy inputCoord_arr[3] = {{3,8},{6,20},{3,98}};
    int n_OPT = 0 ;
    do {
        n_OPT = OPT_mono_create_1d(3,n_OPT,inputCoord_arr,0,254,32,1);
        switch (n_OPT) {
        case 0:
            blist_intf_search_searchbar();
            break;
        case 1:
            blist_intf_search_search_options(search_opt_arr);
            //to clarify
            break;
        case 2:
            blist_intf_search_search_or_cancel(&search_status,search_opt_arr);
            if (search_status) {
                inputCoord_arr[1].x = 0;
            }
            else {
                inputCoord_arr[1].x = 6;
            }
            break;
        }
    } while (n_OPT != -1) ;
}


//main

void blist_intf(int inputAcc_index, char input_blistmenu_visibility[5])
{
    //init display
    displ_rb_arr_init(); //init
    currAcc_index = inputAcc_index;
    curr_bprint_range = 0;
    curr_blist_index  = 0;
    memcpy(blistmenu_visibility,input_blistmenu_visibility,5) ;

    //search init sec
    search_status = 0;
    memset(search_str,0,MAX_SIZE_STRING) ;
    for (register int i = 0; i <= 2; i++)
        search_opt_arr[i] = 0 ;
    search_opt_arr[0] = 1;
    //main init sec
    corxy inputCoord_arr[4] = {{3,3},{9,3},{32,71},{9,116}};
    int n_OPT = 0;
    int flag = 1;

    //main
    blist_intf_base();
    do {
        n_OPT = OPT_mono_create_1d(4,n_OPT,inputCoord_arr,0,219,176,1);
        switch (n_OPT) {
        case 0:
            //search bar
            blist_intf_search();
            break;
        case 1:
            blist_intf_list();
            break;
        case 2:
            blist_intf_pagination();
            break;
        case 3:
            flag = blist_intf_menu();
            break;
        };
    } while ((flag != 0) && (n_OPT != -1));
}
