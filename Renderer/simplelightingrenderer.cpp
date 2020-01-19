#include "simplelightingrenderer.h"
#include <QOpenGLExtraFunctions>

SimpleLightingRenderer::SimpleLightingRenderer(QWidget *parent) :
    BaseGLWidget(parent)
{
}

SimpleLightingRenderer::SimpleLightingRenderer(int _lightNum, Vector4 _clearColor, QWidget *parent) :
    BaseGLWidget(_lightNum, _clearColor, parent)
{
}

SimpleLightingRenderer::~SimpleLightingRenderer()
{
}

void SimpleLightingRenderer::initializeGL()
{
    //BaseGLWidget::initializeGL();
    changeModelAndShaders(":/simpleLight.obj", QString(":/simpleLight.vs"), QString(":/simpleLight.fs"), false);
}

void SimpleLightingRenderer::resizeGL( int width, int height )
{
    BaseGLWidget::resizeGL(width, height);
}

void SimpleLightingRenderer::paintGL()
{
    QOpenGLFunctions *glFuncs = this->context()->functions();
    QOpenGLExtraFunctions* glExtraFuncs = context()->extraFunctions();

    glFuncs->glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glFuncs->glClearColor(clearColor.X(), clearColor.Y(), clearColor.Z(), clearColor.W());

    glFuncs->glEnable(GL_DEPTH_TEST);

    vao->bind();
    ebo->bind();
    m_shader->bind();

    Matrix4D viewMatrix = camera.lookAt();
    Matrix4D projection = camera.getPerspective(4.0f/3.0f, 0.1f, 100.0f);
    Matrix4D translation = model.getTransform().translate(0, 0, -2);
    Matrix4D projView = projection * viewMatrix;
    int uniformModelLoc = m_shader->getUniformLocation("uModel");
    glFuncs->glUniformMatrix4fv(uniformModelLoc, 1, GL_TRUE, translation.getData());

    int uniformViewProj = m_shader->getUniformLocation("viewProj");
    glFuncs->glUniformMatrix4fv(uniformViewProj, 1, GL_TRUE, projView.getData());

    for (int i = 0; i < lightNum; ++i)
    {
        int uniformLightLoc = m_shader->getUniformLocation(("uLights["+to_string(i)+"].position").c_str());
        glFuncs->glUniform4fv(uniformLightLoc, 1, lights[i].getPosition().getData());
        uniformLightLoc = m_shader->getUniformLocation(("uLights["+to_string(i)+"].color").c_str());
        glFuncs->glUniform4fv(uniformLightLoc, 1, lights[i].getColor().getData());
    }

    int uniformLightCount = m_shader->getUniformLocation("uLightCount");
    glExtraFuncs->glUniform1ui(uniformLightCount, static_cast<uint>(lightNum));

    int uniformWarmColor = m_shader->getUniformLocation("uWarmColor");
    glFuncs->glUniform3f(uniformWarmColor, 0.3f, 0.3f, 0.0f);

    int uniformEyePosLoc = m_shader->getUniformLocation("uEyePosition");
    auto cameraPos = camera.getPos();
    glFuncs->glUniform4f(uniformEyePosLoc, cameraPos.X(), cameraPos.Y(), cameraPos.Z(), 1.0f);

    int uniformFUnlit = m_shader->getUniformLocation("uFUnlit");
    glFuncs->glUniform3f(uniformFUnlit, 0.2f, 0.2f, 0.2f);

    GLsizei numFaceIndices = static_cast<GLsizei>(model.getIndices().size());
    glFuncs->glDrawElements(GL_TRIANGLES, numFaceIndices, GL_UNSIGNED_INT, nullptr);
    m_shader->release();
    ebo->release();
    vao->release();

    this->context()->swapBuffers(this->context()->surface());
}
