#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLContext>
#include <QOpenGLShaderProgram>

#include <string>
using std::string;

class BaseGLWidget;

class Shader {

public:
    Shader(const char * vertex, const char * fragment);
    Shader();
    ~Shader();

    void bind();
    void release();

    void loadShaders(const char * vertex, const char * fragment);
    void loadShaderByPath(const QString& vsPath, const QString& fsPath, BaseGLWidget* glWidget = nullptr);

    int getUniformLocation(const char* name);

    void setMat4(const char * name, const QMatrix4x4& matrix);

    GLuint getProgramId();

private:
    QOpenGLShaderProgram * shaderProgram;
};

#endif // SHADER_H
