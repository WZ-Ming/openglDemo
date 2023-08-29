#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent):
    QOpenGLWidget(parent)
{
    this->setMouseTracking(true);    
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    for(QMultiHash<int,myGraphicsItem*>::iterator it=itemsHash.begin();it!=itemsHash.end();it++)
        delete it.value();
    itemsHash.clear();
}

void MyOpenGLWidget::receiveChangeModel(int num)
{
    for(QMultiHash<int,myGraphicsItem*>::iterator it=itemsHash.begin();it!=itemsHash.end();it++)
        delete it.value();
    itemsHash.clear();
    itemGroupHash.clear();
    currentState.currentColorsVector.clear();
    currentState.currentSelectItemsVector.clear();

    int lengthNum=10,widthNum=10,oneCircleNum=20,heightNum=10;
    float hairRadius=0.5,hairHeight=4;
    const float itemSpace=2*hairRadius+hairRadius;
    float cylinderRadius=5,cylinderHeight=itemSpace*heightNum+1;
    float numberSize=0.25f;

    int oneCircleNumTmp=oneCircleNum;
    int countTmp=0;
    const int colorCh=50;
    int colorR=0,colorG=0,colorB=0;
    const int baseColorR0=250,baseColorG0=250,baseColorB0=0;
    const int baseColorR1=0,baseColorG1=128,baseColorB1=0;
    switch (num) {
    case 0:{
        for(int i=0;i<lengthNum;i++){
            for(int j=0;j<widthNum;j++){
                countTmp++;
                if(colorB++>=colorCh){
                    colorB=0;
                    if(colorG++>=colorCh){
                        colorG=0;
                        if(colorR++>=colorCh)
                            colorR=0;
                    }
                }
                drawCylinder(QVector3D(-itemSpace*lengthNum/2+itemSpace*i+itemSpace/2,-itemSpace*widthNum/2+itemSpace*j+itemSpace/2,0),QVector3D(hairRadius,hairRadius,hairHeight),countTmp,numberSize,QColor(baseColorR0+colorR,baseColorG0+colorG,baseColorB0+colorB),QColor(baseColorR1,baseColorG1+colorG,baseColorB1+colorB));
            }
        }
        drawCube(QVector3D(0,0,-itemSpace),QVector3D(lengthNum*itemSpace,widthNum*itemSpace,itemSpace),ignoreColorVector[2]);
    }break;
    case 1:{
        drawCylinder(QVector3D(0,0,-cylinderHeight/2),QVector3D(cylinderRadius,cylinderRadius,cylinderHeight),0,numberSize,ignoreColorVector[2],ignoreColorVector[2]);
        for(int i=0;i<heightNum;i++){
            for(int j=0;j<oneCircleNum;j++){
                countTmp++;
                if(colorB++>=colorCh){
                    colorB=0;
                    if(colorG++>=colorCh){
                        colorG=0;
                        if(colorR++>=colorCh)
                            colorR=0;
                    }
                }
                QVector<axisRotateStruct>vectorAxisRotate;
                vectorAxisRotate.append(axisRotateStruct(0,90));
                vectorAxisRotate.append(axisRotateStruct(1,360/oneCircleNum*j+90));
                drawCylinder(QVector3D(0,0,0),QVector3D(hairRadius,hairRadius,hairHeight),countTmp,numberSize,QColor(baseColorR0+colorR,baseColorG0+colorG,baseColorB0+colorB),QColor(baseColorR1,baseColorG1+colorG,baseColorB1+colorB),QVector3D(cylinderRadius*qCos((float)j/oneCircleNum*2*M_PI),cylinderRadius*qSin((float)j/oneCircleNum*2*M_PI),-cylinderHeight/2+(i+0.5)/heightNum*cylinderHeight),vectorAxisRotate);
            }
        }
    }break;
    case 2:{
        drawSphere(QVector3D(0,0,0),cylinderRadius,ignoreColorVector[2]);
        for(int i=0;i<=heightNum;i++){
            if(i==0 || i==heightNum)
                oneCircleNum=1;
            else if(i==1 || i==heightNum-1)
                oneCircleNum=oneCircleNumTmp/2;
            else
                oneCircleNum=oneCircleNumTmp;
            for(int j=0;j<oneCircleNum;j++){
                countTmp++;
                if(colorB++>=colorCh){
                    colorB=0;
                    if(colorG++>=colorCh){
                        colorG=0;
                        if(colorR++>=colorCh)
                            colorR=0;
                    }
                }
                QVector<axisRotateStruct>vectorAxisRotate;
                vectorAxisRotate.append(axisRotateStruct(2,(float)j/oneCircleNum*360));
                vectorAxisRotate.append(axisRotateStruct(1,180-(float)(i)/heightNum*180));
                vectorAxisRotate.append(axisRotateStruct(2,90));
                drawCylinder(QVector3D(0,0,0),QVector3D(hairRadius,hairRadius,hairHeight),countTmp,numberSize,QColor(baseColorR0+colorR,baseColorG0+colorG,baseColorB0+colorB),QColor(baseColorR1,baseColorG1+colorG,baseColorB1+colorB),QVector3D(cylinderRadius*cos((-90+(float)(i)/heightNum*180)/180*M_PI)*cos((float)j/oneCircleNum*2*M_PI),cylinderRadius*cos((-90+(float)(i)/heightNum*180)/180*M_PI)*sin((float)j/oneCircleNum*2*M_PI),cylinderRadius*sin((-90+(float)(i)/heightNum*180)/180*M_PI)),vectorAxisRotate);
            }
        }
    }break;
    case 3:{
        drawSphere(QVector3D(0,0,0),cylinderRadius,ignoreColorVector[2]);
        for(int i=heightNum/2;i<=heightNum;i++){
            if(i==0 || i==heightNum)
                oneCircleNum=1;
            else if(i==1 || i==heightNum-1)
                oneCircleNum=oneCircleNumTmp/2;
            else
                oneCircleNum=oneCircleNumTmp;
            for(int j=0;j<oneCircleNum;j++){
                countTmp++;
                if(colorB++>=colorCh){
                    colorB=0;
                    if(colorG++>=colorCh){
                        colorG=0;
                        if(colorR++>=colorCh)
                            colorR=0;
                    }
                }
                QVector<axisRotateStruct>vectorAxisRotate;
                vectorAxisRotate.append(axisRotateStruct(2,(float)j/oneCircleNum*360));
                vectorAxisRotate.append(axisRotateStruct(1,180-(float)(i)/heightNum*180));
                vectorAxisRotate.append(axisRotateStruct(2,90));
                drawCylinder(QVector3D(0,0,0),QVector3D(hairRadius,hairRadius,hairHeight),countTmp,numberSize,QColor(baseColorR0+colorR,baseColorG0+colorG,baseColorB0+colorB),QColor(baseColorR1,baseColorG1+colorG,baseColorB1+colorB),QVector3D(cylinderRadius*cos((-90+(float)(i)/heightNum*180)/180*M_PI)*cos((float)j/oneCircleNum*2*M_PI),cylinderRadius*cos((-90+(float)(i)/heightNum*180)/180*M_PI)*sin((float)j/oneCircleNum*2*M_PI),cylinderRadius*sin((-90+(float)(i)/heightNum*180)/180*M_PI)),vectorAxisRotate);
            }
        }

        heightNum/=2;
        oneCircleNum=oneCircleNumTmp;
        drawCylinder(QVector3D(0,0,-cylinderHeight/2),QVector3D(cylinderRadius,cylinderRadius,cylinderHeight/2),0,numberSize,ignoreColorVector[2],ignoreColorVector[2]);
        for(int i=0;i<heightNum;i++){
            for(int j=0;j<oneCircleNum;j++){
                countTmp++;
                if(colorB++>=colorCh){
                    colorB=0;
                    if(colorG++>=colorCh){
                        colorG=0;
                        if(colorR++>=colorCh)
                            colorR=0;
                    }
                }
                QVector<axisRotateStruct>vectorAxisRotate;
                vectorAxisRotate.append(axisRotateStruct(0,90));
                vectorAxisRotate.append(axisRotateStruct(1,360/oneCircleNum*j+90));
                drawCylinder(QVector3D(0,0,0),QVector3D(hairRadius,hairRadius,hairHeight),countTmp,numberSize,QColor(baseColorR0+colorR,baseColorG0+colorG,baseColorB0+colorB),QColor(baseColorR1,baseColorG1+colorG,baseColorB1+colorB),QVector3D(cylinderRadius*qCos((float)j/oneCircleNum*2*M_PI),cylinderRadius*qSin((float)j/oneCircleNum*2*M_PI),-cylinderHeight/2+(float)i/heightNum*cylinderHeight/2),vectorAxisRotate);
            }
        }
    }break;
    case 4:{
        double fCamPara[12]={300,30,30,0,0,1,6,2,1,5,10};
//        fCamPara[1]：x方向总长度
//        fCamPara[2]：x方向孔距
//        fCamPara[3][：排间距
//        fCamPara[4]：螺旋角度
//        fCamPara[5]：Z轴旋转方向
//        fCamPara[6]：加工方向
//        fCamPara[7]：皮数
//        fCamPara[8]：毛数
//        fCamPara[9]：条数
//        fCamPara[10]：皮数
//        fCamPara[11]：毛数

//        int vNum=
        double holeVDis=10,holeHDis=10;
        const int vNum=50,hNum=20;
        const int firstHolesNum=6,remainingHolesNum=5;
        const double radius=10,height=20;
        bool moveDir=true;

        double offsetAngle=360.0/vNum/2*hNum;

        drawCylinder(QVector3D(0,0,-height/2),QVector3D(radius,radius,height),0,numberSize,ignoreColorVector[2],ignoreColorVector[2]);

        QVector<QVector3D>vectorPos;
        for(int i=0;i<hNum;i++){
            for(int j=0;j<vNum;j++){
                countTmp++;
                double angle=0;
                QColor color;
                int k=0;
                if(moveDir)
                    k=j;
                else
                    k=vNum-1-j;
                angle=360.0/vNum*k+offsetAngle/hNum*i;//
                if(k==0)
                    color=Qt::green;
                else if(k>firstHolesNum && k<=vNum-firstHolesNum && (k-firstHolesNum-1)%(remainingHolesNum+1)==0)
                    color=Qt::green;
                else
                    color=Qt::yellow;
//                QVector3D vector3D(radius*cos(angle/180*M_PI),radius*sin(angle/180*M_PI),-height/2+height/(hNum-1)*i);
//                drawSphere(vector3D,0.3,color);
                QVector<axisRotateStruct>vectorAxisRotate;
                vectorAxisRotate.append(axisRotateStruct(0,90));
                vectorAxisRotate.append(axisRotateStruct(1,angle+90));
                drawCylinder(QVector3D(0,0,0),QVector3D(hairRadius,hairRadius,hairHeight),countTmp,numberSize,color,color,
                             QVector3D(radius*cos(angle/180*M_PI),radius*sin(angle/180*M_PI),-height/2+height/(hNum-1)*i),vectorAxisRotate);
            }
            moveDir=!moveDir;
        }
    }break;
    }
    update();
}

void MyOpenGLWidget::initializeGL()
{
    this->initializeOpenGLFunctions();    //为当前上下文初始化提供OpenGL函数解析
    glEnable(GL_DEPTH_TEST);
    glClearColor(ignoreColorVector[1].red(),ignoreColorVector[1].green(),ignoreColorVector[1].blue(),ignoreColorVector[1].alpha());
    //glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glDepthFunc( GL_LEQUAL );
    glShadeModel(GL_FLAT);
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0.0f,0.0f,w,h);     //重置当前的视口（Viewport）。
    glMatrixMode( GL_PROJECTION );//选择投影矩阵。
    glLoadIdentity();//重置投影矩阵。
    gluPerspective( 45.0, static_cast<double>(w)/static_cast<double>(h), 0.1, 100.0 );//建立透视投影矩阵。
    glMatrixMode( GL_MODELVIEW );//选择模型观察矩阵。
    //glLoadIdentity();//重置模型观察矩阵。
//    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
//    glEnable(GL_DEPTH_TEST);
}

void MyOpenGLWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );//清楚屏幕和深度缓存。
    glLoadIdentity();//重置当前的模型观察矩阵。

    double xDis=currentState.rDis*cos(static_cast<double>(currentState.angleYZ)/180*M_PI)*sin(static_cast<double>(currentState.angleXY)/180*M_PI);
    double yDis=currentState.rDis*cos(static_cast<double>(currentState.angleYZ)/180*M_PI)*cos(static_cast<double>(currentState.angleXY)/180*M_PI);
    double zDis=currentState.rDis*sin(static_cast<double>(currentState.angleYZ)/180*M_PI);
    gluLookAt(xDis,-yDis,zDis,0,0,0,0,0,1);

    glTranslatef(currentState.xTran,currentState.yTran,currentState.zTran);
    glRotatef( currentState.xRot,  1.0,  0.0,  0.0 );
    glRotatef( currentState.yRot,  0.0,  1.0,  0.0 );
    glRotatef( currentState.zRot,  0.0,  0.0,  1.0 );//根据xRot、yRot、zRot的实际值来旋转正方体。

    drawAxises();
    for(QMultiHash<int,myGraphicsItem*>::const_iterator it=itemsHash.constBegin();it!=itemsHash.constEnd();it++){
        glTranslatef(it.value()->axisMovePos.x(),it.value()->axisMovePos.y(),it.value()->axisMovePos.z());
        for(int i=0;i<it.value()->vectorAxisRotate.size();i++){
            switch (it.value()->vectorAxisRotate[i].axisSig) {
                case 0:glRotatef( it.value()->vectorAxisRotate[i].rotateangle,  1.0,  0.0,  0.0 );break;
                case 1:glRotatef( it.value()->vectorAxisRotate[i].rotateangle,  0.0,  1.0,  0.0 );break;
                case 2:glRotatef( it.value()->vectorAxisRotate[i].rotateangle,  0.0,  0.0,  1.0 );break;
            }
        }
        drawGraphics(it.value()->m_itemType,it.value()->vectorPoint3f,it.value()->m_color);
        for(int i=it.value()->vectorAxisRotate.size()-1;i>=0;i--){
            switch (it.value()->vectorAxisRotate[i].axisSig) {
                case 0:glRotatef( -it.value()->vectorAxisRotate[i].rotateangle,  1.0,  0.0,  0.0 );break;
                case 1:glRotatef( -it.value()->vectorAxisRotate[i].rotateangle,  0.0,  1.0,  0.0 );break;
                case 2:glRotatef( -it.value()->vectorAxisRotate[i].rotateangle,  0.0,  0.0,  1.0 );break;
            }
        }
        glTranslatef(-it.value()->axisMovePos.x(),-it.value()->axisMovePos.y(),-it.value()->axisMovePos.z());
    }
}

int MyOpenGLWidget::getColorValue(const QColor &color)
{
    return color.red()+color.green()*256+color.blue()*256*256;
}

void MyOpenGLWidget::drawPoint(const QVector3D &point,const QColor& color,const QVector3D& axisMovePos,const QVector<axisRotateStruct>&vectorAxisRotate)
{
    QVector<QVector3D> vector3f;
    QVector<myGraphicsItem *>itemVector;
    vector3f.append(point);
    itemVector.append(addGraphics(pointItem,vector3f,axisMovePos,vectorAxisRotate,color));
    foreach(myGraphicsItem* itemTmp,itemVector)
        itemGroupHash.insert(itemTmp,itemVector);
}

void MyOpenGLWidget::drawLine(const QVector3D &beginPoint,const QVector3D &endPoint,const QColor& color,const QVector3D& axisMovePos,const QVector<axisRotateStruct>&vectorAxisRotate)
{
    QVector<QVector3D> vector3f;
    QVector<myGraphicsItem *>itemVector;
    vector3f.append(beginPoint);
    vector3f.append(endPoint);
    itemVector.append(addGraphics(lineItem,vector3f,axisMovePos,vectorAxisRotate,color));
    foreach(myGraphicsItem* itemTmp,itemVector)
        itemGroupHash.insert(itemTmp,itemVector);
}

void MyOpenGLWidget::drawSphere(const QVector3D &basePoint,const float radius,const QColor& color,const QVector3D& axisMovePos,const QVector<axisRotateStruct>&vectorAxisRotate)
{
    QVector<QVector3D> vector3f;
    QVector<myGraphicsItem *>itemVector;
    vector3f.append(basePoint);
    vector3f.append(QVector3D(radius,20,20));
    itemVector.append(addGraphics(sphereItem,vector3f,axisMovePos,vectorAxisRotate,color));
    foreach(myGraphicsItem* itemTmp,itemVector)
        itemGroupHash.insert(itemTmp,itemVector);
}

MyOpenGLWidget::myGraphicsItem* MyOpenGLWidget::addGraphics(const itemType type, const QVector<QVector3D> &vectorPoint3f, const QVector3D& axisMovePos, const QVector<axisRotateStruct>& vectorAxisRotate, const QColor &color)
{
    myGraphicsItem *itemTmp=new myGraphicsItem;
    itemTmp->m_itemType=type;
    itemTmp->m_color=color;
    itemTmp->vectorPoint3f=vectorPoint3f;
    itemTmp->axisMovePos=axisMovePos;
    itemTmp->vectorAxisRotate=vectorAxisRotate;
    itemsHash.insert(getColorValue(color),itemTmp);
    return itemTmp;
}

void MyOpenGLWidget::drawNumber(QVector3D basePoint, int value, const float length, const QVector3D& axisMovePos, const QVector<axisRotateStruct>& vectorAxisRotate, const float spaceBi, const float height, const QColor &color)
{
    QVector<int> vector;
    QVector<QVector3D> vector3D;
    while (value>0) {
        vector.append(value%10);
        value/=10;
    }
    float space=length/spaceBi;
    basePoint.setX(basePoint.x()-(vector.size()*length+(vector.size()-1)*space)/2);
    basePoint.setY(basePoint.y()+length);
    for(int i=0;i<vector.size();i++)
        vector3D.append(darwSingleNumber(vector[vector.size()-1-i],length,spaceBi,height,QVector3D(basePoint.x()+(space+length)*i,basePoint.y(),basePoint.z())));
    if(vector.size()>0)
        addGraphics(polygonsItem,vector3D,axisMovePos,vectorAxisRotate,color);
}

void MyOpenGLWidget::drawCube(const QVector3D &basePoint,const QVector3D &lengthWidthHeight, const QColor &color,const QVector3D& axisMovePos, const QVector<axisRotateStruct>& vectorAxisRotate)
{
    QVector<QVector3D> vector3DTmp;

    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()));
    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()));
    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()));
    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()));

    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));
    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));
    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));
    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));

    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()));
    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));
    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));
    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()));

    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()));
    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));
    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));
    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()));

    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()));
    vector3DTmp.append(QVector3D(basePoint.x()+lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));
    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));
    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()));

    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()));
    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()-lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));
    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()+lengthWidthHeight.z()));
    vector3DTmp.append(QVector3D(basePoint.x()-lengthWidthHeight.x()/2,basePoint.y()+lengthWidthHeight.y()/2,basePoint.z()));

    QVector<myGraphicsItem*>itemVector;
    itemVector.append(addGraphics(polygonsItem,vector3DTmp,axisMovePos,vectorAxisRotate,color));

    foreach(myGraphicsItem* itemTmp,itemVector)
        itemGroupHash.insert(itemTmp,itemVector);
}

void MyOpenGLWidget::drawCylinder(const QVector3D &basePoint, const QVector3D &radiusAndHeight, const int number, const float numberSize, const QColor& color0, const QColor &color1, const QVector3D& axisMovePos, const QVector<axisRotateStruct>&vectorAxisRotate)
{
    QVector<myGraphicsItem *>itemVector;
    QVector<QVector3D> vector3f(2);
    vector3f[0]=basePoint;
    vector3f[1]=radiusAndHeight;
    itemVector.append(addGraphics(cylinderItem,vector3f,axisMovePos,vectorAxisRotate,color0));

    if(number==0){
        vector3f[0]=QVector3D(basePoint.x(),basePoint.y(),basePoint.z()+radiusAndHeight.z());
        vector3f[1]=QVector3D(0,radiusAndHeight.y(),0);
        itemVector.append(addGraphics(diskItem,vector3f,axisMovePos,vectorAxisRotate,color1));
    }
    else if(number>0){
        vector3f[0]=QVector3D(basePoint.x(),basePoint.y(),basePoint.z()+radiusAndHeight.z());
        vector3f[1]=QVector3D(0,radiusAndHeight.y(),0);
        itemVector.append(addGraphics(diskItem,vector3f,axisMovePos,vectorAxisRotate,color1));
        drawNumber(QVector3D(basePoint.x(),basePoint.y(),basePoint.z()+radiusAndHeight.z()),number,numberSize,axisMovePos,vectorAxisRotate);

//        vector3f[0]=QVector3D(basePoint.x()+radiusAndHeight.x(),basePoint.y(),basePoint.z());
//        vector3f[1]=QVector3D(basePoint.x()+radiusAndHeight.x(),basePoint.y(),basePoint.z()+radiusAndHeight.z());
//        itemVector.append(addGraphics(lineItem,vector3f,axisMovePos,vectorAxisRotate,ignoreColorVector[1]));
//        vector3f[0]=QVector3D(basePoint.x(),basePoint.y()+radiusAndHeight.x(),basePoint.z());
//        vector3f[1]=QVector3D(basePoint.x(),basePoint.y()+radiusAndHeight.x(),basePoint.z()+radiusAndHeight.z());
//        itemVector.append(addGraphics(lineItem,vector3f,axisMovePos,vectorAxisRotate,ignoreColorVector[1]));
//        vector3f[0]=QVector3D(basePoint.x()-radiusAndHeight.x(),basePoint.y(),basePoint.z());
//        vector3f[1]=QVector3D(basePoint.x()-radiusAndHeight.x(),basePoint.y(),basePoint.z()+radiusAndHeight.z());
//        itemVector.append(addGraphics(lineItem,vector3f,axisMovePos,vectorAxisRotate,ignoreColorVector[1]));
//        vector3f[0]=QVector3D(basePoint.x(),basePoint.y()-radiusAndHeight.x(),basePoint.z());
//        vector3f[1]=QVector3D(basePoint.x(),basePoint.y()-radiusAndHeight.x(),basePoint.z()+radiusAndHeight.z());
//        itemVector.append(addGraphics(lineItem,vector3f,axisMovePos,vectorAxisRotate,ignoreColorVector[1]));
    }

    foreach(myGraphicsItem* itemTmp,itemVector)
        itemGroupHash.insert(itemTmp,itemVector);
}

QVector<QVector3D> MyOpenGLWidget::LEDSide(const int sig,const float length,const float spaceBi,const float height,const QVector3D &vectorPoint3f)
{
    float space=length/spaceBi;
    QVector<QVector3D> vector;
    switch (sig) {
    case 0:{
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y(),vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y(),vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-space,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-space,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y(),vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-space,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y(),vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-space,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-space,vectorPoint3f.z()+height));
    }break;
    case 1:{
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y(),vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y(),vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y(),vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y(),vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
    }break;
    case 2:{
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-2*length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-2*length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length-space,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
    }break;
    case 3:{
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length+space,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length+space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length+space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length+space,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length+space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length+space,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length+space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length+space,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length+space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-2*length+space,vectorPoint3f.z()+height));
    }break;
    case 4:{
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-2*length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-2*length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-2*length,vectorPoint3f.z()+height));
    }break;
    case 5:{
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y(),vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y(),vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y(),vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y(),vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-length,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y(),vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+space,vectorPoint3f.y()-length,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length,vectorPoint3f.z()+height));
    }break;
    case 6:{
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length+0.5f*space,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length+0.5f*space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length+0.5f*space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length+0.5f*space,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length-0.5f*space,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length-0.5f*space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length-0.5f*space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length-0.5f*space,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length+0.5f*space,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length+0.5f*space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length-0.5f*space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length-0.5f*space,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length+0.5f*space,vectorPoint3f.z()));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length+0.5f*space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length-0.5f*space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length-0.5f*space,vectorPoint3f.z()));

        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length+0.5f*space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length+0.5f*space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x(),vectorPoint3f.y()-length-0.5f*space,vectorPoint3f.z()+height));
        vector.append(QVector3D(vectorPoint3f.x()+length,vectorPoint3f.y()-length-0.5f*space,vectorPoint3f.z()+height));
    }break;
    default:break;
    }
    return vector;
}

void MyOpenGLWidget::drawGraphics(const itemType type,const QVector<QVector3D> &vectorPoint3f,const QColor &color)
{
    switch (type) {
    case pointItem:{
        glBegin( GL_POINTS );
        glColor3d(color.redF(),color.greenF(),color.blueF());
        for(int i=0;i<vectorPoint3f.size();i++)
            glVertex3f(vectorPoint3f[i].x(),vectorPoint3f[i].y(),vectorPoint3f[i].z());
        glEnd();
    }break;
    case lineItem:{
        glBegin(GL_LINES);
        glColor3d(color.redF(),color.greenF(),color.blueF());
        for(int i=0;i<vectorPoint3f.size();i++)
            glVertex3f(vectorPoint3f[i].x(),vectorPoint3f[i].y(),vectorPoint3f[i].z());
        glEnd();
    }break;
    case polygonsItem:{
        glBegin(GL_QUADS);
        glColor3d(color.redF(),color.greenF(),color.blueF());
        for(int i=0;i<vectorPoint3f.size();i++)
            glVertex3f(vectorPoint3f[i].x(),vectorPoint3f[i].y(),vectorPoint3f[i].z());
        glEnd();
    }break;
    case sphereItem:{
        glTranslatef(vectorPoint3f[0].x(),vectorPoint3f[0].y(),vectorPoint3f[0].z());
        glColor3d(color.redF(),color.greenF(),color.blueF());
        gluSphere(gluNewQuadric(),static_cast<double>(vectorPoint3f[1].x()),static_cast<int>(vectorPoint3f[1].y()),static_cast<int>(vectorPoint3f[1].z())); //绘制球
        glTranslatef(-vectorPoint3f[0].x(),-vectorPoint3f[0].y(),-vectorPoint3f[0].z());
    }break;
    case cylinderItem:{
        glTranslatef(vectorPoint3f[0].x(),vectorPoint3f[0].y(),vectorPoint3f[0].z());
        glColor3d(color.redF(),color.greenF(),color.blueF());
        gluCylinder(gluNewQuadric(), static_cast<double>(vectorPoint3f[1].x()),static_cast<double>(vectorPoint3f[1].y()),static_cast<double>(vectorPoint3f[1].z()), 20, 2);
        glTranslatef(-vectorPoint3f[0].x(),-vectorPoint3f[0].y(),-vectorPoint3f[0].z());
    }break;
    case diskItem:{
        glTranslatef(vectorPoint3f[0].x(),vectorPoint3f[0].y(),vectorPoint3f[0].z());
        glColor3d(color.redF(),color.greenF(),color.blueF());
        gluDisk(gluNewQuadric(), static_cast<double>(vectorPoint3f[1].x()), static_cast<double>(vectorPoint3f[1].y()), 30, 1);
        glTranslatef(-vectorPoint3f[0].x(),-vectorPoint3f[0].y(),-vectorPoint3f[0].z());
    }break;
    }
}

QVector<QVector3D> MyOpenGLWidget::darwSingleNumber(const int value,const float length,const float spaceBi,const float height,const QVector3D vectorPoint3f)
{
    QVector<QVector3D> vector;
    switch(value){
    case 0:{
        vector.append(LEDSide(0,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(1,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(2,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(3,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(4,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(5,length,spaceBi,height,vectorPoint3f));
    }break;
    case 1:{
        vector.append(LEDSide(1,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(2,length,spaceBi,height,vectorPoint3f));
    }break;
    case 2:{
        vector.append(LEDSide(0,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(1,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(6,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(4,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(3,length,spaceBi,height,vectorPoint3f));
    }break;
    case 3:{
        vector.append(LEDSide(0,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(1,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(6,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(2,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(3,length,spaceBi,height,vectorPoint3f));
    }break;
    case 4:{
        vector.append(LEDSide(1,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(2,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(5,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(6,length,spaceBi,height,vectorPoint3f));
    }break;
    case 5:{
        vector.append(LEDSide(0,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(5,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(6,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(2,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(3,length,spaceBi,height,vectorPoint3f));
    }break;
    case 6:{
        vector.append(LEDSide(0,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(5,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(4,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(6,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(2,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(3,length,spaceBi,height,vectorPoint3f));
    }break;
    case 7:{
        vector.append(LEDSide(0,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(1,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(2,length,spaceBi,height,vectorPoint3f));
    }break;
    case 8:{
        vector.append(LEDSide(0,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(1,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(2,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(3,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(4,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(5,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(6,length,spaceBi,height,vectorPoint3f));
    }break;
    case 9:{
        vector.append(LEDSide(0,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(1,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(2,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(3,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(5,length,spaceBi,height,vectorPoint3f));
        vector.append(LEDSide(6,length,spaceBi,height,vectorPoint3f));
    }break;
    default:break;
    }
    return vector;
}

void MyOpenGLWidget::drawAxises()
{
    int lengthTmp=30;
    glBegin(GL_LINES);
    glColor3f(1,0,0);
    glVertex3f(-lengthTmp,0,0);
    glVertex3f(lengthTmp,0,0);

    glVertex3f(lengthTmp,0,0);
    glVertex3f(lengthTmp-1,-1,0);
    glVertex3f(lengthTmp,0,0);
    glVertex3f(lengthTmp-1,0,-1);
    glVertex3f(lengthTmp,0,0);
    glVertex3f(lengthTmp-1,1,0);
    glVertex3f(lengthTmp,0,0);
    glVertex3f(lengthTmp-1,0,1);

    glColor3f(0,1,0);
    glVertex3f(0,-lengthTmp,0);
    glVertex3f(0,lengthTmp,0);
    glVertex3f(0,lengthTmp,0);
    glVertex3f(1,lengthTmp-1,0);
    glVertex3f(0,lengthTmp,0);
    glVertex3f(-1,lengthTmp-1,0);
    glVertex3f(0,lengthTmp,0);
    glVertex3f(0,lengthTmp-1,1);
    glVertex3f(0,lengthTmp,0);
    glVertex3f(0,lengthTmp-1,-1);

    glColor3f(0,0,1);
    glVertex3f(0,0,-lengthTmp);
    glVertex3f(0,0,lengthTmp);
    glVertex3f(0,0,lengthTmp);
    glVertex3f(0,1,lengthTmp-1);
    glVertex3f(0,0,lengthTmp);
    glVertex3f(1,0,lengthTmp-1);
    glVertex3f(0,0,lengthTmp);
    glVertex3f(0,-1,lengthTmp-1);
    glVertex3f(0,0,lengthTmp);
    glVertex3f(-1,0,lengthTmp-1);
    glEnd();
}

void MyOpenGLWidget::receiveXAxisRotate(int axis,int degree)
{
    switch (axis) {
    case 0:currentState.xRot=degree;break;
    case 1:currentState.yRot=degree;break;
    case 2:currentState.zRot=degree;break;
    default:break;
    }
    update();
}

void MyOpenGLWidget::receiveViewPar(const QVector<int>& vector)
{
    currentState.xRot=vector[0];
    currentState.yRot=vector[1];
    currentState.zRot=vector[2];
    currentState.xTran=vector[3];
    currentState.yTran=vector[4];
    currentState.zTran=vector[5];
    currentState.angleXY=vector[6];
    currentState.angleYZ=vector[7];
    update();
}

void MyOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
        currentState.rDis--;
    else
        currentState.rDis++;
    update();
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    if(currentState.mousePressType!=Qt::NoButton){
        QPoint point=event->pos()-currentState.currentCursorPos;
        currentState.currentCursorPos=event->pos();
        switch(currentState.mousePressType){
        case Qt::LeftButton:{
            if(qFabs(point.x())>qFabs(point.y())){
                if(point.x()>0)
                    currentState.angleXY--;
                else
                    currentState.angleXY++;
                if(qFabs(currentState.angleXY)>=360)
                    currentState.angleXY=currentState.angleXY%360;
            }
            if(qFabs(point.x())<qFabs(point.y())){
                if(point.y()>0)
                    currentState.angleYZ++;
                else
                    currentState.angleYZ--;
                if(qFabs(currentState.angleYZ)>=360)
                    currentState.angleYZ=currentState.angleYZ%360;
            }
        }break;
        case Qt::RightButton:{
            if(qFabs(point.x())>qFabs(point.y())){
                if(point.x()>0)
                    currentState.yTran++;
                else
                    currentState.yTran--;
            }
            if(qFabs(point.x())<qFabs(point.y())){
                if(point.y()>0)
                    currentState.xTran++;
                else
                    currentState.xTran--;
            }
        }break;
        case Qt::MidButton:{
            if(point.y()>0)
                currentState.zTran--;
            else
                currentState.zTran++;
        }break;
        default:break;
        }
        update();
    }
}

void MyOpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    currentState.mousePressType=event->button();
    currentState.currentCursorPos=event->pos();
    if(currentState.mousePressType==Qt::LeftButton){
        GLint viewport[4];
        GLdouble projection_matrix[16];
        glGetIntegerv(GL_VIEWPORT, viewport);
        glGetDoublev(GL_PROJECTION_MATRIX, projection_matrix);
        GLint x = event->x();
        GLint y = viewport[3] - event->y() - 1;
        GLubyte pixel[3];
        glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);// 获取当前OpenGL场景中的像素颜色c
        QColor color(pixel[0],pixel[1],pixel[2]);
        if (!ignoreColorVector.contains(color) && itemsHash.contains(getColorValue(color))) {// 检测所选对象
            if(currentState.currentColorsVector.size()>0){
                for(int i=0;i<currentState.currentSelectItemsVector.size();i++)
                    currentState.currentSelectItemsVector[i]->m_color=currentState.currentColorsVector[i];
            }
            currentState.currentColorsVector.clear();
            currentState.currentSelectItemsVector=itemGroupHash.value(itemsHash.value(getColorValue(color)));
            for(int i=0;i<currentState.currentSelectItemsVector.size();i++){
                currentState.currentColorsVector.append(currentState.currentSelectItemsVector.at(i)->m_color);
                currentState.currentSelectItemsVector[i]->m_color=ignoreColorVector[0];
            }
            update();
        }
        else{
            if(currentState.currentColorsVector.size()>0){
                for(int i=0;i<currentState.currentSelectItemsVector.size();i++)
                    currentState.currentSelectItemsVector[i]->m_color=currentState.currentColorsVector[i];
                currentState.currentColorsVector.clear();
                update();
            }
        }
    }
}

void MyOpenGLWidget::mouseReleaseEvent(QMouseEvent*)
{
    currentState.mousePressType=Qt::MouseButton::NoButton;
}

