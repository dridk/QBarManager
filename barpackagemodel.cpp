#include "barpackagemodel.h"
#include <QDebug>
BarPackageModel::BarPackageModel(QObject *parent) :
    QStandardItemModel(parent)
{





}

void BarPackageModel::load(const QVariantList &datas)
{
clear();
setHorizontalHeaderLabels(QStringList()<<"application"<<"version");


foreach ( QVariant item, datas)
{


    QString rawName =item.toMap().value("name").toString();
    QString id =item.toMap().value("id").toString();
    QString version =item.toMap().value("version").toString();


    QStringList names = rawName.remove(id.replace("-",".")).split(".");




    QString name = names[names.length()-2];

    QStandardItem * nameItem = new QStandardItem(0);
    nameItem->setData(item);
    nameItem->setText(name);
    nameItem->setIcon(QIcon(":app.png"));
    if (rawName.contains("sys"))
    nameItem->setEnabled(false);

    QStandardItem * versionItem = new QStandardItem(1);
    versionItem->setText(version);

    QList<QStandardItem*> items;
    items.append(nameItem);
    items.append(versionItem);

    appendRow(items);




}










}
