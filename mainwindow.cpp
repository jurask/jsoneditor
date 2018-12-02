#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "documentview.h"

#include <QActionGroup>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    // group view actions
    QActionGroup* group = new QActionGroup(this);
    group->addAction(ui->actionText);
    group->addAction(ui->actionSingle_column);
    group->addAction(ui->actionDouble_column);
    // connect exit action
    connect(ui->actionExit, &QAction::triggered, qApp, QApplication::quit);

}

MainWindow::~MainWindow(){
    delete ui;
}

QString MainWindow::nextDocumentName(const QString& baseName) const{
    // assemble list of names
    QStringList names;
    for (QMdiSubWindow* window :  ui->mdiArea->subWindowList()){
        DocumentView* documentView = static_cast<DocumentView*>(window->widget());
        names << documentView->documentName();
    }
    // check is base name exists
    if (!names.contains(baseName))
        return baseName;
    // try different indexes until suitable one is found
    unsigned int index = 2;
    while(true){
        QString proposedName = baseName + " " + QString::number(index);
        if (!names.contains(proposedName))
            return proposedName;
        index++;
    }
}

void MainWindow::on_actionNew_triggered(){
    //create
    DocumentView * document = new DocumentView(nextDocumentName(tr("New document")), this);
    document->setAttribute(Qt::WA_DeleteOnClose);
    ui->mdiArea->addSubWindow(document);
    document->show();
}

void MainWindow::on_actionClose_triggered(){
    ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::on_actionOpen_triggered(){
    QString filename = QFileDialog::getOpenFileName(this, tr("Open file"), QDir::homePath(), tr("Json files (*.json);;All files (*.*)"));
    if (filename != ""){
        QFile file(filename);
        DocumentView* document = new DocumentView(file, this);
        if (!document->isValid()){
            delete document;
            return;
        }
        document->setAttribute(Qt::WA_DeleteOnClose);
        ui->mdiArea->addSubWindow(document);
        document->show();
    }
}
