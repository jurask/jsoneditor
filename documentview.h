#ifndef DOCUMENTVIEW_H
#define DOCUMENTVIEW_H

#include <QWidget>

#include "document.h"

namespace Ui {
class DocumentView;
}

class DocumentView : public QWidget
{
    Q_OBJECT

public:
    explicit DocumentView(const QString& name, QWidget* parent = nullptr);
    explicit DocumentView(QFile& file, QWidget* parent = nullptr);
    ~DocumentView();
    QString documentName() const;
    bool isValid() const;
    bool isDirty() const;
    void saveAs();
    void save();

private slots:
    void assembleTitle();

private:
    Ui::DocumentView *ui;
    Document* document;

signals:
    void dirtyChanged(bool dirty);
};

#endif // DOCUMENTVIEW_H
