#ifndef SIMAGEVIEW_H
#define SIMAGEVIEW_H

#include <QLabel>
#include <QGridLayout>
class SImageView : public QWidget
{
    Q_OBJECT
public:
   explicit SImageView(QWidget *parent=nullptr);
   ~SImageView();
public:
    const QImage *image()const;
    const QLabel *label()const;

    void showImage(const QString &filePath);
    void setBackgroundColor(QColor color);

protected:
    virtual void mousePressEvent(QMouseEvent *event);        //单击
    virtual void wheelEvent(QWheelEvent * event);           //滚轮事件
private:
    QGridLayout m_gridLayout;
    QLabel m_outLabel;
    QImage m_curImage;
    float m_curScale;

};

#endif // SIMAGEVIEW_H
