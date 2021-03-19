#include "login_interface.h"
#include"../misc_tools/text_utils/text_utils.h"

void WelcomeMessage(int remAcc_index)
{
    system("cls");
    if (remAcc_index == -1)
        printf("Welcome back to the Library Management program.");
    else
        printf("Welcome back to the Library Management program, %s.",base_Acc[remAcc_index].accUsername);
    printf("\nPress any key to continue.\n");
    any_key_exit();
    system("cls");
}

static void login_intf_base_Login_and_Create(int x)
{
    //print frame
    system("cls");
    int col_info_arr_big[2] = {0,105} ,
        row_info_arr_big[2] = {0,18 } ;

    //input n_col, m_row counts from 1;
    //print go back option
    Draw_Table(1,1,row_info_arr_big,col_info_arr_big,3,5);

    int col_info_arr_menuBack[2] = {0,13 } ,
        row_info_arr_menuBack[2] = {0,1  } ;
    Draw_Table(1,1,row_info_arr_menuBack,col_info_arr_menuBack,15,68);
    Text_to_table_cell(1,1,row_info_arr_menuBack,col_info_arr_menuBack,"Go back",0,0,1,15,68);

    //print by X value
    //x = 0 => login
    //x = 1 => create acc
    int col_info_arr_menuX[2] = {0,13 } ,
        row_info_arr_menuX[2] = {0,1  } ;
    if (x == 0) {
        Draw_Table(1,1,row_info_arr_menuX,col_info_arr_menuX,15,88);
        Text_to_table_cell(1,1,row_info_arr_menuX,col_info_arr_menuX,"Login",0,0,1,15,88);
    }
    else {
        col_info_arr_menuX[1] += 3;
        Draw_Table(1,1,row_info_arr_menuX,col_info_arr_menuX,15,88);
        Text_to_table_cell(1,1,row_info_arr_menuX,col_info_arr_menuX,"Create Acc",0,1,1,15,88);
    }

    //draws the input field, username and password
    int col_info_arr_menuInput[3] = {0,16,34} ,
        row_info_arr_menuInput[2] = {0,1    } ;
    Draw_Table(1,2,row_info_arr_menuInput,col_info_arr_menuInput,5,10);
    Text_to_table_cell(1,1,row_info_arr_menuInput,col_info_arr_menuInput,"Username",0,0,1,5,10);

    Draw_Table(1,2,row_info_arr_menuInput,col_info_arr_menuInput,9,10);
    Text_to_table_cell(1,1,row_info_arr_menuInput,col_info_arr_menuInput,"Password",0,0,1,9,10);
    gotoxy(10,65) ; printf("[ ] Show / Hide");

    //draw rule and instruction
    gotoxy(13,10) ; printf("1. Username must contain characters (a->z , A->Z) ,");
    gotoxy(14,10) ; printf("numbers (0->9) or underscore.");

    gotoxy(16,10) ; printf("2. Maximum length is 32 characters.");

    gotoxy(18,10) ; printf("3. Use Up arrow key, Down arrow key to navigate");
    gotoxy(19,10) ; printf("through the menu.");
}

static int login_intf_checkTaken(AccountData inputAcc)
{
    for (int i = 0; i <= accNumber; i++) {
        if (strcmp(inputAcc.accUsername,base_Acc[i].accUsername) == 0)
            return 1;
    };
    return 0;
}

static int login_intf_checkValidLogin(AccountData inputAcc)
{
    for (int i = 0; i <= accNumber; i++) {
        if ((strcmp(inputAcc.accUsername,base_Acc[i].accUsername) == 0) &&
            (strcmp(inputAcc.accPassword,base_Acc[i].accPassword) == 0)
            )
            return i;
    };
    return -1;
}

static void login_intf_Login_and_Create(int inputState, int *outputIndex)
{
    if ((inputState == 1) && (accNumber == MAX_READED_ACC - 1))
        return ; //out of range
    login_intf_base_Login_and_Create(inputState);
    corxy inputCoord_arr[5] = {{6,8},{10,8},{16,66},{16,86},{10,64}};
    AccountData tmpAcc = {.accUsername = "",
                          .accPassword = "",
                          .accPriority =  1,
                          .accBMcount  = -1,
                          .accFilename = ""
                          };
    char tmpString[MAX_SIZE_STRING] = "";
    int n_OPT = 0;
    int showPassword = 0;
    int tmpIndex;
    int retry_count = 3;

    //validChar_set init
    char validChar_set[128] = "";
    for (int i = 65; i <=  90; i++) validChar_set[i] = i;
    for (int i = 48; i <=  57; i++) validChar_set[i] = i;
    for (int i = 97; i <= 127; i++) validChar_set[i] = i;
    validChar_set[95] = 95 ;
    validChar_set[32] = 32 ;

    do {
        n_OPT = OPT_mono_create_1d(5,n_OPT,inputCoord_arr,0,64,32,1);
        switch (n_OPT) {
        case 0:
            //login_intf_getString(tmpAcc.accUsername,tmpAcc.accUsername,0,0);
            inputString_field_1d(tmpAcc.accUsername,tmpAcc.accUsername,validChar_set,32,32,-1,6,29);
            break;
        case 1:
            //login_intf_getString(tmpAcc.accPassword,tmpAcc.accPassword,1,showPassword);
            inputString_field_1d(tmpAcc.accPassword,tmpAcc.accPassword,validChar_set,32,32,showPassword,10,29);
            break;
        case 2:
            return ;
        case 3:
            //checker
            if (inputState == 0) {
                strcpy(tmpString,tmpAcc.accPassword);
                String_Encrypt(tmpAcc.accPassword);
                if ((tmpIndex = login_intf_checkValidLogin(tmpAcc)) != -1) {
                    *outputIndex = tmpIndex;
                    return ;
                }
                else {
                    strcpy(tmpAcc.accPassword,tmpString);
                    if (retry_count != 0) {
                        gotoxy(19,71); printf("Invalid account, please try again!");
                        gotoxy(21,77); printf("%d more tries.....",retry_count);
                        any_key_exit();
                        gotoxy(19,71); printf("                                  ");
                        gotoxy(21,77); printf("                  ");
                        retry_count--;
                    }
                    else {
                        *outputIndex = -2;
                        return ;
                    }
                };
            }
            else {
                if (login_intf_checkTaken(tmpAcc) == 0) {
                    String_Encrypt(tmpAcc.accPassword);
                    base_Acc_add(tmpAcc);
                    return ;
                }
                else {
                    gotoxy(19,71); printf("This account has already being taken");
                    any_key_exit();
                    gotoxy(19,71); printf("                                    ");
                }
            };
            break;
        case 4:
            //hid or show the password
            gotoxy(10,29); printf("                                ");
            gotoxy(10,66);
            if (showPassword == 42) {
                showPassword = -1;
                printf("#");
                gotoxy(10,29);
                for (int i = 1; i <= (int) strlen(tmpAcc.accPassword); i++) printf("%c",tmpAcc.accPassword[i - 1]);
            }
            else {
                showPassword = 42;
                printf(" ");
                gotoxy(10,29);
                for (int i = 1; i <= (int) strlen(tmpAcc.accPassword); i++) printf("*");
            };
            break;
        };
    } while (n_OPT != -1);

    return ;
}

static void login_intf_base_menu(void)
{
    system("cls");
    int col_info_arr[2] = {0,70},
        row_info_arr[2] = {0, 9};
    Draw_Table(1,1,row_info_arr,col_info_arr,2,5);

    Text_to_table_cell(1,1,row_info_arr,col_info_arr,"[   ] . Login to the program",-1,4,2,2,5);
    Text_to_table_cell(1,1,row_info_arr,col_info_arr,"[   ] . Create an account   ",-1,4,4,2,5);
    Text_to_table_cell(1,1,row_info_arr,col_info_arr,"[   ] . Exit                ",-1,4,6,2,5);
    gotoxy(10,10); printf("Library Management                            Made by kirikiri");
}

int login_intf_menu(int *outputIndex)
{
    corxy inputCoord_arr[3] = {{4,12},{6,12},{8,12}};
    int n_OPT = 0, tmp_OPT;
    int tmpIndex = -1;

    login_intf_base_menu();
    do {
        tmp_OPT = n_OPT;
        n_OPT = OPT_mono_create_1d(3,n_OPT,inputCoord_arr,0,35,32,1);
        switch (n_OPT) {
        case 0:
            login_intf_Login_and_Create(0,&tmpIndex);
            login_intf_base_menu();
            if (tmpIndex != -2) {
                *outputIndex = tmpIndex;
            };
            break;
        case 1:
            login_intf_Login_and_Create(1,&tmpIndex);
            login_intf_base_menu();
            break;
        case -1:
            n_OPT = tmp_OPT;
            break;
        }
    } while ((tmpIndex == -1) && (n_OPT != 2));


    return (n_OPT == 2) ? 0 : (tmpIndex != -2) ? 1 : 0;;
}
