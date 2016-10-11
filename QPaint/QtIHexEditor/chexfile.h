#ifndef CHEXFILE_H
#define CHEXFILE_H

#include <vector>
#include <QString>
#include <QStringList>

unsigned int hexToUInt(const QString &str);

class CHexLine
{
    /**
      * @brief      Macro to automatically create a getter and a setter for a variable.
      * @param var  The variable this property should handle.
      * @param name The name of the property. This will create two methods get<name> and set<name>
      */
    #define MK_PROP3(var, name, type) const type& get##name() { return var; } \
        void set##name(const type &value) { var = value; }
public:
    enum RecordTypes { Data = 0, EndOfFile, ExtendedSegmentAddress, StartSegmentAddress, ExtendedLinearAddress, StartLinearAddress };
private:
    unsigned char   m_ucByteCount;
    unsigned short  m_usAddress;
    RecordTypes     m_RecordType;
    unsigned char   m_ucChecksum;

    std::vector<unsigned char>    m_vData;

    QString getHexNumeric(unsigned int number);

    void    updateChecksum();

public:
    CHexLine();
    CHexLine(const QString &line);

    MK_PROP3(m_ucByteCount, ByteCount, unsigned char)
    MK_PROP3(m_usAddress, Address, unsigned short)
    MK_PROP3(m_RecordType, RecordType, RecordTypes)
    MK_PROP3(m_ucChecksum, Checksum, unsigned char)

    unsigned int columnCount() { return m_vData.size(); }

    int getByte(unsigned int uiColumn) { if(uiColumn >= columnCount()) return -1; return m_vData[uiColumn]; }
    void setByte(unsigned int uiColumn, unsigned char ucByte);

    void    fillFromLine(const QString& line);
    QString getCompleteString();
    QString getAddressString();
    QString getRecordTypeString();
    QString getDataString();
    QString getChecksumString();
};

class CHexFile
{
private:
    std::vector<CHexLine>   m_vLines;
public:
    CHexFile();

    void readFile(const QString &strPath);
    void writeFile(const QString &strFile);

    void setByte(unsigned int uiLine, unsigned int uiColumn, unsigned char ucByte);

    void fillStringList(QStringList &list);

    unsigned int getLineCount();
    CHexLine getLine(unsigned int i);
    int getByte(unsigned int line, unsigned int byte);
};

#endif // CHEXFILE_H
