#ifndef CHEXWIDGET_H
#define CHEXWIDGET_H

#include <QWidget>
#include <QPoint>
#include <list>
#include "chexfile.h"

class CHexWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CHexWidget(QWidget *parent = 0);

    void openFile(const QString &strPath);
    void saveFile(const QString &strFile);
    void paintEvent(QPaintEvent *);
    void keyPressed(QKeyEvent * event);

    bool isModified();

    int  m_cursorPosY;

private:

    struct Modification
    {
        unsigned int line;
        unsigned int byte;
        int value;
    };

    std::list<Modification>::iterator m_currUndoPoint,
                                        m_lastSavePoint;
    std::list<Modification>  m_undoList;

    CHexFile m_currentFile;

    unsigned int m_uiCurrentLine;
    unsigned int m_uiCurrentByte;

    QFont   getFont();

    int     lineToYCoord(int lineNr);
    int     getLineHeight();

    void    moveCursorX(int step);
    void    moveCursorY(int step);

    void undo();
    void redo();
    
signals:
    
public slots:
    
};

#endif // CHEXWIDGET_H
