/* ================================================================
 *  NAME        : Akshay Mittha
 *  REG NO.     : 25048_081
 *  DATE        : 29 / 03 / 2026
 *  FILE        : mp3_header.h
 *  PROJECT     : MP3 Tag Reader and Editor
 *  DESCRIPTION : Central header file defining the MP3 structure,
 *                constants, and function prototypes.
 * ================================================================ */

#ifndef MP3_HEADER_H
#define MP3_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VIEW 	1
#define EDIT 	2

struct MP3
{
    char *mp3_filename;
    FILE *org_mp3_fptr;
    FILE *dup_mp3_fptr;
    char str[100];
    char modifier[5];
};

int validate_cla(int , char **, struct MP3 *);
void view(struct MP3 *);
void edit(struct MP3 *);
void toggle_endianess(int *);
void print_tag_data(FILE *, int );
void cla_tag_to_name(char *,char *);
void tag_to_name(char *);


#endif
