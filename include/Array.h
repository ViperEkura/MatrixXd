#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <cassert>

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

    size_t size() const { return m_size; }
    
    SegmentResource<T> data() const { return m_data; }

    template <typename... Args>
    static Array<T> makeArray(Args... args);

    Array<T> slice(size_t start, size_t end) const;
    
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



// Array
template <typename T>
inline Array<T>::Array(std::vector<T> vec)
{
    m_size = vec.size();
    m_data = SegmentResource<T>(vec.size());
    T* ptr = m_data.data();

    for (size_t i = 0; i < vec.size(); ++i) ptr[i] = vec[i];
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

template <typename T>
template <typename... Args>
Array<T> Array<T>::makeArray(Args... args)
{
    std::vector<T> vec{static_cast<T>(args)...};
    return Array<T>(vec);
}

template<typename T>
Array<T> Array<T>::slice(size_t start, size_t end) const 
{
    assert(start < end && "Start index must be less than end index");
    assert(start >= 0 && end <= m_size && "Indices out of range");

    size_t slice_size = end - start;
    Array<T> result(slice_size);
    
    T* ptr = m_data.data();
    T* result_ptr = result.m_data.data();

    for (size_t i = 0; i < slice_size; ++i) 
        result_ptr[i] = ptr[start + i];

    return result;
}


#endif

