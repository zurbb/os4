#include "VirtualMemory.h"
#include "PhysicalMemory.h"
#include "MemoryConstants.h"

uint64_t offset_mask (uint64_t virtualAddress){
    // Returns the offset of the given virtual address.
    return virtualAddress & (PAGE_SIZE - 1);
}

uint64_t page_number_mask (uint64_t virtual_address, int depth){
    // Returns the page number of the given virtual address.
    virtual_address = virtual_address >> (OFFSET_WIDTH + (VIRTUAL_ADDRESS_WIDTH - OFFSET_WIDTH) * (1 - depth / TABLES_DEPTH));
    uint64_t mask = (VIRTUAL_ADDRESS_WIDTH - OFFSET_WIDTH) / TABLES_DEPTH;
    return virtual_address & ((1 << mask) - 1);
}

void VMinitialize(){
    // Initialize the virtual memory.
    // Initialize the page table.
    for (uint64_t i = 0; i < TABLES_DEPTH; i++){
         PMwrite(i * PAGE_SIZE, 0);
    }
}

void VMread(uint64_t virtualAddress, word_t* value){
    // Reads a word from the given virtual address
    // and puts its content in *value.
    // returns 1 on success.
    // returns 0 on failure (if the address cannot be mapped to a physical
    // address for any reason)
