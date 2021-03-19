#ifndef ENCRYPT_H_INCLUDED
#define ENCRYPT_H_INCLUDED

#include "../../database/libman_database.h"

/*
#ifndef MAX_SIZE_STRING
#define MAX_SIZE_STRING 100
#endif // MAX_SIZE_STRING
*/

#include <string.h>
#include "mddriver.h"

void String_Encrypt(char inputString[MAX_SIZE_STRING]);

#endif // ENCRYPT_H_INCLUDED
