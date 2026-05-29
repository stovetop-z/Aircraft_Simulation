#include "math/tensor.h"

template<typename t>
tensor<t>::tensor(mem& memory, size_t r, size_t c) : row(r), col(c) 
{
    data = static_cast<t*>(memory.allocate(r * c * sizeof(t)));
}

template<typename t>
tensor<t>::~tensor()
{
    delete[] data;
}

template<typename t>
t& tensor<t>::operator()(const size_t r, const size_t c) const
{
    return data[r * col + c];
}