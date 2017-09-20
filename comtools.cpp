#include "comtools.h"

#include <QCoreApplication>

QString QSPTools::GetHexColor(const QColor color)
{
    return QString("%1%2%3").arg(color.red(), 2, 16, QLatin1Char( '0' )).arg(color.green(), 2, 16, QLatin1Char( '0' )).arg(color.blue(), 2, 16, QLatin1Char( '0' ));
}

QString QSPTools::HtmlizeWhitespaces(const QString& str)
{
    QString::const_iterator i;
    QChar ch, quote;
    QString out;
    size_t j, linepos = 0;
    bool isLastSpace = true;
    for (i = str.begin(); i != str.end(); ++i)
    {
        ch = *i;
        if(ch == QChar('<'))
        {
            quote = 0;
            while (i != str.end())
            {
                ch = *i;
                if (quote.unicode())
                {
                    if (ch == QChar('\\'))
                    {
                        if (++i == str.end()) break;
                        ch = *i;
                        if (ch == quote)
                        {
                            if(ch == QChar('"'))
                            {
                                out.append( QString("&quot;") );
                            }
                            else if(ch == QChar('\''))
                            {
                                out.append( QString("&apos;") );
                            }
                            ++i;
                            continue;
                        }
                        out.append( QChar('\\') );
                    }
                    if(ch == QChar('&'))
                    {
                        out.append( QString("&amp;") );
                    }
                    else if(ch == QChar('<'))
                    {
                        out.append( QString("&lt;") );
                    }
                    else if (ch == QChar('>'))
                    {
                        out.append( QString("&gt;") );
                    }
                    else
                    {
                        if (ch == quote)
                            quote = 0;
                        out.append(ch);
                    }
                }
                else
                {
                    out.append(ch);
                    if (ch == QChar('>'))
                        break;
                    else if (ch == QChar('"') || ch == QChar('\''))
                        quote = ch;
                }
                ++i;
            }
            if (i == str.end()) return out;
            isLastSpace = true;
        }
        else if(ch == QChar(' '))
        {
            if (isLastSpace)
                out.append( QString("&nbsp;") );
            else
                out.append( QChar(' ') );
            isLastSpace = !isLastSpace;
            ++linepos;
        }
        else if(ch == QChar('\r'))
        {

        }
        else if(ch == QChar('\n'))
        {
            out.append( QString("<br />") );
            isLastSpace = true;
            linepos = 0;
        }
        else if(ch == QChar('\t'))
        {
            for (j = 4 - linepos % 4; j > 0; --j)
            {
                if (isLastSpace)
                    out.append( QString("&nbsp;") );
                else
                    out.append( QChar(' ') );
                isLastSpace = !isLastSpace;
            }
            linepos += 4 - linepos % 4;
        }
        else
        {
            out.append(ch);
            isLastSpace = false;
            ++linepos;
        }
    }
    return out;
}

QString QSPTools::ProceedAsPlain(const QString& str)
{
    QString::const_iterator i;
    QChar ch;
    QString out;
    for (i = str.begin(); i != str.end(); ++i)
    {
        ch = *i;
        if( ch == QChar('<'))
        {
            out.append( QString("&lt;") );
        }
        else if(ch == QChar('>'))
        {
            out.append( QString("&gt;") );
        }
        else if(ch == QChar('&'))
        {
            out.append( QString("&amp;") );
        }
        else
        {
            out.append(ch);
        }
    }
    return out;
}

QString QSPTools::GetAppPath()
{
    return QCoreApplication::applicationDirPath();
}

QString QSPTools::qspStrToQt(const QSP_CHAR *str)
{
    //return QString::fromWCharArray(str.Str, (int)(str.End - str.Str));
    if(str == 0)
        return QString("");
    else
        return QString::fromUtf16(str);
}
