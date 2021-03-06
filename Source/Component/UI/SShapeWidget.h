#ifndef SSHAPEWIDGET_H
#define SSHAPEWIDGET_H

#include <QWidget>
class SShapeWidget : public QWidget
{
    Q_OBJECT
public:
    enum class Shape
    {
        Elliptic,
        Rect,
        Image,
    };
public:
    explicit SShapeWidget(QWidget *parent=nullptr);
    ~SShapeWidget();
public:
    void setPosition(const QPoint &p);
    QPoint getPosition()const;

    void setSize(const QSize &size);
    QSize getSize()const;

    void setColor(const QColor &color);
    QColor getColor()const;

    void setShape(const Shape shaper,void *data = nullptr);
    Shape getShape() const;
    const void *getShapeData()const;
    void setShapeData(void *data);

    void setDragEnabled(bool isCanDrag);
    bool getDragEnabled()const;

protected:
    void paint(QPainter &);
protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
private:
    QSize       m_size;
    Shape       m_shaper;
    void        *m_pShaperData;     //可能为QColor,可能为QImage

    bool        m_bIsCanDrag;       //是否支持拖拽
};

#endif // SSHAPEWIDGET_H
