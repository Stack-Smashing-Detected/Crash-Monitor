#include "app_resource_viewer.h"
#include "ui_app_resource_viewer.h"

AppResourceViewer::AppResourceViewer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppResourceViewer)
{
    ui->setupUi(this);
}

AppResourceViewer::~AppResourceViewer()
{
    delete ui;
}
