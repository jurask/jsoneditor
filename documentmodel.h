#ifndef DOCUMENTMODEL_H
#define DOCUMENTMODEL_H

#include <QAbstractItemModel>
#include "jsonobject.h"

class DocumentModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit DocumentModel(QString &data, QObject *parent = nullptr);
    ~DocumentModel() override;

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // Editable:
    void addItem(const QModelIndex &ind, JsonItem *item);
    void addItem(const QModelIndex& ind, ItemType type, JsonItem *item);

    /*bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;*/

private:
    JsonObject* root;
    QString parseError;
    bool dirty;
};

#endif // DOCUMENTMODEL_H
