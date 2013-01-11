#ifndef BARPACKAGEMODEL_H
#define BARPACKAGEMODEL_H

#include <QStandardItemModel>

class BarPackageModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit BarPackageModel(QObject *parent = 0);

    void load(const QVariantList& datas);


    
};

#endif // BARPACKAGEMODEL_H
