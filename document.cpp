#include "document.h"
#include <QTextStream>
#include <QFileInfo>
#include <QDir>

Document::Document(const QString& name, QObject* parent) : QObject(parent){
    documentname = name;
    documentpath = "";
    data = new QTextDocument("", this);
    connect(data, &QTextDocument::modificationChanged, this, &Document::dirtyChanged);
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
    data->setModified(false);
    connect(data, &QTextDocument::modificationChanged, this, &Document::dirtyChanged);
    valid = true;
}

bool Document::save(){
    QDir dir = (QFileInfo(documentpath).dir());
    if (!dir.exists()){
        if (!dir.mkpath("."))
            return false;
    }
    QFile file(documentpath);
    bool ok = file.open(QIODevice::WriteOnly | QIODevice::Text);
    if (!ok)
        return false;
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << data->toPlainText();
    out.flush();
    file.close();
    data->setModified(false);
    return true;
}

bool Document::saveAs(QString& name){
    documentpath = name;
    if (!save())
        return false;
    QFileInfo info(name);
    documentname = info.baseName();
    emit nameChanged(documentname);
    return true;
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

bool Document::isDirty() const{
    return data->isModified();
}

bool Document::hasPath() const{
    return documentpath != "";
}
