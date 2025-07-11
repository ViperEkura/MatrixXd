#ifndef VIEW_CPP
#define VIEW_CPP

#include "View.h"

template <typename T>
template <typename... Args>
inline View<T>::View(T first, Args... args)
{
    std::vector<T> vec = {first, args...};
    m_shape = Array<T>(vec);
}

# endif