#include <stdio.h>
#include <stdlib.h>

#include "../misc_tools/libman_tools.h"

static void option_intf_base_menu(int not_enable_rem)
{
    system("cls");
    printf("\x1B[?25l"); //hide cursor
    int base_row = 2;
    gotoxy(base_row, 4); printf("OPTION"); base_row += 2;

    if (not_enable_rem == 0) {
    gotoxy(base_row, 4); printf("[   ]   1. Remembered this account");
                                                       ; base_row += 2;
    }
    else {
    gotoxy(base_row, 4); printf("[%lc%lc%lc]   1. Remembered this account",219,219,219);
                                                       ; base_row += 2;
    }

    gotoxy(base_row, 4); printf("[   ]   2. Return to main menu with changes");
                                                       ; base_row += 2;
    gotoxy(base_row, 4); printf("[   ]   3. Return to main menu, no changes (ESCAPE_KEY)");
}

/*
/////////////////////////////////////////////////

            The main function of this
                     source

/////////////////////////////////////////////////
*/

void option_intf(int *rememberStatus, int *remAcc_index, const int currAcc_index)
{
    int option_menu_OPT;
    int curr_remSta = (*rememberStatus == 0) ? 1 : 0 ;
    int tmp_remSta;
    int not_enable_rem;
    corxy inputCoord_arr_big    [3] = {{4,6},{6,6},{8,6}};
    corxy inputCoord_arr_small  [2] = {{4,44},{4,61}};

    if ((*remAcc_index == currAcc_index          ) ||
        (*remAcc_index == -1                     ) ||
        (base_Acc[currAcc_index].accPriority == 2) ){ //admin is godmode lol
        option_menu_OPT = 0;
        not_enable_rem = 0;
    }
    else {
        inputCoord_arr_big[0].x = 0;
        inputCoord_arr_big[0].y = 0; //will skip
        option_menu_OPT = 1;
        not_enable_rem = 1;
    };

    option_intf_base_menu(not_enable_rem);
    do {
        option_menu_OPT = OPT_mono_create_1d(3,option_menu_OPT,inputCoord_arr_big,0,35,32,1);
        switch (option_menu_OPT) {
        case 0:
            gotoxy(4, 42); printf("[   ]   ON   /   [   ]   OFF");
            tmp_remSta = curr_remSta;
            curr_remSta = OPT_mono_create_1d(2,curr_remSta,inputCoord_arr_small,0,35,32,1);
            gotoxy(4, 42); printf("                            ");
            curr_remSta = (curr_remSta == -1) ? tmp_remSta : curr_remSta;
            break;
        case 1:
            if (not_enable_rem == 0) {
                *rememberStatus = (curr_remSta == 0) ? 1: 0 ;
                if (curr_remSta == 0)
                    *remAcc_index = currAcc_index;
                else
                    *remAcc_index = -1;
            };
            break;
        };
    } while (option_menu_OPT == 0);

    return ;
}
