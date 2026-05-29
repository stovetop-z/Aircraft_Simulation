#pragma once

#include <cstddef>
#include <arm_neon.h>
#include "mem.h"

template<typename t>
struct tensor 
{
    t* data;
    size_t row;
    size_t col;

    tensor(mem& flight_memory, size_t r, size_t c);
    ~tensor();

    t& operator()(const size_t r, const size_t c) const;
};