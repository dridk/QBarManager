#ifndef BLACKBERRYMANAGER_H
#define BLACKBERRYMANAGER_H

#include <QObject>
#include <QProcess>
#include <QVariantMap>
class BlackberryManager : public QObject
{
    Q_OBJECT
public:
    explicit BlackberryManager(QObject *parent = 0);

    bool setBlackberryDeployPath(const QString& path);
    bool isAppRunning(const QString& package);
    void setIpAddress(const QString& ip);
    void setPassword(const QString& password);

    const QString& blackberryDeployPath() const;
    QVariantMap deviceInfo() const;


public slots:
    void installApp(const QString& package, bool launchAfter = false);
    void launchApp(const QString& package);
    void uninstallApp(const QString& package);
    void terminateApp(const QString& package);
    void listInstalledApps();
    void listDeviceInfo();



protected slots:
    void parseStandardOutput();
    void parseStandardError();
    void parseListDeviceInfo();
    void finished(int exitCode);
    void clearReceivedBuffer();

signals:
    void deviceInfoReceived(const QVariantMap& data);

private:
    QString mIpAddress;
    QString mPassworld;
    QString mProgram;
    QProcess * mProcess;
    QVariantMap mDeviceInfo;
    QByteArray mReceivedBuffer;
    QString mCurrentAction;





    
};

#endif // BLACKBERRYMANAGER_H
