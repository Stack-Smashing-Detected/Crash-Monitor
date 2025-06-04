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

}

