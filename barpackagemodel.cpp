#include "barpackagemodel.h"

BarPackageModel::BarPackageModel(QObject *parent) :
    QStandardItemModel(parent)
{

setColumnCount(3);

QStandardItem * item =new QStandardItem;
item->setText("Watch.bar");

appendRow(item);


}
