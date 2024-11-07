#include <stdio.h>
// File utils
#include "fileutils.h"
// Elf pre-defines
#include "data_structures.h"

#define PARSER_VERSION "v0.0.1"

// Entry
int main(int argc, char *argv[]) {
    printf("XBLConfigParser Version %s\n", PARSER_VERSION);
    printf("Copyright (c) 2024-2025 woa-msmnile authors\n\n");

    // Check args
    if (argc != 3) {
        // Print usage if arg numbers not meet.
        printf("Usage: <Path to xbl_config.elf> <Output Directory>\n");
        return -EINVAL;
    }

    // Parse arguments
    FileContent xbl_config = {.filePath = argv[1]};
    const char *OutputDir = argv[2];

    // Try read ELF file
    if (get_file_size(&xbl_config) < sizeof(Elf64_Ehdr))
        return -EINVAL;
    xbl_config.fileBuffer = malloc(xbl_config.fileSize);
    read_file_content(&xbl_config);

    // Try map ELF header
    Elf64_Ehdr *hdr = (Elf64_Ehdr *) xbl_config.fileBuffer;

    // Is it an ELF?
    if (!strstr((const char *) hdr->e_ident, "ELF")) {
        printf("Not a ELF file !!!\n");
        printf("Wrong file? Please check the first arg you provided.\n");
        return -EINVAL;
    }

    // Print ELF header info
    printf("ELF Header Information:\n");
    printf("ELF Magic: 0x%016llx 0x%016llx\n", (uint64_t) hdr->e_ident, (uint64_t) (hdr->e_ident + 8));
    printf("Program Header Offset: 0x0%llx\n", hdr->e_phoff);
    printf("Program Header Numbers: 0x%x\n", hdr->e_phnum);
    printf("Program Header Size: 0x%x\n", hdr->e_phentsize);

    // Parse program headers
    Elf64_Phdr *phdr = (Elf64_Phdr *) (xbl_config.fileBuffer + hdr->e_phoff);
    XCHeader *xc_hdr = NULL;
    for (int i = 0; i < hdr->e_phnum; i++) {
        // Find the first "LOAD" Header
        if (phdr->p_type == PT_LOAD) {
            // Parse this program
            // Print information
            printf("\nCFGL Offset: 0x%llx\n", phdr->p_offset);
            // Map header
            xc_hdr = (XCHeader *) (xbl_config.fileBuffer + phdr->p_offset);
            // It's QC's type, the magic is 'CFGL', check it
            printf("CFGL Header: \"%.4s\"\n", xc_hdr->magic);
            if (!strncmp(xc_hdr->magic, "LGFC", 4)) {
                printf("Invalid Header in first program entry !!!\n");
                printf("Not a valid new version xbl config file.");
                return -EINVAL;
            }
            printf("\nFile Counts: %d\n", xc_hdr->files_count);

            // Save files infos
            XCInfo *xc_info = (XCInfo *) ((uintptr_t) xc_hdr + sizeof(XCHeader));
            uint16_t next_info_offset = 0;
            for (int j = 0; j < xc_hdr->files_count; j++) {
                // Map XCInfo structure
                xc_info = (XCInfo *) ((uintptr_t) xc_info + next_info_offset);

                // Print Info
                printf("File %d\n", j);
                printf("\tName: %s\n", xc_info->str);
                printf("\tSize: 0x%x\n", xc_info->size);
                printf("\tOffset: 0x%x\n", xc_info->offset);
                printf("\tFile Offset: 0x%llx\n", xc_info->offset + phdr->p_offset);
                //printf("\tName Length: %d\n", xc_info->name_len);

                // Fill file content info and write into disk.
                FileContent file_to_write = {
                        .fileBuffer = xc_info->offset + phdr->p_offset + xbl_config.fileBuffer,
                        .fileSize = xc_info->size,
                };
                file_to_write.filePath = malloc(strlen(OutputDir) + strlen(xc_info->str) + 2); // +2 for '/' and '\0'
                sprintf(file_to_write.filePath, "%s/%s", OutputDir, xc_info->str);
                write_file_content(&file_to_write);
                free(file_to_write.filePath); // Free unused memory

                // Make sure len can be mod with 4
                next_info_offset = xc_info->name_len + sizeof(XCInfo)
                                   + 4; // +4 here because the name must have at least 4*00 after it.
                if (next_info_offset % 8)
                    next_info_offset += 8 - next_info_offset % 8;
                // printf("%d\n", next_info_offset);
            }
            break;
        }
        phdr++;
    }

    // Free xbl_config buffer
    free(xbl_config.fileBuffer);
    return 0;
}
