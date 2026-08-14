/* ================================================================
 *  NAME        : Akshay Mittha
 *  REG NO.     : 25048_081
 *  DATE        : 29 / 03 / 2026
 *  FILE        : functions.c
 *  PROJECT     : MP3 Tag Reader and Editor
 *  DESCRIPTION : Shared utility functions for file processing,
 *                tag parsing, data conversion, and CLA validation.
 *
 *  FUNCTION INDEX:
 *    toggle_endianess()   — converts between little and big endian
 *    tag_to_name()        — prints the human-readable tag name
 *    validate_cla()       — validates command line arguments
 *    cla_tag_to_name()    — maps CLA modifiers to ID3 tag strings
 *    print_tag_data()     — reads and prints tag content from file
 * ================================================================ */

#include "mp3_header.h"

void toggle_endianess(int *size)
{
	char *cp = (char *) size;
	char temp;
	for(int i = 0; i < 2; i++)
	{
		temp = cp[i];
		cp[i] = cp[4 - i - 1];
		cp[4 - i - 1] = temp;
	}
}

void tag_to_name(char *str)
{
	if( ! (strcmp(str,"TIT2")) )
		printf("Title / Song Name : ");
		
	else if( !(strcmp(str,"TPE1")))
		printf("Artist Name: ");
		
	else if( !(strcmp(str, "TALB")))
		printf("Album : ");
		
	else if( !(strcmp(str,"TYER")))
		printf("Year : ");
		
	else if( !(strcmp(str, "TCON")))
		printf("Music : ");
	
	else if( !(strcmp(str, "COMM")))
		printf("Comment : ");

	return;
}

int validate_cla(int argc, char *argv[], struct MP3 *mp3)
{
    if( argc == 1 )
    {
		printf("------------------------------------------------------------------------------\n");
		printf("ERROR: ./a.out : INVALID ARGUMENTS\n");
		printf("USAGE : To view please pass like: ./a.out -v mp3filename\n");
		printf("To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n");
		printf("To get help pass like : ./a.out --help\n");
		printf("------------------------------------------------------------------------------\n");
		return 0;
    }

    if( (strcmp(argv[1], "--help") == 0) )
    {
		printf("------------------------------->HELP<-----------------------------------------\n");
		printf("1. -v -> to view mp3 file contents\n");
		printf("2. -e -> to edit mp3 file contents\n");
		printf("\t\t2.1. -t -> to edit song title\n");
		printf("\t\t2.2. -a -> to edit artist name\n");
		printf("\t\t2.3. -A -> to edit album name\n");
		printf("\t\t2.4. -y -> to edit year\n");
		printf("\t\t2.5. -m -> to edit content\n");
		printf("\t\t2.6. -c -> to edit comment\n");
		printf("------------------------------------------------------------------------------\n");
		
		return 0; 
    }

    if(!strcmp(argv[1], "-v"))
    {
		// Do the necessary validation
		if(argv[2] == NULL || argc <= 2)
		{
			printf("ERROR : INVALID ARGUMENT\n");
			printf("USAGE : ./a.out -v <mp3filename>\n\n");
			return 0;
		}
		mp3->mp3_filename = argv[2];
		return VIEW;
    }
    
    if(!strcmp(argv[1], "-e"))
    {
		if( argv[2] == NULL || argc <= 2)
		{
			printf("ERROR : INVALID ARGUMENT\n");
			printf("USAGE : ./a.out -e -t/-a/-A/-m/-y/-c <changing_text> <mp3filename>\n\n");
			return 0;
		}

		// Do the necessary validation
		if(!strcmp(argv[2], "-t") || !strcmp(argv[2], "-a") || !strcmp(argv[2], "-A") || !strcmp(argv[2], "-m") || !strcmp(argv[2], "-y") || !strcmp(argv[2], "-c"))
		{
			// ? Copying the option to be edited to the structure
			strcpy(mp3->modifier, argv[2]);
			strcpy(mp3->str, argv[3]);
			mp3->mp3_filename = argv[4];
			return EDIT;
		}
    }

	return 0;
}

void cla_tag_to_name(char *modifier , char *copy_tag)
{
	if( !(strcmp(modifier, "-t")))
		strcpy(copy_tag, "TIT2");

	else if( !(strcmp(modifier, "-a")))
		strcpy(copy_tag, "TPE1");

	else if( !(strcmp(modifier, "-A")))
		strcpy(copy_tag, "TALB");

	else if( !(strcmp(modifier, "-y")))
		strcpy(copy_tag, "TYER");

	else if( !( strcmp(modifier, "-c")))
		strcpy(copy_tag, "COMM");

	else if( !(strcmp (modifier, "-m")))
		strcpy(copy_tag, "TCON");

	return;
}

void print_tag_data(FILE * org_mp3_fptr, int content_size)
{

	if(content_size <= 0)
	{
		printf("The content size is less than 0 or is 0!\n");
		return;
	}

	char temp;
	while(content_size != 0)
	{
		fread(&temp, 1, sizeof(char), org_mp3_fptr);
		printf("%c",temp);
		content_size--;
	}
	printf("\n");
	return;
}
