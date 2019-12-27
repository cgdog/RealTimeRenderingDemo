#include "matrix4d.h"
#include "Utilities/helperFuncs.h"

namespace LXY {

Matrix4D::Matrix4D()
{
    memset(data, 0, N2*sizeof(float));
    //data[N2-1] = 1;
}

Matrix4D::Matrix4D(const Matrix4D& mat4)
{
    for (int i = 0; i < N2; ++i)
    {
        data[i] = mat4.data[i];
    }
}

Matrix4D::~Matrix4D()
{
}

float* Matrix4D::getData()
{
    return data;
}

void Matrix4D::operator=(const Matrix4D& mat4)
{
    if (this != &mat4)
    {
        for (int i = 0; i < N2; ++i)
        {
            data[i] = mat4.data[i];
        }
    }
}

Matrix4D Matrix4D::operator*(const Matrix4D& mat4)
{
    Matrix4D res;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < N; ++k)
            {
                res(i, j) += (*this)(i, k) * mat4(k, j);
            }
        }
    }
    return res;
}

Matrix4D Matrix4D::operator+(const Matrix4D& mat4)
{
    Matrix4D res;
    for (int i = 0; i < N2; ++i)
    {
        res.data[i] = data[i] + mat4.data[i];
    }
    return res;
}

Matrix4D Matrix4D::operator-(const Matrix4D& mat4)
{
    Matrix4D res;
    for (int i = 0; i < N2; ++i)
    {
        res.data[i] = data[i] - mat4.data[i];
    }
    return res;
}

float& Matrix4D::operator()(int r, int c)
{
    if (r >= 0 && r < N && c >= 0 && c < N)
    {
        return data[r*N+c];
    }
    else
    {
        logErr() << "indices ("<<r <<", " << c << ") is out of range." <<endl;
        return data[0];
    }
}

float& Matrix4D::operator[](int index)
{
    assert(index >= 0 && index < N2);
    return data[index];
}

float Matrix4D::operator[](int index) const
{
    assert(index >= 0 && index < N2);
    return data[index];
}

float Matrix4D::operator()(int r, int c) const
{
    if (r >= 0 && r < N && c >= 0 && c < N)
    {
        return data[r*N+c];
    }
    else
    {
        logErr() << "indices ("<<r <<", " << c << ") is out of range." <<endl;
        return data[0];
    }
}


ostream & operator<<(ostream & out, const Matrix4D & matrix)
{
    int row = 0;
    for (int i = 0; i < matrix.N2; ++i)
    {
        ++row;
        if (row == 4)
        {
            row = 0;
            out << matrix.data[i] << endl;
        }
        else {
            out << matrix.data[i] << " ";
        }
    }
    return out;
}

istream & operator>>(istream & in, Matrix4D & matrix)
{
    float num;
    int i = 0;
    while (in >> num && i < matrix.N2)
    {
        matrix.data[i++] = num;
    }
    return in;
}


}
