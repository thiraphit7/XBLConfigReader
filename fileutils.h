/** @file
 * DualBoot Kernel Patcher Header File.
 *
 *  Copyright (c) 2021-2024 The DuoWoa authors. All rights reserved.
 *  MIT License
 *
 */

#ifndef FILE_UTILS
#define FILE_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

//
// Store some file information and file buffer.
//
typedef struct {
    uint8_t *fileBuffer;
    size_t fileSize;
    char *filePath;
} FileContent, *pFileContent;

size_t get_file_size(FileContent *fileContent);

uint8_t *read_file_content(FileContent *fileContent);

int write_file_content(FileContent *fileContent);

#endif //FILE_UTILS