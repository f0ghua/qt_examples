#include "chexfile.h"
#include <fstream>
#include <QList>
#include <QString>
#include <stdexcept>
#include <QTextStream>
#include <QFile>

unsigned int hexToUInt(const QString &str)
{
    unsigned int retVal = 0;
    for(int i=0; i<str.length(); i++)
    {
        retVal = retVal << 4;
        QString temp = str[i];
        retVal += temp.toUInt(0, 16);
    }

    return retVal;
}

CHexFile::CHexFile()
{
}

void CHexFile::readFile(const QString &strPath)
{
    m_vLines.clear();
    QFile file(strPath);
    if(!file.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("CHexFile::ReadFile: Failed to open file " + strPath.toStdString());
    }
    QTextStream reader(&file);

    while(!reader.atEnd())
    {
    	QString line = reader.readLine().simplified();
		if (!line.isEmpty()) {
        	CHexLine hexLine(line);
			if (hexLine.getRecordType() == CHexLine::Data)
        		m_vLines.push_back(hexLine);
		}
    }

    file.close();
}

void CHexFile::writeFile(const QString &strFile)
{
    QStringList lines;
    this->fillStringList(lines);
    QFile file(strFile);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        throw std::runtime_error("CHexFile::writeFile: Failed to open file " + strFile.toStdString());
    }

    QTextStream writer(&file);
    for(auto iter = lines.begin(); iter != lines.end(); iter++)
    {
        writer << *iter << endl;
    }

    writer.flush();

    file.close();
}

void CHexFile::setByte(unsigned int uiLine, unsigned int uiColumn, unsigned char ucByte)
{
    if(uiLine >= m_vLines.size())
        throw std::runtime_error("CHexFile::setByte: iLine out of range.");

    CHexLine &line = m_vLines[uiLine];
    line.setByte(uiColumn, ucByte);


}

void CHexFile::fillStringList(QStringList &list)
{
    for(unsigned int i = 0; i<m_vLines.size(); i++)
    {
        list.push_back(m_vLines[i].getCompleteString());
    }
}

unsigned int CHexFile::getLineCount()
{
    return m_vLines.size();
}

CHexLine CHexFile::getLine(unsigned int i)
{
    return m_vLines[i];
}

int CHexFile::getByte(unsigned int line, unsigned int byte)
{
    if(line >= m_vLines.size())
        return -1;

    return m_vLines[line].getByte(byte);
}

QString CHexLine::getHexNumeric(unsigned int number)
{
    QString retVal = QString::number(number, 16);
    if(retVal.length() % 2 != 0)
        retVal = "0" + retVal;

    return retVal.toUpper();
}

void CHexLine::updateChecksum()
{
    unsigned char ucChecksum = this->getByteCount();
    unsigned short addr = this->getAddress();
    ucChecksum += (addr & 0xFF00) >> 8;
    ucChecksum += addr & 0x00FF;
    ucChecksum += static_cast<unsigned char>(this->getRecordType());
    for(auto d=m_vData.begin(); d != m_vData.end(); d++)
    {
        ucChecksum += *d;
    }

    ucChecksum = ~ucChecksum;
    ucChecksum += 0x01;
    this->setChecksum(ucChecksum);
}

CHexLine::CHexLine()
{
}

CHexLine::CHexLine(const QString &line)
{
    fillFromLine(line);
}

void CHexLine::setByte(unsigned int uiColumn, unsigned char ucByte)
{
    if(uiColumn >= m_vData.size())
        throw std::runtime_error("CHexLine::setByte: uiColumn out of bounds");

    m_vData[uiColumn] = ucByte;

    updateChecksum();
}

void CHexLine::fillFromLine(const QString &line)
{
    if(line[0] == ';')
        return;

    if(line[0] != ':')
        throw std::runtime_error("CHexLine::fillFromLine, line does not start with ':'");

    QString byteCount = QString(line[1]) + QString(line[2]);
    QString address = QString(line[3]) + QString(line[4]) + QString(line[5]) + QString(line[6]);
    QString recordType = QString(line[7]) + QString(line[8]);

    this->setByteCount(hexToUInt(byteCount));
    this->setAddress(hexToUInt(address));
    this->setRecordType(static_cast<RecordTypes>(hexToUInt(recordType)));

    m_vData.clear();
    m_vData.resize(this->getByteCount());
    for(unsigned int i=0, count=0; count<this->getByteCount(); i+=2, count++)
    {
        QString temp = QString(line[i+9]) + QString(line[i+10]);
        this->setByte(i/2, hexToUInt(temp));
    }

    QString checksum = QString(line[line.size()-2]) + QString(line[line.size()-1]);
    this->setChecksum(hexToUInt(checksum));
}

QString CHexLine::getCompleteString()
{
    QString retVal = ":";

    retVal += getHexNumeric(this->getByteCount());
    retVal += this->getAddressString();

    retVal += this->getRecordTypeString();
    retVal += this->getDataString();

    retVal += this->getChecksumString();

    return retVal;
}

QString CHexLine::getAddressString()
{
    QString address = getHexNumeric(this->getAddress());
    if(address.length() < 4)
    {
        while(address.length() < 4)
            address = "0" + address;
    }

    return address;
}

QString CHexLine::getRecordTypeString()
{
    return getHexNumeric(this->getRecordType());
}

QString CHexLine::getDataString()
{
    QString retVal = "";
    for(std::size_t i=0; i<m_vData.size(); i++)
    {
        retVal += getHexNumeric(m_vData[i]);
    }

    return retVal;
}

QString CHexLine::getChecksumString()
{
    return getHexNumeric(this->getChecksum());
}
