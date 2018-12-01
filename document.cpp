#include "document.h"
#include <QTextStream>
#include <QFileInfo>

Document::Document(const QString& name, QObject* parent) : QObject(parent){
    documentname = name;
    documentpath = "";
    data = "";
    valid = true;
}

Document::Document(QFile& file, QObject* parent) : QObject(parent){
    if (!file.exists()){
        valid = false;
        return;
    }
    bool err = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (err){
        valid = false;
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    data = in.readAll();
    file.close();
    QFileInfo info(file);
    documentpath = info.canonicalFilePath();
    documentname = info.baseName();
    valid = true;
}

bool Document::save(){
    QFile file(documentpath);
    bool err = file.open(QIODevice::WriteOnly | QIODevice::Text);
    if (err)
        return false;
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << data;
    out.flush();
    file.close();
    return true;
}

bool Document::saveAs(QString& name){
    QFileInfo info(name);
    documentpath = info.canonicalFilePath();
    documentname = info.baseName();
    return save();
}
