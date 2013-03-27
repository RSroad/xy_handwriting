#include <QtGui>
#include <QString>
#include <QDebug>

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QtCore>

#include <QLineEdit>

#include "drawwidget.h"
#include <iostream>

#include <QMessageBox>

DrawWidget::DrawWidget()  //画板
{
    setAutoFillBackground(true);  //设置背景色
    setMinimumSize(600, 400); //设置大小

    QPalette palette = this->palette();  //设置调色板
    palette.setColor(QPalette::Window, Qt::white);
    setPalette(palette);

    pix = new QPixmap(400, 400);  //画布大小
    pix->fill(Qt::white);  //需要将颜色改为白色

    for (int i = 0; i < 8; i++) {
        mBtn[i] = new QStringButton(this);
        mBtn[i]->setText("xiyou");
        connect(mBtn[i], SIGNAL(click_with_string(QString)) , this, SLOT(pressBtn(QString)));
    }
    mBtn[0]->setGeometry(400, 0, 100, 100);
    mBtn[1]->setGeometry(500, 0, 100, 100);
    mBtn[2]->setGeometry(400, 100, 100, 100);
    mBtn[3]->setGeometry(500, 100, 100, 100);
    mBtn[4]->setGeometry(400, 200, 100, 100);
    mBtn[5]->setGeometry(500, 200, 100, 100);
    mBtn[6]->setGeometry(400, 300, 100, 100);
    mBtn[7]->setGeometry(500, 300, 100, 100);
}

DrawWidget::~DrawWidget()
{
    for (int i = 0; i < 8; i++)
        delete mBtn[i];
}

void DrawWidget::setStyle(int s)
{
    style = s;
}

void DrawWidget::setWidth(int w)
{
    weigth = w;
}

void DrawWidget::setColor(QColor c)
{
    color = c;
}

void DrawWidget::mousePressEvent(QMouseEvent *e)  //鼠标按下事件
{
    startPos = e->pos(); //鼠标的开始
    myIndex = 0;
    memset(arr, 0, sizeof(arr));
}

void DrawWidget::mouseReleaseEvent(QMouseEvent *)  //鼠标释放事件
{
    Judge(arr, myIndex);  //调用处理函数
    //将找到的字显示在右边? 先打印输出
    //QDebug("%s", chinese_result[0]);
    //将char *类型的chinese_result中的汉字转换为QString类型的，然后在按钮上显示
    //使用：QTextCodec *codec = QTextCodec::codecForName("GBK");
    //     QString strText = codec->toUnicode(string);
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString strText;
    for (int i = 0; i < 8; i++) {
        strText = codec->toUnicode(chinese_result[i]);
        //qDebug() << strText;
        mBtn[i]->setText(strText);
        // connect(colorBtn, SIGNAL(clicked()), this, SLOT(slotColor()));
    }

    myIndex = 0;  //复位
    memset(arr, 0, sizeof(arr));
}

void DrawWidget::mouseMoveEvent(QMouseEvent *e) //鼠标移动事件
{
    QPainter painter(pix);  //
    QPen pen;  //画笔

    pen.setStyle((Qt::PenStyle)style);  //设置画笔
    pen.setWidth(weigth);
    pen.setColor(color);

    painter.setPen(pen);

    painter.drawLine(startPos, e->pos());
    startPos = e->pos();
//    qDebug("(%d, %d)", e->pos().x(), e->pos().y());
    arr[myIndex].x = e->pos().x();
    arr[myIndex++].y = e->pos().y();

    update();
}

void DrawWidget::paintEvent(QPaintEvent *)  //
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0, 0), *pix);  //每次的移动都以当前位置为坐标的开始
}

void DrawWidget::resizeEvent(QResizeEvent *event)
{
    if (height() > pix->height() || width() > pix->width()) {
        QPixmap *newPix = new QPixmap(size());
        newPix->fill(Qt::white);
        QPainter p(newPix);
        p.drawPixmap(QPoint(0, 0), *pix);
        pix = newPix;
    }
    QWidget::resizeEvent(event);
}

void DrawWidget::clear()
{
    QPixmap *clearPix = new QPixmap(size());
    clearPix->fill(Qt::white);
    pix = clearPix;
    clearBtnText();
    m_FLAG = 1;
    update();
}

void DrawWidget::next()  //接口 -- outside
{
    nextBtnText();
    update();
}

void DrawWidget::prev()
{
    prevBtnText();
    update();
}

void DrawWidget::clearBtnText()
{
    for (int i = 0; i < 8; i++) {
        mBtn[i]->setText("xiyou");
    }
}

void DrawWidget::pressBtn(QString rev){
    qDebug() << rev;
    clear();
}

void DrawWidget::nextBtnText()
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString strText;
    for (int i = 0, j = 8; i < 8; i++, j++) {
        strText = codec->toUnicode(chinese_result[j]);
        //qDebug() << strText;
        mBtn[i]->setText(strText);
        //connect(colorBtn, SIGNAL(clicked()), this, SLOT(slotColor()));
    }
}

void DrawWidget::prevBtnText()
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString strText;
    for (int i = 0, j = 0; i < 8; i++, j++) {
        strText = codec->toUnicode(chinese_result[j]);
        //qDebug() << strText;
        mBtn[i]->setText(strText);
    }
}
