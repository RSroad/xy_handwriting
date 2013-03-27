#ifndef QSTRINGBUTTON_H
#define QSTRINGBUTTON_H

#include <QPushButton>

class QStringButton : public QPushButton
{
    Q_OBJECT
public:
    explicit QStringButton(QWidget *parent = 0);
    QStringButton(const QString button_label,QWidget *parent=0);

signals:
    void click_with_string(QString);

public slots:
    void emit_string_signal();

};

#endif // QSTRINGBUTTON_H
