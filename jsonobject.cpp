#include "jsonobject.h"
#include <QJsonObject>
#include <QIcon>

JsonObject::JsonObject(const QJsonValue &data, JsonItem *parent):JsonItem(parent){
    QJsonObject object = data.toObject();
    QStringList keys = object.keys();
    for (QString key:keys){
        QJsonValue value = object[key];
        JsonItem* item;
        switch(value.type()){
            case QJsonValue::Null:
                item = new JsonItem(this);
                break;
            /*case QJsonValue::Bool:
                item = new JsonBool(value, this);
                break;
            case QJsonValue::Double:
                item = new JsonDouble(value, this);
                break;
            case QJsonValue::String:
                item = new JsonString(value, this);
                break;
            case QJsonValue::Array:
                item = new JsonArray(value, this);
                break;*/
            case QJsonValue::Object:
                item = new JsonObject(value, this);
                break;
            default:
                item = new JsonItem(this);
                break;
        }
        pchildren.append(QPair<QString, JsonItem*>(key, item));
    }
}

JsonObject::JsonObject(JsonItem *parent):JsonItem(parent){
}

JsonObject::~JsonObject(){
    for (QPair<QString, JsonItem*>& child:pchildren){
        delete child.second;
    }
}

JsonItem* JsonObject::child(int row){
    if (pchildren.length() > row)
        return pchildren[row].second;
    else
        return nullptr;
}

int JsonObject::indexOf(JsonItem* item) const{
    for (int i = 0; i < pchildren.length(); i++){
        if (pchildren[i].second == item)
            return i;
    }
    return -1;
}

int JsonObject::rowCount() const{
    return pchildren.length();
}

QVariant JsonObject::data(int role, int column){
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        if (column == 1)
            return "Object";
        else if (parent())
            return parent()->labelForChild(this);
    } else if (role == Qt::DecorationRole && column == 0)
        return QIcon::fromTheme("folder");
    else if (role == Qt::UserRole)
        return QVariant::fromValue(type());
    return QVariant();
}

QString JsonObject::labelForChild(JsonItem *child) const{
    int index = indexOf(child);
    return pchildren[index].first;
}

QJsonValue JsonObject::toJson() const{
    QJsonObject object;
    for (QPair<QString, JsonItem*> data:pchildren)
        object.insert(data.first, data.second->toJson());
    return QJsonValue(object);
}

bool JsonObject::insertChild(QPair<QString, JsonItem *> child, int position){
    pchildren.insert(position, child);
    return true;
}

ItemType JsonObject::type() const{
    return ItemType::Object;
}

bool JsonObject::setLabel(JsonItem *item, QString label){
    int index = indexOf(item);
    if (index != -1){
        pchildren[index].first = label;
        return true;
    } else
        return false;
}

bool JsonObject::removeChildrenAt(int i){
    delete pchildren[i].second;
    pchildren.removeAt(i);
    return true;
}

bool JsonObject::appendItem(JsonItem *item, QString label){
    pchildren.append(QPair<QString, JsonItem*>(label, item));
}
