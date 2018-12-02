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

private:
    Ui::DocumentView *ui;
    Document* document;
};

#endif // DOCUMENTVIEW_H
