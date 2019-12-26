#include "matrix4d.h"
#include "Utilities/helperFuncs.h"

namespace LXY {

Matrix4D::Matrix4D()
{
    memset(data, 0, N2*sizeof(float));
    data[N2-1] = 1;
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
                res(i, j) += (*this)(i, k) + mat4(k, j);
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
        return data[r*c+c];
    }
    else
    {
        logErr() << "indices ("<<r <<", " << c << ") is out of range." <<endl;
        return data[0];
    }
}

float Matrix4D::operator()(int r, int c) const
{
    if (r >= 0 && r < N && c >= 0 && c < N)
    {
        return data[r*c+c];
    }
    else
    {
        logErr() << "indices ("<<r <<", " << c << ") is out of range." <<endl;
        return data[0];
    }
}

// to be optimized
void Matrix4D::rotate(float angle, float x, float y, float z)
{
    float c = cos(angle);
    float s = sin(angle);
    data[0] = c + (1 - c) * x * x;
    data[1] = (1 - c) * x * y - s * z;
    data[2] = (1 - c) * x * z + s * y;
    data[4] = (1 - c) * x * y + s * z;
    data[5] = c + (1 - c) * y * y;
    data[6] = (1 - c) * y * z - s * x;
    data[8] = (1 - c) * x * z - s * y;
    data[9] = (1 - c) * y * z + s * x;
    data[10] = c + (1 - c) * z * z;
}

void Matrix4D::translate(float x, float y, float z)
{
    data[3] = x;
    data[7] = y;
    data[11] = z;
}

void Matrix4D::scale(float x, float y, float z)
{
    data[0] *= x;
    data[5] *= y;
    data[10] *= z;
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
