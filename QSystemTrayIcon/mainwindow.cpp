#include "mainwindow.h"
#include "ui_mainwindow.h"

bool quit = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trayicon = new QSystemTrayIcon(this);
    //创建QIcon对象，参数是图标资源，值为项目的资源文件中图标的地址
    QIcon icon(":trayicon");
    trayiconMenu = new QMenu(this);
    //为托盘菜单添加菜单项
    trayiconMenu->addAction(ui->action_quit);
    //为托盘菜单添加分隔符
    trayiconMenu->addSeparator();
    //将创建的QIcon对象作为系统托盘图标
    trayicon->setIcon(icon);
    //显示托盘图标
    trayicon->show();
    //设置系统托盘提示
    trayicon->setToolTip(tr("托盘测试"));
    //将创建菜单作为系统托盘菜单
    trayicon->setContextMenu(trayiconMenu);
    //在系统托盘显示气泡消息提示
    trayicon->showMessage(tr("hahaya"), tr("托盘测试"), QSystemTrayIcon::Information, 5000);

    //为系统托盘绑定单击信号的槽 即图标激活时
    connect(trayicon,
    	SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
    	this,
    	SLOT(onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
	switch(reason)
	{
  	//单击
	case QSystemTrayIcon::Trigger:
		break;
  	//双击
	case QSystemTrayIcon::DoubleClick:
      	//恢复窗口显示
		this->setWindowState(Qt::WindowActive);
		this->show();
		break;
	default:
		break;
	}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (quit) {
		event->accept();
		return;
	}

	if(trayicon->isVisible()) {
		hide();
		event->ignore();
	}
}

void MainWindow::on_action_quit_triggered()
{
	quit = true;
	this->hide();
	this->close();
}
