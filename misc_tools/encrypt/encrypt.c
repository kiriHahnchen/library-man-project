#include "encrypt.h"

void String_Encrypt(char inputString[MAX_SIZE_STRING])
{
    //add salt
    int j = 0, count = 0;
    size_t len = ((len = strlen(inputString)) <= (MAX_SIZE_STRING / 2)) ? MAX_SIZE_STRING - len - 1: (len * 3923) % (MAX_SIZE_STRING - len),
           len2 = strlen(inputString) ;
    for (int i = len2; (size_t) count != len; i++) {
        *((inputString) + i) = *((inputString) + j);
        j++;
        count++;
    };

    len = strlen(inputString) ;
    j = 0;

    for (int i = 0; (size_t) i <= (len / 2); i++) {
        *((inputString) + i) = (*((inputString) + i) + 39) % 128;
    };

    //MD5-ed the string
	MDString((inputString) + 0 ,inputString);
	MDString((inputString) + 2 ,inputString);
	MDString((inputString) + 6 ,inputString);
	MDString((inputString) + 12,inputString);

}
