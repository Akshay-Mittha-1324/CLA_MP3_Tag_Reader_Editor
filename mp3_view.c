/* ================================================================
 *  NAME        : Akshay Mittha
 *  REG NO.     : 25048_081
 *  DATE        : 29 / 03 / 2026
 *  FILE        : mp3_view.c
 *  PROJECT     : MP3 Tag Reader and Editor
 *  DESCRIPTION : Implements the viewing functionality to extract
 *                and display ID3 tags from MP3 files.
 *
 *  FUNCTION INDEX:
 *    view()               — traverses and prints ID3 tags
 * ================================================================ */

#include "mp3_header.h"

void view(struct MP3 *mp3)
{
    // ? Open the file
    mp3 -> org_mp3_fptr = fopen(mp3->mp3_filename,"rb");  

    // ? Check if the file is available
    if(mp3 -> org_mp3_fptr == NULL) 
    {
        perror("ERROR ");
        return;
    }

    // ? Buffer to store ID3 from the file
    char mp3_buf[4];     
    
    // ? Reading the 3 bytes from file i.e. reading ID3
    // ? fread(buffer, sizeof(datatype), number_of_elements_to_be_read, file_pointer)
    fread(mp3_buf, 1, 3, mp3->org_mp3_fptr);
    mp3_buf[3] = '\0';

    // ? Comparing the ID3 with file content using the buffer
    printf("MP3 File Information\n---------------------------\n");
    if(strcmp(mp3_buf,"ID3") == 0)   
    {
        printf("\tIt's a mp3 file\n");
    }
    else
    {
        printf("\tIt's not an mp3 file\n");
        fclose(mp3->org_mp3_fptr);
        return;
    }
    printf("---------------------------\n");

    // ? Skipping 7 bytes in the file

    fseek(mp3->org_mp3_fptr, 7, SEEK_CUR); 

    // ? Buffer to store File Tags
    char TAG[5];    

    // ? Size of the content
    int content_size;

    // ? Tag count 
    int tag_count = 6;

    // ? Reading the tag from the file and storing it into buffer
    while(1)
    {
        if(fread(TAG, 1, 4, mp3->org_mp3_fptr) != 4)
            break;
        
        // ? Checking if the TAG is null terminated
        if(TAG[0] == '\0')
            break;

        // ? Making the tag null terminated
        TAG[4] = '\0';    

        // ? Reading the size of Frame
        fread(&content_size, 4, 1, mp3->org_mp3_fptr);    

        // ? Converting Big to Little Endian
        toggle_endianess(&content_size);

        // ? Checking the content size if it is zero or not
        if(content_size <= 0)
            continue;

        // ? Skipping 3 bytes
        fseek(mp3->org_mp3_fptr, 3, SEEK_CUR);  

        // ? Converting the tag to proper human understandable name 
        tag_to_name(TAG);
           
        // ? Printing the Frame Content
        if( !(strcmp(TAG, "COMM")) || 
            !(strcmp(TAG, "TCON")) || 
            !(strcmp(TAG, "TALB")) || 
            !(strcmp(TAG, "TIT2")) || 
            !(strcmp(TAG, "TPE1")) || 
            !(strcmp(TAG, "TYER")))
        {
            tag_count--;
            print_tag_data(mp3->org_mp3_fptr,content_size - 1);
        }

        // ? Skipping the content if it is not to be printed
        else
            fseek(mp3->org_mp3_fptr, content_size - 1 , SEEK_CUR);
    }
    fclose(mp3->org_mp3_fptr);
}