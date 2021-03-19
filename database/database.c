#include "libman_database.h"
#include "../misc_tools/encrypt/encrypt.h"

void FirstTime_Run_Init(void)
{
    _mkdir("account");
    _mkdir("book");
    FILE *fp = fopen(OPTION_FILEPATH,"rb");
    if (fp == NULL)
        Option_Write(*(base_Acc + 0),0); //initialization of option file, base_acc is dummy
}

static int isFirstTimeLogin(void)
{
    DIR *dir;
    struct dirent *ent;
    int return_sta = 0;
    if ((dir = opendir ("account")) != NULL) {
        readdir(dir); //get rid of "."
        readdir(dir); //get rid of ".."
        if ((ent = readdir(dir)) == NULL)
            return_sta = 1;
        closedir(dir);
    };
    return return_sta;
}


void FirstTime_Login_Init(void)
{
    if (isFirstTimeLogin()) {
        AccountData
            admin =
            {
                .accUsername = "admin" ,
                .accPassword = "admin",
                .accPriority = 2,
                .accFilename = "admin.bin",
                .accBMcount = -1    //reset BMcount
            } ,

            guest =
            {
                .accUsername = "guest" ,
                .accPassword = "", //blank pass
                .accPriority = 0,
                .accFilename = "guest.bin",
                .accBMcount  = -1    //reset BMcount
            } ;

        String_Encrypt(admin.accPassword);
        String_Encrypt(guest.accPassword);

        _chdir("account");
        Acc_Write_single(admin);
        Acc_Write_single(guest);
        _chdir("..\\");
    };
}
