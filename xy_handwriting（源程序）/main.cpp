#include <QtGui/QApplication>
#include <QtCore>

#include "mainwindow.h"
#include "painter.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTranslator translator;

    translator.load("painter_zh");
    app.installTranslator(&translator);

    Painter p;
    p.show();

    return app.exec();
}
