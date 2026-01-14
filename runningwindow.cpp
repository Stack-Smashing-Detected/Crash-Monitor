#include "runningwindow.h"
#include "ui_runningwindow.h"
#include "headers/application_manager.h"
#include "headers/process_algorithms.h"

RunningWindow::RunningWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RunningWindow)
{
    ui->setupUi(this);


}

RunningWindow::~RunningWindow()
{
    delete ui;
}
