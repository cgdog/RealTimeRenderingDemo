#ifndef MATRIX4D_H
#define MATRIX4D_H
#include <iostream>
using namespace std;

namespace LXY {

class Matrix4D
{
public:
    Matrix4D();
    Matrix4D(const Matrix4D& mat4);
    ~Matrix4D();

    float* getData();

    float& operator()(int r, int c);
    float& operator[](int index);
    float operator[](int index) const;
    void operator=(const Matrix4D& mat4);
    float operator()(int r, int c) const;

    Matrix4D operator*(const Matrix4D& mat4);
    Matrix4D operator+(const Matrix4D& mat4);
    Matrix4D operator-(const Matrix4D& mat4);


    friend ostream & operator<<(ostream & out, const Matrix4D & matrix);
    friend istream & operator>>(istream & in, Matrix4D & matrix);

private:
    const static int N = 4;
    const static int N2 = N * N;
    float data[N2];
};

}

#endif // MATRIX4D_H
