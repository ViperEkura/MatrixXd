#ifndef VIEW_H
#define VIEW_H

#include "Array.h"

template<typename T>
class View
{
    Array<size_t> m_shape;
public:
    template<typename... Args> View(T first, Args... args);
};

#endif