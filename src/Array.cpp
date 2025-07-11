#ifndef ARRAY_CPP
#define ARRAY_CPP

#include "Array.h"


// SegmentResource

template<typename T> 
SegmentResource<T>::SegmentResource(const SegmentResource<T>& other)
{
    m_data_ptr = other.m_data_ptr;
    m_data_ref_cnt = other.m_data_ref_cnt;
    if(other.m_data_ref_cnt != nullptr) ++(*other.m_data_ref_cnt);
}

template <typename T>
SegmentResource<T>& SegmentResource<T>::operator=(const SegmentResource<T> &other)
{
    if(&other == this) return *this;
    if(m_data_ref_cnt != nullptr && --(*m_data_ref_cnt) == 0) delete[] m_data_ptr, delete m_data_ref_cnt;
    if(other.m_data_ptr != nullptr) ++(*other.m_data_ref_cnt);
    
    m_data_ptr = other.m_data_ptr;
    m_data_ref_cnt = other.m_data_ref_cnt;
}


template<typename T> 
SegmentResource<T>::~SegmentResource(){
    if(m_data_ref_cnt != nullptr && --(*m_data_ref_cnt) == 0)
    {
        delete[] m_data_ptr, delete m_data_ref_cnt;
        m_data_ptr = nullptr, m_data_ref_cnt = nullptr;
    }
}



// Array
template <typename T>
Array<T>::Array(std::vector<T> vec)
{
    m_size = vec.size();
    m_data = SegmentResource<T>(vec.size());
    for(int i = 0; i < vec.size(); ++i) m_data.m_data_ptr[i] = vec[i];
}

template <typename T>
inline Array<T>::Array(const Array<T> &other)
{
    m_data = other.m_data;
    m_size = other.m_size;
}

template<class T> 
inline Array<T> &Array<T>::operator=(const Array<T> &other)
{
    m_data = other.m_data;
    m_size = other.m_size;
}


template<class T> 
Array<T>::~Array(){
    // do nothing
}

template <typename T>
template <typename... Args>
Array<T>::Array(T first, Args... args)
{
    std::vector<T> vec = {first, args...};
    m_size = vec.size();
    m_data = SegmentResource<T>(vec.size());
    for(int i = 0; i < vec.size(); ++i) m_data.m_data_ptr[i] = vec[i];
}

template <typename T>
template <typename... Args>
inline Array<T> Array<T>::makeArray(T first, Args... args)
{
    std::vector<T> vec = {first, args...};
    return Array<T>(vec);
}

#endif

