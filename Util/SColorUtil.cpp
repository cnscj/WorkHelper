#include "SColorUtil.h"

QString SColorUtil::makeColorString(const QColor &color, const QString type)
{
    if(type.toUpper() == "RGBA")
    {
        return QString("%1(%2, %3, %4, %5)")
                .arg(type)
                .arg(color.red())
                .arg(color.green())
                .arg(color.blue())
                .arg(color.alpha());
    }
    if(type.toUpper() == "RGB")
    {
        return QString("%1(%2, %3, %4)")
                .arg(type)
                .arg(color.red())
                .arg(color.green())
                .arg(color.blue());
    }
    if(type.toUpper() == "HEX")
    {
        QString ret = QString("#%1%2%3%4")
                     .arg(color.alpha() != 255 ? QString("%1").arg(color.alpha(),2, 16, QLatin1Char('0')) : QString())
                     .arg(color.red(),2, 16, QLatin1Char('0'))
                     .arg(color.green(),2, 16, QLatin1Char('0'))
                     .arg(color.blue(),2, 16, QLatin1Char('0'));

        if (type == "HEX")
        {
            ret = ret.toUpper();
        }
        return ret;
    }

    return color.name();
}
