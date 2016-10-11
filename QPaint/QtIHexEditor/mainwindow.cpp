#include "mainwindow.h"
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    m_hexWidget = new CHexWidget();
    m_hexWidget->setMinimumSize(1000, 900);
    m_hexWidget->setMaximumSize(1000, 900);
    m_strOpenedFile = "";
    scrollArea->setWidget(m_hexWidget);
    scrollArea->setFocusPolicy(Qt::NoFocus);
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Hex"), "~", tr("Hex files (*.hex);;All files (*.*)"));

    if(fileName.length() > 0)
    {
        this->m_hexWidget->openFile(fileName);
        m_strOpenedFile = fileName;
        this->m_hexWidget->setFocusPolicy(Qt::NoFocus);
        //this->m_hexWidget->setFocus();

        updateTitle();
    }
}

void MainWindow::on_action_Save_triggered()
{
    if(m_strOpenedFile.length() > 0)
    {
        m_hexWidget->saveFile(m_strOpenedFile);
        updateTitle();
    }
    else
    {
        saveAs();
    }
}

void MainWindow::saveAs()
{
    QString savePath = QFileDialog::getSaveFileName(this,tr("Save as"), tr("~"), tr("Hex file (*.hex);;Any file (*.*)"));

    if(savePath.length() > 0)
    {
        m_hexWidget->saveFile(savePath);
        m_strOpenedFile = savePath;
        this->updateTitle();
    }
}

void MainWindow::updateTitle()
{
    QString title = "IHex hex editor";

    if(m_strOpenedFile.length() > 0)
    {
        title += ": " + m_strOpenedFile;
        if(m_hexWidget->isModified())
            title += "*";
    }

    this->setWindowTitle(title);

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    m_hexWidget->keyPressed(event);
    scrollArea->ensureVisible(1, m_hexWidget->m_cursorPosY);
    updateTitle();
}

void MainWindow::on_action_Save_as_triggered()
{
    saveAs();
}
