#include "Component/SDrawTool.h"

SDrawTool::SDrawTool():
    m_selectedMark(-1)
{

}

SDrawTool::~SDrawTool()
{
    clearPoints();
}

void SDrawTool::addPoint(const QPoint &p)
{
    SMarkPoint *pMark = new SMarkPoint(p);
    m_Points.push_back(pMark);
}

void SDrawTool::deletePoint(int index)
{
    if(index < 0 || index >= m_Points.length())
    {
        return;
    }
    m_Points.erase(m_Points.begin() + index);
}

SMarkPoint *SDrawTool::getPoint(int index)
{
    if(index < 0 || index >= m_Points.length())
    {
        return nullptr;
    }
    return m_Points.at(index);
}

int SDrawTool::searchPoint(const QPoint &p,int r)
{
    //判断选中了哪个点
    auto rt = QRect(p.x() - r, p.y() - r,  2*r,  2*r);
    for(int i = 0; i<m_Points.length(); i++)
    {
        if(rt.contains(m_Points.at(i)->getMarkPos()))
        {
            return i;
        }
    }
    return -1;
}

void SDrawTool::clearPoints()
{
    for (auto it = m_Points.begin(); it != m_Points.end() ; it++)
    {
        delete *it;
    }
    m_Points.clear();
}

const QVector<SMarkPoint *> *SDrawTool::getPoints()
{
    return &m_Points;
}

void SDrawTool::selectPoint(int index)
{
    m_selectedMark = index;
    m_Points.at(index)->setMarkColor(Qt::red);
}

bool SDrawTool::isSelectedPoint()
{
    return (m_selectedMark != -1);
}

void SDrawTool::cancelPoint()
{
    if(isSelectedPoint())
    {
        m_Points.at(m_selectedMark)->setMarkColor(Qt::black);
        m_selectedMark = -1;
    }
}

int SDrawTool::getSelectedPoint()
{
    return m_selectedMark;
}

void SDrawTool::drawBezier(QPainter *painter)
{
    for(int i = 0; i<m_Points.length(); i++)
    {
        if( i && ((i+1) % 2 == 0) )
        {
            drawLine(painter,m_Points.at(i - 1),m_Points.at(i));
        }
        if(i && ((i+1) % 4 == 0) )
        {
            drawBezier3(painter,m_Points.at(i - 3),m_Points.at(i - 2),m_Points.at(i - 1),m_Points.at(i));
        }
        drawPoint(painter,m_Points.at(i));
    }

}

void SDrawTool::drawPoints(QPainter *painter)
{

    for(int i = 0; i<m_Points.length(); i++)
    {
        drawPoint(painter,m_Points.at(i));
    }
}

void SDrawTool::drawPolygon(QPainter *painter)
{
    int n = m_Points.length();
    for(int i = 0; i < n - 1; i++)
    {
        drawLine(painter,m_Points.at(i),m_Points.at(i+1));
    }
    if (n>0) drawLine(painter,m_Points.at(n-1),m_Points.at(0));
}

void SDrawTool::drawPoint(QPainter *painter, SMarkPoint *p)
{
    auto pos = p->getMarkPos();
    auto size = p->getMarkSize();
    auto color = p->getMarkColor();
    auto old = painter->brush();

    painter->setBrush(QBrush(color));
    painter->drawEllipse(pos,size,size);

    painter->setBrush(old);
}

void SDrawTool::drawLine(QPainter *painter, SMarkPoint *a,  SMarkPoint *b)
{
    auto old = painter->pen();

    painter->setPen(QPen(Qt::lightGray));
    painter->drawLine(a->getMarkPos(),b->getMarkPos());

    painter->setPen(old);
}

void SDrawTool::drawBezier3(QPainter *painter, SMarkPoint *start, SMarkPoint *pos1, SMarkPoint *pos2, SMarkPoint *end)
{
    QPainterPath path;
    path.moveTo(start->getMarkPos());
    path.cubicTo(pos1->getMarkPos(), pos2->getMarkPos(),end->getMarkPos());
    painter->drawPath(path);
}
