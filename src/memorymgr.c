#include "memorymgr.h"
#include "lib/itoa.h"
#include "drivers/vga.h"

PageTable page_table;
unsigned char memory_pool[PAGE_SIZE];
MemoryBlock *free_list = (MemoryBlock *)memory_pool;

void memory_init()
{
    free_list->pid = 0;
    free_list->size = PAGE_SIZE - sizeof(MemoryBlock);
    free_list->isFree = 1;
    free_list->next = NULL;
    for (size_t i = 0; i < RESERVED_SIZE; i++)
    {
        page_table.pages[i].status = PAGE_FREE;
        page_table.pages[i].head = NULL;
        page_table.pages[i].total_size = PAGE_SIZE;
    }
    print_string("Memory init OK.", GREEN);
    return;
}

void *memory_alloc(size_t size, unsigned int pid)
{
    print_string("call_allc1",WHITE_COLOR);
    size = (size + sizeof(void *) - 1) & ~(sizeof(void *) - 1);
    print_string("call_allc2",WHITE_COLOR);
    MemoryBlock *current = free_list;

    while (current != NULL)
    {
        print_string("call_allc3",WHITE_COLOR);
        if (current->isFree && current->size >= size)
        {
            print_string("call_allc4",WHITE_COLOR);
            if (current->size > size + sizeof(MemoryBlock))
            {
                MemoryBlock *new_block = (MemoryBlock *)((unsigned char *)current + sizeof(MemoryBlock) + size);
                new_block->size = current->size - size - sizeof(MemoryBlock);
                new_block->isFree = 1;
                new_block->next = current->next;

                current->size = size;
                current->isFree = 0;
                current->next = new_block;
            }
            else
            {
                current->isFree = 0;
            }

            current->pid = pid;
            return (void *)((unsigned char *)current + sizeof(MemoryBlock));
        }

        current = current->next;
    }

    return NULL;
}

void memory_free(void *ptr, unsigned int pid)
{
    if (ptr == NULL)
        return;

    MemoryBlock *block = (MemoryBlock *)((unsigned char *)ptr - sizeof(MemoryBlock));

    if (block->isFree)
        return;

    char *data = (char *)((unsigned char *)block + sizeof(MemoryBlock));
    for (size_t i = 0; i < block->size; i++) {
        data[i] = 0;
    }

    PageEntry *page = &page_table.pages[block->pid % RESERVED_SIZE];

    if (page->head == block)
    {
        page->head = block->next;
    }
    else
    {
        MemoryBlock *prev = page->head;
        while (prev != NULL && prev->next != block)
        {
            prev = prev->next;
        }

        if (prev != NULL)
        {
            prev->next = block->next;
        }
    }

    block->pid = 0;
    block->isFree = 1;
    block->next = free_list;
    free_list = block;

    if (page->head == NULL && page->status != PAGE_FREE) {
        page->status = PAGE_FREE;
    }

    memory_defragment();
}

void memory_defragment()
{
    for (size_t i = 0; i < RESERVED_SIZE; i++)
    {
        PageEntry *page = &page_table.pages[i];

        if (page->status == PAGE_ALLOCD)
        {
            MemoryBlock *prev = NULL;
            MemoryBlock *curr = page->head;

            while (curr != NULL)
            {
                if (curr->isFree && prev && prev->isFree)
                {
                    prev->size += curr->size;
                    prev->next = curr->next;
                    curr = prev->next;
                }
                else
                {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }
}

void print_memory_map()
{
    char str[32];
    for (size_t i = 0; i < RESERVED_SIZE; i++)
    {
        PageEntry *page = &page_table.pages[i];

        itoa(i, str);
        print_string("Page ", WHITE_COLOR);
        print_string(str, WHITE_COLOR);
        print_string(": Status = ", WHITE_COLOR);

        switch (page->status)
        {
        case PAGE_FREE:
            print_string("FREE", WHITE_COLOR);
            break;
        case PAGE_ALLOCD:
            print_string("ALLOCD", WHITE_COLOR);
            break;
        case PAGE_FRG:
            print_string("FRAG", WHITE_COLOR);
            break;
        default:
            print_string("UNKNOWN", WHITE_COLOR);
            break;
        }

        itoa(page->total_size, str);
        print_string(", Total Size = ", WHITE_COLOR);
        print_string(str, WHITE_COLOR);

        itoa(page->used_size, str);
        print_string(", Used Size = ", WHITE_COLOR);
        print_string(str, WHITE_COLOR);

        MemoryBlock *block = page->head;
        while (block != NULL)
        {
            itoa(block->pid, str);
            print_string(", Block PID = ", WHITE_COLOR);
            print_string(str, WHITE_COLOR);

            itoa(block->size, str);
            print_string(", Size = ", WHITE_COLOR);
            print_string(str, WHITE_COLOR);

            block = block->next;
        }

        print_string("\n", WHITE_COLOR);
    }
}

void print_address(void *ptr)
{
    char address_str[20];
    itoa((unsigned int)ptr, address_str);
    print_string(address_str, WHITE_COLOR);
}

void print_allc_memory_map()
{
    char str[50];
    for (size_t i = 0; i < RESERVED_SIZE; i++)
    {
        PageEntry *page = &page_table.pages[i];
        if (page->status != PAGE_FREE)
        {
            MemoryBlock *block = page->head;
            while (block != NULL)
            {
                itoa((unsigned int)block, str);
                print_string(str, WHITE_COLOR);
                itoa(block->size, str);
                print_string(str, WHITE_COLOR);
                block = block->next;
            }
        }
    }
}


void print_free_list() {
    MemoryBlock *current = free_list;
    while (current != NULL) {
        print_string("Free block: ", YELLOW);
        char buffer[16];
        itoa(current->size, buffer);
        print_string(buffer, YELLOW);
        current = current->next;
    }
}
