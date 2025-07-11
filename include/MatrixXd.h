#ifndef MATRIX_XD_H
#define MATRIX_XD_H

#include <vector>



template <typename T> class SegmentResource;
template <typename T> class Array;
template <typename T> class View;

template<typename T, typename... Args>
std::vector<T> makeVector(T first, Args... args) 
{
    return {first, args...};
}

template<typename T, typename... Args>
Array<T> makeArray(T first, Args... args) 
{
    std::vector<T> vec = makeVector(first, args...);
    return Array<T>(vec);
}


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

    T* data() const { return m_data_ptr; }
    int refCount() const { return m_data_ref_cnt ? *m_data_ref_cnt : 0; }

};


template <typename T>
class Array
{

private:
    SegmentResource<T> m_data;
    size_t m_size;
public:
    Array(size_t size)
        : m_data(SegmentResource<T>(size)), m_size(size){}
    
    Array(std::vector<T> vec);

    Array(const Array<T>& other);
    Array<T>& operator=(const Array<T>& other);
    ~Array();

    size_t size() const { return m_size; }
    SegmentResource<T> data() const { return m_data; }
};


template <typename T>
class View
{
public:
    static View<T> createView(Array<T> data, View<T> view)
    {

    }
};

#endif