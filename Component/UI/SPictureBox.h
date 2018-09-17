#ifndef SPictureBox_H
#define SPictureBox_H

#include <QWidget>
#include <QImage>
#include <QPixmap>


class SPictureBox : public QWidget
{
    Q_OBJECT
public:
    enum PB_MODE {FIXED_SIZE, FIX_SIZE_CENTRED, AUTO_ZOOM, AUTO_SIZE};
    explicit SPictureBox(QWidget *parent = 0);
public:
    void setMode(PB_MODE mode);
    ~SPictureBox();
private:
    QPixmap m_pixmap;
    double m_scale;
    PB_MODE m_mode;
    QBrush m_brush;
protected:
    void paintEvent(QPaintEvent * event);
signals:

public slots:
    bool setImage(QImage &image, double scale = 1.0);
    void setBackground(QBrush brush);
};

#endif // SPictureBox_H
