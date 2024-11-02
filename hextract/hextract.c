#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


/*
    HEXTRACT:
        File input: Argument -> Enter relative or full path of file to extract hex data
        Segment Offset: Input -> Enter point in file (in bytes) to begin extraction
        Segment Length: Input -> Enter length of desired segment (in bytes)
        Print Offsets: Input -> Enter 1 or 0 to toggle offset printing

        NOTE:
            If full file contents desired, enter 0 for Segment Offset, and 0 for Segment Length
*/


void print_line(uint8_t* buffer, int bytes, int offset, int line_len, bool show_offsets) {
    if (show_offsets == true) {
        printf("%d |", offset);
    }

    for (int i = 0; i < line_len; i++) {
        if (i > 0 && i % 4 == 0) {
            printf(" ");
        }
        if (i < bytes) {
            printf(" %02X", buffer[i]);
        } else {
            printf("   ");
        }
    }

    printf("\n");
}


void dump_file(FILE* file, int offset, int seg_len, int line_len, int show_offsets) {
    long fsize;

    uint8_t* buffer = (uint8_t*)malloc(line_len);
    if (buffer == NULL) {
        fprintf(stderr, "Error: insufficient memory.\n");
        exit(1);
    }

    // Find length of file (in bytes)
    fseek(file, 0, SEEK_END);
    fsize = ftell(file);
    fseek(file, 0, SEEK_SET);


    // Seek offset
    fseek(file, offset, SEEK_SET);

    // Set segment length to length of file if seg_len^0 = 0
    if (seg_len == 0) {
        seg_len = fsize;
    }

    printf("File size: %ld bytes", fsize);
    printf("\n");

    // Read hex encoded binary from file
    while (true) {
        int max_bytes;

        if (seg_len < 0) {
            max_bytes = line_len;
        } else if (line_len < seg_len) {
            max_bytes = line_len;
        } else {
            max_bytes = seg_len;
        }

        int bytes = fread(buffer, sizeof(uint8_t), max_bytes, file);
        if (bytes > 0) {
            print_line(buffer, bytes, offset, line_len, show_offsets);
            offset += bytes;
            seg_len -= bytes;
        } else {
            break;
        }
    }

    free(buffer);
}


int main(int argc, char *argv[]) {
    // Default to reading from stdin.
    FILE* file = stdin;
    char* filename = argv[1];

    if (filename != NULL) {
        file = fopen(filename, "rb");
        if (file == NULL) {
            fprintf(stderr, "Error: cannot open the file '%s'.\n", filename);
            exit(1);
        }
        
        // Set dump args and settings
        int offset;
        printf("Enter segment offset (0 for full file): ");
        scanf("%d", &offset);
        
        int seg_len;
        printf("Enter segment length (0 for full file): ");
        scanf("%d", &seg_len);
        printf("\n");
        int line_len = 16;

        int show_offsets;
        printf("Enter 1 to show offsets, or 0 to hide them: ");
        scanf("%d", &show_offsets);

        if (show_offsets == 1) {
            dump_file(file, offset, seg_len, line_len, true);
        }
        if (show_offsets == 0) {
            dump_file(file, offset, seg_len, line_len, false);
        }
        else {
            printf("You must enter a 0 or a 1. ");
        }

        fclose(file);
    }
    else {
        printf("$hextract program requires a valid file name as an argument. ");
    }
}
