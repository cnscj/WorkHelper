#ifndef SFILENAMEFACTOR_H
#define SFILENAMEFACTOR_H

#include <QWidget>

namespace Ui {
class SFileNameFactor;
}

class SFileNameFactor : public QWidget
{
    Q_OBJECT

public:
    explicit SFileNameFactor(QWidget *parent = 0);
    ~SFileNameFactor();

protected slots:
    void showToText();

private:
    Ui::SFileNameFactor *ui;
};

#endif // SFILENAMEFACTOR_H
