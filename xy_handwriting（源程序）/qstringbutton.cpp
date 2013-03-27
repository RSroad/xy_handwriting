#include "qstringbutton.h"

QStringButton::QStringButton(QWidget *parent) :
    QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(emit_string_signal()));
}
QStringButton::QStringButton(const QString button_label, QWidget *parent) :
        QPushButton(button_label, parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(emit_string_signal()));
}

void QStringButton::emit_string_signal()
{
    emit click_with_string(this->text());
}
