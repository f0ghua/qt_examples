#include "ihexline.h"
#include <algorithm>

IHexLine::IHexLine():
    m_lineType(DataLine),
    m_recordType(0),
    m_address(0),
    m_originalLine(":00000001FF")
{

}

IHexLine::IHexLine(const QString &line)
{
    parseLine(line);
}

void IHexLine::parseLine(const QString &line)
{
    m_data.clear();
    m_originalLine = line;
    if(line.length() == 0)
    {
        return;
    }
    else if(line[0] == ';')
    {
        m_lineType = Comment;
        return;
    }
    else if(line[0] == ':')
    {
        bool ok = false;
        m_lineType = InvalidDataLine;
        int dataLength = line.mid(1, 2).toInt(&ok, 16);
        if(!ok)
        {
            return;
        }

        m_address = line.mid(3, 4).toUInt(&ok, 16);
        if(!ok)
        {
            return;
        }

        m_recordType = line.mid(7, 2).toUInt(&ok, 16);

        QString dataLine = line.mid(9);

        for(int i=0; i<dataLine.size()-2; i+=2)
        {
            unsigned char temp = line.mid(i, 2).toInt(&ok, 16);
            if(!ok)
            {
                return;
            }
            m_data.push_back(temp);
        }

        if(dataLength != m_data.length())
        {
            return;
        }

        m_lineType = DataLine;
    }
    else
    {
        m_lineType = Unknown;
    }
}

QString IHexLine::toString()
{
    if(lineType() != DataLine)
    {
        return m_originalLine;
    }

    QString retVal = ":";

    retVal += toHex(m_data.length(), 2);
    retVal += toHex(m_address, 4);
    retVal += toHex(m_recordType, 2);
    for(int i=0; i<m_data.length(); i++)
    {
        retVal += toHex(m_data[i], 2);
    }

    retVal += toHex(checksum(), 2);

    return retVal;
}

int IHexLine::byteCount()
{
    return m_data.length();
}

std::uint8_t IHexLine::checksum()
{
    std::uint8_t sum = byteCount();
    sum += (m_address >> 8);
    sum += (m_address & 0x00FF);
    sum += m_recordType;
    std::for_each(m_data.begin(), m_data.end(), [&sum](std::uint8_t d) { sum += d; });
    return sum;
}
IHexLine::LineType IHexLine::lineType() const
{
    return m_lineType;
}

void IHexLine::setLineType(const LineType &lineType)
{
    m_lineType = lineType;
}
int IHexLine::recordType() const
{
    return m_recordType;
}

void IHexLine::setRecordType(int recordType)
{
    m_recordType = recordType;
}
std::uint32_t IHexLine::address() const
{
    return m_address;
}

void IHexLine::setAddress(std::uint32_t address)
{
    m_address = address;
}

QString IHexLine::toHex(std::uint32_t num, std::uint32_t len)
{
    QString retVal = QString::number(num, 16);
    while(retVal.length() < len)
    {
        retVal = "0" + retVal;
    }

    return retVal;
}




