#include <stdio.h>
#include <stdlib.h>
#include "../misc_tools/con_utils/con_utils.h"

void credit_intf(void)
{
    int base_row = 2;
    system("cls");
    printf("\x1B[?25l"); //hide cursor
    gotoxy(base_row,4); printf("Made, by kirikiri"); base_row++;
                                                                  base_row++;
    gotoxy(base_row,4); printf("FPTU HCM city")    ; base_row++;
    //gotoxy(base_row,4); printf("SE161224")         ; base_row++;
                                                                ; base_row++;
    gotoxy(base_row,4); printf("Press any key to go back to the main menu");
                                                                ; base_row++;
    gotoxy(base_row,4); any_key_exit();
}
