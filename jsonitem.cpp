#include "jsonitem.h"
#include <QtGlobal>
#include <QIcon>
#include "jsonobject.h"

JsonItem::JsonItem(JsonItem* parent){
    parentItem = parent;
}

JsonItem::~JsonItem(){
}

JsonItem* JsonItem::child(int row){
    Q_UNUSED(row);
    return nullptr;
}

JsonItem* JsonItem::parent() const{
    return parentItem;
}

int JsonItem::row(){
    if (parentItem)
        return parentItem->indexOf(this);
    else
        return 0;
}

int JsonItem::indexOf(JsonItem *item) const{
    Q_UNUSED(item);
    return 0;
}

int JsonItem::rowCount() const{
    return 0;
}

QVariant JsonItem::data(int role, int column){
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (column == 1)
            return "null";
        else
            return parent()->labelForChild(this);
    } else if (role == Qt::DecorationRole && column == 0)
        return QIcon("://icons/null.svg");
    else if (role == Qt::UserRole)
        return QVariant::fromValue(type());
    else
        return QVariant();
}

QString JsonItem::labelForChild(JsonItem *child) const{
    Q_UNUSED(child);
    return "";
}

QJsonValue JsonItem::toJson() const{
    return QJsonValue();
}

bool JsonItem::insertChild(QPair<QString, JsonItem *> child, int position){
    Q_UNUSED(child);
    Q_UNUSED(position);
    return false;
}

ItemType JsonItem::type() const{
    return ItemType::Null;
}

bool JsonItem::setData(const QVariant &data){
    Q_UNUSED(data);
    return false;
}

bool JsonItem::setLabelInContainer(QString label){
    if (parentItem->type() == ItemType::Object){
        JsonObject* parent = static_cast<JsonObject*>(parentItem);
        return parent->setLabel(this, label);
    } else
        return false;
}

bool JsonItem::removeChildrenAt(int i){
    Q_UNUSED(i);
    return false;
}

bool JsonItem::appendItem(JsonItem *item, QString label){
    Q_UNUSED(label);
    Q_UNUSED(item);
    return false;
}

void JsonItem::setParent(JsonItem* parent){
    parentItem = parent;
}
