#ifndef MATRIX_XD_H
#define MATRIX_XD_H 

#include "Array.h"


class View{
private:
    Array<int> m_shape;
public:
    template<typename... Args> 
    View(Args... args);

    View(const View& other);

    View& operator=(const View& other);

    int size() const;
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
    template<typename... Args> MatrixXd(Args... args);

    int size() const { return m_shape.size(); }
    MatrixXd<T> view(View shape);
    template<typename... Args> MatrixXd<T> view(Args... args);
};


//View
template <typename... Args>
inline View::View(Args... args)
{
    m_shape = Array<int>::makeArray(args...);
}

inline View::View(const View &other)
{
    m_shape = other.m_shape;
}

 inline View& View::operator=(const View &other)
{
    m_shape = other.m_shape;
    return *this;
}

int View::size() const
{
    int size = m_shape[0];
    for(int i = 1; i < m_shape.size(); ++i)
        size *= m_shape[i];

    return size;
}



// MatrixXd

template<typename T> 
MatrixXd<T>::MatrixXd(Array<T> data)
{
    m_data = data;
    m_shape = View(data.size());
}

template<typename T> 
MatrixXd<T>::MatrixXd(Array<T> data, View shape)
{
    m_data = data;
    m_shape = shape;
}


template<class T> 
template<class... Args> 
MatrixXd<T>::MatrixXd(Args ...args)
{
    m_shape = View(args...);
    m_data = Array<T>(m_shape.size());
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


