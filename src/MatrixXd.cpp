#ifndef MATRIX_XD_CPP
#define MATRIX_XD_CPP

#include "MatrixXd.h"


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