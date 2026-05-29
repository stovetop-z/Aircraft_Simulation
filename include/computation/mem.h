#pragma once

#include <cstdint>
#include <cstddef>

struct mem 
{
    uint8_t* buffer;
    size_t capacity;
    size_t offset;

    mem(size_t size);
    ~mem();

    void* allocate(size_t byte);
    void reset();
};