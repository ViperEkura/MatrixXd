#ifndef MATRIXXD_CPP
#define MATRIXXD_CPP

#include "MatrixXd.h"


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


template <typename T>
inline Array<T>::Array(const Array<T> &other){
    m_data = other.m_data;
    m_size = other.m_size;
}


template<class T> 
Array<T> &Array<T>::operator=(const Array<T> &other)
{
    m_data = other.m_data;
    m_size = other.m_size;
}


template<class T> 
Array<T>::~Array(){
    // do nothing
}



#endif

