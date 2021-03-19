/* MDDRIVER.C - test driver for MD2, MD4 and MD5
 */

/* Copyright (C) 1990-2, RSA Data Security, Inc. Created 1990. All
rights reserved.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
 */

/* The following makes MD default to MD5 if it has not already been
  defined with C compiler flags.
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "md5global.h"
#include "mddriver.h"

/* Digests a string and prints the result.
 */
void MDString (inputString, outputString)
char *inputString;
char outputString[32];
{
  MD_CTX context;
  unsigned char digest[16];
  unsigned int len = strlen ((char *)inputString);

  MDInit (&context);
  MDUpdate (&context, inputString, len);
  MDFinal (digest, &context);

  MDPrint (digest,outputString);

}


/* Prints a message digest in hexadecimal.
 */
void MDPrint (digest, outputString)
unsigned char digest[16];
char outputString[32];
{
    unsigned int i;
    memset(outputString,'\0',MAX_SIZE_STRING);
    for (i = 0; i < 16; i++)
        sprintf (outputString + i*2,"%02x", digest[i]);
    //outputString[32] = '\0';
}
