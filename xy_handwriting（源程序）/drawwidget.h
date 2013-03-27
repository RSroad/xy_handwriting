#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include "external_call.h"
#include "qstringbutton.h"

class QPoint;
class QPixmap;
class QColor;

class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    DrawWidget();
    ~DrawWidget();

    void mousePressEvent(QMouseEvent *);  //鼠标移动事件函数
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void paintEvent(QPaintEvent *);  //重写绘画事件
    void resizeEvent(QResizeEvent *);  //改变大小

    void clearBtnText();  //清除(还原)按钮上的字符
    void nextBtnText();
    void prevBtnText();

signals:
    void clickWithString(QString);

public slots:
    void setStyle(int);  //改变画笔风格
    void setWidth(int);  //改变画笔的粗细
    void setColor(QColor);  //改变颜色
    void clear();
    void next();
    void prev();
    void pressBtn(QString);

private:
    QPixmap *pix;  //用来填充画笔QPaint
    QPoint startPos;  //开始位置
    QPoint endPos;  //结束位置

    int style;  //对画笔风格的设置
    int weigth; //画笔大小
    QColor color;

    int myIndex;  //点的信息
    struct my_arr arr[MAXSIZE];

    QStringButton *mBtn[8];
    QLabel * el;
};

#endif // DRAWWIDGET_H
