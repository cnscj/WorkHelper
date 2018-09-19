#ifndef SIMAGEWIDGET_H
#define SIMAGEWIDGET_H

#include <QLabel>
class SImageWidget: public QLabel
{
    Q_OBJECT
public:
    explicit SImageWidget(QWidget *parent=nullptr);
    ~SImageWidget();
public:
    const QImage *image()const;
    int contentWidth()const;
    int contentHeight()const;
    QSize contentSize()const;
    QRect contentRect()const;
    QPoint contentPixelPos(int x,int y)const;
    QPoint contentPixelPos(const QPoint &p)const;
    QRgb  contentPixel(int x,int y)const;
    QRgb  contentPixel(const QPoint &p)const;
public:
   void showBackgroundColor(const QColor &color);
   void showImage(const QString &filePath);
public:
   void setScale(float scale);
   float getScale()const;

   void setBackground(const QColor &color);
   const QColor &getBackground()const;
protected:
   void drawPixmap(const QImage *img);
   void drawPixmap(QImage *img,const QString &filePath);
protected:
   virtual void paintEvent(QPaintEvent *e);
   virtual void mousePressEvent(QMouseEvent *event);        //单击
   virtual void wheelEvent(QWheelEvent * event);           //滚轮事件
private:
   QImage m_curImage;
   QColor m_curBgColor;
   float m_curScale;


};

#endif // SIMAGEWIDGET_H
