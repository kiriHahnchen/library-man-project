#ifndef LOGIN_INTERFACE_H_INCLUDED
#define LOGIN_INTERFACE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../database/libman_database.h"
#include "../misc_tools/libman_tools.h"

void WelcomeMessage(int remAcc_index);

int login_intf_menu(int *outputIndex);


#endif // LOGIN_INTERFACE_H_INCLUDED
