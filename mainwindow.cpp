#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QDebug>
#define PATH "/home/sacha/bbndk/host_10_0_9_404/linux/x86/usr/bin"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mProcess = new QProcess(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(action()));
   // connect(mProcess,SIGNAL(finished(int)),this,SLOT(loadText()));
    connect(mProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(loadText()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::action()
{

    QString program = QString(PATH)+"/blackberry-deploy -listDeviceInfo 169.254.0.1 -password descent ";
    qDebug()<<program;
    QStringList arguments;
    //arguments << "-listDeviceInfo"<<"-password descent";


    mProcess->start(program);


}

void MainWindow::loadText()
{
    qDebug()<<"END";
    ui->plainTextEdit->appendPlainText(mProcess->readAllStandardOutput());



}
