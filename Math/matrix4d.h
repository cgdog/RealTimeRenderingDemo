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
    void operator=(const Matrix4D& mat4);
    float operator()(int r, int c) const;

    Matrix4D operator*(const Matrix4D& mat4);
    Matrix4D operator+(const Matrix4D& mat4);
    Matrix4D operator-(const Matrix4D& mat4);

    // https://zhuanlan.zhihu.com/p/78987582
    void rotate(float angle, float x, float y, float z);
    void translate(float x, float y, float z);
    void scale(float x, float y, float z);

    friend ostream & operator<<(ostream & out, const Matrix4D & matrix);
    friend istream & operator>>(istream & in, Matrix4D & matrix);

private:
    const static int N = 4;
    const static int N2 = N * N;
    float data[N2];
};

}

#endif // MATRIX4D_H
