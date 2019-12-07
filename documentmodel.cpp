#include "documentmodel.h"
#include "jsonobject.h"
#include <QJsonObject>
#include <QJsonParseError>
#include <QTextCodec>

DocumentModel::DocumentModel(QString& data, QObject* parent) : QAbstractItemModel(parent){
    root = new JsonObject();
    JsonItem* rootElement = nullptr;
    QJsonParseError error;
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QJsonDocument jsonDocument = QJsonDocument::fromJson(codec->fromUnicode(data), &error);
    if (error.error != QJsonParseError::NoError){
        // error parsing file
        rootElement = new JsonItem(root);
        parseError = error.errorString();
    }
    if (jsonDocument.isObject()){
        rootElement = new JsonObject(jsonDocument.object(), root);
        //valid = true;
    }
    /*else if (jsonDocument.isArray()){
        rootElement = new JsonArray(data.array(), root);
        //valid = true;
    }*/
    else{
        rootElement = new JsonItem(root);
        //valid = true;
    }
    addItem(QModelIndex(), rootElement);
    dirty = false;
}

DocumentModel::~DocumentModel(){
    if (root)
        delete root;
}

QModelIndex DocumentModel::index(int row, int column, const QModelIndex &parent) const{
    if (!hasIndex(row, column, parent))
        return QModelIndex();
    JsonItem* parentItem;
    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<JsonItem*>(parent.internalPointer());
    JsonItem* child = parentItem->child(row);
    if (child)
        return createIndex(row, column, child);
    else
        return QModelIndex();
}

QModelIndex DocumentModel::parent(const QModelIndex &index) const{
    if (!index.isValid())
        return QModelIndex();
    JsonItem* child = static_cast<JsonItem*>(index.internalPointer());
    JsonItem* parent = child->parent();
    if (parent != root)
        return createIndex(parent->row(), 0, parent);
    else
        return QModelIndex();
}

int DocumentModel::rowCount(const QModelIndex &parent) const{
    JsonItem * item;
    if (!parent.isValid())
        item = root;
    else
        item = static_cast<JsonItem*>(parent.internalPointer());
    return item->rowCount();
}

int DocumentModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return 2;
}

QVariant DocumentModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();
    return static_cast<JsonItem*>(index.internalPointer())->data(role, index.column());
}

QVariant DocumentModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role == Qt::DisplayRole){
        if (section == 0)
            return "Key";
        else
            return "Value";
    } else
        return QVariant();

}

void DocumentModel::addItem(const QModelIndex &index, ItemType type, JsonItem* item){
    if (!item){
        switch(type){
            /*case ItemType::Array:
                item = new JsonArray();
                break;*/
            case ItemType::Object:
                item = new JsonObject();
                break;
            /*case ItemType::String:
                item = new JsonString(QString());
                break;
            case ItemType::Double:
                item = new JsonDouble(0);
                break;
            case ItemType::Bool:
                item = new JsonBool(false);
                break;*/
            case ItemType::Null:
                item = new JsonItem();
                break;
            default:
                return;
        }
    }
    if (index.data(Qt::UserRole).value<ItemType>() == ItemType::Array || index.data(Qt::UserRole).value<ItemType>() == ItemType::Object){
        // user has selected object or array, so append item to it
        QModelIndex insertIndex = this->index(index.row(), 0, index.parent());
        beginInsertRows(insertIndex, rowCount(insertIndex), rowCount(insertIndex));
        item->setParent(static_cast<JsonItem*>(index.internalPointer()));
        static_cast<JsonItem*>(index.internalPointer())->appendItem(item, "New item");
        endInsertRows();
        dirty = true;
        //emit statusChanged();
    } else if(index.data(Qt::UserRole).value<ItemType>() == ItemType::Null && !index.parent().isValid()){
        // user has selected null root node, replace it with corresponding item
        if (root->rowCount()){
            beginRemoveRows(QModelIndex(), 0, 0);
            root->removeChildrenAt(0);
            endRemoveRows();
        }
        item->setParent(root);
        beginInsertRows(QModelIndex(), 0, 0);
        root->appendItem(item, "root");
        endInsertRows();
        dirty = true;
        //emit statusChanged();
    } else if (!index.isValid() && rowCount(QModelIndex()) == 0){
        // constructing root element of new model
        item->setParent(root);
        beginInsertRows(QModelIndex(), 0, 0);
        root->appendItem(item, "root");
        endInsertRows();
    }
}

void DocumentModel::addItem(const QModelIndex &ind, JsonItem *item){
    addItem(ind, ItemType::Null, item);
}

/*bool DocumentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags DocumentModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}*/
