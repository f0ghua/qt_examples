#ifndef IHEXLINE_H
#define IHEXLINE_H

#include <QString>
#include <QList>
#include <cstdint>

class IHexLine
{    
public:
    enum LineType
    {
        InvalidDataLine = -1,
        DataLine,
        Comment,
        Unknown
    };

    IHexLine();
    IHexLine(const QString &line);

    void parseLine(const QString &line);

    QString toString();
    int byteCount();
    std::uint8_t checksum();

    LineType lineType() const;
    void setLineType(const LineType &lineType);

    int recordType() const;
    void setRecordType(int recordType);

    std::uint32_t address() const;
    void setAddress(std::uint32_t address);

private:
    LineType m_lineType;
    int m_recordType;
    std::uint32_t m_address;
    QList<std::uint8_t> m_data;
    QString m_originalLine;

    QString toHex(std::uint32_t num, std::uint32_t len);
};

#endif // IHEXLINE_H
