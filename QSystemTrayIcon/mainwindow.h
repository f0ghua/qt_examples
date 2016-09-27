#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>

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
	void on_action_quit_triggered();
	void onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason);

protected:
	void closeEvent(QCloseEvent *event);

private:
	Ui::MainWindow *ui;

	QSystemTrayIcon *trayicon;
	QMenu *trayiconMenu;
};

#endif // MAINWINDOW_H
