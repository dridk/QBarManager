#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QLineEdit>
#include <QStringListModel>
#include <QLabel>
#include <QProgressBar>
#include "blackberrymanager.h"
#include "barpackagemodel.h"
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
    void showError(int error, const QString& message);
    void addPackage();
    void remPackage();
    void loadData(const QVariantList& data);
    void launchApp();
    void openGithub();

protected slots:
    void setProcessing(bool processing);


protected:
    void init();
    void loadSettings();


private:
    BlackberryManager * mManager;
    BarPackageModel * mModel;
    QStringListModel mTempModel; // just for testing
    Ui::MainWindow *ui;
    QToolBar * mToolBar;
    QLabel * mProgressLabel;
    QLineEdit * mIpComboBox;
    QLineEdit * mPasswordBox;
    QAction * mConnectAction;
    QAction * mRunAction;
    QAction * mInstallAction;
    QAction * mUnInstallAction;
    QAction * mGithubAction;

};

#endif // MAINWINDOW_H
