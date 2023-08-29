#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtOpenGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sendAxisRotate(int axis,int degree);
    void sendViewPar(const QVector<int>& vector);

private slots:
    void on_VSlider_xAxis_valueChanged(int value);

    void on_VSlider_yAxis_valueChanged(int value);

    void on_VSlider_zAxis_valueChanged(int value);

    void on_pBtn_mainView_clicked();

    void on_pBtn_TopView_clicked();

    void on_pushButton_bottomView_clicked();

    void on_pushButton_behindView_clicked();

    void on_pBtn_leftView_clicked();

    void on_pBtn_rightView_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
