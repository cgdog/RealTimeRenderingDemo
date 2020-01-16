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
    //http://www.lighthouse3d.com/tutorials/glsl-tutorial/uniform-blocks/
    //https://doc.qt.io/qt-5/qopenglextrafunctions.html#glGetUniformBlockIndex
    //https://blog.csdn.net/wangdingqiaoit/article/details/52717963
    //BaseGLWidget::paintGL();

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

    GLuint lightUBlockIndex = glExtraFuncs->glGetUniformBlockIndex(m_shader->getProgramId(), "LightUBlock");

    for (int i = 0; i < lightNum; ++i)
    {
        auto indexStr = ("uLights["+to_string(i+1)+"].position").c_str();
        int uniformLightLoc = m_shader->getUniformLocation("uLights[0].position");
        glFuncs->glUniform4fv(uniformLightLoc, 1, lights[i].getPosition().getData());
        indexStr = ("uLights["+to_string(i)+"].color").c_str();
        uniformLightLoc = m_shader->getUniformLocation("uLights[0].color");
        glFuncs->glUniform4fv(uniformLightLoc, 1, lights[i].getColor().getData());
    }

    int uniformLightCount = m_shader->getUniformLocation("uLightCount");
    glFuncs->glUniform1i(uniformLightCount, lightNum);

    int uniformEyePosLoc = m_shader->getUniformLocation("uEyePosition");
    auto cameraPos = camera.getPos();
    glFuncs->glUniform4f(uniformEyePosLoc, cameraPos.X(), cameraPos.Y(), cameraPos.Z(), 1.0f);

    GLsizei numFaceIndices = static_cast<GLsizei>(model.getIndices().size());
    glFuncs->glDrawElements(GL_TRIANGLES, numFaceIndices, GL_UNSIGNED_INT, nullptr);
    m_shader->release();
    ebo->release();
    vao->release();

    this->context()->swapBuffers(this->context()->surface());
}
