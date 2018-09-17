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
public:
   void showBackgroundColor(const QColor &color);
   void showImage(const QString &filePath);
public:
   void setScale(float scale);
   float getScale();

   void setBackground(const QColor &color);
   const QColor &getBackground();
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
