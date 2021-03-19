#include <stdio.h>
#include <stdlib.h>

#include "../database/libman_database.h"
#include "../misc_tools/libman_tools.h"
#include "libman_interface.h"

static void main_menu_intf_base(AccountData inputAcc)
{
    system("cls");
    printf("\x1B[?25l"); //hide cursor
    gotoxy(2,4);
    printf("Library Management");
    gotoxy(2,50);
    printf("Welcome, %s",inputAcc.accUsername);
    gotoxy( 5, 4); printf("[   ]   1. View Booklist");
    gotoxy( 7, 4); printf("[   ]   2. View Bookmark");
    gotoxy( 9, 4); printf("[   ]   3. Options");
    gotoxy(11, 4); printf("[   ]   4. Edit account");
    gotoxy(13, 4); printf("[   ]   5. Credits");
    gotoxy(15, 4); printf("[   ]   6. Logout");
    gotoxy(17, 4); printf("[   ]   7. Exit");
}

int main_menu_intf(int *rememberStatus, int *remAcc_index, int *currAcc_index)
{
    if (*currAcc_index == -1) return 0;
    main_menu_intf_base(base_Acc[*currAcc_index]);
    corxy inputCoord_arr[7] = {{5,6},{7,6},{9,6},{11,6},{13,6},{15,6},{17,6}};
    int n_OPT = 0, tmp_OPT;
    char blistmenu_visibility[5] ;
    do {
        tmp_OPT = n_OPT;
        n_OPT = OPT_mono_create_1d(7,n_OPT,inputCoord_arr,0,35,32,1);
        switch (n_OPT) {
        case 0:
            switch (base_Acc[*currAcc_index].accPriority) {
            case 0:
                memset(blistmenu_visibility + 1,0,4);
                blistmenu_visibility[0] = 3;
                break;
            case 1:
                memset(blistmenu_visibility + 1,0,3);
                blistmenu_visibility[0] = 2;
                blistmenu_visibility[4] = 1;
                break;
            case 2:
                memset(blistmenu_visibility,1,5);
                break;
            };
            blist_intf(*currAcc_index,blistmenu_visibility);
            main_menu_intf_base(base_Acc[*currAcc_index]);
            break;
        case 1:
            if (base_Acc[*currAcc_index].accPriority == 0) {
                gotoxy(7,30); printf("Not allowed!!!");
                any_key_exit();
                gotoxy(7,30); printf("              "); //cleanup
            }
            else {

                //main_menu_intf_base(base_Acc[currAcc_index]);
            };
            break;
        case 2:
            option_intf(rememberStatus,remAcc_index,*currAcc_index);
            main_menu_intf_base(base_Acc[*currAcc_index]);
            break;
        case 3:
            break;
        case 4:
            credit_intf();
            main_menu_intf_base(base_Acc[*currAcc_index]);
            break;
        case -1:
            n_OPT = tmp_OPT;
        };
    } while ((n_OPT != 6) && (n_OPT != 5)) ;
    if (n_OPT == 5) *currAcc_index = -1;

    return (n_OPT == 6) ? 0 : 2;
}
