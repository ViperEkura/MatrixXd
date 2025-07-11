#ifndef MATRIXXD_CPP
#define MATRIXXD_CPP

#include "MatrixXd.h"


template<typename T> 
MatrixResource<T>::MatrixResource(const MatrixResource<T>& other)
{
    m_data_ptr = other.m_data_ptr;
    m_data_ref_cnt = other.m_data_ref_cnt;
    if(other.m_data_ref_cnt != nullptr) ++(*other.m_data_ref_cnt);
}

template <typename T>
MatrixResource<T>& MatrixResource<T>::operator=(const MatrixResource<T> &other)
{
    if(&other == this) return *this;
    if(m_data_ref_cnt != nullptr && --(*m_data_ref_cnt) == 0) delete[] m_data_ptr, delete m_data_ref_cnt;
    if(other.m_data_ptr != nullptr) ++(*other.m_data_ref_cnt);
    
    m_data_ptr = other.m_data_ptr;
    m_data_ref_cnt = other.m_data_ref_cnt;
}


template<typename T> 
MatrixResource<T>::~MatrixResource(){
    if(m_data_ref_cnt != nullptr && --(*m_data_ref_cnt) == 0)
    {
        delete[] m_data_ptr, delete m_data_ref_cnt;
        m_data_ptr = nullptr, m_data_ref_cnt = nullptr;
    }
}

#endif

