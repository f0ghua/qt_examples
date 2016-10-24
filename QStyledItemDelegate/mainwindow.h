#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "XIGBConfigModel.h"
#include "XIGBSignalDelegate.h"
#include "XIGBMsgDelegate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_m_btnStep_clicked();
    void on_m_btnRun_clicked();

private:
    Ui::MainWindow *ui;

    XIGBConfigMsgModel *m_modelMessage;
    XIGBConfigSignalModel *m_modelSignal;
    XIGBMsgDelegate *m_delegateMessage;

    void tableMessageInitialize();
    void tableSignalInitialize();
};

#endif // MAINWINDOW_H
