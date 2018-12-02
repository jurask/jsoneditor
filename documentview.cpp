#include "documentview.h"
#include "ui_documentview.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QCloseEvent>

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

void DocumentView::saveAs(){
    QString filename = QFileDialog::getSaveFileName(this, tr("Save file as"), QDir::homePath(), tr("Json files (*.json);;All files (*.*)"));
    if (filename != ""){
        if (!document->saveAs(filename))
            QMessageBox::critical(this, "Error", "Error saving file");
    }
}

void DocumentView::save(){
    if (!document->hasPath()){
        saveAs();
        return;
    }
    if (!document->save())
        QMessageBox::critical(this, "Error", "Error saving file");
}

bool DocumentView::close(){
    if (document->isDirty()){
        QMessageBox::StandardButton btn = QMessageBox::warning(this, "Document not saved", "Document " + document->name() + " not saved, do you want to save it?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (btn == QMessageBox::Yes){
            save();
            return true;
        } else if (btn == QMessageBox::No)
            return true;
        else
            return false;
    } else
        return true;
}

void DocumentView::closeEvent(QCloseEvent *event){
    if (close())
        event->accept();
    else
        event->ignore();
}
