#include "blackberrymanager.h"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QRegExp>
BlackberryManager::BlackberryManager(QObject *parent) :
    QObject(parent)
{

    mProcess = new QProcess(this);
    connect(mProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(parseStandardOutput()));
    connect(mProcess,SIGNAL(readyReadStandardError()),this,SLOT(parseStandardError()));
    connect(mProcess,SIGNAL(finished(int)),this,SLOT(finished(int)));
    connect(mProcess,SIGNAL(started()),this,SLOT(started()));

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
    if (mCurrentAction.isEmpty())
    {
        QStringList arguments;
        arguments <<"-installApp"<<mIpAddress<<"-password"<<mPassworld<<package;
        qDebug()<<mProgram<<arguments.join(" ");
        mCurrentAction = "installApp";
        mProcess->start(mProgram,arguments);


    }
}

void BlackberryManager::launchApp(const QString &package)
{
    if (mCurrentAction.isEmpty())
    {
        QStringList arguments;
        arguments <<"-launchApp"<<mIpAddress<<"-password"<<mPassworld<<"-package-fullname"<<package;
        qDebug()<<mProgram<<arguments.join(" ");
        mCurrentAction = "launchApp";
        mProcess->start(mProgram,arguments);


    }
}

void BlackberryManager::uninstallApp(const QString &package)
{
    if (mCurrentAction.isEmpty())
    {
        QStringList arguments;
        arguments <<"-uninstallApp"<<mIpAddress<<"-password"<<mPassworld<<"-package-fullname"<<package;
        qDebug()<<mProgram<<arguments.join(" ");
        mCurrentAction = "uninstallApp";
        mProcess->start(mProgram,arguments);
    }

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
    if (mCurrentAction.isEmpty()){
        QStringList arguments;
        arguments << "-listInstalledApps"<<mIpAddress<<"-password"<<mPassworld;
        mCurrentAction = "listInstalledApps";
        qDebug()<<mProgram<<arguments.join(" ");
        mProcess->start(mProgram,arguments);
    }
}

void BlackberryManager::listDeviceInfo()
{
    if (mCurrentAction.isEmpty()){
        QStringList arguments;
        arguments << "-listDeviceInfo"<<mIpAddress<<"-password"<<mPassworld;
        mCurrentAction = "listDeviceInfo";
        qDebug()<<mProgram<<arguments.join(" ");
        mProcess->start(QDir::fromNativeSeparators(mProgram),arguments);
    }

}

void BlackberryManager::parseStandardOutput()
{
    QString data = mProcess->readAllStandardOutput();
    mReceivedBuffer.append(data);
}
void BlackberryManager::parseStandardError()
{

    qDebug()<<mProcess->error();
    QString raw = mProcess->readAllStandardError();
    emit errorReceived(mProcess->error(), raw);
    emit isProcessing(false);


}

void BlackberryManager::parseListDeviceInfo()
{
    qDebug()<<"parse listDeviceInfo";
    QString raw = mReceivedBuffer;
    mDeviceInfo.clear();
    foreach (QString line, raw.split("\n"))
    {
        QString key = line.section("::",0,0);
        QString value = line.section("::",1,1);

        if (!key.isEmpty() && !value.isEmpty())
            mDeviceInfo[key] = value;
    }

}

void BlackberryManager::parseListInstalledApps()
{

    qDebug()<<"parse listInfoInstalled";
    QString raw = mReceivedBuffer;
    mInstalledApps.clear();
    foreach (QString line, raw.split("\n"))
    {
        if ( line.contains(QRegExp("^.*::")))
        {
            QStringList splits = line.split(",");
            QVariantMap data;
            for (int i=0;  i< splits.count(); i++)
            {


                if ( i == 0)
                {
                    data["name"] = splits[i].section("::",0,0);
                    data["id"] = splits[i].section("::",1,1);


                }

                if (i==1 )
                    data["version"] = splits[i];
            }

            mInstalledApps.append(data);

        }

    }


    qDebug()<<mInstalledApps;

}

void BlackberryManager::finished(int exitCode)
{
    QString oldAction = mCurrentAction;
    mCurrentAction.clear();

    if(!exitCode)
    {

        if (oldAction == "listDeviceInfo")
        {
            parseListDeviceInfo();
            emit deviceInfoReceived(mDeviceInfo);

        }

        if ( oldAction == "listInstalledApps")
        {
            parseListInstalledApps();
            emit installedAppsReceived(mInstalledApps);
        }

        if ( oldAction == "installApp" || oldAction == "uninstallApp")
            listInstalledApps();

    }

    emit isProcessing(false);


}

void BlackberryManager::started()
{
    mReceivedBuffer.clear();
    emit isProcessing(true);
}
