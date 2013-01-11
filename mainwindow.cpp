#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#define PATH "/home/sacha/bbndk/host_10_0_9_404/linux/x86/usr/bin"

#include <QToolBar>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QMovie>
#include <QLabel>
#include <QUrl>
#include <QDesktopServices>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mManager = new BlackberryManager;
    mModel = new BarPackageModel;

    ui->setupUi(this);
    init();
    connect(mConnectAction,SIGNAL(triggered()),this,SLOT(connection()));
    connect(mManager,SIGNAL(deviceInfoReceived(QVariantMap)),this,SLOT(setDeviceInfo(QVariantMap)));
    connect(mManager,SIGNAL(errorReceived(int,QString)),this,SLOT(showError(int,QString)));
    connect(mManager,SIGNAL(installedAppsReceived(QVariantList)),this,SLOT(loadData(QVariantList)));
    connect(mInstallAction,SIGNAL(triggered()),this,SLOT(addPackage()));
    connect(mUnInstallAction,SIGNAL(triggered()),this,SLOT(remPackage()));
    connect(mRunAction,SIGNAL(triggered()),this,SLOT(launchApp()));
    connect(mManager,SIGNAL(isProcessing(bool)),this,SLOT(setProcessing(bool)));
    connect(ui->actionAbout_Qt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(mGithubAction,SIGNAL(triggered()),this,SLOT(openGithub()));


}

MainWindow::~MainWindow()
{
    delete ui;
    delete mManager;
    delete mModel;
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
    mManager->listInstalledApps();



}

void MainWindow::showError(int error, const QString &message)
{

    QMessageBox::critical(this,"error happens",message);

}

void MainWindow::addPackage()
{

    QString path = QFileDialog::getOpenFileName(this,"bar package","","Bar Package (*.bar)");
    if (!path.isEmpty())
    {
        mManager->installApp(path);

    }





}

void MainWindow::remPackage()
{

    if ( ui->tableView->selectionModel()->selectedRows().isEmpty())
        return;

    QStandardItem * item = mModel->item(ui->tableView->currentIndex().row());
    QString package = item->data().toMap().value("name").toString();
    mManager->uninstallApp(package);


}

void MainWindow::loadData(const QVariantList &data)
{


    mModel->load(data);
    ui->tableView->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);

    ui->tableView->setStyleSheet("");



}

void MainWindow::launchApp()
{

    if ( ui->tableView->selectionModel()->selectedRows().isEmpty())
        return;

    QStandardItem * item = mModel->item(ui->tableView->currentIndex().row());
    QString package = item->data().toMap().value("name").toString();
    mManager->launchApp(package);



}

void MainWindow::openGithub()
{

    QDesktopServices::openUrl(QUrl("https://github.com/dridk/QBarManager"));

}

void MainWindow::init()
{

    ui->tableView->setModel(mModel);
    mToolBar = new QToolBar;
    mIpComboBox = new QLineEdit;
    mPasswordBox = new QLineEdit;
    mProgressLabel = new QLabel;




    QMovie * loading = new QMovie(":loading.gif");
    mProgressLabel->setMovie(loading);
    loading->start();

    mProgressLabel->setVisible(false);


    statusBar()->addPermanentWidget(mProgressLabel);
    mIpComboBox->setPlaceholderText("IP address");
    mPasswordBox->setPlaceholderText("Password");

    mIpComboBox->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));
    mPasswordBox->setSizePolicy(QSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum));

    mToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    mToolBar->setIconSize(QSize(16,16));
    mToolBar->addWidget(mIpComboBox);
    mToolBar->addWidget(mPasswordBox);
    mConnectAction = mToolBar->addAction(QIcon(":refresh.png"),"connect");
    mToolBar->addSeparator();

    mInstallAction = mToolBar->addAction(QIcon(":install.png"),"install(s)");
    mUnInstallAction = mToolBar->addAction(QIcon(":uninstall.png"),"UnInstall(s)");
    mRunAction = mToolBar->addAction(QIcon(":run.png"),"launch");
    mGithubAction = ui->menuHelp->addAction(QIcon(":github.png"),"Feedback");

    ui->menuFile->addAction(mInstallAction);
    ui->menuFile->addAction(mUnInstallAction);
    ui->menuFile->addAction(mRunAction);


    addToolBar(mToolBar);
    ui->tableView->setStyleSheet("QTableView {background-image:url(:bg.png); background-repeat:none;background-position:center center;background-color:white}");


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

void MainWindow::setProcessing(bool processing)
{
    mToolBar->setEnabled(!processing);
    ui->tableView->setEnabled(!processing);
    mProgressLabel->setVisible(processing);
}



