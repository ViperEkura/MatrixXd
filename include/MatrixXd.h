#ifndef MATRIX_XD_H
#define MATRIX_XD_H 

#include "Array.h"


class View{
private:
    Array<size_t> m_shape;
public:
    template<typename... Args> View(Args... args) 
        : m_shape(Array<size_t>::makeArray(args...)) {}
    
    size_t size() const;
};

template <typename T>
class MatrixXd
{
private:
    Array<T> m_data;
    View m_shape;
public:
    MatrixXd(Array<T> data);
    MatrixXd(Array<T> data, View shape);

    MatrixXd<T> view(View shape);
    template<typename... Args> MatrixXd<T> view(Args... args);
};


//View

size_t View::size() const
{
    size_t size = m_shape[0];
    for(size_t i = 1; i < m_shape.size(); ++i)
    {
        size *= m_shape[i];
    }
    return size;
}



// MatrixXd

template<typename T> 
MatrixXd<T>::MatrixXd(Array<T> data)
{
    m_data = data;
}

template<typename T> 
MatrixXd<T>::MatrixXd(Array<T> data, View shape)
{
    m_data = data;
    m_shape = shape;
}

template <typename T>
MatrixXd<T> MatrixXd<T>::view(View shape)
{
    m_shape = shape;
    return MatrixXd(m_data, shape);
}


template <typename T>
template <typename... Args>
inline MatrixXd<T> MatrixXd<T>::view(Args... args)
{
    m_shape = View(args...);
    return MatrixXd(m_data, m_shape);
}

#endif


