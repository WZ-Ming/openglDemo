#ifndef MYOPENGLDEMO_H
#define MYOPENGLDEMO_H

#include<QDebug>
#include<QVector3D>
#include<QHash>
#include<QMultiHash>
#include<QPointer>
#include <QMouseEvent>
#include <QWheelEvent>
#include<QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include<GL/gl.h>
#include<GL/glu.h>

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
     Q_OBJECT
public:
    MyOpenGLWidget(QWidget* parent=nullptr);
    ~MyOpenGLWidget() override;

public slots:
    void receiveXAxisRotate(int axis,int degree);
    void receiveViewPar(const QVector<int>& vector);
    void receiveChangeModel(int num);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void wheelEvent(QWheelEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent*) override;

private:
    enum itemType{pointItem,lineItem,polygonsItem,sphereItem,cylinderItem,diskItem};
    struct axisRotateStruct{
      int axisSig;
      float rotateangle;
      axisRotateStruct(){}
      axisRotateStruct(int _axisSig,float _rotateangle){
          axisSig=_axisSig;
          rotateangle=_rotateangle;
      }
    };

    struct myGraphicsItem{
      QVector<QVector3D>  vectorPoint3f;
      QColor m_color;
      itemType m_itemType;
      QVector3D axisMovePos=QVector3D(0,0,0);
      QVector<axisRotateStruct> vectorAxisRotate;
    };

    struct currentStateStruct{
        int xRot=0;
        int yRot=0;
        int zRot=0;
        int xTran=0;
        int yTran=0;
        int zTran=0;
        int rDis=50;
        int angleXY=0;
        int angleYZ=0;
        Qt::MouseButton mousePressType;
        QPoint currentCursorPos=QPoint(0,0);

        QVector<QColor>currentColorsVector;
        QVector<myGraphicsItem*>currentSelectItemsVector;
    }currentState;

    QHash<myGraphicsItem*,QVector<myGraphicsItem*>>itemGroupHash;
    QMultiHash<int,myGraphicsItem*>itemsHash;
    const QVector<QColor>ignoreColorVector={Qt::white,Qt::black,Qt::darkGray};

public:
    void drawAxises();
    void drawPoint(const QVector3D &point,const QColor& color,const QVector3D& axisMovePos=QVector3D(0,0,0),const QVector<axisRotateStruct>&vectorAxisRotate=QVector<axisRotateStruct>());
    void drawLine(const QVector3D &beginPoint,const QVector3D &endPoint,const QColor& color,const QVector3D& axisMovePos=QVector3D(0,0,0),const QVector<axisRotateStruct>&vectorAxisRotate=QVector<axisRotateStruct>());
    void drawSphere(const QVector3D &basePoint,const float radius,const QColor& color,const QVector3D& axisMovePos=QVector3D(0,0,0),const QVector<axisRotateStruct>&vectorAxisRotate=QVector<axisRotateStruct>());
    void drawCube(const QVector3D &basePoint,const QVector3D &lengthWidthHeight, const QColor &color,const QVector3D& axisMovePos=QVector3D(0,0,0),const QVector<axisRotateStruct>&vectorAxisRotate=QVector<axisRotateStruct>());
    void drawNumber(QVector3D basePoint,int value, const float length,const QVector3D& axisMovePos=QVector3D(0,0,0),const QVector<axisRotateStruct>&vectorAxisRotate=QVector<axisRotateStruct>(),const float spaceBi=5, const float height=0.1f, const QColor &color=Qt::black);
    void drawCylinder(const QVector3D &basePoint, const QVector3D &radiusAndHeight, const int number, const float numberSize, const QColor& color0, const QColor& color1,const QVector3D& axisMovePos=QVector3D(0,0,0),const QVector<axisRotateStruct>&vectorAxisRotate=QVector<axisRotateStruct>());

private:
    void drawGraphics(const itemType type,const QVector<QVector3D> &vectorPoint3f,const QColor &color);
    myGraphicsItem* addGraphics(const itemType type, const QVector<QVector3D> &vectorPoint3f, const QVector3D &axisMovePos, const QVector<axisRotateStruct> &vectorAxisRotate, const QColor &color);

    QVector<QVector3D> LEDSide(const int sig, const float length, const float spaceBi, const float height, const QVector3D &vectorPoint3f);
    QVector<QVector3D> darwSingleNumber(const int value, const float length, const float spaceBi, const float height, const QVector3D vectorPoint3f);

    int getColorValue(const QColor &color);

};

#endif // MYOPENGLDEMO_H
