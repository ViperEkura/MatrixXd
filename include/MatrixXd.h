#ifndef MATRIX_XD_H
#define MATRIX_XD_H

template <typename T>
struct MatrixResource
{
    T* m_data_ptr;
    int* m_data_ref_cnt;

    MatrixResource() 
        : m_data_ptr(nullptr), m_data_ref_cnt(nullptr){}

    MatrixResource(T* data_ptr, int* data_ref_cnt) 
        : m_data_ptr(data_ptr), m_data_ref_cnt(data_ref_cnt){}
    
    MatrixResource(int resource_size) 
        : m_data_ptr(new T[resource_size]), m_data_ref_cnt(new int(1)){}

    MatrixResource(const MatrixResource<T>& other);

    MatrixResource<T>& operator=(const MatrixResource<T>& other);
    
    ~MatrixResource();
};


class MatrixBase
{
    MatrixResource<float> m_resource;
    MatrixBase(int size): m_resource(MatrixResource<float>(size)) {}

};




#endif