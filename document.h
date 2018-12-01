#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QFile>
#include <QIODevice>
#include "documentmodel.h"

class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(const QString& name, QObject* parent = nullptr);
    explicit Document(QFile &file, QObject* parent = nullptr);
    bool save();
    bool saveAs(QString& name);

signals:

public slots:
private:
    QString data;
    QString documentname;
    QString documentpath;
    DocumentModel* model = nullptr;
    bool valid;
};

#endif // DOCUMENT_H
