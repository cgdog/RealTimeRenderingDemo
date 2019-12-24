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

class BaseGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    BaseGLWidget(QWidget *parent=0);
    virtual ~BaseGLWidget() override;
    virtual QSize minimumSizeHint() const override;
    virtual QSize sizeHint() const override;
    virtual void setClearColor(const QColor &color);

protected:
    virtual void initializeGL() override = 0;
    virtual void resizeGL( int width, int height ) override = 0;
    virtual void paintGL() override = 0;

    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

protected slots:


protected:
    QOpenGLBuffer *m_vbo;
    QOpenGLVertexArrayObject *m_vao;
    QOpenGLShaderProgram *m_shader;

    Model model;

    QTimer *m_timer;
    QColor clearColor;
    QPoint lastPos;

};

#endif // BASEGLWIDGET_H
