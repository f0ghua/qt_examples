#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "chexwidget.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

    CHexWidget *m_hexWidget;

    QString     m_strOpenedFile;

    void saveAs();
    void updateTitle();

    void keyPressEvent(QKeyEvent *);
    
public:
    explicit MainWindow(QWidget *parent = 0);
private slots:
    void on_actionQuit_triggered();
    void on_action_Open_triggered();
    void on_action_Save_triggered();
    void on_action_Save_as_triggered();
};

#endif // MAINWINDOW_H
