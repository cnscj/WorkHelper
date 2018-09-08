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
    const QImage *getImage()const;
    const QLabel *getLabel()const;

    void showImage(const QString &filePath);
    int imageWidth()const;
    int imageHeight()const;

    bool isImageNull()const;
    QRgb getPixel(int i,int j) const;
protected:
    //重写滚轮事件
    virtual void wheelEvent(QWheelEvent * event);
private:
    QGridLayout m_gridLayout;
    QLabel m_outLabel;
    QImage m_curImage;
    float m_curScale;

};

#endif // SIMAGEVIEW_H
