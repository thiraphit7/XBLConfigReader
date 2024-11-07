#include <stdint.h>

// Referred to Linux elf.h
/* 64-bit ELF base types. */
typedef uint64_t Elf64_Addr;
typedef uint16_t Elf64_Half;
typedef int16_t Elf64_SHalf;
typedef uint64_t Elf64_Off;
typedef int32_t Elf64_Sword;
typedef uint32_t Elf64_Word;
typedef uint64_t Elf64_Xword;
typedef int64_t Elf64_Sxword;

#define EI_NIDENT 16
typedef struct elf64_hdr {
    unsigned char e_ident[EI_NIDENT];    /* ELF "magic number" */
    Elf64_Half e_type;
    Elf64_Half e_machine;
    Elf64_Word e_version;
    Elf64_Addr e_entry;        /* Entry point virtual address */
    Elf64_Off e_phoff;        /* Program header table file offset */
    Elf64_Off e_shoff;        /* Section header table file offset */
    Elf64_Word e_flags;
    Elf64_Half e_ehsize;
    Elf64_Half e_phentsize;
    Elf64_Half e_phnum;
    Elf64_Half e_shentsize;
    Elf64_Half e_shnum;
    Elf64_Half e_shstrndx;
} Elf64_Ehdr;

/* Program Headers */
typedef struct elf64_phdr {
    Elf64_Word p_type;
    Elf64_Word p_flags;
    Elf64_Off p_offset;        /* Segment file offset */
    Elf64_Addr p_vaddr;        /* Segment virtual address */
    Elf64_Addr p_paddr;        /* Segment physical address */
    Elf64_Xword p_filesz;        /* Segment size in file */
    Elf64_Xword p_memsz;        /* Segment size in memory */
    Elf64_Xword p_align;        /* Segment alignment, file & memory */
} Elf64_Phdr;

// Program header types defines
#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6

// QC XBL Config program data structure
typedef struct xc_program_header {
    char magic[4]; // 'CFGL'
    uint8_t unk1[2];
    uint16_t files_count;
    uint8_t unk2[8];
} XCHeader;

typedef struct xc_program_info {
    uint32_t offset; // Offset to CFGL program
    uint32_t size;
    uint8_t unk1[16];
    uint32_t name_len;
    const char str[];  // This will not count into struct size
} XCInfo;
