#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

static const QString g_style = \
    "QTableView {\
        padding: 2px;\
    }\
    QHeaderView::section:horizontal {\
        height: 24px;\
    }\
    QHeaderView::section {\
        border: 1px solid;\
        border-top-color: rgb(255, 255, 255);\
        border-bottom-color: rgb(128, 128, 128);\
        border-left-color: rgb(255, 255, 255);\
        border-right-color: rgb(128, 128, 128);\
    }\
    QTableView::item {\
        color: black;\
        border: 1px solid;\
        border-top-color: rgb(255, 255, 255);\
        border-bottom-color: rgb(128, 128, 128);\
        border-left-color: rgb(255, 255, 255);\
        border-right-color: rgb(128, 128, 128);\
        background-color: rgb(220, 220, 220);\
    }";

#ifndef F_NO_DEBUG
//#include "XTableDebug.h"
#endif

void MainWindow::tableMessageInitialize()
{
    HierarchicalHeaderView *hv = new HierarchicalHeaderView(Qt::Horizontal, ui->m_tblMessage);
    hv->setHighlightSections(true);
    hv->setSectionsClickable(true);
    ui->m_tblMessage->setHorizontalHeader(hv);

    m_modelMessage = new XIGBConfigMsgModel();
    ui->m_tblMessage->setModel(m_modelMessage);

    m_delegateMessage = new XIGBMsgDelegate();
    ui->m_tblMessage->setItemDelegate(m_delegateMessage);

    // Make the combo boxes always displayed.
    /*
    for (int i = 0; i < m_modelMessage->rowCount(); ++i) {
        for (int j = 0; j < m_modelMessage->columnCount(); j++)
            ui->m_tblMessage->openPersistentEditor(m_modelMessage->index(i, j));
    }
    */

    ui->m_tblMessage->verticalHeader()->setVisible(false);
    ui->m_tblMessage->horizontalHeader()->setStretchLastSection(true);

    for (int i = 7; i < 15; i++) {
        ui->m_tblMessage->setColumnWidth(i, 32);
    }
}

void MainWindow::tableSignalInitialize()
{
    HierarchicalHeaderView *hvSignal = new HierarchicalHeaderView(Qt::Horizontal, ui->m_tblSignal);
    hvSignal->setHighlightSections(true);
    hvSignal->setSectionsClickable(true);
    ui->m_tblSignal->setHorizontalHeader(hvSignal);

    m_modelSignal = new XIGBConfigSignalModel();
    ui->m_tblSignal->setModel(m_modelSignal);

    //QPushButton* helpButton = new QPushButton("Help");
    //ui->m_tblSignal->setIndexWidget(m_modelSignal->index(0,0), helpButton);
    XIGBSignalDelegate_RawValue *rawValueDelegate = new XIGBSignalDelegate_RawValue(ui->m_tblSignal);
    ui->m_tblSignal->setItemDelegateForColumn(XIGBSignalDelegate::COL_RAWVALUE, rawValueDelegate);

    XIGBSignalDelegate_Define *defineDelegate = new XIGBSignalDelegate_Define(ui->m_tblSignal);
    ui->m_tblSignal->setItemDelegateForColumn(XIGBSignalDelegate::COL_DEFINE, defineDelegate);

    QCheckBoxDelegate *checkboxDelegate = new QCheckBoxDelegate(ui->m_tblSignal);
    ui->m_tblSignal->setItemDelegateForColumn(XIGBSignalDelegate::COL_ENABLE, checkboxDelegate);

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int col = 0;

    ui->setupUi(this);

    this->setStyleSheet(g_style);
    ui->m_splMain->setStretchFactor(0, 4);
    ui->m_splMain->setStretchFactor(1, 2);

    tableMessageInitialize();
    tableSignalInitialize();
/*
    QStandardItem *item = new QStandardItem( true );
    item->setCheckable(true);
    item->setCheckState(Qt::Unchecked);
    m_modelMessage->setItem(0, 3, item);
*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_m_btnStep_clicked()
{
	for (int i = 0; i < m_modelMessage->m_params.count(); i++) {
		qDebug() << m_modelMessage->m_params.at(i).msgFrameType;
	}
}

void MainWindow::on_m_btnRun_clicked()
{

}
