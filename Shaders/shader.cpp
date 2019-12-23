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

Shader::~Shader() {
    if (nullptr != shaderProgram) {
        shaderProgram->bind();
        shaderProgram->removeAllShaders();
        shaderProgram->release();
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
