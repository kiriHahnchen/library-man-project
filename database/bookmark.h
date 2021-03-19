#ifndef BOOKMARK_H_INCLUDED
#define BOOKMARK_H_INCLUDED

#include "../../misc_tools/text_utils/text_utils.h"
#include "../../misc_tools/init_utils/init_utils.h"

int Bookmark_AddSingle(readedBook *input_bookLinker, readedAccount *input_accLinker); //add a book to single user

void Bookmark_DelSingle(readedBook *input_bookLinker, readedAccount *input_accLinker); //single user

void Bookmark_DelAll(readedBook *input_bookLinker);


#endif // BOOKMARK_H_INCLUDED
