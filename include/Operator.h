#ifndef OPERATOR_H
#define OPERATOR_H


template<typename Tp>
void WAXPBY(Tp* x, Tp* y, Tp* z, int size, Tp alpha, Tp beta);

template<typename Tp>
void WAXMY(Tp* x, Tp* y, Tp* z, int size, Tp alpha);

template<typename Tp>
Tp DDOT(Tp* x, Tp* y, Tp* z, int size);



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
Tp DDOT(Tp* x, Tp* y, Tp* z, int size)
{
    Tp sum = 0;
    for (int i = 0; i < size; i++)
        sum += x[i] * y[i];
    return sum;
}

#endif