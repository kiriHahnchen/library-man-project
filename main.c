#include <stdio.h>
#include <stdlib.h>

#include "database/libman_database.h"
#include "misc_tools/libman_tools.h"
#include "interface/libman_interface.h"

//initialization
int accNumber  ,
    bookNumber ;

int main()
{
    //first time init
    FirstTime_Run_Init();
    FirstTime_Login_Init();

    //initialization
    accNumber  = base_Acc_init ();
    bookNumber = base_Book_init();


    int rememberStatus ;
    int remAcc_index  = Option_Read(&rememberStatus),
        currAcc_index = remAcc_index;

    printf("%d %d %d\n",accNumber,bookNumber,remAcc_index);

    currAcc_index += 0;

    //init screen
    system("cls");
    printf("\x1B[?25l"); //hide cursor

    //main loop
    WelcomeMessage(remAcc_index);

    int goto_mainmenu = (remAcc_index != -1) ? 1 : 2;
    do {
        switch (goto_mainmenu) {
        case 1: goto_mainmenu = main_menu_intf  (&rememberStatus,&remAcc_index,&currAcc_index); break;
        case 2: goto_mainmenu = login_intf_menu (                              &currAcc_index); break;
        };
    } while (goto_mainmenu != 0);
    system("cls") ;

    //post-init, writing data
    Acc_Write_all();
    Book_Write_all();
    if (remAcc_index == -1)
        Option_Write(*(base_Acc + 0),0);
    else
        Option_Write(*(base_Acc + remAcc_index),rememberStatus);
    //all done !
    return 0;
}
