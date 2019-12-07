#ifndef JSONITEM_H
#define JSONITEM_H

#include <QVariant>
#include <QJsonValue>
#include "types.h"


class JsonItem
{
public:
    JsonItem(JsonItem* parent = nullptr);
    virtual ~JsonItem();
    virtual JsonItem* child(int row);
    virtual JsonItem* parent() const;
    virtual int row();
    virtual int indexOf(JsonItem *item) const;
    virtual int rowCount() const;
    virtual QVariant data(int role, int column);
    virtual QString labelForChild(JsonItem *child) const;
    virtual QJsonValue toJson() const;
    virtual bool insertChild(QPair<QString, JsonItem *> child, int position);
    virtual ItemType type() const;
    virtual bool setData(const QVariant& data);
    bool setLabelInContainer(QString label);
    virtual bool removeChildrenAt(int i);
    virtual bool appendItem(JsonItem* item, QString label);
    void setParent(JsonItem* parent);

private:
    JsonItem* parentItem = nullptr;
};

#endif // JSONITEM_H
