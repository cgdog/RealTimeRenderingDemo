#ifndef BASEGLWIDGET_H
#define BASEGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QMouseEvent>

#include "Models/model.h"
#include <string>
#include "Shaders/shader.h"
#include "Models/camera.h"
#include "Models/light.h"
#include "Utilities/timemanager.h"

using std::string;

class BaseGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    BaseGLWidget(QWidget *parent=nullptr);
    BaseGLWidget(int _lightNum, Vector4 _clearColor=Vector4(0.0f, 0.0f, 0.0f, 1.0f), QWidget *parent=nullptr);
    virtual ~BaseGLWidget() override;
    virtual QSize minimumSizeHint() const override;
    virtual QSize sizeHint() const override;
    virtual void setClearColor(const Vector4 &color);
    virtual void changeModel(const string& modelPath, bool isUpdateGL = true);
    virtual void changeShaders(const QString& vsPath, const QString& fsPath, bool isUpdateGL = true);
    virtual void changeModelAndShaders(const string& modelPath, const QString& vsPath, const QString& fsPath, bool isUpdateGL = true);
    virtual void changeLight();
    virtual void preProcessShader(string& vs, string& fs);
    virtual void loadViewMatrix(const string& path);
    virtual void loadDefaultViewMatrix(const string& path);
    void loadViewMatrixByModelPath(const string& modelPath);
    virtual void saveViewMatrix();

    int getLightNum();

protected:
    virtual void initializeGL() override;
    virtual void resizeGL( int width, int height) override;
    virtual void paintGL() override;

    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

protected slots:


protected:
    QOpenGLBuffer *vbo;
    QOpenGLBuffer *ebo;
    QOpenGLVertexArrayObject *vao;
    Shader * m_shader;

    Model model;

    QTimer *timer;
    Vector4 clearColor;
    QPoint lastPos;

    Camera camera;
    int lightNum;
    Light* lights;

    LXY::TimeManager timeManaer;
    int deltaTime;
    int lastTime;

    float rotationFactor = 0.02f;
    int xRot;
    int yRot;
    int zRot;
};

#endif // BASEGLWIDGET_H
