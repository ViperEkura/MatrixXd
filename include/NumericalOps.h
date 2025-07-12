#ifndef NUMERICAL_OPS_H
#define NUMERICAL_OPS_H


template<typename Tp>
void WAXPBY(Tp* x, Tp* y, Tp* z, int size, Tp alpha, Tp beta);

template<typename Tp>
void WAXMY(Tp* x, Tp* y, Tp* z, int size, Tp alpha);

template<typename Tp>
void WAXDY(Tp* x, Tp* y, Tp* z, int size, Tp alpha, Tp eps);

template<typename Tp>
Tp DDOT(Tp* x, Tp* y, Tp* z, int size);

template<typename Tp>
void MATMUL(Tp* lhs, Tp* rhs, Tp* out, int x, int y, int z, int batch);


// Operator
template<typename Tp>
void WAXPBY(Tp* x, Tp* y, Tp* z, int size, Tp alpha, Tp beta)
{
    for (int i = 0; i < size; ++i)
        z[i] = alpha * x[i] + beta * y[i];
}

template<typename Tp>
void WAXMY(Tp* x, Tp* y, Tp* z, int size, Tp alpha)
{
    for (int i = 0; i < size; ++i)
        z[i] = alpha * x[i] * y[i];
}

template<typename Tp>
void WAXDY(Tp* x, Tp* y, Tp* z, int size, Tp alpha, Tp eps)
{
    for (int i = 0; i < size; ++i)
        z[i] = alpha * x[i] / (y[i] + eps);
}

template<typename Tp>
Tp DDOT(Tp* x, Tp* y, Tp* z, int size)
{
    Tp sum = 0;
    for (int i = 0; i < size; i++)
        sum += x[i] * y[i];
    return sum;
}

template<typename Tp>
void MATMUL(Tp* lhs, Tp* rhs, Tp* out, int x, int y, int z, int batch)
{
    for (int b = 0; b < batch; ++b) {
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) {
                Tp sum = 0;
                for (int k = 0; k < z; ++k) {
                    sum += lhs[b * x * z + i * z + k] * rhs[b * z * y + k * y + j];
                    // sum += lhs[b, i, k] * rhs[b, k, j];
                }
                out[b * x * y + i * y + j] = sum;
                // out[b, i, j] = sum;
            }
        }
    }
}

#endif