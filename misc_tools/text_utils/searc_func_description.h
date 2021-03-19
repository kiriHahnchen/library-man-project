#ifndef SEARC_FUNC_DESCRIPTION_H_INCLUDED
#define SEARC_FUNC_DESCRIPTION_H_INCLUDED

/**

        Max supported string length is 500 characters ;


 ________  ________  ___      ___ ________  ________   ________  _______   ________
|\   __  \|\   ___ \|\  \    /  /|\   __  \|\   ___  \|\   ____\|\  ___ \ |\   ___ \
\ \  \|\  \ \  \_|\ \ \  \  /  / | \  \|\  \ \  \\ \  \ \  \___|\ \   __/|\ \  \_|\ \
 \ \   __  \ \  \ \\ \ \  \/  / / \ \   __  \ \  \\ \  \ \  \    \ \  \_|/_\ \  \ \\ \
  \ \  \ \  \ \  \_\\ \ \    / /   \ \  \ \  \ \  \\ \  \ \  \____\ \  \_|\ \ \  \_\\ \
   \ \__\ \__\ \_______\ \__/ /     \ \__\ \__\ \__\\ \__\ \_______\ \_______\ \_______\
    \|__|\|__|\|_______|\|__|/       \|__|\|__|\|__| \|__|\|_______|\|_______|\|_______|

    //*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&
    *--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//
    -*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*-
    __*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*
    *^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__

    ADVANCED SEARCHING SYNTAX

    & [FIELD 1] ; [FIELD 2] ; [FIELD 3]

    (#) Note: By inputting the string in this format, it effectively ignores the inputted search options, and
        overwrites(1) it to the right format describe inside the string, that is, to make the searching more
        straight-forward.

        (1): does not display to the screen, sorry for the inconvenience

        There should be no extra ';' symbol

    MEANING:

    * & : TELLS THE SEARCHBAR THIS IS A FLAG TO SEARCH FOR THE CONTENTS INPUTTED INTO THE SEARCHBAR
          NEEDS TO BE FOLLOWED BY A SPACE (' ') CHARACTER, IF NOT, THE SEARCH FUNC WILL NOT OPERATED

    * [FIELD 1] : BY TITLE

    * [FIELD 2] : BY QUANTITY
       (#) Note : Only accepts numberic strings , alphabetic and special characters strings are not
           accepted by this field

           If specify this field, if the value is found, no other searching is needed anymore.
           Therefore, this field is being processes first, right after it is [FIELD 1] and [FIELD 3]

    * [FIELD 3] : BY METADATA
          +  Author       ;
          +  Language     ;
          +  Subject      ;
          +  Publisher    ;
          +  Quantity     ;
       (#) Note : Although technically, title is also belongs to the metadata_, but
           since we already bring it into a separated option, if we disable THAT option,
           the search function will not looking for the title field anymore

    * ';' CHARACTER: SEPERATED BETWEEN DIFFERENT FIELD-S

    //*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&
    *--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//
    -*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*-
    __*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*
    *^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__

    USAGE :

      IF ONLY HAVE [FIELD 1], THE ';' AND THE '&' CHARACTER IS NOT NEEDED

      IF HAS (HAVE) OTHER FIELD-(S), IT IS NECESSARY TO WRITE THE "& " FIRST,
      AND THEN WRITE THE ';' CHARACTERS TO SEPARATE DIFFERENT FIELDS

      EX 1: '& ;156 178 9012;JILL HUBBERT'
      IN THIS EXAMPLE, WE HAVE [FIELD 2] AND [FIELD 3] , THE [FIELD 1] IS OMITTED, SO WE DONT CARE ABOUT THAT PART

      EX 2: '& ;;'
      IN THIS EXAMPLE, ALL THREE FIELDS ARE BEING OMITTED, EVEN IF THEY HAVE SPACES BETWEEN THEM
      SO, THE SEARCH FUNC WILL NOT OPERATED, NO CHANGES WERE MADE

      EX 3: '& ;;KOLL'
      HAS [FIELD 3]

      EX 4: 'JELLY'
      ONLY HAS [FIELD 1], THE SEARCH FUNC WILL SEARCH FOR THE INFOMATION

      EX 5: 'JELLY;512;HELLO
      THIS IS STILL [FIELD 1], BECAUSE IT DOES NOT HAVE THE "& " STRING IN THE FIRST POSITION

    //*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&
    *--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//
    -*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*-
    __*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*
    *^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__

    ANALYZER
        - Finds the "& " at the beginning of the input search string
            - If exists, the advanced searching mode will enter the advanced searching mode
              If not, falls back to the normal searching mode

        - With title and meta-data field
             * Within each field, divide the whole field into sub-chunks
             * With each sub-chunks, if the position is found, then score is computed and added to the sum score
             * Everything in a "" pair is considered a sub-chunk, so the program will not divided it into smaller
               sub-chunks
             * Results that has the highest relevance will be put first
             * Results that has no relevance will not be put into the output

        - With quantity field
             * Divide the whole chunk into smaller sub-chunks
             * Finding if the sub-chunk is a valid number chunk, and then compare them with the value inside
               the quantity field of the book
             * If the desired number was not found, it returns fail    and the relevance will decreases
             * If the desired number was     found, it returns success and the relevance will increases
             * The number chunk is at [FIELD 2]

    //*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&
    *--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//
    -*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*-
    __*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*
    *^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__
 *
 */

 /**

  ___      ___ ________  ________   ___  ___       ___       ________
|\  \    /  /|\   __  \|\   ___  \|\  \|\  \     |\  \     |\   __  \
\ \  \  /  / | \  \|\  \ \  \\ \  \ \  \ \  \    \ \  \    \ \  \|\  \
 \ \  \/  / / \ \   __  \ \  \\ \  \ \  \ \  \    \ \  \    \ \   __  \
  \ \    / /   \ \  \ \  \ \  \\ \  \ \  \ \  \____\ \  \____\ \  \ \  \
   \ \__/ /     \ \__\ \__\ \__\\ \__\ \__\ \_______\ \_______\ \__\ \__\
    \|__|/       \|__|\|__|\|__| \|__|\|__|\|_______|\|_______|\|__|\|__|



 *
 *
 */

 /**
    //*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&
    *--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//
    -*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*-
    __*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*
    *^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__

    VANILLA SEARCHING SYNTAX

    <TEXT NEEDS TO BE SEARHCED>

    W.I.P

    //*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&
    *--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//
    -*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*-
    __*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*
    *^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__

    MEANING:

    <TEXT NEEDS TO BE SEARHCED>

    //*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&
    *--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//
    -*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*-
    __*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*
    *^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__

    USAGE :

    W.I.P

    //*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&
    *--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//
    -*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*-
    __*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*
    *^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__

    ANALYZER

    - When passing the string into the searchbar, it will first analyzes to see if this is vanilla mode
    or advanced mode, if is vanilla mode then the following steps will be made to search

    - First, the string will be broken down into smaller sub-chunks, each sub-chunks will be passed into
    the search function and produces the appropriate score.
    - In the vanilla mode, all string will be process in its RAW FORM, that is, even if you pass the ""
    into the desired string, it will read that symbol and search for it

        * E.g:
            - Text of the murderer "libman lib"

            In this example , the text is being broken down into these sub-chunks:

            + Text
            + of
            + the
            + murderer
            + "libman
            + lib"

            As you can see, you expected this to be "libman lib" , but instead it is being broken down
            into two (or more) sub-chunks, such result is undesirable, so , if you want to do this, you
            should search in the advanced mode instead

    - For each sub-chunk , it will be evaluate against the criteria in the opt-box
    - If is "By title" and "By metadata", search as normal
    - If is "By quantity", confirms the string is a valid num string, then process


    //*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&
    *--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//
    -*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*-
    __*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*
    *^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__*^&//*--*__
 *
 */

#endif // SEARC_FUNC_DESCRIPTION_H_INCLUDED

