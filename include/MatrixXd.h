#ifndef MATRIX_XD_H
#define MATRIX_XD_H 

#include "Array.h"


class View {
private:
    Array<int> m_shape;
    Array<bool> m_is_broadcasted;
public:
    template<typename... Args> 
    View(Args... args);

    View(Array<int> shape);

    View(Array<int> shape, Array<bool> is_broadcasted);

    View(const View& other);

    View& operator=(const View& other);

    int size() const;
    int ndim() const { return m_shape.size(); } 
    int dim(int i) const { return m_shape[i]; }

    static View broadcastShape(const View& a, const View& b); 
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

    template<typename... Args> 
    MatrixXd(Args... args);

    int size() const { return m_shape.size(); }

    MatrixXd<T> view(View shape);
    
    template<typename... Args> 
    MatrixXd<T> view(Args... args);

    MatrixXd<T> operator+(const MatrixXd<T>& other);

    MatrixXd<T> operator-(const MatrixXd<T>& other);

    MatrixXd<T> operator*(const MatrixXd<T>& other);

    MatrixXd<T> operator/(const MatrixXd<T>& other);

};


//View
template <typename... Args>
inline View::View(Args... args)
{
    m_shape = Array<int>::makeArray(args...);
    m_is_broadcasted = Array<bool>(m_shape.size());
}

inline View::View(Array<int> shape)
{
    m_shape = shape;
    m_is_broadcasted = Array<bool>(m_shape.size());
}

inline View::View(Array<int> shape, Array<bool> is_broadcasted)
{
    m_shape = shape;
    m_is_broadcasted = is_broadcasted;
}

inline View::View(const View &other)
{
    m_shape = other.m_shape;
    m_is_broadcasted = other.m_is_broadcasted;
}

 inline View& View::operator=(const View &other)
{
    m_shape = other.m_shape;
    m_is_broadcasted = other.m_is_broadcasted;
    return *this;
}

int View::size() const
{
    int size = 1;
    for(int i = 0; i < m_shape.size(); ++i)
        if(!m_is_broadcasted[i]) size *= m_shape[i];

    return size;
}

inline View View::broadcastShape(const View& a, const View& b)
{
    int ndim = std::max(a.ndim(), b.ndim());
    Array<int> result_shape(ndim);
    Array<bool> is_broadcasted(ndim);

    for (int i = 0; i < ndim; ++i) {
        int dim_a = (i < a.ndim()) ? a.dim(i) : 1;
        int dim_b = (i < b.ndim()) ? b.dim(i) : 1;
        assert(dim_a == dim_b || dim_a == 1 || dim_b == 1);
        result_shape[i] = std::max(dim_a, dim_b);
        
        if (dim_a != dim_b) is_broadcasted[i] = true;
        else is_broadcasted[i] = false;
    }
    return View(result_shape);
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


template<class T> 
MatrixXd<T> MatrixXd<T>::operator+(const MatrixXd<T> &other)
{
    View target_shape = View::broadcastShape(m_shape, other.m_shape);
    Array<T> result_data = m_data + other.m_data;
    return MatrixXd<T>(result_data, target_shape);
}

template<class T> 
MatrixXd<T> MatrixXd<T>::operator-(const MatrixXd<T> &other)
{
    View target_shape = View::broadcastShape(m_shape, other.m_shape); 
    Array<T> result_data = m_data - other.m_data;
    return MatrixXd<T>(result_data, target_shape);
}

template<class T> 
MatrixXd<T> MatrixXd<T>::operator*(const MatrixXd<T> &other)
{
    View target_shape = View::broadcastShape(m_shape, other.m_shape);
    Array<T> result_data = m_data * other.m_data;
    return MatrixXd<T>(result_data, target_shape);
}

template<class T> 
MatrixXd<T> MatrixXd<T>::operator/(const MatrixXd<T> &other)
{
    View target_shape = View::broadcastShape(m_shape, other.m_shape);
    Array<T> result_data = m_data / other.m_data;
    return MatrixXd<T>(result_data, target_shape);
}

#endif
