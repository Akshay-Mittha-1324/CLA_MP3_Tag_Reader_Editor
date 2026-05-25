/* ================================================================
 *  NAME        : Akshay Mittha
 *  REG NO.     : 25048_081
 *  DATE        : 29 / 03 / 2026
 *  FILE        : mp3_main.c
 *  PROJECT     : MP3 Tag Reader and Editor
 *  DESCRIPTION : Main entry point for the application. Handles
 *                command-line arguments and routes to view/edit.
 *
 *  FUNCTION INDEX:
 *    main()               — coordinates viewing or editing operations
 *
 * NOTE: 
        The file name is same after the execution of the edit operation instead of 
        new separate file its getting stored in the same file name. Because 
        after the execution of the edit operation the new separate file is removed.
 * ================================================================ */

#include "mp3_header.h"

int main(int argc, char *argv[])
{
    /* structure variable declaration */
    struct MP3 mp3;

    printf("****************************************\n");
    printf(" Welcome to MP3 Tag Reader and Editor\n");
    printf("****************************************\n\n");

    int ret = validate_cla(argc,argv,&mp3);

    if(ret == VIEW)
    {
	    view(&mp3);

    }
    else if(ret == EDIT)
    {
        edit(&mp3);
    }
    else
    {
        printf("Please enter proper option!\nOption should be -v or -e\n");
    }

    return 0;

}
