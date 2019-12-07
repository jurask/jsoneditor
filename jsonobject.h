#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "jsonitem.h"
#include <QJsonValue>


class JsonObject : public JsonItem
{
public:
    JsonObject(const QJsonValue &data, JsonItem *parent = nullptr);
    JsonObject(JsonItem *parent = nullptr);
    ~JsonObject() override;
    JsonItem* child(int row) override;
    int indexOf(JsonItem *item) const override;
    int rowCount() const override;
    QVariant data(int role, int column) override;
    QString labelForChild(JsonItem *child) const override;
    QJsonValue toJson() const override;
    bool insertChild(QPair<QString, JsonItem*> child, int position) override;
    ItemType type() const override;
    bool setLabel(JsonItem* item, QString label);
    bool removeChildrenAt(int i) override;
    bool appendItem(JsonItem *item, QString label) override;

private:
    QList<QPair<QString, JsonItem*> > pchildren;

};

#endif // JSONOBJECT_H
