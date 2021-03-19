#ifndef MDDRIVER_H_INCLUDED
#define MDDRIVER_H_INCLUDED

#ifndef MD
#define MD 5
#endif

#if MD == 5
#include "md5.h"
#endif

#include "../../database/libman_database.h"

/*
#ifndef MAX_SIZE_STRING
#define MAX_SIZE_STRING 100
#endif // MAX_SIZE_STRING
*/

void MDString PROTO_LIST ((char *, char [32]));
void MDPrint PROTO_LIST ((unsigned char [16], char [32]));


#if MD == 5
#define MD_CTX MD5_CTX
#define MDInit MD5Init
#define MDUpdate MD5Update
#define MDFinal MD5Final
#endif

#endif // MDDRIVER_H_INCLUDED
