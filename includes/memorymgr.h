#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

#define PAGE_SIZE 4096
#define RESERVED_SIZE 1024

typedef enum
{
    PAGE_FREE = 0x00,   // Page is completely free
    PAGE_ALLOCD = 0x01, // Page is fully allocated
    PAGE_FRG = 0x02     // Page is fragmented
} PageStatus;

typedef struct MemoryBlock
{
    unsigned int pid;  // Process ID
    unsigned int size; // Size of block
    unsigned char isFree;

    struct MemoryBlock *next; // LinkedList
} MemoryBlock;

typedef struct PageEntry
{
    PageStatus status;
    unsigned int total_size;
    unsigned int used_size;
    unsigned int block_count;
    MemoryBlock *head;
} PageEntry;

typedef struct PageTable
{
    PageEntry pages[RESERVED_SIZE];
} PageTable;

extern PageTable page_table;
extern unsigned char memory_pool[PAGE_SIZE];

void memory_init();
void *memory_alloc(size_t size, unsigned int pid);
void memory_free(void *ptr, unsigned int pid);
void memory_defragment();
void print_memory_map();
void print_address(void *ptr);
void print_allc_memory_map();
void print_free_list();

#endif /* MEMORY_H */