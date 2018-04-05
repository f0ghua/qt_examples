#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString s = "Hello World";
    ui->plainTextEdit->appendPlainText(s);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonBox_accepted()
{
    ui->xSLed->switchXSLed();
}
