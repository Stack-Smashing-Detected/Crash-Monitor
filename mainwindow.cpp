#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QFont>
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

    // Style the title
    ui->title->setAlignment(Qt::AlignCenter);
    QFont titleFont = ui->title->font();
    titleFont.setBold(true);
    titleFont.setPointSize(20);
    ui->title->setFont(titleFont);

    // Style the subtitle
    ui->subtitle->setAlignment(Qt::AlignCenter);
    QFont subtitleFont = ui->subtitle->font();
    subtitleFont.setItalic(true);
    ui->subtitle->setFont(subtitleFont);

    // Style the instructions
    ui->instructions->setAlignment(Qt::AlignLeft);
    ui->instructions->setStyleSheet("""margin-top: 10px""");

    // Generate the eye catch image in the eyeCatch label
    ui->eyeCatch->setScaledContents(true);
    ui->eyeCatch->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_runBtn_clicked()
{
    // run the crash monitor program, include a loading message if needed.
}

void MainWindow::on_helpBtn_clicked()
{
    // open the help tab for assistance on using the application
    helpWindow = new HelpWindow(this);
    helpWindow->show();
}


void MainWindow::on_settingsBtn_clicked()
{
    // open the settings tab to change application settings.
    settings = new Settings(this);
    settings->show();
}

void MainWindow::on_viewBtn_clicked(){
    // open the view processes window
    app_resource_viewer = new AppResourceViewer(this);
    app_resource_viewer->show();
}


