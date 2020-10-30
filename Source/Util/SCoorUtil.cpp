#include "SCoorUtil.h"

QPoint SCoorUtil::getBoxInBoxCenterPos(const QRect &a,const QRect &b)
{
    return QPoint((a.width()-b.width())/2,(a.height()-b.height())/2);
}
