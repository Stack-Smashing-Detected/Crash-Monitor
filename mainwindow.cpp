#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QString>
#include <QFrame>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/images/app-visual.png");

    // set the eye catch image
    ui->eyeCatch->setScaledContents(true);
    ui->eyeCatch->setPixmap(pix);

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_runBtn_clicked()
{
    // run the crash monitor program, include a loading message while it waits to collect
    // data and run the program.
}





void MainWindow::on_helpBtn_clicked()
{
    // open the help tab for assistance on using the application
    helpWindow = new HelpWindow(this);
    helpWindow->show();
}

