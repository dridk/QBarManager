#include "blackberrymanager.h"
#include <QDebug>
#include <QFile>
BlackberryManager::BlackberryManager(QObject *parent) :
    QObject(parent)
{

    mProcess = new QProcess(this);
    connect(mProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(parseStandardOutput()));
    connect(mProcess,SIGNAL(readyReadStandardError()),this,SLOT(parseStandardError()));
    connect(mProcess,SIGNAL(finished(int)),this,SLOT(finished(int)));
    connect(mProcess,SIGNAL(started()),this,SLOT(clearReceivedBuffer()));

}

bool BlackberryManager::setBlackberryDeployPath(const QString &path)
{
    if (!QFile::exists(path))
        return false;

    mProgram = path;
    return true;
}

void BlackberryManager::installApp(const QString &package, bool launchAfter)
{
    QStringList arguments;
    arguments << "-listDeviceInfo"<<mIpAddress<<"-password"<<mPassworld;
    mProcess->start(mProgram,arguments);
}

void BlackberryManager::launchApp(const QString &package)
{
}

void BlackberryManager::uninstallApp(const QString &package)
{
}

void BlackberryManager::terminateApp(const QString &package)
{
}


bool BlackberryManager::isAppRunning(const QString &package)
{
}

void BlackberryManager::setIpAddress(const QString &ip)
{
    mIpAddress = ip;
}

void BlackberryManager::setPassword(const QString &password)
{
    mPassworld = password;
}

const QString &BlackberryManager::blackberryDeployPath() const
{
    return mProgram;
}

QVariantMap BlackberryManager::deviceInfo() const
{
    return  mDeviceInfo;
}

void BlackberryManager::listInstalledApps()
{
}

void BlackberryManager::listDeviceInfo()
{
    if (mCurrentAction.isEmpty()){
        QStringList arguments;
        arguments << "-listDeviceInfo"<<mIpAddress<<"-password"<<mPassworld;
        mCurrentAction = "listDeviceInfo";
        mProcess->start(mProgram,arguments);
    }

}

void BlackberryManager::parseStandardOutput()
{
    QString data = mProcess->readAllStandardOutput();
    mReceivedBuffer.append(data);
}
void BlackberryManager::parseStandardError()
{

    qDebug()<<mProcess->readAllStandardError();


}

void BlackberryManager::parseListDeviceInfo()
{
    QString raw = mReceivedBuffer;
    mDeviceInfo.clear();
    foreach (QString line, raw.split("\n"))
    {
        QString key = line.section("::",0,0);
        QString value = line.section("::",1,1);

        if (!key.isEmpty() && !value.isEmpty())
            mDeviceInfo[key] = value;
    }


    emit deviceInfoReceived(mDeviceInfo);

}

void BlackberryManager::finished(int exitCode)
{
    if (mCurrentAction == "listDeviceInfo")
        parseListDeviceInfo();





    mCurrentAction.clear();



}

void BlackberryManager::clearReceivedBuffer()
{
    mReceivedBuffer.clear();
}
