#include "shader.h"
#include "Utilities/helperFuncs.h"
using namespace LXY;

Shader::Shader(const char * vertex, const char * fragment) {

    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertex);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragment);

    if (shaderProgram->link()) {
        log() << "OK. linked shader program." << endl;
    } else {
        shaderProgram->log();
        logErr() << "error: link shader program failed." << endl;
    }
}

Shader::Shader() : shaderProgram(nullptr)
{

}

Shader::~Shader() {
    if (nullptr != shaderProgram) {
        delete shaderProgram;
        shaderProgram = nullptr;
    }
}


void Shader::bind() {
    if (nullptr != shaderProgram) {
        shaderProgram->bind();
    }
}

void Shader::release() {
    if (nullptr != shaderProgram) {
        shaderProgram->release();
    }
}

int Shader::getUniformLocation(const char* name)
{
    return shaderProgram->uniformLocation(name);
}

void Shader::setMat4(const char * name, const QMatrix4x4& matrix)
{
    int uniformLoc = shaderProgram->uniformLocation(name);
    shaderProgram->setUniformValue(uniformLoc, matrix);
}

void Shader::loadShaders(const char * vertex, const char * fragment)
{
    if (nullptr == shaderProgram)
    {
        shaderProgram = new QOpenGLShaderProgram();
    }
    if (shaderProgram->isLinked())
    {
        shaderProgram->bind();
        shaderProgram->removeAllShaders();
        shaderProgram->release();
    }

    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertex);
    shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragment);
    if (shaderProgram->link()) {
        log() << "OK. linked shader program." << endl;
    } else {
        shaderProgram->log();
        logErr() << "error: link shader program failed." << endl;
    }
}

void Shader::loadShaderByPath(const QString& vsPath, const QString& fsPath)
{
    if (vsPath.length() == 0 || fsPath.length() == 0)
    {
        logErr() << "Error.shader path is empty." << endl;
        return;
    }
    string vertexSource;
    string fragmentSource;

    if (vsPath.startsWith(":/"))
    {
        vertexSource = readFileToString2(vsPath);
    } else {
        vertexSource = readFileToString(vsPath);
    }

    if (fsPath.startsWith(":/"))
    {
        fragmentSource = readFileToString2(fsPath);
    } else {
        fragmentSource = readFileToString(fsPath);
    }

    loadShaders(vertexSource.c_str(), fragmentSource.c_str());
}
