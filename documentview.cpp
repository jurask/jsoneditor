#include "documentview.h"
#include "ui_documentview.h"

#include <QMessageBox>

DocumentView::DocumentView(const QString &name, QWidget* parent) : QWidget(parent), ui(new Ui::DocumentView){
    ui->setupUi(this);
    document = new Document(name, this);
    ui->text->setDocument(document->textDocument());
    setWindowTitle(name);
    connect(document, &Document::nameChanged, this, &DocumentView::assembleTitle);
    connect(document, &Document::dirtyChanged, this, &DocumentView::assembleTitle);
    ui->stack->setCurrentIndex(2);
}

DocumentView::DocumentView(QFile& file, QWidget* parent) : QWidget (parent), ui(new Ui::DocumentView){
    ui->setupUi(this);
    document = new Document(file, this);
    if (!document->isValid()){
        QMessageBox::critical(this, "Error", "Error opening file");
        return;
    }
    ui->text->setDocument(document->textDocument());
    setWindowTitle(document->name());
    connect(document, &Document::nameChanged, this, &DocumentView::assembleTitle);
    connect(document, &Document::dirtyChanged, this, &DocumentView::assembleTitle);
}

DocumentView::~DocumentView(){
    delete ui;
}

QString DocumentView::documentName() const{
    return document->name();
}

bool DocumentView::isValid() const{
    return document->isValid();
}

bool DocumentView::isDirty() const{
    return document->isDirty();
}

void DocumentView::assembleTitle(){
    bool dirty = document->isDirty();
    QString title = document->name();
    if (!dirty)
        setWindowTitle(title);
    else
        setWindowTitle(title+"*");
}
