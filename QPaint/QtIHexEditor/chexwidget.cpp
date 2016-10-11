#include "chexwidget.h"
#include "QPainter"
#include <QFont>
#include <QFontMetrics>
#include <QKeyEvent>

unsigned int keyToHexValue(int key)
{
    if(key >= Qt::Key_0 && key <= Qt::Key_9)
    {
        return key - static_cast<unsigned int>(Qt::Key_0);
    }

    return key - 0x37;
}

CHexWidget::CHexWidget(QWidget *parent) :
    QWidget(parent)
{
    m_undoList.clear();
    m_currUndoPoint = m_undoList.begin();
    m_lastSavePoint = m_undoList.end();
}

void CHexWidget::openFile(const QString &strPath)
{
    this->m_currentFile.readFile(strPath);
    this->update();
    m_uiCurrentLine = 0;
    m_uiCurrentByte = 0;
    m_undoList.clear();
    m_currUndoPoint = m_undoList.begin();
    m_lastSavePoint = m_undoList.end();
}

void CHexWidget::saveFile(const QString& strFile)
{
    this->m_currentFile.writeFile(strFile);
    m_lastSavePoint = m_currUndoPoint;
}

void CHexWidget::paintEvent(QPaintEvent *)
{
    QBrush white(Qt::white);
    QBrush black(Qt::black);
    QPainter painter(this);

    QFont font = getFont();

    QFontMetrics metrics(font);

    painter.setBackground(white);
    painter.setBrush(white);
    painter.setFont(font);

    painter.drawRect(0, 0, this->width(), this->height());
    painter.setBrush(black);
    painter.drawLine(0, getLineHeight(), this->width(), getLineHeight());

    painter.drawText(10, getLineHeight() - 4, "Address");
    painter.drawText(80, getLineHeight() - 4, "Data");

    int y = 2*getLineHeight();
    this->setMinimumHeight(y + lineToYCoord(m_currentFile.getLineCount()));

    painter.drawLine(75, 0, 75, this->height());
    int maxWidth = 0;
    unsigned int lineCnt = m_currentFile.getLineCount();

    if(lineCnt == 0)
    {
        maxWidth = 120;
    }
    else
    {
        for(unsigned int i=0; i<lineCnt; i++)
        {
            y = lineToYCoord(i);
            QString addr =  m_currentFile.getLine(i).getAddressString();
            painter.drawText(10, y,  addr);
            if(m_uiCurrentLine == i)
            {
                QString lineStr = m_currentFile.getLine(i).getDataString();
                int markerW = metrics.charWidth(lineStr, m_uiCurrentByte);
                int markerX = metrics.width(lineStr, m_uiCurrentByte);

                unsigned int x = 80;
                unsigned int h = getLineHeight();

                painter.fillRect(markerX+x, y-h+2, markerW, h+2, Qt::gray);
            }

            painter.drawText(80, y,  m_currentFile.getLine(i).getDataString());

            if(80 + metrics.width(m_currentFile.getLine(i).getDataString()) > maxWidth)
                maxWidth = 80 + metrics.width(m_currentFile.getLine(i).getDataString());
        }

        for(unsigned int i=0; i<lineCnt; i++)
        {
            y = lineToYCoord(i);
            QString checksum = this->m_currentFile.getLine(i).getChecksumString();
            painter.drawText(maxWidth + 25, y, checksum);
        }
    }

    this->setMinimumWidth(maxWidth+100);

    painter.drawLine(maxWidth + 20, 0, maxWidth + 20, this->height());

    painter.drawText(maxWidth + 25, metrics.height() + 1, "Checksum");
}

void CHexWidget::keyPressed(QKeyEvent *event)
{
    int key = event->key();
    if((key >= Qt::Key_0 && key <= Qt::Key_9) || (key >= Qt::Key_A && key <= Qt::Key_F))
    {
        /*if(m_currUndoPoint != m_undoList.begin())
        {
            m_undoList.erase(m_undoList.begin(), m_currUndoPoint);
        }*/


        int byte = m_currentFile.getByte(m_uiCurrentLine, m_uiCurrentByte/2);

        Modification mod;
        mod.line = m_uiCurrentLine;
        mod.byte = m_uiCurrentByte/2;
        mod.value = byte;

        m_undoList.insert(m_currUndoPoint, mod);
        m_currUndoPoint--;

        if(byte == -1)
        {
            QWidget::keyPressEvent(event);
            return;
        }

        if(m_uiCurrentByte % 2 == 0)
        {
            // MSB selected
            byte = (keyToHexValue(key) << 4) + (byte & 0x0F);
        }
        else
        {
            // LSB selected
            byte = keyToHexValue(key) + (byte & 0xF0);
        }

        byte = byte & 0x00FF;
        m_currentFile.setByte(m_uiCurrentLine, m_uiCurrentByte/2, byte);
        moveCursorX(1);
    }
    else
    {
        switch(key)
        {
        case Qt::Key_U:
            if((event->modifiers() & Qt::ShiftModifier) == 0)
                undo();
            else
                redo();
            break;
        case Qt::Key_H:
        case Qt::Key_Left:
            moveCursorX(-1);
            break;

        case Qt::Key_L:
        case Qt::Key_Right:
            moveCursorX(1);
            break;

        case Qt::Key_K:
        case Qt::Key_Up:
            if(m_uiCurrentLine != 0)
                m_uiCurrentLine -= 1;
            break;
        case Qt::Key_J:
        case Qt::Key_Down:
            if(m_uiCurrentLine + 1 < m_currentFile.getLineCount())
                m_uiCurrentLine += 1;

            break;

        default:
            QWidget::keyPressEvent(event);
            return;
        }
    }



    m_cursorPosY = lineToYCoord(m_uiCurrentLine);

    this->update();
}

bool CHexWidget::isModified()
{
    return (m_currUndoPoint != m_lastSavePoint);
}


QFont CHexWidget::getFont()
{
    QFont font;
    font.setFamily("Courier");
    font.setPointSize(10);

    return font;
}

int CHexWidget::lineToYCoord(int lineNr)
{
    QFontMetrics metrics(getFont());
    int h = getLineHeight();
    return (2*h + lineNr*h);
}

int CHexWidget::getLineHeight()
{
    QFontMetrics metrics(getFont());
    return metrics.height() + 5;
}

void CHexWidget::moveCursorX(int step)
{
    if(step > 0)
    {
        if(m_uiCurrentByte+step < 2*m_currentFile.getLine(m_uiCurrentLine).columnCount())
            m_uiCurrentByte += step;
    }
    else
    {
        int currByte = m_uiCurrentByte;
        if(currByte+step >= 0)
            m_uiCurrentByte += step;
    }
}

void CHexWidget::moveCursorY(int step)
{
    if(step < 0)
    {
        int currLine = m_uiCurrentLine;
        if(currLine+step >= 0)
            m_uiCurrentLine += step;
    }
    else
    {

    }
}

void CHexWidget::undo()
{
    if(m_currUndoPoint != m_undoList.end())
    {
        int value = m_currUndoPoint->value;
        auto line = m_currUndoPoint->line;
        auto byte = m_currUndoPoint->byte;

        int oldValue = m_currentFile.getByte(line, byte);
        m_currUndoPoint->value = oldValue;
        m_currUndoPoint++;
        m_currentFile.setByte(line, byte, value);
    }
}

void CHexWidget::redo()
{
    if(m_currUndoPoint != m_undoList.begin())
    {
        m_currUndoPoint--;
        int value = m_currUndoPoint->value;
        auto line = m_currUndoPoint->line;
        auto byte = m_currUndoPoint->byte;

        int oldValue = m_currentFile.getByte(line, byte);
        m_currUndoPoint->value = oldValue;
        m_currentFile.setByte(line, byte, value);
    }
}
