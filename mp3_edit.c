/* ================================================================
 *  NAME        : Akshay Mittha
 *  REG NO.     : 25048_081
 *  DATE        : 29 / 03 / 2026
 *  FILE        : mp3_edit.c
 *  PROJECT     : MP3 Tag Reader and Editor
 *  DESCRIPTION : Implements the editing functionality for ID3 tags
 *                in MP3 files.
 *
 *  FUNCTION INDEX:
 *    edit()               — modifies specified tag in the MP3 file
 * ================================================================ */

#include "mp3_header.h"

void edit(struct MP3 *mp3)
{
    mp3->dup_mp3_fptr = fopen("song.mp3", "wb");
    mp3->org_mp3_fptr = fopen(mp3->mp3_filename, "rb");

    if(mp3->org_mp3_fptr == NULL || mp3->dup_mp3_fptr == NULL)
    {
        perror("ERROR: ");
        return;
    }

    char id3_header[11];
    char encoding;
    char ch;
    char tag[5];
    char copy_tag[5];
    int old_content_size;
    int str_len;
    int new_content_size_to_write;
    char frame_flag[3];

    // ? Copying data from the original file to duplicate file
    fread(id3_header, 1, 10, mp3->org_mp3_fptr);
    fwrite(id3_header, 1, 10, mp3->dup_mp3_fptr);
    
    while(1)
    {
        // ? Reading the tag from the original file
        fread(tag, 1, 4, mp3->org_mp3_fptr);
        tag[4] = '\0';

        // ? Checking if tag is null
        if(tag[0] == '\0')
        {
            fwrite(tag, 1, 4, mp3->dup_mp3_fptr);
            break;
        }
            
        // Reading the frame size from the original file
        fread(&old_content_size, 4, 1, mp3->org_mp3_fptr);

        // ? Toggle Endianess to make it little endian
        toggle_endianess(&old_content_size);

        // ? Reading the frame flags from the original file
        fread(frame_flag, 1, 2, mp3->org_mp3_fptr);

        // ? Calling the fuction to get the cla tag to name 
        cla_tag_to_name(mp3->modifier, copy_tag);

        // ? Comparing the read tag with the cla tag
        if( !(strcmp(tag, copy_tag)))
        {
            str_len = strlen(mp3->str);

            new_content_size_to_write = 1 + str_len;

            // ? Writing the tag to the duplicate file
            fwrite(copy_tag, 4, 1, mp3->dup_mp3_fptr);

            // ? Toggle Endianess to convert it to big endianess
            toggle_endianess(&new_content_size_to_write);

            // ? Writing the size of the content to the duplicate file
            fwrite(&new_content_size_to_write, 4, 1, mp3->dup_mp3_fptr);

            // ? Writing the flag to the duplicate file to make it 10 bytes
            fwrite(frame_flag, 1, 2, mp3->dup_mp3_fptr);

            // ? Writing encoding flag to duplicate file
            fwrite(&encoding, 1, 1, mp3->dup_mp3_fptr);

            // ? Writing the new tag to the file
            fwrite(mp3->str, 1, str_len, mp3->dup_mp3_fptr);

            // ? Moving the original file pointer using the old size of the content to the end of the content
            fseek(mp3->org_mp3_fptr, old_content_size , SEEK_CUR);
            
        }
        else
        {
            // ? Writing the data from original file to duplicate file as it is
            fwrite(tag, 4, sizeof(char), mp3->dup_mp3_fptr);

            // ? Toggle Endianess
            toggle_endianess(&old_content_size);

            // ? Writing the size of the content to the duplicate file
            fwrite(&old_content_size, 1, sizeof(int), mp3->dup_mp3_fptr);

            // ? Toggle Endianess
            toggle_endianess(&old_content_size);

            // ? Writing the flag to the duplicate file to make it 10 bytes
            fwrite(frame_flag, 2, sizeof(char), mp3->dup_mp3_fptr);
            
            // ? Writing the data from original file to duplicate file as it is
            for(int i = 0; i < old_content_size; i++)
            {
                fread(&ch, 1, sizeof(ch), mp3->org_mp3_fptr);
                fwrite(&ch, 1, sizeof(ch), mp3->dup_mp3_fptr);
            }
        }
    }
    // ? Coping all the the remaining data to the duplicate file
    while(fread(&ch, 1, sizeof(ch), mp3->org_mp3_fptr) > 0)
        fwrite(&ch, 1, sizeof(ch), mp3->dup_mp3_fptr);

    // ? Closing the file Pointers    
    fclose(mp3->org_mp3_fptr);
    fclose(mp3->dup_mp3_fptr);
    
    // ? Removing the original File and Renaming the duplicate file to the original file name 
    remove(mp3->mp3_filename);
    rename("song.mp3", mp3->mp3_filename);
    printf("File edited successfully\n");
    return;
}