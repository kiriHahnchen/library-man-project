#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED

#define OPTION_FILEPATH "option.bin"

void init_option(void);

void edit_option(AccountInfo inputAcc, int rememberStatus, int echoStatus);

void read_option(char outputUsername[MAX_SIZE_STRING], int *rememberStatus, int *echoStatus);

#endif // OPTION_H_INCLUDED
