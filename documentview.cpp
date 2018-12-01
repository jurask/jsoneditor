#include "documentview.h"
#include "ui_documentview.h"

DocumentView::DocumentView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DocumentView)
{
    ui->setupUi(this);
}

DocumentView::~DocumentView()
{
    delete ui;
}
