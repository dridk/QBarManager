#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QLineEdit>
#include "blackberrymanager.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connection();
    void showBlackBerryDeployDialog();
    void setDeviceInfo(const QVariantMap& data);

protected:
    void init();
    void loadSettings();


private:
    BlackberryManager * mManager;
    Ui::MainWindow *ui;
    QLineEdit * mIpComboBox;
    QLineEdit * mPasswordBox;
    QAction * mConnectAction;
    QAction * mAddAction;
    QAction * mRemAction;
    QAction * mInstallAction;
    QAction * mUnInstallAction;

};

#endif // MAINWINDOW_H
