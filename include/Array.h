#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <cassert>
#include "NumericalOps.h"

template <typename T>
class SegmentResource
{
private:
    T* m_data_ptr;
    int* m_data_ref_cnt;
public:
    SegmentResource() 
        : m_data_ptr(nullptr), m_data_ref_cnt(nullptr){}

    SegmentResource(T* data_ptr, int* data_ref_cnt) 
        : m_data_ptr(data_ptr), m_data_ref_cnt(data_ref_cnt){}
    
    SegmentResource(int resource_size) 
        : m_data_ptr(new T[resource_size]), m_data_ref_cnt(new int(1)){}

    SegmentResource(const SegmentResource<T>& other);

    SegmentResource<T>& operator=(const SegmentResource<T>& other);
    
    ~SegmentResource();

    T& operator[](int index);

    T operator[](int index) const;

    T* data() const { return m_data_ptr; }

    int refCount() const { return m_data_ref_cnt ? *m_data_ref_cnt : 0; }

};


template <typename T>
class Array
{
private:
    SegmentResource<T> m_data;
    int m_size;

public:
    Array()
        : m_data(), m_size(0) {}
    Array(int size)
        : m_data(SegmentResource<T>(size)), m_size(size){}
    
    Array(std::vector<T> vec);

    Array(std::initializer_list<T> list);

    Array(const Array<T>& other);
    
    Array<T>& operator=(const Array<T>& other);
    
    T& operator[](int index);
    
    T operator[](int index) const;

    Array<T> operator+(const Array<T>& other) const;

    Array<T> operator-(const Array<T>& other) const;
    
    Array<T> operator*(const Array<T>& other) const;

    Array<T> operator/(const Array<T>& other) const;

    int size() const { return m_size; }

    T* data() const { return m_data.data(); }

    T* begin() const {return m_data.data();}

    T* end() const {return m_data.data() + m_size;}

    template <typename... Args>
    static Array<T> makeArray(Args... args);

    Array<T> slice(int start, int end) const;
};

// SegmentResource

template<typename T> 
inline SegmentResource<T>::SegmentResource(const SegmentResource<T>& other)
{
    m_data_ptr = other.m_data_ptr;
    m_data_ref_cnt = other.m_data_ref_cnt;
    if(other.m_data_ref_cnt != nullptr) ++(*other.m_data_ref_cnt);
}

template <typename T>
inline SegmentResource<T>& SegmentResource<T>::operator=(const SegmentResource<T> &other)
{
    if(&other == this) return *this;
    if(m_data_ref_cnt != nullptr && --(*m_data_ref_cnt) == 0) delete[] m_data_ptr, delete m_data_ref_cnt;
    if(other.m_data_ptr != nullptr) ++(*other.m_data_ref_cnt);
    
    m_data_ptr = other.m_data_ptr;
    m_data_ref_cnt = other.m_data_ref_cnt;

    return *this;
}


template<typename T> 
inline SegmentResource<T>::~SegmentResource(){
    if(m_data_ref_cnt != nullptr && --(*m_data_ref_cnt) == 0)
    {
        delete[] m_data_ptr, delete m_data_ref_cnt;
        m_data_ptr = nullptr, m_data_ref_cnt = nullptr;
    }
}

template <typename T>
inline T& SegmentResource<T>::operator[](int index)
{
    return m_data_ptr[index];
}

template <typename T>
T SegmentResource<T>::operator[](int index) const {
    return m_data_ptr[index];
}

// Array
template <typename T>
inline Array<T>::Array(std::vector<T> vec)
{
    m_size = vec.size();
    m_data = SegmentResource<T>(vec.size());
    std::copy(vec.begin(), vec.end(), m_data.data());
}

template<typename T> 
inline Array<T>::Array(std::initializer_list<T> list) 
{
    m_size = list.size();
    m_data = SegmentResource<T>(m_size);
    std::copy(list.begin(), list.end(), m_data.data());
}

template <typename T>
inline Array<T>::Array(const Array<T> &other)
{
    m_data = other.m_data;
    m_size = other.m_size;
}

template<typename T> 
inline Array<T> &Array<T>::operator=(const Array<T> &other)
{
    m_data = other.m_data;
    m_size = other.m_size;
    return *this;
}

template<class T> 
T& Array<T>::operator[](int index)
{
    assert(index >= -m_size && index < m_size && "Index out of range");
    return m_data[(index + m_size) % m_size]; 
}

template<class T> 
T Array<T>::operator[](int index) const
{
    assert(index >= -m_size && index < m_size && "Index out of range");
    return m_data[(index + m_size) % m_size]; 
}

template<class T> 
Array<T> Array<T>::operator+(const Array<T> &other) const
{
    assert(m_size == other.m_size && "Array size mismatch");
    Array<T> result(m_size);
    WAXPBY(m_data.data(), other.m_data.data(), result.m_data.data(), m_size, 1.0, 1.0);
}


template<class T> 
Array<T> Array<T>::operator-(const Array<T> &other) const
{
    assert(m_size == other.m_size && "Array size mismatch");
    Array<T> result(m_size);
    WAXPBY(m_data.data(), other.m_data.data(), result.m_data.data(), m_size, 1.0, -1.0);
}

template<class T> 
Array<T> Array<T>::operator*(const Array<T> &other) const
{
    assert(m_size == other.m_size && "Array size mismatch");
    Array<T> result(m_size);
    WAXMY(m_data.data(), other.m_data.data(), result.m_data.data(), m_size, 1.0);
}

template <typename T>
inline Array<T> Array<T>::operator/(const Array<T> &other) const
{
    assert(m_size == other.m_size && "Array size mismatch");
    Array<T> result(m_size);
    WAXDY(m_data.data(), other.m_data.data(), result.m_data.data(), m_size, 1.0, 0);
}

template <typename T>
template <typename... Args>
Array<T> Array<T>::makeArray(Args... args)
{
    return Array<T>{static_cast<T>(args)...};
}

template<typename T>
Array<T> Array<T>::slice(int start, int end) const 
{
    assert(start < end && "Start index must be less than end index");
    assert(start >= 0 && end <= m_size && "Indices out of range");

    int slice_size = end - start;
    Array<T> result(slice_size);
    std::copy(this->begin() + start, this->begin() + end, result.data());

    return result;
}


#endif

