#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLContext>
#include <QOpenGLShaderProgram>

#include <string>
using std::string;

class Shader {

public:
    Shader(const char * vertex, const char * fragment);
    ~Shader();

    void bind();
    void release();

private:
    QOpenGLShaderProgram * shaderProgram;
};

#endif // SHADER_H
