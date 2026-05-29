#include "computation/mem.h"

mem::mem(size_t size) : capacity(size), offset(0) 
{
    buffer = new uint8_t[size];
}
mem::~mem()
{
    delete[] buffer;
}

void* mem::allocate(size_t bytes) 
{
    size_t padding = (16 - (reinterpret_cast<uintptr_t>(buffer + offset) % 16)) % 16;
    size_t total_allocation = bytes + padding;

    if(offset + total_allocation > capacity)
        return nullptr;

    uint8_t* curr_ptr = buffer + offset + total_allocation;
    offset += total_allocation;
}

void mem::reset() 
{
    offset = 0;
}