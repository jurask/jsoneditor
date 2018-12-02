#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>
#include <QFile>
#include <QIODevice>
#include <QTextDocument>
#include "documentmodel.h"

class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(const QString& name, QObject* parent = nullptr);
    explicit Document(QFile &file, QObject* parent = nullptr);
    bool save();
    bool saveAs(QString& name);
    bool isValid() const;
    QString name() const;
    QTextDocument* textDocument();
    bool isDirty() const;

signals:
    void nameChanged(QString name);
    void dirtyChanged(bool dirty);

public slots:
private:
    QTextDocument* data = nullptr;
    QString documentname;
    QString documentpath;
    DocumentModel* model = nullptr;
    bool valid;
};

#endif // DOCUMENT_H
