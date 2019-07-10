#ifndef SMAINWIDGET_H
#define SMAINWIDGET_H

#include <QWidget>
#include <QStack>

namespace Ui {
class SMainWidget;
}

class SMainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SMainWidget(QWidget *parent = 0);
    ~SMainWidget();
private slots:
    void enterWidget(int index);
private:
    Ui::SMainWidget *ui;
    QStack<QWidget *> m_moduleStack;
};

#endif // SMAINWIDGET_H
