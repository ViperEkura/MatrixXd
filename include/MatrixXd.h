#ifndef MATRIX_XD_H
#define MATRIX_XD_H 

#include "Array.h"


class View{
private:
    Array<size_t> m_shape;
public:
    template<typename... Args> View(Args... args) : m_shape(Array::makeArray(args...)) {}
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


#endif


