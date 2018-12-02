#include "document.h"
#include <QTextStream>
#include <QFileInfo>

Document::Document(const QString& name, QObject* parent) : QObject(parent){
    documentname = name;
    documentpath = "";
    data = new QTextDocument("", this);
    valid = true;
}

Document::Document(QFile& file, QObject* parent) : QObject(parent){
    if (!file.exists()){
        valid = false;
        return;
    }
    bool ok = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!ok){
        valid = false;
        return;
    }
    QTextStream in(&file);
    in.setCodec("UTF-8");
    data = new QTextDocument(in.readAll(), this);
    file.close();
    QFileInfo info(file);
    documentpath = info.canonicalFilePath();
    documentname = info.baseName();
    valid = true;
}

bool Document::save(){
    QFile file(documentpath);
    bool ok = file.open(QIODevice::WriteOnly | QIODevice::Text);
    if (!ok)
        return false;
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << data->toPlainText();
    out.flush();
    file.close();
    return true;
}

bool Document::saveAs(QString& name){
    QFileInfo info(name);
    documentpath = info.canonicalFilePath();
    documentname = info.baseName();
    emit nameChanged(documentname);
    return save();
}

QString Document::name() const{
    return documentname;
}

QTextDocument* Document::textDocument(){
    return data;
}

bool Document::isValid() const{
    return valid;
}
