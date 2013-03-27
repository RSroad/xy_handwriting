#include "painter.h"

Painter::Painter(QWidget *parent)
    :QMainWindow(parent)
{
    QFont font("Sans Serif", 12);
    setFont(font);

    setWindowTitle(tr("xy手写"));

    widget = new DrawWidget;
    setCentralWidget(widget);

    createToolBar();

    //setMinimumSize(600, 400);

    slotStyle();
    widget->setWidth(widthSpinBox->value());
    widget->setColor(Qt::black);
}

void Painter::createToolBar()
{
    QToolBar *toolBar = addToolBar("Tool");
    QLabel *label_1 = new QLabel(tr("style:"));

    styleComboBox = new QComboBox;  //复选框
    styleComboBox->addItem("SolidLine", Qt::SolidLine);
    styleComboBox->addItem("DashLine", Qt::DashLine);
    styleComboBox->addItem("DotLine", Qt::DotLine);
    styleComboBox->addItem("DashDotLine", Qt::DashDotLine);
    styleComboBox->addItem("DashDotDotLine", Qt::DashDotDotLine);

    toolBar->addWidget(label_1);  //添加到bar上
    toolBar->addWidget(styleComboBox);
    toolBar->addSeparator();  //添加分割线

    connect(styleComboBox, SIGNAL(activated(int)), this, SLOT(slotStyle()));  //将选项和设置风格联系起来

    QLabel *label_2 = new QLabel(tr("width")); //画笔宽度 --
    widthSpinBox = new QSpinBox;
    widthSpinBox->setRange(0, 10);  //范围
    toolBar->addWidget(label_2);
    toolBar->addWidget(widthSpinBox);
    toolBar->addSeparator();

    connect(widthSpinBox, SIGNAL(valueChanged(int)), widget, SLOT(setWidth(int)));  //将设置的值和画笔宽度联系起来

//    colorBtn = new QToolButton;     //颜色
//    QPixmap pixmap(20, 20);
//    pixmap.fill(Qt::black);
//    colorBtn->setIcon(QIcon(pixmap));
//    toolBar->addWidget(colorBtn);
//    toolBar->addSeparator();

//    connect(colorBtn, SIGNAL(clicked()), this, SLOT(slotColor()));

    QToolButton *clearBtn = new QToolButton;
    clearBtn->setText(tr("clear"));
    toolBar->addWidget(clearBtn);
    toolBar->addSeparator();

    connect(clearBtn, SIGNAL(clicked()), widget, SLOT(clear()));

    QToolButton *prevBtn = new QToolButton;
    prevBtn->setText(tr("prev"));
    toolBar->addWidget(prevBtn);
    toolBar->addSeparator();

    connect(prevBtn, SIGNAL(clicked()), widget, SLOT(prev()));

    QToolButton *nextBtn = new QToolButton;
    nextBtn->setText(tr("next"));
    toolBar->addWidget(nextBtn);

    connect(nextBtn, SIGNAL(clicked()), widget, SLOT(next()));
}

void Painter::slotStyle()
{
    widget->setStyle(styleComboBox->itemData(
            styleComboBox->currentIndex(), Qt::UserRole).toInt());
}

void Painter::slotColor()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid()) {
        widget->setColor(color);
        QPixmap p(20, 20);
        p.fill(color);
        colorBtn->setIcon(QIcon(p));
    }
}
