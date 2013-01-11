#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#define PATH "/home/sacha/bbndk/host_10_0_9_404/linux/x86/usr/bin"

#include <QToolBar>
#include <QSettings>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mManager = new BlackberryManager;

    ui->setupUi(this);
    init();
    connect(mConnectAction,SIGNAL(triggered()),this,SLOT(connection()));
    connect(mManager,SIGNAL(deviceInfoReceived(QVariantMap)),this,SLOT(setDeviceInfo(QVariantMap)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connection()
{

    mManager->setPassword(mPasswordBox->text());
    mManager->setIpAddress(mIpComboBox->text());
    mManager->listDeviceInfo();

    QSettings settings;
    settings.setValue("ipAddress", mIpComboBox->text());



}

void MainWindow::showBlackBerryDeployDialog()
{

    QString path = QFileDialog::getOpenFileName(this,"blackberryDeploy","","blackberry-deploy");
    mManager->setBlackberryDeployPath(path);
    QSettings settings;
    settings.setValue("blackberryDeployPath",path);


}

void MainWindow::setDeviceInfo(const QVariantMap &data)
{


    statusBar()->showMessage(QString("Connected with  %1 %2").arg(data["modelfullname"].toString()).arg(data["flash_version"].toString()));


}

void MainWindow::init()
{


    mIpComboBox = new QLineEdit;
    mPasswordBox = new QLineEdit;

    mIpComboBox->setPlaceholderText("IP address");
    mPasswordBox->setPlaceholderText("Password");

    mIpComboBox->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
    mPasswordBox->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));

    QToolBar * toolbar = new QToolBar;
    toolbar->addWidget(mIpComboBox);
    toolbar->addWidget(mPasswordBox);
    mConnectAction = toolbar->addAction("connect");
    toolbar->addSeparator();
    mAddAction = toolbar->addAction("Add bar");
    mRemAction = toolbar->addAction("Remove bar");
    mInstallAction = toolbar->addAction("install(s)");
    mUnInstallAction = toolbar->addAction("UnInstall(s)");

    addToolBar(toolbar);



    loadSettings();


}

void MainWindow::loadSettings()
{
    QSettings settings;
    mIpComboBox->setText(settings.value("ipAddress").toString());
    mManager->setBlackberryDeployPath(settings.value("blackberryDeployPath").toString());

    if ( mManager->blackberryDeployPath().isEmpty())
        showBlackBerryDeployDialog();


}

