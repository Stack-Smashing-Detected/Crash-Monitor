#include "app_resource_viewer.h"
#include "ui_app_resource_viewer.h"
#include "headers/process_finder.h"
#include <memory>
#include <QVBoxLayout>



AppResourceViewer::AppResourceViewer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppResourceViewer)
{
    ui->setupUi(this);

    // Create a diectory pointer to pass to the process finder
    DIR *dirp;
    // create an instance of the process finder object, eventually this will be used as a shared pointer.
    std::unique_ptr<ProcessFinder> processListPtr = std::make_unique<ProcessFinder>(dirp);
    std::vector<std::string> appList = processListPtr->getProcessList();

    // set up list viewers
    cpuTab = ui->tabWidget->widget(0);
    ramTab = ui->tabWidget->widget(1);

    cpuUsageView = new QListWidget(cpuTab);
    ramUsageView = new QListWidget(ramTab);

    // style lists
    QVBoxLayout *qvBoxLayoutT1 = new QVBoxLayout;
    qvBoxLayoutT1->addWidget(cpuUsageView);

    QVBoxLayout *qvBoxLayoutT2 = new QVBoxLayout;
    qvBoxLayoutT2->addWidget(ramUsageView);

    cpuTab->setLayout(qvBoxLayoutT1);
    ramTab->setLayout(qvBoxLayoutT2);

    // fill lists
    fillListViewer(appList, cpuUsageView);
    fillListViewer(appList, ramUsageView);
}
AppResourceViewer::~AppResourceViewer()
{
    delete ui;
}

void AppResourceViewer::fillListViewer(std::vector<std::string> &appList, QListWidget *listWidget){
    for (const std::string &item: appList){
        listWidget->addItem(QString::fromStdString(item));
    }
}
