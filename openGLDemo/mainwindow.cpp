#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType<QVector<int>>("QVector<int>");
    qRegisterMetaType<QVector<int>>("QVector<int>&");
    connect(this,&MainWindow::sendAxisRotate,ui->openGLWidget,&MyOpenGLWidget::receiveXAxisRotate);
    connect(this,&MainWindow::sendViewPar,ui->openGLWidget,&MyOpenGLWidget::receiveViewPar);
    connect(ui->comboBox,SIGNAL(activated(int)),ui->openGLWidget,SLOT(receiveChangeModel(int)));
    ui->label->setText(QString::number(ui->VSlider_xAxis->value())+","+QString::number(ui->VSlider_yAxis->value())+","+QString::number(ui->VSlider_zAxis->value()));
    ui->comboBox->setCurrentIndex(1);
    ui->comboBox->activated(ui->comboBox->currentIndex());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_VSlider_xAxis_valueChanged(int value)
{
    emit sendAxisRotate(0,value);
    ui->label->setText(QString::number(ui->VSlider_xAxis->value())+","+QString::number(ui->VSlider_yAxis->value())+","+QString::number(ui->VSlider_zAxis->value()));
}

void MainWindow::on_VSlider_yAxis_valueChanged(int value)
{
    emit sendAxisRotate(1,value);
    ui->label->setText(QString::number(ui->VSlider_xAxis->value())+","+QString::number(ui->VSlider_yAxis->value())+","+QString::number(ui->VSlider_zAxis->value()));
}

void MainWindow::on_VSlider_zAxis_valueChanged(int value)
{
    emit sendAxisRotate(2,value);
    ui->label->setText(QString::number(ui->VSlider_xAxis->value())+","+QString::number(ui->VSlider_yAxis->value())+","+QString::number(ui->VSlider_zAxis->value()));
}

void MainWindow::on_pBtn_mainView_clicked()
{
    QVector<int> vector(8,0);
    sendViewPar(vector);
}

void MainWindow::on_pushButton_behindView_clicked()
{
    QVector<int> vector(8,0);
    vector[2]=180;
    sendViewPar(vector);
}

void MainWindow::on_pBtn_TopView_clicked()
{
    QVector<int> vector(8,0);
    vector[0]=-90;
    sendViewPar(vector);
}

void MainWindow::on_pushButton_bottomView_clicked()
{
    QVector<int> vector(8,0);
    vector[0]=90;
    sendViewPar(vector);
}


void MainWindow::on_pBtn_leftView_clicked()
{
    QVector<int> vector(8,0);
    vector[2]=90;
    sendViewPar(vector);
}

void MainWindow::on_pBtn_rightView_clicked()
{
    QVector<int> vector(8,0);
    vector[2]=-90;
    sendViewPar(vector);
}
